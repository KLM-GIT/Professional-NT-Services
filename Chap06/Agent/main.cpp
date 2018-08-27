#include "precomp.h"
#include "eventlog.h"
#include "QService.h"
#include "CServiceInstall.h"

int main()
{
   LPTSTR szName = _T("MQAgent");
   LPTSTR szDisplay = _T("MQ Agent Service");

   // Process command line
   TCHAR* pszCmdLine = GetCommandLine();
   CharLowerBuff(pszCmdLine, lstrlen(pszCmdLine));
   if(_tcsstr(pszCmdLine, _T("-install")))
   {
      CServiceInstall si(szName, szDisplay);
      si.Install();

      CEventLog log(szName);
      log.RegisterLog(_T("D:\\Temp\\AgentMsg.dll"));
      return 0;
   }
   else if(_tcsstr(pszCmdLine, _T("-remove")))
   {
      CServiceInstall si(szName, szDisplay);
      si.Remove();
      return 0;
   }

   CQueueService Agent(szName, szDisplay, SERVICE_WIN32_OWN_PROCESS);

   // Set up an entry for the one service and go
   BEGIN_SERVICE_MAP
      SERVICE_MAP_ENTRY(CQueueService, MQAgent)
   END_SERVICE_MAP

   return 0;
}
