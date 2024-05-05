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
//ʶ����Ľӿں���
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

//��ʻ֤
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
//��֤ͨ�Ķ����ӿں���
int(WINAPI *CVR_InitComm)(int);
int(WINAPI *CVR_Authenticate)(void);									           			    		
int(WINAPI *CVR_CloseComm)(void);

//��ס֤ɨ��ʶ�� �㶫
int (WINAPI *pRecogGDResidencePermitAll)(LPTSTR, IDCARD_ALL&, bool ,char* );

//��ס֤�Ա�ʶ�� �㶫
int (WINAPI *pRecogGDResidencePermitOnlyAll)(LPCTSTR, IDCARD_ALL &, bool, char* );

//��ס֤ɨ��ʶ�� ��ݸ
int (WINAPI *pRecogDongGuanResidencePermitAll)(char*, IDCARD_ALL& , bool, char* );

//��ס֤�Ա�ʶ�� ��ݸ
int (WINAPI *pRecogDongGuanResidencePermitOnlyAll)(char*, IDCARD_ALL& , bool, char* );

//��ס֤ɨ��Ա� ����
int (WINAPI *pRecogShenZhenResidencePermitAll)(char*, IDCARD_ALL&, bool, char*);

//��ס֤�ȶ�ʶ�� ����
int (WINAPI *pRecogShenZhenResidencePermitOnlyAll)(char*, IDCARD_ALL&, bool, char*);
//��Ƭʶ��
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
	HANDLE hMutex=CreateMutex(NULL,	TRUE,"֤��ʶ��ϵͳ");  
	if(hMutex==NULL || GetLastError() == ERROR_ALREADY_EXISTS)  
	{  
	
		CloseHandle(hMutex);

 		CWnd*   IDcardhWnd  =  CWnd::FindWindow(NULL,WinTitle); //�ҵ��������һ��ʵ���ľ������ť��Ϣ
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
	//����
	
	m_hMyDll=LoadLibrary(_T("idcarddll.dll"));	
	   
	if(m_hMyDll == NULL)
	{  
		MessageBox(NULL,"����ʶ����Ķ�̬��ʧ��!","֤��ʶ��ϵͳ",0); 
		m_bLoaded = false;
		return FALSE; 
	}
	   
	if(theApp.IDReader == "1")
	{
		m_CVRhMyDll=LoadLibrary("termb.dll");
		if(m_CVRhMyDll == NULL)
		{
			m_bLoaded = false;
			MessageBox(NULL,"�����Ķ�����̬��ʧ��!","֤��ʶ��ϵͳ",0); 
			return FALSE; 
		}  
	 }
	   //��ȡ�ӿڵ�ַ
	   
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
	   //��ʻ֤
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
	  //��ȡ�汾��
	   pGetVersionInfo = (char* (WINAPI *)())GetProcAddress(theApp.m_hMyDll,"GetVersionInfo");
	   pCheckWTScanner = (BOOL (WINAPI*)(char*))GetProcAddress(theApp.m_hMyDll,"CheckWTScanner");
	
	   //��ȡɨ���ס֤��ַ �㶫 
	   pRecogGDResidencePermitAll = (int (WINAPI*)(LPTSTR , IDCARD_ALL&, bool ,char*))GetProcAddress(theApp.m_hMyDll,"RecogGDResidencePermitAll");
	
	   //��ȡ�ԱȾ�ס֤��ַ �㶫
	   pRecogGDResidencePermitOnlyAll = (int (WINAPI*)(LPCTSTR , IDCARD_ALL&, bool ,char*))GetProcAddress(theApp.m_hMyDll,"RecogGDResidencePermitOnlyAll");

	   //��ȡɨ���ס֤��ַ ��ݸ
	   pRecogDongGuanResidencePermitAll = (int (WINAPI*)(char* ,IDCARD_ALL&, bool, char*))GetProcAddress(theApp.m_hMyDll, "RecogDongGuanResidencePermitAll");

	   //��ȡ�ԱȾ�ס֤��ַ ��ݸ
	   pRecogDongGuanResidencePermitOnlyAll = (int (WINAPI*)(char* ,IDCARD_ALL&, bool, char*))GetProcAddress(theApp.m_hMyDll, "RecogDongGuanResidencePermitOnlyAll");
	   
	   //��ȡɨ���ס֤��ַ ����
	   pRecogShenZhenResidencePermitAll = (int (WINAPI*)(char*, IDCARD_ALL&, bool, char*))GetProcAddress(theApp.m_hMyDll, "RecogShenZhenResidencePermitAll");
	   
	   //��ȡ�ԱȾ�ס֤��ַ ����	   
	   pRecogShenZhenResidencePermitOnlyAll= (int (WINAPI*)(char*, IDCARD_ALL&, bool, char*))GetProcAddress(theApp.m_hMyDll,"RecogShenZhenResidencePermitOnlyAll");
       
		 //��Ƭʶ��
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
		   //ж�ض�̬��
		   FreeLibrary(m_hMyDll);
		   MessageBox(NULL,"����ʶ��̬��ʧ��!","֤��ʶ��ϵͳ",0); 
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
			   MessageBox(NULL,"���ض�����̬��ʧ��!","֤��ʶ��ϵͳ",0); 
			   return FALSE; 	   
		   }			
	   }
	   //����ʶ����� 
	   if( pLoad()!=0 )
	   {   
		   MessageBox(NULL,"����ʶ�����ʧ��!","֤��ʶ��ϵͳ",0); 
		   AfxMessageBox(_T("�����豸�����Ƿ���ȷ!"));
		   //ж�ض�̬��
		   FreeLibrary(m_hMyDll);
		   m_bLoaded = false;
		   return FALSE; 
	   }
	   else
	   {
		   m_bLoaded = true;		   
	   }

	   m_VecStr.clear(); 
	   //���ʼ������
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
		   m_pMainWnd->SetWindowText(_T("֤��ʶ��ϵͳ"));

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
	ThreadExit =true;//ʹ�Ķ����߳��˳�
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
    //��ȡ��ʾ����
    GetPrivateProfileString(_T("PROPERTY"),_T("Title"),_T(""),lpszTmp,MAX_PATH,strCurrPath);
     if(_tcslen(lpszTmp)>0)
	 {
		 WinTitle = lpszTmp;
	 }
	 else
	 {
		 WinTitle = _T("֤��ʶ��ϵͳ");
	 }
	_tcscpy(lpszTmp,_T(""));
	
	//��ȡ�豸����
	 TCHAR DevicesType_tmp[MAX_PATH];
	 _tcscpy(DevicesType_tmp,_T(""));
	 GetPrivateProfileString(_T("PROPERTY"), _T("DeviceType"), _T(""), DevicesType_tmp,MAX_PATH, strCurrPath );
	 if(_tcslen(DevicesType_tmp)>0)
	 {
		 DeviceType = DevicesType_tmp;
	 }
	


	//��ȡ�豸����
	TCHAR Devicesname_tmp[MAX_PATH];
	_tcscpy(Devicesname_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("DeviceName"), _T(""), Devicesname_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(Devicesname_tmp)>0)
	{
		DeviceName = Devicesname_tmp;
	}


	//��ȡ����汾
	TCHAR Version_tmp[MAX_PATH];
	_tcscpy(Version_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("Version"), _T(""), Version_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(Version_tmp)>0)
	{
		Version = Version_tmp;
	}



	//��ȡ�����ĵ�
	TCHAR Help_tmp[MAX_PATH];
	_tcscpy(Help_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("DeviceHelp"), _T(""), Help_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(Help_tmp)>0)
	{
		DeviceHelp = Help_tmp;
	}
	
	//��ȡ����ͼƬ
	TCHAR BgImage_tmp[MAX_PATH];
	_tcscpy(BgImage_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("BgImage"), _T(""), BgImage_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(BgImage_tmp)>0)
	{
		BgImage = BgImage_tmp;
	}
	
	//��ȡ����ͼƬ
	TCHAR AdImage_tmp[MAX_PATH];
	_tcscpy(AdImage_tmp,_T(""));
	GetPrivateProfileString(_T("PROPERTY"), _T("AdImage"), _T(""), AdImage_tmp,MAX_PATH, strCurrPath );
	if(_tcslen(AdImage_tmp)>0)
	{
		AdImage = AdImage_tmp;
	}

	//��ȡ��������Ϣ
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
		strTemp.Format("��ȡ��ǰĿ¼���ִ��󣬴������Ϊ%d",nErrorCode);	
		MessageBox(NULL,strTemp,"֤��ʶ��ϵͳ",0); 
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
	//��ʼ������������
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
// 			//������ܷ��Ͷ�����Ϣ			
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
			//������ܷ��Ͷ�����Ϣ			
			pMainFrame->SendMessage(WM_MY_MESSAGE,0,0); 
			Sleep(0);
		}
		

	}
    CVR_CloseComm();
	AfxEndThread(0);
	return 0;	
}

void CIDCardApp::OnEditIdcardone() 
{ //һ��֤ɨ��ʶ��
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		pView->m_InfoDlg.m_name      = card.name;	//����
		pView->m_InfoDlg.m_sex       = card.sex;	//�Ա�
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;	//��������
		pView->m_InfoDlg.m_address   = card.address;	
		pView->m_InfoDlg.m_signdate  = card.signdate;	//ǩ����
		pView->m_InfoDlg.m_validdate = card.validterm;	//��Ч��
		pView->m_InfoDlg.m_id        = card.number;	//
		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}
	else if(result == 1)
	{		
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 2)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 3)
	{   
		
       	MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
	
}

//һ�����֤����ʶ��
void  CIDCardApp::Idcardone(CString  &file_name) 
{   
	if(!m_bLoaded)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	CopyFile(file_name, strAppPath, FALSE);   // �����ļ�	
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
		pView->m_InfoDlg.m_sError = "�û�������ļ���������!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
		
	}
	else if(result == 2)
	{
		pView->m_InfoDlg.m_sError = "���ļ�ʧ��!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 3)
	{
		pView->m_InfoDlg.m_sError = "ʶ��ʧ��!";
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
// �������֤ɨ��ʶ��
void CIDCardApp::OnEditIdcardtwo() 
{
	// TODO: Add your command handler code here
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
	
	//���ԭ������
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0);
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
        pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
	} 
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();

	
}

//�������֤����ʶ��
void CIDCardApp::Idcardtwo(CString &file_name) 
{ 
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	
	//���ԭ������
	pView->m_IdcardTwoInfo.DelLegacyData();
	pViewImage->m_DlgImage.m_ImageFilePath = "";
	

	//��ʾ��Ҫ��Dlg  ���ز���Ҫ��Dlg
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
	CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
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
		pView->m_IdcardTwoInfo.m_sError = "�û�������ļ���������!";
		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	}
	else if(result == 2)
	{
		pView->m_IdcardTwoInfo.m_sError = "���ļ�ʧ��!";
		pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		pView->m_IdcardTwoInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 3)
	{
		pView->m_IdcardTwoInfo.m_sError = "ʶ��ʧ��!";
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
//����֤ɨ��
void CIDCardApp::OnFileHuixiang() 
{

	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}

void CIDCardApp::Huixiang(CString &file_name) 
{//����֤ͼ����ʶ��
	if(!m_bLoaded)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	   CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
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
		   pView->m_InfoDlg.m_sError = "�û�������ļ���������!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
		   
	   }
	   else if(result == 2)
	   {
		   pView->m_InfoDlg.m_sError = "���ļ�ʧ��!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_InfoDlg.m_sError = "ʶ��ʧ��!";
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
//����֤����ɨ��ʶ��
void CIDCardApp::OnFileIdcardtwoback() 
{
	// TODO: Add your command handler code here
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_IdcardBackInfo.UpdateData(FALSE);
		pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();

}


void CIDCardApp::Idcardtwoback(CString  &file_name) 
{//����֤����ͼ����ʶ��
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	   CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
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
		   pView->m_IdcardBackInfo.m_sError = "�û�������ļ���������!";
		   pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardBackInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   else if(result == 2)
	   {
		   pView->m_IdcardBackInfo.m_sError = "���ļ�ʧ��!";
		   pView->m_IdcardBackInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardBackInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 3)
	   {
		   pView->m_IdcardBackInfo.m_sError = "ʶ��ʧ��!";
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
//��ʻ֤ɨ��ʶ��
void CIDCardApp::OnFileDriveport() 
{

	// TODO: Add your command handler code here

	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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

		pView->m_InfoDlg.m_name      = card.name;	//����
		pView->m_InfoDlg.m_sex       = card.sex;	//�Ա�
		pView->m_InfoDlg.m_nation    = card.people;    //���� ��Ϊ��
		pView->m_InfoDlg.m_birthdate = card.birthday;	//��������
		pView->m_InfoDlg.m_address   = card.address;	//סַ
		pView->m_InfoDlg.m_signdate  = card.signdate;   //ǩ������ ��Ϊ��
		pView->m_InfoDlg.m_validdate = card.validterm;	//��Ч�� ��Ϊ��
		pView->m_InfoDlg.m_id        = card.number;	//֤����

		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 

	}	
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 3)
	{
	       MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	   	   
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();

}

void CIDCardApp::FileDriveport(CString &file_name)
{//��ʻ֤ͼ����ʶ��
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	   CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
	   int result = pRecogDPOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	   ::DeleteFile(strAppPath);
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
	   if(result == 0)
	   {
		   pView->m_InfoDlg.m_sError = "";

		pView->m_InfoDlg.m_name      = card.name;	//����
		pView->m_InfoDlg.m_sex       = card.sex;	//�Ա�
		pView->m_InfoDlg.m_nation    = card.people;    //���� ��Ϊ��
		pView->m_InfoDlg.m_birthdate = card.birthday;	//��������
		pView->m_InfoDlg.m_address   = card.address;	//סַ
		pView->m_InfoDlg.m_signdate  = card.signdate;   //ǩ������ ��Ϊ��
		pView->m_InfoDlg.m_validdate = card.validterm;	//��Ч�� ��Ϊ��
		pView->m_InfoDlg.m_id        = card.number;	//֤����
		   
		   pView->m_InfoDlg.m_headFilePath = head_name;
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_InfoDlg.m_sError = "�û�������ļ���������!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   else if(result == 2)
	   {
		   pView->m_InfoDlg.m_sError = "���ļ�ʧ��!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_InfoDlg.m_sError = "ʶ��ʧ��!";
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

//����ɨ��ʶ��
void CIDCardApp::OnFilePassport() 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
	//  result �ӿڵ��÷���ֵ 
	int result = pRecogPassPortALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	head_name.Replace("TempPic","picture");
	file_name.Replace("TempPic","picture");
	CopyDirectory(theApp.m_strCurPath+"TempPic",theApp.m_strCurPath+"picture",FALSE);
	
	
	if(result == 0)
	{   

			pView->m_PassPortInfo.m_sError = "";
	  
			if(card.name[0]>= 'A' && card.name[0]<= 'z' )  //��������ǲ���Ӣ�ĵ�
			{
				pView->m_PassPortInfo.m_name_en = card.name; //�����  ��ֱ�Ӹ���Ӣ����
			}
			else
			{
				pView->m_PassPortInfo.m_name = card.name;  // ���� �͸�������
			}
			
			if( pView->m_PassPortInfo.m_name.Find(';') != -1)
			{
				// �����ֵ�����ȡӢ��
				pView->m_PassPortInfo.m_name_en = pView->m_PassPortInfo.m_name.Mid(pView->m_PassPortInfo.m_name.Find(';')+1,pView->m_PassPortInfo.m_name.GetLength() - pView->m_PassPortInfo.m_name.Find(';') -1);
				//��������ȡ����
				pView->m_PassPortInfo.m_name = pView->m_PassPortInfo.m_name.Mid(0,pView->m_PassPortInfo.m_name.Find(';'));
				
			}
			
			
			CString str = card.people;   //people �����أ�ǩ����
			
 			int birthplace = str.Find(';');
 			int plaseissue = str.GetLength();
			
			
			pView->m_PassPortInfo.m_birthplace = str.Mid(0,birthplace);	// ������
			pView->m_PassPortInfo.m_plaseissue = str.Mid(birthplace+1,plaseissue);	// ǩ����
			
			pView->m_PassPortInfo.m_sex       = card.sex;	// �Ա�
			pView->m_PassPortInfo.m_dateissue = card.validterm; //  ǩ������
			pView->m_PassPortInfo.m_birthdate = card.birthday;	//��������	pView->m_PassPortInfo.m_dateissue = card.validterm; //  ǩ������
			pView->m_PassPortInfo.m_signdate  = card.signdate;  //  ��Ч����
			pView->m_PassPortInfo.m_number    = card.number;	//  ֤����

			CString Tepmstr = 	card.address;	//address  ǩ�������������һ�У�������ڶ���
			int temp = 3;
			temp = Tepmstr.Find(';');

			pView->m_PassPortInfo.m_native    = Tepmstr.Left(temp);	// ����

			pView->m_PassPortInfo.m_code = Tepmstr.Right(Tepmstr.GetLength()-temp);	//������
			pView->m_PassPortInfo.m_code.Replace(";","\r\n");

			//��ʾ̨��֤�����֤����
			if (_tcscmp(card.other,_T("T"))==0)
			{
				pView->m_PassPortInfo.m_strOther = card.people;
			}

			pView->m_PassPortInfo.m_headFilePath = head_name;  //�ļ�ͷ����
			pViewImage->m_DlgImage.m_ImageFilePath = file_name;	//�ļ���


			pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
			pView->m_PassPortInfo.UpdateData(FALSE);	//�༭����ʾ����
			pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	
	}
	else if(result == 1)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_PassPortInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}

//���ձȶ�ʶ��
void CIDCardApp::Passport(CString  &file_name) 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	   CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
	   int result = pRecogPassPortOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,31,head_name.GetBuffer(head_name.GetLength()));
	   ::DeleteFile(strAppPath);
	   if(result == 0)
	   {
		   pView->m_PassPortInfo.m_sError = "";
		   
		   if(card.name[0]>= 'A' && card.name[0]<= 'z' )  //��������ǲ���Ӣ�ĵ�
		   {
			   pView->m_PassPortInfo.m_name_en = card.name; //�����  ��ֱ�Ӹ���Ӣ����
		   }
		   else
		   {
			   pView->m_PassPortInfo.m_name = card.name;  // ���� �͸�������
		   }
		   
		   if( pView->m_PassPortInfo.m_name.Find(';') != -1)
		   {
			   // �����ֵ�����ȡӢ��
			   pView->m_PassPortInfo.m_name_en = pView->m_PassPortInfo.m_name.Mid(pView->m_PassPortInfo.m_name.Find(';')+1,pView->m_PassPortInfo.m_name.GetLength() - pView->m_PassPortInfo.m_name.Find(';') -1);
			   //��������ȡ����
			   pView->m_PassPortInfo.m_name = pView->m_PassPortInfo.m_name.Mid(0,pView->m_PassPortInfo.m_name.Find(';'));
			   
		   }
		   
		   
		   CString str = card.people;   //people �����أ�ǩ����
		   
		   int birthplace = str.Find(';');
		   int plaseissue = str.GetLength();
		   
		   
		   pView->m_PassPortInfo.m_birthplace = str.Mid(0,birthplace);	// ������
		   pView->m_PassPortInfo.m_plaseissue = str.Mid(birthplace+1,plaseissue);	// ǩ����
		   
		   
		   
		   pView->m_PassPortInfo.m_sex       = card.sex;	// �Ա� 
		   pView->m_PassPortInfo.m_birthdate = card.birthday;	//��������
		   pView->m_PassPortInfo.m_dateissue = card.validterm; //  ǩ������
		   pView->m_PassPortInfo.m_signdate  = card.signdate;  //  ��Ч����
		   pView->m_PassPortInfo.m_number    = card.number;	//  ֤����
		   
		   CString Tepmstr = 	card.address;	//address  ǩ�������������һ�У�������ڶ���
		   int temp = 3;
		   temp = Tepmstr.Find(';');
		   
		   pView->m_PassPortInfo.m_native    = Tepmstr.Left(temp);	// ����
		   
		   pView->m_PassPortInfo.m_code = Tepmstr.Right(Tepmstr.GetLength()-temp);	//������
		   pView->m_PassPortInfo.m_code.Replace(";","\r\n");
		   //��ʾ̨��֤�����֤����
		   if (_tcscmp(card.other,_T("T"))==0)
		   {
			   pView->m_PassPortInfo.m_strOther = card.people;
		   }
		   pView->m_PassPortInfo.m_headFilePath = head_name;  //�ļ�ͷ����
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;	//�ļ���
		  
		   pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_PassPortInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_PassPortInfo.m_sError = "�û�������ļ���������!";
		   pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_PassPortInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   else if(result == 2)
	   {
		   pView->m_PassPortInfo.m_sError = "���ļ�ʧ��!";
		   pView->m_PassPortInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_PassPortInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_PassPortInfo.m_sError = "ʶ��ʧ��!";
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

//ǩ֤ɨ��ʶ��
void CIDCardApp::OnFileQianzheng() 
{
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
		
	
}
//ǩ֤ͼ����ʶ��
void CIDCardApp::Qianzheng(CString  &file_name) 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	   CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
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
		   //ע����Ч���޺�ǩ������
		   pView->m_InfoDlg.m_signdate  = card.validterm;
		   pView->m_InfoDlg.m_validdate = card.signdate;
		   pView->m_InfoDlg.m_id        = card.number;	
           pView->m_InfoDlg.m_stcCaption = _T("ǩ���أ�");
		   pView->m_InfoDlg.m_headFilePath = head_name;
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 1) //
		   
	   {
		   pView->m_InfoDlg.m_sError = "�û�������ļ���������!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
		   
	   }
	   else if(result == 2)
	   {
		   pView->m_InfoDlg.m_sError = "���ļ�ʧ��!";
		   pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		   pView->m_InfoDlg.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_InfoDlg.m_sError = "ʶ��ʧ��!";
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
{//���ݲ�֤ͬ�����ͽ��в�֤ͬ����ͼ��ɨ�貢���浽ָ����·����
	// TODO: Add your command handler code here
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
	//	theApp.Qianzheng();Ĭ��
		type = 10;
		break;
	case 5:		
	//	theApp.Xingshi();Ĭ��
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
	//	theApp.shibingzheng();Ĭ��
		type = 10;
		break;
	case 11:
	//	theApp.GDjuzhuzheng();Ĭ��
		type = 10;
		break;
	case 12:
	//	theApp.DGjuzhuzheng();Ĭ��
		type = 10;
		break;
	case 13:
	//	theApp.SZjuzhuzheng();Ĭ��
		type = 10;
		break;
	case 14:
	//ȫ��Ļɨ��
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
			MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0);
		else if(result == 2)
			MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0);
		else if(result == 4)
		{
			MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
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
//��ʻ֤ɨ��ʶ��
void CIDCardApp::OnFileXingshi() 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	} 
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		   pView->m_VLInfo.m_strVType = card.VehicleType;	//��������
		   pView->m_VLInfo.m_strVIN = card.VIN;				//����ʶ�����
		   pView->m_VLInfo.m_strPlateNo = card.PlateNo;		//���ƺ�
		   pView->m_VLInfo.m_strOwner = card.Owner;			//������
	       pView->m_VLInfo.m_strIssueDate = card.IssueDate;	//��֤����
		   pView->m_VLInfo.m_strEngnieNo = card.EngineNo;	//����������
		   pView->m_VLInfo.m_strAddress = card.Address;		//סַ
		   pView->m_VLInfo.m_strModel = card.Model;			//Ʒ���ͺ�

		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;

		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 


	   }
	   else if(result == 1)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
		   
	   }
	   else if(result == 2)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		   
	   }
	   else if(result == 3)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
				 
	   }
	   else if(result == 4)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		   theApp.OnAppExit();
	   }
	   
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();
	   
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock(); 

	   
}

//��ʻ֤ͼ����ʶ��
void CIDCardApp::Xingshi(CString  &file_name) 
{	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	//��ʾ���±���ֵ
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
	   CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
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
	
		   pView->m_VLInfo.m_strPlateNo = "�û�������ļ���������!";
		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	   }
	   else if(result == 2)
	   {
		   pView->m_VLInfo.m_strPlateNo = "���ļ�ʧ��!";
		   pView->m_VLInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_VLInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	   }
	   else if(result == 3)
	   {
		   pView->m_VLInfo.m_strPlateNo = "ʶ��ʧ��!";
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

//��ʱ����֤
void CIDCardApp::OnTempTwo() 
{
	// TODO: Add your command handler code here
	
	if( pRecogNewIdcardTempALL == NULL)
		return;
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		   MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
	   }
	   else if(result == 2)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0);
	   }
	   else if(result == 3)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
	   } 
	   else if(result == 4)
	   {
		   MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		   theApp.OnAppExit();
	   }
	   
	   
	   head_name.ReleaseBuffer();
	   file_name.ReleaseBuffer();
	   m_hMutex.Lock();
	   bEnableFileScan = true;
	   m_hMutex.Unlock();
	
	   
}


//��ʱ����֤ͼ����ʶ��
void CIDCardApp::TempTwo(CString  &file_name)
{
	if(pRecogNewIdcardOnlyTempALL == NULL )
	{
		return;
	}
	
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	   CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
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
		   pView->m_IdcardTwoInfo.m_sError = "�û�������ļ���������!";
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	   }
	   else if(result == 2)
	   {
		   pView->m_IdcardTwoInfo.m_sError = "���ļ�ʧ��!";
		   pView->m_IdcardTwoInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_IdcardTwoInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	   }
	   else if(result == 3)
	   {
		   pView->m_IdcardTwoInfo.m_sError = "ʶ��ʧ��!";
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
        OutputDebugString("Դ�ļ���Ϊ�գ��޷����п���!");   
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
	
    BOOL bRet = FALSE; // ��ΪԴĿ¼������Ϊ�գ����Ը�ֵһ���ᱻ�޸�
    CFileFind ff;  
    BOOL bFound = ff.FindFile(strSrcPath+"*",   0);  
    while(bFound)      // �ݹ鿽��
    {  
        bFound = ff.FindNextFile();  
        if( ff.GetFileName() == "." || ff.GetFileName() == ".." )  
            continue;
		
        CString strSubSrcPath = ff.GetFilePath();
        CString strSubDespath = strSubSrcPath;
        strSubDespath.Replace(strSrcPath, strDesPath);
		
        if( ff.IsDirectory() )
		{
            bRet = CopyDirectory(strSubSrcPath, strSubDespath, bFailIfExists);     // �ݹ鿽���ļ���
			::DeleteFile(strSubSrcPath);
		}
        else
		{
            bRet = CopyFile(strSubSrcPath, strSubDespath, bFailIfExists);   // �����ļ�
			::DeleteFile(strSubSrcPath);
		}
        if ( !bRet )
            break;
    }
    ff.Close();
    return bRet;
}

//����֤ɨ��ʶ��
void CIDCardApp::OnFileJunguanzheng() 
{
	// TODO: Add your command handler code here
			
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 2)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 3)
	{   
		
       	MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();

}
// ʿ��֤ɨ��ʶ��
void CIDCardApp::OnFileShibingzheng() 
{
	// TODO: Add your command handler code here

	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	
	if(m_VecStr.size() != 0)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 2)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 3)
	{   
		
       	MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}


void  CIDCardApp::junguanzheng(CString  &file_name) 
{  //����֤ͼ����ʶ��
	if(!m_bLoaded)
	{	
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	CopyFile(file_name, strAppPath, FALSE);   // �����ļ�	
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
		pView->m_InfoDlg.m_signdate  = card.signdate;	 //ǩ������ ��
		pView->m_InfoDlg.m_validdate = card.validterm;   // ��Ч�� ��
		pView->m_InfoDlg.m_id        = card.number;	
		pView->m_InfoDlg.m_headFilePath = head_name;
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 		
	}
	else if(result == 1) //
		
	{
		pView->m_InfoDlg.m_sError = "�û�������ļ���������!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
		
	}
	else if(result == 2)
	{
		pView->m_InfoDlg.m_sError = "���ļ�ʧ��!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 3)
	{
		pView->m_InfoDlg.m_sError = "ʶ��ʧ��!";
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

//ʿ��֤ͼ����ʶ��
void  CIDCardApp::shibingzheng(CString  &file_name) 
{   
	if(!m_bLoaded)
	{
		
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	CopyFile(file_name, strAppPath, FALSE);   // �����ļ�	
	int result = pRecogSoldieryCardOnlyALL(file_name.GetBuffer(file_name.GetLength()),card,true,2,head_name.GetBuffer(head_name.GetLength()));
	::DeleteFile(strAppPath);
	
	if(result == 0)
	{
		pView->m_InfoDlg.m_sError = "";
		pView->m_InfoDlg.m_name      = card.name;
		pView->m_InfoDlg.m_sex       = card.sex;
		pView->m_InfoDlg.m_nation    = card.people;
		pView->m_InfoDlg.m_birthdate = card.birthday;
		pView->m_InfoDlg.m_address   = card.address;  //����
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
		pView->m_InfoDlg.m_sError = "�û�������ļ���������!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
		
	}
	else if(result == 2)
	{
		pView->m_InfoDlg.m_sError = "���ļ�ʧ��!";
		pView->m_InfoDlg.InvalidateRect(NULL,TRUE); 
		pView->m_InfoDlg.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		
	}
	else if(result == 3)
	{
		pView->m_InfoDlg.m_sError = "ʶ��ʧ��!";
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
			AfxMessageBox(_T("�޷�λ�汾��Ϣ!"));
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


//��ס֤ɨ��ʶ�� �㶫
void CIDCardApp::OnFileGdJuzhuzheng() 
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	

}

//�㶫��ס֤�Ա�ʶ��
void CIDCardApp::GDjuzhuzheng(CString &file_name)
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
   
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
		pView->m_ResidentInfo.m_sError = "�û�������ļ���������!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	 }
	 else if(result == 2)
	 {
		 pView->m_ResidentInfo.m_sError = "���ļ�ʧ��!";
		 pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		 pView->m_ResidentInfo.UpdateData(FALSE);
		 pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	 }
	 else if(result == 3)
	 {
		 pView->m_ResidentInfo.m_sError = "ʶ��ʧ��!";
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

//��ס֤ɨ��ʶ�� ��ݸ
void CIDCardApp::OnFileDgJuzhuzheng() 
{
	// TODO: Add your command handler code here

	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();



}


void CIDCardApp :: DGjuzhuzheng(CString &file_name)
{// ��ס֤�ȶ�ʶ�� ��ݸ
    if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
	
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
		pView->m_ResidentInfo.m_sError = "�û�������ļ���������!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
    else if(result == 2)
	{
		pView->m_ResidentInfo.m_sError = "���ļ�ʧ��!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	}
	else if(result == 3)
	{
		pView->m_ResidentInfo.m_sError = "ʶ��ʧ��!";
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


//��ס֤ɨ��ʶ�� ����
void CIDCardApp::OnFileSzJuzhuzheng() 
{
	// TODO: Add your command handler code here
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 3)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ʶ��ʧ��!","֤��ʶ��ϵͳ",0);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	
	head_name.ReleaseBuffer();
	file_name.ReleaseBuffer();
	m_hMutex.Lock();
	bEnableFileScan = true;
	m_hMutex.Unlock();
	
}

//��ס֤�ȶ�ʶ�� ����
void CIDCardApp::SZjuzhuzheng(CString &file_name)
{
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
	CopyFile(head_name, strAppPath, FALSE);   // �����ļ�
	
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
		pView->m_ResidentInfo.m_sError = "�û�������ļ���������!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
	else if(result == 2)
	{
		pView->m_ResidentInfo.m_sError = "���ļ�ʧ��!";
		pView->m_ResidentInfo.InvalidateRect(NULL,TRUE); 
		pView->m_ResidentInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	}
	else if(result == 3)
	{
		pView->m_ResidentInfo.m_sError = "ʶ��ʧ��!";
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
//��������ʾ��ǰ�����ļ���
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

//��Ƭʶ��
void CIDCardApp::RecognizeBusinessCardFromFile(const CString &file_name)
{
  
	if(!m_bLoaded)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
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
		pView->m_BusinessCardInfo.m_strName = "�û�������ļ���������!";
		pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE); 
		pView->m_BusinessCardInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 	
	}
	else if(result == 2)
	{
		   pView->m_BusinessCardInfo.m_strName = "���ļ�ʧ��!";
		   pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE); 
		   pView->m_BusinessCardInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE); 
		   
	 }
	 else if(result == 3)
	 {
		   pView->m_BusinessCardInfo.m_strName = "ʶ��ʧ��!";
		   pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE);  
		   pView->m_BusinessCardInfo.UpdateData(FALSE);
		   pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		   pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);			
	 }
	 else if (result==5)
	 {
		 pView->m_BusinessCardInfo.m_strName = _T("�ݲ�֧����Ƭʶ��!");
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
		MessageBox(this->GetMainWnd()->m_hWnd,"ɨ��ʶ����ļ���ʧ�ܣ��޷�����ʶ��!","֤��ʶ��ϵͳ",0); 
		return;
	}
	if(m_VecStr.size() != 0)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"��������ʶ��δ���!","֤��ʶ��ϵͳ",0); 
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
		MessageBox(this->GetMainWnd()->m_hWnd,"�ɼ�ͼ��������!","֤��ʶ��ϵͳ",0); 
	}
	else if(result == 2)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"�û�������ļ�·����������Ҫ��!","֤��ʶ��ϵͳ",0); 
		
	}
	else if(result == 3)
	{
		pView->m_BusinessCardInfo.m_strName = "ʶ��ʧ��!";
		pView->m_BusinessCardInfo.InvalidateRect(NULL,TRUE);  
		pView->m_BusinessCardInfo.UpdateData(FALSE);
		pViewImage->m_DlgImage.m_ImageFilePath = file_name;
		pViewImage->m_DlgImage.InvalidateRect(NULL,TRUE);
	}
	else if(result == 4)
	{
		MessageBox(this->GetMainWnd()->m_hWnd,"Ŀǰ�����豸û������!","֤��ʶ��ϵͳ",0); 
		theApp.OnAppExit();
	}
	else if (result==5)
	{
		pView->m_BusinessCardInfo.m_strName = _T("�ݲ�֧����Ƭʶ��!");
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
