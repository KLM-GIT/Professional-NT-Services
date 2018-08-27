#include <windows.h>

void main ()
{
	HANDLE hToken;
	if( OpenProcessToken(GetCurrentProcess(),
		TOKEN_QUERY, &hToken ) )
	{
		//Determine buffer space neede
		DWORD cbInfo = 0;
		if ( !GetTokenInformation( hToken, TokenUser, 0, 0, &cbInfo )
				&& ERROR_INSUFFICIENT_BUFFER == GetLastError() )
		{
			TOKEN_USER* pTUser = (TOKEN_USER*) malloc( cbInfo );
			GetTokenInformation( hToken, TokenUser, pTUser, cbInfo, &cbInfo );
			
			PSID pSID = pTUser->User.Sid;

			DWORD cbName = 255;
			TCHAR lpName[255]  = {0};
			DWORD cbDomName = 1024;
			TCHAR lpDom[1024] = {0};
			SID_NAME_USE Use;

			if( LookupAccountSid( 0, pSID,	lpName, &cbName,  
						lpDom, &cbDomName, &Use ) )
			{
				//Do something with it...
			}
		}
	}
}
