VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   4725
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   9150
   LinkTopic       =   "Form1"
   ScaleHeight     =   4725
   ScaleWidth      =   9150
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command2 
      Caption         =   "GetAdminData"
      Height          =   495
      Left            =   6120
      TabIndex        =   5
      Top             =   240
      Width           =   1935
   End
   Begin VB.TextBox Text2 
      Height          =   375
      Left            =   4560
      TabIndex        =   3
      Text            =   "1000"
      Top             =   240
      Width           =   1215
   End
   Begin VB.ListBox List1 
      Height          =   3570
      Left            =   120
      TabIndex        =   2
      Top             =   840
      Width           =   8895
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Left            =   120
      TabIndex        =   1
      Text            =   "1"
      Top             =   120
      Width           =   1335
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Get List"
      Height          =   495
      Left            =   1680
      TabIndex        =   0
      Top             =   120
      Width           =   1215
   End
   Begin VB.Label Label1 
      Caption         =   "Num Iterations"
      Height          =   375
      Left            =   3240
      TabIndex        =   4
      Top             =   240
      Width           =   1095
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False

Private Sub Command1_Click()

Dim x%
For x = 1 To CInt(Text2.Text)
    Dim o As Object
    Set o = CreateObject("BusObject.Author.1")
    List1.Clear
    
    Dim va As Variant
    va = o.GetAuthorList(CLng(Text1.Text))

    Dim I As Integer
    Dim j As Integer
    Dim row$
    
    For j = LBound(va, 2) To UBound(va, 2)
        row$ = ""
        For I = LBound(va, 1) To UBound(va, 1)
            row$ = row$ + CStr(va(I, j)) + Chr$(9)
        Next I
        List1.AddItem row$
    Next j
    DoEvents
    Set o = Nothing
Next x
End Sub

Private Sub Command2_Click()

    Dim o As Object
    Set o = CreateObject("BusObject.PoolAdminData.1")
    List1.Clear
    
    Dim va As Variant
    va = o.GetPoolInfo()

    Dim I As Integer
    Dim j As Integer
    Dim row$
    
    For j = LBound(va, 2) To UBound(va, 2)
        row$ = ""
        For I = LBound(va, 1) To UBound(va, 1)
            row$ = row$ + CStr(va(I, j)) + Chr$(9)
        Next I
        List1.AddItem row$
    Next j
    DoEvents
    Set o = Nothing

End Sub

Private Sub Form_Load()
    Me.Show
'    Command1_Click
End Sub

