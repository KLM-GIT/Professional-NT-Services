#define _WIN32_WINNT 0x500 //NT4sp3
#define UNICODE 
#define _UNICODE

#include <windows.h>
#include <process.h>

#include <iostream>
using namespace std;

#ifdef UNICODE
	#define _tcout wcout
	#define _ttol _wtol
	#define _tostream wostream
#else
	#define _tcout cout
	#define _tostream ostream
	#define _ttol atol
#endif

#include <TCHAR.h>

#include <mq.h>
#include "ceventlog.h"
#include "monitor.h"

typedef unsigned (WINAPI *PBEGINTHREADEX_TFUNC) 
(
	LPVOID lpThreadParameter
);

typedef unsigned* PBEGINTHREADEX_TID;