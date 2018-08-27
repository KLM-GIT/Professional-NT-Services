MessageIdTypedef=DWORD

SeverityNames=(Success=0x0:STATUS_SEVERITY_SUCCESS
               Informational=0x1:STATUS_SEVERITY_INFORMATIONAL
               Warning=0x2:STATUS_SEVERITY_WARNING
               Error=0x3:STATUS_SEVERITY_ERROR
              )

FacilityNames=(System=0x0:FACILITY_SYSTEM
               Runtime=0x2:FACILITY_RUNTIME
               Stubs=0x3:FACILITY_STUBS
               Io=0x4:FACILITY_IO_ERROR_CODE
              )

LanguageNames=(English=0x409:MSG00409)
LanguageNames=(Testian=0x90AA:MSG090AA)

MessageId=0x1
Severity=Informational
SymbolicName=LOGTEST_GENERIC
Language=English
%1
.
Language=Testian
%1
.

MessageId=
Severity=Error
Facility=Runtime
SymbolicName=LOGTEST_WIN32_ERROR
Language=English
%1
.
Language=Testian
%1
.

MessageId=
Severity=Error
SymbolicName=LOGTEST_MULTISTRING_ERROR
Language=English
Logtest reported the following Error: Number %1, %2
.
Language=Testian
Error following the reported Logtest: Number %1, %2
.

MessageId=
Severity=Error
SymbolicName=LOGTEST_ERROR
Language=English
Logtest write operation failed in file %1.
.
Language=Testian
File in failed operation write Logtest %1.
.

MessageId=
Severity=Informational
SymbolicName=LOGTEST_INFO_1
Language=English
The logtest was successful.
.
Language=Testian
Successful was logtest the.
.

MessageId=
Severity=Error
SymbolicName=LOGTEST_ERROR_WITH_DATA
Language=English
Logtest operation failed (The LOGTEST_DUDLEY structure is the event data.)
.
Language=Testian
Failed operation Logtest (Data event the is structure LOGTEST_DUDLEY the.)
.
