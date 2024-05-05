VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "证件识别API调用例程"
   ClientHeight    =   9750
   ClientLeft      =   120
   ClientTop       =   450
   ClientWidth     =   14745
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   9750
   ScaleWidth      =   14745
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton NO 
      Caption         =   "取消"
      Height          =   495
      Left            =   8640
      TabIndex        =   63
      Top             =   8040
      Visible         =   0   'False
      Width           =   2055
   End
   Begin VB.CommandButton Yes 
      Caption         =   "确认"
      Height          =   495
      Left            =   6480
      TabIndex        =   62
      Top             =   8040
      Visible         =   0   'False
      Width           =   2175
   End
   Begin VB.DirListBox Dir1 
      Height          =   3030
      Left            =   6480
      TabIndex        =   61
      Top             =   5040
      Visible         =   0   'False
      Width           =   4215
   End
   Begin VB.DriveListBox Drive1 
      Height          =   300
      Left            =   6480
      TabIndex        =   60
      Top             =   4800
      Visible         =   0   'False
      Width           =   4215
   End
   Begin VB.CommandButton Button_Next 
      Caption         =   "->"
      Enabled         =   0   'False
      Height          =   375
      Left            =   12600
      TabIndex        =   24
      Top             =   7200
      Width           =   375
   End
   Begin VB.CommandButton Button_Pre 
      Caption         =   "<-"
      Enabled         =   0   'False
      Height          =   375
      Left            =   8400
      TabIndex        =   23
      Top             =   7200
      Width           =   375
   End
   Begin VB.TextBox Text_ButtonType 
      Height          =   375
      Left            =   9960
      TabIndex        =   19
      Top             =   3720
      Width           =   2535
   End
   Begin VB.TextBox Text_DeviceStatus 
      Height          =   375
      Left            =   9960
      TabIndex        =   18
      Top             =   2880
      Width           =   2535
   End
   Begin VB.TextBox Text_DeviceName 
      Height          =   375
      Left            =   9960
      TabIndex        =   17
      Top             =   2040
      Width           =   2535
   End
   Begin VB.TextBox TextDG 
      Height          =   3615
      Left            =   4560
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   12
      Top             =   5760
      Width           =   3615
   End
   Begin VB.CheckBox Check_Image 
      Caption         =   "white"
      Height          =   255
      Index           =   0
      Left            =   4560
      TabIndex        =   11
      Tag             =   "1"
      Top             =   3360
      Value           =   1  'Checked
      Width           =   1215
   End
   Begin VB.Timer Timer1 
      Interval        =   200
      Left            =   8280
      Top             =   5400
   End
   Begin VB.CommandButton Command10 
      Caption         =   "Camera Serial Number"
      Height          =   375
      Index           =   3
      Left            =   9960
      TabIndex        =   10
      Top             =   3360
      Width           =   2535
   End
   Begin VB.CommandButton Command9 
      Caption         =   "Check Device Online"
      Height          =   375
      Index           =   2
      Left            =   9960
      TabIndex        =   9
      Top             =   2520
      Width           =   2535
   End
   Begin VB.CommandButton Command8 
      Caption         =   "Get Current Device Name"
      Height          =   375
      Index           =   1
      Left            =   9960
      TabIndex        =   8
      Top             =   1680
      Width           =   2535
   End
   Begin VB.Frame Frame7 
      Caption         =   "Other Interfaces"
      Height          =   5055
      Left            =   9600
      TabIndex        =   6
      Top             =   240
      Width           =   3255
      Begin VB.TextBox Text_ButtonRFIDType 
         Height          =   375
         Left            =   360
         TabIndex        =   65
         Top             =   4320
         Width           =   2415
      End
      Begin VB.CommandButton Command12 
         Caption         =   "RFID Serial Number"
         Height          =   420
         Index           =   4
         Left            =   360
         TabIndex        =   64
         Top             =   3960
         Width           =   2415
      End
      Begin VB.TextBox Text_KernelVersion 
         Height          =   375
         Left            =   360
         TabIndex        =   16
         Top             =   960
         Width           =   2535
      End
      Begin VB.CommandButton Command6 
         Caption         =   "Get SDK Version"
         Height          =   375
         Index           =   0
         Left            =   360
         TabIndex        =   7
         Top             =   600
         Width           =   2535
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Operate"
      Height          =   5055
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   9255
      Begin VB.Frame Frame3 
         Caption         =   "Set Parameter"
         Height          =   4575
         Left            =   3960
         TabIndex        =   25
         Top             =   360
         Width           =   5055
         Begin VB.Frame Frame9 
            Caption         =   "ImagePath"
            Height          =   615
            Left            =   2400
            TabIndex        =   52
            Top             =   3600
            Width           =   2295
            Begin VB.CommandButton ImagePath 
               Caption         =   "Path"
               Height          =   255
               Left            =   120
               TabIndex        =   56
               Top             =   240
               Width           =   615
            End
            Begin VB.TextBox Text_ImagePath 
               Height          =   270
               Left            =   840
               TabIndex        =   53
               Top             =   240
               Width           =   1335
            End
         End
         Begin VB.Frame Frame6 
            Caption         =   "VIZ District"
            Height          =   615
            Left            =   360
            TabIndex        =   49
            Top             =   3600
            Width           =   1815
            Begin VB.OptionButton Option2 
               Caption         =   "No"
               Height          =   300
               Left            =   1080
               TabIndex        =   51
               Top             =   240
               Width           =   570
            End
            Begin VB.OptionButton Option1 
               Caption         =   "Yes"
               Height          =   300
               Left            =   240
               TabIndex        =   50
               Top             =   240
               Value           =   -1  'True
               Width           =   930
            End
         End
         Begin VB.Frame Frame5 
            Caption         =   "Save Image Type"
            Height          =   975
            Left            =   360
            TabIndex        =   44
            Top             =   2520
            Width           =   4335
            Begin VB.CheckBox Check_Image 
               Caption         =   "Ultraviolet"
               Height          =   255
               Index           =   2
               Left            =   2880
               TabIndex        =   48
               Tag             =   "3"
               Top             =   240
               Width           =   1335
            End
            Begin VB.CheckBox Check_Image 
               Caption         =   "Chip Head"
               Height          =   255
               Index           =   4
               Left            =   1440
               TabIndex        =   47
               Tag             =   "5"
               Top             =   600
               Width           =   1215
            End
            Begin VB.CheckBox Check_Image 
               Caption         =   "Infrared"
               Height          =   255
               Index           =   1
               Left            =   1440
               TabIndex        =   46
               Tag             =   "2"
               Top             =   240
               Width           =   1215
            End
            Begin VB.CheckBox Check_Image 
               Caption         =   "Head"
               Height          =   255
               Index           =   3
               Left            =   120
               TabIndex        =   45
               Tag             =   "4"
               Top             =   600
               Value           =   1  'Checked
               Width           =   975
            End
         End
         Begin VB.Frame Frame4 
            Caption         =   "Save DG Type"
            Height          =   2175
            Left            =   360
            TabIndex        =   26
            Top             =   240
            Width           =   4335
            Begin VB.CheckBox Check1 
               Caption         =   "DG0"
               Height          =   225
               Index           =   17
               Left            =   120
               TabIndex        =   66
               Tag             =   "1"
               Top             =   360
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG17"
               Height          =   225
               Index           =   16
               Left            =   1080
               TabIndex        =   43
               Tag             =   "17"
               Top             =   1800
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG16"
               Height          =   225
               Index           =   15
               Left            =   120
               TabIndex        =   42
               Tag             =   "16"
               Top             =   1800
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG15"
               Height          =   225
               Index           =   14
               Left            =   3360
               TabIndex        =   41
               Tag             =   "15"
               Top             =   1440
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG14"
               Height          =   225
               Index           =   13
               Left            =   2160
               TabIndex        =   40
               Tag             =   "14"
               Top             =   1440
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG13"
               Height          =   225
               Index           =   12
               Left            =   1080
               TabIndex        =   39
               Tag             =   "13"
               Top             =   1440
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG12"
               Height          =   225
               Index           =   11
               Left            =   120
               TabIndex        =   38
               Tag             =   "12"
               Top             =   1440
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG11"
               Height          =   225
               Index           =   10
               Left            =   3360
               TabIndex        =   37
               Tag             =   "11"
               Top             =   1080
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG10"
               Height          =   225
               Index           =   9
               Left            =   2160
               TabIndex        =   36
               Tag             =   "10"
               Top             =   1080
               Width           =   735
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG9"
               Height          =   225
               Index           =   8
               Left            =   1080
               TabIndex        =   35
               Tag             =   "9"
               Top             =   1080
               Width           =   975
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG8"
               Height          =   225
               Index           =   7
               Left            =   120
               TabIndex        =   34
               Tag             =   "8"
               Top             =   1080
               Width           =   855
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG7"
               Height          =   225
               Index           =   6
               Left            =   3360
               TabIndex        =   33
               Tag             =   "7"
               Top             =   720
               Width           =   975
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG6"
               Height          =   225
               Index           =   5
               Left            =   2160
               TabIndex        =   32
               Tag             =   "6"
               Top             =   720
               Width           =   975
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG5"
               Height          =   225
               Index           =   4
               Left            =   1080
               TabIndex        =   31
               Tag             =   "5"
               Top             =   720
               Width           =   855
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG4"
               Height          =   225
               Index           =   3
               Left            =   120
               TabIndex        =   30
               Tag             =   "4"
               Top             =   720
               Width           =   855
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG2"
               Height          =   225
               Index           =   2
               Left            =   2160
               TabIndex        =   29
               Tag             =   "2"
               Top             =   360
               Value           =   1  'Checked
               Width           =   975
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG3"
               Height          =   225
               Index           =   1
               Left            =   3360
               TabIndex        =   28
               Tag             =   "3"
               Top             =   360
               Width           =   975
            End
            Begin VB.CheckBox Check1 
               Caption         =   "DG1"
               Height          =   225
               Index           =   0
               Left            =   1080
               TabIndex        =   27
               Tag             =   "1"
               Top             =   360
               Value           =   1  'Checked
               Width           =   735
            End
         End
      End
      Begin VB.Frame Frame2 
         Caption         =   "Scan And Recogition"
         Height          =   4575
         Left            =   240
         TabIndex        =   1
         Top             =   360
         Width           =   3615
         Begin VB.ComboBox ScrollMode 
            Enabled         =   0   'False
            Height          =   300
            ItemData        =   "Form1.frx":0000
            Left            =   120
            List            =   "Form1.frx":0002
            TabIndex        =   57
            Text            =   "ScrollMode"
            Top             =   1800
            Width           =   3135
         End
         Begin VB.TextBox ConFigPath 
            Height          =   390
            Left            =   1680
            TabIndex        =   55
            Text            =   "IDCardConfig.ini"
            Top             =   840
            Width           =   1695
         End
         Begin VB.CommandButton ConfigFilePath 
            Caption         =   "ConfigFilePath"
            Height          =   420
            Left            =   120
            TabIndex        =   54
            Top             =   840
            Width           =   1455
         End
         Begin VB.CommandButton Button_RecogSID 
            Caption         =   "RecogSIDCard"
            Enabled         =   0   'False
            Height          =   375
            Left            =   120
            TabIndex        =   22
            Top             =   3960
            Width           =   3255
         End
         Begin VB.CommandButton Command2 
            Caption         =   "Identity Recogition"
            Enabled         =   0   'False
            Height          =   375
            Left            =   120
            TabIndex        =   15
            Top             =   3360
            Width           =   3255
         End
         Begin VB.TextBox Text2 
            Enabled         =   0   'False
            Height          =   375
            Left            =   1680
            TabIndex        =   13
            Text            =   "13"
            Top             =   1320
            Width           =   1695
         End
         Begin VB.CommandButton Command3 
            Caption         =   "Free Kerenl"
            Enabled         =   0   'False
            Height          =   375
            Left            =   120
            TabIndex        =   5
            Top             =   2880
            Width           =   3255
         End
         Begin VB.TextBox Text1 
            Height          =   375
            Left            =   1080
            TabIndex        =   3
            Top             =   360
            Width           =   2295
         End
         Begin VB.CommandButton Command1 
            Caption         =   "Load Kernel"
            Height          =   375
            Left            =   120
            TabIndex        =   4
            Top             =   2280
            Width           =   3255
         End
         Begin VB.Label Label5 
            Caption         =   "Device:"
            Height          =   255
            Left            =   3360
            TabIndex        =   21
            Top             =   4560
            Width           =   735
         End
         Begin VB.Label Label3 
            Caption         =   "Card Type"
            Height          =   255
            Left            =   360
            TabIndex        =   14
            Top             =   1440
            Width           =   1095
         End
         Begin VB.Label Label2 
            Caption         =   "User ID:"
            Height          =   255
            Left            =   120
            TabIndex        =   2
            Top             =   480
            Width           =   855
         End
      End
   End
   Begin VB.Frame Frame8 
      Caption         =   "Result"
      Height          =   3855
      Left            =   120
      TabIndex        =   58
      Top             =   5520
      Width           =   8175
      Begin VB.TextBox ResultTextBox 
         Height          =   6375
         Left            =   120
         MultiLine       =   -1  'True
         ScrollBars      =   2  'Vertical
         TabIndex        =   59
         Top             =   240
         Width           =   4095
      End
   End
   Begin VB.Image Image1 
      Height          =   3735
      Left            =   8760
      Stretch         =   -1  'True
      Top             =   5640
      Width           =   3855
   End
   Begin VB.Label Label4 
      Caption         =   "Card Type"
      Height          =   255
      Left            =   480
      TabIndex        =   20
      Top             =   4080
      Width           =   855
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function InitIDCard Lib "IDCard.dll" (ByVal lpUserId As String, ByVal nType As Long, ByVal lpDirectory As String) As Long
    
    Private Declare Function FreeIDCard Lib "IDCard.dll" () As Integer
    
    Private Declare Function SetUserDefinedImageSize Lib "IDCard.dll" (ByVal nWidth As Long, ByVal nHeight As Long) As Boolean

    Private Declare Function CheckDeviceOnline Lib "IDCard.dll" () As Boolean
   
    Private Declare Function SetIDCardID Lib "IDCard.dll" (ByVal nMainID As Long, ByRef nSubID As Long, ByVal nSubIdCount As Long) As Long
   
    Private Declare Function AddIDCardID Lib "IDCard.dll" (ByVal nMainID As Long, ByRef nSubID As Long, ByVal nSubIdCount As Long) As Long

    Private Declare Function GetCurrentDevice Lib "IDCard.dll" (ByRef deviceName As Byte, ByVal nBufferLenth As Long) As Boolean
   
    Private Declare Function GetDeviceSN Lib "IDCard.dll" (ByRef lpBuffer As Byte, ByVal nBufferLenth As Long) As Long

    Private Declare Function GetVersionInfo Lib "IDCard.dll" (ByRef lpBuffer As Byte, ByVal nBufferLenth As Long) As Long
  
    Private Declare Function DetectDocument Lib "IDCard.dll" () As Long

    Private Declare Function SaveImageEx Lib "IDCard.dll" (ByVal lpFileName As String, ByVal nType As Long) As Long
    
    Private Declare Function AutoProcessIDCard Lib "IDCard.dll" (ByRef nCardType As Long) As Long
    
    Private Declare Function GetRecogResultEx Lib "IDCard.dll" (ByVal nAttribute As Long, ByVal nIndex As Long, ByRef lpBuffer As Byte, ByRef nBufferLen As Long) As Long
    
    Private Declare Function GetFieldNameEx Lib "IDCard.dll" (ByVal nAttribute As Long, ByVal nIndex As Long, ByRef lpBuffer As Byte, ByRef nBufferLen As Long) As Long
    
    Private Declare Function SetRecogDG Lib "IDCard.dll" (ByVal nDG As Long) As Long
    
    Private Declare Function SetSaveImageType Lib "IDCard.dll" (ByVal nImageType As Long) As Long
    
    Private Declare Function SetRecogVIZ Lib "IDCard.dll" (ByVal bRecogVIZ As Boolean) As Long
    
    Private Declare Function SetConfigByFile Lib "IDCard.dll" (ByVal lpConfigFile As String) As Long
    
    Private Declare Function ResetIDCardID Lib "IDCard.dll" () As Integer
    
    
'声明接口
    '初始化证件接口

    '打开端口函数
    Private Declare Function SDT_OpenPort Lib "sdtapi.dll" (ByVal iPort As Long) As Long
    '关闭端口函数
    Private Declare Function SDT_ClosePort Lib "sdtapi.dll" (ByVal iPort As Long) As Long
    '开始寻找身份证
    Private Declare Function SDT_StartFindIDCard Lib "sdtapi.dll" (ByVal iPart As Long, ByRef pRAPDU() As Byte, ByVal iIfOpen As Long) As Long
    '选择身份证

    Private Declare Function SDT_SelectIDCard Lib "sdtapi.dll" (ByVal iPort As Long, ByRef pRAPDU() As Byte, ByVal iIfOpen As Long) As Long
    '将数据写入文件

    Private Declare Function SDT_ReadBaseMsgToFile Lib "sdtapi.dll" (ByVal iPortID As Long, ByRef pcCHMsgFileName As String, ByRef puiCHMsgFileLen As Long, ByRef pcPHMsgFileName As String, ByRef puiPHMsgFileName As String, ByVal iIfOpen As Long)
    '将数据写入数组

    Private Declare Function SDT_ReadBaseMsg Lib "sdtapi.dll" (ByVal iPort As Long, ByRef pucCHMsg As Byte, ByRef puiCHmsgLen As Long, ByRef pucPHMsg As Byte, ByRef puiPHMsgLen As Long, ByVal iIfOpen As Long) As Long
    Private Declare Function SDT_ReadNewAppMsg Lib "sdtapi.dll" (ByVal iPort As Long, ByVal pucAppMsg As String, ByRef puiAppmsgLen As Long, ByVal iIfOpen As Long) As Long
    '由wlt得到bmp
    Private Declare Function GetBmp Lib "WltRS.dll" (ByVal filename As String, ByVal nType As Long) As Long
    '获取序列号
    Private Declare Function SDT_GetSAMIDToStr Lib "sdtapi.dll" (ByVal iPort As Integer, ByRef pcSAMIDStr As Byte, ByVal iIfOpen As Integer) As Long
    Private Declare Function SDT_GetSAMID Lib "sdtapi.dll" (ByVal iPort As Integer, ByRef pcSAMID As Byte, ByVal iIfOpen As Integer) As Long

    Dim m_NIDapi As Boolean '= False
    Dim pcCHMsgFileName As String
    Dim puiCHMsgFileLen As Long
    Dim pcPHMsgFileName As String
    Dim puiPHMsgFileLen As Long
    Dim pucCHMsg(512) As Byte
    Dim puiCHmsgLen As Long
    Dim pucPHMsg(1024) As Byte
    Dim puiPHMsgLen As Long
    Dim strImagePath(5) As String
    Dim nSaveFlag(5) As Long
    Dim str1 As String
    Dim m_nOpenPort As Long '= 0
    Dim nIndex As Long  '= 0

    Dim m_bIsInitSuccess As Boolean

Private Sub Button_Next_Click()
        
    nIndex = nIndex + 1
    If nIndex = 5 Then
        nIndex = 0
    End If
        
    For i = nIndex To 4
          If Check_Image(i).value Then
                Image1.Picture = LoadPicture(strImagePath(i))
                nIndex = i
                Exit Sub
          End If
    Next i
        
    For i = 0 To 4
          If Check_Image(i).value Then
                Image1.Picture = LoadPicture(strImagePath(i))
                nIndex = i
                Exit Sub
          End If
    Next i
End Sub

Private Sub Button_Pre_Click()
    nIndex = nIndex - 1
    If nIndex = -1 Then
        nIndex = 4
    End If
            
    For i = nIndex To 0 Step -1
          If Check_Image(i).value Then
                Image1.Picture = LoadPicture(strImagePath(i))
                nIndex = i
                Exit Sub
          End If
    Next i
        
    For i = 4 To 0 Step -1
          If Check_Image(i).value Then
                Image1.Picture = LoadPicture(strImagePath(i))
                nIndex = i
                Exit Sub
          End If
    Next i
End Sub

Private Sub Button_RecogSID_Click()

        '寻找卡

        Dim nRet As Long
        Dim pRAPDU(8) As Byte '//卡片输出
        Dim str As String
        nRet = SDT_ReadNewAppMsg(m_nOpenPort, str, puiCHmsgLen, 0)
        If nRet = &H90 Or nRet = &H91 Then
            MsgBox ("此卡已读过，请重新放证！")
            Exit Sub
        End If
        nRet = SDT_StartFindIDCard(m_nOpenPort, pRAPDU, 0)
        If nRet <> &H9F Then
            MsgBox ("寻找卡失败")
            Exit Sub
        End If

            '选卡
            nRet = SDT_SelectIDCard(m_nOpenPort, pRAPDU, 0)
            If nRet <> &H90 Then
                MsgBox ("选择身份证失败")
                Exit Sub
            End If

            '读取数据到数组
            nRet = SDT_ReadBaseMsg(m_nOpenPort, pucCHMsg(0), puiCHmsgLen, pucPHMsg(0), puiPHMsgLen, 0)
            If nRet <> &H90 Then
                MsgBox ("读取数据到数组失败")
                Exit Sub
            End If

            '显示基本信息
            'GetName (str)
           ' str = pucCHMsg
        
            
            Dim value As String
            value = pucCHMsg
          
            If Mid(value, 125, 1) = " " Then
              str = Mid(value, 1, 15)
              ResultTextBox.Text = "姓名:" & "  " & str & vbCrLf
              str = Mid(value, 16, 1)
              If str = "1" Then
                  str = "男"
              Else
                  str = "女"
              End If
              
              ResultTextBox.Text = ResultTextBox.Text + "性别:" & "  " & str & vbCrLf
              str = Mid(value, 17, 2)
              Select Case (str)
                  Case "01"
                      str = "汉"
                  Case "02"
                      str = "蒙古"
                  Case "03"
                      str = "回"
                  Case "04"
                      str = "藏"
                  Case "05"
                      str = "维吾尔"
                  Case "06"
                      str = "苗"
                  Case "07"
                      str = "彝"
                  Case "08"
                      str = "壮"
                  Case "09"
                      str = "布依"
                  Case "10"
                      str = "朝鲜"
                  Case "11"
                      str = "满"
                  Case "12"
                      str = "侗"
                  Case "13"
                      str = "瑶"
                  Case "14"
                      str = "白"
                  Case "15"
                      str = "土家"
                  Case "16"
                      str = "哈尼"
                  Case "17"
                      str = "哈萨克"
                  Case "18"
                      str = "傣"
                  Case "19"
                      str = "黎"
                  Case "20"
                      str = "傈僳"
                  Case "21"
                      str = "佤"
                  Case "22"
                      str = "畲"
                  Case "23"
                      str = "高山"
                  Case "24"
                      str = "拉祜"
                  Case "25"
                      str = "水"
                  Case "26"
                      str = "东乡"
                  Case "27"
                      str = "纳西"
                  Case "28"
                      str = "景颇"
                  Case "29"
                      str = "柯尔克孜"
                  Case "30"
                      str = "土"
                  Case "31"
                      str = "达斡尔"
                  Case "32"
                      str = "仫佬"
                  Case "33"
                      str = "羌"
                  Case "34"
                      str = "布朗"
                  Case "35"
                      str = "撒拉"
                  Case "36"
                      str = "毛南"
                  Case "37"
                      str = "仡佬"
                  Case "38"
                      str = "锡伯"
                  Case "39"
                      str = "阿昌"
                  Case "40"
                      str = "普米"
                  Case "41"
                      str = "塔吉克"
                  Case "42"
                      str = "怒"
                  Case "43"
                      str = "乌孜别克"
                  Case "44"
                      str = "俄罗斯"
                  Case "45"
                      str = "鄂温克"
                  Case "46"
                      str = "德昂"
                  Case "47"
                      str = "保安"
                  Case "48"
                      str = "裕固"
                  Case "49"
                      str = "京"
                  Case "50"
                      str = "塔塔尔"
                  Case "51"
                      str = "独龙"
                  Case "52"
                      str = "鄂伦春"
                  Case "53"
                      str = "赫哲"
                  Case "54"
                      str = "门巴"
                  Case "55"
                      str = "珞巴"
                  Case "56"
                      str = "基诺"
                  Case "97"
                      str = "其他"
                  Case "98"
                      str = "外国血统中国籍人士"
              End Select
              ResultTextBox.Text = ResultTextBox.Text + "民族:" & "  " & str & vbCrLf
              str = Mid(value, 19, 8)
              ResultTextBox.Text = ResultTextBox.Text + "出生日期:" & "  " & str & vbCrLf
              str = Mid(value, 27, 35)
              ResultTextBox.Text = ResultTextBox.Text + "住址:" & "  " & str & vbCrLf
            
              str = Mid(value, 62, 18)
              ResultTextBox.Text = ResultTextBox.Text + "公民身份号码:" & "  " & str & vbCrLf
              str = Mid(value, 80, 15)
              ResultTextBox.Text = ResultTextBox.Text + "签发机关:" & "  " & str & vbCrLf
              str = Mid(value, 95, 8)
              Dim str1 As String
              str1 = Mid(value, 103, 8)
              ResultTextBox.Text = ResultTextBox.Text + "有效期起始日期:" & str & vbCrLf
              ResultTextBox.Text = ResultTextBox.Text + "有效期终止日期:" & str1 & vbCrLf
              
               If puiPHMsgLen > 0 Then
                  ResultTextBox.Text = ResultTextBox.Text + "指纹信息:" & "有" & vbCrLf
               Else
                  ResultTextBox.Text = ResultTextBox.Text + "指纹信息:" & "无" & vbCrLf
               End If
              End If
            
            
            If Mid(value, 125, 1) = "I" Then
              str = Mid(value, 1, 60)
              ResultTextBox.Text = "姓名:" & "  " & str & vbCrLf
              str = Mid(value, 61, 1)
              If str = "1" Then
                  str = "男"
              Else
                  str = "女"
              End If
              
              ResultTextBox.Text = ResultTextBox.Text + "性别:" & "  " & str & vbCrLf
              str = Mid(value, 62, 15)
              ResultTextBox.Text = ResultTextBox.Text + "永久居留证号码:" & "  " & str & vbCrLf
              str = Mid(value, 77, 3)
              ResultTextBox.Text = ResultTextBox.Text + "国籍或所在地区代码:" & "  " & str & vbCrLf
              str = Mid(value, 80, 15)
              ResultTextBox.Text = ResultTextBox.Text + "中文姓名:" & "  " & str & vbCrLf
              str = Mid(value, 95, 8)
              str1 = Mid(value, 103, 8)
              ResultTextBox.Text = ResultTextBox.Text + "证件签发日期:" & str & vbCrLf
              ResultTextBox.Text = ResultTextBox.Text + "证件终止日期:" & str1 & vbCrLf
              str = Mid(value, 111, 8)
              ResultTextBox.Text = ResultTextBox.Text + "出生日期:" & "  " & str & vbCrLf
              str = Mid(value, 119, 2)
              ResultTextBox.Text = ResultTextBox.Text + "证件版本号:" & "  " & str & vbCrLf
              str = Mid(value, 121, 4)
              ResultTextBox.Text = ResultTextBox.Text + "受理机关代码:" & "  " & str & vbCrLf
              ResultTextBox.Text = ResultTextBox.Text + "证件类别:" & "  " & "I" & vbCrLf
              str = Mid(value, 126, 3)
              ResultTextBox.Text = ResultTextBox.Text + "预留项:" & "  " & str & vbCrLf
         End If
              
         If Mid(value, 125, 1) = "J" Then
              str = Mid(value, 1, 15)
              ResultTextBox.Text = "姓名:" & "  " & str & vbCrLf
              str = Mid(value, 16, 1)
              If str = "1" Then
                  str = "男"
              Else
                  str = "女"
              End If
              
              ResultTextBox.Text = ResultTextBox.Text + "性别:" & "  " & str & vbCrLf
              str = Mid(value, 17, 2)
              ResultTextBox.Text = ResultTextBox.Text + "预留区:" & "  " & str & vbCrLf
              str = Mid(value, 19, 8)
              ResultTextBox.Text = ResultTextBox.Text + "出生日期:" & "  " & str & vbCrLf
              str = Mid(value, 27, 35)
              ResultTextBox.Text = ResultTextBox.Text + "住址:" & "  " & str & vbCrLf
              str = Mid(value, 62, 18)
              ResultTextBox.Text = ResultTextBox.Text + "公民身份证号码:" & "  " & str & vbCrLf
              str = Mid(value, 80, 15)
              ResultTextBox.Text = ResultTextBox.Text + "签发机关:" & "  " & str & vbCrLf
              str = Mid(value, 95, 8)
              str1 = Mid(value, 103, 8)
              ResultTextBox.Text = ResultTextBox.Text + "有效期起始日期:" & str & vbCrLf
              ResultTextBox.Text = ResultTextBox.Text + "有效期终止日期:" & str1 & vbCrLf
              str = Mid(value, 111, 9)
              ResultTextBox.Text = ResultTextBox.Text + "通行证号码:" & "  " & str & vbCrLf
              str = Mid(value, 120, 2)
              ResultTextBox.Text = ResultTextBox.Text + "签发次数:" & "  " & str & vbCrLf
              str = Mid(value, 122, 3)
              ResultTextBox.Text = ResultTextBox.Text + "预留区:" & "  " & str & vbCrLf
              ResultTextBox.Text = ResultTextBox.Text + "证件类别:" & "  " & "J" & vbCrLf
              str = Mid(value, 126, 3)
              ResultTextBox.Text = ResultTextBox.Text + "预留区:" & "  " & str & vbCrLf
              If puiPHMsgLen > 0 Then
                  ResultTextBox.Text = ResultTextBox.Text + "指纹信息:" & "有" & vbCrLf
              Else
                  ResultTextBox.Text = ResultTextBox.Text + "指纹信息:" & "无" & vbCrLf
              End If
              
         End If

          TextDG.Text = " not any DG info"
          Image1.Visible = True
            '显示图像
           str = CurDir() '得到当前路径
           value = pucPHMsg
           str = str + "\head.wlt"
          
           Button_Pre.Enabled = False
           Button_Next.Enabled = False
        
          '将数据写入文件
           Open str For Binary As #2
             Put #2, , pucPHMsg
           Close #2
           
           nRet = GetBmp(str, 2)
           str = CurDir() + "\head.bmp"
           Image1.Picture = LoadPicture(str)
End Sub

Private Sub Command1_Click()


    If m_bIsInitSuccess = True Then
            ResultTextBox.Text = "The recognition engine is loaded successfully."
    
    Exit Sub
    End If
    
    Dim nRet As Long
    Dim strTmp As String
    Dim nConFig As Integer
    strTmp = Text1.Text
    If strTmp = "" Then
        Exit Sub
    End If
    
    nRet = InitIDCard(StrConv(strTmp, vbUnicode), 0, StrConv("", vbUnicode))
     
    
    If nRet = 0 Then
        ResultTextBox.Text = "The recognition engine is loaded successfully."
        ScrollMode.Enabled = True
        Command1.Enabled = False
        Command3.Enabled = True
        m_bIsInitSuccess = True
    Else
         Select Case (nRet)
         
            Case 1
                         
                ResultTextBox.Text = "UserID error."
                                             
            Case 2
                                                             
                ResultTextBox.Text = "Device initialization failed."
                                                                                 
            Case 3
                                                                                                 
                ResultTextBox.Text = "Failed to initialize the certificate core."
                                                                                                                     
            Case 4
                                                                                                                                     
                ResultTextBox.Text = "The authorization file was not found."
                                                                                                                                                         
            Case 5
                                                                                                                                                                         
                ResultTextBox.Text = "Failed to load template file."
                                                                                                                                                                                             
            Case 6
                                                                                                                                                                                                             
                ResultTextBox.Text = "Failed to initialize card reader."
                                                                                                                                                                                                                                 
            Case Else
                                                                                                                                                                                                                                                 
                ResultTextBox.Text = "The recognition engine is loaded failure."
            
            End Select
            
        'ResultTextBox.Text = "The recognition engine is loaded failure." & str(nRet)

        m_bIsInitSuccess = False
        Exit Sub
    End If
    
    Command6_Click (Index)
    Command8_Click (Index)
    Command9_Click (Index)
    Command10_Click (Index)
    
     '打开端口
    Dim iPort As Long

    If m_NIDapi = False Then
        Dim nRt As Long
        For iPort = 1001 To 1016
            nRt = SDT_OpenPort(iPort)
            If nRt = &H90 Then
                m_nOpenPort = iPort
                m_NIDapi = True
                Exit For
            End If
            
        Next iPort
    End If

    If m_NIDapi = False Then
        MsgBox ("Open port failed (打开端口失败)")
        Exit Sub
    End If
    Command12_Click (Index)
    
    Dim strConFigFile As String
    strConFigFile = ConFigPath.Text
    If strConFigFile <> "" Then

      nRet = SetConfigByFile(StrConv(strConFigFile, vbUnicode))
    End If
    
    Dim nSubID(1) As Long
    nSubID(0) = 0
    Dim nTmp As Long
    
    'nTmp = SetIDCardID(13, nSubID(0), 1)
    'nTmp = AddIDCardID(2, nSubID(0), 1)
        
        
        
    If ScrollMode.Text = "Automatic identification" Then
       Timer1.Enabled = True
    End If

End Sub


    
Private Sub Command10_Click(Index As Integer)
    If m_bIsInitSuccess = False Then
        ResultTextBox.Text = "Please successful loading recognition engine"
        Exit Sub
    End If
    Dim nRet As Integer
    Dim bRet As Long
    Dim strTmp(128) As Byte
    nRet = GetDeviceSN(strTmp(0), 16)
    If nRet = 0 Then
        Text_ButtonType.Text = strTmp
    End If
End Sub

    
Private Sub Command12_Click(Index As Integer)

    Dim nRet As Integer
    Dim strTmp(1023) As Byte
    nRet = SDT_GetSAMIDToStr(1001, strTmp(0), 0)
    If nRet = &H90 Then
        Text_ButtonRFIDType.Text = StrConv(strTmp, vbUnicode)
    Else
        Text_ButtonRFIDType.Text = "Failed to get Device Sequence"
    End If
    
    Exit Sub
    
    'SDT_GetSAMID获取序列号有点小问题**************************************************************************************************************************************************'
    Dim i As Integer
    Dim nHex As Integer
    Dim nVal As Integer
    Dim szHexBuf(64) As Byte
    Dim sHexBufSrc(129) As Byte
    Dim StrHex As String
    
    nRet = SDT_GetSAMID(1001, szHexBuf(0), 0)
    If nRet = &H90 Then
        i = 0
        nVal = 0
        For j = 0 To 63
        
            nHex = szHexBuf(j) / 16
            If nVal + 48 >= 48 And nHex + 48 <= 57 Then
               sHexBufSrc(i) = nHex + 48
            End If

           If nVal + 55 >= 65 And nHex + 55 <= 70 Then
              sHexBufSrc(i) = nHex + 55
            End If
        
           i = i + 1
           nHex = szHexBuf(j) Mod 16
           If nVal + 48 >= 48 And nHex + 48 <= 57 Then
              sHexBufSrc(i) = nHex + 48
           End If

           If nVal + 55 >= 65 And nHex + 55 <= 70 Then
              sHexBufSrc(i) = nHex + 55
           End If
           i = i + 1
        
       Next j
       
       
        For j = 0 To 128
            Text_ButtonRFIDType.Text = Text_ButtonRFIDType.Text + Chr(sHexBufSrc(j))
        Next j
       
        '0500030028833016734005173000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000 后面0未去掉 20190919
       'nRet = 0
        'For j = 128 To 0 Step -1
           ' If Chr(sHexBufSrc(j)) = "0" Or Chr(sHexBufSrc(j)) = "\0" Then
             '  nRet = nRet + 1
            'Else
              ' Exit For
          '  End If
        'Next j
   
      'Text_ButtonRFIDType.Text = nRet
       
       
    Else
        Text_ButtonRFIDType.Text = "Failed to get Device Sequence"
    End If
End Sub

Private Sub Command2_Click()


        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "Please successful loading recognition engine"
            Exit Sub
        End If
             

        '
        Dim nCardType As Long
        nCardType = CInt(Val(Text2.Text))
        If (nCardType <= 0) Then
            ResultTextBox.Text = "Invalid CardSizeType,please re-enter a valid."
            Exit Sub
        End If

        Dim nSubID(1) As Long
        nSubID(0) = 0
        Dim nTmp As Long
        nTmp = ResetIDCardID()
        nTmp = AddIDCardID(nCardType, nSubID(0), 1)
       
        Dim nDG As Long: nDG = 0
        Dim nSaveImage As Long: nSaveImage = 0
        Dim bViz As Boolean
        
        For i = 0 To 16
                If Check1(i).value Then
                    nDG = nDG + 2 ^ (Check1(i).Tag - 1)
                End If
        Next i
        
        For i = 0 To 4
              If Check_Image(i).value Then
                    nSaveImage = nSaveImage + 2 ^ (Check_Image(i).Tag - 1)
                    nSaveFlag(i) = Check_Image(i).value
                End If
        Next i
        
        If Option1.value = -1 Then
            bViz = True
            Else
            bViz = False
        End If
        

        Dim MAX_CH_NUM As Long
        MAX_CH_NUM = 256
        Dim szFieldValue(255) As Byte
        Dim szFieldName(255) As Byte
        
        SetRecogDG (nDG)
        SetSaveImageType (nSaveImage)
        SetRecogVIZ (bViz)
        
        nCardType = 0
        nRet = AutoProcessIDCard(nCardType)
        Dim nIndex As Long
        nIndex = 1
        ResultTextBox.Text = "recognition successful" & vbCrLf
        
        If nRet > 0 Then
             Do While (1)
                 Dim strTmp(255) As Byte
                 Dim strTmp1(255) As Byte
                 Dim strFieldName As String
                 Dim strFieldValue As String
                 nRet = GetRecogResultEx(1, nIndex, szFieldValue(0), MAX_CH_NUM)
                 
                 If nRet = 3 Then
                    Exit Do
                 End If
                
                 MAX_CH_NUM = 256
                 nRet = GetFieldNameEx(1, nIndex, szFieldName(0), MAX_CH_NUM)
                 MAX_CH_NUM = 256
                 If nnRet = 0 Then
                     strFieldName = szFieldName
                     ResultTextBox.Text = ResultTextBox.Text + strFieldName
                     ResultTextBox.Text = ResultTextBox.Text + ":"
                     strFieldValue = szFieldValue
                     ResultTextBox.Text = ResultTextBox.Text + strFieldValue
                     ResultTextBox.Text = ResultTextBox.Text + vbCrLf
                 End If
                nIndex = nIndex + 1
            Loop
            
            'DG
            Dim nLen As Long: nLen = 128
            Dim nLenDg As Long: nLenDg = 42000
            Dim szValue As String
            Dim strNameInfo As String
            Dim strValueInfo As String
            
            If nCardType = 1 Then
                nIndex = 1
                TextDG.Text = "Success to read the card" & vbCrLf
                 Do While (1)
                    Dim b(256) As Byte
                    Dim a(42000) As Byte
                    nRet = GetFieldNameEx(0, nIndex, b(0), nLen)
                    nRet = GetRecogResultEx(0, nIndex, a(0), nLenDg)
                    If nRet = 3 Then
                        Exit Do
                    End If
                    If nRet = 0 Then
                        strNameInfo = b
                        strValueInfo = a
                        TextDG.Text = TextDG.Text + strNameInfo
                        TextDG.Text = TextDG.Text + ":"
                        TextDG.Text = TextDG.Text + strValueInfo
                        TextDG.Text = TextDG.Text + vbCrLf
                                   
                        nLen = 128
                        nLenDg = 42000
                    End If
                    
                    nIndex = nIndex + 1
                Loop
            Else
                TextDG.Text = " not any DG info"
            End If
        
        Else
            'ResultTextBox.Text =
            ResultTextBox.Text = "Return Value:   " + str(nRet) + vbCrLf + "fail to read the card" + vbCrLf
            Image1.Visible = False
            Exit Sub
        
        End If
               
        strImagePath(0) = Text_ImagePath.Text + "\EPRSampleDemo.jpg"
        strImagePath(1) = Text_ImagePath.Text + "\EPRSampleDemoIR.jpg"
        strImagePath(2) = Text_ImagePath.Text + "\EPRSampleDemoUV.jpg"
        strImagePath(3) = Text_ImagePath.Text + "\EPRSampleDemoHead.jpg"
        strImagePath(4) = Text_ImagePath.Text + "\EPRSampleDemoHeadEC.jpg"
        
        
        Dim strSrcImg1 As String
        strSrcImg1 = Text_ImagePath.Text + "\EPRSampleDemo.jpg"
        strPath = StrConv(strSrcImg1, vbUnicode)
        nRet = SaveImageEx(strPath, nSaveImage)
        
        If nRet <> 0 Then
            
            strErrCode = "return value：" & str(nRet) & vbCrLf
            ResultTextBox.Text = ResultTextBox.Text + strErrCode
            ResultTextBox.Text = ResultTextBox.Text + "save image failed"
            Exit Sub
        End If

     Dim nImageNum As Long
     nImageNum = 0
     For j = 0 To 4
      If Check_Image(j).value Then
            nImageNum = nImageNum + 1
      End If
     Next j
    
    If nImageNum > 1 Then
         Button_Pre.Enabled = True
         Button_Next.Enabled = True
    End If
    
    For i = 0 To 4
        If Check_Image(i).value Then
            Image1.Visible = True
            Image1.Picture = LoadPicture(strImagePath(i))
            Exit Sub
        End If
    Next i

        
End Sub

Private Sub Command3_Click()

        If m_bIsInitSuccess = True Then
        Dim d As Integer
            ScrollMode.Enabled = False
            Command3.Enabled = False
            Command1.Enabled = True
            
            Text_KernelVersion.Text = ""
            Text_DeviceName.Text = ""
            Text_DeviceStatus.Text = ""
            Text_ButtonType.Text = ""
            Text_ButtonRFIDType.Text = ""
            Timer1.Enabled = False
            d = FreeIDCard()
            ResultTextBox.Text = "Successful free recognition engine"
            TextDG = ""
            Image1.Visible = False
            m_bIsInitSuccess = False
        Else
            ResultTextBox.Text = "no load engine"
        End If
End Sub



Private Sub Command6_Click(Index As Integer)
        If m_bIsInitSuccess = False Then
            Text_KernelVersion.Text = "Please successful loading recognition engine."
            Exit Sub
        End If
        Dim MAX_CH_NUM As Long
        MAX_CH_NUM = 50
        Dim strTmp(50) As Byte
        
        nRet = GetVersionInfo(strTmp(0), MAX_CH_NUM)
        Text_KernelVersion.Text = strTmp
End Sub



Private Sub Command8_Click(Index As Integer)
        If m_bIsInitSuccess = False Then
            Text_DeviceName.Text = "Please successful loading recognition engine."
            Exit Sub
        End If
        Dim MAX_CH_NUM As Long
        MAX_CH_NUM = 128
        Dim bRet As Long
        Dim strTmp(128) As Byte
        'strTmp = New String(CChar(""), 128)
       ' Dim a As Byte()
        'a = System.Text.Encoding.Unicode.GetBytes(strTmp)
        bRet = GetCurrentDevice(strTmp(0), MAX_CH_NUM)
        If bRet = 1 Then
            Text_DeviceName.Text = strTmp
        End If
End Sub

Private Sub Command9_Click(Index As Integer)
        If m_bIsInitSuccess = False Then
            Text_DeviceStatus.Text = "Please successful loading recognition engine."
            Exit Sub
        End If
        Dim bRet As Long
        bRet = CheckDeviceOnline()
        If bRet = 1 Then
            Text_DeviceStatus.Text = "The device is online."
        Else
            Text_DeviceStatus.Text = "The device is not online."
        End If
End Sub


Private Sub ConfigFilePath_Click()
      CommonDialog1.ShowOpen
      ConFigPath.Text = CommonDialog1.filename
End Sub


Private Sub Form_Load()

 Dim strFieldValue As String

    ScrollMode.AddItem "Automatic identification"
    ScrollMode.AddItem "Manual identification"
    ScrollMode.Text = "Automatic identification"
End Sub



Private Sub ScrollMode_Click()
        Dim strConFigFile As String
        If ScrollMode.Text = "Automatic identification" Then
        
            strConFigFile = ConFigPath.Text
            If strConFigFile <> "" Then
              nRet = SetConfigByFile(StrConv(strConFigFile, vbUnicode))
            End If
            Timer1.Enabled = True
            ResultTextBox.Text = ""
            TextDG.Text = ""
            Button_RecogSID.Enabled = False
            Command2.Enabled = False
            Text2.Enabled = False
            Image1.Visible = False
        End If

        If ScrollMode.Text = "Manual identification" Then
            Timer1.Enabled = False
            ResultTextBox.Text = ""
            TextDG.Text = ""
            Button_RecogSID.Enabled = True
            Command2.Enabled = True
            Text2.Enabled = True
            Image1.Visible = False
        End If
End Sub

Private Sub Timer1_Timer()

        If DetectDocument <> 1 Then
            Exit Sub
        End If
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "Please successful loading recognition engine."
            Exit Sub
        End If
       
        Dim nDG As Long: nDG = 0
        Dim nSaveImage As Long: nSaveImage = 0
        Dim bViz As Boolean
        
        For i = 0 To 16
                If Check1(i).value Then
                    nDG = nDG + 2 ^ (Check1(i).Tag - 1)
                End If
        Next i
        
        For i = 0 To 4
              If Check_Image(i).value Then
                    nSaveImage = nSaveImage + 2 ^ (Check_Image(i).Tag - 1)
                End If
        Next i
        
        If Option1.value = -1 Then
            bViz = True
            Else
            bViz = False
        End If
        

     
        
        Dim MAX_CH_NUM As Long
        MAX_CH_NUM = 256
        Dim szFieldValue(255) As Byte
        Dim szFieldName(255) As Byte
        
        SetRecogDG (nDG)
        SetSaveImageType (nSaveImage)
        SetRecogVIZ (bViz)
        
        Dim nCardType As Long
        Dim nRet As Long
        Dim nIndex As Long
        nIndex = 1
        ResultTextBox.Text = "recognition successful" & vbCrLf
        nCardType = 0
        nRet = AutoProcessIDCard(nCardType)

        If nRet > 0 Then

             Do While (1)

                 Dim strTmp(255) As Byte
                 Dim strTmp1(255) As Byte
                 Dim strFieldName As String
                 Dim strFieldValue As String
                 
                 nRet = GetRecogResultEx(1, nIndex, szFieldValue(0), MAX_CH_NUM)

                 If nRet = 3 Then
                    Exit Do
                 End If
                
                 MAX_CH_NUM = 256
                 nRet = GetFieldNameEx(1, nIndex, szFieldName(0), MAX_CH_NUM)
                 MAX_CH_NUM = 256
                 If nnRet = 0 Then
                     strFieldName = szFieldName
                     ResultTextBox.Text = ResultTextBox.Text + strFieldName
                     ResultTextBox.Text = ResultTextBox.Text + ":"
                     strFieldValue = szFieldValue
                     ResultTextBox.Text = ResultTextBox.Text + strFieldValue
                     ResultTextBox.Text = ResultTextBox.Text + vbCrLf
                 End If
                nIndex = nIndex + 1
            Loop

            'DG
            Dim nLen As Long: nLen = 128
            Dim nLenDg As Long: nLenDg = 42000
            Dim szValue As String
            Dim strNameInfo As String
            Dim strValueInfo As String
            
            If nCardType = 1 Then
                nIndex = 1
                TextDG.Text = "Success to read the card" & vbCrLf
                 Do While (1)
                    Dim b(256) As Byte
                    Dim a(42000) As Byte
                    nRet = GetFieldNameEx(0, nIndex, b(0), nLen)
                    nRet = GetRecogResultEx(0, nIndex, a(0), nLenDg)
                    If nRet = 3 Then
                        Exit Do
                    End If
                    If nRet = 0 Then
                        strNameInfo = b
                        strValueInfo = a
                        TextDG.Text = TextDG.Text + strNameInfo
                        TextDG.Text = TextDG.Text + ":"
                        TextDG.Text = TextDG.Text + strValueInfo
                        TextDG.Text = TextDG.Text + vbCrLf
                                   
                        nLen = 128
                        nLenDg = 42000
                    End If
                    
                    nIndex = nIndex + 1
                Loop
            Else
                TextDG.Text = " not any DG info"
            End If
        
        Else
            ResultTextBox.Text = "Return Value:" + str(nRet) + vbCrLf
            ResultTextBox.Text = ResultTextBox.Text + "fail to read the card" + vbCrLf
            Image1.Visible = False

            Exit Sub
        
        End If
    
        Dim strRunPath As String
       'strRunPath = application.sTartuppath + "\"
        
        strImagePath(0) = Text_ImagePath.Text + "\EPRSampleDemo.jpg"
        strImagePath(1) = Text_ImagePath.Text + "\EPRSampleDemoIR.jpg"
        strImagePath(2) = Text_ImagePath.Text + "\EPRSampleDemoUV.jpg"
        strImagePath(3) = Text_ImagePath.Text + "\EPRSampleDemoHead.jpg"
        strImagePath(4) = Text_ImagePath.Text + "\EPRSampleDemoHeadEC.jpg"
        
        strSrcImg = Text_ImagePath.Text + "\EPRSampleDemo.jpg"
        Dim strPath As String
        strPath = StrConv(strSrcImg, vbUnicode)
        nRet = SaveImageEx(strPath, nSaveImage)

        If nRet <> 0 Then
            strErrCode = "return value：" & str(nRet) & vbCrLf
            ResultTextBox.Text = ResultTextBox.Text + strErrCode
            ResultTextBox.Text = ResultTextBox.Text + "save image failed"
            'Exit Sub
        End If
                    
        Dim nImageNum As Long
        nImageNum = 0
        For j = 0 To 4
         If Check_Image(j).value Then
               nImageNum = nImageNum + 1
         End If
        Next j
        
       If nImageNum > 1 Then
            Button_Pre.Enabled = True
            Button_Next.Enabled = True
       End If
            
       For i = 0 To 4
        If Check_Image(i).value Then
           Image1.Visible = True
           Image1.Picture = LoadPicture(strImagePath(i))
           Exit Sub
        End If
       Next i
End Sub

Private Sub ImagePath_Click()
    Drive1.Visible = True
    Dir1.Visible = True
    Yes.Visible = True
    NO.Visible = True

End Sub


Private Sub Drive1_Change()
    Dir1 = Drive1.Drive
End Sub

Private Sub Dir1_Change()
     Text_ImagePath.Text = Dir1.Path
End Sub

Private Sub Yes_Click()
   
    Dir1.Visible = False
    Drive1.Visible = False
    Yes.Visible = False
    NO.Visible = False
    
End Sub

Private Sub NO_Click()
    Dir1.Visible = False
    Drive1.Visible = False
    Yes.Visible = False
    NO.Visible = False
    Text_ImagePath.Text = ""
End Sub
