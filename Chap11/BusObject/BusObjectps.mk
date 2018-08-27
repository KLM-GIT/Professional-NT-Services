
BusObjectps.dll: dlldata.obj BusObject_p.obj BusObject_i.obj
	link /dll /out:BusObjectps.dll /def:BusObjectps.def /entry:DllMain dlldata.obj BusObject_p.obj BusObject_i.obj kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib 

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL $<

clean:
	@del BusObjectps.dll
	@del BusObjectps.lib
	@del BusObjectps.exp
	@del dlldata.obj
	@del BusObject_p.obj
	@del BusObject_i.obj
