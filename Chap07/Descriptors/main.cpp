#include <windows.h>
#include <aclapi.h>

void ChangeMutexDacl(  );

void main()
{
	SECURITY_DESCRIPTOR sd;
	InitializeSecurityDescriptor( &sd, SECURITY_DESCRIPTOR_REVISION );

	EXPLICIT_ACCESS ea[2];
	BuildExplicitAccessWithName( &ea[0], __TEXT("Guests"), MUTEX_ALL_ACCESS,
		GRANT_ACCESS, NO_INHERITANCE );

	BuildExplicitAccessWithName( &ea[1], __TEXT("kxm"), MUTEX_ALL_ACCESS,
		GRANT_ACCESS, NO_INHERITANCE );

	ACL* pdacl = 0;

	SetEntriesInAcl( 2, &ea[0], 0, &pdacl );

	SetSecurityDescriptorDacl( &sd, TRUE, pdacl, FALSE );
	SECURITY_ATTRIBUTES sa = { sizeof sa, &sd, FALSE };
	HANDLE hMutex = CreateMutex( &sa, FALSE, __TEXT("MyMutex") );

	LocalFree( pdacl );

	//Do work
	//........


	//ChangeDACL on MUTEX
	ChangeMutexDacl( );

	CloseHandle( hMutex );

}

void ChangeMutexDacl ()
{
	ACL* pOlddacl = 0;
	ACL* pNewdacl = 0;
	EXPLICIT_ACCESS ea;

	BuildExplicitAccessWithName( &ea, __TEXT("Guests"), MUTEX_ALL_ACCESS,
		GRANT_ACCESS, NO_INHERITANCE );
	
	HANDLE hMutex = OpenMutex( MUTEX_ALL_ACCESS, FALSE, __TEXT("MyMutex"));

	GetSecurityInfo( hMutex, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 
			NULL, NULL, &pOlddacl, NULL, NULL );
	
	SetEntriesInAcl( 1, &ea, pOlddacl, &pNewdacl );
	
	SetSecurityInfo( hMutex, SE_KERNEL_OBJECT, DACL_SECURITY_INFORMATION, 
			NULL, NULL, pNewdacl, NULL );
	
	LocalFree( pNewdacl );
	LocalFree( pOlddacl );
	CloseHandle( hMutex );
}