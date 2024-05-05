
Option Strict Off
Option Explicit On
Imports System
Imports System.IO
Imports VB = Microsoft.VisualBasic
Public Class Form1

    '声明接口
    '初始化、释放证件核心接口
    Private Declare Function InitIDCard Lib "IDCard.dll" (ByRef lpUserId As Byte, ByVal nType As Integer, ByRef lpDirectory As Byte) As Integer
    Private Declare Sub FreeIDCard Lib "IDCard.dll" ()

    '检测设备是否在线
    Private Declare Function CheckDeviceOnline Lib "IDCard.dll" () As Boolean

    '从采集设备获取图片到内存
    Private Declare Function AcquireImage Lib "IDCard.dll" (ByVal nImageSizeType As Integer) As Integer
    Private Declare Function SetAcquireImageType Lib "IDCard.dll" (ByVal nLightType As Integer, ByVal nImageType As Integer) As Boolean
    Private Declare Function SetUserDefinedImageSize Lib "IDCard.dll" (ByVal nWidth As Integer, ByVal nHeight As Integer) As Boolean
    Private Declare Function SetAcquireImageResolution Lib "IDCard.dll" (ByVal nResolutionX As Integer, ByVal nResolutionY As Integer) As Boolean

    '设置要识别的证件类型
    Private Declare Function ResetIDCardID Lib "IDCard.dll" () As Integer
    Private Declare Function AddIDCardID Lib "IDCard.dll" (ByVal nMainID As Integer, ByVal nSubID() As Integer, ByVal nSubIdCount As Integer) As Integer
    Private Declare Function SetIDCardRejectType Lib "IDCard.dll" (ByVal nMainID As Integer, ByVal bFlag As Boolean) As Integer
    Private Declare Function RecogIDCard Lib "IDCard.dll" () As Integer
    Private Declare Function RecogIDCardEX Lib "IDCard.dll" (ByVal nMainID As Integer, ByVal nSubID As Integer) As Integer
    '获取识别结果
    Private Declare Function GetRecogResult Lib "IDCard.dll" (ByVal nIndex As Integer, ByRef lpBuffer As Byte, ByRef nBufferLen As Integer) As Integer
    Private Declare Function GetFieldName Lib "IDCard.dll" (ByVal nIndex As Integer, ByRef llpBuffe As Byte, ByRef nBufferLen As Integer) As Integer
    Private Declare Function GetIDCardName Lib "IDCard.dll" (ByRef llpBuffe As Byte, ByRef nBufferLen As Integer) As Integer
    Private Declare Function GetSubID Lib "IDCard.dll" () As Integer
    Private Declare Function GetResultType Lib "IDCard.dll" (ByVal nIndex As Integer) As Integer

    '保存图片
    Private Declare Auto Function SaveImage Lib "IDCard.dll" (ByRef lpFileName As Byte) As Integer
    Private Declare Auto Function SaveHeadImage Lib "IDCard.dll" (ByRef lpFileName As Byte) As Integer


    '名片
    Private Declare Function RecogBusinessCard Lib "IDCard.dll" (ByVal nIndex As Integer) As Integer
    Private Declare Function GetBusinessCardResult Lib "IDCard.dll" (ByVal nID As Integer, ByVal nIndex As Integer, ByRef lpBuffer As Byte, ByRef nBufferLen As Integer) As Integer
    Private Declare Function GetBusinessCardFieldName Lib "IDCard.dll" (ByVal nID As Integer, ByRef llpBuffe As Byte, ByRef nBufferLen As Integer) As Integer
    Private Declare Function GetBusinessCardResultCount Lib "IDCard.dll" (ByVal nID As Integer) As Integer
    Private Declare Function GetBusinessCardPosition Lib "IDCard.dll" (ByVal nID As Integer, ByVal nIndex As Integer, ByRef nBufferLen As Integer, ByRef nRight As Integer, ByRef nTop As Integer, ByVal nBottom As Integer) As Integer


    '其他接口
    Private Declare Function GetCurrentDevice Lib "IDCard.dll" (ByRef deviceName As Byte, ByVal nBufferLenth As Long) As Boolean
    Private Declare Sub GetVersionInfo Lib "IDCard.dll" (ByRef lpBuffer As Byte, ByVal nBufferLenth As Integer)
    Private Declare Function GetDeviceSN Lib "IDCard.dll" (ByRef deviceName As Byte, ByVal nBufferLenth As Long) As Integer
    Private Declare Function CheckDeviceSI Lib "IDCard.dll" (ByRef lpSI As Byte, ByVal nBufferLenth As Long) As Integer
    Private Declare Function WriteDeviceSI Lib "IDCard.dll" (ByRef lpSI As Byte, ByVal nBufferLenth As Long) As Integer


    Dim m_bIsInitSuccess As Boolean = False

    '加载识别核心
    Private Sub BtnLoadKernal_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnLoadKernal.Click
        If m_bIsInitSuccess = True Then
            ResultTextBox.Text = "识别核心已成功加载"
            Exit Sub
        End If
        Dim nRet As Integer
        Dim strTmp As Byte()
        strTmp = System.Text.Encoding.Unicode.GetBytes(UserID.Text)
        '初始化识别核心
        Dim szTmp As String
        szTmp = New String(CChar(""), 128)
        Dim vbs As Byte()
        vbs = System.Text.Encoding.Unicode.GetBytes(szTmp)
        nRet = InitIDCard(strTmp(0), 1, vbs(0))
        If nRet = 0 Then
            ResultTextBox.Text = "加载识别核心成功"
            m_bIsInitSuccess = True
        Else
            ResultTextBox.Text = "初始化识别核心失败" & Str(nRet)

            m_bIsInitSuccess = False
        End If

        GetDeviceInfo()
    End Sub

    '识别并获取识别结果
    Private Sub BtnRecog_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnRecog.Click
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "未成功加载识别核心，不能进行识别"
            Exit Sub
        End If

        '判断采集图像参数是否正确
        If (Int(Val(TBCardSizeType.Text)) <= 0) Then
            ResultTextBox.Text = "无效的证件尺寸类型"
            Exit Sub
        End If

        '调用图像采集接口获取内存图像
        Dim nRet As Integer
        nRet = AcquireImage(Int(Val(TBCardSizeType.Text)))

        If nRet <> 0 Then
            Dim strRetCode As String
            strRetCode = "返回值:" & Str(nRet) & vbCrLf
            ResultTextBox.Text = strRetCode
            ResultTextBox.Text += "采集图像失败"
        End If

        '2、识别
        '判断识别参数是否正确
        Dim nCardType As Integer
        nCardType = Int(Val(TBCardType.Text))
        If (nCardType <= 0) Then

            ResultTextBox.Text = "无效的证件类型，请重新输入有效的证件类型"
            Exit Sub
        End If


        '调用识别接口进行识别
        'CarTypeID可以表示一种证件，也可以表示多种证件，如1表示一代证，2表示二代证，3表示二代证背面，那么m_nCarTypeID=1表示识别一代证
        If (nCardType = 1010) Then
            Dim MAX_NUM As Integer = 128
            Dim sFieldValue As String
            Dim sFieldName As String
            Dim a1 As Byte()
            Dim b1 As Byte()
            nRet = RecogBusinessCard(1)
            If nRet = 0 Then
                ResultTextBox.Text = "识别成功" & vbCrLf
                sFieldName = New String(CChar(""), 128)
                sFieldValue = New String(CChar(""), 128)
                Dim nID As Integer = 0
                Dim outtype As Integer = 1
                Do While (outtype)
                    If nRet >= 0 Then
                        Dim strTmp As String
                        Dim strTmp1 As String
                        a1 = System.Text.Encoding.Unicode.GetBytes(sFieldName)
                        nRet = GetBusinessCardFieldName(nID, a1(0), MAX_NUM)
                        strTmp = System.Text.Encoding.Unicode.GetString(a1) & vbCrLf
                        Dim nIdex As Integer = 0
                        Dim nCount As Integer
                        nCount = GetBusinessCardResultCount(nID)
                        If nCount = 0 Then
                            ResultTextBox.Text += strTmp
                            ResultTextBox.Text += ":"
                            ResultTextBox.Text += ""
                            ResultTextBox.Text += vbCrLf
                        End If
                        Do While (nIdex < nCount)
                            b1 = System.Text.Encoding.Unicode.GetBytes(sFieldValue)
                            GetBusinessCardResult(nID, nIdex, b1(0), MAX_NUM)
                            strTmp1 = System.Text.Encoding.Unicode.GetString(b1) & ":"
                            ResultTextBox.Text += strTmp
                            ResultTextBox.Text += ":"
                            ResultTextBox.Text += strTmp1
                            ResultTextBox.Text += vbCrLf
                            nIdex += 1
                        Loop
                        '获取识别的字段名称,nIndex对应的字段名称可以查开发文档

                        nID += 1
                    Else
                        outtype = 0

                    End If
                Loop
            End If
            Exit Sub
        End If

        Dim nSubID(1) As Integer
        nSubID(0) = 0
        ResetIDCardID()
        AddIDCardID(nCardType, nSubID, 1)
        '识别接口调用前，设置拒识类型
        SetIDCardRejectType(nCardType, True)
        nRet = RecogIDCard()
        'RecogIDCardEx接口调用
        'nRet = RecogIDCardEx(nCardType, nSubID)

        '3、有需要可以保存采集的图像和证件头像
        '保存采集的图像到本地，此接口调用前必须先调用采集接口fpAcquireImage获取图像
        '无论识别是否成功,都保存图片
        Dim strRunPath As String = Application.StartupPath + "\"
        Dim strSrcImg As String = strRunPath + "IDCardTest.jpg"
        Dim strSavePath As Byte()

        strSavePath = System.Text.Encoding.Unicode.GetBytes(strSrcImg)

        SaveImage(strSavePath(0))

        '  SaveImage(strSrcImg)
        '保存识别获取的头像到本地
        Dim strHeadImg As String = strRunPath
        strHeadImg += "IDCardTest_Head.jpg"
        Dim strSaveHeadPath As Byte()
        strSaveHeadPath = System.Text.Encoding.Unicode.GetBytes(strHeadImg)
        SaveImage(strSaveHeadPath(0))
        Dim nImageRet As Integer = 0
        nImageRet = SaveHeadImage(strSaveHeadPath(0))
        If (nImageRet <> 0) Then
            Dim strErrCode As String
            strErrCode = "返回值：" & Str(nRet) & vbCrLf
            ResultTextBox.Text = strErrCode
            ResultTextBox.Text += "保存头像失败"
        End If

        If (nRet <= 0) Then
            Dim strErrCode As String
            strErrCode = "返回值:" & Str(nRet) & vbCrLf
            ResultTextBox.Text = strErrCode
            ResultTextBox.Text += "识别失败"
            Exit Sub
        End If

        '获取识别结果
        Dim MAX_CH_NUM As Integer = 128
        Dim szFieldValue As String
        Dim szFieldName As String
        Dim szCardName As String
        Dim cTmpName As Byte()
        Dim cTmpValue As Byte()
        Dim cTmpCardName As Byte()

        szFieldName = New String(CChar(""), 128)
        szFieldValue = New String(CChar(""), 128)
        szCardName = New String(CChar(""), 128)
        Dim nIndex As Integer = 1
        ResultTextBox.Text = "识别成功" & vbCrLf
        '识别成功后调用GetIDCardName接口获取证件名
        ResultTextBox.Text += "证件名 :"
        cTmpCardName = System.Text.Encoding.Unicode.GetBytes(szCardName)
        GetIDCardName(cTmpCardName(0), MAX_CH_NUM)
        ResultTextBox.Text += (System.Text.Encoding.Unicode.GetString(cTmpCardName)) & vbCrLf
        '识别成功后调用GetSubID接口获取证件的SubID
        ResultTextBox.Text += "SubID :"
        ResultTextBox.Text += (GetSubID().ToString()) & vbCrLf
        Dim output As Integer = 1

        Do While (output)
            If nRet <> 3 Then
                Dim strResultValue As String
                Dim strResultName As String
                Dim strResultType As String
                cTmpValue = System.Text.Encoding.Unicode.GetBytes(szFieldValue)
                '获取nIndex对应的识别内容
                nRet = GetRecogResult(nIndex, cTmpValue(0), MAX_CH_NUM)
                strResultValue = System.Text.Encoding.Unicode.GetString(cTmpValue) & vbCrLf
                '获取识别字段的类型
                strResultType = GetResultType(nIndex)
                '获取识别的字段名称,nIndex对应的字段名称可以查开发文档
                Dim nnRet As Integer
                cTmpName = System.Text.Encoding.Unicode.GetBytes(szFieldName)
                nnRet = GetFieldName(nIndex, cTmpName(0), MAX_CH_NUM)
                strResultName = System.Text.Encoding.Unicode.GetString(cTmpName) & ":"
                '用于显示 
                If nnRet = 0 Then
                    ResultTextBox.Text += strResultName
                    ResultTextBox.Text += "("
                    ResultTextBox.Text += strResultType
                    ResultTextBox.Text += ")"
                    ResultTextBox.Text += ":"
                    ResultTextBox.Text += strResultValue
                    ResultTextBox.Text += vbCrLf
                End If
                nIndex += 1
            Else
                output = 0

            End If
        Loop

    End Sub

    '卸载识别核心
    Private Sub BtnFreeKernal_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnFreeKernal.Click

        If m_bIsInitSuccess = True Then
            '释放识别核心
            FreeIDCard()
            ResultTextBox.Text = "卸载识别核心完成"
            m_bIsInitSuccess = False
        Else
            ResultTextBox.Text = "识别核心未加载"
        End If
    End Sub

    '自定义图像尺寸
    Private Sub BtnSetImageWH_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnSetImageWH.Click
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "识别核心未加载，请先加载识别核心"
            Exit Sub
        End If
        Dim nImgWidth As Integer
        Dim strWidth As String
        strWidth = TBImageWidth.Text
        nImgWidth = Int(Val(strWidth))
        If strWidth.Length = 0 Then
            ResultTextBox.Text = "请先输入自定义图像的尺寸参数"
            Exit Sub
        End If
        If nImgWidth <= 0 Then
            ResultTextBox.Text = "图像宽度参数不正确，请重新输入"
        End If
        Dim nImgHeight As Integer
        Dim strHeight As String
        strHeight = TBImageHeight.Text
        If strHeight.Length = 0 Then
            ResultTextBox.Text = "请先输入自定义图像的尺寸参数"
            Exit Sub
        End If
        nImgHeight = Int(Val(strHeight))
        If nImgHeight <= 0 Then
            ResultTextBox.Text = "图像高度参数不正确，请重新输入"
        End If
        Dim bRet As Boolean
        bRet = SetUserDefinedImageSize(nImgWidth, nImgHeight)
        If bRet = True Then
            ResultTextBox.Text = "图像尺寸设置成功"
        Else
            ResultTextBox.Text = "图像尺寸设置失败"
        End If
    End Sub
    '图像分辨率设置
    Private Sub BtnSetAcquireImgResolution_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles BtnSetAcquireImgResolution.Click
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "识别核心未加载，请先加载识别核心"
            Exit Sub
        End If
        Dim nResolutionX As Integer
        Dim strResolution As String
        strResolution = TBHoriResolution.Text
        If strResolution.Length = 0 Then
            ResultTextBox.Text = "请先输入自定义图像的分辨率"
            Exit Sub
        End If
        nResolutionX = Int(Val(strResolution))
        If nResolutionX < 0 Then
            ResultTextBox.Text = "图像水平分辨率参数不正确，请重新输入"
        End If
        Dim nResolutionY As Integer
        nResolutionY = nResolutionX

        Dim bRet As Boolean
        bRet = SetAcquireImageResolution(nResolutionX, nResolutionY)
        If bRet = True Then
            ResultTextBox.Text = "分辨率设置成功"
        Else
            ResultTextBox.Text = "分辨率设置失败"
        End If
    End Sub

    '检测设备是否在线
    Private Sub BtnCheckDeviceOnLine_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "识别核心未加载，请先加载识别核心"
            Exit Sub
        End If
        Dim bRet As Boolean
        bRet = CheckDeviceOnline()
        If bRet = True Then
            ResultTextBox.Text = "设备在线"
        Else
            ResultTextBox.Text = "设备不在线"
        End If
    End Sub


    Private Sub Form1_Closing(ByVal sender As Object, ByVal e As System.ComponentModel.CancelEventArgs) Handles Me.FormClosing
        FreeIDCard()
    End Sub

    Private Sub ClassiferAndRecognize()

        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "未成功加载识别核心，不能进行识别"
            Exit Sub
        End If

        '调用图像采集接口获取内存图像
        Dim nRet As Integer
        nRet = AcquireImage(21)

        If nRet <> 0 Then
            Dim strRetCode As String
            strRetCode = "返回值:" & Str(nRet) & vbCrLf
            ResultTextBox.Text = strRetCode
            ResultTextBox.Text += "采集图像失败"
        End If

        '调用识别接口进行识别

        Dim nSubID(1) As Integer
        nSubID(0) = 0

        AddIDCardID(1, nSubID, 1)
        AddIDCardID(2, nSubID, 1)
        AddIDCardID(3, nSubID, 1)
        AddIDCardID(4, nSubID, 1)
        AddIDCardID(5, nSubID, 1)
        AddIDCardID(6, nSubID, 1)
        AddIDCardID(7, nSubID, 1)
        AddIDCardID(9, nSubID, 1)
        AddIDCardID(10, nSubID, 1)
        AddIDCardID(11, nSubID, 1)
        AddIDCardID(12, nSubID, 1)
        AddIDCardID(13, nSubID, 1)
        AddIDCardID(14, nSubID, 1)
        AddIDCardID(15, nSubID, 1)
        AddIDCardID(16, nSubID, 1)
        AddIDCardID(1000, nSubID, 1)
        AddIDCardID(1001, nSubID, 1)
        AddIDCardID(1003, nSubID, 1)
        AddIDCardID(1004, nSubID, 1)
        AddIDCardID(1005, nSubID, 1)
        AddIDCardID(1107, nSubID, 1)
        AddIDCardID(1008, nSubID, 1)
        AddIDCardID(1009, nSubID, 1)
        AddIDCardID(1010, nSubID, 1)

        nRet = RecogIDCard()
        If (nRet <= 0) Then
            Dim strErrCode As String
            strErrCode = "返回值:" & Str(nRet) & vbCrLf
            ResultTextBox.Text = strErrCode
            ResultTextBox.Text += "识别失败"
            Exit Sub
        End If

        '获取识别结果

        Dim MAX_CH_NUM As Integer = 128
        Dim szFieldValue As String
        Dim szFieldName As String
        Dim a As Byte()
        Dim b As Byte()
        szFieldName = New String(CChar(""), 128)
        szFieldValue = New String(CChar(""), 128)
        Dim nIndex As Integer = 1
        ResultTextBox.Text = "识别成功" & vbCrLf
        Do While (1)
            Dim strTmp As String
            Dim strTmp1 As String
            b = System.Text.Encoding.Unicode.GetBytes(szFieldValue)
            '获取nIndex对应的识别内容
            nRet = GetRecogResult(nIndex, b(0), MAX_CH_NUM)
            strTmp = System.Text.Encoding.Unicode.GetString(b) & vbCrLf
            If nRet = 3 Then
                Exit Sub
            End If
            '获取识别的字段名称,nIndex对应的字段名称可以查开发文档
            Dim nnRet As Integer
            a = System.Text.Encoding.Unicode.GetBytes(szFieldName)
            nnRet = GetFieldName(nIndex, a(0), MAX_CH_NUM)
            strTmp1 = System.Text.Encoding.Unicode.GetString(a) & ":"
            '用于显示 
            If nnRet = 0 Then
                ResultTextBox.Text += strTmp1
                ResultTextBox.Text += ":"
                ResultTextBox.Text += strTmp
                ResultTextBox.Text += vbCrLf

            End If
            nIndex += 1
        Loop

        '3、有需要可以保存采集的图像和证件头像
        '保存采集的图像到本地，此接口调用前必须先调用采集接口fpAcquireImage获取图像
        Dim strRunPath As String = Application.StartupPath + "\"
        Dim strSrcImg As String = strRunPath + "IDCardTest.jpg"
        SaveImage(strSrcImg)
        '保存识别获取的头像到本地
        Dim strHeadImg As String = strRunPath
        strHeadImg += "IDCardTest_Head.jpg"
        nRet = SaveHeadImage(strHeadImg)
        If (nRet <> 0) Then
            Dim strErrCode As String
            strErrCode = "返回值：" & Str(nRet) & vbCrLf
            ResultTextBox.Text = strErrCode
            ResultTextBox.Text += "保存头像失败"
            Exit Sub
        End If
    End Sub

    Private Sub BtnGetDeviceSN_Click(ByVal sender As System.Object, ByVal e As System.EventArgs)
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "识别核心未加载，请先加载识别核心"
            Exit Sub
        End If
        Dim MAX_CH_NUM As Long = 50
        Dim strTmp As String
        strTmp = New String(CChar(""), 50)
        Dim a As Byte()
        a = System.Text.Encoding.Unicode.GetBytes(strTmp)
        GetDeviceSN(a(0), 16)
        ResultTextBox.Text = System.Text.Encoding.Unicode.GetString(a)
    End Sub

    Private Sub Button_AcquireImage_Click(sender As Object, e As EventArgs) Handles Button_AcquireImage.Click
        AcquireImage(20)

        Dim nRet As Integer = 0
        Dim strRunPath As String = Application.StartupPath + "\"
        Dim strSrcImg As String = strRunPath + "IDCardTest.jpg"
        Dim strSavePath As Byte()
        strSavePath = System.Text.Encoding.Unicode.GetBytes(strSrcImg)
        SaveImage(strSavePath(0))

        '  SaveImage(strSrcImg)
        '保存识别获取的头像到本地
        Dim strHeadImg As String = strRunPath
        strHeadImg += "IDCardTest_Head.jpg"
        Dim strSaveHeadPath As Byte()
        strSaveHeadPath = System.Text.Encoding.Unicode.GetBytes(strHeadImg)
        SaveImage(strSaveHeadPath(0))
        nRet = SaveHeadImage(strSaveHeadPath(0))
        If (nRet <> 0) Then
            Dim strErrCode As String
            strErrCode = "返回值：" & Str(nRet) & vbCrLf
            ResultTextBox.Text = strErrCode
            ResultTextBox.Text += "保存头像失败"
            Exit Sub
        End If
    End Sub

    Private Sub GetDeviceInfo()
        If m_bIsInitSuccess = False Then
            ResultTextBox.Text = "识别核心未加载，请先加载识别核心"
            Exit Sub
        End If
        '
        Dim bRet As Boolean
        bRet = CheckDeviceOnline()
        If bRet = True Then
            ResultTextBox.Text += "设备工作正常"
        Else
            ResultTextBox.Text += "设备连接异常"
        End If
        '获取开发包版本信息
        Dim nBuffVersionlen As Integer = 50
        Dim strTmpVersion As String
        strTmpVersion = New String(CChar(""), 50)
        Dim strVersion As Byte()
        strVersion = System.Text.Encoding.Unicode.GetBytes(strTmpVersion)
        GetVersionInfo(strVersion(0), nBuffVersionlen)
        Dim strVersionRet As String = System.Text.Encoding.Unicode.GetString(strVersion)
        strVersionRet = strVersionRet.Substring(strVersionRet.LastIndexOf(" "))
        strVersionRet = strVersionRet.Substring(0, strVersionRet.IndexOf(vbNullChar))


        '获取设备名
        Dim nBuffDeviceNamelen As Long = 128
        Dim strTmpDeviceName As String
        strTmpDeviceName = New String(CChar(""), 128)
        Dim strDeviceName As Byte()
        strDeviceName = System.Text.Encoding.Unicode.GetBytes(strTmpDeviceName)
        bRet = GetCurrentDevice(strDeviceName(0), nBuffDeviceNamelen)
        Dim strDeviceNameRet As String = System.Text.Encoding.Unicode.GetString(strDeviceName)
        strDeviceNameRet = strDeviceNameRet.Substring(0, strDeviceNameRet.IndexOf(vbNullChar))

        '获取序列号
        Dim nBuffDeviceSNlen As Long = 50
        Dim strTmpDeviceSN As String
        strTmpDeviceSN = New String(CChar(""), 50)
        Dim strDeviceSN As Byte()
        strDeviceSN = System.Text.Encoding.Unicode.GetBytes(strTmpDeviceSN)
        GetDeviceSN(strDeviceSN(0), 16)
        Dim strDeviceSNRet As String = System.Text.Encoding.Unicode.GetString(strDeviceSN)
        strDeviceSNRet = strDeviceSNRet.Substring(0, strDeviceSNRet.IndexOf(vbNullChar))

        Me.Text = "中安扫描仪测试例_" + strVersionRet + "_" + strDeviceNameRet + "(" + strDeviceSNRet + ")"
    End Sub

End Class
