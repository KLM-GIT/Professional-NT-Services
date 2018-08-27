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
// MessageId: BUSOBJ_GENERIC
//
// MessageText:
//
//  %1
//
#define BUSOBJ_GENERIC                   ((DWORD)0x60002000L)

//
// MessageId: BUSOBJ_GENERIC_ERROR
//
// MessageText:
//
//  %1
//
#define BUSOBJ_GENERIC_ERROR             ((DWORD)0xE0002001L)

//
// MessageId: BUSOBJ_WIN32_ERROR
//
// MessageText:
//
//  %1
//
#define BUSOBJ_WIN32_ERROR               ((DWORD)0xE0002002L)

//
// MessageId: BUSOBJ_PAUSED
//
// MessageText:
//
//  The service is paused.
//
#define BUSOBJ_PAUSED                    ((DWORD)0x60002003L)

//
// MessageId: BUSOBJ_STOPPED
//
// MessageText:
//
//  The service is stopped.
//
#define BUSOBJ_STOPPED                   ((DWORD)0x60002004L)

//
// MessageId: BUSOBJ_STARTED
//
// MessageText:
//
//  The service is started.
//
#define BUSOBJ_STARTED                   ((DWORD)0x60002005L)

//
// MessageId: BUSOBJ_CONTINUED
//
// MessageText:
//
//  The service continued.
//
#define BUSOBJ_CONTINUED                 ((DWORD)0x60002006L)

//
// MessageId: BUSOBJ_CONFIGURATION_DATA_MISSING
//
// MessageText:
//
//  Data was not found in the registry for key %1. The service could not start.
//
#define BUSOBJ_CONFIGURATION_DATA_MISSING ((DWORD)0xE0002007L)

//
// MessageId: BUSOBJ_NOSESSIONS_AVAILABLE
//
// MessageText:
//
//  A client requested a resource and none were available.
//
#define BUSOBJ_NOSESSIONS_AVAILABLE      ((DWORD)0x60002008L)

//
// MessageId: BUSOBJ_MORESESSIONS_ALLOCATED
//
// MessageText:
//
//  %1 additional resources were added. The count is now %2.
//
#define BUSOBJ_MORESESSIONS_ALLOCATED    ((DWORD)0x60002009L)

//
// MessageId: BUSOBJ_MAXIMUM_SESSIONS_ALLOCATED
//
// MessageText:
//
//  The maximum number of allowed sessions has been allocated.
//
#define BUSOBJ_MAXIMUM_SESSIONS_ALLOCATED ((DWORD)0x6000200AL)

//
// MessageId: BUSOBJ_HANDLE_CONNECTION_FAILED
//
// MessageText:
//
//  Attempt to allocate a resource handle failed. 
//
#define BUSOBJ_HANDLE_CONNECTION_FAILED  ((DWORD)0xE000200BL)

//
// MessageId: BUSOBJ_SERVICE_STOPPED_PAUSED
//
// MessageText:
//
//  The service is stopped or paused.
//
#define BUSOBJ_SERVICE_STOPPED_PAUSED    ((DWORD)0xE000200CL)

