// PoolAdminData.cpp : Implementation of CPoolAdminData
#include "stdafx.h"
#include "BusObject.h"
#include "PoolAdminData.h"

/////////////////////////////////////////////////////////////////////////////
// CPoolAdminData


STDMETHODIMP CPoolAdminData::GetPoolInfo(VARIANT * paVariant)
{
	RHANDLEHEADER* pTemp = 0;
	BOOL bTemp = 0;
	long tmpHandle = 0;

	CResourceArray* pArray = _Module.m_pQM->GetResourceArray();
	int count = pArray->GetCount();

	// Allocations for variant array
	long theDim[2];	
	const int numcols = 3;

	//Set up Array
	//Create the array
	SAFEARRAYBOUND sabound[2]; //2d array
	sabound[0].cElements = numcols;    
	sabound[0].lLbound = 1;
	sabound[1].cElements = count;
	sabound[1].lLbound = 0;

	VariantInit(paVariant);
	paVariant->vt = VT_VARIANT | VT_ARRAY;
	paVariant->parray = SafeArrayCreate(VT_VARIANT,2,sabound);
	
	for( int pos=0; pos<count; pos++ )
	{
		pTemp = pArray->m_pHandles[pos];
		if( pTemp )
		{
			//poke in the position and busy state
			bTemp = pTemp->bFree;

			//Access the RHANDLE and get handle value
			tmpHandle = (long)pTemp->pRH->handle;

			theDim[1] = pos; //row dimension value

			theDim[0] = 1; //position
			CComVariant vC1( pos );
			SafeArrayPutElement(paVariant->parray,theDim,&vC1);

			theDim[0] = 2; //handle
			CComVariant vC2( tmpHandle );
			SafeArrayPutElement(paVariant->parray,theDim,&vC2);

			theDim[0] = 3; //busy
			CComVariant vC3( bTemp );
			SafeArrayPutElement(paVariant->parray,theDim,&vC3);
		}
	}

	return S_OK;
}

STDMETHODIMP CPoolAdminData::GetUsageStats(long * pConnections, long * pRemaining)
{
	*pConnections = _Module.m_pQM->GetNumResources();
	*pRemaining = _Module.m_pQM->FreeResourcesLeft();
	return S_OK;
}
