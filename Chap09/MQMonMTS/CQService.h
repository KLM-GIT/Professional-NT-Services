#include "cservice.h"

#define NUMWORKERS 4
#define MAX_QUEUE_PATH 257

class CQueueService : public CService
{
public:
	CQueueService( LPCTSTR szName, LPCTSTR szDisplay, DWORD dwType );
	~CQueueService();
	
	virtual void Run( );

	DECLARE_SERVICE( CQueueService, MQAgentMTS )

protected:
	virtual void OnStop( );
	virtual void Init( );
	virtual void DeInit( );

//Attributes
	BOOL m_bStop;

//Implementation -- work specific
	HRESULT CreateQueue();
	BOOL OpenQueue( LPWSTR wszName, LPWSTR wszLabel );
	void CloseQueue();

	void RetrieveMessage();
	BOOL SendMessage( LPTSTR szFNQueue, TCHAR* szLabel, TCHAR* szMsg );
	static DWORD WINAPI TFuncType( LPVOID lpParameter );

	TCHAR m_wszQueueName[MAX_QUEUE_PATH];
	TCHAR m_wszFormatName[MAX_QUEUE_PATH];
	TCHAR m_wszQueueLabel[MAX_QUEUE_PATH];

	BOOL m_bOpen;

private:
	HANDLE m_hWorkers[NUMWORKERS];
	DWORD m_dwWorkerID[NUMWORKERS];
	QUEUEHANDLE m_hQueue;
};
