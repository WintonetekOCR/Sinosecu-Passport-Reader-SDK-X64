<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Me.GroupBox1 = New System.Windows.Forms.GroupBox()
        Me.GroupBox4 = New System.Windows.Forms.GroupBox()
        Me.Button_AcquireImage = New System.Windows.Forms.Button()
        Me.GroupBox7 = New System.Windows.Forms.GroupBox()
        Me.Label12 = New System.Windows.Forms.Label()
        Me.TBHoriResolution = New System.Windows.Forms.TextBox()
        Me.Label8 = New System.Windows.Forms.Label()
        Me.BtnSetAcquireImgResolution = New System.Windows.Forms.Button()
        Me.GroupBox6 = New System.Windows.Forms.GroupBox()
        Me.Label11 = New System.Windows.Forms.Label()
        Me.Label10 = New System.Windows.Forms.Label()
        Me.Label7 = New System.Windows.Forms.Label()
        Me.Label6 = New System.Windows.Forms.Label()
        Me.TBImageHeight = New System.Windows.Forms.TextBox()
        Me.TBImageWidth = New System.Windows.Forms.TextBox()
        Me.BtnSetImageWH = New System.Windows.Forms.Button()
        Me.GroupBox2 = New System.Windows.Forms.GroupBox()
        Me.BtnFreeKernal = New System.Windows.Forms.Button()
        Me.BtnRecog = New System.Windows.Forms.Button()
        Me.Label3 = New System.Windows.Forms.Label()
        Me.Label2 = New System.Windows.Forms.Label()
        Me.TBCardSizeType = New System.Windows.Forms.TextBox()
        Me.TBCardType = New System.Windows.Forms.TextBox()
        Me.BtnLoadKernal = New System.Windows.Forms.Button()
        Me.Label1 = New System.Windows.Forms.Label()
        Me.UserID = New System.Windows.Forms.TextBox()
        Me.GroupBox9 = New System.Windows.Forms.GroupBox()
        Me.TextBox_ResultDescription = New System.Windows.Forms.TextBox()
        Me.ResultTextBox = New System.Windows.Forms.TextBox()
        Me.GroupBox1.SuspendLayout()
        Me.GroupBox4.SuspendLayout()
        Me.GroupBox7.SuspendLayout()
        Me.GroupBox6.SuspendLayout()
        Me.GroupBox2.SuspendLayout()
        Me.GroupBox9.SuspendLayout()
        Me.SuspendLayout()
        '
        'GroupBox1
        '
        Me.GroupBox1.Controls.Add(Me.GroupBox4)
        Me.GroupBox1.Controls.Add(Me.GroupBox2)
        Me.GroupBox1.Location = New System.Drawing.Point(31, 6)
        Me.GroupBox1.Name = "GroupBox1"
        Me.GroupBox1.Size = New System.Drawing.Size(519, 321)
        Me.GroupBox1.TabIndex = 0
        Me.GroupBox1.TabStop = False
        Me.GroupBox1.Text = "操作"
        '
        'GroupBox4
        '
        Me.GroupBox4.Controls.Add(Me.Button_AcquireImage)
        Me.GroupBox4.Controls.Add(Me.GroupBox7)
        Me.GroupBox4.Controls.Add(Me.GroupBox6)
        Me.GroupBox4.Location = New System.Drawing.Point(224, 24)
        Me.GroupBox4.Name = "GroupBox4"
        Me.GroupBox4.Size = New System.Drawing.Size(279, 283)
        Me.GroupBox4.TabIndex = 2
        Me.GroupBox4.TabStop = False
        Me.GroupBox4.Text = "自定义图像采集参数设置"
        '
        'Button_AcquireImage
        '
        Me.Button_AcquireImage.Location = New System.Drawing.Point(82, 241)
        Me.Button_AcquireImage.Name = "Button_AcquireImage"
        Me.Button_AcquireImage.Size = New System.Drawing.Size(110, 28)
        Me.Button_AcquireImage.TabIndex = 13
        Me.Button_AcquireImage.Text = "自定义图像采集"
        Me.Button_AcquireImage.UseVisualStyleBackColor = True
        '
        'GroupBox7
        '
        Me.GroupBox7.Controls.Add(Me.Label12)
        Me.GroupBox7.Controls.Add(Me.TBHoriResolution)
        Me.GroupBox7.Controls.Add(Me.Label8)
        Me.GroupBox7.Controls.Add(Me.BtnSetAcquireImgResolution)
        Me.GroupBox7.Location = New System.Drawing.Point(20, 146)
        Me.GroupBox7.Name = "GroupBox7"
        Me.GroupBox7.Size = New System.Drawing.Size(242, 89)
        Me.GroupBox7.TabIndex = 2
        Me.GroupBox7.TabStop = False
        Me.GroupBox7.Text = "设置分辨率"
        '
        'Label12
        '
        Me.Label12.AutoSize = True
        Me.Label12.Location = New System.Drawing.Point(149, 26)
        Me.Label12.Name = "Label12"
        Me.Label12.Size = New System.Drawing.Size(23, 12)
        Me.Label12.TabIndex = 12
        Me.Label12.Text = "DPI"
        '
        'TBHoriResolution
        '
        Me.TBHoriResolution.Location = New System.Drawing.Point(74, 22)
        Me.TBHoriResolution.Multiline = True
        Me.TBHoriResolution.Name = "TBHoriResolution"
        Me.TBHoriResolution.Size = New System.Drawing.Size(60, 21)
        Me.TBHoriResolution.TabIndex = 9
        Me.TBHoriResolution.Text = "300"
        '
        'Label8
        '
        Me.Label8.AutoSize = True
        Me.Label8.Location = New System.Drawing.Point(6, 26)
        Me.Label8.Name = "Label8"
        Me.Label8.Size = New System.Drawing.Size(65, 12)
        Me.Label8.TabIndex = 7
        Me.Label8.Text = "采集分辨率" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10)
        '
        'BtnSetAcquireImgResolution
        '
        Me.BtnSetAcquireImgResolution.Location = New System.Drawing.Point(62, 49)
        Me.BtnSetAcquireImgResolution.Name = "BtnSetAcquireImgResolution"
        Me.BtnSetAcquireImgResolution.Size = New System.Drawing.Size(110, 28)
        Me.BtnSetAcquireImgResolution.TabIndex = 6
        Me.BtnSetAcquireImgResolution.Text = "设置采集分辨率"
        Me.BtnSetAcquireImgResolution.UseVisualStyleBackColor = True
        '
        'GroupBox6
        '
        Me.GroupBox6.Controls.Add(Me.Label11)
        Me.GroupBox6.Controls.Add(Me.Label10)
        Me.GroupBox6.Controls.Add(Me.Label7)
        Me.GroupBox6.Controls.Add(Me.Label6)
        Me.GroupBox6.Controls.Add(Me.TBImageHeight)
        Me.GroupBox6.Controls.Add(Me.TBImageWidth)
        Me.GroupBox6.Controls.Add(Me.BtnSetImageWH)
        Me.GroupBox6.Location = New System.Drawing.Point(20, 20)
        Me.GroupBox6.Name = "GroupBox6"
        Me.GroupBox6.Size = New System.Drawing.Size(242, 120)
        Me.GroupBox6.TabIndex = 1
        Me.GroupBox6.TabStop = False
        Me.GroupBox6.Text = "设置图像宽高"
        '
        'Label11
        '
        Me.Label11.AutoSize = True
        Me.Label11.Location = New System.Drawing.Point(162, 65)
        Me.Label11.Name = "Label11"
        Me.Label11.Size = New System.Drawing.Size(59, 12)
        Me.Label11.TabIndex = 12
        Me.Label11.Text = "英寸/1000"
        '
        'Label10
        '
        Me.Label10.AutoSize = True
        Me.Label10.Location = New System.Drawing.Point(162, 28)
        Me.Label10.Name = "Label10"
        Me.Label10.Size = New System.Drawing.Size(59, 12)
        Me.Label10.TabIndex = 11
        Me.Label10.Text = "英寸/1000"
        '
        'Label7
        '
        Me.Label7.AutoSize = True
        Me.Label7.Location = New System.Drawing.Point(18, 63)
        Me.Label7.Name = "Label7"
        Me.Label7.Size = New System.Drawing.Size(41, 12)
        Me.Label7.TabIndex = 10
        Me.Label7.Text = "图像高"
        '
        'Label6
        '
        Me.Label6.AutoSize = True
        Me.Label6.Location = New System.Drawing.Point(20, 28)
        Me.Label6.Name = "Label6"
        Me.Label6.Size = New System.Drawing.Size(41, 12)
        Me.Label6.TabIndex = 9
        Me.Label6.Text = "图像宽"
        '
        'TBImageHeight
        '
        Me.TBImageHeight.Location = New System.Drawing.Point(81, 60)
        Me.TBImageHeight.Multiline = True
        Me.TBImageHeight.Name = "TBImageHeight"
        Me.TBImageHeight.Size = New System.Drawing.Size(60, 21)
        Me.TBImageHeight.TabIndex = 8
        Me.TBImageHeight.Text = "0"
        '
        'TBImageWidth
        '
        Me.TBImageWidth.Location = New System.Drawing.Point(81, 24)
        Me.TBImageWidth.Multiline = True
        Me.TBImageWidth.Name = "TBImageWidth"
        Me.TBImageWidth.Size = New System.Drawing.Size(60, 21)
        Me.TBImageWidth.TabIndex = 7
        Me.TBImageWidth.Text = "0"
        '
        'BtnSetImageWH
        '
        Me.BtnSetImageWH.Location = New System.Drawing.Point(62, 87)
        Me.BtnSetImageWH.Name = "BtnSetImageWH"
        Me.BtnSetImageWH.Size = New System.Drawing.Size(110, 28)
        Me.BtnSetImageWH.TabIndex = 6
        Me.BtnSetImageWH.Text = "设置采集尺寸"
        Me.BtnSetImageWH.UseVisualStyleBackColor = True
        '
        'GroupBox2
        '
        Me.GroupBox2.Controls.Add(Me.BtnFreeKernal)
        Me.GroupBox2.Controls.Add(Me.BtnRecog)
        Me.GroupBox2.Controls.Add(Me.Label3)
        Me.GroupBox2.Controls.Add(Me.Label2)
        Me.GroupBox2.Controls.Add(Me.TBCardSizeType)
        Me.GroupBox2.Controls.Add(Me.TBCardType)
        Me.GroupBox2.Controls.Add(Me.BtnLoadKernal)
        Me.GroupBox2.Controls.Add(Me.Label1)
        Me.GroupBox2.Controls.Add(Me.UserID)
        Me.GroupBox2.Location = New System.Drawing.Point(15, 24)
        Me.GroupBox2.Name = "GroupBox2"
        Me.GroupBox2.Size = New System.Drawing.Size(203, 283)
        Me.GroupBox2.TabIndex = 0
        Me.GroupBox2.TabStop = False
        Me.GroupBox2.Text = "识别调用程序"
        '
        'BtnFreeKernal
        '
        Me.BtnFreeKernal.Location = New System.Drawing.Point(46, 237)
        Me.BtnFreeKernal.Name = "BtnFreeKernal"
        Me.BtnFreeKernal.Size = New System.Drawing.Size(110, 28)
        Me.BtnFreeKernal.TabIndex = 8
        Me.BtnFreeKernal.Text = "释放识别核心"
        Me.BtnFreeKernal.UseVisualStyleBackColor = True
        '
        'BtnRecog
        '
        Me.BtnRecog.Location = New System.Drawing.Point(46, 198)
        Me.BtnRecog.Name = "BtnRecog"
        Me.BtnRecog.Size = New System.Drawing.Size(110, 28)
        Me.BtnRecog.TabIndex = 7
        Me.BtnRecog.Text = "采集并识别"
        Me.BtnRecog.UseVisualStyleBackColor = True
        '
        'Label3
        '
        Me.Label3.AutoSize = True
        Me.Label3.Location = New System.Drawing.Point(7, 162)
        Me.Label3.Name = "Label3"
        Me.Label3.Size = New System.Drawing.Size(77, 12)
        Me.Label3.TabIndex = 6
        Me.Label3.Text = "证件尺寸类型" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10)
        '
        'Label2
        '
        Me.Label2.AutoSize = True
        Me.Label2.Location = New System.Drawing.Point(19, 125)
        Me.Label2.Name = "Label2"
        Me.Label2.Size = New System.Drawing.Size(53, 12)
        Me.Label2.TabIndex = 5
        Me.Label2.Text = "证件类型"
        '
        'TBCardSizeType
        '
        Me.TBCardSizeType.Location = New System.Drawing.Point(107, 158)
        Me.TBCardSizeType.Multiline = True
        Me.TBCardSizeType.Name = "TBCardSizeType"
        Me.TBCardSizeType.Size = New System.Drawing.Size(90, 21)
        Me.TBCardSizeType.TabIndex = 4
        Me.TBCardSizeType.Text = "2"
        '
        'TBCardType
        '
        Me.TBCardType.Location = New System.Drawing.Point(107, 119)
        Me.TBCardType.Multiline = True
        Me.TBCardType.Name = "TBCardType"
        Me.TBCardType.Size = New System.Drawing.Size(90, 21)
        Me.TBCardType.TabIndex = 3
        Me.TBCardType.Text = "2"
        '
        'BtnLoadKernal
        '
        Me.BtnLoadKernal.Location = New System.Drawing.Point(42, 69)
        Me.BtnLoadKernal.Name = "BtnLoadKernal"
        Me.BtnLoadKernal.Size = New System.Drawing.Size(110, 28)
        Me.BtnLoadKernal.TabIndex = 2
        Me.BtnLoadKernal.Text = "加载识别核心"
        Me.BtnLoadKernal.UseVisualStyleBackColor = True
        '
        'Label1
        '
        Me.Label1.AutoSize = True
        Me.Label1.Location = New System.Drawing.Point(7, 33)
        Me.Label1.Name = "Label1"
        Me.Label1.Size = New System.Drawing.Size(65, 12)
        Me.Label1.TabIndex = 1
        Me.Label1.Text = "用户设置ID"
        '
        'UserID
        '
        Me.UserID.Location = New System.Drawing.Point(78, 30)
        Me.UserID.Multiline = True
        Me.UserID.Name = "UserID"
        Me.UserID.Size = New System.Drawing.Size(119, 21)
        Me.UserID.TabIndex = 0
        '
        'GroupBox9
        '
        Me.GroupBox9.Controls.Add(Me.TextBox_ResultDescription)
        Me.GroupBox9.Controls.Add(Me.ResultTextBox)
        Me.GroupBox9.Location = New System.Drawing.Point(31, 355)
        Me.GroupBox9.Name = "GroupBox9"
        Me.GroupBox9.Size = New System.Drawing.Size(519, 194)
        Me.GroupBox9.TabIndex = 2
        Me.GroupBox9.TabStop = False
        Me.GroupBox9.Text = "结果"
        '
        'TextBox_ResultDescription
        '
        Me.TextBox_ResultDescription.BackColor = System.Drawing.SystemColors.MenuBar
        Me.TextBox_ResultDescription.Location = New System.Drawing.Point(325, 20)
        Me.TextBox_ResultDescription.Multiline = True
        Me.TextBox_ResultDescription.Name = "TextBox_ResultDescription"
        Me.TextBox_ResultDescription.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.TextBox_ResultDescription.Size = New System.Drawing.Size(178, 162)
        Me.TextBox_ResultDescription.TabIndex = 1
        Me.TextBox_ResultDescription.Text = "获取的字段结果的类型" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "0-读卡获取" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "1-视读区OCR获取" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "2-机读区识别导出" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "3-机读区OCR获取" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10) & "4-视读区识别导出" & Global.Microsoft.VisualBasic.ChrW(13) & Global.Microsoft.VisualBasic.ChrW(10)
        '
        'ResultTextBox
        '
        Me.ResultTextBox.BackColor = System.Drawing.SystemColors.MenuBar
        Me.ResultTextBox.Location = New System.Drawing.Point(15, 20)
        Me.ResultTextBox.Multiline = True
        Me.ResultTextBox.Name = "ResultTextBox"
        Me.ResultTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical
        Me.ResultTextBox.Size = New System.Drawing.Size(288, 162)
        Me.ResultTextBox.TabIndex = 0
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 12.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(590, 566)
        Me.Controls.Add(Me.GroupBox9)
        Me.Controls.Add(Me.GroupBox1)
        Me.Name = "Form1"
        Me.Text = "中安证件识别API调用例程"
        Me.GroupBox1.ResumeLayout(False)
        Me.GroupBox4.ResumeLayout(False)
        Me.GroupBox7.ResumeLayout(False)
        Me.GroupBox7.PerformLayout()
        Me.GroupBox6.ResumeLayout(False)
        Me.GroupBox6.PerformLayout()
        Me.GroupBox2.ResumeLayout(False)
        Me.GroupBox2.PerformLayout()
        Me.GroupBox9.ResumeLayout(False)
        Me.GroupBox9.PerformLayout()
        Me.ResumeLayout(False)

    End Sub
    Friend WithEvents GroupBox1 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox2 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox4 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox7 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox6 As System.Windows.Forms.GroupBox
    Friend WithEvents GroupBox9 As System.Windows.Forms.GroupBox
    Friend WithEvents Label1 As System.Windows.Forms.Label
    Friend WithEvents UserID As System.Windows.Forms.TextBox
    Friend WithEvents BtnFreeKernal As System.Windows.Forms.Button
    Friend WithEvents BtnRecog As System.Windows.Forms.Button
    Friend WithEvents Label3 As System.Windows.Forms.Label
    Friend WithEvents Label2 As System.Windows.Forms.Label
    Friend WithEvents TBCardSizeType As System.Windows.Forms.TextBox
    Friend WithEvents TBCardType As System.Windows.Forms.TextBox
    Friend WithEvents BtnLoadKernal As System.Windows.Forms.Button
    Friend WithEvents TBHoriResolution As System.Windows.Forms.TextBox
    Friend WithEvents Label8 As System.Windows.Forms.Label
    Friend WithEvents BtnSetAcquireImgResolution As System.Windows.Forms.Button
    Friend WithEvents Label7 As System.Windows.Forms.Label
    Friend WithEvents Label6 As System.Windows.Forms.Label
    Friend WithEvents TBImageHeight As System.Windows.Forms.TextBox
    Friend WithEvents TBImageWidth As System.Windows.Forms.TextBox
    Friend WithEvents BtnSetImageWH As System.Windows.Forms.Button
    Friend WithEvents ResultTextBox As System.Windows.Forms.TextBox
    Friend WithEvents Label12 As System.Windows.Forms.Label
    Friend WithEvents Label11 As System.Windows.Forms.Label
    Friend WithEvents Label10 As System.Windows.Forms.Label
    Friend WithEvents Button_AcquireImage As Button
    Friend WithEvents TextBox_ResultDescription As TextBox
End Class
