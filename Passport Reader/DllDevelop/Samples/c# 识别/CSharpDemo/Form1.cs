using System;
using System.Collections.Generic;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

//add manually
using System.Runtime.InteropServices;
using System.IO;

namespace CSharpDemo
{
    public partial class Form1 : Form
    {
        private System.Windows.Forms.Timer t = new System.Windows.Forms.Timer();
        delegate int InitIDCard([MarshalAs(UnmanagedType.LPWStr)] String userID, int nType, [MarshalAs(UnmanagedType.LPWStr)] String lpDirectory);
        delegate int GetFieldNameEx(int nAttribute, int nIndex, [MarshalAs(UnmanagedType.LPWStr)] String ArrBuffer, ref int nBufferLen);
        delegate int GetRecogResultEx(int nAttribute, int nIndex, [MarshalAs(UnmanagedType.LPWStr)] String lpBuffer, ref int nBufferLen);
        delegate int GetCurrentDevice([MarshalAs(UnmanagedType.LPWStr)] String ArrDeviceName, int nLength);
        delegate void GetVersionInfo([MarshalAs(UnmanagedType.LPWStr)] String ArrVersion, int nLength);
        delegate bool CheckDeviceOnline();
        delegate void ResetIDCardID();
        delegate int AddIDCardID(int nMainID, int[] nSubID, int nSubIdCount);
        delegate int DetectDocument();
        delegate void SetRecogDG(int nDG);
        delegate void SetRecogVIZ(bool bRecogVIZ);
        delegate void SetSaveImageType(int nImageType);
        delegate int SetConfigByFile([MarshalAs(UnmanagedType.LPWStr)] String strConfigFile);
        delegate void FreeIDCard();
        delegate int GetDeviceSN([MarshalAs(UnmanagedType.LPWStr)] String ArrSn, int nLength);
        delegate int SaveImageEx([MarshalAs(UnmanagedType.LPWStr)] String lpFileName, int nType);
        delegate int AutoProcessIDCard(ref int nCardType);
        delegate int GetBarcodeCount();
        delegate int GetBarcodeRecogResult(int nIndex, [MarshalAs(UnmanagedType.LPWStr)] String lpBuffer, ref int nBufferLen, [MarshalAs(UnmanagedType.LPWStr)] String resultType, ref int nTypeLenth);
        delegate int RecogBarCode([MarshalAs(UnmanagedType.LPWStr)] String lpBuffer, ref int nLen);
        delegate int RecogCellPhoneBarCode();
        delegate int GetGrabSignalType();

        //delegate int InitIDCardSN([MarshalAs(UnmanagedType.LPWStr)] String userID, int nType, [MarshalAs(UnmanagedType.LPWStr)] String lpDirectory, [MarshalAs(UnmanagedType.LPWStr)] String lpDeviceSN);

        InitIDCard pInitIDCard;
        GetFieldNameEx pGetFieldNameEx;
        GetCurrentDevice pGetCurrentDevice;
        GetVersionInfo pGetVersionInfo;
        CheckDeviceOnline pCheckDeviceOnline;
        ResetIDCardID pResetIDCardID;
        AddIDCardID pAddIDCardID;
        DetectDocument pDetectDocument;
        GetGrabSignalType pGetGrabSignalType;
        SetRecogDG pSetRecogDG;
        SetRecogVIZ pSetRecogVIZ;
        SetConfigByFile pSetConfigByFile;
        GetBarcodeCount pGetBarcodeCount;
        GetBarcodeRecogResult pGetBarcodeRecogResult;
        SetSaveImageType pSetSaveImageType;
        FreeIDCard pFreeIDCard;
        GetDeviceSN pGetDeviceSN;
        SaveImageEx pSaveImageEx;
        AutoProcessIDCard pAutoProcessIDCard;
        GetRecogResultEx pGetRecogResultEx;
        RecogBarCode pRecogBarCode;
        RecogCellPhoneBarCode pRecogCellPhoneBarCode;
        //SID
        delegate int SDT_OpenPort(int iPort);
        //delegate int SDT_OpenPortBySN(int iPort,ref byte pDeviceSN);
        delegate int SDT_ClosePort(int iPort);
        delegate int SDT_StartFindIDCard(int iPort, ref byte pRAPDU, int iIfOpen);
        delegate int SDT_SelectIDCard(int iPort, ref byte pRAPDU, int iIfOpen);
        delegate int SDT_ReadBaseMsg(int iPort, ref byte pucCHMsg, ref int puiCHMsgLen, ref byte pucPHMsg, ref int puiPHMsgLen, int iIfOpen);
        delegate int SDT_ReadNewAppMsg(int iPort, ref byte pucAppMsg, ref int puiAppMsgLen, int iIfOpen);
        delegate int GetBmp(string filename, int nType);
        delegate int SDT_GetSAMIDToStr(int iPortID, ref byte pcSAMIDStr, int iIfOpen);
        delegate int SDT_GetSAMID(int iPortID, ref byte pcSAMID, int iIfOpen);

        SDT_OpenPort pSDT_OpenPort;
        SDT_ClosePort pSDT_ClosePort;
        SDT_StartFindIDCard pSDT_StartFindIDCard;
        SDT_SelectIDCard pSDT_SelectIDCard;
        SDT_ReadBaseMsg pSDT_ReadBaseMsg;
        SDT_ReadNewAppMsg pSDT_ReadNewAppMsg;
        GetBmp pGetBmp;
        SDT_GetSAMIDToStr pSDT_GetSAMIDToStr;
        SDT_GetSAMID pSDT_GetSAMID;
        //SID
        bool m_bLoad = false;                // sdtapi.dll  loaded successfully flag     
        byte[] pucCHMsg = new byte[512];       // text info
        byte[] pucPHMsg = new byte[1024];      // image info
        int puiCHMsgLen = 512;              // text info data length
        int puiPHMsgLen = 1024;             // image info data length
        int m_nOpenPort = 0;                // sid port
        bool m_bSID = false;                 // chinese IDCard
        string m_strLogPath = Application.StartupPath;     // the log path
        bool m_bDevice = false;
        string strDeviceName = "";
        //image
        private IList<Image> m_ListImage = new List<Image>();
        FileStream m_fs;
        StreamWriter m_sw;
        int nReadSucceedCount = 1;
        private System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
        int nSaveimg=1;
        //indicates the idcard.dll is loaded or not
        bool m_bIsIDCardLoaded = false;
        int ncount = 0;
        int m_ImageIndex = 0;
        bool bScroll = false;
        bool bEnd = false;
        public Form1()
        {
            InitializeComponent();
            //System.Windows.Forms.Timer timer = new System.Windows.Forms.Timer();
            timer.Tick += new System.EventHandler(this.AutoClassAndRecognize);
            timer.Enabled = true;
            //initialize the dropdown list
            TextBox_ImagePath.Text = System.Environment.CurrentDirectory;
            ScrollIdent.Items.Insert(0, "automatic identification");
            ScrollIdent.Items.Insert(1, "Manual identification");
            ScrollIdent.SelectedIndex = 0;
            btnFreeBtn.Enabled = false;
            bScroll = false;
            btnCurrDeviceName.Enabled = false;
            btnGetSDKVersion.Enabled = false;
            btnCheckDeviceOnLine.Enabled = false;
            btnGetDeviceSN.Enabled = false;
            btnGetDeviceRFIDSN.Enabled = false;
            if ("automatic identification" == ScrollIdent.Text)
            {
                CardType.Enabled = false;
                recogbutton.Enabled = false;
                button_ReadSIDCard.Enabled = false;
            }
            else if ("Manual identification" == ScrollIdent.Text)
            {
                CardType.Enabled = true;
                recogbutton.Enabled = true;
                button_ReadSIDCard.Enabled = true;
            }
            else
            { };
        }
        public static class MyDll
        {
            [DllImport("Kernel32.dll")]
            public static extern IntPtr LoadLibrary(string path);

            [DllImport("Kernel32.dll")]
            public static extern bool FreeLibrary(IntPtr hModule);

            [DllImport("Kernel32.dll")]
            private static extern IntPtr GetProcAddress(IntPtr hModule, string procName);

            public static Delegate LoadFunction<T>(IntPtr hModule, string functionName)
            {
                IntPtr functionAddress = GetProcAddress(hModule, functionName);
                if (functionAddress.ToInt64() == 0)
                {
                    return null;
                }
                return Marshal.GetDelegateForFunctionPointer(functionAddress, typeof(T));
            }
        }


        public bool LoadDllIDCard()
        {
            string DllPath = TEXTBOX_DLLPATH.Text;
            DllPath += "\\IDCard.dll";

            IntPtr hModule = MyDll.LoadLibrary(@DllPath);
            if (hModule.ToInt64() == 0)
            {
                MessageBox.Show("Load " + DllPath + " failed.");
                return false;
            }

            pInitIDCard = (InitIDCard)MyDll.LoadFunction<InitIDCard>(hModule, "InitIDCard");
            pGetFieldNameEx = (GetFieldNameEx)MyDll.LoadFunction<GetFieldNameEx>(hModule, "GetFieldNameEx");
            pGetCurrentDevice = (GetCurrentDevice)MyDll.LoadFunction<GetCurrentDevice>(hModule, "GetCurrentDevice");
            pGetVersionInfo = (GetVersionInfo)MyDll.LoadFunction<GetVersionInfo>(hModule, "GetVersionInfo");
            pCheckDeviceOnline = (CheckDeviceOnline)MyDll.LoadFunction<CheckDeviceOnline>(hModule, "CheckDeviceOnline");
            pResetIDCardID = (ResetIDCardID)MyDll.LoadFunction<ResetIDCardID>(hModule, "ResetIDCardID");
            pAddIDCardID = (AddIDCardID)MyDll.LoadFunction<AddIDCardID>(hModule, "AddIDCardID");
            pDetectDocument = (DetectDocument)MyDll.LoadFunction<DetectDocument>(hModule, "DetectDocument");
            pGetGrabSignalType = (GetGrabSignalType)MyDll.LoadFunction<GetGrabSignalType>(hModule, "GetGrabSignalType");
            pSetRecogVIZ = (SetRecogVIZ)MyDll.LoadFunction<SetRecogVIZ>(hModule, "SetRecogVIZ");
            pSetConfigByFile = (SetConfigByFile)MyDll.LoadFunction<SetConfigByFile>(hModule, "SetConfigByFile");
            pSetRecogDG = (SetRecogDG)MyDll.LoadFunction<SetRecogDG>(hModule, "SetRecogDG");
            pSetSaveImageType = (SetSaveImageType)MyDll.LoadFunction<SetSaveImageType>(hModule, "SetSaveImageType");
            pGetDeviceSN = (GetDeviceSN)MyDll.LoadFunction<GetDeviceSN>(hModule, "GetDeviceSN");
            pSaveImageEx = (SaveImageEx)MyDll.LoadFunction<SaveImageEx>(hModule, "SaveImageEx");
            pAutoProcessIDCard = (AutoProcessIDCard)MyDll.LoadFunction<AutoProcessIDCard>(hModule, "AutoProcessIDCard");
            pGetBarcodeCount = (GetBarcodeCount)MyDll.LoadFunction<GetBarcodeCount>(hModule, "GetBarcodeCount");
            pGetBarcodeRecogResult = (GetBarcodeRecogResult)MyDll.LoadFunction<GetBarcodeRecogResult>(hModule, "GetBarcodeRecogResult");
            pRecogBarCode = (RecogBarCode)MyDll.LoadFunction<RecogBarCode>(hModule, "RecogBarCode");
            pRecogCellPhoneBarCode = (RecogCellPhoneBarCode)MyDll.LoadFunction<RecogCellPhoneBarCode>(hModule, "RecogCellPhoneBarCode");
            pGetRecogResultEx = (GetRecogResultEx)MyDll.LoadFunction<GetRecogResultEx>(hModule, "GetRecogResultEx");
            pFreeIDCard = (FreeIDCard)MyDll.LoadFunction<FreeIDCard>(hModule, "FreeIDCard");

            if (pInitIDCard == null || pGetCurrentDevice == null || pGetVersionInfo == null || pCheckDeviceOnline == null ||
                pResetIDCardID == null || pAddIDCardID == null || pDetectDocument == null || pGetDeviceSN == null || 
                pSaveImageEx == null || pFreeIDCard == null || pAutoProcessIDCard == null || pGetRecogResultEx == null || 
                pGetFieldNameEx == null || pSetRecogDG == null || pSetSaveImageType == null || pSetRecogVIZ == null ||
                pSetConfigByFile == null || pGetBarcodeCount == null || pGetBarcodeRecogResult == null || pRecogBarCode == null || pRecogCellPhoneBarCode == null || pGetGrabSignalType == null )
            {
                MyDll.FreeLibrary(hModule);
                MessageBox.Show("Export IDCard.dll API failed");
                return false;
            }
            return true;
        }

        //Load Kernel
        private void btnLoadKernal_Click(object sender, EventArgs e)
        {
            //Load Kernel

            char[] arr_UserID = textBoxUserID.Text.ToCharArray();
            string UserID = new string(arr_UserID);
            char[] arr_DllPath = TEXTBOX_DLLPATH.Text.ToCharArray();//dll path

            if (!LoadDllIDCard())
            {
                return;
            }
            int nRet; 
            int nConFig;
            string strTextConFigPath = textConFigPath.Text;
            nRet = pInitIDCard(UserID, 1, TEXTBOX_DLLPATH.Text);//dll directory
            if (nRet != 0)
            {
                switch (nRet)
                {
                    case 1:
                        textBoxDisplayResult.Text = "UserID error.\n";
                        break;
                    case 2:
                        textBoxDisplayResult.Text = "Device initialization failed.\n";
                        break;
                    case 3:
                        textBoxDisplayResult.Text = "Failed to initialize the certificate core.\n";
                        break;
                    case 4:
                        textBoxDisplayResult.Text = "The authorization file was not found.\n";
                        break;
                    case 5:
                        textBoxDisplayResult.Text = "Failed to load template file.\n";
                        break;
                    case 6:
                        textBoxDisplayResult.Text = "Failed to initialize card reader.\n";
                        break;
                    default:
                        break;
                }
                return;
            }
            nConFig = pSetConfigByFile(strTextConFigPath);
            ScrollIdent.Enabled = true;
            btnLoadKernal.Enabled = false;
            btnFreeBtn.Enabled = true;
            btnCurrDeviceName.Enabled = true;
            btnGetSDKVersion.Enabled = true;
            btnCheckDeviceOnLine.Enabled = true;
            btnGetDeviceSN.Enabled = true;
            btnGetDeviceRFIDSN.Enabled = true;
            m_bIsIDCardLoaded = true;
            textBoxDisplayResult.Text = "The recognition engine is loaded successfully.\r\n";

            
            btnGetDeviceSN_Click(sender, e);
            btnCheckDeviceOnLine_Click(sender, e);
            btnCurrDeviceName_Click(sender, e);
            btnGetSDKVersion_Click(sender, e);

            LoadDLL();
            if (m_bLoad)
            {
                textBoxDisplayResult.Text += "The stdapi.dll is loaded successfully.\r\n";
            }
            else
            {
                textBoxDisplayResult.Text += "The stdapi.dll is loaded failed.\r\n";
                return;
            }
            btnGetDeviceRFIDSN_Click(sender, e);
            m_strLogPath = Application.StartupPath  + "\\InterFaceLog.log";

            if ("automatic identification" == ScrollIdent.Text)
            {
                bEnd = false;
                timer.Start();
                CardType.Enabled = false;
                recogbutton.Enabled = false;
                button_ReadSIDCard.Enabled = false;
            }
            else if ("Manual identification" == ScrollIdent.Text)
            {
                CardType.Enabled = true;
                recogbutton.Enabled = true;
                button_ReadSIDCard.Enabled = true;
            }
            else
            { };
            
        }

        //close the application
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (m_bIsIDCardLoaded)
            {
                pFreeIDCard();
                m_bIsIDCardLoaded = false;
            }
        }

        //get SDK version

        private void btnGetSDKVersion_Click(object sender, EventArgs e)
        {
            //make sure the kernel is loaded
            if (!m_bIsIDCardLoaded)
            {
                TEXTBOX_SDKVERSION.Text = "Please successful loading recognition engine";
                return;
            }

            String cArrVersion = new String('\0', 128);
            pGetVersionInfo(cArrVersion, 128);
            TEXTBOX_SDKVERSION.Text = cArrVersion;
        }

        private void GetContent()
        {
            int MAX_CH_NUM = 128;
            int nBufLen = MAX_CH_NUM * sizeof(byte);
            textBoxDisplayResult.Clear();
            textBoxDisplayResult.Text = "Success to read the card\r\n";
            
            for (int i = 0; ; i++)
            {
                String cArrFieldValue = new String('\0', MAX_CH_NUM);
                String cArrFieldName = new String('\0', MAX_CH_NUM);
                int nRet = pGetRecogResultEx(1, i, cArrFieldValue, ref nBufLen);
                if (nRet == 3)
                    break;
                nBufLen = MAX_CH_NUM * sizeof(byte);
                pGetFieldNameEx(1, i, cArrFieldName, ref nBufLen);
                nBufLen = MAX_CH_NUM * sizeof(byte);
                textBoxDisplayResult.AppendText(cArrFieldName);
                textBoxDisplayResult.AppendText(":");
                textBoxDisplayResult.AppendText(cArrFieldValue);
                textBoxDisplayResult.AppendText("\r\n");
            }
        }

        private void GetDGContent()
        {
            textBoxDG.Clear();
            textBoxDG.Text = "Success to read the card\r\n";
            int MAX_CH_NUM = 128;
            int nBufLen = 42000;
            for (int j = 0; ; j++)
            {
                String ArrFieldValue = new String('\0', nBufLen);
                String ArrFieldName = new String('\0', MAX_CH_NUM);

                int nResu = pGetRecogResultEx(0, j, ArrFieldValue, ref nBufLen);
                if (nResu == 3)
                    break;
                nBufLen = MAX_CH_NUM * sizeof(byte);
                pGetFieldNameEx(0, j, ArrFieldName, ref nBufLen);
                textBoxDG.AppendText(ArrFieldName);
                textBoxDG.AppendText(":");
                textBoxDG.AppendText(ArrFieldValue);
                textBoxDG.AppendText("\r\n");
                nBufLen = 42000;
            }
        }

        //Recognize 
        private void btnScanAndRecog_Click(object sender, EventArgs e)
        {
            if (!m_bIsIDCardLoaded)
            {
                textBoxDisplayResult.Text = "Please successful loading recognition engine";
                return;
            }
            btnCheckDeviceOnLine_Click(sender, e);
            if (!m_bDevice)
            {
                return;
            }
            int nRet = 0;
            int nCardType = int.Parse(CardType.Text);
            if (nCardType <= 0)
            {
                textBoxDisplayResult.Text = "Invalid CardSizeType,please re-enter a valid.";
                return;
            }

            int[] nSubID = new int[1];
            nSubID[0] = 0;
            pResetIDCardID();
            nRet = pAddIDCardID(nCardType, nSubID, 1);

            //get param
            int nDG = 0;
            foreach (Control c in groupBox4.Controls)//groupBox4
            {
                if (c is CheckBox)//CheckBox 
                {
                    CheckBox cb = (CheckBox)c;
                    if (cb.Checked)
                        nDG |= (1 << (int.Parse(cb.Tag.ToString())));
                }
            }

            int nSaveImage = 0;
            foreach (Control c in groupBox5.Controls)
            {
                if (c is CheckBox)
                {
                    CheckBox cb = (CheckBox)c;
                    if (cb.Checked)
                        nSaveImage |= int.Parse(cb.Tag.ToString());
                }
            }

            bool bVIZ = radioVIZ.Checked;

            int ncardType = 0;

            pSetRecogDG(nDG);
            pSetSaveImageType(nSaveImage);
            pSetRecogVIZ(bVIZ);

            nRet = pAutoProcessIDCard(ref ncardType);

            if (nRet > 0 || nRet == -8 || nRet == -1115 || nRet == -1117)
            {
                GetContent();
                //show DG info                 
                if (1 == ncardType)
                    GetDGContent();
                else
                    textBoxDG.Text = "no any DG info";
            }
            else
            {
                textBoxDisplayResult.Text = "Return Value:";
                textBoxDisplayResult.Text += nRet.ToString();
                textBoxDisplayResult.Text += "\r\n";
                textBoxDisplayResult.Text += "fail to read the card\r\n";
                textBoxDG.Text = "";
                ((PictureBox)PictureBox_Image).Visible = false;
                return;
            }

            //save Image
            //String strRunPath = System.Windows.Forms.Application.StartupPath + "\\";
            char[] arr_ImagePath = TextBox_ImagePath.Text.ToCharArray();//Image Path
            string strImagePath = new string(arr_ImagePath);
            strImagePath += "\\SampleDemo.jpg";
            if (File.Exists(strImagePath))
            {
                File.Delete(strImagePath);
                string strIR= @strImagePath.Insert(@strImagePath.Length - 4, "IR");
                if (File.Exists(strIR))
                    File.Delete(strIR);
                string strUV = @strImagePath.Insert(@strImagePath.Length - 4, "UV");
                if( File.Exists(strUV))
                   File.Delete(strUV);
                string strhead = @strImagePath.Insert(@strImagePath.Length - 4, "Head");
                if (File.Exists(strhead))
                    File.Delete(strhead);
                string strheadEC = @strImagePath.Insert(@strImagePath.Length - 4, "HeadEC");
                if (File.Exists(strheadEC))
                    File.Delete(strheadEC);


            }
            

            nRet = pSaveImageEx(strImagePath, nSaveImage);
            nSaveimg = -nRet;
            SaveImagePath(sender, e, nSaveImage, strImagePath);

            if (1 == ncardType || 2 == ncardType)
                ShowImage(sender, e);
            else
            {
                textBoxDG.Text = "";
                ((PictureBox)PictureBox_Image).Visible = false;
            }
        }
        //check device

        private void btnCheckDeviceOnLine_Click(object sender, EventArgs e)
        {
            if (!m_bIsIDCardLoaded)
            {
                TEXTBOX_DEVICESTATUS.Text = "Please successful loading recognition engine.";
                return;
            }

            bool bRet = pCheckDeviceOnline();
            if (bRet)
            {
                TEXTBOX_DEVICESTATUS.Text = "The device is online.";
                m_bDevice = true;
            }
            else
            {
                TEXTBOX_DEVICESTATUS.Text = "The device is not offline.";
                m_bDevice = false;
                ncount++;
            }

        }
        //get device name

        private void btnCurrDeviceName_Click(object sender, EventArgs e)
        {
            if (!m_bIsIDCardLoaded)
            {
                TEXTBOX_DEVICENAME.Text = "Please successful loading recognition engine.";
                return;
            }

            String cArrDeviceName = new String('\0', 128);
            pGetCurrentDevice(cArrDeviceName, 128);
            TEXTBOX_DEVICENAME.Text = cArrDeviceName;

            strDeviceName += cArrDeviceName;
        }


        private void AutoClassAndRecognize(object sender, EventArgs e)
        {
            if (!m_bIsIDCardLoaded)
                return;
            if (bEnd)
                return;
            bEnd = true;
            int nRet = 0;
            btnCheckDeviceOnLine_Click(sender, e);
            if (!m_bDevice)
            {
                bEnd = false;
                return;
            }

            nRet = pDetectDocument();
            if(nRet!= 0)
                Console.WriteLine(nRet);
            if (nRet == 1)
            {
                //get param
                int nDG = 0;
                foreach (Control c in groupBox4.Controls)//groupBox4
                {
                    if (c is CheckBox)//CheckBox 
                    {
                        CheckBox cb = (CheckBox)c;
                        if (cb.Checked)
                            nDG |= (1 << (int.Parse(cb.Tag.ToString())));
                    }
                }

                int nSaveImage = 0;
                foreach (Control c in groupBox5.Controls)
                {
                    if (c is CheckBox)
                    {
                        CheckBox cb = (CheckBox)c;
                        if (cb.Checked)
                            nSaveImage |= int.Parse(cb.Tag.ToString());
                    }
                }

                bool bVIZ = radioVIZ.Checked;

                pSetRecogDG(nDG);
                pSetSaveImageType(nSaveImage);
                pSetRecogVIZ(bVIZ);

                int nCardType = 0;
                nRet = pAutoProcessIDCard(ref nCardType);

                if (nRet > 0 || nRet == -8 || nRet == -1115 || nRet == -1117)
                {
                    GetContent();
                    //show DG info                 
                    if (1 == nCardType)
                        GetDGContent();
                    else
                        textBoxDG.Text = "no any DG info";
                }
                else
                {
                    textBoxDisplayResult.Text = "Return Value:";
                    textBoxDisplayResult.Text += nRet.ToString();
                    textBoxDisplayResult.Text += "\r\n";
                    textBoxDisplayResult.Text += "fail to read the card\r\n";
                    textBoxDG.Text = "";
                    ((PictureBox)PictureBox_Image).Visible = false;
                    bEnd = false;
                    return;
                }
                //SaveImage
                string strImagePath = TextBox_ImagePath.Text;
                strImagePath += "\\SampleDemo.jpg";
                nRet = pSaveImageEx(strImagePath, nSaveImage);
                nSaveimg = -nRet;
                SaveImagePath(sender, e, nSaveImage, strImagePath);

                if (1 == nCardType || 2 == nCardType)
                    ShowImage(sender, e);
                else
                {
                    textBoxDG.Text = "";
                    ((PictureBox)PictureBox_Image).Visible = false;
                } 
            }else if (nRet == 3)
            {
                nRet = pRecogCellPhoneBarCode();
                if (nRet > 0)
                {
                    textBoxDisplayResult.Clear();
                    textBoxDisplayResult.Text = "Success to read the card\r\n";
                    int codeNumber = pGetBarcodeCount();
                    for (int i = 0; i < codeNumber; i++)
                    {
                        int MAX_CH_NUM = 512;
                        int nValueLen = MAX_CH_NUM * sizeof(byte);
                        int nTypeLen = MAX_CH_NUM * sizeof(byte);
                        String barcodeValue = new String('\0', MAX_CH_NUM);
                        String barcodeType = new String('\0', MAX_CH_NUM);

                        int rRet = pGetBarcodeRecogResult(i, barcodeValue, ref nValueLen, barcodeType, ref nTypeLen);
                        string type = barcodeType.Replace("\0", "");
                        string vlaue = barcodeValue.Replace("\0", "");
                        textBoxDisplayResult.AppendText(type);
                        
                        textBoxDisplayResult.AppendText(vlaue);
                        textBoxDisplayResult.AppendText("\r\n");

                    }
                }
            }
            bEnd = false;
        }

        private void btnGetDeviceSN_Click(object sender, EventArgs e)
        {
            if (!m_bIsIDCardLoaded)
            {
                TEXTBOX_SERIALNUMBER.Text = "Please successful loading recognition engine.！";
                return;
            }
            String cArrSN = new String('\0', 16);
            int nRet = pGetDeviceSN(cArrSN, 16);
            if (nRet == 0)
                TEXTBOX_SERIALNUMBER.Text = cArrSN;
            else
                TEXTBOX_SERIALNUMBER.Text = "Failed to get Device Sequence";
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            groupBox7.Left = this.Width / 2 - groupBox7.Width / 2;

            groupBoxDisplayResult.Top = groupBox7.Top + groupBox7.Height;
            groupBoxDisplayResult.Left = this.Width / 2 - groupBoxDisplayResult.Width / 2;
        }

        private void btnFreeBtn_Click(object sender, EventArgs e)
        {
            bEnd = true;
            timer.Stop();
            if (m_bIsIDCardLoaded)
            {
                TEXTBOX_DEVICENAME.Clear();
                TEXTBOX_SDKVERSION.Clear();
                TEXTBOX_DEVICESTATUS.Clear();
                TEXTBOX_SERIALNUMBER.Clear();
                TEXTBOX_RFUD_SERIALNUMBER.Clear();
                btnCurrDeviceName.Enabled = false;
                btnGetSDKVersion.Enabled = false;
                btnCheckDeviceOnLine.Enabled = false;
                btnGetDeviceSN.Enabled = false;
                btnGetDeviceRFIDSN.Enabled = false;
                ScrollIdent.Enabled = false;
                m_bIsIDCardLoaded = false;
                textBoxDisplayResult.Text = "Free Kernel Successful";
                textBoxDG.Text = "";
                ((PictureBox)PictureBox_Image).Visible = false;
                btnFreeBtn.Enabled = false;
                CardType.Enabled = false;
                recogbutton.Enabled = false;
                button_ReadSIDCard.Enabled = false;
                btnLoadKernal.Enabled = true;
                ScrollIdent.SelectedIndex = 0;
                pFreeIDCard();
            }
        }

        //Save ImagePath
        private void SaveImagePath(object sender, EventArgs e, int nType, string strPath)
        {
            imageList1.Images.Clear();
            if ((nType & 1) == 1 &&(nSaveimg==0 || (nSaveimg & 1)!=1))
            {
                if (System.IO.File.Exists(@strPath))
                {
                    FileStream fileStream = new FileStream(@strPath, FileMode.Open, FileAccess.Read);
                    imageList1.Images.Add(Image.FromStream(fileStream)); //ting
                    fileStream.Close();
                    fileStream.Dispose();
                }
            }
            if ((nType & 2) == 2 && (nSaveimg == 0 || (nSaveimg & 2) != 2))
            {
                string strIR = @strPath.Insert(@strPath.Length - 4, "IR");
                if (System.IO.File.Exists(strIR))
                {
                    FileStream fileStream = new FileStream(@strIR, FileMode.Open, FileAccess.Read);
                    imageList1.Images.Add(Image.FromStream(fileStream)); //ting
                    fileStream.Close();
                    fileStream.Dispose();
                }
            }
            if ((nType & 4) == 4 && (nSaveimg == 0 || (nSaveimg & 4) != 4))
            {
                string strUV = @strPath.Insert(@strPath.Length - 4, "UV");
                if (System.IO.File.Exists(strUV))
                {
                    FileStream fileStream = new FileStream(@strUV, FileMode.Open, FileAccess.Read);
                    imageList1.Images.Add(Image.FromStream(fileStream)); //ting
                    fileStream.Close();
                    fileStream.Dispose();
                }
            }
            if ((nType & 8) == 8 && (nSaveimg == 0 || (nSaveimg & 8) != 8))
            {
                string strHead = strPath.Insert(strPath.Length - 4, "Head");
                if (System.IO.File.Exists(strHead))
                {
                    FileStream fileStream = new FileStream(@strHead, FileMode.Open, FileAccess.Read);
                    imageList1.Images.Add(Image.FromStream(fileStream)); //ting
                    fileStream.Close();
                    fileStream.Dispose();
                }
            }
            if ((nType & 16) == 16 && (nSaveimg == 0 || (nSaveimg & 16) != 16))
            {
                string strHeadEC = strPath.Insert(strPath.Length - 4, "HeadEC");
                if (System.IO.File.Exists(strHeadEC))
                {
                    FileStream fileStream = new FileStream(@strHeadEC, FileMode.Open, FileAccess.Read);
                    imageList1.Images.Add(Image.FromStream(fileStream)); //ting
                    fileStream.Close();
                    fileStream.Dispose();
                }
            }

            if (imageList1.Images.Count <= 1)
            {
                Button_Pre.Enabled = false;
                Button_Next.Enabled = false;
            }
            else
            {
                Button_Pre.Enabled = true;
                Button_Next.Enabled = true;
            }
        }

        //Show Image
        private void ShowImage(object sender, EventArgs e)
        {
            if (imageList1.Images.Count > 0)
            {
                PictureBox_Image.Image = imageList1.Images[0];
                ((PictureBox)PictureBox_Image).Visible = true;
            }
        }

        private void BtnNext_Click(object sender, EventArgs e)
        {
            m_ImageIndex++;
            if (m_ImageIndex > imageList1.Images.Count - 1)
            {
                m_ImageIndex = 0;
            }
            PictureBox_Image.Image = imageList1.Images[m_ImageIndex];
        }

        private void BtnPre_Click(object sender, EventArgs e)
        {
            m_ImageIndex--;
            if (m_ImageIndex < 0)
            {
                m_ImageIndex = imageList1.Images.Count - 1;
            }
            PictureBox_Image.Image = imageList1.Images[m_ImageIndex];
        }

        /*-------------------------- The Following Is SID.-----------------------------*/

        // Read Card chip for SIDCard
        /* 0: success
          -1: load  sdtapi.dll  failed 
          -2：SDT_ReadNewAppMsg error
          -3：SDT_StartFindIDCard  error
          -4：SDT_SelectIDCard  error
          -5: SDT_ReadBaseMsg  error  */
        private int ReadCard(object sender, EventArgs e)
        {
            if (m_bLoad != true) return -1;

            m_fs = new FileStream(m_strLogPath, FileMode.OpenOrCreate);
            m_sw = new StreamWriter(m_fs);
            string strLog = "ReadCard";
            m_sw.WriteLine(strLog);
            strLog = "SDT_ReadNewAppMsg";
            m_sw.WriteLine(strLog);
            m_sw.Flush();
            m_fs.Flush();
            m_sw.Close();
            m_fs.Close();

            byte[] pucAppMsg = new byte[320];
            int len = 320;
            int nRet = pSDT_ReadNewAppMsg(m_nOpenPort, ref pucAppMsg[0], ref len, 0);
            if (nRet == 0x91 || nRet == 0x90)
                return -2;

            textBoxDisplayResult.Clear();
            textBoxDG.Text = "";
            PictureBox_Image.Visible = false;
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            strLog = "SDT_StartFindIDCard";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();
            byte[] pRAPDU = new byte[30];
            nRet = pSDT_StartFindIDCard(m_nOpenPort, ref pRAPDU[0], 0);
            if (nRet != 0x9F)
            {
                return -3;
            }

            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            strLog = "SDT_SelectIDCard";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();
            if (pSDT_SelectIDCard(m_nOpenPort, ref pRAPDU[0], 0) != 0x90)
                return -4;

            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            strLog = "SDT_ReadBaseMsg";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();
            nRet = pSDT_ReadBaseMsg(m_nOpenPort, ref pucCHMsg[0], ref puiCHMsgLen, ref pucPHMsg[0], ref puiPHMsgLen, 0);
            if (nRet != 0x90)
            {
                MessageBox.Show("SDT_ReadBaseMsg failed");
                return -5;
            }

            textBoxDisplayResult.Text = nReadSucceedCount.ToString();
            textBoxDisplayResult.Text += "\r\n";
            nReadSucceedCount++;
            string strSID = System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2);
            if (strSID == "I")
            {
                m_bSID = false;
                string filepath = System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
                filepath = filepath.Substring(0, filepath.LastIndexOf('\\') + 1);
                string strFileName = filepath + "CHMsg_Prp.txt";
                FileStream fs;
                StreamWriter sw;
                if (!File.Exists(strFileName))
                    fs = new FileStream(strFileName, FileMode.Create);
                else
                    fs = new FileStream(strFileName, FileMode.Append);

                sw = new StreamWriter(fs);
                string strContent = "";
                strContent = System.Text.Encoding.Unicode.GetString(pucCHMsg);
                sw.WriteLine(strContent);
                sw.Close();
                fs.Close();
                ShowCHMsg_Prp();
            }else if (strSID == "Y") // 新版中国绿卡（）
            {
                m_bSID = false;
                string filepath = System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
                filepath = filepath.Substring(0, filepath.LastIndexOf('\\') + 1);
                string strFileName = filepath + "CHMsg_Prp.txt";
                FileStream fs;
                StreamWriter sw;
                if (!File.Exists(strFileName))
                    fs = new FileStream(strFileName, FileMode.Create);
                else
                    fs = new FileStream(strFileName, FileMode.Append);

                sw = new StreamWriter(fs);
                string strContent = "";
                strContent = System.Text.Encoding.Unicode.GetString(pucCHMsg);
                sw.WriteLine(strContent);
                sw.Close();
                fs.Close();
                ShowCHMsg_PrpNew();
            }
            else if (strSID == "J")
            {
                m_bSID = false;
                string filepath = System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
                filepath = filepath.Substring(0, filepath.LastIndexOf('\\') + 1);
                string strFileName = filepath + "CHMsg_Prp.txt";
                FileStream fs;
                StreamWriter sw;
                if (!File.Exists(strFileName))
                    fs = new FileStream(strFileName, FileMode.Create);
                else
                    fs = new FileStream(strFileName, FileMode.Append);

                sw = new StreamWriter(fs);
                string strContent = "";
                strContent = System.Text.Encoding.Unicode.GetString(pucCHMsg);
                sw.WriteLine(strContent);
                sw.Close();
                fs.Close();
                ShowCHMsg_Rrp();
            }
            else
            {
                m_bSID = true;
                string filepath = System.Diagnostics.Process.GetCurrentProcess().MainModule.FileName;
                filepath = filepath.Substring(0, filepath.LastIndexOf('\\') + 1);
                string strFileName = filepath + "CHMsg_SID.txt";
                FileStream fs;
                //     StreamWriter sw;
                if (!File.Exists(strFileName))
                    fs = new FileStream(strFileName, FileMode.Create);
                else
                    fs = new FileStream(strFileName, FileMode.Append);
                string strContent = "";
                strContent = System.Text.Encoding.Unicode.GetString(pucCHMsg);
                fs.Close();
                ShowCHMsg_SID();

            }
            textBoxDG.Text = "no any DG info";

            ((PictureBox)PictureBox_Image).Visible = true;
            char[] arr_ImagePath = TextBox_ImagePath.Text.ToCharArray();
            string strImagePath = new string(arr_ImagePath);
            SavePhoto(strImagePath, 2);
            strImagePath += "\\head.bmp";
            PictureBox_Image.ImageLocation = strImagePath;
            Button_Pre.Enabled = false;
            Button_Next.Enabled = false;

            return 0;
        }

        // Permanent residence permit for foreigners
        void ShowCHMsg_Prp()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "ShowCHMsg_Prp";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            /**/
            textBoxDisplayResult.Text += "Recognition Succeed : \r\n";
            textBoxDisplayResult.Text += "证件名称:外国人永久居留身份证2017版\r\n";

            textBoxDisplayResult.Text += "姓名 : ";
            textBoxDisplayResult.Text += GetName();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "性别 : ";
            textBoxDisplayResult.Text += GetSex();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "永久居留证号码 : ";
            textBoxDisplayResult.Text += GetIDCode();
            textBoxDisplayResult.Text += "\r\n";


            textBoxDisplayResult.Text += "国籍或所在地区代码 : ";
            textBoxDisplayResult.Text += GetPeople();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "中文姓名 : ";
            textBoxDisplayResult.Text += GetPeopleChineseName();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件签发日期 : ";
            textBoxDisplayResult.Text += GetIssueDay();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件终止日期 : ";
            textBoxDisplayResult.Text += GetExpityDay();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "出生日期 : ";
            textBoxDisplayResult.Text += GetBirthday();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件版本号 : ";
            textBoxDisplayResult.Text += GetCardVersion();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "当次申请受理机关代码 : ";
            textBoxDisplayResult.Text += GetAuthority();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件类型标识 : I";
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "预留项 : ";
            textBoxDisplayResult.Text += GetReverse();
            textBoxDisplayResult.Text += "\r\n";
        }
        void ShowCHMsg_PrpNew()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "ShowCHMsg_PrpNew";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            textBoxDisplayResult.Text += "Recognition Succeed : \r\n";
            textBoxDisplayResult.Text += "证件名称:外国人永久居留身份证2023版\r\n";

            textBoxDisplayResult.Text += "中国姓名 : ";
            textBoxDisplayResult.Text += GetName();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "性别 : ";
            textBoxDisplayResult.Text += GetSex();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "换证次数 : ";
            textBoxDisplayResult.Text += GetNumberOfCertificateRenewals();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "出生日期 : ";
            textBoxDisplayResult.Text += GetBirthday();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "英文姓名 : ";
            textBoxDisplayResult.Text += GetEngName();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件号码 : ";
            textBoxDisplayResult.Text += GetIDCode();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "预留空间 : ";
            textBoxDisplayResult.Text += GetReservedSpace();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件签发日期 : ";
            textBoxDisplayResult.Text += GetIssueDay();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件有效日期 : ";
            textBoxDisplayResult.Text += GetExpityDay();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "英文姓名备用 : ";
            textBoxDisplayResult.Text += GetEnglishNameStandBy();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "所属国家和地区代码 : ";
            textBoxDisplayResult.Text += GetCountryOrRegionCode();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件类型标识 : ";
            textBoxDisplayResult.Text += GetNumberFlag();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "既往版本外国人永久居留证号码关联项 : ";
            textBoxDisplayResult.Text += GetNumberAssociation();
            textBoxDisplayResult.Text += "\r\n";


            textBoxDisplayResult.Text += "既往版本证件号码 : ";
            textBoxDisplayResult.Text += GetOldIDCode();
            textBoxDisplayResult.Text += "\r\n";
        }
        //  IDCard of chinese
        void ShowCHMsg_SID()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "ShowCHMsg_SID";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            textBoxDisplayResult.Text += "Recognition Succeed : \r\n";
            textBoxDisplayResult.Text += "证件名称:二代证\r\n";

            textBoxDisplayResult.Text += "姓名 : ";
            textBoxDisplayResult.Text += GetName();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "性别 : ";
            textBoxDisplayResult.Text += GetSex();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "民族 : ";
            textBoxDisplayResult.Text += GetPeople();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "出生日期 : ";
            textBoxDisplayResult.Text += GetBirthday();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "住址 : ";
            textBoxDisplayResult.Text += GetAddress();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "公民身份号码 : ";
            textBoxDisplayResult.Text += GetIDCode();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "签发机关 : ";
            textBoxDisplayResult.Text += GetAuthority();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "有效期起始日期 : ";
            textBoxDisplayResult.Text += GetIssueDay();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "有效期截止日期 : ";
            textBoxDisplayResult.Text += GetExpityDay();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text +=  "指纹信息：";
            if (GetFingerprintInfo().Length > 0)
            {
                textBoxDisplayResult.Text += "有\r\n";
            }
            else
            {
                textBoxDisplayResult.Text += "无\r\n";
            }
        }

        // Residence permit for Hong Kong, Macao and Taiwan residents
        void ShowCHMsg_Rrp()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "ShowCHMsg_Rrp";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            /**/
            textBoxDisplayResult.Text += "Recognition Succeed : \r\n";
            textBoxDisplayResult.Text += "证件名称:港澳台居民居住证\r\n";

            textBoxDisplayResult.Text += "姓名 : ";
            textBoxDisplayResult.Text += GetName();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "性别 : ";
            textBoxDisplayResult.Text += GetSex();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "预留项 : ";
            textBoxDisplayResult.Text += GetReverse(32,4);
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "出生日期 : ";
            textBoxDisplayResult.Text += GetBirthday();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "住址 : ";
            textBoxDisplayResult.Text += GetAddress();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "民族 : ";
            textBoxDisplayResult.Text += GetPeople();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "公民身份证号码 : ";
            textBoxDisplayResult.Text += GetIDCode();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "签发机关： : ";
            textBoxDisplayResult.Text += GetAuthority();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "有效期起始日期 : ";
            textBoxDisplayResult.Text += GetIssueDay();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "有效期截止日期 : ";
            textBoxDisplayResult.Text += GetExpityDay();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "通行证号码 : ";
            textBoxDisplayResult.Text += GetPassNum();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "签发次数 : ";
            textBoxDisplayResult.Text += GetIssueNum();
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "预留项 : ";
            textBoxDisplayResult.Text += GetReverse(242,6);
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "证件类型标识 : J";
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "预留项 : ";
            textBoxDisplayResult.Text += GetReverse(250, 6);
            textBoxDisplayResult.Text += "\r\n";

            textBoxDisplayResult.Text += "指纹信息：";
            if (GetFingerprintInfo().Length > 0)
            {
                textBoxDisplayResult.Text += "有\r\n";
            }
            else
            {
                textBoxDisplayResult.Text += "无\r\n";
            }
        }

        // get name
        string GetName()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetName";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return "";
            string str = "";
            if (m_bSID)
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 0, 30);
            else if(System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) == "I")
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 0, 120);
            else if (System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) == "Y")
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 0, 30);
            else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 0, 30);
            str.TrimEnd();
            return str;
        }

        // get chinese name of foreigners
        string GetPeopleChineseName()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetPeopleChineseName";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 158, 30);
            return str;
        }

        
        string GetCardVersion()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetCardVersion";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 236, 4);
            return str;
        }

        // get reverse
        string GetReverse()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetReverse";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 250, 6);
            return str;
        }
        //get reverse
        string GetReverse(int nPosition,int nVal)
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetReverse";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, nPosition, nVal);
            return str;
        }

      
        string GetSex()
        {
            if (puiCHMsgLen == 0) return " ";

            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetSex";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            byte sex = 0;
            if (System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) == "I")
                sex = pucCHMsg[120];
            else if (System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) == "Y")
                sex = pucCHMsg[30];
            else
                sex = pucCHMsg[30];
            if (sex == '1')
                return "男";
            else
                return "女";
        }
        // 换证次数
        string GetNumberOfCertificateRenewals()
        {
            if (puiCHMsgLen == 0) return " ";

            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetNumberOfCertificateRenewals";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();
            return  System.Text.Encoding.Unicode.GetString(pucCHMsg, 32, 4);
        }
        // get people of chinese
        string GetPeople()
        {
            if (puiCHMsgLen == 0) return " ";

            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetPeople";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (m_bSID)
            {
                string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 32, 4);
                switch (str)
                {
                    case "01": return "汉";
                    case "02": return "蒙古";
                    case "03": return "回";
                    case "04": return "藏";
                    case "05": return "维吾尔";
                    case "06": return "苗";
                    case "07": return "彝";
                    case "08": return "壮";
                    case "09": return "布依";
                    case "10": return "朝鲜";
                    case "11": return "满";
                    case "12": return "侗";
                    case "13": return "瑶";
                    case "14": return "白";
                    case "15": return "土家";
                    case "16": return "哈尼";
                    case "17": return "哈萨克";
                    case "18": return " 傣";
                    case "19": return " 黎";
                    case "20": return " 傈僳";
                    case "21": return " 佤";
                    case "22": return " 畲";
                    case "23": return " 高山";
                    case "24": return " 拉祜";
                    case "25": return " 水";
                    case "26": return " 东乡";
                    case "27": return " 纳西";
                    case "28": return " 景颇";
                    case "29": return " 柯尔克孜";
                    case "30": return " 土";
                    case "31": return " 达斡尔";
                    case "32": return " 仫佬";
                    case "33": return "羌";
                    case "34": return "布朗";
                    case "35": return "撒拉";
                    case "36": return "毛南";
                    case "37": return "仡佬";
                    case "38": return "锡伯";
                    case "39": return "阿昌";
                    case "40": return "普米";
                    case "41": return "塔吉克";
                    case "42": return "怒";
                    case "43": return "乌孜别克";
                    case "44": return "俄罗斯";
                    case "45": return "鄂温克";
                    case "46": return "德昂";
                    case "47": return "保安";
                    case "48": return "裕固";
                    case "49": return "京";
                    case "50": return "塔塔尔";
                    case "51": return "独龙";
                    case "52": return "鄂伦春";
                    case "53": return "赫哲";
                    case "54": return "门巴";
                    case "55": return "珞巴";
                    case "56": return "基诺";
                    case "97": return "其他";
                    case "98": return "外国血统中国籍人士";
                    default: return "";
                }
            }
            else
            {
                string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 152, 6);
                str.TrimEnd();
                return str;
            }
        }

        
        string GetBirthday()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetBirthday";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = "";
            if (m_bSID)
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 36, 16);
            else if(System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) == "I")
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 220, 16);
            else 
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 36, 16);
            str.TrimEnd();
            return str;
        }

        
        string GetAddress()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetAddress";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 52, 70);
            return str;
        }
        string GetEngName()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetEngName";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 52, 70);
            return str;
        }

        string GetAuthority()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetAuthority";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = "";
            if (m_bSID)
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 158, 30);
            else if(System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) == "I")
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 240, 8);
            else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 158, 30);
            str.TrimEnd();
            return str;
        }
        // 新版绿卡 预留空间
        string GetReservedSpace()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetReservedSpace";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return " ";
            string str = "";
            str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 158, 30);
            str.TrimEnd();
            return str;
        }
        // SIDCard Number
        string GetIDCode()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetIDCode";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return "";
            string str = "";
            if (m_bSID)
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 122, 36);
            else if(System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) == "I")
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 122, 30);
            else if (System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2) == "Y")
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 122, 36);
            else
                str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 122, 36);
            str.TrimEnd();
            return str;
        }

        
        string GetIssueDay()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetIssueDay";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return "";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 188, 16);
            return str;
        }

        
        string GetExpityDay()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetExpityDay";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return "";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 204, 16);
            return str;
        }

        string GetEnglishNameStandBy()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetEnglishNameStandBy";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return "";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 220, 22);
            return str;
        }

        string GetCountryOrRegionCode()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetCountryOrRegionCode";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return "";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 242, 6);
            return str;
        }

        string GetNumberFlag()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetNumberFlag";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0) return "";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 248, 2);
            return str;
        }

        string GetNumberAssociation()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetNumberAssociation";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (puiCHMsgLen == 0 && puiCHMsgLen <= 250) return "";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 250, 6);
            return str;
        }

        int AssignedNumbers(string cstr)
        {
            if (cstr == ("A"))
            {
                return 10;
            }
            else if (cstr == ("B"))
            {
                return 11;
            }
            else if (cstr == ("C"))
            {
                return 12;
            }
            else if (cstr == ("D"))
            {
                return 13;
            }
            else if (cstr == ("E"))
            {
                return 14;
            }
            else if (cstr == ("F"))
            {
                return 15;
            }
            else if (cstr == ("G"))
            {
                return 16;
            }
            else if (cstr == ("H"))
            {
                return 17;
            }
            else if (cstr == ("I"))
            {
                return 18;
            }
            else if (cstr == ("J"))
            {
                return 19;
            }
            else if (cstr == ("K"))
            {
                return 20;
            }
            else if (cstr == ("L"))
            {
                return 21;
            }
            else if (cstr == ("M"))
            {
                return 22;
            }
            else if (cstr == ("N"))
            {
                return 23;
            }
            else if (cstr == ("O"))
            {
                return 24;
            }
            else if (cstr == ("P"))
            {
                return 25;
            }
            else if (cstr == ("Q"))
            {
                return 26;
            }
            else if (cstr == ("R"))
            {
                return 27;
            }
            else if (cstr == ("S"))
            {
                return 28;
            }
            else if (cstr == ("T"))
            {
                return 29;
            }
            else if (cstr == ("U"))
            {
                return 30;
            }
            else if (cstr == ("V"))
            {
                return 31;
            }
            else if (cstr == ("W"))
            {
                return 32;
            }
            else if (cstr == ("X"))
            {
                return 33;
            }
            else if (cstr == ("Y"))
            {
                return 34;
            }
            else if (cstr == ("Z"))
            {
                return 35;
            }
            else if (cstr == ("<"))
            {
                return 0;
            }
            else
            {
                return -1;
            }
        }

        string GetOldIDCode()
        {
            string strOldIDCard="";
            if ("" == GetNumberAssociation().Trim())
            {
                return "";
            }else
            {
                strOldIDCard = GetCountryOrRegionCode();
                strOldIDCard += GetIDCode().Substring(1, 2).Trim();
                strOldIDCard += GetNumberAssociation().Substring(0,2).Trim();
                strOldIDCard += GetIDCode().Substring(8, 6).Trim();
                strOldIDCard += GetNumberAssociation().Substring(2,1).Trim();

                // 计算校验位
                string strTemporary = strOldIDCard;
                int count = 0;
                if (AssignedNumbers(strTemporary.Substring(0,1).Trim()) != -1)
                {
                    count += AssignedNumbers(strTemporary.Substring(0,1).Trim()) * 7;
                }
                if (AssignedNumbers(strTemporary.Substring(1, 1).Trim()) != -1)
                {
                    count += AssignedNumbers(strTemporary.Substring(1, 1).Trim()) * 3;
                }
                if (AssignedNumbers(strTemporary.Substring(2, 1).Trim()) != -1)
                {
                    count += AssignedNumbers(strTemporary.Substring(2, 1).Trim()) * 1;
                }
                count += Convert.ToInt32(strTemporary.Substring(3, 1).Trim()) * 7;
                count += Convert.ToInt32(strTemporary.Substring(4, 1).Trim()) * 3;
                count += Convert.ToInt32(strTemporary.Substring(5, 1).Trim()) * 1;
                count += Convert.ToInt32(strTemporary.Substring(6, 1).Trim()) * 7;
                count += Convert.ToInt32(strTemporary.Substring(7, 1).Trim()) * 3;
                count += Convert.ToInt32(strTemporary.Substring(8, 1).Trim()) * 1;
                count += Convert.ToInt32(strTemporary.Substring(9, 1).Trim()) * 7;
                count += Convert.ToInt32(strTemporary.Substring(10, 1).Trim()) * 3;
                count += Convert.ToInt32(strTemporary.Substring(11, 1).Trim()) * 1;
                count += Convert.ToInt32(strTemporary.Substring(12, 1).Trim()) * 7;
                count += Convert.ToInt32(strTemporary.Substring(13, 1).Trim()) * 3;
                strOldIDCard += count % 10;
            }
            return strOldIDCard;
        }

        //get pass number
        string GetPassNum()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetIssueDay";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (0 == puiCHMsgLen)
                return "";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 220, 18);
            return str;
        }

       
        string GetIssueNum()
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "GetIssueDay";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            if (0 == puiCHMsgLen)
                return "";
            string str = System.Text.Encoding.Unicode.GetString(pucCHMsg, 238, 4);
            return str;
        }

        
        string GetFingerprintInfo()
        {
            string str = "";
            if (puiPHMsgLen != 0)
                str = "有";
            else
                str = "无";

            return str;
        }

        // save chip head to image file
        int SavePhoto(string retFileName, int nType)
        {
            m_fs = new FileStream(m_strLogPath, FileMode.Append);
            m_sw = new StreamWriter(m_fs);
            string strLog = "SavePhoto";
            m_sw.WriteLine(strLog);
            m_sw.Close();
            m_fs.Close();

            string savepath = retFileName + "\\head.wlt";
            FileStream fs;
            fs = new FileStream(savepath, FileMode.Create, FileAccess.ReadWrite);
            fs.Write(pucPHMsg, 0, pucPHMsg.Length);
            fs.Close();
            pGetBmp(savepath, 2);
            return 0;
        }

        public bool LoadDllapi()
        {
            string DllPath = this.TEXTBOX_DLLPATH.Text;
            DllPath += "\\sdtapi.dll";

            IntPtr hModuleadi = MyDll.LoadLibrary(@DllPath);
            if (hModuleadi.ToInt64() == 0)
            {
                MessageBox.Show("Load sdtapi.dll failed \n");
                return false;
            }
            pSDT_OpenPort = (SDT_OpenPort)MyDll.LoadFunction<SDT_OpenPort>(hModuleadi, "SDT_OpenPort");
            pSDT_ClosePort = (SDT_ClosePort)MyDll.LoadFunction<SDT_ClosePort>(hModuleadi, "SDT_ClosePort");
            pSDT_StartFindIDCard = (SDT_StartFindIDCard)MyDll.LoadFunction<SDT_StartFindIDCard>(hModuleadi, "SDT_StartFindIDCard");
            pSDT_SelectIDCard = (SDT_SelectIDCard)MyDll.LoadFunction<SDT_SelectIDCard>(hModuleadi, "SDT_SelectIDCard");
            pSDT_ReadBaseMsg = (SDT_ReadBaseMsg)MyDll.LoadFunction<SDT_ReadBaseMsg>(hModuleadi, "SDT_ReadBaseMsg");
            pSDT_ReadNewAppMsg = (SDT_ReadNewAppMsg)MyDll.LoadFunction<SDT_ReadNewAppMsg>(hModuleadi, "SDT_ReadNewAppMsg");
            pSDT_GetSAMIDToStr = (SDT_GetSAMIDToStr)MyDll.LoadFunction<SDT_GetSAMIDToStr>(hModuleadi, "SDT_GetSAMIDToStr");
            pSDT_GetSAMID = (SDT_GetSAMID)MyDll.LoadFunction<SDT_GetSAMID>(hModuleadi, "SDT_GetSAMID");

            DllPath = this.TEXTBOX_DLLPATH.Text + "\\WltRS.dll";

            IntPtr hModuleWltRS = MyDll.LoadLibrary(@DllPath);
            if (hModuleWltRS.ToInt64() == 0)
            {
                MessageBox.Show("Load WltRS.dll failed ");
                return false;
            }
            pGetBmp = (GetBmp)MyDll.LoadFunction<GetBmp>(hModuleWltRS, "GetBmp");


            if (pSDT_OpenPort == null || pSDT_ClosePort == null || pSDT_StartFindIDCard == null || pSDT_SelectIDCard == null || pSDT_ReadBaseMsg == null ||
                pSDT_ReadNewAppMsg == null || pSDT_GetSAMIDToStr == null || pSDT_GetSAMID == null)
            {
                MyDll.FreeLibrary(hModuleadi);
                MessageBox.Show("Export sdtapi.dll API failed.");
                return false;
            }

            if (pGetBmp == null)
            {
                MyDll.FreeLibrary(hModuleWltRS);
                MessageBox.Show("Export sdtapi.dll API failed. ");
                return false;
            }

            return true;
        }

        
        private void LoadDLL()
        {
            if (m_bLoad == false)
            {
                if (!LoadDllapi())
                {
                    return;
                }
                else
                {
                    for (int iPort = 1001; iPort < 1017; ++iPort)
                    {
                        if (pSDT_OpenPort(iPort) == 0x90)
                        {
                            m_nOpenPort = iPort;
                            m_bLoad = true;
                            break;
                        }
                    }
                }
            }

            if (m_bLoad != true)
                MessageBox.Show("Open port failed！");
        }

        private void button_ReadSIDCard_Click(object sender, EventArgs e)
        {
            ReadCard(sender, e);
        }

        private void btnDllPath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.ShowDialog();
            this.TEXTBOX_DLLPATH.Text = fbd.SelectedPath;
            string strPathName = fbd.SelectedPath + "\\IDCardConfig.ini";
            textConFigPath.Text = strPathName;
        }

        private void Picpath_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.ShowDialog();
            this.TextBox_ImagePath.Text = fbd.SelectedPath;
        }

        private void ScrollIdent_SelectedIndexChanged(object sender, EventArgs e)
        {
            if ("automatic identification" == ScrollIdent.Text)
            {
                bEnd = false;
                timer.Start();
                textBoxDG.Text = "";
                textBoxDisplayResult.Text = "";
                CardType.Enabled = false;
                recogbutton.Enabled = false;
                button_ReadSIDCard.Enabled = false;
                ((PictureBox)PictureBox_Image).Visible = false;

                if (bScroll == true)
                {
                    int nConFig;
                    string strTextConFigPath = textConFigPath.Text;
                    nConFig = pSetConfigByFile(strTextConFigPath);
                    //textConFigPath.Text= "Return Value:";
                    //textConFigPath.Text += nConFig.ToString();
                }
                bScroll = true;
            }
            else if ("Manual identification" == ScrollIdent.Text)
            {
                textBoxDG.Text = "";
                textBoxDisplayResult.Text = "";
                bEnd = true;
                timer.Stop();
                ((PictureBox)PictureBox_Image).Visible = false;
                CardType.Enabled = true;
                recogbutton.Enabled = true;
                button_ReadSIDCard.Enabled = true;
            }
            else
            { };
        }

        private void btnConFigPath_Click(object sender, EventArgs e)
        {
            this.openFileDialog1.ShowDialog();
            textConFigPath.Text = this.openFileDialog1.FileName;
        }

        int AscllToInt(int nVal)
        {
            int n = 0;
            if ((nVal + 48) >= '0' && (nVal + 48) <= '9')
                n = nVal + 48;
            //if ((nVal+97) >= 'a'&&(nVal+97) <= 'f')
            //	n = nVal + 97;
            if ((nVal + 55) >= 'A' && (nVal + 55) <= 'F')
                n = nVal + 55;
            return n;
        }

        private void btnGetDeviceRFIDSN_Click(object sender, EventArgs e)
        {
            if (!m_bLoad)
            {
                TEXTBOX_RFUD_SERIALNUMBER.Text = "Please successful loading recognition engine.！";
                return;
            }

            byte[] cArrSN = new byte[1024];
            int nRet = pSDT_GetSAMIDToStr(m_nOpenPort, ref cArrSN[0], 0);
            if (nRet == 0x90)
                TEXTBOX_RFUD_SERIALNUMBER.Text = Encoding.UTF8.GetString(cArrSN);
            else
                TEXTBOX_RFUD_SERIALNUMBER.Text = "Failed to get Device Sequence";
            /*******************************************************************/


            byte[] szHexBuf = new byte[64];
            byte[] sHexBufSrc = new byte[129];
            nRet = pSDT_GetSAMID(m_nOpenPort, ref szHexBuf[0], 0);
            if (nRet == 0x90)
            {
                int i = 0;
                for (int j = 0; j < szHexBuf.Length; j++)
                {
                    int nHex = szHexBuf[j] / 16;
                    sHexBufSrc[i++] = (byte)AscllToInt(nHex);
                    sHexBufSrc[i++] = (byte)AscllToInt(szHexBuf[j] % 16);
                }
                System.Text.ASCIIEncoding asciiEncoding = new System.Text.ASCIIEncoding();
                string sHexBufDest = asciiEncoding.GetString(sHexBufSrc);

                
                ////save SDT_GetSAMID and change to 16bit 
                for (int j = sHexBufDest.Length-1; j != 0; j--)
                {
                    if (sHexBufDest[j] == '0' || sHexBufDest[j] == '\0')
                    {
                        sHexBufDest = sHexBufDest.Remove(sHexBufDest.Length - 1, 1); //remover buffer "
                    }
                    else
                        break;
                }
                return;
            }
        }
    }
}

