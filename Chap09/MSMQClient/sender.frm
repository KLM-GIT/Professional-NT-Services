VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5415
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8100
   LinkTopic       =   "Form1"
   ScaleHeight     =   5415
   ScaleWidth      =   8100
   StartUpPosition =   3  'Windows Default
   Begin VB.TextBox Text2 
      Height          =   315
      Left            =   6600
      TabIndex        =   7
      Text            =   "1"
      Top             =   600
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   285
      Left            =   6600
      TabIndex        =   6
      Text            =   "1"
      Top             =   240
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Send Type 2"
      Height          =   375
      Left            =   4680
      TabIndex        =   5
      Top             =   600
      Width           =   1695
   End
   Begin VB.ListBox lstResponse 
      Height          =   2985
      Left            =   360
      TabIndex        =   3
      Top             =   1440
      Width           =   7455
   End
   Begin VB.CheckBox chkAsync 
      Caption         =   "Asynch Message Receive"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   720
      Width           =   2295
   End
   Begin VB.CommandButton cmdSend 
      Caption         =   "Send Type 1"
      Height          =   375
      Left            =   4680
      TabIndex        =   1
      Top             =   240
      Width           =   1695
   End
   Begin VB.TextBox txtmsg 
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Top             =   240
      Width           =   4095
   End
   Begin VB.Label Label2 
      Caption         =   "Threshold"
      Height          =   255
      Left            =   360
      TabIndex        =   9
      Top             =   0
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Iterations"
      Height          =   255
      Left            =   6600
      TabIndex        =   8
      Top             =   0
      Width           =   1215
   End
   Begin VB.Label lbl 
      Caption         =   "Response Queue"
      Height          =   375
      Left            =   360
      TabIndex        =   4
      Top             =   1080
      Width           =   1455
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit
Dim WithEvents qEvent As MSMQEvent
Attribute qEvent.VB_VarHelpID = -1
Dim qrResp As MSMQQueue
Const cLabel = "AgentMonitorQ"
Const cPath = ".\AgentMonitorQ"
Const cRespLabel = "AgentMonitor Response Queue"
Const cRespPath = ".\AgentMonitorRespQ"
Const AGENT_REQUEST_1 = 239
Const AGENT_REQUEST_2 = 240

Function CreateQueue(ByVal label As String, ByVal path As String) As MSMQQueueInfo
    Dim qi As New MSMQQueueInfo
    qi.PathName = path
    qi.label = label
    qi.Create
    If Not qi Is Nothing Then
        Set CreateQueue = qi
    End If
End Function

Function CreateQueueInfo(ByVal label As String, ByVal path As String) As MSMQQueueInfo
    Dim qry As New MSMQQuery
    Dim qinfos As MSMQQueueInfos
    Dim qi As MSMQQueueInfo
    
    'Find the queue or create it if it doesnt exist
    Set qinfos = qry.LookupQueue(label:=label)
    qinfos.Reset
    Set qi = qinfos.Next
    If qi Is Nothing Then
        Set qi = CreateQueue(label, path)
    End If

    If Not qi Is Nothing Then
        Set CreateQueueInfo = qi
    End If
End Function
Function OpenQueue(ByVal label As String, ByVal path As String, ByVal qtype As Long) As MSMQQueue
    Dim qry As New MSMQQuery
    Dim qi As MSMQQueueInfo
    Dim qinfos As MSMQQueueInfos
    
    'Find the queue or create it if it doesnt exist
    Set qinfos = qry.LookupQueue(label:=label)
    qinfos.Reset
    Set qi = qinfos.Next
    If qi Is Nothing Then
        Set qi = CreateQueue(label, path)
    End If
    
    'Open the queue for send or receive
    Dim q As MSMQQueue
    Set q = qi.Open(qtype, MQ_DENY_NONE)
    If q.IsOpen = False Then
        Set OpenQueue = Nothing
    Else
        Set OpenQueue = q
    End If
End Function

Function SendMessage(ByVal msgtext As String, ByVal mtype As Long)
    Dim q As MSMQQueue
    Set q = OpenQueue(cLabel, cPath, MQ_SEND_ACCESS)
    
    Dim msg As New MSMQMessage
    
    'Create the resp queue info object
    Dim qiResp As MSMQQueueInfo
    Set qiResp = CreateQueueInfo(cRespLabel, cRespPath)
    
    Set msg.ResponseQueueInfo = qiResp
    msg.Body = (msgtext)
    msg.AppSpecific = mtype
    msg.label = "Agent Message"
    msg.Send q
        
    q.Close
End Function

Private Sub chkAsync_Click()
    If chkAsync.Value = 1 Then
        Set qEvent = New MSMQEvent
        Set qrResp = OpenQueue(cRespLabel, cRespPath, MQ_RECEIVE_ACCESS)
        qrResp.EnableNotification Event:=qEvent, ReceiveTimeout:=1000
    Else
        qrResp.Close
        Set qEvent = Nothing
        Set qrResp = Nothing
    End If
End Sub

Private Sub cmdSend_Click()
    Dim i&
    For i = 1 To CLng(Text1.Text)
        SendMessage txtmsg.Text, AGENT_REQUEST_1
    Next i
End Sub

Private Sub Command1_Click()
    Dim i&
    For i = 1 To CLng(Text2.Text)
        SendMessage txtmsg.Text, AGENT_REQUEST_2
    Next i
End Sub

Private Sub qEvent_Arrived(ByVal Queue As Object, ByVal Cursor As Long)
    Dim msg As MSMQMessage
    Set msg = Queue.Receive
    lstResponse.AddItem msg.label & "  " & msg.Body
    
    Queue.EnableNotification Event:=qEvent
End Sub



