#include "precomp.h"
#include "CQuartermaster.h"

DWORD WINAPI ThreadFunc(LPVOID lpParameter);
CQuartermaster* g_pQM = new CQuartermaster;

const int NUMCLIENTS = 64;
const int SLEEP = 0;                 // 'Work time' for each thread - i.e. how
                                     //   long it will hold the resource
const int NUMALLOC = 1000;           // Number of times each thread will run
const int NUMSTARTRESOURCES = 5;     // Number of handles to start with
const int MAXPOSSIBLE = 100;         // Maximum number of handles that can be
                                     //   allocated
const int WAITFORHANDLE = 2000;      // Time a client will wait for a handle
const int HANDLEEXPIRES = 600000;    // 10 minutes - time each resource can
                                     //   live before being considered 'dead'
const int DEADRESOURCEPOLL = 600000; // 10 minutes - time between each garbage
                                     //   collection
const int ALLOCATIONPOLL = 2000;     // ms between each check for whether to
                                     //   allocate more
const int RESOURCEALLOCSIZE = 1;     // Number of resources to add at a time
const int MINPOOLSIZE = 0;           // Least amount of resources before
                                     //   adding more

int main()
{
   g_pQM->Init(MAXPOSSIBLE, NUMSTARTRESOURCES, WAITFORHANDLE, HANDLEEXPIRES,
            ALLOCATIONPOLL, MINPOOLSIZE, RESOURCEALLOCSIZE, DEADRESOURCEPOLL);

   // Do a bunch of allocations
   g_pQM->AllocateResources(NUMSTARTRESOURCES);

   // Main line client calls
   DWORD sTime = GetTickCount();
   CHAR sz[100];

   HANDLE hThread[NUMCLIENTS] = {0};
   DWORD dwID[NUMCLIENTS] = {0};
   for(int s = 0 ; s < NUMCLIENTS ; s++)
   {
      hThread[s] = CreateThread(0, 0, &ThreadFunc, 0, 0, &dwID[s]);
      wsprintf(sz, "Thread %d created with id: %lu\n", s, dwID[s]);
      OutputDebugString(sz);
   }

   // Wait for threads to complete. Can only wait for 64!
   WaitForMultipleObjects(NUMCLIENTS, &hThread[0], TRUE, INFINITE);

   // Timing output
   sTime = (GetTickCount() - sTime);
   wsprintf(sz, "Total Time was: %lu\n", sTime);
   OutputDebugString(sz);

   // FYI
   wsprintf(sz, "Final Allocated Resources were: %lu\n", g_pQM->GetNumResources());
   OutputDebugString(sz);

   // Deallocate
   g_pQM->DeallocateResources();

   for(int t = 0 ; t < NUMCLIENTS ; t++)
      CloseHandle(hThread[t]);

   delete g_pQM;
   return 0;
}


DWORD WINAPI ThreadFunc(LPVOID lpParameter)
{
   DWORD dwID = GetCurrentThreadId();
   CHAR sz[100];
   long h;
   const RHANDLE* pHandle = 0;

   for(int x = 0 ; x < NUMALLOC ; x++)
   {
      h = 0;
      DWORD ret = g_pQM->GetFreeResource(&pHandle);
      if(ret == 0)
      {
         h = pHandle->handle;

#ifdef _DEBUG
         wsprintf(sz, "Thread: %lu -- Count: %d -- HandleVal: %li \n", dwID, x, h);
         OutputDebugString(sz);
#endif

         Sleep(SLEEP);
         g_pQM->ReleaseResource(pHandle);
      }
      else
      {
         wsprintf(sz, "Could not get handle---->Thread: %lu -- Count: %d -- HandleVal: %li \n", dwID, x, h);
         OutputDebugString(sz);
      }
   }
   return 0;
}
