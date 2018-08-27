// CtrlPan.h

#ifndef _CTRLPAN_H_
#define _CTRLPAN_H_

#include <cpl.h> // control panel definitions

class CControlPanel
{
public:
	LONG OnInquire( UINT uAppNum, CPLINFO* pInfo );
    CControlPanel();
    virtual ~CControlPanel();    

    // Event handlers
    virtual LONG OnDblclk(HWND hwndCPl, UINT uAppNum, LONG lData); 
    virtual LONG OnExit();
    virtual LONG OnGetCount();
    virtual LONG OnInit();
    virtual LONG OnNewInquire(UINT uAppNum, NEWCPLINFO* pInfo); 
    virtual LONG OnStop(UINT uAppNum, LONG lData); 

    // static member functions (callbacks)
    static LONG APIENTRY CPlApplet(HWND hwndCPl, UINT  uMsg,
                                   LONG lParam1, LONG lParam2);

    // static data
    static CControlPanel* m_pThis;
};

#endif // _CTRLPAN_H_
