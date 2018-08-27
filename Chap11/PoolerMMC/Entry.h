// Entry.h: interface for the CEntry class.
//
//////////////////////////////////////////////////////////////////////
#include <mmc.h>

#if !defined(AFX_ENTRY_H__C8FF6D20_F7C9_11D1_846A_0020AF05ED45__INCLUDED_)
#define AFX_ENTRY_H__C8FF6D20_F7C9_11D1_846A_0020AF05ED45__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CEntry;
typedef CEntry* LPENTRY;

class CEntry  {
public:
	CEntry();
	CEntry (LPOLESTR szName, int nTier, LPENTRY lpParent);
	CEntry (int pos, long handle, BOOL bFree, 
			int nTier, LPENTRY lpParent);
	~CEntry();


	int GetSubCount() {return m_nSubCount;}
	HSCOPEITEM GetScope () {return m_hScope;}
	int GetTier () {return m_nTier;}
	void SetScope (HSCOPEITEM hScope){m_hScope = hScope;}
	LPENTRY GetParent() {return m_pParent;}

	LPENTRY GetSubEntry (int pos)
	{ 
		if (pos >= m_nSubCount)
			return NULL;

		return m_pSubEntries[pos];
	}

	LPENTRY AddSubEntry (LPOLESTR szName);
	LPENTRY AddSubEntry (int pos, long handle, BOOL bFree);
	void RefreshConnectionData();
	void RefreshSubEntries();
	void LoadSubEntries();
	
	LPOLESTR GetState();
	LPOLESTR GetHandle();
	LPOLESTR GetPos();
	LPOLESTR GetName();
	LPOLESTR GetRemaining();
	LPOLESTR GetConnections();

private:
	LPENTRY* m_pSubEntries;
	HSCOPEITEM m_hScope;
	LPENTRY m_pParent;

	int m_nTier;
	int m_nSubCount;

	//Item information
	OLECHAR m_szName[25];
	
	int m_nPos;
	long m_Handle;
	BOOL m_bFree;
	long m_lRemaining;
	long m_lConnections;
};


#endif // !defined(AFX_ENTRY_H__C8FF6D20_F7C9_11D1_846A_0020AF05ED45__INCLUDED_)
