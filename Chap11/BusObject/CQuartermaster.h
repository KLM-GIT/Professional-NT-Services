struct RHANDLE
{
	SQLHDBC handle; //type of handle changes
	long pos;
};

typedef struct tagRHANDLEHEADER
{
	const RHANDLE*	pRH;
	BOOL	bFree;
	DWORD	dwTime;

} RHANDLEHEADER;


class NODE
{
public:
	NODE(const RHANDLE* x): pRH(x), prev(NULL), next(NULL) {}

	const RHANDLE* pRH;
	NODE* prev;
	NODE* next;
} ;

//List class is linked list of RHANDLEs
class CFreeList
{
public:
	CFreeList();
	~CFreeList();
	
	const RHANDLE* Pop( );
	void AddTail( const RHANDLE* newHandle );

	DWORD GetCount( ) 
	{ 
		DWORD dwCount;
		EnterCriticalSection( &m_cs );
		dwCount = m_Count;
		LeaveCriticalSection( &m_cs );
		return dwCount;
	}
	
	void RemoveAll( );

private:
	DWORD m_Count;

	NODE* m_pHead;
	NODE* m_pTail;
	CRITICAL_SECTION m_cs;
};

//CResourceArray Class manages data structures for handle information
class CResourceArray
{
public:
	CResourceArray( long dwSize );
	~CResourceArray();

	RHANDLEHEADER** m_pHandles;
	long m_size;

	const RHANDLE* Add( );
	void RemoveAll( );
	void SetBusy( const long position )
	{	
		m_pHandles[position]->bFree = FALSE;
		m_pHandles[position]->dwTime = ::GetTickCount( );
	}
	void SetFree( const long position )
	{
		m_pHandles[position]->bFree = TRUE;
		m_pHandles[position]->dwTime = 0;
	}
	
	BOOL IsFree( const long position )
	{
		BOOL bFree;
		bFree = m_pHandles[position]->bFree;
		return bFree;
	}

	long GetCount()
	{
		long lRet;
		EnterCriticalSection( &m_cs );
		lRet = m_count;
		LeaveCriticalSection( &m_cs );
		return lRet;
	}

	void AllocateEnvironment();
	SQLHDBC GetResourceHandle( );
	void ReleaseResourceHandle( SQLHDBC hResHandle );
	void Init( LPTSTR szServer, LPTSTR szLogin, LPTSTR szPassword);

private:
	SQLHENV m_hEnv;
	CRITICAL_SECTION m_cs;	
	long m_count;

	//Added for database connection
	TCHAR m_szPassword[25];
	TCHAR m_szLogin[25];
	TCHAR m_szServer[25];
};


///////////////////////////////////////
class CQuartermaster
{
public:
	//Constructors / destructors
	CQuartermaster();
	~CQuartermaster();

	static CQuartermaster* m_pThis;
	//Public methods
	void Init( 	DWORD dwMaxResources,
				DWORD dwStartResources,
				DWORD dwWaitForHandleTime,
				DWORD dwHandleLifeTime,
				DWORD dwAllocationPoll,
				DWORD dwMinPoolSize, 
				DWORD dwResourceAllocSize, 
				DWORD dwDeadResourcePoll,
				LPTSTR szServer, 
				LPTSTR szLogin,
				LPTSTR szPassword );

	DWORD AllocateResources( DWORD dwNumAdd );
	void DeallocateResources( );
	
	DWORD GetFreeResource( const RHANDLE** poutHandle );
	void ReleaseResource( const RHANDLE* pResource );

	void ReleaseDeadResources( );

	DWORD FreeResourcesLeft( ) 
	{
		DWORD dwCount;
		dwCount = m_pFreeList->GetCount();
		return dwCount; 
	}
	
	DWORD GetNumResources( ) 
	{
		DWORD dwCount;
		EnterCriticalSection(&m_cs);
		dwCount = m_dwNumCurrentResources;
		LeaveCriticalSection(&m_cs);
		return dwCount; 
	}

	void SetStop( ) 
	{
		SetEvent( m_hStopEvent );
		WaitForSingleObject(m_hAllocThread, INFINITE );
		WaitForSingleObject(m_hRefreshThread, INFINITE );
	}

	CResourceArray* GetResourceArray() {return m_pResources;} //Added for enumeration

	static DWORD WINAPI AllocateMoreResourcesThread( LPVOID lpParameter );
	static DWORD WINAPI RefreshDeadResourcesThread( LPVOID lpParameter );

private:
	//Private attributes
	CFreeList* m_pFreeList;
	CResourceArray* m_pResources;
	
	DWORD m_dwNumCurrentResources;

	//Registry defaults
	DWORD m_dwStartResources;
	DWORD m_dwMaxResources;
	DWORD m_dwWaitForHandleTime;
	DWORD m_dwHandleLifeTime;
	DWORD m_dwAllocationPoll;
	DWORD m_dwMinPoolSize;
	DWORD m_dwResourceAllocSize;
	DWORD m_dwDeadResourcePoll;

	HANDLE m_hSem; //Semaphore
	CRITICAL_SECTION m_cs;
	HANDLE m_hStopEvent;
	bool m_bStartAllocator;

	//Static threads
	HANDLE m_hAllocThread;
	HANDLE m_hRefreshThread;

};

