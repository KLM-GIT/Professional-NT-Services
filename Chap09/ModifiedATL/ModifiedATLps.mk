
ModifiedATLps.dll: dlldata.obj ModifiedATL_p.obj ModifiedATL_i.obj
	link /dll /out:ModifiedATLps.dll /def:ModifiedATLps.def /entry:DllMain dlldata.obj ModifiedATL_p.obj ModifiedATL_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del ModifiedATLps.dll
	@del ModifiedATLps.lib
	@del ModifiedATLps.exp
	@del dlldata.obj
	@del ModifiedATL_p.obj
	@del ModifiedATL_i.obj
