#define _WIN32_WINNT 0x403 //NT4 sp3
#define UNICODE 
#define _UNICODE

#include <windows.h>
#include <process.h>

#include <iostream>
using namespace std;

#ifdef UNICODE
	#define _tcout wcout
	#define _tostream wostream
#else
	#define _tcout cout
	#define _tostream ostream
#endif

#include <TCHAR.h>
#include "Monitor.h"