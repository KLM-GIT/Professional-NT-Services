#include "cservice.h"

class CMonitor : public CService
{
public:
   CMonitor(LPTSTR szName, LPTSTR szDisplay, DWORD dwType);
   virtual void Run();

DECLARE_SERVICE(CMonitor, Monitor)

protected:
   DWORD Ping();
   virtual void OnPause();
   virtual void OnContinue();
   virtual void OnStop();
   virtual void Init();
   virtual void DeInit();
   virtual void ParseArgs(DWORD argc, LPTSTR* argv);

//Attributes
   HANDLE m_hPauseNotifyEvent;

   CHAR m_pingAddress[25];
   DWORD m_nCycleTime;
   unsigned short m_nPort;

   bool m_bPause;
   bool m_bStop;
};
