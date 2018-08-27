; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPropPage1
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "busobjcpl.h"
LastPage=0

ClassCount=4
Class1=CBusObjCplApp
Class2=CCplPropSheet
Class3=CPropPage1
Class4=CPropPage2

ResourceCount=2
Resource1=IDD_PAGE_SERVER
Resource2=IDD_PAGE_PARAMS

[CLS:CBusObjCplApp]
Type=0
BaseClass=CWinApp
HeaderFile=BusObjCpl.h
ImplementationFile=BusObjCpl.cpp
LastObject=CBusObjCplApp

[CLS:CCplPropSheet]
Type=0
BaseClass=CPropertySheet
HeaderFile=CplPropSheet.h
ImplementationFile=CplPropSheet.cpp

[CLS:CPropPage1]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropPage1.h
ImplementationFile=PropPage1.cpp
LastObject=IDC_EDIT_PASSWORD
Filter=D
VirtualFilter=idWC

[CLS:CPropPage2]
Type=0
BaseClass=CPropertyPage
HeaderFile=PropPage2.h
ImplementationFile=PropPage2.cpp
Filter=D
VirtualFilter=idWC

[DLG:IDD_PAGE_SERVER]
Type=1
Class=CPropPage1
ControlCount=6
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_SERVERNAME,edit,1350631552
Control5=IDC_EDIT_USERNAME,edit,1350631552
Control6=IDC_EDIT_PASSWORD,edit,1350631584

[DLG:IDD_PAGE_PARAMS]
Type=1
Class=CPropPage2
ControlCount=19
Control1=IDC_INITSESSIONS,edit,1350631552
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,button,1342177287
Control4=IDC_MAXSESSIONS,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_REALLOCSIZE,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_REALLOCPOLL,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_REALLOCMIN,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_HANDLELIFE,edit,1350631552
Control13=IDC_STATIC,static,1342308352
Control14=IDC_DEADPOLL,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_MAXWAIT,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_WAITTOCLOSE,edit,1350631552
Control19=IDC_STATIC,static,1342308352

