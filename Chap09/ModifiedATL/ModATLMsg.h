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


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: MODATL_GENERIC
//
// MessageText:
//
//  %1
//
#define MODATL_GENERIC                   ((DWORD)0x60002000L)

//
// MessageId: MODATL_GENERIC_ERROR
//
// MessageText:
//
//  %1
//
#define MODATL_GENERIC_ERROR             ((DWORD)0xE0002001L)

//
// MessageId: MODATL_WIN32_ERROR
//
// MessageText:
//
//  %1
//
#define MODATL_WIN32_ERROR               ((DWORD)0xE0002002L)

//
// MessageId: MODATL_PAUSED
//
// MessageText:
//
//  The 401k data service is paused.
//
#define MODATL_PAUSED                    ((DWORD)0x60002003L)

//
// MessageId: MODATL_STOPPED
//
// MessageText:
//
//  The 401k data service is stopped.
//
#define MODATL_STOPPED                   ((DWORD)0x60002004L)

//
// MessageId: MODATL_STARTED
//
// MessageText:
//
//  The 401k data service is started.
//
#define MODATL_STARTED                   ((DWORD)0x60002005L)

//
// MessageId: MODATL_CONTINUED
//
// MessageText:
//
//  The 401k data service continued.
//
#define MODATL_CONTINUED                 ((DWORD)0x60002006L)

//
// MessageId: MODATL_CONFIGURATION_DATA_MISSING
//
// MessageText:
//
//  Data was not found in the registry for key %1. The service could not start.
//
#define MODATL_CONFIGURATION_DATA_MISSING ((DWORD)0xE0002007L)

