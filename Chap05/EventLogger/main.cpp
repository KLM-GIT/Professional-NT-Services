#include "precomp.h"
#include "EventLog.h"

int main()
{
   CEventLog log(_T("logtest"));

   // **Change to your path**
   log.RegisterLog(_T("D:\\Temp\\EventLogMsg.dll"));

   // Simple write
   log.LogEvent(LOGTEST_INFO_1, EVENTLOG_INFORMATION_TYPE);

   // Single string write
   log.LogEvent(LOGTEST_ERROR, _T("c:\\dummy.txt"));

   // Win32 error write
   log.LogWin32Error(LOGTEST_WIN32_ERROR, NULL, 1234);

   // Data Write
   struct LOGTEST_DUDLEY
   {
      int  d1;
      char name[25];
   } dummy = {51, "ABCDEFGHI"};

   log.LogEvent(LOGTEST_ERROR_WITH_DATA, sizeof(LOGTEST_DUDLEY), &dummy);
   return 0;
}
