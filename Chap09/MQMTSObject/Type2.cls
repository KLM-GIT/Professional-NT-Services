VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Type2"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Const DSN = "DSN=MQMTS;uid=sa;pwd=pw"
Public Function GetHighestSales(ByVal HighQuantity As Integer) As Integer

On Error GoTo eh
    Dim cn As New ADODB.Connection
    Dim rs As New ADODB.Recordset
    Dim sql$
    
    sql = "select stor_id, SUM(qty) total from sales group by " _
     & "stor_id, qty having SUM(qty)<" & HighQuantity & " order by total desc"

    cn.Open DSN
    Set rs = cn.Execute(sql, adCmdText)
    If Not rs.EOF Then
        GetHighestSales = rs("stor_id")
    Else
        GetHighestSales = 0
    End If
    rs.Close
    cn.Close
    
    GetObjectContext().SetComplete

Exit Function
eh:
    GetHighestSales = 0
    GetObjectContext().SetAbort
End Function


