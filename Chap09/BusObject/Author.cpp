// Author.cpp : Implementation of CAuthor
#include "stdafx.h"
#include "BusObject.h"
#include "Author.h"

/////////////////////////////////////////////////////////////////////////////
// CAuthor

STDMETHODIMP CAuthor::GetAuthorList(long nContract, VARIANT * pDataArray)
{
	const RHANDLE* pRH = 0;	
	DWORD dwErr = _Module.m_pQM->GetFreeResource( &pRH );
	if( dwErr != 0 )
		return dwErr;

	SQLHDBC hdbc = pRH->handle;


	//Do the work
	SQLRETURN rc;
	SQLHSTMT hstmt = NULL;

    // Allocate statement handle 
    rc = SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt); 


	// Allocations for variant array
	long theDim[2];	
	long count= 0;
	const int INITROWS = 5; //Batch size for redim
	const int numcols = 7;

	//Set up Array
	//Create the array
	SAFEARRAYBOUND sabound[2]; //2-D array
	sabound[0].cElements = numcols;    
	sabound[0].lLbound = 1;
	sabound[1].cElements = INITROWS;
	sabound[1].lLbound = 1;

	int currows = INITROWS;
	VariantInit(pDataArray);
	pDataArray->vt = VT_VARIANT | VT_ARRAY; //means variant array
	pDataArray->parray = SafeArrayCreate(VT_VARIANT,2,sabound);


	SQLSMALLINT Contract;
	SQLINTEGER  ContractInd = 0;
	UCHAR szSQL[100] = "select au_lname, au_fname, phone, address, city, state, zip from authors where contract=?\0";

	SQLPrepare(hstmt, szSQL , SQL_NTS);

	SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_SSHORT, SQL_BIT, 0, 0,
					 &Contract, 0, &ContractInd);

	Contract = (short int) nContract;

	rc = SQLExecute(hstmt);   
	
	const int LNAMELEN = 41;
	const int FNAMELEN = 21;
	const int PHONELEN = 13;
	const int ADDRLEN = 41;
	const int CITYLEN = 21;
	const int STATELEN = 3;
	const int ZIPLEN = 6;

	SQLCHAR szLName[LNAMELEN];
	SQLCHAR szFName[FNAMELEN]; 
	SQLCHAR szPhone[PHONELEN];
	SQLCHAR szAddress[ADDRLEN];
	SQLCHAR szCity[CITYLEN];
	SQLCHAR szState[STATELEN];
	SQLCHAR szZip[ZIPLEN];

	SQLINTEGER  cbLName, cbFName, cbPhone, cbAddress, cbCity, cbState, cbZip;

	if (rc == SQL_SUCCESS) {    
		while (TRUE)
		{
			rc = SQLFetch(hstmt);
			if (rc == SQL_ERROR)
				break;

			if (rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO)
			{
				count++;
				if( count > currows )
				{
					//Redim the array by INITROWS size
					SAFEARRAYBOUND sabound2[1]; 
					sabound2[0].cElements = currows + INITROWS;
					sabound2[0].lLbound = 1;
					SafeArrayRedim( pDataArray->parray, sabound2); //Tricky; the new bound only describes the
					currows += INITROWS;			//dim you can change, not all new dims.
				}

				SQLGetData(hstmt, 1, SQL_C_CHAR, szLName, LNAMELEN, &cbLName);
				SQLGetData(hstmt, 2, SQL_C_CHAR, szFName, FNAMELEN, &cbFName);
				SQLGetData(hstmt, 3, SQL_C_CHAR, szPhone, PHONELEN, &cbPhone);
				SQLGetData(hstmt, 4, SQL_C_CHAR, szAddress, ADDRLEN, &cbAddress);
				SQLGetData(hstmt, 5, SQL_C_CHAR, szCity, CITYLEN, &cbCity);
				SQLGetData(hstmt, 6, SQL_C_CHAR, szState, STATELEN, &cbState);
				SQLGetData(hstmt, 7, SQL_C_CHAR, szZip, ZIPLEN, &cbZip);

				//Set the value in each row
				theDim[1] = count; //row dimension value

				theDim[0] = 1; //column dimension value
				CComVariant vC1( (CHAR*)szLName );
				SafeArrayPutElement(pDataArray->parray,theDim,&vC1);
				
				theDim[0] = 2;
				CComVariant vC2( (CHAR*)szFName );
				SafeArrayPutElement(pDataArray->parray,theDim,&vC2);

				theDim[0] = 3;
				CComVariant vC3( (CHAR*)szPhone );
				SafeArrayPutElement(pDataArray->parray,theDim,&vC3);
			
				theDim[0] = 4;
				CComVariant vC4( (CHAR*)szAddress );
				SafeArrayPutElement(pDataArray->parray,theDim,&vC4);

				theDim[0] = 5;
				CComVariant vC5( (CHAR*)szCity );
				SafeArrayPutElement(pDataArray->parray,theDim,&vC5);

				theDim[0] = 6;
				CComVariant vC6( (CHAR*)szState );
				SafeArrayPutElement(pDataArray->parray,theDim,&vC6);

				theDim[0] = 7;
				CComVariant vC7( (CHAR*)szZip );
				SafeArrayPutElement(pDataArray->parray,theDim,&vC7);
			}
			else
			{
				break;
			}    
		}
	}

	// Close
	SQLFreeHandle(SQL_HANDLE_STMT, hstmt);                

	 //Return the handle to the pool
	_Module.m_pQM->ReleaseResource( pRH );

	//Redim the array to its actual size
	SAFEARRAYBOUND sabound2[1]; 
	sabound2[0].cElements = count;
	sabound2[0].lLbound = 1;
	SafeArrayRedim( pDataArray->parray, sabound2);

	return S_OK;
}
