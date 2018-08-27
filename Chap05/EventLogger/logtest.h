//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_SYSTEM                  0x0
#define FACILITY_STUBS                   0x3
#define FACILITY_RUNTIME                 0x2
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: LOGTEST_GENERIC
//
// MessageText:
//
//  %1
//
#define LOGTEST_GENERIC                  ((DWORD)0x60000001L)

//
// MessageId: LOGTEST_WIN32_ERROR
//
// MessageText:
//
//  %1
//
#define LOGTEST_WIN32_ERROR              ((DWORD)0xE0020001L)

//
// MessageId: LOGTEST_MULTISTRING_ERROR
//
// MessageText:
//
//  Logtest reported the following Error: Number %1, %2
//
#define LOGTEST_MULTISTRING_ERROR        ((DWORD)0xE0020002L)

//
// MessageId: LOGTEST_ERROR
//
// MessageText:
//
//  Logtest write operation failed in file %1.
//
#define LOGTEST_ERROR                    ((DWORD)0xE0020003L)

//
// MessageId: LOGTEST_INFO_1
//
// MessageText:
//
//  The logtest was successful.
//
#define LOGTEST_INFO_1                   ((DWORD)0x60020004L)

//
// MessageId: LOGTEST_ERROR_WITH_DATA
//
// MessageText:
//
//  Logtest operation failed (The LOGTEST_DUDLEY structure is the event data.)
//
#define LOGTEST_ERROR_WITH_DATA          ((DWORD)0xE0020005L)

