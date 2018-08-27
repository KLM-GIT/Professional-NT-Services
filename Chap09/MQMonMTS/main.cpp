#include "precomp.h"
#include "CQService.h"
#include "CServiceInstall.h"

//BOOL g_bStop;
int main ( )
{
	LPTSTR szName = _T("MQAgentMTS");
	LPTSTR szDisplay = _T("MQ Agent/Monitor Calls MTS");

	//Process command line
	TCHAR* pszCmdLine = GetCommandLine();
	CharLowerBuff( pszCmdLine, lstrlen( pszCmdLine ) );
	if ( _tcsstr( pszCmdLine, _TEXT( "-install" ) ) )
	{
		CServiceInstall si = CServiceInstall( szName, szDisplay );
		si.Install();

		CEventLog log(szName);
		log.RegisterLog( _T("c:\\temp\\MQMonMTSMsg.dll"));

		return 0;
	}
	else if ( _tcsstr( pszCmdLine, _TEXT( "-remove" ) ) )
	{
		CServiceInstall si = CServiceInstall( szName, szDisplay );
		si.Remove();
		return 0;
	}

	CQueueService qservice ( szName, szDisplay, SERVICE_WIN32_OWN_PROCESS );

	//Set up an entry for the one service and go
	BEGIN_SERVICE_MAP
		SERVICE_MAP_ENTRY( CQueueService, MQAgentMTS )
	END_SERVICE_MAP

	return 0;
}

