issue: Excel-VBA:"根据安全设置，已禁用宏，若要运行宏，您需要重新打开此工作簿，然后选择启用宏。"

1.关闭所有打开的Excel文件，新建一个空白Excel文档
空白文档建好后，按ALT+11弹出VB编辑窗口
在左侧工作簿1下右键，插入模块
去掉EXCEL【根据安全设置,已禁用宏。……】
在弹出窗口内粘贴以下内容：

```
Sub RmvMacros()
    Dim wbk As Workbook
    Dim strFilename As String

    strFilename = Application.GetOpenFilename("Excel 文件 (*.xls;*.xlsx),*.xls;*.xlsx") '要删除宏的文件名

    If strFilename = "False" 
      Then Exit Sub
    Application.EnableEvents = False '禁止在打开时触发事件
    Application.DisplayAlerts = False
    Set wbk = Workbooks.Open(strFilename)
    For Each sht In wbk.Sheets
        sht.Visible = True
        If sht.Type = 3 Or sht.Type = 4 Then sht.Delete
    Next
    For i = wbk.Names.Count To 1 Step -1
        If wbk.Names(i).Visible = False Then wbk.Names(i).Delete
    Next i
    wbk.Close savechanges:=True
    Application.DisplayAlerts = True
    Application.EnableEvents = True
End Sub
```

+ 去掉EXCEL【根据安全设置,已禁用宏。……】
 

+ 按F5，在弹出的窗口内找到想要清理的Excel文件，打开
去掉EXCEL【根据安全设置,已禁用宏。……】
6

+ 等命令执行完毕后，点右上角X，关闭文档。

+ 重新打开弹窗文件，烦人的弹窗终于消失了。

> 整个世界清静了～～
