using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

//add manually
using System.Runtime.InteropServices;
using System.Collections;
////////////////////
using System.Threading;
using System.Timers;

namespace CSharpDemo
{
    public partial class Form1 : Form
    {
        //private System.Windows.Forms.Timer t = new System.Windows.Forms.Timer();
        public Form1()
        {
            InitializeComponent();
        }

        //indicates the idcard.dll is loaded or not
        bool m_bIsIDCardLoaded = false;

        public static class MyDll
        {
            [DllImport("Kernel32.dll")]
            public static extern IntPtr LoadLibrary(string path);

            [DllImport("Kernel32.dll")]
            public static extern bool FreeLibrary(IntPtr hModule);

            [DllImport("Kernel32.dll")]
            private static extern IntPtr GetProcAddress(IntPtr hModule, string procName);
            [DllImport("kernel32.dll")]
            public static extern uint GetLastError();

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

        //初始化
        public delegate int InitIDCard([MarshalAs(UnmanagedType.LPWStr)] String strUserID, int nType, [MarshalAs(UnmanagedType.LPWStr)] String strDllPath);       
        public delegate void FreeIDCard();

        //检测设备状态
        public delegate bool CheckDeviceOnlineEx();

        //图像采集
        public delegate int AcquireImage(int nCardType);       
        public delegate bool SetAcquireImageType(int nLightType, int nImageType);       
        public delegate bool SetUserDefinedImageSize(int nWidth, int nHeight);        
        public delegate bool SetAcquireImageResolution(int nResolutionX, int nResolutionY);

        //识别并获取识别结果
        public delegate int ResetIDCardID();       
        public delegate int AddIDCardID(int nMainID, int[] nSubID, int nSubIdCount);
        public delegate int SetIDCardRejectType(int nMainID, bool bFlag);
        public delegate int RecogIDCard();       
        public delegate int RecogIDCardEX(int nMainID, int nSubID);
        public delegate int GetRecogResult(int nIndex, [MarshalAs(UnmanagedType.LPWStr)] String strBuffer, ref int nBufferLen);
        public delegate int GetFieldName(int nIndex, [MarshalAs(UnmanagedType.LPWStr)] String strBuffer, ref int nBufferLen);        
        public delegate int GetResultType(int nIndex);
        public delegate int GetIDCardName([MarshalAs(UnmanagedType.LPWStr)] String strBuffer, ref int nBufferLen);       
        public delegate int GetSubID();

        //图像保存
        public delegate int SaveImage([MarshalAs(UnmanagedType.LPWStr)] String strFileName);        
        public delegate int SaveHeadImage([MarshalAs(UnmanagedType.LPWStr)] String strFileName);

        //其它接口
        public delegate int GetCurrentDevice([MarshalAs(UnmanagedType.LPWStr)] String strDeviceName, int nLength);
        public delegate void GetVersionInfo([MarshalAs(UnmanagedType.LPWStr)] String strVersion, int nLength);
        public delegate int GetDeviceSN([MarshalAs(UnmanagedType.LPWStr)] String strDevcieSn, int nLength);
        public delegate int WriteDeviceSI([MarshalAs(UnmanagedType.LPWStr)] String strDeviceSI, int nLength);
        public delegate int CheckDeviceSI([MarshalAs(UnmanagedType.LPWStr)]String strDeviceSI, int nLength);

        //名片接口
        public delegate int RecogBusinessCard(int nType);
        public delegate int GetBusinessCardResultCount(int nID);
        public delegate int GetBusinessCardResult(int nID, int nIndex, [MarshalAs(UnmanagedType.LPWStr)] String strBuffer, ref int nBufferLen);
        public delegate int GetBusinessCardFieldName(int nID, [MarshalAs(UnmanagedType.LPWStr)] String strBuffer, ref int nBufferLen);
        public delegate int GetBusinessCardPosition(int nID, int nIndex, ref int nBufferLen, ref int nRight, ref int nTop, ref int nBottoom);
        //初始化
        InitIDCard lpInitIDCard;
        FreeIDCard lpFreeIDCard;
        //检测设备
        CheckDeviceOnlineEx lpCheckDeviceOnlineEx;
        //拍照
        AcquireImage lpAcquireImage;
        SetAcquireImageType lpSetAcquireImageType;
        SetAcquireImageResolution lpSetAcquireImageResolution;
        SetUserDefinedImageSize lpSetUserDefinedImageSize;
        //设置证件类型
        ResetIDCardID lpResetIDCardID;
        AddIDCardID lpAddIDCardID;
        SetIDCardRejectType lpSetIDCardRejectType;
        //识别并获取结果
        RecogIDCard lpRecogIDCard;
        RecogIDCardEX lpRecogIDCardEX;
        GetRecogResult lpGetRecogResult;
        GetResultType lpGetResultType;
        GetFieldName lpGetFieldName;
        GetSubID lpGetSubID;
        GetIDCardName lpGetIDCardName;
        //保存图片
        SaveImage lpSaveImage;
        SaveHeadImage lpSaveHeadImage;
        //其他接口
        GetVersionInfo lpGetVersionInfo;
        GetCurrentDevice lpGetCurrentDevice;
        GetDeviceSN lpGetDeviceSN;
        CheckDeviceSI lpCheckDeviceSI;
        WriteDeviceSI lpWriteDeviceSI;
        //名片接口
        RecogBusinessCard lpRecogBusinessCard;
        GetBusinessCardResultCount lpGetBusinessCardResultCount;
        GetBusinessCardResult lpGetBusinessCardResult;
        GetBusinessCardFieldName lpGetBusinessCardFieldName;
        GetBusinessCardPosition lpGetBusinessCardPosition;


        private IntPtr m_handle;//指针或句柄

        //加载识别核心
        private void btnLoadKernal_Click(object sender, EventArgs e)
        {
            //check if the kernel is loaded or not
            if (m_bIsIDCardLoaded)
            {
                textBoxDisplayResult.Text = "核心已经加载成功";
                return;
            }

            String strDllPath = textBox_DllPath.Text;
            String strTmp = "";
            if (strDllPath.Length == 0)
            {
                strTmp += "IDCard.dll";
            }
            else
            {
                strTmp += strDllPath + "\\IDCard.dll";
            }
            m_handle = MyDll.LoadLibrary(@strTmp);
             //m_handle = MyDll.LoadLibraryEx(@strTmp,null,8);
            if (m_handle.ToInt64() == 0)
            {
                uint nRes = MyDll.GetLastError();
                textBoxDisplayResult.Text = "加载IDCard.dll失败" + nRes.ToString();
                return;
            }
            //初始化
            lpInitIDCard = (InitIDCard)MyDll.LoadFunction<InitIDCard>(m_handle, "InitIDCard");
            lpFreeIDCard = (FreeIDCard)MyDll.LoadFunction<FreeIDCard>(m_handle, "FreeIDCard");
            //检测设备
            lpCheckDeviceOnlineEx = (CheckDeviceOnlineEx)MyDll.LoadFunction<CheckDeviceOnlineEx>(m_handle, "CheckDeviceOnlineEx");
            //拍照设置
            lpAcquireImage = (AcquireImage)MyDll.LoadFunction<AcquireImage>(m_handle, "AcquireImage");
            lpSetAcquireImageType = (SetAcquireImageType)MyDll.LoadFunction<SetAcquireImageType>(m_handle, "SetAcquireImageType");
            lpSetAcquireImageResolution = (SetAcquireImageResolution)MyDll.LoadFunction<SetAcquireImageResolution>(m_handle, "SetAcquireImageResolution");
            lpSetUserDefinedImageSize = (SetUserDefinedImageSize)MyDll.LoadFunction<SetUserDefinedImageSize>(m_handle, "SetUserDefinedImageSize");
            //识别并获取结果
            lpResetIDCardID = (ResetIDCardID)MyDll.LoadFunction<ResetIDCardID>(m_handle, "ResetIDCardID");
            lpAddIDCardID = (AddIDCardID)MyDll.LoadFunction<AddIDCardID>(m_handle, "AddIDCardID");
            lpSetIDCardRejectType = (SetIDCardRejectType)MyDll.LoadFunction<SetIDCardRejectType>(m_handle, "SetIDCardRejectType");
            lpRecogIDCard = (RecogIDCard)MyDll.LoadFunction<RecogIDCard>(m_handle, "RecogIDCard");
            lpRecogIDCardEX = (RecogIDCardEX)MyDll.LoadFunction<RecogIDCardEX>(m_handle, "RecogIDCardEX");
            lpGetRecogResult = (GetRecogResult)MyDll.LoadFunction<GetRecogResult>(m_handle, "GetRecogResult");
            lpGetResultType = (GetResultType)MyDll.LoadFunction<GetResultType>(m_handle, "GetResultType");
            lpGetFieldName = (GetFieldName)MyDll.LoadFunction<GetFieldName>(m_handle, "GetFieldName");
            lpGetSubID = (GetSubID)MyDll.LoadFunction<GetSubID>(m_handle, "GetSubID");
            lpGetIDCardName = (GetIDCardName)MyDll.LoadFunction<GetIDCardName>(m_handle, "GetIDCardName");
            //保存图片
            lpSaveImage = (SaveImage)MyDll.LoadFunction<SaveImage>(m_handle, "SaveImage");
            lpSaveHeadImage = (SaveHeadImage)MyDll.LoadFunction<SaveHeadImage>(m_handle, "SaveHeadImage");
            //其他接口
            lpGetVersionInfo = (GetVersionInfo)MyDll.LoadFunction<GetVersionInfo>(m_handle, "GetVersionInfo");
            lpGetCurrentDevice = (GetCurrentDevice)MyDll.LoadFunction<GetCurrentDevice>(m_handle, "GetCurrentDevice");
            lpGetDeviceSN = (GetDeviceSN)MyDll.LoadFunction<GetDeviceSN>(m_handle, "GetDeviceSN");
            lpCheckDeviceSI = (CheckDeviceSI)MyDll.LoadFunction<CheckDeviceSI>(m_handle, "CheckDeviceSI");
            lpWriteDeviceSI = (WriteDeviceSI)MyDll.LoadFunction<WriteDeviceSI>(m_handle, "WriteDeviceSI");
            //名片接口
            lpRecogBusinessCard = (RecogBusinessCard)MyDll.LoadFunction<RecogBusinessCard>(m_handle, "RecogBusinessCard");
            lpGetBusinessCardResult = (GetBusinessCardResult)MyDll.LoadFunction<GetBusinessCardResult>(m_handle, "GetBusinessCardResult");
            lpGetBusinessCardResultCount = (GetBusinessCardResultCount)MyDll.LoadFunction<GetBusinessCardResultCount>(m_handle, "GetBusinessCardResultCount");
            lpGetBusinessCardFieldName = (GetBusinessCardFieldName)MyDll.LoadFunction<GetBusinessCardFieldName>(m_handle, "GetBusinessCardFieldName");
            lpGetBusinessCardPosition = (GetBusinessCardPosition)MyDll.LoadFunction<GetBusinessCardPosition>(m_handle, "GetBusinessCardPosition");

            if (lpInitIDCard == null || lpGetCurrentDevice == null 
                || lpCheckDeviceOnlineEx == null 
                || lpAcquireImage == null || lpSetAcquireImageType == null 
                || lpSetAcquireImageResolution == null || lpSetUserDefinedImageSize == null 
                || lpResetIDCardID == null ||lpAddIDCardID == null 
                || lpRecogIDCard == null || lpRecogIDCardEX == null 
                || lpGetRecogResult == null 
                || lpGetFieldName == null || lpGetResultType == null || lpGetFieldName == null
                || lpGetIDCardName == null || lpGetSubID == null 
                || lpGetVersionInfo == null || lpGetCurrentDevice == null || lpGetDeviceSN == null 
                || lpCheckDeviceSI == null || lpWriteDeviceSI == null 
                || lpRecogBusinessCard == null 
                || lpGetBusinessCardResult == null || lpGetBusinessCardResultCount == null 
                || lpGetBusinessCardFieldName == null || lpGetBusinessCardPosition == null  )
            {
                MyDll.FreeLibrary(m_handle);
                textBoxDisplayResult.Text = "初始化识别核心失败, 错误代码：-2\r\n";
                return;
            }

            //初始化识别核心
            int nRet;
            char[] arrUserID = textBoxUserID.Text.ToCharArray();
            if(strDllPath.Length != 0)
            {
                char[] arrDllPath = strDllPath.ToCharArray();
                nRet = lpInitIDCard(textBoxUserID.Text, 1, strDllPath);
            }
            else
            {
                nRet = lpInitIDCard(textBoxUserID.Text, 1, null);
            }            
            if (nRet != 0)
            {
                textBoxDisplayResult.Text = "初始化识别核心失败,\r\n";
                String strtmp=nRet.ToString();
                textBoxDisplayResult.Text += "返回值："+strtmp;
                return;
            }
            m_bIsIDCardLoaded = true;
            textBoxDisplayResult.Text = "加载识别核心成功\r\n";

            GetDeviceInfo();
         }


        //close the application
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            btnFreeKernal_Click(sender, e);
        }


        //扫描、识别并获取识别结果
        private void btnScanAndRecog_Click(object sender, EventArgs e)
        {
            if (!m_bIsIDCardLoaded)
            {
                textBoxDisplayResult.Text = "识别核心未加载，请先加载识别核心";
                return;
            }
            //扫描
            int nScanSizeType = int.Parse(textBoxScanSize.Text);
            if (nScanSizeType <= 0)
            {
                textBoxDisplayResult.Text = "无效的扫描尺寸，请重新设置";
                return;
            }

            //get image from device
            int nRet = lpAcquireImage(nScanSizeType);
            if (nRet != 0)
            {
                textBoxDisplayResult.Text = "返回值:";
                textBoxDisplayResult.Text += nRet.ToString();
                textBoxDisplayResult.Text += "\r\n";
                textBoxDisplayResult.Text += "采集图像失败";
            }


            //保存采集的图像
            String strRunPath = System.Windows.Forms.Application.StartupPath + "\\";
            String strImgPath = strRunPath + "test.jpg";
            nRet = lpSaveImage(strImgPath);
            if (nRet != 0)
            {
                MessageBox.Show("保存图像失败, " + nRet.ToString() + "！");
            }

            //识别
            int nCardType = int.Parse(textBoxCardType.Text);
            if (nCardType <= 0)
            {
                textBoxDisplayResult.Text = "无效的证件类型";
                return;
            }
            //调用识别接口进行识别
            //nCardType可以表示一种证件，也可以表示多种证件，如1表示一代证，2表示二代证，4表示二代证背面，那么nCardType=1表示识别一代证
            if (nCardType == 1010)
            {
                nRet = lpRecogBusinessCard(1);
                if (nRet == 0)
                {
                    textBoxDisplayResult.Text = "识别成功\r\n";
                    int MAX_CH_NUM = 128;
                    
                    for (int i = 0; ; i++)
                    {
                        //char[] cArrFieldValue = new char[MAX_CH_NUM];
                        //char[] cArrFieldName = new char[MAX_CH_NUM];
                        String strFieldValue = new string('\0', MAX_CH_NUM);
                        String strFieldName = new string('\0', MAX_CH_NUM);

                        nRet = lpGetBusinessCardFieldName(i, strFieldName, ref MAX_CH_NUM);
                        if (nRet <= 0)
                        {
                            break;
                        }
                        int nCount = lpGetBusinessCardResultCount(i);
                        if (nCount == 0)
                        {
                            textBoxDisplayResult.Text += strFieldName;
                            textBoxDisplayResult.Text += ":";
                            textBoxDisplayResult.Text += "";
                            textBoxDisplayResult.Text += "\r\n";
                        }
                        for (int j = 0; j < nCount; j++)
                        {
                            nRet =lpGetBusinessCardResult(i, j, strFieldValue, ref MAX_CH_NUM);
                            textBoxDisplayResult.Text += strFieldName;
                            textBoxDisplayResult.Text += ":";
                            textBoxDisplayResult.Text += strFieldValue;
                            textBoxDisplayResult.Text += "\r\n";
                        }
                    }
                }
            }
            else
            {
                //RecogID()接口调用
                int[] nSubID = new int[1];
                nSubID[0] = 0;
                nRet = lpResetIDCardID();
                nRet = lpAddIDCardID(nCardType, nSubID, 1);
                nRet = lpSetIDCardRejectType(nCardType, true);
                //若要调用拒识借口，需在识别调用
                //MyDll.SetIDCardTypeReject(nCardType,true);
                nRet = lpRecogIDCard();
                //RecogIDCardEx接口调用
                //nRet = MyDll.RecogIDCardEx(nCardType,0);
                if (nRet <= 0)
                {
                    textBoxDisplayResult.Text = "返回值:";
                    textBoxDisplayResult.Text += nRet.ToString();
                    textBoxDisplayResult.Text += "\r\n";
                    textBoxDisplayResult.Text += "识别失败";
                    return;
                }

                //如果需要在识别后可以保存头像
                String strHeadPath = strRunPath + "test_Head.jpg";
                lpSaveHeadImage(strHeadPath);

                int MAX_CH_NUM = 128;
                //char[] cArrFieldValue = new char[MAX_CH_NUM];
                //char[] cArrFieldName = new char[MAX_CH_NUM];
                //char[] cArrCardName = new char[MAX_CH_NUM];
                String strFieldValue = new string('\0', MAX_CH_NUM);
                String strFieldName = new string('\0', MAX_CH_NUM);
                String strCardName = new string('\0', MAX_CH_NUM);

                textBoxDisplayResult.Text = "识别成功\r\n";
                //识别成功后调用GetIDCardName接口获取证件名
                textBoxDisplayResult.Text += "证件名 : ";
                lpGetIDCardName(strCardName, ref MAX_CH_NUM);
                textBoxDisplayResult.Text += strCardName;
                textBoxDisplayResult.Text += "\r\n";
                //识别成功后调用GetSubID接口获取证件的SubID
                textBoxDisplayResult.Text += "SubID : ";
                textBoxDisplayResult.Text += (lpGetSubID()).ToString();
                textBoxDisplayResult.Text += "\r\n";
                for (int i = 1; ; i++)
                {
                    MAX_CH_NUM = 128;
                    nRet = lpGetRecogResult(i, strFieldValue, ref MAX_CH_NUM);
                    if (nRet == 3)
                    {
                        break;
                    }
                    MAX_CH_NUM = 128;
                    lpGetFieldName(i, strFieldName, ref MAX_CH_NUM);

                    textBoxDisplayResult.Text += strFieldName;
                    textBoxDisplayResult.Text += "(";
                    textBoxDisplayResult.Text += (lpGetResultType(i)).ToString();
                    textBoxDisplayResult.Text += ")";
                    textBoxDisplayResult.Text += ":";
                    textBoxDisplayResult.Text += strFieldValue;
                    textBoxDisplayResult.Text += "\r\n";
                }               
            }          
        }

       
        //自定义图像采集尺寸的设置
        private void btnSetImageSize_Click(object sender, EventArgs e)
        {
            String strWidth = textBoxImageWidth.Text;
            String strHeight = textBoxImageHeight.Text;
            if(strWidth.Length==0 || strHeight.Length == 0)
            {
                textBoxDisplayResult.Text = "请输入自定义图像尺寸数值。";
                return;
            }

            if (!m_bIsIDCardLoaded)
            {
                textBoxDisplayResult.Text = "识别核心未加载，请先加载识别核心";
                return;
            }

            int nImgWidth = int.Parse(strWidth);
            if (nImgWidth <= 0)
            {
                textBoxDisplayResult.Text = "图像宽度参数不正确，请重新输入";
                return;

            }
            int nImgHeight = int.Parse(textBoxImageHeight.Text);
            if (nImgHeight <= 0)
            {
                textBoxDisplayResult.Text = "图像高度参数不正确，请重新输入";
                return;
            }
            if (lpSetUserDefinedImageSize(nImgWidth, nImgHeight))
            {
                textBoxDisplayResult.Text = "图像尺寸设置成功";
            }
            else
            {
                textBoxDisplayResult.Text = "图像尺寸设置失败";
            }

        }

        //图像分辨率设置
        private void btnSetImageResolution_Click(object sender, EventArgs e)
        {
            if (!m_bIsIDCardLoaded)
            {
                textBoxDisplayResult.Text = "识别核心未加载，请先加载识别核心";
                return;
            }
            String strResolution = textBoxHoriResolution.Text;
            if(strResolution.Length==0)
            {
                textBoxDisplayResult.Text = "请输入自定义图像的分辨率。";
                return;
            }
            int nResolutionX = int.Parse(strResolution);
            if (nResolutionX < 0)
            {
                textBoxDisplayResult.Text = "图像水平分辨率参数不正确，请重新输入";
                return;

            }
            int nResolutionY = nResolutionX;
            if (lpSetAcquireImageResolution(nResolutionX, nResolutionY))
            {
                textBoxDisplayResult.Text = "分辨率设置成功";
            }
            else
            {
                textBoxDisplayResult.Text = "分辨率设置失败";
            }

        }


        private void btnFreeKernal_Click(object sender, EventArgs e)
        {
            if (m_bIsIDCardLoaded)
            {
                lpFreeIDCard();
                m_bIsIDCardLoaded = false;
            }
            MyDll.FreeLibrary(m_handle);
            textBoxDisplayResult.Text = "成功释放核心。";
        }

        //采集图像并保存
        private void btnAcquireImage_Click(object sender, EventArgs e)
        {
            int nRet = lpAcquireImage(20);//20代表自定义尺寸，去拍照前注意先设置好尺寸，尺寸单位为1/1000英寸
            if (nRet != 0)
            {
                textBoxDisplayResult.Text = "返回值:";
                textBoxDisplayResult.Text += nRet.ToString();
                textBoxDisplayResult.Text += "\r\n";
                textBoxDisplayResult.Text += "采集图像失败";
            }

            //保存采集的图像
            String strRunPath = System.Windows.Forms.Application.StartupPath + "\\";
            String strImgPath = strRunPath + "test.jpg";
            nRet = lpSaveImage(strImgPath);
            if (nRet != 0)
            {
                MessageBox.Show("保存图像失败！");
            }
        }

        private void GetDeviceInfo()
        {
            if (!m_bIsIDCardLoaded)
            {
                textBoxDisplayResult.Text = "识别核心未加载，请先加载识别核心\r\n";
                return;
            }

            bool bRet = lpCheckDeviceOnlineEx();
            if (bRet)
            {
                textBoxDisplayResult.Text += "设备在线";
            }
            else
            {
                textBoxDisplayResult.Text += "设备不在线";
                return;
            }
            //获取设备序列号
            char[] cArrSN = new char[16];
            String strDeviceSN = new string('\0', 16);
            lpGetDeviceSN(strDeviceSN, 16);
            //获取设备名
            char[] cArrDeviceName = new char[128];
            String strDeviceName = new string('\0', 128);
            lpGetCurrentDevice(strDeviceName, 128);
            //获取开发包版本信息
            char[] cArrVersion = new char[128];
            String strVersion = new string('\0', 128);
            lpGetVersionInfo(strVersion, 128);

            int nLen = 0;
            //string strVersion = new String(cArrVersion);
            nLen = strVersion.LastIndexOf(" ");
            if (nLen > 0)
            {
                strVersion = strVersion.Substring(nLen);
            }
            nLen = strVersion.IndexOf("\0");
            if (nLen > 0)
            {
                strVersion = strVersion.Substring(0, nLen);
            }

            //string strDeviceName = new String(cArrDeviceName);
            nLen = strDeviceName.IndexOf("\0");
            if (nLen > 0)
            {
                strDeviceName = strDeviceName.Substring(0, nLen);
            }

            //string strDeviceSN = new String(cArrSN);
            nLen = strDeviceSN.IndexOf('\0');
            if (nLen > 0)
            {
                strDeviceSN = strDeviceSN.Substring(0, nLen);
            }
            
            this.Text = "扫描仪测试例_" + strVersion + "_" + strDeviceName + "(" + strDeviceSN + ")";
        }
    }
}

