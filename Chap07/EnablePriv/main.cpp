#include <windows.h>

void main( )
{
	TCHAR* pszCmdLine = __TEXT("TaskMgr.exe");
	
	HANDLE hToken;
	TOKEN_PRIVILEGES tokpriv;
	tokpriv.PrivilegeCount = 1;
	LookupPrivilegeValue( NULL, SE_DEBUG_NAME, 
		&tokpriv.Privileges[0].Luid );
	tokpriv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	if( OpenProcessToken(GetCurrentProcess(),
		TOKEN_ADJUST_PRIVILEGES, &hToken ) )
	{
		if( AdjustTokenPrivileges( hToken, FALSE, &tokpriv, 
				sizeof(tokpriv), NULL, NULL ) )
		{
			ShellExecute( NULL, NULL, pszCmdLine, NULL,
				NULL, SW_SHOWNORMAL );
		}
	}	
	CloseHandle( hToken );
}