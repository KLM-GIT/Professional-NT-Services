struct RHANDLE
{
   long handle;
   long pos;
};

struct RHANDLEHEADER
{
   const RHANDLE* pRH;
   bool bFree;
   DWORD dwTime;
};

struct NODE
{
   const RHANDLE* pRH;
   NODE* prev;
   NODE* next;
};

// List class is linked list of RHANDLEs
class CFreeList
{
public:
   CFreeList();
   ~CFreeList();

   const RHANDLE* Pop();
   void AddTail(const RHANDLE* newHandle);
   void RemoveAll();

   DWORD GetCount()
   {
      DWORD dwCount;
      EnterCriticalSection(&m_cs);
      dwCount = m_Count;
      LeaveCriticalSection(&m_cs);
      return dwCount;
   }

private:
   DWORD m_Count;
   NODE* m_pHead;
   NODE* m_pTail;
   CRITICAL_SECTION m_cs;
};

// CResourceArray Class manages data structures for handle information
class CResourceArray
{
public:
   CResourceArray(long dwSize);
   ~CResourceArray();

   RHANDLEHEADER** m_pHandles;
   long m_size;

   const RHANDLE* Add();
   void RemoveAll();

   void SetBusy(const long position)
   {
      m_pHandles[position]->bFree = false;
      m_pHandles[position]->dwTime = GetTickCount();
   }

   void SetFree(const long position)
   {
      m_pHandles[position]->bFree = true;
      m_pHandles[position]->dwTime = 0;
   }

   bool IsFree(const long position)
   {
      return m_pHandles[position]->bFree;
   }

   long GetCount()
   {
      long lRet;
      EnterCriticalSection(&m_cs);
      lRet = m_count;
      LeaveCriticalSection(&m_cs);
      return lRet;
   }

   long GetResourceHandle();
   void ReleaseResourceHandle(long hResHandle);

private:
   CRITICAL_SECTION m_cs;
   long m_count;
};


///////////////////////////////////////
class CQuartermaster
{
public:
   static CQuartermaster* m_pThis;

   // Constructors / destructors
   CQuartermaster();
   ~CQuartermaster();

   // Public methods
   void Init(DWORD dwMaxResources,      DWORD dwStartResources,
             DWORD dwWaitForHandleTime, DWORD dwHandleLifeTime,
             DWORD dwAllocationPoll,    DWORD dwMinPoolSize,
             DWORD dwResourceAllocSize, DWORD dwDeadResourcePoll);

   DWORD AllocateResources(DWORD dwNumAdd);
   void DeallocateResources();

   DWORD GetFreeResource(const RHANDLE** poutHandle);
   void ReleaseResource(const RHANDLE* pResource);
   void ReleaseDeadResources();

   DWORD FreeResourcesLeft()
   {
      DWORD dwCount;
      dwCount = m_pFreeList->GetCount();
      return dwCount; 
   }

   DWORD GetNumResources()
   {
      DWORD dwCount;
      EnterCriticalSection(&m_cs);
      dwCount = m_dwNumCurrentResources;
      LeaveCriticalSection(&m_cs);
      return dwCount;
   }

   void SetStop()
   {
      SetEvent(m_hStopEvent);
      WaitForSingleObject(m_hAllocThread, INFINITE);
      WaitForSingleObject(m_hRefreshThread, INFINITE);
   }

   static DWORD WINAPI AllocateMoreResourcesThread(LPVOID lpParameter);
   static DWORD WINAPI RefreshDeadResourcesThread(LPVOID lpParameter);

private:
   // Private attributes
   CFreeList* m_pFreeList;
   CResourceArray* m_pResources;

   DWORD m_dwNumCurrentResources;

   // Registry defaults
   DWORD m_dwStartResources;
   DWORD m_dwMaxResources;
   DWORD m_dwWaitForHandleTime;
   DWORD m_dwHandleLifeTime;
   DWORD m_dwAllocationPoll;
   DWORD m_dwMinPoolSize;
   DWORD m_dwResourceAllocSize;
   DWORD m_dwDeadResourcePoll;

   HANDLE m_hSem;                                // Semaphore
   CRITICAL_SECTION m_cs;
   HANDLE m_hStopEvent;
   bool m_bStartAllocator;

   // Static threads
   HANDLE m_hAllocThread;
   HANDLE m_hRefreshThread;
};
