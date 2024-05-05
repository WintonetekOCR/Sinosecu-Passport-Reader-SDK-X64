namespace CSharpDemo
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.textBox_DllPath = new System.Windows.Forms.TextBox();
            this.label_DllPath = new System.Windows.Forms.Label();
            this.btnFreeKernal = new System.Windows.Forms.Button();
            this.btnScanAndRecog = new System.Windows.Forms.Button();
            this.textBoxScanSize = new System.Windows.Forms.TextBox();
            this.label20 = new System.Windows.Forms.Label();
            this.textBoxCardType = new System.Windows.Forms.TextBox();
            this.textBoxUserID = new System.Windows.Forms.TextBox();
            this.label19 = new System.Windows.Forms.Label();
            this.labelCardType = new System.Windows.Forms.Label();
            this.btnLoadKernal = new System.Windows.Forms.Button();
            this.groupBoxDisplayResult = new System.Windows.Forms.GroupBox();
            this.textBox_ResultDescription = new System.Windows.Forms.TextBox();
            this.textBoxDisplayResult = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnAcquireImage = new System.Windows.Forms.Button();
            this.label8 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxHoriResolution = new System.Windows.Forms.TextBox();
            this.btnSetImageResolution = new System.Windows.Forms.Button();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxImageHeight = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxImageWidth = new System.Windows.Forms.TextBox();
            this.btnSetImageSize = new System.Windows.Forms.Button();
            this.imageList1 = new System.Windows.Forms.ImageList(this.components);
            this.groupBox1.SuspendLayout();
            this.groupBoxDisplayResult.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.textBox_DllPath);
            this.groupBox1.Controls.Add(this.label_DllPath);
            this.groupBox1.Controls.Add(this.btnFreeKernal);
            this.groupBox1.Controls.Add(this.btnScanAndRecog);
            this.groupBox1.Controls.Add(this.textBoxScanSize);
            this.groupBox1.Controls.Add(this.label20);
            this.groupBox1.Controls.Add(this.textBoxCardType);
            this.groupBox1.Controls.Add(this.textBoxUserID);
            this.groupBox1.Controls.Add(this.label19);
            this.groupBox1.Controls.Add(this.labelCardType);
            this.groupBox1.Controls.Add(this.btnLoadKernal);
            this.groupBox1.Location = new System.Drawing.Point(24, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(274, 239);
            this.groupBox1.TabIndex = 1;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "扫描识别流程";
            // 
            // textBox_DllPath
            // 
            this.textBox_DllPath.Location = new System.Drawing.Point(82, 56);
            this.textBox_DllPath.Name = "textBox_DllPath";
            this.textBox_DllPath.Size = new System.Drawing.Size(114, 21);
            this.textBox_DllPath.TabIndex = 11;
            this.textBox_DllPath.Text = "../../../../lib";
            // 
            // label_DllPath
            // 
            this.label_DllPath.AutoSize = true;
            this.label_DllPath.Location = new System.Drawing.Point(16, 59);
            this.label_DllPath.Name = "label_DllPath";
            this.label_DllPath.Size = new System.Drawing.Size(59, 12);
            this.label_DllPath.TabIndex = 10;
            this.label_DllPath.Text = "DllPath：";
            // 
            // btnFreeKernal
            // 
            this.btnFreeKernal.Location = new System.Drawing.Point(115, 88);
            this.btnFreeKernal.Name = "btnFreeKernal";
            this.btnFreeKernal.Size = new System.Drawing.Size(81, 23);
            this.btnFreeKernal.TabIndex = 9;
            this.btnFreeKernal.Text = "释放核心";
            this.btnFreeKernal.UseVisualStyleBackColor = true;
            this.btnFreeKernal.Click += new System.EventHandler(this.btnFreeKernal_Click);
            // 
            // btnScanAndRecog
            // 
            this.btnScanAndRecog.Location = new System.Drawing.Point(66, 189);
            this.btnScanAndRecog.Name = "btnScanAndRecog";
            this.btnScanAndRecog.Size = new System.Drawing.Size(115, 23);
            this.btnScanAndRecog.TabIndex = 8;
            this.btnScanAndRecog.Text = "采集图像并识别";
            this.btnScanAndRecog.UseVisualStyleBackColor = true;
            this.btnScanAndRecog.Click += new System.EventHandler(this.btnScanAndRecog_Click);
            // 
            // textBoxScanSize
            // 
            this.textBoxScanSize.Location = new System.Drawing.Point(78, 150);
            this.textBoxScanSize.Name = "textBoxScanSize";
            this.textBoxScanSize.Size = new System.Drawing.Size(93, 21);
            this.textBoxScanSize.TabIndex = 7;
            this.textBoxScanSize.Text = "2";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(8, 155);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(65, 12);
            this.label20.TabIndex = 6;
            this.label20.Text = "扫描尺寸：";
            // 
            // textBoxCardType
            // 
            this.textBoxCardType.Location = new System.Drawing.Point(79, 120);
            this.textBoxCardType.Name = "textBoxCardType";
            this.textBoxCardType.Size = new System.Drawing.Size(92, 21);
            this.textBoxCardType.TabIndex = 5;
            this.textBoxCardType.Text = "2";
            // 
            // textBoxUserID
            // 
            this.textBoxUserID.Location = new System.Drawing.Point(82, 29);
            this.textBoxUserID.Name = "textBoxUserID";
            this.textBoxUserID.Size = new System.Drawing.Size(114, 21);
            this.textBoxUserID.TabIndex = 4;
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(16, 32);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(53, 12);
            this.label19.TabIndex = 3;
            this.label19.Text = "用户ID：";
            // 
            // labelCardType
            // 
            this.labelCardType.AutoSize = true;
            this.labelCardType.Location = new System.Drawing.Point(9, 125);
            this.labelCardType.Name = "labelCardType";
            this.labelCardType.Size = new System.Drawing.Size(65, 12);
            this.labelCardType.TabIndex = 2;
            this.labelCardType.Text = "证件类型：";
            // 
            // btnLoadKernal
            // 
            this.btnLoadKernal.Location = new System.Drawing.Point(28, 88);
            this.btnLoadKernal.Name = "btnLoadKernal";
            this.btnLoadKernal.Size = new System.Drawing.Size(81, 23);
            this.btnLoadKernal.TabIndex = 0;
            this.btnLoadKernal.Text = "加载核心";
            this.btnLoadKernal.UseVisualStyleBackColor = true;
            this.btnLoadKernal.Click += new System.EventHandler(this.btnLoadKernal_Click);
            // 
            // groupBoxDisplayResult
            // 
            this.groupBoxDisplayResult.Controls.Add(this.textBox_ResultDescription);
            this.groupBoxDisplayResult.Controls.Add(this.textBoxDisplayResult);
            this.groupBoxDisplayResult.Location = new System.Drawing.Point(12, 262);
            this.groupBoxDisplayResult.Name = "groupBoxDisplayResult";
            this.groupBoxDisplayResult.Size = new System.Drawing.Size(600, 297);
            this.groupBoxDisplayResult.TabIndex = 3;
            this.groupBoxDisplayResult.TabStop = false;
            this.groupBoxDisplayResult.Text = "显示结果";
            // 
            // textBox_ResultDescription
            // 
            this.textBox_ResultDescription.Location = new System.Drawing.Point(310, 20);
            this.textBox_ResultDescription.Multiline = true;
            this.textBox_ResultDescription.Name = "textBox_ResultDescription";
            this.textBox_ResultDescription.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBox_ResultDescription.Size = new System.Drawing.Size(284, 271);
            this.textBox_ResultDescription.TabIndex = 12;
            this.textBox_ResultDescription.Text = "字段类型说明\r\n";
            // 
            // textBoxDisplayResult
            // 
            this.textBoxDisplayResult.Location = new System.Drawing.Point(6, 20);
            this.textBoxDisplayResult.Multiline = true;
            this.textBoxDisplayResult.Name = "textBoxDisplayResult";
            this.textBoxDisplayResult.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.textBoxDisplayResult.Size = new System.Drawing.Size(289, 271);
            this.textBoxDisplayResult.TabIndex = 0;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnAcquireImage);
            this.groupBox3.Controls.Add(this.label8);
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.textBoxHoriResolution);
            this.groupBox3.Controls.Add(this.btnSetImageResolution);
            this.groupBox3.Controls.Add(this.label5);
            this.groupBox3.Controls.Add(this.label6);
            this.groupBox3.Controls.Add(this.label3);
            this.groupBox3.Controls.Add(this.textBoxImageHeight);
            this.groupBox3.Controls.Add(this.label4);
            this.groupBox3.Controls.Add(this.textBoxImageWidth);
            this.groupBox3.Controls.Add(this.btnSetImageSize);
            this.groupBox3.Location = new System.Drawing.Point(322, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(290, 239);
            this.groupBox3.TabIndex = 5;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "图像采集设置";
            // 
            // btnAcquireImage
            // 
            this.btnAcquireImage.Location = new System.Drawing.Point(38, 189);
            this.btnAcquireImage.Name = "btnAcquireImage";
            this.btnAcquireImage.Size = new System.Drawing.Size(165, 23);
            this.btnAcquireImage.TabIndex = 10;
            this.btnAcquireImage.Text = "采集自定义图像";
            this.btnAcquireImage.UseVisualStyleBackColor = true;
            this.btnAcquireImage.Click += new System.EventHandler(this.btnAcquireImage_Click);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(180, 125);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(23, 12);
            this.label8.TabIndex = 25;
            this.label8.Text = "DPI";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(5, 125);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(47, 12);
            this.label10.TabIndex = 22;
            this.label10.Text = "分辨率:";
            // 
            // textBoxHoriResolution
            // 
            this.textBoxHoriResolution.Location = new System.Drawing.Point(81, 122);
            this.textBoxHoriResolution.Name = "textBoxHoriResolution";
            this.textBoxHoriResolution.Size = new System.Drawing.Size(66, 21);
            this.textBoxHoriResolution.TabIndex = 21;
            this.textBoxHoriResolution.Text = "300";
            // 
            // btnSetImageResolution
            // 
            this.btnSetImageResolution.Location = new System.Drawing.Point(39, 150);
            this.btnSetImageResolution.Name = "btnSetImageResolution";
            this.btnSetImageResolution.Size = new System.Drawing.Size(164, 20);
            this.btnSetImageResolution.TabIndex = 20;
            this.btnSetImageResolution.Text = "设置自定义采集分辨率";
            this.btnSetImageResolution.UseVisualStyleBackColor = true;
            this.btnSetImageResolution.Click += new System.EventHandler(this.btnSetImageResolution_Click);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(191, 57);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(59, 12);
            this.label5.TabIndex = 19;
            this.label5.Text = "英寸/1000";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(191, 35);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(59, 12);
            this.label6.TabIndex = 18;
            this.label6.Text = "英寸/1000";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(6, 57);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 12);
            this.label3.TabIndex = 17;
            this.label3.Text = "图像高:";
            // 
            // textBoxImageHeight
            // 
            this.textBoxImageHeight.Location = new System.Drawing.Point(65, 54);
            this.textBoxImageHeight.Name = "textBoxImageHeight";
            this.textBoxImageHeight.Size = new System.Drawing.Size(106, 21);
            this.textBoxImageHeight.TabIndex = 16;
            this.textBoxImageHeight.Text = "0";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 30);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 12);
            this.label4.TabIndex = 15;
            this.label4.Text = "图像宽:";
            // 
            // textBoxImageWidth
            // 
            this.textBoxImageWidth.Location = new System.Drawing.Point(65, 27);
            this.textBoxImageWidth.Name = "textBoxImageWidth";
            this.textBoxImageWidth.Size = new System.Drawing.Size(106, 21);
            this.textBoxImageWidth.TabIndex = 14;
            this.textBoxImageWidth.Text = "0";
            // 
            // btnSetImageSize
            // 
            this.btnSetImageSize.Location = new System.Drawing.Point(40, 81);
            this.btnSetImageSize.Name = "btnSetImageSize";
            this.btnSetImageSize.Size = new System.Drawing.Size(163, 20);
            this.btnSetImageSize.TabIndex = 13;
            this.btnSetImageSize.Text = "设置自定义采集尺寸";
            this.btnSetImageSize.UseVisualStyleBackColor = true;
            this.btnSetImageSize.Click += new System.EventHandler(this.btnSetImageSize_Click);
            // 
            // imageList1
            // 
            this.imageList1.ColorDepth = System.Windows.Forms.ColorDepth.Depth8Bit;
            this.imageList1.ImageSize = new System.Drawing.Size(16, 16);
            this.imageList1.TransparentColor = System.Drawing.Color.Transparent;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(625, 571);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBoxDisplayResult);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Wintone ";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBoxDisplayResult.ResumeLayout(false);
            this.groupBoxDisplayResult.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label labelCardType;
        private System.Windows.Forms.Button btnLoadKernal;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox textBoxUserID;
        private System.Windows.Forms.GroupBox groupBoxDisplayResult;
        private System.Windows.Forms.TextBox textBoxDisplayResult;
        private System.Windows.Forms.TextBox textBoxScanSize;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox textBoxCardType;
        private System.Windows.Forms.Button btnScanAndRecog;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox textBoxImageHeight;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxImageWidth;
        private System.Windows.Forms.Button btnSetImageSize;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.TextBox textBoxHoriResolution;
        private System.Windows.Forms.Button btnSetImageResolution;
        private System.Windows.Forms.Button btnFreeKernal;
        private System.Windows.Forms.Button btnAcquireImage;
        private System.Windows.Forms.ImageList imageList1;
        private System.Windows.Forms.TextBox textBox_DllPath;
        private System.Windows.Forms.Label label_DllPath;
        private System.Windows.Forms.TextBox textBox_ResultDescription;
    }
 }

