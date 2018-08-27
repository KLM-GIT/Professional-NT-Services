// Entry.cpp: implementation of the CEntry class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "entry.h"
#include "busobject.h"
#include <stdio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
//#define new DEBUG_NEW
#endif

CEntry::CEntry()
{
	m_nTier = -1;
	m_pParent = 0;
	m_nSubCount = 0;
	m_pSubEntries = NULL;
	m_hScope = NULL;

	wcscpy( m_szName , L"Root");

	m_nPos = 0;
	m_Handle = NULL;
	m_bFree = FALSE;
	m_lConnections = 0;
	m_lRemaining = 0;
}

//Constructor for level 0
CEntry::CEntry (LPOLESTR szName, int nTier, LPENTRY lpParent)
{
	m_nTier = nTier;
	m_nSubCount = 0;
	m_pParent = lpParent;

	wcscpy (m_szName, szName);

	RefreshConnectionData();

	LoadSubEntries();
}

//Constructor for list items
CEntry::CEntry (int pos, long handle, BOOL bFree, 
				int nTier, LPENTRY lpParent)
{
	if( nTier != 1 )
		return;

	m_nTier = nTier;
	m_pParent = lpParent;
	m_nSubCount = 0;
	m_pSubEntries = NULL;
	m_hScope = NULL;

	OLECHAR sz[25];
	wsprintf( sz, L"Handle #%d", pos );
	wcscpy( m_szName, sz );

	m_nPos = pos;
	m_Handle = handle;
	m_bFree = bFree;
	m_lConnections = 0;
	m_lRemaining = 0;
}

CEntry::~CEntry()
{
	if( m_pSubEntries )
		delete[] m_pSubEntries;
}

//Adds a new entry to the sub entry list
LPENTRY CEntry::AddSubEntry (LPOLESTR szName)
{
	CEntry* pEntry = new CEntry(szName, m_nTier + 1, this );

	LPENTRY* pSub = new LPENTRY[ m_nSubCount + 1];

	//Copy array
	if (m_nSubCount)
	{
		memcpy (pSub, m_pSubEntries, m_nSubCount * sizeof (LPENTRY));
		delete [] m_pSubEntries;
	}

	m_pSubEntries = pSub;
	m_pSubEntries[m_nSubCount++] = pEntry;

	return pEntry;
}

//Overloaded for adding handle map items. (tier 1)
LPENTRY CEntry::AddSubEntry (int pos, long handle, BOOL bFree)
{
	LPENTRY pEntry = new CEntry (pos, handle, bFree, m_nTier + 1, this );

	LPENTRY* pSub = new LPENTRY[m_nSubCount + 1];

	//Copy array
	if (m_nSubCount)
	{
		memcpy (pSub, m_pSubEntries, m_nSubCount * sizeof (LPENTRY));
		delete [] m_pSubEntries;
	}

	m_pSubEntries = pSub;
	m_pSubEntries[m_nSubCount++] = pEntry;

	return pEntry;
}

//Properties
LPOLESTR CEntry::GetName()
{
	LPOLESTR sz = new OLECHAR[ wcslen(m_szName) + 1];
	wcscpy (sz, m_szName);
	return sz;
}

LPOLESTR CEntry::GetPos()
{
	LPOLESTR sz = new OLECHAR[4];
	wsprintf( sz, L"%d", m_nPos );
	return sz;

}

LPOLESTR CEntry::GetHandle()
{
	LPOLESTR sz = new OLECHAR[10];
	wsprintf( sz, L"%lu", m_Handle );
	return sz;

}

LPOLESTR CEntry::GetState()
{
	LPOLESTR sz = new OLECHAR[5];
	if( m_bFree )
		wsprintf( sz, L"Free" );
	else
		wsprintf( sz, L"Used" );

	return sz;

}

LPOLESTR CEntry::GetConnections()
{
	LPOLESTR sz = new OLECHAR[4];
	wsprintf( sz, L"%d", m_lConnections );
	return sz;
}

LPOLESTR CEntry::GetRemaining()
{
	LPOLESTR sz = new OLECHAR[4];
	wsprintf( sz, L"%d", m_lRemaining );
	return sz;

}

void CEntry::LoadSubEntries()
{
	//Attach to server and query for variant array.
	COSERVERINFO serverInfo;
	memset (&serverInfo, 0, sizeof (COSERVERINFO));
	serverInfo.pwszName = m_szName;

	MULTI_QI qis[1];
	memset (qis, 0, sizeof (MULTI_QI));

	qis[0].pIID = &IID_IPoolAdminData;
	HRESULT hr = CoCreateInstanceEx (CLSID_PoolAdminData, NULL, CLSCTX_LOCAL_SERVER, &serverInfo, 1, qis);

	if (FAILED (hr))
		return;

	IPoolAdminData* piPoolAdmin = (IPoolAdminData*) qis[0].pItf;

	//Return the data into a variant array
	VARIANT var;
	VariantInit(&var);
	hr = piPoolAdmin->GetPoolInfo( &var );
	if (FAILED (hr))
		return;

	//March through array and attach to sub items
    long rowLower=0, rowUpper=0;
	long thedim[2];

	SAFEARRAY* psa = var.parray;
	hr = SafeArrayGetLBound(psa, 2, &rowLower );
	hr = SafeArrayGetUBound(psa, 2, &rowUpper );

	for( int i=rowLower; i<=rowUpper; i++ )
	{
		thedim[1] = i;
		
		thedim[0] = 1;
		CComVariant vPos;
		hr = SafeArrayGetElement(psa, thedim, &vPos);
		
		CComVariant vHandle;
		thedim[0] = 2;
		hr = SafeArrayGetElement(psa, thedim, &vHandle);

		CComVariant vFree;
		thedim[0] = 3;
		hr = SafeArrayGetElement(psa, thedim, &vFree);
		
		AddSubEntry( vPos.lVal, vHandle.lVal, vFree.boolVal );
	}

	piPoolAdmin->Release();
	
}

void CEntry::RefreshSubEntries()
{
	if ( m_nTier == 0 )
	{
		delete[] m_pSubEntries;
		m_pSubEntries = NULL;
		m_nSubCount = 0;
		LoadSubEntries();
	}
	else if( m_nTier == -1 )
	{
		for(int i=0; i<m_nSubCount; i++)
		{
			m_pSubEntries[i]->RefreshConnectionData();
		}
	}
}

void CEntry::RefreshConnectionData()
{
	COSERVERINFO serverInfo;
	memset (&serverInfo, 0, sizeof (COSERVERINFO));
	serverInfo.pwszName = m_szName;

	MULTI_QI qis[1];
	memset (qis, 0, sizeof (MULTI_QI));

	qis[0].pIID = &IID_IPoolAdminData;
	HRESULT hr = CoCreateInstanceEx (CLSID_PoolAdminData, NULL, CLSCTX_LOCAL_SERVER, &serverInfo, 1, qis);

	if (FAILED (hr))
		return;

	IPoolAdminData* piPoolAdmin = (IPoolAdminData*) qis[0].pItf;

	long lConnections = 0, lRemaining = 0;
	hr = piPoolAdmin->GetUsageStats( &lConnections, &lRemaining );
	if (FAILED (hr))
		return;
	
	m_lConnections = lConnections;
	m_lRemaining = lRemaining;

	piPoolAdmin->Release();

}
