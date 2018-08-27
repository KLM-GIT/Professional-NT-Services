
EmptyServiceps.dll: dlldata.obj EmptyService_p.obj EmptyService_i.obj
	link /dll /out:EmptyServiceps.dll /def:EmptyServiceps.def /entry:DllMain dlldata.obj EmptyService_p.obj EmptyService_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del EmptyServiceps.dll
	@del EmptyServiceps.lib
	@del EmptyServiceps.exp
	@del dlldata.obj
	@del EmptyService_p.obj
	@del EmptyService_i.obj
