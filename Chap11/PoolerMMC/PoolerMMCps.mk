
PoolerMMCps.dll: dlldata.obj PoolerMMC_p.obj PoolerMMC_i.obj
	link /dll /out:PoolerMMCps.dll /def:PoolerMMCps.def /entry:DllMain dlldata.obj PoolerMMC_p.obj PoolerMMC_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del PoolerMMCps.dll
	@del PoolerMMCps.lib
	@del PoolerMMCps.exp
	@del dlldata.obj
	@del PoolerMMC_p.obj
	@del PoolerMMC_i.obj
