
Option Strict Off
Option Explicit On
Imports System
Imports System.IO
Imports VB = Microsoft.VisualBasic
Public Class DGtext

    Private Declare Function InitIDCard Lib "IDCard.dll" (ByRef lpUserId As Byte, ByVal nType As Integer, ByRef lpDirectory As Byte) As Integer
    Private Declare Sub FreeIDCard Lib "IDCard.dll" ()
    Private Declare Function CheckDeviceOnline Lib "IDCard.dll" () As Boolean
    Private Declare Function AddIDCardID Lib "IDCard.dll" (ByVal nMainID As Integer, ByVal nSubID() As Integer, ByVal nSubIdCount As Integer) As Integer
    Private Declare Function GetCurrentDevice Lib "IDCard.dll" (ByRef deviceName As Byte, ByVal nBufferLenth As Long) As Boolean
    Private Declare Sub GetVersionInfo Lib "IDCard.dll" (ByRef lpBuffer As Byte, ByVal nBufferLenth As Integer)
    Private Declare Function GetDeviceSN Lib "IDCard.dll" (ByRef deviceName As Byte, ByVal nBufferLenth As Long) As Integer
    Private Declare Function SaveImageEx Lib "IDCard.dll" (ByRef lpFileName As Byte, ByVal nType As Integer) As Integer

    Private Declare Function AutoProcessIDCard Lib "IDCard.dll" (ByRef nCardType As Integer) As Integer
    Private Declare Function GetRecogResultEx Lib "IDCard.dll" (ByVal nAttribute As Integer, ByVal nIndex As Integer, ByRef lpBuffer As Byte, ByRef nBufferLen As Integer) As Integer
    Private Declare Function GetFieldNameEx Lib "IDCard.dll" (ByVal nAttribute As Integer, ByVal nIndex As Integer, ByRef lpBuffer As Byte, ByRef nBufferLen As Integer) As Integer
    Private Declare Sub SetRecogDG Lib "IDCard.dll" (ByVal nDG As Integer)
    Private Declare Sub SetSaveImageType Lib "IDCard.dll" (ByVal nImageType As Integer)
    Private Declare Sub SetRecogVIZ Lib "IDCard.dll" (ByVal bRecogVIZ As Boolean)
    Private Declare Function DetectDocument Lib "IDCard.dll" () As Integer
    Private Declare Function SetConfigByFile Lib "IDCard.dll" (ByRef lpConfigFile As Byte) As Integer
    Private Declare Sub ResetIDCardID Lib "IDCard.dll" ()

    '---------------------------------The Followed is SID.------------------------------------’
    '打开端口函数
    Private Declare Function SDT_OpenPort Lib "sdtapi.dll" (ByVal iPort As Integer) As Integer

    'Public Declare Function SDT_OpenPortA Lib "sdtapi.dll" Alias "SDT_OpenPort" (ByVal iPort As Long) As Long

    '关闭端口函数
    Private Declare Function SDT_ClosePort Lib "sdtapi.dll" (ByVal iPort As Integer) As Integer

    'Public Declare Function SDT_ClosePortA Lib "sdtapi.dll" Alias "SDT_ClosePort" (ByVal iPort As Long) As Long

    '开始寻找身份证
    Private Declare Function SDT_StartFindIDCard Lib "sdtapi.dll" (ByVal iPart As Integer, ByRef pRAPDU() As Byte, ByVal iIfOpen As Integer) As Integer

    'Public Declare Function SDT_StartFindIDCardA Lib "sdtapi.dll" Alias "SDT_StartFindIDCard" (ByVal iPart As Long, ByRef pRAPDU As Byte, ByVal iIfOpen As Long) As Long

    '选择身份证
    Private Declare Function SDT_SelectIDCard Lib "sdtapi.dll" (ByVal iPort As Integer, ByRef pRAPDU() As Byte, ByVal iIfOpen As Integer) As Integer

    'Public Declare Function SDT_SelectIDCardA Lib "sdtapi.dll" Alias "SDT_SelectIDCard" (ByVal iPort As Long, ByRef pRAPDU As Byte, ByVal iIfOpen As Long) As Long

    '将数据写入文件
    Private Declare Function SDT_ReadBaseMsgToFile Lib "sdtapi.dll" (ByVal iPortID As Integer, ByRef pcCHMsgFileName As String, ByRef puiCHMsgFileLen As Integer, ByRef pcPHMsgFileName As String, ByRef puiPHMsgFileName As String, ByVal iIfOpen As Integer)

    '将数据写入数组
    Private Declare Function SDT_ReadBaseMsg Lib "sdtapi.dll" (ByVal iPort As Integer, ByVal pucCHMsg() As Byte, ByRef puiCHmsgLen As Integer, ByVal pucPHMsg() As Byte, ByRef puiPHMsgLen As Integer, ByVal iIfOpen As Integer) As Integer

    'Public Declare Function SDT_ReadBaseMsgA Lib "sdtapi.dll" Alias "SDT_ReadBaseMsg" (ByVal iPort As Long, ByRef pucCHMsg As Byte, ByRef puiCHMsgLen As Long, ByRef pucPHMsg As Byte, ByRef puiPHMsgLen As Long, ByVal iIfOpen As Long) As Long

    Private Declare Function SDT_ReadNewAppMsg Lib "sdtapi.dll" (ByVal iPort As Integer, ByVal pucAppMsg() As Byte, ByRef puiAppmsgLen As Integer, ByVal iIfOpen As Integer) As Integer

    'Public Declare Function SDT_ReadNewAppMsgA Lib "sdtapi.dll" Alias "SDT_ReadNewAppMsg" (ByVal iPort As Long, ByRef pucCHMsg As Byte, ByRef puiCHMsgLen As Long, ByVal iIfOpen As Long) As Long

    '由wlt得到bmp
    Private Declare Function GetBmp Lib "WltRS.dll" (ByRef filename As Byte, ByVal nType As Integer) As Integer
    '获取序列号
    Private Declare Function SDT_GetSAMIDToStr Lib "sdtapi.dll" (ByVal iPortID As Integer, ByVal pRAPDU() As Byte， ByVal iIfOpen As Integer) As Integer

    Private Declare Function SDT_GetSAMID Lib "sdtapi.dll" (ByVal iPortID As Integer, ByVal pRAPDU() As Byte， ByVal iIfOpen As Integer) As Integer

    'Public Declare Function SDT_ReadBaseMsgToFile Lib "sdtapi.dll" (ByVal iPortID As Long, ByRef pcCHMsgFileName As Byte, ByRef puiCHMsgFileLen As Long, ByRef pcPHMsgFileName As Byte, ByRef puiPHMsgFileLen As Long, ByVal iIfOpen As Long) As Long

    Dim m_NIDapi As Boolean = False
    Dim pcCHMsgFileName As String
    Dim puiCHMsgFileLen As Integer
    Dim pcPHMsgFileName As String
    Dim puiPHMsgFileLen As Integer
    Dim pucCHMsg(512) As Byte
    Dim puiCHMsgLen As Long
    Dim pucPHMsg(1024) As Byte
    Dim puiPHMsgLen As Long
    Dim str As String
    Dim str1 As String
    Dim m_nOpenPort As Integer = 0
    Dim m_bIsInitSuccess As Boolean = False
    Dim m_nReadSID As Integer = 0
    Dim m_ListImage As New List(Of Image)
    Dim m_nImageIndex As Integer = 0
    Dim nRetSaveimg As Integer = 0

    'Load recognition engine
    Private Sub BtnLoadKernal_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnLoadKernal.Click
        If m_bIsInitSuccess = True Then
            ResultTextBox.Text = "The recognition engine is loaded successfully."
            Exit Sub
        End If
        Dim nRet As Integer
        Dim nConFig As Integer
        Dim strTextConFigPath As String
        Dim strTmp As Byte()
        strTmp = System.Text.Encoding.Unicode.GetBytes(UserID.Text)

        strTextConFigPath = TextConfigfile.Text
        'If Dir(strTextConFigPath & "IDCard.dll") <> "" Then
        '    ResultTextBox.Text = "Failed to initialize the recognition engine."
        '    Exit Sub
        'End If
        If UserID.Text = "" Then
            Exit Sub
        End If

        nRet = InitIDCard(strTmp(0), 1, 0)
        If nRet = 0 Then
            ResultTextBox.Text = "The recognition engine is loaded successfully."
            m_bIsInitSuccess = True
            Me.RecongSoroll.Enabled = True
            BtnLoadKernal.Enabled = False
            Me.BtnFreeKernal.Enabled = True
            BtnGetVersion.Enabled = True
            BtnGetDeviceName.Enabled = True
            BtnCheckDeviceOnLine.Enabled = True
            BtnGetDeviceSN.Enabled = True
            BtnGetDeviceRFIDSN.Enabled = True
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
            'ResultTextBox.Text = "The recognition engine is loaded failure."
            m_bIsInitSuccess = False
            Exit Sub
        End If

        If strTextConFigPath <> "" Then
            strTmp = System.Text.Encoding.Unicode.GetBytes(TextConfigfile.Text)
            nConFig = SetConfigByFile(strTmp(0))
        End If

        BtnGetVersion_Click(sender, e)
        BtnCheckDeviceOnLine_Click(sender, e)
        BtnGetDeviceName_Click(sender, e)
        BtnGetDeviceSN_Click(sender, e)

        '打开端口
        Dim iPort As Integer
        m_nReadSID = 0
        If m_NIDapi = False Then
            Dim nRt As Integer
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
            MsgBox("打开端口失败")
            Exit Sub
        End If
        Button1_Click(sender, e)

        If Me.RecongSoroll.Text = "Automatic identification" Then
            Me.Timer1.Enabled = True
        End If

    End Sub


    Private Sub GetDGContent()

    End Sub

    Private Sub BtnRecog_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles btnRecog.Click
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "Please successful loading recognition engine."
            Exit Sub
        End If

        Dim nRet As Integer
        Dim nAuto As Integer
        Dim nCardType As Integer
        nCardType = 0

        nCardType = Int(Val(CardType.Text))
        If (nCardType <= 0) Then
            ResultTextBox.Text = "Invalid CardSizeType,please re-enter a valid."
            Exit Sub
        End If

        Dim nSubID(1) As Integer
        nSubID(0) = 0
        ResetIDCardID()
        AddIDCardID(nCardType, nSubID, 1)

        Dim nDG As Integer
        Dim nSaveImage As Integer
        Dim bVIZ As Boolean

        nDG = GetCheckBoxValueByGroup(Me.GroupBox5)
        nSaveImage = GetCheckBoxValueByGroup(Me.GroupBox6)
        bVIZ = Me.RadioButton1.Checked

        SetRecogDG(nDG)
        SetSaveImageType(nSaveImage)
        SetRecogVIZ(bVIZ)

        Dim nCard As Integer
        nCardType = 0

        ResultTextBox.Text = "recognition successful" & vbCrLf
        nAuto = AutoProcessIDCard(nCard)
        If nAuto > 0 Then
            GetContent()
            If nCard = 1 Then
                TextBoxDG.Clear()
                GetDGContent(nDG, True)
            Else
                TextBoxDG.Text = "not any DG info"
            End If

            If nCard = 1 Or nCard = 2 Then
                PictureBox_Image.Visible = True
            Else
                PictureBox_Image.Visible = False
            End If
        Else
            ResultTextBox.Text = "Return Value:"
            ResultTextBox.Text += nRet.ToString()
            ResultTextBox.Text += vbCrLf
            ResultTextBox.Text += "fail to read the card"
            ResultTextBox.Text += vbCrLf
            TextBoxDG.Text = ""
            PictureBox_Image.Visible = False
            Exit Sub
        End If
        Dim strImagePath As String = TextBox_ImagePath.Text + "\"
        Dim strSrcImg As String = strImagePath + "EPRSampleDemo.jpg"
        Dim strSavePath As Byte()
        strSavePath = System.Text.Encoding.Unicode.GetBytes(strSrcImg)
        nRet = SaveImageEx(strSavePath(0), nSaveImage)
        nSaveImage = -nRet

        SaveImagePath(strSrcImg, nSaveImage)
        If m_ListImage.Count > 0 Then
            PictureBox_Image.Image = m_ListImage(0)

        End If

    End Sub

    '
    Private Sub BtnFreeKernal_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnFreeKernal.Click

        If m_bIsInitSuccess = True Then
            BtnGetVersion.Enabled = False
            BtnGetDeviceName.Enabled = False
            BtnCheckDeviceOnLine.Enabled = False
            BtnGetDeviceSN.Enabled = False
            BtnGetDeviceRFIDSN.Enabled = False
            TextBox_SDKVersion.Clear()
            TextBox_DeviceName.Clear()
            TextBox_DeviceStatus.Clear()
            TextBox_SerialNumber.Clear()
            TextBox_RFID_SerialNumber.Clear()
            ResultTextBox.Text = "Successful free recognition engine"
            TextBoxDG.Clear()
            Me.Timer1.Enabled = False
            m_bIsInitSuccess = False
            BtnLoadKernal.Enabled = True
            Me.BtnFreeKernal.Enabled = False

            Me.RecongSoroll.Enabled = False
            Me.RecongSoroll.SelectedIndex = 0
            CardType.Enabled = False
            btnRecog.Enabled = False
            btnRecogSIDCard.Enabled = False
            PictureBox_Image.Visible = False
            FreeIDCard()
        Else
            ResultTextBox.Text = "Recognition engine is not loaded."
            ClosePort(sender, e)
        End If
    End Sub

    Private Sub SaveImagePath(ByVal strPath As String, ByVal nType As Integer)

        m_ListImage.Clear()
        m_nImageIndex = 0
        If CheckBox18.Checked = True And (((nRetSaveimg And 1) = 0) Or (nRetSaveimg = 0)) Then

            If File.Exists(strPath) Then
                Dim stream As New FileStream(strPath, FileMode.Open, FileAccess.Read)
                m_ListImage.Add(Image.FromStream(stream))
                stream.Close()
                stream.Dispose()

            End If
        End If


        If CheckBox21.Checked = True And (((nRetSaveimg And 2) = 0) Or (nRetSaveimg = 0)) Then
            Dim strIR As String = strPath.Insert(strPath.Length() - 4, "IR")
            If File.Exists(strIR) Then
                Dim stream As New FileStream(strIR, FileMode.Open, FileAccess.Read)
                m_ListImage.Add(Image.FromStream(stream))
                stream.Close()
                stream.Dispose()
            End If
        End If


        If CheckBox22.Checked = True And (((nRetSaveimg And 4) = 0) Or (nRetSaveimg = 0)) Then
            Dim strUV As String = strPath.Insert(strPath.Length() - 4, "UV")
            If File.Exists(strUV) Then
                Dim stream As New FileStream(strUV, FileMode.Open, FileAccess.Read)
                m_ListImage.Add(Image.FromStream(stream))
                stream.Close()
                stream.Dispose()
            End If
        End If


        If CheckBox19.Checked = True And (((nRetSaveimg And 8) = 0) Or (nRetSaveimg = 0)) Then
            Dim strHead As String = strPath.Insert(strPath.Length() - 4, "Head")
            If File.Exists(strHead) Then
                Dim stream As New FileStream(strHead, FileMode.Open, FileAccess.Read)
                m_ListImage.Add(Image.FromStream(stream))
                stream.Close()
                stream.Dispose()
            End If
        End If


        If CheckBox20.Checked = True And (((nRetSaveimg And 16) = 0) Or (nRetSaveimg = 0)) Then
            Dim strHeadEC As String = strPath.Insert(strPath.Length() - 4, "HeadEC")
            'm_ListImage.Add(Image.FromFile(strHeadEC))
            If File.Exists(strHeadEC) Then
                Dim stream As New FileStream(strHeadEC, FileMode.Open, FileAccess.Read)
                m_ListImage.Add(Image.FromStream(stream))
                stream.Close()
                stream.Dispose()

            End If
        End If


        If m_ListImage.Count > 1 Then
            Button_Pre.Enabled = True
            Button_Next.Enabled = True
        Else
            Button_Pre.Enabled = False
            Button_Next.Enabled = False
        End If

    End Sub

    Private Sub Button_Next_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Next.Click
        m_nImageIndex = m_nImageIndex + 1
        If m_nImageIndex > m_ListImage.Count - 1 Then
            m_nImageIndex = 0
        End If
        PictureBox_Image.Image = m_ListImage(m_nImageIndex)
    End Sub

    Private Sub Button_Pre_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button_Pre.Click
        m_nImageIndex = m_nImageIndex - 1
        If m_nImageIndex < 0 Then
            m_nImageIndex = m_ListImage.Count - 1
        End If
        PictureBox_Image.Image = m_ListImage(m_nImageIndex)
    End Sub

    '
    Private Sub BtnGetVersion_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "Please successful loading recognition engine"
            Exit Sub
        End If
        Dim MAX_CH_NUM As Integer = 50
        Dim strTmp As String
        strTmp = New String(CChar(""), 50)
        Dim a As Byte()
        a = System.Text.Encoding.Unicode.GetBytes(strTmp)
        GetVersionInfo(a(0), MAX_CH_NUM)
        TextBox_SDKVersion.Text = System.Text.Encoding.Unicode.GetString(a)
    End Sub

    '获取当前连接的设备名称
    Private Sub BtnGetDeviceName_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnGetDeviceName.Click
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "Please successful loading recognition engine"
            Exit Sub
        End If
        Dim MAX_CH_NUM As Long = 128
        Dim bRet As Boolean
        Dim strTmp As String
        strTmp = New String(CChar(""), 128)
        Dim a As Byte()
        a = System.Text.Encoding.Unicode.GetBytes(strTmp)
        bRet = GetCurrentDevice(a(0), MAX_CH_NUM)
        If bRet = True Then
            TextBox_DeviceName.Text = System.Text.Encoding.Unicode.GetString(a)
        End If
    End Sub

    '检测设备是否在线
    Private Sub BtnCheckDeviceOnLine_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnCheckDeviceOnLine.Click
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "Please successful loading recognition engine"
            Exit Sub
        End If
        Dim bRet As Boolean
        bRet = CheckDeviceOnline()
        If bRet = True Then
            TextBox_DeviceStatus.Text = "The device is online."
        Else
            TextBox_DeviceStatus.Text = "The device is not online."
        End If
    End Sub


    Private Sub Form1_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles Me.FormClosing
        FreeIDCard()
        ClosePort(sender, e)
    End Sub

    Private Sub Timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Timer1.Tick
        If m_bIsInitSuccess = True Then
            If (DetectDocument <> 1) Then
            Else
                ClassiferAndRecognize()
            End If
        End If

    End Sub

    Function GetCheckBoxValueByGroup(ByVal c As GroupBox) As Integer
        Dim tp As Type = GetType(CheckBox)
        Dim ck As CheckBox
        Dim value As Integer
        For Each ctr As Control In c.Controls
            If ctr.GetType Is tp Then
                ck = CType(ctr, CheckBox)
                If ck.Checked Then
                    value += (1 << (Int32.Parse(ck.Tag.ToString)))
                End If
            End If
        Next
        GetCheckBoxValueByGroup = value
    End Function

    Sub GetDGContent(ByVal nDG As Integer, ByVal bRawData As Boolean)
        Dim nRet As Integer
        Dim a(42000) As Byte
        Dim b(128) As Byte
        Dim nIndex As Integer = 1

        Dim nLen As Integer = 42000
        Dim MAX_CH_NUM As Integer = 128

        TextBoxDG.Text = "Success to read the card" & vbCrLf
        Do While (1)
            nRet = GetFieldNameEx(0, nIndex, b(0), MAX_CH_NUM)
            nRet = GetRecogResultEx(0, nIndex, a(0), nLen)
            If nRet = 3 Then
                Exit Do
            End If

            If nRet = 0 Then
                TextBoxDG.Text += System.Text.Encoding.Unicode.GetString(b)
                TextBoxDG.Text += ":"
                TextBoxDG.Text += System.Text.Encoding.Unicode.GetString(a)
                TextBoxDG.Text += vbCrLf

                MAX_CH_NUM = 128
                nLen = 42000
                ReDim a(42000)
                ReDim b(128)
            End If
            nIndex += 1
        Loop
    End Sub

    Private Sub GetContent()
        ResultTextBox.Text += "Success to read the card" & vbCrLf
        Dim MAX_CH_NUM As Integer = 128
        Dim strResult As String
        Dim strName As String
        Dim a As Byte()
        Dim b As Byte()
        Dim strResultTmp As String
        Dim strNameTmp1 As String
        strName = New String(CChar(""), 128)
        strResult = New String(CChar(""), 128)
        Dim nIndex As Integer = 1
        ResultTextBox.Text = "recognition successful" & vbCrLf

        Do While (1)
            strResultTmp = ""
            strNameTmp1 = ""
            b = System.Text.Encoding.Unicode.GetBytes(strResult)
            Dim nRet As Integer
            MAX_CH_NUM = 256
            nRet = GetRecogResultEx(1, nIndex, b(0), MAX_CH_NUM)
            strResultTmp = System.Text.Encoding.Unicode.GetString(b) & vbCrLf
            If nRet = 3 Then
                Exit Do
            End If

            Dim nnRet As Integer
            MAX_CH_NUM = 256
            a = System.Text.Encoding.Unicode.GetBytes(strName)
            nnRet = GetFieldNameEx(1, nIndex, a(0), MAX_CH_NUM)
            strNameTmp1 = System.Text.Encoding.Unicode.GetString(a) & ":"
            '  
            If nnRet = 0 Then
                ResultTextBox.Text += strNameTmp1
                ResultTextBox.Text += ":"
                ResultTextBox.Text += strResultTmp
                ResultTextBox.Text += vbCrLf

            End If
            nIndex += 1
        Loop
    End Sub

    Private Sub ClassiferAndRecognize()

        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "Please successful loading recognition engine"
            Exit Sub
        End If


        Dim nRet As Integer
        Dim nDG As Integer
        Dim nSaveImage As Integer
        Dim bVIZ As Boolean

        nDG = GetCheckBoxValueByGroup(Me.GroupBox5)
        nSaveImage = GetCheckBoxValueByGroup(Me.GroupBox6)
        bVIZ = Me.RadioButton1.Checked

        SetRecogDG(nDG)
        SetSaveImageType(nSaveImage)
        SetRecogVIZ(bVIZ)

        Dim nCardType As Integer
        nCardType = 0
        nRet = AutoProcessIDCard(nCardType)
        If nRet > 0 Then

            GetContent()
            If nCardType = 1 Then
                TextBoxDG.Clear()
                GetDGContent(nDG, True)
            Else
                TextBoxDG.Text = "not any DG info"
            End If

            If nCardType = 1 Or nCardType = 2 Then
                PictureBox_Image.Visible = True
            Else
                PictureBox_Image.Visible = False
            End If
        Else
            ResultTextBox.Text = "Return Value:"
            ResultTextBox.Text += nRet.ToString()
            ResultTextBox.Text += vbCrLf
            ResultTextBox.Text += "fail to read the card"
            ResultTextBox.Text += vbCrLf
            TextBoxDG.Text = ""
            PictureBox_Image.Visible = False
            Exit Sub
        End If

        Dim strRunPath As String = Application.StartupPath + "\"
        Dim strImgPath As String = TextBox_ImagePath.Text + "\"
        Dim strSrcImg As String

        If strImgPath = "\" Then
            strSrcImg = strRunPath + "EPRSampleDemo.jpg"
        Else
            strSrcImg = strImgPath + "EPRSampleDemo.jpg"
        End If


        Dim szFilename As Byte()
        szFilename = System.Text.Encoding.Unicode.GetBytes(strSrcImg)
        nRet = SaveImageEx(szFilename(0), nSaveImage)
        nRetSaveimg = -nRet
        SaveImagePath(strSrcImg, nSaveImage)
        If m_ListImage.Count > 0 Then
            PictureBox_Image.Image = m_ListImage(0)
        End If

    End Sub

    Private Sub BtnGetDeviceSN_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnGetDeviceSN.Click
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "Please successful loading recognition engine"
            Exit Sub
        End If
        Dim MAX_CH_NUM As Long = 50
        Dim strTmp As String
        strTmp = New String(CChar(""), 50)
        Dim a As Byte()
        a = System.Text.Encoding.Unicode.GetBytes(strTmp)
        Dim nRet As Integer

        nRet = GetDeviceSN(a(0), 16)
        If nRet = 0 Then
            TextBox_SerialNumber.Text = System.Text.Encoding.Unicode.GetString(a)
        Else
            TextBox_SerialNumber.Text = "Failed to get Device Sequence"
        End If

    End Sub

    Sub AscllToInt(ByRef n As Integer, ByVal nVal As Integer)
        n = 0
        If nVal + 48 >= 48 And nVal + 48 <= 57 Then
            n = nVal + 48
        End If

        If nVal + 55 >= 65 And nVal + 55 <= 70 Then
            n = nVal + 55
        End If
    End Sub
    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles BtnGetDeviceRFIDSN.Click
        If m_bIsInitSuccess = False Then
            TextBox_RFID_SerialNumber.Text = "Please successful loading recognition engine"
            Exit Sub
        End If

        Dim nRet As Long
        Dim pRAPDUStr(1000) As Byte
        nRet = SDT_GetSAMIDToStr(1001, pRAPDUStr, 0)
        If nRet = &H90 Then
            TextBox_RFID_SerialNumber.Text = System.Text.UTF8Encoding.UTF8.GetString(pRAPDUStr)
        Else
            TextBox_RFID_SerialNumber.Text = "Failed to get Device Sequence\r\n"
        End If
        'StrHex获取16进制序列号*****************************************************************************
        Dim nHex As Integer = 0
        Dim nVal As Integer = 0
        Dim szHexBuf(64) As Byte
        Dim sHexBufSrc(129) As Byte
        nRet = SDT_GetSAMID(1001, szHexBuf, 0)
        If nRet = &H90 Then
            Dim i As Integer = 0
            For j = 0 To szHexBuf.Length - 1

                nHex = szHexBuf(j) / 16
                AscllToInt(nVal, nHex)
                sHexBufSrc(i) = nVal
                i += 1
                AscllToInt(nVal, szHexBuf(j) Mod 16)
                sHexBufSrc(i) = nVal
                i += 1
            Next j

            Dim StrHex As String = System.Text.Encoding.ASCII.GetString(sHexBufSrc)
            For k = StrHex.Length - 1 To 0 Step -1

                If StrHex(k) = "0" Or StrHex(k) = "\0" Then
                    StrHex = Mid(StrHex, 1, Len(StrHex) - 1)
                Else
                    Exit For
                End If

            Next k
        End If

    End Sub

    Public Sub GetName(ByRef str As String)
        If puiCHMsgLen > 0 Then
            If System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = " " Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 0, 30)
            ElseIf System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = "I" Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 0, 120)
            Else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 0, 30)
            End If
        End If
    End Sub

    Private Sub GetSex(ByRef str As String)
        If puiCHMsgLen > 0 Then
            If System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = " " Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 30, 2)
            ElseIf System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = "I" Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 120, 2)
            Else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 30, 2)
            End If
        End If

        If str = "1" Then
            str = "男"
        Else
            str = "女"
        End If

    End Sub

    Private Sub GetPeopleChineseName(ByRef str As String)
        If puiCHMsgLen > 0 Then
            If System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = "I" Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 158, 30)
            End If
        End If
    End Sub

    Private Sub GetPeople(ByRef str As String)
        If puiCHMsgLen > 0 Then
            If System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = " " Then
                Dim people(2) As Byte
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 32, 4)

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
            Else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 152, 6)
            End If
        End If
    End Sub

    Private Sub GetCardVersion(ByRef str As String)

        If puiCHMsgLen > 0 Then
            If System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = "I" Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 236, 4)
            End If
        End If
    End Sub

    Private Sub GetBirthday(ByRef str As String)

        If puiCHMsgLen > 0 Then
            If System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = "I" Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 220, 16)
            Else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 36, 16)
            End If

        End If
    End Sub

    Private Sub GetAddress(ByRef str As String)
        If puiCHMsgLen > 0 Then
            str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 52, 70)
        End If
    End Sub

    Private Sub GetIDCode(ByRef str As String)
        If puiCHMsgLen > 0 Then
            If System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = " " Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 122, 36)
            ElseIf System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = "I" Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 122, 30)
            Else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 122, 36)
            End If
        End If
    End Sub

    Private Sub GetReverse(ByRef str As String, ByVal nPosition As Integer, ByVal nVal As Integer)
        If puiCHMsgLen > 0 Then
            str = System.Text.Encoding.Unicode.GetString(pucCHMsg, nPosition, nVal)
        End If
    End Sub

    Private Sub GetAuthority(ByRef str As String)
        If puiCHMsgLen > 0 Then
            If System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) = "I" Then
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 240, 8)
            Else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 158, 30)
            End If
        End If
    End Sub

    Sub GetIssueDay(ByRef str As String)
        If puiCHMsgLen > 0 Then
            str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 188, 16)
        End If

    End Sub

    Private Sub GetFingerprintInfo(ByRef str As String)
        If puiPHMsgLen > 0 Then
            str = "有"
        Else
            str = "无"
        End If

    End Sub

    Private Sub GetPassNum(ByRef str As String)
        If puiCHMsgLen > 0 Then
            str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 220, 18)
        End If
    End Sub

    Private Sub GetIssueNum(ByRef str As String)
        If puiCHMsgLen > 0 Then
            str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 238, 4)
        End If
    End Sub

    Private Sub GetExpityDay(ByRef str As String)
        If puiCHMsgLen > 0 Then
            str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 204, 16)
        End If
    End Sub

    Private Sub ShowCHMsg_SID()
        '显示二代证基本信息
        ResultTextBox.Text += "证件名称：二代证" & vbCrLf
        GetName(str)
        ResultTextBox.Text += "姓名:" & " " & str & vbCrLf
        GetSex(str)
        ResultTextBox.Text += "性别:" & " " & str & vbCrLf
        GetPeople(str)
        ResultTextBox.Text += "民族:" & " " & str & vbCrLf
        GetBirthday(str)
        ResultTextBox.Text += "出生日期:" & " " & str & vbCrLf
        GetAddress(str)
        ResultTextBox.Text += "住址:" & " " & str & vbCrLf
        GetIDCode(str)
        ResultTextBox.Text += "公民身份证号码:" & str & vbCrLf
        GetAuthority(str)
        ResultTextBox.Text += "签发机关:" & " " & str & vbCrLf
        GetIssueDay(str)
        ResultTextBox.Text += "有效期起始日期:" & " " & str & vbCrLf
        GetExpityDay(str)
        ResultTextBox.Text += "有效期终止日期:" & " " & str & vbCrLf
        GetFingerprintInfo(str)
        ResultTextBox.Text += "指纹信息:" & " " & str & vbCrLf

    End Sub

    Private Sub ShowCHMsg_Prp()
        '显示外国人永久居住证基本信息
        ResultTextBox.Text += "证件名称：外国人永久居留证" & vbCrLf
        GetName(str)
        ResultTextBox.Text += "姓名:" & " " & str & vbCrLf
        GetSex(str)
        ResultTextBox.Text += "性别:" & " " & str & vbCrLf
        GetIDCode(str)
        ResultTextBox.Text += "永久居留证号码:" & str & vbCrLf
        GetPeople(str)
        ResultTextBox.Text += "国籍或所在地区代码:" & " " & str & vbCrLf
        GetPeopleChineseName(str)
        ResultTextBox.Text += "中文姓名:" & " " & str & vbCrLf
        GetIssueDay(str)
        ResultTextBox.Text += "有效期起始日期:" & " " & str & vbCrLf
        GetExpityDay(str)
        ResultTextBox.Text += "有效期终止日期:" & " " & str & vbCrLf
        GetBirthday(str)
        ResultTextBox.Text += "出生日期:" & " " & str & vbCrLf
        GetCardVersion(str)
        ResultTextBox.Text += "证件版本号:" & " " & str & vbCrLf
        GetAuthority(str)
        ResultTextBox.Text += "当次申请受理机关代码:" & " " & str & vbCrLf
        ResultTextBox.Text += "证件类型标识:" & " " & "I" & vbCrLf
        GetReverse(str, 250, 6)
        ResultTextBox.Text += "预留项:" & " " & str & vbCrLf

    End Sub

    Private Sub ShowCHMsg_Rrp()
        '显示港澳台居民居住证文字信息到界面
        ResultTextBox.Text += "证件名称：港澳台居民居住证" & vbCrLf
        GetName(str)
        ResultTextBox.Text += "姓名:" & " " & str & vbCrLf
        GetSex(str)
        ResultTextBox.Text += "性别:" & " " & str & vbCrLf
        GetReverse(str, 32, 4)
        ResultTextBox.Text += "预留项:" & " " & str & vbCrLf
        GetBirthday(str)
        ResultTextBox.Text += "出生日期:" & " " & str & vbCrLf
        GetAddress(str)
        ResultTextBox.Text += "住址:" & " " & str & vbCrLf
        GetPeople(str)
        ResultTextBox.Text += "民族:" & " " & str & vbCrLf
        GetIDCode(str)
        ResultTextBox.Text += "公民身份证号码:" & str & vbCrLf
        GetAuthority(str)
        ResultTextBox.Text += "签发机关:" & " " & str & vbCrLf
        GetIssueDay(str)
        ResultTextBox.Text += "有效期起始日期:" & " " & str & vbCrLf
        GetExpityDay(str)
        ResultTextBox.Text += "有效期终止日期:" & " " & str & vbCrLf
        GetPassNum(str)
        ResultTextBox.Text += "通行证号码:" & " " & str & vbCrLf
        GetIssueNum(str)
        ResultTextBox.Text += "签发次数:" & " " & str & vbCrLf
        GetReverse(str, 242, 6)
        ResultTextBox.Text += "预留项:" & " " & str & vbCrLf
        ResultTextBox.Text += "证件类型标识:" & " " & "J" & vbCrLf
        GetReverse(str, 250, 6)
        ResultTextBox.Text += "预留项:" & " " & str & vbCrLf
        GetFingerprintInfo(str)
        ResultTextBox.Text += "指纹信息:" & " " & str & vbCrLf
    End Sub

    Private Sub SavePhoto(ByRef filename As String, ByVal nType As Integer)

        filename += "\head.wlt"
        My.Computer.FileSystem.WriteAllBytes(filename, pucPHMsg, True)

        Dim file(filename.Length()) As Byte
        file = System.Text.Encoding.Default.GetBytes(filename)
        GetBmp(file(0), 2)

    End Sub

    Private Sub ReadSIDCard() Handles btnRecogSIDCard.Click

        '寻找卡
        Dim nRet As Integer
        Dim pRAPDU(8) As Byte '//卡片输出 
        nRet = SDT_ReadNewAppMsg(m_nOpenPort, pucCHMsg, puiCHMsgLen, 0)
        If nRet = &H90 Or nRet = &H91 Then
            MsgBox("此卡已读过，请重新放证！")
            Exit Sub
        End If
        nRet = SDT_StartFindIDCard(m_nOpenPort, pRAPDU, 0)
        If nRet <> &H9F Then
            MsgBox("寻找卡失败")
            Exit Sub
        End If

        '选卡
        nRet = SDT_SelectIDCard(m_nOpenPort, pRAPDU, 0)
        If nRet <> &H90 Then
            MsgBox("选择身份证失败")
            Exit Sub
        End If

        '读取数据到数组        
        nRet = SDT_ReadBaseMsg(m_nOpenPort, pucCHMsg, puiCHMsgLen, pucPHMsg, puiPHMsgLen, 0)
        If nRet <> &H90 Then
            MsgBox("读取数据到数组失败")
            Exit Sub
        End If

        If 0 = puiCHMsgLen Then
            Exit Sub
        Else
            Dim strType As String
            strType = System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2)
            If strType = " " Then
                ShowCHMsg_SID()
            ElseIf strType = "I" Then
                ShowCHMsg_Prp()
            Else
                ShowCHMsg_Rrp()
            End If
        End If



        m_nReadSID = 1
        TextBoxDG.Text = "not any DG info"
        '显示图像
        PictureBox_Image.Visible = True
        str = CurDir() '得到当前路径
        str = TextBox_ImagePath.Text + "\"
        SavePhoto(str, 2)
        str = Mid(str, 1, str.Length() - 4)
        str += ".bmp"
        PictureBox_Image.Load(str)
        Me.Button_Pre.Enabled = False
        Me.Button_Next.Enabled = False


    End Sub

    Private Sub ClosePort(ByVal sender As System.Object, ByVal e As System.EventArgs) 'Handles Button3.Click'
        Dim n As Integer
        If m_NIDapi = True Then
            n = SDT_ClosePort(0)
            If n = &H90 Then
                m_NIDapi = False
            End If
        End If
        End
    End Sub

    Private Sub ImagePath_Click(sender As Object, e As EventArgs) Handles ImagePath.Click
        Me.FolderBrowserDialog1.ShowDialog()
        'If se = DialogResult.OK Then
        TextBox_ImagePath.Clear()
        TextBox_ImagePath.Text = FolderBrowserDialog1.SelectedPath
        'End If
    End Sub

    Private Sub btnConFigFile_Click(sender As Object, e As EventArgs) Handles btnConFigFile.Click
        If OpenFileDialog1.ShowDialog() = DialogResult.OK Then
            TextConfigfile.Clear()
            TextConfigfile.Text = OpenFileDialog1.FileName
        End If
    End Sub

    Private Sub btnChangeScroll_Click(sender As Object, e As EventArgs) Handles RecongSoroll.SelectedIndexChanged
        If Me.RecongSoroll.Text = "Automatic identification" Then
            Dim nConFig As Integer
            Dim strTextConFigPath As String
            Dim strfigByFile As Byte()

            strTextConFigPath = TextConfigfile.Text
            strfigByFile = System.Text.Encoding.Unicode.GetBytes(TextConfigfile.Text)
            If strTextConFigPath <> "" Then
                nConFig = SetConfigByFile(strfigByFile(0))
            End If

            ResultTextBox.Clear()
            TextBoxDG.Clear()
            Me.Timer1.Enabled = True
            btnRecogSIDCard.Enabled = False
            btnRecog.Enabled = False
            CardType.Enabled = False
            PictureBox_Image.Visible = False
        End If

        If Me.RecongSoroll.Text = "Manual identification" Then
            ResultTextBox.Clear()
            TextBoxDG.Clear()
            'GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(False);
            Me.Timer1.Enabled = False
            btnRecogSIDCard.Enabled = True
            btnRecog.Enabled = True
            CardType.Enabled = True
            PictureBox_Image.Visible = False
        End If

    End Sub

    Private Sub DGtext_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        RecongSoroll.SelectedIndex = 0
    End Sub
End Class
