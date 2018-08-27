#define _WIN32_WINNT 0x400
#define UNICODE 
#define _UNICODE

#include <windows.h>
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
#include "logtest.h"
