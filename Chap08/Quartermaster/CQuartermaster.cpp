#include "precomp.h"
#include "CQuartermaster.h"

const int HANDLEALLOCCOST = 1000;  // Simulated time for allocation
const int SPINX = 5000;            // Spin count for critical sections

//----------------------------------------
//
// List Class members
//


CFreeList::CFreeList() : m_pHead(NULL), m_pTail(NULL), m_Count(0)
{
   InitializeCriticalSection/*AndSpinCount*/(&m_cs/*, SPINX*/);
}

CFreeList::~CFreeList()
{
   RemoveAll();
   DeleteCriticalSection(&m_cs);
}

void CFreeList::AddTail(const RHANDLE* newHandle)
{
   NODE* pNew = new NODE;
   pNew->pRH = newHandle;
   pNew->prev = NULL;
   pNew->next = NULL;

   EnterCriticalSection(&m_cs);

   if(m_pTail == NULL)                           // List is empty
      m_pHead = pNew;
   else
   {
      pNew->prev = m_pTail;
      m_pTail->next = pNew;
   }

   m_pTail = pNew;
   m_Count++;

   LeaveCriticalSection(&m_cs);
}

void CFreeList::RemoveAll()
{
   NODE* pNext = 0;

   EnterCriticalSection(&m_cs);

   NODE* p = m_pHead;
   while(p != NULL)
   {
      pNext = p->next;
      delete p;
      p = pNext;
   }
   m_pHead = m_pTail = NULL;
   m_Count = 0;

   LeaveCriticalSection(&m_cs);
}

const RHANDLE* CFreeList::Pop()
{
   const RHANDLE* rh = 0;
   EnterCriticalSection(&m_cs);

   NODE* p = m_pHead;
   if(p != NULL)
   {
      // Obtain RHANDLE
      rh = p->pRH;

      if(p->next)
      {
         p->next->prev = NULL;
         m_pHead = p->next;
      }
      else
         m_pHead = m_pTail = NULL;

      delete p;
      m_Count--;
   }

   LeaveCriticalSection( &m_cs );
   return rh;
}

//---------------------------------------------------------------------------
// CResourceArray Class

CResourceArray::CResourceArray(long dwSize) : m_size(dwSize), m_count(0)
{
   InitializeCriticalSection/*AndSpinCount*/(&m_cs/*, SPINX*/);

   m_pHandles = new RHANDLEHEADER* [dwSize];
   memset(m_pHandles, 0, sizeof(RHANDLEHEADER*) * dwSize);
}

CResourceArray::~CResourceArray()
{
   RemoveAll();                                  // Just in case
   delete [] m_pHandles;
   m_size = 0;
   m_pHandles = NULL;
   DeleteCriticalSection(&m_cs);
}

const RHANDLE* CResourceArray::Add()
{
   long hSession = 0;
   RHANDLE* chd = 0;

   EnterCriticalSection(&m_cs);
   if(m_count < m_size)
   {
      hSession = GetResourceHandle();
      if(hSession != 0)
      {
         RHANDLEHEADER* pSH = new RHANDLEHEADER;
         chd = new RHANDLE;
         chd->handle = hSession;
         chd->pos = m_count; 

         pSH->pRH = chd;
         pSH->bFree = true;
         pSH->dwTime = 0;

         m_pHandles[m_count] = pSH;
         m_count++;
      }
      else
      {
         // Event Log call
         OutputDebugString(__TEXT("Handle could not be allocated\n"));
      }
   }
   LeaveCriticalSection( &m_cs );

   return chd;
}

void CResourceArray::RemoveAll()
{
   RHANDLEHEADER* pTemp = 0;

   EnterCriticalSection(&m_cs);
   for(int i = 0 ; i < m_count ; i++)
   {
      pTemp = m_pHandles[i];
      if(pTemp)
      {
         const RHANDLE* pRHTemp = pTemp->pRH;
         if(pRHTemp)
         {
            ReleaseResourceHandle(pRHTemp->handle);
            delete (RHANDLE*)pRHTemp;
         }
         delete pTemp;
      }
      m_pHandles[i] = NULL;
   }
   m_count = 0;
   LeaveCriticalSection(&m_cs);
}

long CResourceArray::GetResourceHandle()
{
   // Call connection function (fake allocator below)
   long handle = 10000 + m_count;
   return handle;
}

void CResourceArray::ReleaseResourceHandle(long hResHandle)
{
#ifdef _DEBUG
   CHAR sz[100] = {0};
   wsprintf(sz, "Handle Dellocated-------------->%Handle: %d\n", hResHandle);
   OutputDebugString(sz);
#endif
}

//---------------------------------------------------------------------------
//
// CQuartermaster Class
//
//

CQuartermaster* CQuartermaster::m_pThis = 0;

CQuartermaster::CQuartermaster() : m_dwNumCurrentResources(0), m_bStartAllocator(false)
{
	m_pThis = this;
	InitializeCriticalSection/*AndSpinCount*/(&m_cs/*, SPINX*/);
}

void CQuartermaster::Init(DWORD dwMaxResources,      DWORD dwStartResources,
                          DWORD dwWaitForHandleTime, DWORD dwHandleLifeTime,
                          DWORD dwAllocationPoll,    DWORD dwMinPoolSize,
                          DWORD dwResourceAllocSize, DWORD dwDeadResourcePoll)
{
   // Event to signal workers to stop
   m_hStopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
   m_dwStartResources = dwStartResources;
   m_dwMaxResources = dwMaxResources;
   m_dwWaitForHandleTime = dwWaitForHandleTime;
   m_dwHandleLifeTime = dwHandleLifeTime;
   m_dwAllocationPoll = dwAllocationPoll;
   m_dwMinPoolSize = dwMinPoolSize;
   m_dwResourceAllocSize = dwResourceAllocSize;
   m_dwDeadResourcePoll =dwDeadResourcePoll;

   m_pResources = new CResourceArray(dwMaxResources);
   m_pFreeList = new CFreeList;

   // Initialize the Semaphore with max possible no. of resources
   m_hSem = CreateSemaphore(NULL, 0, dwMaxResources, NULL);

   DWORD dwAid;
   DWORD dwPid;
   m_hAllocThread = CreateThread(0, 0, &CQuartermaster::AllocateMoreResourcesThread, 0, 0, &dwAid);
   m_hRefreshThread = CreateThread(0, 0, &CQuartermaster::RefreshDeadResourcesThread, 0, 0, &dwPid);
}

CQuartermaster::~CQuartermaster()
{
   if(m_hAllocThread)
      CloseHandle(m_hAllocThread);
   if(m_hRefreshThread)
      CloseHandle(m_hRefreshThread);

   CloseHandle(m_hSem);

   delete m_pResources;
   m_pResources = NULL;

   delete m_pFreeList;
   m_pFreeList = NULL;

   DeleteCriticalSection(&m_cs);
}

DWORD CQuartermaster::GetFreeResource(const RHANDLE** poutHandle)
{
   // Function does *not* find a handle *known* to be valid. It is up to the
   //  client to check handle validity and retry if necessary.
   const RHANDLE* pHandle = 0;

   // Wait on the semaphore. I can block for a short time if no handles left.
   if(WaitForSingleObject(m_hSem, m_dwWaitForHandleTime) == WAIT_OBJECT_0)
   {
      // Get the handle and give it out
      pHandle = m_pFreeList->Pop();
      if(pHandle)
      {
         // Mark time and busy
         m_pResources->SetBusy(pHandle->pos);
         *poutHandle = pHandle;
         return 0;
      }
   }

   *poutHandle = NULL;
   return E_NORESOURCESAVAILABLE;
}

void CQuartermaster::ReleaseResource(const RHANDLE* handle)
{
   // Make sure handle hasn't been released twice by client accidentally
   if(handle)
   {
      if(m_pResources->IsFree(handle->pos) == false)
      {
         long lPrev;
         m_pResources->SetFree(handle->pos);
         m_pFreeList->AddTail(handle);
         ReleaseSemaphore(m_hSem, 1, &lPrev);
      }
   }
}

DWORD CQuartermaster::AllocateResources(DWORD dwNumAdd)
{
   DWORD count = 0;
   const RHANDLE* pRH = 0;
   DWORD newRes = 0;

   DWORD dwNumRes = GetNumResources();

   if(dwNumAdd + dwNumRes > m_dwMaxResources)
      newRes = m_dwMaxResources - dwNumRes;
   else
      newRes = dwNumAdd;

   // Connect the sessions
   for(DWORD i = 0 ; i < newRes ; i++)
   {
      pRH = m_pResources->Add();
      if(pRH)
      {
         m_pFreeList->AddTail(pRH);
         count++;
      }
   }

   InterlockedExchangeAdd((long*)&m_dwNumCurrentResources, count);

   // Release Semaphore 'count' number of times
   if(count > 0)
   {
      long dwPrev;
      ReleaseSemaphore(m_hSem, (long)count, &dwPrev);
   }

   // Write to event log that x new handles were allocated
   // Also write if maximum session limit was reached

#ifdef _DEBUG
   CHAR sz[100] = {0};
   wsprintf(sz, "Allocations were increased----->%lu\n", m_dwNumCurrentResources);
   OutputDebugString(sz);
#endif

   // Allow the allocator thread to start, if it hasn't before
   if(!m_bStartAllocator)
      InterlockedExchange((long*)&m_bStartAllocator, true);

   // Return
   return count;
}

void CQuartermaster::DeallocateResources()
{
   EnterCriticalSection(&m_cs);

   // Stop the allocator/deadresource threads
   SetStop();

   m_dwNumCurrentResources = 0;
   m_pResources->RemoveAll();
   m_pFreeList->RemoveAll();

   LeaveCriticalSection(&m_cs);
}

// Will be called on a schedule by another thread
void CQuartermaster::ReleaseDeadResources()
{
   // Walk the list and see if any bFrees are false with
   //  (now - timestamp) > m_dwHandleLifetime
   //  If so, bFree = true and add back to free list
   CRITICAL_SECTION cs;
   InitializeCriticalSection(&cs);

   DWORD now = GetTickCount();
   RHANDLEHEADER* pTemp = 0;
   DWORD stamp = 0;

   long count = m_pResources->GetCount();
   for(long i = 0 ; i < count ; i++)
   {
      pTemp = m_pResources->m_pHandles[i];
      if(pTemp)
      {
         EnterCriticalSection(&cs);
         if(m_pResources->IsFree(i) == false)
         {
            stamp = pTemp->dwTime;
            if(now - stamp > m_dwHandleLifeTime)
            {
               if(pTemp->pRH)
               {
                  m_pResources->SetFree(i);
                  m_pFreeList->AddTail(pTemp->pRH);
               }
            }
         }
         LeaveCriticalSection(&cs);
      }
   }
   DeleteCriticalSection(&cs);
}

/////////
//Background task threads
/////////

DWORD WINAPI CQuartermaster::AllocateMoreResourcesThread(LPVOID lpParameter)
{
   while(WaitForSingleObject(m_pThis->m_hStopEvent, m_pThis->m_dwAllocationPoll) == WAIT_TIMEOUT)
   {
      if(m_pThis->FreeResourcesLeft() <= m_pThis->m_dwMinPoolSize && m_pThis->m_bStartAllocator)
      {
         m_pThis->AllocateResources(m_pThis->m_dwResourceAllocSize);
         Sleep(HANDLEALLOCCOST);    // *Simulation* of amount of time it takes
      }
   }
   return 0;
}

DWORD WINAPI CQuartermaster::RefreshDeadResourcesThread(LPVOID lpParameter)
{
   while(WaitForSingleObject(m_pThis->m_hStopEvent, m_pThis->m_dwDeadResourcePoll) == WAIT_TIMEOUT)
   {
      m_pThis->ReleaseDeadResources();
   }
   return 0;
}
