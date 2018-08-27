#define UNICODE
#define _UNICODE

#include <windows.h>
#include <aclapi.h>
#include <TCHAR.h>
#include <stdio.h>

void main()
{
	ACL* pNewdacl = 0;
	ACL* pOlddacl = 0;

	SECURITY_DESCRIPTOR sd;
	PSECURITY_DESCRIPTOR psd;
	DWORD dwNeeded = 0;

	EXPLICIT_ACCESS ea;
   	SC_HANDLE hSCM = NULL;
	SC_HANDLE hService = NULL;
	BOOL bDaclHere = FALSE, bDaclDefault = FALSE;

	//Set up the ACE that I want to put into the DACL
	BuildExplicitAccessWithName(&ea, __TEXT("NORTHAMERICA\\kevmill"), SERVICE_START,
                                                DENY_ACCESS, NO_INHERITANCE);

	//Open the SCM and service, requesting the proper access (WRITE_DAC|READ_CONTROL)
	hSCM = OpenSCManager( NULL,
							NULL,
							SC_MANAGER_CONNECT );
	
	hService = OpenService(hSCM, _TEXT("BusObject"), WRITE_DAC | READ_CONTROL );
	
	//Query the service for its existing DACL. Don't know how big a buffer to allocate,
	//so ask first.
	BOOL bret =	QueryServiceObjectSecurity( hService, DACL_SECURITY_INFORMATION, 
		psd, 0, &dwNeeded);

	if (!bret)
	{
		// Allocate a buffer of the size the Query call said it needed
		psd = (PSECURITY_DESCRIPTOR)LocalAlloc(LHND, dwNeeded);
		
		// Call again with the right size buffer
		bret = QueryServiceObjectSecurity( hService, DACL_SECURITY_INFORMATION, 
		psd, dwNeeded, &dwNeeded);
	}

	if (bret)
	{
		//Get the DACL out of the SD we just obtained
		GetSecurityDescriptorDacl(psd, &bDaclHere, &pOlddacl,
                                     &bDaclDefault);
		//Merge the new ACE with the old DACL. 
		SetEntriesInAcl(1, &ea, pOlddacl, &pNewdacl);

		//Initialize a new SD to hold the new DACL
		InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
		
		//Add the new DACL to the new SD
		SetSecurityDescriptorDacl(&sd, TRUE, pNewdacl, FALSE);

		//Replace the existing SD on the service with the new SD
		bret = SetServiceObjectSecurity(hService, DACL_SECURITY_INFORMATION,
                &sd);

		if (bret)
			_tprintf( _TEXT("SetObjectSecurity Succeeded!") );
		else
			_tprintf( _TEXT("SetObjectSecurity Failed!") );
	}

	if (hService) CloseServiceHandle( hService );
	if (hSCM) CloseServiceHandle( hSCM );
	LocalFree(pNewdacl);
	LocalFree(psd);
	return;
}
