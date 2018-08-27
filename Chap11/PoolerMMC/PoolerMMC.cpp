// PoolerMMC.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f PoolerMMCps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "PoolerMMC.h"

#include "PoolerMMC_i.c"
#include "ComponentData.h"
#include "DataObject.h"
#include "Component.h"
#include "ExtendContextMenu.h"


CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_Component, CComponent)
	OBJECT_ENTRY(CLSID_ComponentData, CComponentData)
	OBJECT_ENTRY(CLSID_DataObject, CDataObject)
	OBJECT_ENTRY(CLSID_ExtendContextMenu, CExtendContextMenu)
END_OBJECT_MAP()

void Register();
void Unregister();

/////////////////////////////////////////////////////////////////////////////
// DLL Entry Point

extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		_Module.Init(ObjectMap, hInstance);
		DisableThreadLibraryCalls(hInstance);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
		_Module.Term();
	return TRUE;    // ok
}

/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	return (_Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	Register();
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	Unregister();
	_Module.UnregisterServer();
	return S_OK;
}

void Register ()
{
	HKEY hMmcParentKey;
	RegOpenKey (HKEY_LOCAL_MACHINE,
				L"Software\\Microsoft\\MMC\\SnapIns",
				&hMmcParentKey);
  
	HKEY hObjMonParentKey;
	RegCreateKey (hMmcParentKey,
	              L"{C8FF6D1B-F7C9-11D1-846A-0020AF05ED45}", //ComponentData CoClass
				  &hObjMonParentKey);

	RegSetValueEx (hObjMonParentKey,
				   L"NameString", 0, REG_SZ,
				   (LPBYTE)L"Pooler SnapIn", sizeof(L"Pooler SnapIn"));

	RegSetValueEx (hObjMonParentKey,
				   L"NodeType", 0, REG_SZ,
				   (LPBYTE)L"{A2AF0D5A-F7E6-11d1-846A-0020AF05ED45}", //Root Node Type UUID
				   sizeof(L"{A2AF0D5A-F7E6-11d1-846A-0020AF05ED45}"));

	HKEY hStandAloneKey;
	RegCreateKey (hObjMonParentKey, L"StandAlone", &hStandAloneKey);
	RegCloseKey (hStandAloneKey);              

	HKEY hNodeTypesKey;
	RegCreateKey (hObjMonParentKey, L"NodeTypes", &hNodeTypesKey);

	HKEY hNodeKey;
	RegCreateKey (hNodeTypesKey,
				  L"{A2AF0D5A-F7E6-11d1-846A-0020AF05ED45}",
				  &hNodeKey);

	RegSetValueEx (hNodeKey,
				   NULL, 0, REG_SZ,
				   (LPBYTE)L"Root Node",
				   sizeof(L"Root Node"));

	RegCloseKey (hNodeKey);

	RegCloseKey (hNodeTypesKey);
	RegCloseKey (hObjMonParentKey);
	RegCloseKey (hMmcParentKey);
}

void Unregister ()
{
	HKEY hMmcParentKey;
	RegOpenKey (HKEY_LOCAL_MACHINE,
				L"Software\\Microsoft\\MMC\\SnapIns",
				&hMmcParentKey);

	HKEY hObjMonParentKey;
	RegOpenKey (hMmcParentKey,
				L"{C8FF6D1D-F7C9-11D1-846A-0020AF05ED45}",
				&hObjMonParentKey);
  
	HKEY hNodeTypesKey;
	RegOpenKey (hObjMonParentKey,
				L"NodeTypes",
				&hNodeTypesKey);

	RegDeleteKey (hNodeTypesKey, L"{A2AF0D5A-F7E6-11d1-846A-0020AF05ED45}");
	RegCloseKey (hNodeTypesKey);

	RegDeleteKey (hObjMonParentKey, L"NodeTypes");
	RegDeleteKey (hObjMonParentKey, L"StandAlone");
	RegCloseKey (hObjMonParentKey);

	RegDeleteKey (hMmcParentKey, L"{C8FF6D1D-F7C9-11D1-846A-0020AF05ED45}");
	RegCloseKey (hMmcParentKey);
}
