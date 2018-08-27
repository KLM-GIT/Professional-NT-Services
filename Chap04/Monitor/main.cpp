#include "precomp.h"
#include "cmonitor.h"
#include "cserviceinstall.h"

int main()
{
   LPTSTR szName = _T("Monitor");
   LPTSTR szDisplay = _T("Ping Monitoring Service");

   // Process command line
   TCHAR* pszCmdLine = GetCommandLine();
   CharLowerBuff(pszCmdLine, lstrlen(pszCmdLine));
   if(_tcsstr(pszCmdLine, _T("-install")))
   {
      CServiceInstall si(szName, szDisplay);
      si.Install();
      return 0;
   }
   else if(_tcsstr(pszCmdLine, _T("-remove")))
   {
      CServiceInstall si(szName, szDisplay);
      si.Remove();
      return 0;
   }

   // Good place to step in and debug
   // DebugBreak();

   // Create the object instance
   CMonitor Monitor(szName, szDisplay, SERVICE_WIN32_OWN_PROCESS);

   // Set up an entry for the one service and go
   BEGIN_SERVICE_MAP
      SERVICE_MAP_ENTRY(CMonitor, Monitor)
   END_SERVICE_MAP

   return 0;
}
