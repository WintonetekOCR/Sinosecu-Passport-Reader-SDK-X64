// IDCard.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "IDCard.h"
#include "MainFrm.h"
#include "IDCardDoc.h"
#include "IDCardView.h"
#include "IDCardInfoView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#include<direct.h>

/////////////////////////////////////////////////////////////////////////////
// CIDCardApp



BEGIN_MESSAGE_MAP(CIDCardApp, CWinApp)
//{{AFX_MSG_MAP(CIDCardApp)
ON_COMMAND(ID_EDIT_IDCARDONE, OnEditIdcardone)
ON_COMMAND(ID_EDIT_IDCARDTWO, OnEditIdcardtwo)
ON_COMMAND(ID_FILE_HUIXIANG, OnFileHuixiang)
ON_COMMAND(ID_FILE_IDCARDTWOBACK, OnFileIdcardtwoback)
ON_COMMAND(ID_FILE_DRIVEPORT, OnFileDriveport)
ON_COMMAND(ID_FILE_PASSPORT, OnFilePassport)
ON_COMMAND(ID_FILE_QIANZHENG, OnFileQianzheng)
ON_COMMAND(ID_FILE_SCANRECO, OnFileScanreco)
ON_COMMAND(ID_FILE_XINGSHI, OnFileXingshi)
ON_COMMAND(ID_TEMP_TWO, OnTempTwo)
ON_COMMAND(IDC_FILE_JUNGUANZHENG, OnFileJunguanzheng)
ON_COMMAND(IDC_FILE_SHIBINGZHENG, OnFileShibingzheng)
ON_COMMAND(ID_FILE_FirmwareVersion, OnFILEFirmwareVersion)
ON_COMMAND(ID_FILE_GD_JUZHUZHENG_AVA6, OnFileGdJuzhuzheng)
ON_COMMAND(ID_FILE_DG_JUZHUZHENG_AVA6, OnFileDgJuzhuzheng)
ON_COMMAND(ID_FILE_SZ_JUZHUZHENG_AVA6, OnFileSzJuzhuzheng)
ON_COMMAND(ID_EDIT_IDCARDONE_AVA6, OnEditIdcardone)
ON_COMMAND(ID_EDIT_IDCARDTWO_AVA6, OnEditIdcardtwo)
ON_COMMAND(ID_FILE_HUIXIANG_AVA6, OnFileHuixiang)
ON_COMMAND(ID_FILE_IDCARDTWOBACK_AVA6, OnFileIdcardtwoback)
ON_COMMAND(ID_FILE_DRIVEPORT_AVA6, OnFileDriveport)
ON_COMMAND(ID_FILE_PASSPORT_AVA6, OnFilePassport)
ON_COMMAND(ID_FILE_QIANZHENG_AVA6, OnFileQianzheng)
ON_COMMAND(ID_FILE_SCANRECO_AVA6, OnFileScanreco)
ON_COMMAND(ID_FILE_XINGSHI_AVA6, OnFileXingshi)
ON_COMMAND(ID_TEMP_TWO_AVA6, OnTempTwo)
ON_COMMAND(ID_FILE_JUNGUANZHENG_AVA6, OnFileJunguanzheng)
ON_COMMAND(ID_FILE_SHIBINGZHENG_AVA6, OnFileShibingzheng)
ON_COMMAND(ID_FILE_SZ_JUZHUZHENG, OnFileSzJuzhuzheng)
ON_COMMAND(ID_FILE_GD_JUZHUZHENG, OnFileGdJuzhuzheng)
ON_COMMAND(ID_FILE_DG_JUZHUZHENG, OnFileDgJuzhuzheng)
ON_COMMAND(ID_FILE_BC, OnFileRecogBusinessCard)
ON_COMMAND(ID_FILE_BC_SCAN, OnFileRecogBusinessCard)
	//}}AFX_MSG_MAP
// Standard file based document commands
ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
// Standard print setup command
ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
//识别核心接口函数
int   (WINAPI *pLoad)(void);
void  (WINAPI *pFree)(void);
int(WINAPI *pScanRecogExAll)(LPCTSTR,IDCARD_ALL&,bool,int,int,char *,short);


int(WINAPI *pRecogIdcardOnlyALL)(LPCTSTR ,IDCARD_ALL & ,bool ,int ,int ,char*);
int(WINAPI *pRecogNewIdcardALL) ( LPTSTR , IDCARD_ALL& , bool , int , char* );
int(WINAPI *pRecogNewIdcardOnlyALL)(LPCTSTR ,IDCARD_ALL & ,bool,int,char* );
int(WINAPI *pRecogNewIdcardOnlyTempALL)(LPCTSTR ,IDCARD_ALL & ,bool ,int ,char* );
int(WINAPI *pScanImageEx)(char*, short);
int(WINAPI *pRecogDPALL)(LPTSTR,IDCARD_ALL &,bool,int,char*);
int(WINAPI *pRecogDPOnlyALL)(LPCTSTR,IDCARD_ALL &,bool,int,char*);
int(WINAPI *pRecogLaissezPasserALL)(LPTSTR ,IDCARD_ALL & ,bool , int ,char* );
int(WINAPI *pRecogLaissezPasserOnlyALL)(LPCTSTR,IDCARD_ALL &,bool,int,char*);
int(WINAPI *pRecogLicenseALL)(LPTSTR,IDCARD_ALL &,bool,char*);
int(WINAPI *pRecogLicenseOnlyALL)(LPCTSTR,IDCARD_ALL &,bool,char*);
int(WINAPI *pRecogVisaALL)(LPTSTR ,IDCARD_ALL & ,bool ,int ) ;
int(WINAPI *pRecogVisaOnlyALL)(LPTSTR , IDCARD_ALL & , bool , int);

//行驶证
int(WINAPI *pRecogVehicleLicenseEXALL)(LPTSTR,VEHICLELICENS_ALL & ,bool );
int(WINAPI *pRecogVehicleLicenseEXOnlyALL)(LPTSTR ,VEHICLELICENS_ALL & ,bool);

int(WINAPI *pRecogPassPortALL)(LPTSTR,IDCARD_ALL &,bool,int,char*);
int(WINAPI *pRecogPassPortOnlyALL)(LPCTSTR,IDCARD_ALL &,bool,int,char*);
int(WINAPI *pRecogNewIdBackALL)(LPTSTR,IDCARD_ALL &,bool);
int(WINAPI *pRecogNewIdBackOnlyALL)(LPCTSTR,IDCARD_ALL &,bool);
int(WINAPI *GetButtonDownType)(void);

int(WINAPI *pRecogNewIdcardTempALL)(LPTSTR, IDCARD_ALL&, bool, int, char* );

int(WINAPI *pRecogSoldieryCardALL)(LPTSTR ,IDCARD_ALL &,bool,int,char*);
int(WINAPI *pRecogSoldieryCardOnlyALL)(LPCTSTR,IDCARD_ALL &,bool,int,char*);
BOOL (WINAPI *pReadFirmwareVersionInfo)(LPTSTR,int);
char* (WINAPI *pGetVersionInfo)();
BOOL (WINAPI *pCheckWTScanner)(char* pScannerType);
//快证通阅读器接口函数
int(WINAPI *CVR_InitComm)(int);
int(WINAPI *CVR_Authenticate)(void);									           			    		
int(WINAPI *CVR_CloseComm)(void);

//居住证扫描识别 广东
int (WINAPI *pRecogGDResidencePermitAll)(LPTSTR, IDCARD_ALL&, bool ,char* );

//居住证对比识别 广东
int (WINAPI *pRecogGDResidencePermitOnlyAll)(LPCTSTR, IDCARD_ALL &, bool, char* );

//居住证扫描识别 东莞
int (WINAPI *pRecogDongGuanResidencePermitAll)(char*, IDCARD_ALL& , bool, char* );

//居住证对比识别 东莞
int (WINAPI *pRecogDongGuanResidencePermitOnlyAll)(char*, IDCARD_ALL& , bool, char* );

//居住证扫描对比 深圳
int (WINAPI *pRecogShenZhenResidencePermitAll)(char*, IDCARD_ALL&, bool, char*);

//居住证比对识别 深圳
int (WINAPI *pRecogShenZhenResidencePermitOnlyAll)(char*, IDCARD_ALL&, bool, char*);
//名片识别
int (WINAPI* lpfnRecogBusinessCardAll)(LPCTSTR,BCR_RESULT& );

int (WINAPI* lpfnRecogBusinessCardOnlyAll)(LPCTSTR,BCR_RESULT&);

UINT  CVReader(LPVOID lpParameter);// thread data
UINT  CVButtonReader(LPVOID lpParameter);// thread data

CIDCardApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CIDCardApp initialization

CIDCardApp::CIDCardApp()
{
	// TODO: add construction code here,
	m_strCurPath = GetWorkPath();
	m_LBtn = 0;
	m_RBtn = 0;
	ThreadExit = false;
	m_bLoaded = false;
	m_LStyeImage = 14;
	m_LStye = 0;
	bEnableFileScan = true;
	m_pReadContent = NULL;
	m_wndSplitWidth = 0;
	m_wndSplitHeigh = 0;
	Version = "";
	m_scale = 1;
	m_time = 1000;
	m_bCVRInitOK = false;
	WinTitle = _T("");
	Scanner = "0";
	Cameras = "1";

	// Place all significant initialization in InitInstance
}

BOOL CIDCardApp::InitInstance()
{
	AfxEnableControlContainer();
	
	LoadCOMConfig();
	// Standard initialization
	HANDLE hMutex=CreateMutex(NULL,	TRUE,"证件识别系统");  
	if(hMutex==NULL || GetLastError() == ERROR_ALREADY_EXISTS)  
	{  
	
		CloseHandle(hMutex);

 		CWnd*   IDcardhWnd  =  CWnd::FindWindow(NULL,WinTitle); //找到程序的上一个实例的句柄发按钮消息
		if(IDcardhWnd != NULL)
		{
			
			if(::IsIconic(IDcardhWnd->m_hWnd))
			{
				ShowWindow(IDcardhWnd->m_hWnd,SW_RESTORE);		
			}
			
			::SetForegroundWindow(IDcardhWnd->m_hWnd);
			
			if(theApp.DeviceType=="0")
			{			
				int nRet = m_MySti.GetButtonDownType();
				if (nRet==1||nRet==2)
				{ 	
					IDcardhWnd->PostMessage(WM_BTN_MESSAGE,nRet,NULL);
				}
			}	
		}		
        return FALSE; 
	}
	
	CString str = m_strCurPath + "\\picture";

	if(GetFileAttributes(str)!= FILE_ATTRIBUTE_DIRECTORY)
	{
		if (!CreateDirectory(str,NULL))
		{
			return FALSE;
		}
	}

	str = m_strCurPath + "\\TempPic";
	if(GetFileAttributes(str) != FILE_ATTRIBUTE_DIRECTORY)
	{
		if (!CreateDirectory(str,NULL))
		{
			return FALSE;
		}
	}
	//保留
	
	m_hMyDll=LoadLibrary(_T("idcarddll.dll"));	
	   
	if(m_hMyDll == NULL)
	{  
		MessageBox(NULL,"加载识别核心动态库失败!","证件识别系统",0); 
		m_bLoaded = false;
		return FALSE; 
	}
	   
	if(theApp.IDReader == "1")
	{
		m_CVRhMyDll=LoadLibrary("termb.dll");
		if(m_CVRhMyDll == NULL)
		{
			m_bLoaded = false;
			MessageBox(NULL,"加载阅读器动态库失败!","证件识别系统",0); 
			return FALSE; 
		}  
	 }
	   //获取接口地址
	   
	   pLoad          = (int  (WINAPI *)(void))GetProcAddress(m_hMyDll,"LoadIdcardLibrary");
	   pFree          = (void (WINAPI *)(void))GetProcAddress(m_hMyDll,"FreeIdcardLibrary");
	   
	   pScanRecogExAll            = (int (WINAPI *)(LPCTSTR,IDCARD_ALL&,bool,int,int,char *,short))GetProcAddress(theApp.m_hMyDll,"RecogIdcardExALL");
	   pRecogIdcardOnlyALL        = (int (WINAPI *)(LPCTSTR,IDCARD_ALL&,bool,int,int,char *))GetProcAddress(theApp.m_hMyDll,"RecogIdcardOnlyALL");
	   pRecogNewIdcardALL         = (int (WINAPI *) (LPTSTR , IDCARD_ALL& , bool , int , char* ))GetProcAddress(theApp.m_hMyDll,"RecogNewIdcardALL");
	   pRecogNewIdcardOnlyALL     = (int (WINAPI *)(LPCTSTR ,IDCARD_ALL & ,bool,int,char* ))GetProcAddress(theApp.m_hMyDll,"RecogNewIdcardOnlyALL");
	   pScanImageEx               = (int (WINAPI *)(char*, short))GetProcAddress(theApp.m_hMyDll,"ScanImageEx");
	   pRecogDPALL                = (int (WINAPI *)(LPTSTR,IDCARD_ALL &,bool,int,char*))GetProcAddress(theApp.m_hMyDll,"RecogDPALL");
	   pRecogDPOnlyALL            = (int (WINAPI *)(LPCTSTR,IDCARD_ALL &,bool,int,char*))GetProcAddress(theApp.m_hMyDll,"RecogDPOnlyALL");
	   pRecogLaissezPasserALL     = (int (WINAPI *)(LPTSTR ,IDCARD_ALL & ,bool , int ,char* ))GetProcAddress(theApp.m_hMyDll,"RecogLaissezPasserALL");
	   pRecogLaissezPasserOnlyALL = (int (WINAPI *)(LPCTSTR,IDCARD_ALL &,bool,int,char*))GetProcAddress(theApp.m_hMyDll,"RecogLaissezPasserOnlyALL");
	   pRecogLicenseALL           = (int (WINAPI *)(LPTSTR,IDCARD_ALL &,bool,char*))GetProcAddress(theApp.m_hMyDll,"RecogLicenseALL");
	   pRecogLicenseOnlyALL       = (int (WINAPI *)(LPCTSTR,IDCARD_ALL &,bool,char*))GetProcAddress(theApp.m_hMyDll,"RecogLicenseOnlyALL");
	   pRecogVisaALL              = (int (WINAPI *)(LPTSTR ,IDCARD_ALL & ,bool ,int ) )GetProcAddress(theApp.m_hMyDll,"RecogVisaALL");
	   pRecogVisaOnlyALL          = (int (WINAPI*) (LPTSTR , IDCARD_ALL & , bool , int ) )GetProcAddress(theApp.m_hMyDll,"RecogVisaOnlyALL");
	   //行驶证
	   pRecogVehicleLicenseEXALL  = (int (WINAPI *)(LPTSTR ,VEHICLELICENS_ALL & ,bool))GetProcAddress(theApp.m_hMyDll,"RecogVehicleLicenseEXALL");
	   pRecogVehicleLicenseEXOnlyALL = (int (WINAPI *)(LPTSTR ,VEHICLELICENS_ALL & ,bool))GetProcAddress(theApp.m_hMyDll,"RecogVehicleLicenseEXOnlyALL");
	  
	   pRecogPassPortALL          = (int (WINAPI *)(LPTSTR,IDCARD_ALL &,bool,int,char*))GetProcAddress(theApp.m_hMyDll,"RecogPassPortALL");
	   pRecogPassPortOnlyALL      = (int (WINAPI *)(LPCTSTR,IDCARD_ALL &,bool,int,char*))GetProcAddress(theApp.m_hMyDll,"RecogPassPortOnlyALL");
	   pRecogNewIdBackALL         = (int (WINAPI *)(LPTSTR,IDCARD_ALL &,bool))GetProcAddress(theApp.m_hMyDll,"RecogNewIdBackALL");
	   pRecogNewIdBackOnlyALL     = (int (WINAPI *)(LPCTSTR,IDCARD_ALL &,bool))GetProcAddress(theApp.m_hMyDll,"RecogNewIdBackOnlyALL");	
	   GetButtonDownType = (int (WINAPI *)(void))GetProcAddress(m_hMyDll,"GetButtonDownType");
	   pRecogNewIdcardOnlyTempALL = (int (WINAPI *)(LPCTSTR ,IDCARD_ALL & ,bool ,int ,char* ))GetProcAddress(theApp.m_hMyDll,"RecogNewIdcardOnlyTempALL");
       pRecogNewIdcardTempALL = (int (WINAPI *)(LPTSTR, IDCARD_ALL&, bool, int, char* ))GetProcAddress(theApp.m_hMyDll,"RecogNewIdcardTempALL");
	   pRecogSoldieryCardALL = (int (WINAPI *)(LPTSTR ,IDCARD_ALL &,bool,int,char*))GetProcAddress(theApp.m_hMyDll,"RecogSoldieryCardALL");
	   pRecogSoldieryCardOnlyALL= ( int (WINAPI *)(LPCTSTR,IDCARD_ALL &,bool,int,char*))GetProcAddress(theApp.m_hMyDll,"RecogSoldieryCardOnlyALL");

	   pReadFirmwareVersionInfo = (BOOL (WINAPI*)(LPTSTR,int))GetProcAddress(theApp.m_hMyDll,"ReadFirmwareVersionInfo");
	  //获取版本号
	   pGetVersionInfo = (char* (WINAPI *)())GetProcAddress(theApp.m_hMyDll,"GetVersionInfo");
	   pCheckWTScanner = (BOOL (WINAPI*)(char*))GetProcAddress(theApp.m_hMyDll,"CheckWTScanner");
	
	   //获取扫描居住证地址 广东 
	   pRecogGDResidencePermitAll = (int (WINAPI*)(LPTSTR , IDCARD_ALL&, bool ,char*))GetProcAddress(theApp.m_hMyDll,"RecogGDResidencePermitAll");
	
	   //获取对比居住证地址 广东
	   pRecogGDResidencePermitOnlyAll = (int (WINAPI*)(LPCTSTR , IDCARD_ALL&, bool ,char*))GetProcAddress(theApp.m_hMyDll,"RecogGDResidencePermitOnlyAll");

	   //获取扫描居住证地址 东莞
	   pRecogDongGuanResidencePermitAll = (int (WINAPI*)(char* ,IDCARD_ALL&, bool, char*))GetProcAddress(theApp.m_hMyDll, "RecogDongGuanResidencePermitAll");

	   //获取对比居住证地址 东莞
	   pRecogDongGuanResidencePermitOnlyAll = (int (WINAPI*)(char* ,IDCARD_ALL&, bool, char*))GetProcAddress(theApp.m_hMyDll, "RecogDongGuanResidencePermitOnlyAll");
	   
	   //获取扫描居住证地址 深圳
	   pRecogShenZhenResidencePermitAll = (int (WINAPI*)(char*, IDCARD_ALL&, bool, char*))GetProcAddress(theApp.m_hMyDll, "RecogShenZhenResidencePermitAll");
	   
	   //获取对比居住证地址 深圳	   
	   pRecogShenZhenResidencePermitOnlyAll= (int (WINAPI*)(char*, IDCARD_ALL&, bool, char*))GetProcAddress(theApp.m_hMyDll,"RecogShenZhenResidencePermitOnlyAll");
       
		 //名片识别
	   lpfnRecogBusinessCardOnlyAll = (int(WINAPI*)(LPCTSTR,BCR_RESULT&))GetProcAddress(m_hMyDll,_T("RecogBusinessCardOnlyAll"));
	   lpfnRecogBusinessCardAll = (int(WINAPI*)(LPCTSTR,BCR_RESULT&))GetProcAddress(m_hMyDll,_T("RecogBusinessCardAll"));
      
 	   if(pRecogSoldieryCardALL == NULL || pRecogSoldieryCardOnlyALL == NULL
 		   || pLoad == NULL || pFree == NULL ||pScanRecogExAll == NULL 
  		   || GetButtonDownType == NULL || pRecogNewIdBackALL== NULL
 		   || pRecogDPALL == NULL || pRecogNewIdcardALL == NULL 
  		   || pRecogPassPortALL == NULL|| pScanImageEx == NULL
  		   || pRecogLicenseALL== NULL||pRecogLaissezPasserALL== NULL
  		   || pRecogIdcardOnlyALL == NULL || pRecogDPOnlyALL == NULL 
   		   || pRecogNewIdcardOnlyALL == NULL ||pRecogNewIdBackOnlyALL == NULL 
		   || pRecogLicenseOnlyALL == NULL || pRecogPassPortOnlyALL == NULL
		   || pRecogNewIdBackOnlyALL == NULL||pRecogLaissezPasserOnlyALL == NULL 
		   || pRecogVehicleLicenseEXOnlyALL== NULL||pRecogVehicleLicenseEXALL== NULL
 		   || pRecogGDResidencePermitAll == NULL || pRecogGDResidencePermitOnlyAll == NULL
 		   || pRecogDongGuanResidencePermitAll == NULL || pRecogDongGuanResidencePermitOnlyAll == NULL
 		   || pRecogShenZhenResidencePermitAll == NULL || pRecogShenZhenResidencePermitOnlyAll == NULL
		   ||lpfnRecogBusinessCardAll==NULL||lpfnRecogBusinessCardOnlyAll==NULL)
	   {
		   //卸载动态库
		   FreeLibrary(m_hMyDll);
		   MessageBox(NULL,"加载识别动态库失败!","证件识别系统",0); 
		   return FALSE; 
	   } 
	   
	   if(theApp.IDReader == "1")
	   {
		   CVR_InitComm       = (int (WINAPI *)(int))GetProcAddress(m_CVRhMyDll,"CVR_InitComm");
		   CVR_Authenticate   = (int (WINAPI *)(void))GetProcAddress(m_CVRhMyDll,"CVR_Authenticate");
		   m_pReadContent     = (int (WINAPI *)(int))GetProcAddress(m_CVRhMyDll,"CVR_Read_Content");
		   CVR_CloseComm      = (int (WINAPI *)(void))GetProcAddress(m_CVRhMyDll,"CVR_CloseComm");
		   
		   if(CVR_InitComm == NULL || CVR_CloseComm == NULL || CVR_Authenticate == NULL || m_pReadContent == NULL)
		   {  
			   FreeLibrary(m_hMyDll);
			   FreeLibrary(m_CVRhMyDll);	   
			   MessageBox(NULL,"加载读卡动态库失败!","证件识别系统",0); 
			   return FALSE; 	   
		   }			
	   }
	   //加载识别核心 
	   if( pLoad()!=0 )
	   {   
		   MessageBox(NULL,"加载识别核心失败!","证件识别系统",0); 
		   AfxMessageBox(_T("请检查设备连接是否正确!"));
		   //卸载动态库
		   FreeLibrary(m_hMyDll);
		   m_bLoaded = false;
		   return FALSE; 
	   }
	   else
	   {
		   m_bLoaded = true;		   
	   }

	   m_VecStr.clear(); 
	   //其初始化作用
	   if(theApp.DeviceType==theApp.Scanner)
	   {
		   AVA6Sti();
	   }
	   
	   if(theApp.IDReader == "1")
	   {
		   CVRFun();
	   }
	   // If you are not using these features and wish to reduce the size
	   //  of your final executable, you should remove from the following
	   //  the specific initialization routines you do not need.
	   
#ifdef _AFXDLL
	   Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	   Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
	   // Change the registry key under which our settings are stored.
	   // TODO: You should modify this string to be something appropriate
	   // such as the name of your company or organization.
	   SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	   
	   LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	   
	   // Register the application's document templates.  Document templates
	   //  serve as the connection between documents, frame windows and views.
	   CSingleDocTemplate* pDocTemplate;
	   pDocTemplate = new CSingleDocTemplate(
		   IDR_MAINFRAME,
		   RUNTIME_CLASS(CIDCardDoc),
		   RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		   RUNTIME_CLASS(CIDCardImageView));
	   AddDocTemplate(pDocTemplate);	
	   // Parse command line for standard shell commands, DDE, file open
	   CCommandLineInfo cmdInfo;
	   ParseCommandLine(cmdInfo);
	   // Dispatch commands specified on the command line
	   if (!ProcessShellCommand(cmdInfo))
		   return FALSE;
	   if(Version==_T(""))
	      Version = pGetVersionInfo(); 
	 
	   if(WinTitle.GetLength()>0)
	       m_pMainWnd->SetWindowText(WinTitle);
	   else
		   m_pMainWnd->SetWindowText(_T("证件识别系统"));

	   // The one and only window has been initialized, so show and update it.
	   m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);
	   m_pMainWnd->UpdateWindow(); 
	   
	   return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	
	// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	
	// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
//{{AFX_MSG_MAP(CAboutDlg)
// No message handlers
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIDCardApp message handlers

int CIDCardApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class	
	ThreadExit =true;//使阅读器线程退出
    Sleep(100);
	if(theApp.DeviceType == theApp.Scanner)
	{
		m_MySti.EndSTI();
	}
	if (m_bCVRInitOK==1)
	{
		 CVR_CloseComm();
	}
	
	if(m_bLoaded == true)
	{   
		m_bLoaded =false;
		pFree();
		if(m_hMyDll != NULL)
		{
			FreeLibrary(m_hMyDll);
		}
		
		if(theApp.DeviceType == theApp.Cameras )
		{
			if(m_CVRhMyDll != NULL)
			{
				FreeLibrary(m_CVRhMyDll);
			}		
		}
		
	}	
	
	return CWinApp::ExitInstance();
}

void CIDCardApp::LoadCOMConfig(void)
{
	CStdioFile myFile;
	TCHAR lpszTmp[MAX_PATH];
	CString strCurrPath = m_strCurPath;
	strCurrPath += _T("versionConfig.ini");
	_tcscpy(lpszTmp,_T(""));
    //读取显示标题
    GetPrivateProfileString(_T("PROPERTY"),_T("Title"),_T(""),lpszTmp,MAX_PATH,strCurrPath);
     if(_tcslen(lpszTmp)>0)
	 {
		 WinTitle = lpszTmp;
	 }
	 else
	 {
		 WinTitle = _T("证件识别系统");
	 }
	_tcscpy(lpszTmp,_T(""));
	
	//读取设备类型
	 TCHAR DevicesType_tmp[MAX_PATH];
	 _tcscpy(DevicesType_tmp,_T(""));
	 GetPrivateProfileString(_T("PROPERTY"), _T("DeviceType"), _T(""), DevicesType_tmp,MAX_PATH, strCurrPath );
	 if(_tcslen(DevicesType_tmp)>0)
	 {
		 DeviceType = DevicesType_tmp;
	 }
	


	//读取设备名称
	TCHAR Devicesname_tmp[MAX_PATH];
	_tcscpy(Devicesname_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("DeviceName"), _T(""), Devicesname_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(Devicesname_tmp)>0)
	{
		DeviceName = Devicesname_tmp;
	}


	//读取软件版本
	TCHAR Version_tmp[MAX_PATH];
	_tcscpy(Version_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("Version"), _T(""), Version_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(Version_tmp)>0)
	{
		Version = Version_tmp;
	}



	//读取帮助文档
	TCHAR Help_tmp[MAX_PATH];
	_tcscpy(Help_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("DeviceHelp"), _T(""), Help_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(Help_tmp)>0)
	{
		DeviceHelp = Help_tmp;
	}
	
	//读取背景图片
	TCHAR BgImage_tmp[MAX_PATH];
	_tcscpy(BgImage_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("BgImage"), _T(""), BgImage_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(BgImage_tmp)>0)
	{
		BgImage = BgImage_tmp;
	}
	
	//读取其他图片
	TCHAR AdImage_tmp[MAX_PATH];
	_tcscpy(AdImage_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("AdImage"), _T(""), AdImage_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(AdImage_tmp)>0)
	{
		AdImage = AdImage_tmp;
	}

	//读取读卡器信息
	TCHAR IDReader_tmp[MAX_PATH];
	_tcscpy(IDReader_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("IDReader"), _T(""), IDReader_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(IDReader_tmp)>0)
	{
		IDReader = IDReader_tmp;
	}


}

CString CIDCardApp::GetWorkPath(void)
{
	CString  sWorkPath , strTemp;
	sWorkPath.Empty();
	strTemp.Empty();
	int nRet = 0,nErrorCode = 0;
	nRet = GetModuleFileName(NULL,sWorkPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	if(0 == nRet)
    {
		nErrorCode = GetLastError();
		strTemp.Format("获取当前目录出现错误，错误代码为%d",nErrorCode);	
		MessageBox(NULL,strTemp,"证件识别系统",0); 
	}
	sWorkPath.ReleaseBuffer();
	int nPos;
	nPos=sWorkPath.ReverseFind ('\\');
	if(nPos!=-1)  
		sWorkPath=sWorkPath.Left (nPos+1); 
	else  
		sWorkPath.Empty();
	return sWorkPath;
}

void CIDCardApp::AVA6Sti()
{	

	   CMainFrame* pFrame = (CMainFrame*)(this->m_pMainWnd);
	   m_MySti.StartSTI();
	   int nRet = m_MySti.GetButtonDownType();

	   if( nRet == 1 ) 	
	   {
		   SendMessage(pFrame->m_hWnd,WM_BTN_MESSAGE,nRet,0);		
	   }	   	   
}

void CIDCardApp::CVRFun()
{ 
	if(!m_bLoaded)
	{
		return;
	}
// 	int iRetUSB=0,iRetCOM=0;
//     int iPort;
// 	bool flag = false;
// 	
// 	for (iPort=1001; iPort<=1016; iPort++)
// 	{
// 		iRetUSB=CVR_InitComm(iPort);
// 		if (iRetUSB==1)
// 		{   
// 			flag = true;
// 			break;
// 		}
// 	}

//     if(!flag)
// 	{
// 		
// 		CMainFrame* pFrame = (CMainFrame*)(this->m_pMainWnd);
// 		CWinThread* pThread = AfxBeginThread (CVButtonReader, pFrame,
// 		THREAD_PRIORITY_NORMAL, 0, 0,NULL); 
// 	}
// 	else
// 	{
// 		CMainFrame* pFrame = (CMainFrame*)(this->m_pMainWnd);
// 		CWinThread* pThread = AfxBeginThread (CVReader, pFrame,
// 		THREAD_PRIORITY_NORMAL, 0, 0,NULL);   
// 	}
//////////////////////////////////////////////////////////////////////////
	//初始化读卡器连接
 	for (int iPort=1001; iPort<=1016; iPort++)
 	{
 		if (1==CVR_InitComm(iPort))
 		{   
//			AfxMessageBox("OK");
 			m_bCVRInitOK = true;
 			break;
 		}
 	}

}


UINT CVButtonReader(LPVOID lpParameter)
{
	CMainFrame *pMainFrame;
    pMainFrame  = (CMainFrame *) lpParameter;	
    short nType=0;
	while(!theApp.ThreadExit && theApp.m_bLoaded == true)
	{		
		nType = GetButtonDownType();
		if(nType!=0)
		{		//PostMessage
			pMainFrame->SendMessage(WM_BTN_MESSAGE,nType,0);
			Sleep(0);
			nType = 0;			
		}		
	}
	AfxEndThread(0);
	return 0;	
}

UINT CVReader(LPVOID lpParameter)
{	
	CMainFrame *pMainFrame;
    pMainFrame  = (CMainFrame *) lpParameter;	
    short nType=0;
	while(!theApp.ThreadExit && theApp.m_bLoaded == true)
	{				
// 		if (1==CVR_Authenticate())
// 		{
// 			nType = GetButtonDownType();
// 			if(nType!=0)
// 			{		//PostMessage
// 				pMainFrame->SendMessage(WM_BTN_MESSAGE,nType,0);
// 				Sleep(0);
// 				nType = 0;			
// 			}
// 			//向主框架发送读卡消息			
// 			pMainFrame->SendMessage(WM_MY_MESSAGE,0,0); 
// 			Sleep(0);
// 		}

		nType = GetButtonDownType();
		if(nType!=0)
		{		//PostMessage
			pMainFrame->SendMessage(WM_BTN_MESSAGE,nType,0);
			Sleep(0);
			nType = 0;			
		}
		if (1==CVR_Authenticate())
		{
			//向主框架发送读卡消息			
			pMainFrame->SendMessage(WM_MY_MESSAGE,0,0); 
			Sleep(0);
		}
		

	}
    CVR_CloseComm();
	AfxEndThread(0);
	return 0;	
}

void CIDCardApp::OnEditIdcardone() 
{ //一代证扫描识别
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
		
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
	CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	

	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";
	
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideIdcardTwoInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();
    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showInfoDlg();

	
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	int result = pScanRecogExAll(file_name.GetBuffer(file_name.GetLength()),card,true,0,63,head_name.GetBuffer(head_name.GetLength()),3);
	
	file_name.Replace("TempPic","picture");
	head_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	if(result == 0)
	{   
		pView->m_InfoDlg.m_name      = card.name;	//名字
		pView->m_InfoDlg.m_sex       = card.sex;	//性别
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;	//出生日期
		pView->m_InfoDlg.m_address   = card.address;	
		pView->m_InfoDlg.m_signdate  = card.signdate;	//签发期
		pView->m_InfoDlg.m_validdate = card.validterm;	//有效期
		pView->m_InfoDlg.m_id        = card.number;	//
		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{		
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
		
	}
	else if(result == 2)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
	}
	else if(result == 3)
	{   
		
       	MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
	
}

//一代身份证导入识别
void  CIDCardApp::Idcardone(CString  &file_name) 
{   
	if(!m_bLoaded)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
    pFrame->m_wndSplitter.RecalcLayout();  
	
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";

	
// 	pView->HidePassPortInfo();
//     pView->HideIdcardTwoInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();
	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showInfoDlg();
	//pView->m_InfoDlg.UpdateData(false);
	


	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	CopyFile(file_name, strAppPath, FALSE);   // 拷贝文件	
	int result = pRecogIdcardOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,0,63,head_name.GetBuffer(head_name.GetLength()));
	::DeleteFile(strAppPath);
	
	if(result == 0)
	{
		pView->m_InfoDlg.m_sError = "";
		pView->m_InfoDlg.m_name      = card.name;
		pView->m_InfoDlg.m_sex       = card.sex;
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;
		pView->m_InfoDlg.m_address   = card.address;
		pView->m_InfoDlg.m_signdate  = card.signdate;
		pView->m_InfoDlg.m_validdate = card.validterm;
		pView->m_InfoDlg.m_id        = card.number;	
		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;

		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	}
	else if(result == 1) //
		
	{
		pView->m_InfoDlg.m_sError = "用户输入的文件名不存在!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
		
	}
	else if(result == 2)
	{
		pView->m_InfoDlg.m_sError = "打开文件失败!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 3)
	{
		pView->m_InfoDlg.m_sError = "识别失败!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
}
// 二代身份证扫描识别
void CIDCardApp::OnEditIdcardtwo() 
{
	// TODO: Add your command handler code here
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
    m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();   
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	
	//清除原有数据
	pView->m_IdcardTwoInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";

	
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HidInfoDlg();
// 	pView->HideVLInfo();
	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showIdcardTwoInfo();
	
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	int result = pRecogNewIdcardALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	
	file_name.Replace("TempPic","picture");
    head_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	if(result == 0)
	{
		pView->m_IdcardTwoInfo.m_sError = "";
		pView->m_IdcardTwoInfo.m_name      = card.name;
		pView->m_IdcardTwoInfo.m_sex       = card.sex;
		pView->m_IdcardTwoInfo.m_nation    = card.people;
		pView->m_IdcardTwoInfo.m_birthdate = card.birthday;
		pView->m_IdcardTwoInfo.m_address   = card.address;
		pView->m_IdcardTwoInfo.m_id        = card.number;
		pView->m_IdcardTwoInfo.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		
		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0);
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
        pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
	} 
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证识别系统",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();

	
}

//二代身份证导入识别
void CIDCardApp::Idcardtwo(CString &file_name) 
{ 
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	//清除原有数据
	pView->m_IdcardTwoInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";
	

	//显示需要的Dlg  隐藏不需要的Dlg
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HidInfoDlg();
// 	pView->HideVLInfo();
	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showIdcardTwoInfo();
	
	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
    CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	int result = pRecogNewIdcardOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	::DeleteFile(strAppPath);
	pView->m_InfoDlg.drawPic();
	if(result == 0)
	{   
		pView->m_IdcardTwoInfo.m_name      = card.name;
		pView->m_IdcardTwoInfo.m_sex       = card.sex;
		pView->m_IdcardTwoInfo.m_nation    = card.people;
		pView->m_IdcardTwoInfo.m_birthdate = card.birthday;
		pView->m_IdcardTwoInfo.m_address   = card.address;
		pView->m_IdcardTwoInfo.m_id        = card.number;
		pView->m_IdcardTwoInfo.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;

		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	

	}
	else if(result == 1) //
		
	{
		pView->m_IdcardTwoInfo.m_sError = "用户输入的文件名不存在!";
		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	}
	else if(result == 2)
	{
		pView->m_IdcardTwoInfo.m_sError = "打开文件失败!";
		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 3)
	{
		pView->m_IdcardTwoInfo.m_sError = "识别失败!";
		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
        pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);		
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
}	  	  			
//回乡证扫描
void CIDCardApp::OnFileHuixiang() 
{

	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	
// 	pView->HideIdcardTwoInfo();
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();

    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showInfoDlg();
	
	
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	int result = pRecogLaissezPasserALL(file_name.GetBuffer(file_name.GetLength()),card,true,63,head_name.GetBuffer(head_name.GetLength()) );
	
	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	
	if(result == 0)
	{   
		pView->m_InfoDlg.m_sError = "";
		pView->m_InfoDlg.m_name      = card.name;
		pView->m_InfoDlg.m_sex       = card.sex;
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;
		pView->m_InfoDlg.m_address   = card.address;
		pView->m_InfoDlg.m_signdate  = card.signdate;
		pView->m_InfoDlg.m_validdate = card.validterm;
		pView->m_InfoDlg.m_id        = card.number;
		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
		
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}

void CIDCardApp::Huixiang(CString &file_name) 
{//回乡证图像导入识别
	if(!m_bLoaded)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
   	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
// 	pView->HideIdcardTwoInfo();
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();
	pView->HideAllDialog();
	pViewImage->showDlgImage();

	pView->showInfoDlg();
	//pView->m_InfoDlg.UpdateData(false);
	
	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	   CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	   CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	   int result = pRecogLaissezPasserOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,63,head_name.GetBuffer(head_name.GetLength()) );
	   ::DeleteFile(strAppPath);
	   if(result == 0)
	   { 
		   pView->m_InfoDlg.m_sError = "";
		   pView->m_InfoDlg.m_name      = card.name;
		   pView->m_InfoDlg.m_sex       = card.sex;
		   pView->m_InfoDlg.m_nation    = card.people;
		   pView->m_InfoDlg.m_birthdate = card.birthday;
		   pView->m_InfoDlg.m_address   = card.address;
		   pView->m_InfoDlg.m_signdate  = card.signdate;
		   pView->m_InfoDlg.m_validdate = card.validterm;
		   pView->m_InfoDlg.m_id        = card.number;	
		   pView->m_InfoDlg.m_headFilePath = head_name;
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_InfoDlg.m_sError = "用户输入的文件名不存在!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
		   
	   }
	   else if(result == 2)
	   {
		   pView->m_InfoDlg.m_sError = "打开文件失败!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_InfoDlg.m_sError = "识别失败!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();	
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
}
//二代证背面扫描识别
void CIDCardApp::OnFileIdcardtwoback() 
{
	// TODO: Add your command handler code here
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
    m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
   	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_IdcardBackInfo.m_signdate      = "";
	pView->m_IdcardBackInfo.m_signoffice     =  "";
	pView->m_IdcardBackInfo.m_sError = "";
    pViewImage->m_DlgImage.m_ImageFilePath = "";
	
// 	pView->HidInfoDlg();
//     pView->HidePassPortInfo();
// 	pView->HideIdcardTwoInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();

	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showIdcardBackInfo();

	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	   
	file_name = strAppPath;
	head_name = "";
	int result = pRecogNewIdBackALL(file_name.GetBuffer(file_name.GetLength()),card,true);
	
	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	
	if(result == 0)
	{   
		
		pView->m_IdcardBackInfo.m_signdate      = card.number;
        pView->m_IdcardBackInfo.m_signoffice     =  card.address;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		pView->m_IdcardBackInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
		
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_IdcardBackInfo.UpdateData(FALSE);
		pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();

}


void CIDCardApp::Idcardtwoback(CString  &file_name) 
{//二代证背面图像导入识别
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return; 
	} 
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
   	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_IdcardBackInfo.m_sError = "";
	pView->m_IdcardBackInfo.m_signdate      = "";
	pView->m_IdcardBackInfo.m_signoffice     = "";
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
// 	pView->HidInfoDlg();
//     pView->HidePassPortInfo();
// 	pView->HideIdcardTwoInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();
    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showIdcardBackInfo();

	
	CString head_name;
	IDCARD_ALL card;
	head_name = "";
	
	   CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	   CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	   int result = pRecogNewIdBackOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true);
	   ::DeleteFile(strAppPath);
	   if(result == 0)
	   {
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_IdcardBackInfo.m_sError = "";
		   pView->m_IdcardBackInfo.m_signdate      = card.number;
		   pView->m_IdcardBackInfo.m_signoffice     =  card.address;
		   pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardBackInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_IdcardBackInfo.m_sError = "用户输入的文件名不存在!";
		   pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardBackInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   else if(result == 2)
	   {
		   pView->m_IdcardBackInfo.m_sError = "打开文件失败!";
		   pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardBackInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 3)
	   {
		   pView->m_IdcardBackInfo.m_sError = "识别失败!";
		   pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardBackInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
	   
}
//驾驶证扫描识别
void CIDCardApp::OnFileDriveport() 
{

	// TODO: Add your command handler code here

	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
    m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  

	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
// 	pView->HideIdcardTwoInfo();
//     pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();
	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showInfoDlg();

	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	   
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	int result =  pRecogDPALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	if(result == 0)
	{
		pView->m_InfoDlg.m_sError = "";

		pView->m_InfoDlg.m_name      = card.name;	//姓名
		pView->m_InfoDlg.m_sex       = card.sex;	//性别
		pView->m_InfoDlg.m_nation    = card.people;    //民族 现为空
		pView->m_InfoDlg.m_birthdate = card.birthday;	//出生日期
		pView->m_InfoDlg.m_address   = card.address;	//住址
		pView->m_InfoDlg.m_signdate  = card.signdate;   //签发日期 现为空
		pView->m_InfoDlg.m_validdate = card.validterm;	//有效期 现为空
		pView->m_InfoDlg.m_id        = card.number;	//证件号

		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}	
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
		
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
	}
	else if(result == 3)
	{
	       MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	   	   
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();

}

void CIDCardApp::FileDriveport(CString &file_name)
{//驾驶证图像导入识别
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	

	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
	pView->HideIdcardTwoInfo();
	pView->HidePassPortInfo();
	pView->HideIdcardBackInfo();
	pView->HideResidentInfo();
		pView->HideVLInfo();
	pViewImage->showDlgImage();
	pView->showInfoDlg();
	//pView->m_InfoDlg.UpdateData(false);
	
	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	   CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	   CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	   int result = pRecogDPOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	   ::DeleteFile(strAppPath);
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
	   if(result == 0)
	   {
		   pView->m_InfoDlg.m_sError = "";

		pView->m_InfoDlg.m_name      = card.name;	//姓名
		pView->m_InfoDlg.m_sex       = card.sex;	//性别
		pView->m_InfoDlg.m_nation    = card.people;    //民族 现为空
		pView->m_InfoDlg.m_birthdate = card.birthday;	//出生日期
		pView->m_InfoDlg.m_address   = card.address;	//住址
		pView->m_InfoDlg.m_signdate  = card.signdate;   //签发日期 现为空
		pView->m_InfoDlg.m_validdate = card.validterm;	//有效期 现为空
		pView->m_InfoDlg.m_id        = card.number;	//证件号
		   
		   pView->m_InfoDlg.m_headFilePath = head_name;
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_InfoDlg.m_sError = "用户输入的文件名不存在!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   else if(result == 2)
	   {
		   pView->m_InfoDlg.m_sError = "打开文件失败!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_InfoDlg.m_sError = "识别失败!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();	
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
}

//护照扫描识别
void CIDCardApp::OnFilePassport() 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
   	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	
	pView->m_PassPortInfo.DelLegacyData();
    pViewImage->m_DlgImage.m_ImageFilePath = "";
	
// 	pView->HideIdcardTwoInfo();
// 	pView->HidInfoDlg();
// 	pView->HideIdcardBackInfo();
// 	pView->HideVLInfo();
// 	pView->HideResidentInfo();

    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showPassPortInfo();
   	
	
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name = "",head_name = "";
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	//  result 接口调用返回值 
	int result = pRecogPassPortALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	
	if(result == 0)
	{   

			pView->m_PassPortInfo.m_sError = "";
	  
			if(card.name[0]>= 'A' && card.name[0]<= 'z' )  //检测名字是不是英文的
			{
				pView->m_PassPortInfo.m_name_en = card.name; //如果是  就直接赋给英文名
			}
			else
			{
				pView->m_PassPortInfo.m_name = card.name;  // 不是 就给中文名
			}
			
			if( pView->m_PassPortInfo.m_name.Find(';') != -1)
			{
				// 从名字当中提取英文
				pView->m_PassPortInfo.m_name_en = pView->m_PassPortInfo.m_name.Mid(pView->m_PassPortInfo.m_name.Find(';')+1,pView->m_PassPortInfo.m_name.GetLength() - pView->m_PassPortInfo.m_name.Find(';') -1);
				//名字中提取中文
				pView->m_PassPortInfo.m_name = pView->m_PassPortInfo.m_name.Mid(0,pView->m_PassPortInfo.m_name.Find(';'));
				
			}
			
			
			CString str = card.people;   //people 出生地；签发地
			
 			int birthplace = str.Find(';');
 			int plaseissue = str.GetLength();
			
			
			pView->m_PassPortInfo.m_birthplace = str.Mid(0,birthplace);	// 出生地
			pView->m_PassPortInfo.m_plaseissue = str.Mid(birthplace+1,plaseissue);	// 签发地
			
			pView->m_PassPortInfo.m_sex       = card.sex;	// 性别
			pView->m_PassPortInfo.m_dateissue = card.validterm; //  签发日期
			pView->m_PassPortInfo.m_birthdate = card.birthday;	//出生日期	pView->m_PassPortInfo.m_dateissue = card.validterm; //  签发日期
			pView->m_PassPortInfo.m_signdate  = card.signdate;  //  有效日期
			pView->m_PassPortInfo.m_number    = card.number;	//  证件号

			CString Tepmstr = 	card.address;	//address  签发国；机读码第一行；机读码第二行
			int temp = 3;
			temp = Tepmstr.Find(';');

			pView->m_PassPortInfo.m_native    = Tepmstr.Left(temp);	// 国籍

			pView->m_PassPortInfo.m_code = Tepmstr.Right(Tepmstr.GetLength()-temp);	//机读码
			pView->m_PassPortInfo.m_code.Replace(";","\r\n");

			//显示台胞证的身份证号码
			if (_tcscmp(card.other,_T("T"))==0)
			{
				pView->m_PassPortInfo.m_strOther = card.people;
			}

			pView->m_PassPortInfo.m_headFilePath = head_name;  //文件头名字
			pViewImage->m_DlgImage.m_ImageFilePath = file_name;	//文件名


			pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
			pView->m_PassPortInfo.UpdateData(FALSE);	//编辑框显示内容
			pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	
	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_PassPortInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}

//护照比对识别
void CIDCardApp::Passport(CString  &file_name) 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();	
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	
	pView->m_PassPortInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
//     pView->HideIdcardTwoInfo();
// 	pView->HidInfoDlg();
// 	pView->HideIdcardBackInfo();
// 	pView->HideVLInfo();
// 	pView->HideResidentInfo();

    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showPassPortInfo();
	
	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	   CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	   CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	   int result = pRecogPassPortOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	   ::DeleteFile(strAppPath);
	   if(result == 0)
	   {
		   pView->m_PassPortInfo.m_sError = "";
		   
		   if(card.name[0]>= 'A' && card.name[0]<= 'z' )  //检测名字是不是英文的
		   {
			   pView->m_PassPortInfo.m_name_en = card.name; //如果是  就直接赋给英文名
		   }
		   else
		   {
			   pView->m_PassPortInfo.m_name = card.name;  // 不是 就给中文名
		   }
		   
		   if( pView->m_PassPortInfo.m_name.Find(';') != -1)
		   {
			   // 从名字当中提取英文
			   pView->m_PassPortInfo.m_name_en = pView->m_PassPortInfo.m_name.Mid(pView->m_PassPortInfo.m_name.Find(';')+1,pView->m_PassPortInfo.m_name.GetLength() - pView->m_PassPortInfo.m_name.Find(';') -1);
			   //名字中提取中文
			   pView->m_PassPortInfo.m_name = pView->m_PassPortInfo.m_name.Mid(0,pView->m_PassPortInfo.m_name.Find(';'));
			   
		   }
		   
		   
		   CString str = card.people;   //people 出生地；签发地
		   
		   int birthplace = str.Find(';');
		   int plaseissue = str.GetLength();
		   
		   
		   pView->m_PassPortInfo.m_birthplace = str.Mid(0,birthplace);	// 出生地
		   pView->m_PassPortInfo.m_plaseissue = str.Mid(birthplace+1,plaseissue);	// 签发地
		   
		   
		   
		   pView->m_PassPortInfo.m_sex       = card.sex;	// 性别 
		   pView->m_PassPortInfo.m_birthdate = card.birthday;	//出生日期
		   pView->m_PassPortInfo.m_dateissue = card.validterm; //  签发日期
		   pView->m_PassPortInfo.m_signdate  = card.signdate;  //  有效日期
		   pView->m_PassPortInfo.m_number    = card.number;	//  证件号
		   
		   CString Tepmstr = 	card.address;	//address  签发国；机读码第一行；机读码第二行
		   int temp = 3;
		   temp = Tepmstr.Find(';');
		   
		   pView->m_PassPortInfo.m_native    = Tepmstr.Left(temp);	// 国籍
		   
		   pView->m_PassPortInfo.m_code = Tepmstr.Right(Tepmstr.GetLength()-temp);	//机读码
		   pView->m_PassPortInfo.m_code.Replace(";","\r\n");
		   //显示台胞证的身份证号码
		   if (_tcscmp(card.other,_T("T"))==0)
		   {
			   pView->m_PassPortInfo.m_strOther = card.people;
		   }
		   pView->m_PassPortInfo.m_headFilePath = head_name;  //文件头名字
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;	//文件名
		  
		   pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_PassPortInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_PassPortInfo.m_sError = "用户输入的文件名不存在!";
		   pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_PassPortInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   else if(result == 2)
	   {
		   pView->m_PassPortInfo.m_sError = "打开文件失败!";
		   pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_PassPortInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_PassPortInfo.m_sError = "识别失败!";
		   pView->m_PassPortInfo.InvalidateRect(NULL,TRUE);  
		   pView->m_PassPortInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);			
	   }
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
}

//签证扫描识别
void CIDCardApp::OnFileQianzheng() 
{
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
//     pView->HideIdcardTwoInfo();
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideVLInfo();
// 	pView->HideResidentInfo();

    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showInfoDlg();
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	   
	file_name = strAppPath;
    head_name = "";
	
	int result = pRecogVisaALL(file_name.GetBuffer(file_name.GetLength()),card,true,63);
	file_name.Replace("TempPic","picture");
	head_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	if(result == 0)
	{   
		pView->m_InfoDlg.m_name      = card.name;
		pView->m_InfoDlg.m_sex       = card.sex;
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;
		pView->m_InfoDlg.m_address   = card.address;
		pView->m_InfoDlg.m_signdate  = card.signdate;
		pView->m_InfoDlg.m_validdate = card.validterm;
		pView->m_InfoDlg.m_id        = card.number;
		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
		
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
		
	
}
//签证图像导入识别
void CIDCardApp::Qianzheng(CString  &file_name) 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";

	
// 	pView->HideIdcardTwoInfo();
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideVLInfo();
// 	pView->HideResidentInfo();

	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showInfoDlg();
	
	CString head_name;
	IDCARD_ALL card;
	head_name = "";
	
	   CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	   CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	   int result = pRecogVisaOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,63);
	   ::DeleteFile(strAppPath);

	   if(result == 0)
	   {
		   pView->m_InfoDlg.m_sError = "";
		   pView->m_InfoDlg.m_name      = card.name;
		   pView->m_InfoDlg.m_sex       = card.sex;
		   pView->m_InfoDlg.m_nation    = card.people;
		   pView->m_InfoDlg.m_birthdate = card.birthday;
		   pView->m_InfoDlg.m_address   = card.address;
		   //注意有效期限和签发日期
		   pView->m_InfoDlg.m_signdate  = card.validterm;
		   pView->m_InfoDlg.m_validdate = card.signdate;
		   pView->m_InfoDlg.m_id        = card.number;	
           pView->m_InfoDlg.m_stcCaption = _T("签发地：");
		   pView->m_InfoDlg.m_headFilePath = head_name;
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_InfoDlg.m_sError = "用户输入的文件名不存在!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
		   
	   }
	   else if(result == 2)
	   {
		   pView->m_InfoDlg.m_sError = "打开文件失败!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_InfoDlg.m_sError = "识别失败!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
}

void CIDCardApp::OnFileScanreco() 
{//根据不同证件类型进行不同证件的图像扫描并保存到指定的路径下
	// TODO: Add your command handler code here
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	
   	CString file_name;
	CFileDialog fdlg(FALSE,"*.jpg","Img0001", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,"JPG Image Files (*.jpg)|*.jpg||", NULL );



	int type = 10;
	switch(theApp.m_LStyeImage)
	{
	case 0:
		//theApp.Idcardone();
		type = 1;
		break;
	case 1:
		//theApp.Idcardtwo();
		type = 6;
		break;
	case 2:
		//theApp.FileDriveport();
		type = 2;
		break;
	case 3:
		//theApp.Huixiang();	
		type = 6;
		break;			
	case 4:
	//	theApp.Qianzheng();默认
		type = 10;
		break;
	case 5:		
	//	theApp.Xingshi();默认
		type = 10;
		break;
	case 6:
	//	theApp.Passport();
		type = 4;
		break;
	case 7:	
		//theApp.Idcardtwoback();
		type = 6;
		break;
	case 8:
	//	theApp.TempTwo();
		type = 6;
		break;
	case 9:
	//	theApp.junguanzheng();
		type = 16;
		break;
	case 10:
	//	theApp.shibingzheng();默认
		type = 10;
		break;
	case 11:
	//	theApp.GDjuzhuzheng();默认
		type = 10;
		break;
	case 12:
	//	theApp.DGjuzhuzheng();默认
		type = 10;
		break;
	case 13:
	//	theApp.SZjuzhuzheng();默认
		type = 10;
		break;
	case 14:
	//全屏幕扫描
		type = 10;
		break;
		
	default:
	//	theApp.Idcardone(filePath);
		type = 10;
		break;
	}




	
	if(fdlg.DoModal()==IDOK)
	{
		file_name = fdlg.GetPathName();
		int result = pScanImageEx(file_name.GetBuffer(file_name.GetLength()),type);
		file_name.ReleaseBuffer();
		if(result == 0)
		{ 
			pView->HideIdcardTwoInfo();
			pView->HidePassPortInfo();
			pView->HideIdcardBackInfo();
			pView->HideVLInfo();
			pView->HideResidentInfo();
			pView->HidInfoDlg();
			pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
			pFrame->m_wndSplitter.RecalcLayout();  
			pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh + 500,   0);
			pFrame->m_bottomSplit.RecalcLayout();  
				pViewImage->showDlgImage();
			pViewImage->m_DlgImage.m_ImageFilePath = file_name;
			pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
		}
		else if(result == 1)
			MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0);
		else if(result == 2)
			MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0);
		else if(result == 4)
		{
			MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
			theApp.OnAppExit();
		}
		
	}
	else
	{
		m_hMutex.Lock();
		bEnableFileScan = true;
		m_hMutex.Unlock();
	}
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
	
}
//行驶证扫描识别
void CIDCardApp::OnFileXingshi() 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	} 
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	   
	   CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
	   CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	   CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	   pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	   pFrame->m_wndSplitter.RecalcLayout();  
	   pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
	   pFrame->m_bottomSplit.RecalcLayout();  

	  
	   pView->m_VLInfo.DelLegacyData();
	   pViewImage->m_DlgImage.m_ImageFilePath = ""; 

// 	   pView->HideIdcardTwoInfo();
// 	   pView->HidePassPortInfo();
// 	   pView->HideIdcardBackInfo();
// 	   pView->HideResidentInfo();
// 	   pView->HidInfoDlg();

       pView->HideAllDialog();
	   pViewImage->showDlgImage();
	   pView->ShowVLInfo();
	   
	   CString   strAppPath; 
	   strAppPath = theApp.m_strCurPath;
	   CString   sTime;   
	   SYSTEMTIME   CurTime;   
	   GetLocalTime(&CurTime);   
	   sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		   CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
	   strAppPath += "TempPic\\";
	   strAppPath += sTime+".jpg";
	   
	   VEHICLELICENS_ALL card;
	   CString file_name,head_name;
	   
	   file_name = strAppPath;
	   head_name = "";
	   int result = pRecogVehicleLicenseEXALL(file_name.GetBuffer(file_name.GetLength()),card,true);
	   head_name.Replace("TempPic","picture");
	   file_name.Replace("TempPic","picture");
	   CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	   
	   if(result == 0)
	   { 
		   pView->m_VLInfo.m_strVType = card.VehicleType;	//车辆类型
		   pView->m_VLInfo.m_strVIN = card.VIN;				//车辆识别代号
		   pView->m_VLInfo.m_strPlateNo = card.PlateNo;		//车牌号
		   pView->m_VLInfo.m_strOwner = card.Owner;			//所有人
	       pView->m_VLInfo.m_strIssueDate = card.IssueDate;	//发证日期
		   pView->m_VLInfo.m_strEngnieNo = card.EngineNo;	//发动机号码
		   pView->m_VLInfo.m_strAddress = card.Address;		//住址
		   pView->m_VLInfo.m_strModel = card.Model;			//品牌型号

		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;

		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 


	   }
	   else if(result == 1)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
		   
	   }
	   else if(result == 2)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		   
	   }
	   else if(result == 3)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
				 
	   }
	   else if(result == 4)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		   theApp.OnAppExit();
	   }
	   
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();
	   
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock(); 

	   
}

//行驶证图像导入识别
void CIDCardApp::Xingshi(CString  &file_name) 
{	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth, 0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	//显示更新变量值
	pView->m_VLInfo.DelLegacyData();

//     pView->HideIdcardTwoInfo();
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HidInfoDlg();

	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->ShowVLInfo();

	
	CString head_name;
	VEHICLELICENS_ALL card;
	head_name = "";
	   CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	   CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	   int result = pRecogVehicleLicenseEXOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true);
	   ::DeleteFile(strAppPath);
	   if(result == 0)
	   {
		   pView->m_VLInfo.m_strVType = card.VehicleType;
		   pView->m_VLInfo.m_strVIN = card.VIN;
		   pView->m_VLInfo.m_strPlateNo = card.PlateNo;
		   pView->m_VLInfo.m_strOwner = card.Owner;
		   pView->m_VLInfo.m_strIssueDate = card.IssueDate;
		   pView->m_VLInfo.m_strEngnieNo = card.EngineNo;
		   pView->m_VLInfo.m_strAddress = card.Address;
		   pView->m_VLInfo.m_strModel = card.Model;
		   pView->m_VLInfo.m_strUsingType = card.UseCharacter;
		   pView->m_VLInfo.m_strRegistrationDate = card.RegisterDate;
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;

		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	   }
	   else if(result == 1) 
	   {
	
		   pView->m_VLInfo.m_strPlateNo = "用户输入的文件名不存在!";
		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	   }
	   else if(result == 2)
	   {
		   pView->m_VLInfo.m_strPlateNo = "打开文件失败!";
		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   else if(result == 3)
	   {
		   pView->m_VLInfo.m_strPlateNo = "识别失败!";
		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 				
	   }
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();	
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
}

//临时二代证
void CIDCardApp::OnTempTwo() 
{
	// TODO: Add your command handler code here
	
	if( pRecogNewIdcardTempALL == NULL)
		return;
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
    m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();   
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	
	pView->m_IdcardTwoInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";
	
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HidInfoDlg();
// 	pView->HideVLInfo();

    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showIdcardTwoInfo();
	
	
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	int result = pRecogNewIdcardTempALL (file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	head_name.Replace("TempPic","picture");
	   file_name.Replace("TempPic","picture");
	   CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	   
	   if(result == 0)
	   {
		   
		   pView->m_IdcardTwoInfo.m_sError = "";
		   pView->m_IdcardTwoInfo.m_name      = card.name;
		   pView->m_IdcardTwoInfo.m_sex       = card.sex;
		   pView->m_IdcardTwoInfo.m_nation    = card.people;
		   pView->m_IdcardTwoInfo.m_birthdate = card.birthday;
		   pView->m_IdcardTwoInfo.m_address   = card.address;
		   pView->m_IdcardTwoInfo.m_id        = card.number;
		   pView->m_IdcardTwoInfo.m_headFilePath = head_name;
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	   }
	   else if(result == 1)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
	   }
	   else if(result == 2)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0);
	   }
	   else if(result == 3)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
	   } 
	   else if(result == 4)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		   theApp.OnAppExit();
	   }
	   
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
	
	   
}


//临时二代证图像导入识别
void CIDCardApp::TempTwo(CString  &file_name)
{
	if(pRecogNewIdcardOnlyTempALL == NULL )
	{
		return;
	}
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_IdcardTwoInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HidInfoDlg();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();
    
	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showIdcardTwoInfo();
	
	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	   CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	   CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	   int result = pRecogNewIdcardOnlyTempALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	   ::DeleteFile(strAppPath);
	   pView->m_InfoDlg.drawPic();
	   if(result == 0)
	   {   
		   pView->m_IdcardTwoInfo.m_name      = card.name;
		   pView->m_IdcardTwoInfo.m_sex       = card.sex;
		   pView->m_IdcardTwoInfo.m_nation    = card.people;
		   pView->m_IdcardTwoInfo.m_birthdate = card.birthday;
		   pView->m_IdcardTwoInfo.m_address   = card.address;
		   pView->m_IdcardTwoInfo.m_id        = card.number;
		   pView->m_IdcardTwoInfo.m_headFilePath = head_name;
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_IdcardTwoInfo.m_sError = "用户输入的文件名不存在!";
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 2)
	   {
		   pView->m_IdcardTwoInfo.m_sError = "打开文件失败!";
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_IdcardTwoInfo.m_sError = "识别失败!";
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);		
	   }
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
	   
}

void CIDCardApp::exitApp()
{       
	// CVR_CloseComm();
	theApp.OnAppExit();
}


BOOL CIDCardApp::CopyDirectory(CString strSrcPath, CString strDesPath, BOOL bFailIfExists/*=FALSE*/)
{
    if( strSrcPath.IsEmpty() )
    {       
        OutputDebugString("源文件名为空，无法进行拷贝!");   
        return FALSE;
    }
	CFileFind fFind;
	
    if ( !fFind.FindFile(strDesPath) )
    {
        //if ( !PCNewFileCopy( strDesPath ) )
		return FALSE;
    }
	
    if ( strSrcPath.GetAt(strSrcPath.GetLength()-1) != '\\' )
        strSrcPath += '\\';
    if ( strDesPath.GetAt(strDesPath.GetLength()-1) != '\\' )
        strDesPath += '\\';
	
    BOOL bRet = FALSE; // 因为源目录不可能为空，所以该值一定会被修改
    CFileFind ff;  
    BOOL bFound = ff.FindFile(strSrcPath+"*",   0);  
    while(bFound)      // 递归拷贝
    {  
        bFound = ff.FindNextFile();  
        if( ff.GetFileName() == "." || ff.GetFileName() == ".." )  
            continue;
		
        CString strSubSrcPath = ff.GetFilePath();
        CString strSubDespath = strSubSrcPath;
        strSubDespath.Replace(strSrcPath, strDesPath);
		
        if( ff.IsDirectory() )
		{
            bRet = CopyDirectory(strSubSrcPath, strSubDespath, bFailIfExists);     // 递归拷贝文件夹
			::DeleteFile(strSubSrcPath);
		}
        else
		{
            bRet = CopyFile(strSubSrcPath, strSubDespath, bFailIfExists);   // 拷贝文件
			::DeleteFile(strSubSrcPath);
		}
        if ( !bRet )
            break;
    }
    ff.Close();
    return bRet;
}

//军官证扫描识别
void CIDCardApp::OnFileJunguanzheng() 
{
	// TODO: Add your command handler code here
			
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
		
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
	CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";
	
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideIdcardTwoInfo();
// 	pView->HideVLInfo();
// 	pView->HideResidentInfo();

    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showInfoDlg();
	//pView->m_InfoDlg.UpdateData(false);
	
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	int result = pRecogSoldieryCardALL(file_name.GetBuffer(file_name.GetLength()),card,true,1,head_name.GetBuffer(head_name.GetLength()));
	
	file_name.Replace("TempPic","picture");
	head_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	if(result == 0)
	{   
		pView->m_InfoDlg.m_name      = card.name;
		pView->m_InfoDlg.m_sex       = card.sex;
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;
		pView->m_InfoDlg.m_address   = card.address;
		pView->m_InfoDlg.m_signdate  = card.signdate;
		pView->m_InfoDlg.m_validdate = card.validterm;
		pView->m_InfoDlg.m_id        = card.number;

		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{		
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
		
	}
	else if(result == 2)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
	}
	else if(result == 3)
	{   
		
       	MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();

}
// 士兵证扫描识别
void CIDCardApp::OnFileShibingzheng() 
{
	// TODO: Add your command handler code here

	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
		
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
	CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name,head_name;
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";
	
// 	pView->HidePassPortInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideIdcardTwoInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();

    pView->HideAllDialog();
    pViewImage->showDlgImage();
	pView->showInfoDlg();
	
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	int result = pRecogSoldieryCardALL(file_name.GetBuffer(file_name.GetLength()),card,true,2,head_name.GetBuffer(head_name.GetLength()));
	
	file_name.Replace("TempPic","picture");
	head_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	if(result == 0)
	{   
		pView->m_InfoDlg.m_name      = card.name;
		pView->m_InfoDlg.m_sex       = card.sex;
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;
		pView->m_InfoDlg.m_address   = card.address;
		pView->m_InfoDlg.m_signdate  = card.signdate;
		pView->m_InfoDlg.m_validdate = card.validterm;
		pView->m_InfoDlg.m_id        = card.number;

		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	
	}
	else if(result == 1)
	{		
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
		
	}
	else if(result == 2)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
	}
	else if(result == 3)
	{   
		
       	MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}


void  CIDCardApp::junguanzheng(CString  &file_name) 
{  //军官证图像导入识别
	if(!m_bLoaded)
	{	
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
    pFrame->m_wndSplitter.RecalcLayout();  
	
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
// 	pView->HidePassPortInfo();
//     pView->HideIdcardTwoInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();
	pView->HideAllDialog();

	pViewImage->showDlgImage();
	pView->showInfoDlg();

	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	CopyFile(file_name, strAppPath, FALSE);   // 拷贝文件	
	int result = pRecogSoldieryCardOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,1,head_name.GetBuffer(head_name.GetLength()));
	::DeleteFile(strAppPath);
	
	if(result == 0)
	{
		pView->m_InfoDlg.m_sError = "";
		pView->m_InfoDlg.m_name      = card.name;
		pView->m_InfoDlg.m_sex       = card.sex;
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;
		pView->m_InfoDlg.m_address   = card.address;
		pView->m_InfoDlg.m_signdate  = card.signdate;	 //签发日期 空
		pView->m_InfoDlg.m_validdate = card.validterm;   // 有效期 空
		pView->m_InfoDlg.m_id        = card.number;	
		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	}
	else if(result == 1) //
		
	{
		pView->m_InfoDlg.m_sError = "用户输入的文件名不存在!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
		
	}
	else if(result == 2)
	{
		pView->m_InfoDlg.m_sError = "打开文件失败!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 3)
	{
		pView->m_InfoDlg.m_sError = "识别失败!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
}

//士兵证图像导入识别
void  CIDCardApp::shibingzheng(CString  &file_name) 
{   
	if(!m_bLoaded)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
    pFrame->m_wndSplitter.RecalcLayout();  
	
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout();  
	
	pView->m_InfoDlg.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath ="";
	
// 	pView->HidePassPortInfo();
//     pView->HideIdcardTwoInfo();
// 	pView->HideIdcardBackInfo();
// 	pView->HideResidentInfo();
// 	pView->HideVLInfo();

	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showInfoDlg();
	


	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	CopyFile(file_name, strAppPath, FALSE);   // 拷贝文件	
	int result = pRecogSoldieryCardOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,2,head_name.GetBuffer(head_name.GetLength()));
	::DeleteFile(strAppPath);
	
	if(result == 0)
	{
		pView->m_InfoDlg.m_sError = "";
		pView->m_InfoDlg.m_name      = card.name;
		pView->m_InfoDlg.m_sex       = card.sex;
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;
		pView->m_InfoDlg.m_address   = card.address;  //籍贯
		pView->m_InfoDlg.m_signdate  = card.signdate;
		pView->m_InfoDlg.m_validdate = card.validterm;
		pView->m_InfoDlg.m_id        = card.number;	
		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	}
	else if(result == 1) //
		
	{
		pView->m_InfoDlg.m_sError = "用户输入的文件名不存在!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
		
	}
	else if(result == 2)
	{
		pView->m_InfoDlg.m_sError = "打开文件失败!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 3)
	{
		pView->m_InfoDlg.m_sError = "识别失败!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
}

void CIDCardApp::OnFILEFirmwareVersion() 
{
	// TODO: Add your command handler code here22222222222222222

	
		if (DeviceType == Cameras && pReadFirmwareVersionInfo!=NULL)
		{
			char szVersionInfo[10];
			memset(szVersionInfo,0,sizeof(char)*10);
			pReadFirmwareVersionInfo(szVersionInfo,10);
			AfxMessageBox(szVersionInfo);
		}
		else
		{
			AfxMessageBox(_T("无分位版本信息!"));
			//return;
		}



	
}


CString CIDCardApp::GetSDKVesion()
{
	if (Version!=NULL)
	{
		return Version;
	}
	else
	{
		return "";
	}
}
CString CIDCardApp::GetDeviceType()
{
	if (DeviceType==NULL)
	{
		return _T("");
	}
	else
	{
		return DeviceType;
	}
}

BOOL CIDCardApp::CheckScannerOnline(CString strType)
{
	BOOL bOnline = FALSE;
	if (pCheckWTScanner!=NULL)
	{	
		BOOL bOnline = pCheckWTScanner(strType.GetBuffer(strType.GetLength()));
	    strType.ReleaseBuffer();
	}
	return bOnline;
}	


//居住证扫描识别 广东
void CIDCardApp::OnFileGdJuzhuzheng() 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
   	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 

	pView->m_ResidentInfo.DelLegacyData();	
	pViewImage->m_DlgImage.m_ImageFilePath = "";


// 	pView->HideIdcardTwoInfo();
// 	pView->HidInfoDlg();
// 	pView->HideIdcardBackInfo();
// 	pView->HideVLInfo();
// 	pView->HidePassPortInfo();
    pView->HideAllDialog();

	pViewImage->showDlgImage();
	pView->showResidentInfo();
	
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name = "",head_name = "";
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	int result = pRecogGDResidencePermitAll(file_name.GetBuffer(file_name.GetLength()),card,true,head_name.GetBuffer(head_name.GetLength()));
	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	
	if(result == 0)
	{   
	
	//	temp ++;
		pView->m_ResidentInfo.m_sError = "";
	  
		pView->m_ResidentInfo.m_name = card.name;
					
		if( pView->m_ResidentInfo.m_name.Find(';') != -1)
		{	
			//	pView->m_ResidentInfo.m_name_en = pView->m_ResidentInfo.m_name.Mid(pView->m_ResidentInfo.m_name.Find(';')+1,pView->m_ResidentInfo.m_name.GetLength() - pView->m_ResidentInfo.m_name.Find(';') -1);
			pView->m_ResidentInfo.m_name = pView->m_ResidentInfo.m_name.Mid(0,pView->m_ResidentInfo.m_name.Find(';'));		
		}
		
		pView->m_ResidentInfo.m_minzu = card.people;
		
		CString str = card.other;
		
		
		pView->m_ResidentInfo.m_birthplace = card.other;			
		pView->m_ResidentInfo.m_placeissue = card.address;
		
		pView->m_ResidentInfo.m_sex = card.sex;
		pView->m_ResidentInfo.m_birthdate = card.birthday;
		pView->m_ResidentInfo.m_validdate = card.validterm;
		pView->m_ResidentInfo.m_signdate = card.signdate;
		pView->m_ResidentInfo.m_number1    = card.number;
		pView->m_ResidentInfo.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;


		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	

}

//广东居住证对比识别
void CIDCardApp::GDjuzhuzheng(CString &file_name)
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}

	bEnableFileScan = false;
	m_hMutex.Unlock();	
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	
	pView->m_ResidentInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";

	
    pView->HideIdcardTwoInfo();
	pView->HidInfoDlg();
	pView->HideIdcardBackInfo();
	pView->HideVLInfo();
	pView->HidePassPortInfo();
	pViewImage->showDlgImage();
	pView->showResidentInfo();
	
	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
    CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
   
	int result = pRecogGDResidencePermitOnlyAll(file_name.GetBuffer(file_name.GetLength()),card,true,head_name.GetBuffer(head_name.GetLength()));
	::DeleteFile(strAppPath);


	if(result == 0)
	{   
		pView->m_ResidentInfo.m_sError = "";	  			   
		pView->m_ResidentInfo.m_name = card.name;
		
		if( pView->m_ResidentInfo.m_name.Find(';') != -1)
		{		
			pView->m_ResidentInfo.m_name = pView->m_ResidentInfo.m_name.Mid(0,pView->m_ResidentInfo.m_name.Find(';'));		
		}
		
		pView->m_ResidentInfo.m_minzu = card.people;
		pView->m_ResidentInfo.m_placeissue = card.address;	   
		pView->m_ResidentInfo.m_sex = card.sex;
		CString str = card.other; 
		
		pView->m_ResidentInfo.m_birthplace = str;
		pView->m_ResidentInfo.m_validdate = card.birthday;
		pView->m_ResidentInfo.m_signdate = card.signdate;			   
		pView->m_ResidentInfo.m_number1   = card.number;
		if (_tcslen(card.number)>14)
		{	
			pView->m_ResidentInfo.m_birthdate = pView->m_ResidentInfo.m_number1.Mid(6,8);
		}
		
		pView->m_ResidentInfo.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 1) //		   
	{
		pView->m_ResidentInfo.m_sError = "用户输入的文件名不存在!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	 }
	 else if(result == 2)
	 {
		 pView->m_ResidentInfo.m_sError = "打开文件失败!";
		 pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		 pView->m_ResidentInfo.UpdateData(FALSE);
		 pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	 }
	 else if(result == 3)
	 {
		 pView->m_ResidentInfo.m_sError = "识别失败!";
		 pView->m_ResidentInfo.InvalidateRect(NULL,TRUE);  
		 pView->m_ResidentInfo.UpdateData(FALSE);
		 pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		 pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);			
	 }
	 
	 head_name.ReleaseBuffer();
	 file_name.ReleaseBuffer();
	 m_hMutex.Lock();
	 bEnableFileScan = true;
	 m_hMutex.Unlock();
}

//居住证扫描识别 东莞
void CIDCardApp::OnFileDgJuzhuzheng() 
{
	// TODO: Add your command handler code here

	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
   	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 


	pView->m_ResidentInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";


// 	pView->HideIdcardTwoInfo();
// 	pView->HidInfoDlg();
// 	pView->HideIdcardBackInfo();
// 	pView->HideVLInfo();
// 	pView->HidePassPortInfo();
	pView->HideAllDialog();

	pViewImage->showDlgImage();
	pView->showResidentInfo();
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name = "",head_name = "";
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	int result = pRecogDongGuanResidencePermitAll(file_name.GetBuffer(file_name.GetLength()),card,true,head_name.GetBuffer(head_name.GetLength()));
	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	
	if(result == 0)
	{   	
		pView->m_ResidentInfo.m_sError = "";	
		pView->m_ResidentInfo.m_name = card.name;	
		
		if( pView->m_ResidentInfo.m_name.Find(';') != -1)
		{			
			pView->m_ResidentInfo.m_name = pView->m_ResidentInfo.m_name.Mid(0,pView->m_ResidentInfo.m_name.Find(';'));				
		}
		
		pView->m_ResidentInfo.m_sex = card.sex;				
		pView->m_ResidentInfo.m_birthplace = card.people;
		pView->m_ResidentInfo.m_placeissue = card.address;
		
		pView->m_ResidentInfo.m_birthdate = card.birthday;
		pView->m_ResidentInfo.m_validdate = card.validterm;
		pView->m_ResidentInfo.m_signdate = card.signdate;
		pView->m_ResidentInfo.m_number1    = card.number;

		int length = pView->m_ResidentInfo.m_number1.GetLength();
		int mid = pView->m_ResidentInfo.m_number1.Find(';');
		if(mid!=-1)
		{
			pView->m_ResidentInfo.m_number2 = pView->m_ResidentInfo.m_number1.Mid(mid+1,length - mid);
			pView->m_ResidentInfo.m_number1 = pView->m_ResidentInfo.m_number1.Mid(0,mid);
		}
		pView->m_ResidentInfo.m_server = card.other;
		pView->m_ResidentInfo.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;

	
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();



}


void CIDCardApp :: DGjuzhuzheng(CString &file_name)
{// 居住证比对识别 东莞
    if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();	
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	

	pView->m_ResidentInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";

    pView->HideIdcardTwoInfo();
	pView->HidInfoDlg();
	pView->HideIdcardBackInfo();
	pView->HideVLInfo();
	pView->HidePassPortInfo();
	pViewImage->showDlgImage();
	pView->showResidentInfo();
	
	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	
	int result = pRecogDongGuanResidencePermitOnlyAll(file_name.GetBuffer(file_name.GetLength()),card,true,head_name.GetBuffer(head_name.GetLength()));
	::DeleteFile(strAppPath);
				
	if(result == 0)
	{
		pView->m_ResidentInfo.m_sError = "";
		
		pView->m_ResidentInfo.m_name = card.name;
		
		if( pView->m_ResidentInfo.m_name.Find(';') != -1)
		{			
			pView->m_ResidentInfo.m_name = pView->m_ResidentInfo.m_name.Mid(0,pView->m_ResidentInfo.m_name.Find(';'));				
		}
		
		pView->m_ResidentInfo.m_sex = card.sex;				
		pView->m_ResidentInfo.m_birthplace = card.people;
		pView->m_ResidentInfo.m_placeissue = card.address;
		
		pView->m_ResidentInfo.m_birthdate = card.birthday;
		pView->m_ResidentInfo.m_validdate = card.validterm;
		pView->m_ResidentInfo.m_signdate = card.signdate;
		pView->m_ResidentInfo.m_number1    = card.number;
				
		int length = pView->m_ResidentInfo.m_number1.GetLength();
		int mid = pView->m_ResidentInfo.m_number1.Find(';');
		if(mid!=-1)
		{
			pView->m_ResidentInfo.m_number2 = pView->m_ResidentInfo.m_number1.Mid(mid+1,length - mid);
			pView->m_ResidentInfo.m_number1 = pView->m_ResidentInfo.m_number1.Mid(0,mid);
		}
		
		pView->m_ResidentInfo.m_server = card.other;
		pView->m_ResidentInfo.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
		
	}
	else if(result == 1) //		   
	{
		pView->m_ResidentInfo.m_sError = "用户输入的文件名不存在!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
    else if(result == 2)
	{
		pView->m_ResidentInfo.m_sError = "打开文件失败!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	}
	else if(result == 3)
	{
		pView->m_ResidentInfo.m_sError = "识别失败!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE);  
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);			
	}
	   
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	   
}


//居住证扫描识别 深圳
void CIDCardApp::OnFileSzJuzhuzheng() 
{
	// TODO: Add your command handler code here
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
   	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 


	pView->m_ResidentInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";


// 	pView->HideIdcardTwoInfo();
// 	pView->HidInfoDlg();
// 	pView->HideIdcardBackInfo();
// 	pView->HideVLInfo();
// 	pView->HidePassPortInfo();

    pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showResidentInfo();
	
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	IDCARD_ALL card;
	CString file_name = "",head_name = "";
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	int result = pRecogShenZhenResidencePermitAll(file_name.GetBuffer(file_name.GetLength()),card,true,head_name.GetBuffer(head_name.GetLength()));
	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	if(result == 0)
	{   

		pView->m_ResidentInfo.m_sError = "";

	  	pView->m_ResidentInfo.m_name = card.name;
		pView->m_ResidentInfo.m_sex = card.sex;				
		pView->m_ResidentInfo.m_minzu = card.people;
		pView->m_ResidentInfo.m_placeissue = card.address;
				
		pView->m_ResidentInfo.m_signdate = card.signdate;
		pView->m_ResidentInfo.m_number1    = card.number;

		int length = pView->m_ResidentInfo.m_number1.GetLength();
		int mid = pView->m_ResidentInfo.m_number1.Find(';');
		if(mid!=-1)
		{
			pView->m_ResidentInfo.m_number2 = pView->m_ResidentInfo.m_number1.Mid(mid+1,length - mid);
			pView->m_ResidentInfo.m_number1 = pView->m_ResidentInfo.m_number1.Mid(0,mid);
		}

		pView->m_ResidentInfo.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;

	
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"识别失败!","证件识别系统",0);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}

//居住证比对识别 深圳
void CIDCardApp::SZjuzhuzheng(CString &file_name)
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();	
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,   0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,   0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	

 	pView->m_ResidentInfo.DelLegacyData();

 	pViewImage->m_DlgImage.m_ImageFilePath = "";


//     pView->HideIdcardTwoInfo();
// 	pView->HidInfoDlg();
// 	pView->HideIdcardBackInfo();
// 	pView->HideVLInfo();
// 	pView->HidePassPortInfo();

	pView->HideAllDialog();
	pViewImage->showDlgImage();
	pView->showResidentInfo();		
	CString head_name;
	IDCARD_ALL card;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
	
	CString strAppPath =theApp.m_strCurPath + "TempPic\\temp.jpg";
	CopyFile(head_name, strAppPath, FALSE);   // 拷贝文件
	
	int result = pRecogShenZhenResidencePermitOnlyAll(file_name.GetBuffer(file_name.GetLength()),card,true,head_name.GetBuffer(head_name.GetLength()));
	::DeleteFile(strAppPath);
	
	
	if(result == 0)
	{
		
		pView->m_ResidentInfo.m_sError = "";
		
		pView->m_ResidentInfo.m_name = card.name;
		pView->m_ResidentInfo.m_sex = card.sex;					
		pView->m_ResidentInfo.m_placeissue = card.address;
		pView->m_ResidentInfo.m_signdate = card.signdate;
		pView->m_ResidentInfo.m_number1    = card.number;
		
		pView->m_ResidentInfo.m_minzu = card.people;
		pView->m_ResidentInfo.m_birthdate = card.birthday;
		pView->m_ResidentInfo.m_validdate = card.validterm;
		
		int length = pView->m_ResidentInfo.m_number1.GetLength();
		int mid = pView->m_ResidentInfo.m_number1.Find(';');
		if(mid!=-1)
		{
			pView->m_ResidentInfo.m_number2 = pView->m_ResidentInfo.m_number1.Mid(mid+1,length - mid);
			pView->m_ResidentInfo.m_number1 = pView->m_ResidentInfo.m_number1.Mid(0,mid);
		}
			
		pView->m_ResidentInfo.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		
		
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 1) //		   
	{
		pView->m_ResidentInfo.m_sError = "用户输入的文件名不存在!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
	else if(result == 2)
	{
		pView->m_ResidentInfo.m_sError = "打开文件失败!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	}
	else if(result == 3)
	{
		pView->m_ResidentInfo.m_sError = "识别失败!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE);  
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);			
	}
	   
    head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	   
}
//标题中显示当前处理文件名
void CIDCardApp::DisplayFileNameOnTitle(const CString& strFilePath)
{
    CString str = strFilePath.Right(strFilePath.GetLength()-strFilePath.ReverseFind(L'\\')-1);
	TCHAR szWinTitle[MAX_PATH];
	_tcscpy(szWinTitle,WinTitle);
	_tcscat(szWinTitle,_T("-["));
	_tcscat(szWinTitle,str);
	_tcscat(szWinTitle,_T("]"));
	m_pMainWnd->SetWindowText(szWinTitle);

}

//名片识别
void CIDCardApp::RecognizeBusinessCardFromFile(const CString &file_name)
{
  
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();	
	
	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	
  
    pView->HideAllDialog();
 	pViewImage->m_DlgImage.m_ImageFilePath = "";
	pViewImage->showDlgImage();
	pView->ShowBusinessCardDlg();
	pView->m_BusinessCardInfo.ResetMemData();
		
	BCR_RESULT card;
	int result = 0;
	try
	{
    	result	= lpfnRecogBusinessCardOnlyAll(file_name,card);
	}
	catch (...)
	{
		m_hMutex.Lock();
		bEnableFileScan = true;
	    m_hMutex.Unlock();
	}

	if(result == 0)
	{
		pView->m_BusinessCardInfo.m_strName = card.PersonName;
		pView->m_BusinessCardInfo.m_strAddress = card.Address;
		pView->m_BusinessCardInfo.m_strPostCode = card.PostCode;
		pView->m_BusinessCardInfo.m_strCallNum = card.CallNum;
		pView->m_BusinessCardInfo.m_strCompany = card.CompanyName;
		pView->m_BusinessCardInfo.m_strDepartment = card.Department;
		pView->m_BusinessCardInfo.m_strEmail = card.Email;
		pView->m_BusinessCardInfo.m_strFax = card.Fax;
		pView->m_BusinessCardInfo.m_strHomePage = card.HomePage;
		pView->m_BusinessCardInfo.m_strJob = card.JobName;
		pView->m_BusinessCardInfo.m_strMobile = card.Mobile;
		pView->m_BusinessCardInfo.m_strRemark = card.Remark;
		pView->m_BusinessCardInfo.m_strTel = card.Telephone;
		
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
	
		pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE); 
		pView->m_BusinessCardInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 1) //		   
	{
		pView->m_BusinessCardInfo.m_strName = "用户输入的文件名不存在!";
		pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE); 
		pView->m_BusinessCardInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
	else if(result == 2)
	{
		   pView->m_BusinessCardInfo.m_strName = "打开文件失败!";
		   pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_BusinessCardInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	 }
	 else if(result == 3)
	 {
		   pView->m_BusinessCardInfo.m_strName = "识别失败!";
		   pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE);  
		   pView->m_BusinessCardInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);			
	 }
	 else if (result==5)
	 {
		 pView->m_BusinessCardInfo.m_strName = _T("暂不支持名片识别!");
		 pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE);  
		 pView->m_BusinessCardInfo.UpdateData(FALSE);
		 pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		 pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
	}
	  
	 m_hMutex.Lock();
	 bEnableFileScan = true;
	 m_hMutex.Unlock();
	   
}

void CIDCardApp::OnFileRecogBusinessCard() 
{
	// TODO: Add your command handler code here
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"扫描识别核心加载失败，无法进行识别!","证件识别系统",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"批量导入识别未完成!","证件识别系统",0); 
		return;
	}
	m_hMutex.Lock();
	if(!bEnableFileScan)
	{
		m_hMutex.Unlock();
		return;
	}
	bEnableFileScan = false;
	m_hMutex.Unlock();
	
   	CMainFrame *pFrame = (CMainFrame *)(this->m_pMainWnd);
    CIDCardImageView *pViewImage  = static_cast<CIDCardImageView*>(pFrame->m_wndSplitter.GetPane(0,0));
	CIDCardInfoView *pView  = static_cast<CIDCardInfoView*>(pFrame->m_wndSplitter.GetPane(0,1));
	pFrame->m_wndSplitter.SetColumnInfo(0, m_wndSplitWidth,0); 
	pFrame->m_wndSplitter.RecalcLayout();  
	pFrame->m_bottomSplit.SetRowInfo(0, m_wndSplitHeigh,0);
   	pFrame->m_bottomSplit.RecalcLayout(); 
	
	
    pView->HideAllDialog();
	pViewImage->m_DlgImage.m_ImageFilePath = "";
	pViewImage->showDlgImage();
	pView->ShowBusinessCardDlg();
	pView->m_BusinessCardInfo.ResetMemData();
	
	CString   strAppPath; 
	strAppPath = theApp.m_strCurPath;
	CString   sTime;   
    SYSTEMTIME   CurTime;   
    GetLocalTime(&CurTime);   
    sTime.Format("%d%d%d%d%d%d",CurTime.wYear,CurTime.wMonth,CurTime.wDay,
		CurTime.wHour,CurTime.wMinute,CurTime.wSecond);   
    strAppPath += "TempPic\\";
    strAppPath += sTime+".jpg";
	
	BCR_RESULT card;
	CString file_name = "";
	CString head_name = "";
	file_name = strAppPath;
	head_name = file_name.Left(file_name.GetLength() - 4) + "_head";
	head_name += file_name.Right(4);
    int result = 0;
	try
	{
        result = lpfnRecogBusinessCardAll(file_name.GetBuffer(file_name.GetLength()),card);
	}
	catch(...)
	{
		head_name.ReleaseBuffer();
		file_name.ReleaseBuffer();
		m_hMutex.Lock();
		bEnableFileScan = true;
    	m_hMutex.Unlock();
	}

	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	
	if(result == 0)
	{   
		pView->m_BusinessCardInfo.m_strName = card.PersonName;
		pView->m_BusinessCardInfo.m_strAddress = card.Address;
		pView->m_BusinessCardInfo.m_strPostCode = card.PostCode;
		pView->m_BusinessCardInfo.m_strCallNum = card.CallNum;
		pView->m_BusinessCardInfo.m_strCompany = card.CompanyName;
		pView->m_BusinessCardInfo.m_strDepartment = card.Department;
		pView->m_BusinessCardInfo.m_strEmail = card.Email;
		pView->m_BusinessCardInfo.m_strFax = card.Fax;
		pView->m_BusinessCardInfo.m_strHomePage = card.HomePage;
		pView->m_BusinessCardInfo.m_strJob = card.JobName;
		pView->m_BusinessCardInfo.m_strMobile = card.Mobile;
		pView->m_BusinessCardInfo.m_strRemark = card.Remark;
		pView->m_BusinessCardInfo.m_strTel = card.Telephone;
		
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
	
		pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE); 
		pView->m_BusinessCardInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"采集图像发生错误!","证件识别系统",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"用户输入的文件路径名不符合要求!","证件识别系统",0); 
		
	}
	else if(result == 3)
	{
		pView->m_BusinessCardInfo.m_strName = "识别失败!";
		pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE);  
		pView->m_BusinessCardInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"目前拍照设备没有在线!","证件识别系统",0); 
		theApp.OnAppExit();
	}
	else if (result==5)
	{
		pView->m_BusinessCardInfo.m_strName = _T("暂不支持名片识别!");
		pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE);  
		pView->m_BusinessCardInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}
