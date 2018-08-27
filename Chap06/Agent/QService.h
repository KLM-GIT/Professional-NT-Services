#include "cservice.h"

const int MAX_QUEUE_PATH = 257;

class CQueueService : public CService
{
public:
   CQueueService(LPCTSTR szName, LPCTSTR szDisplay, DWORD dwType);
   virtual void Run();

DECLARE_SERVICE(CQueueService, MQAgent)

protected:
   virtual void OnStop();
   virtual void Init();
   virtual void DeInit();

   // Attributes
   bool m_bStop;

   // Implementation - work specific
   HRESULT CreateQueue();
   bool OpenQueue(LPWSTR wszName, LPWSTR wszLabel);

   bool SendMessage(LPTSTR szFNQueue, TCHAR* szLabel, TCHAR* szMsg);
   void RetrieveMessage();

   TCHAR m_wszQueueName[MAX_QUEUE_PATH];
   TCHAR m_wszFormatName[MAX_QUEUE_PATH];
   TCHAR m_wszQueueLabel[MAX_QUEUE_PATH];

   bool m_bOpen;

private:
   QUEUEHANDLE m_hQueue;
};
