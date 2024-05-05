
// EPRSampleDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "EPRSampleDemo.h"
#include "EPRSampleDemoDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <locale>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DG0 0x00000001
#define DG1 0x00000002
#define DG2 0x00000004
#define DG3 0x00000008
#define DG4 0x00000010
#define DG5 0x00000020
#define DG6 0x00000040
#define DG7 0x00000080
#define DG8 0x00000100
#define DG9 0x00000200
#define DG10 0x00000400
#define DG11 0x00000800
#define DG12 0x00001000
#define DG13 0x00002000
#define DG14 0x00004000
#define DG15 0x00008000
#define DG16 0x00010000
#define DG17 0x00020000

#define WHITEIMAGE 0x00000001
#define IRIMAGE 0x00000002
#define UVIMAGE 0x00000004
#define PAGEHEAD 0x00000008
#define CHIPHEAD 0x00000010

#define AUTO_DETECT_PASSPORT 911
const int MAX_RESULT_LEN = 42000;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEPRSampleDemoDlg dialog


CEPRSampleDemoDlg::CEPRSampleDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEPRSampleDemoDlg::IDD, pParent)
	, m_bCheckVerity(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_strUserID = _T("");
	m_strResult = _T("");
	m_strDGResult = _T("");
	m_bWhiteImage = false;
	m_bIRImage = false;
	m_bUVImage = false;
	m_bPageHead = false;
	m_bChipHead = false;
	m_bVIZ = false;
	m_ReadDGFlag = 0;
	m_SaveImageFlag = 0;
	m_strWorkPath = _T("");
	m_strImagePath = _T("");

	m_OldRect.SetRect(0, 0, 0, 0);
	m_ctrlInfo.RemoveAll();

	m_bInitSuccess = false;
	m_hIDCard = NULL;
	m_nCardType = 0;
	m_strErrMsg = _T("");
	m_nIDNum = 13;
	nImageType = 0;
	m_nImageIndex = 0;
	m_bLoad = false;
}

void CEPRSampleDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_RESULT, m_EditResult);
	DDX_Control(pDX, IDC_EDIT_DG_RESULT, m_EditDG);
	DDX_Control(pDX, IDC_EDIT_DLLPATH, m_editLibPath);
	DDX_Control(pDX, IDC_EDIT_IMAGEPATH, m_editPicPath);
	DDX_Control(pDX, IDC_EDIT_CONFIGPATH, m_editFigPath);
	DDX_Check(pDX, IDC_CHECK_VERIFY, m_bCheckVerity);
}

BEGIN_MESSAGE_MAP(CEPRSampleDemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOADKERNEL, &CEPRSampleDemoDlg::OnBnClickedButtonLoadkernel)
	ON_BN_CLICKED(IDC_BUTTON_FREEKERNEL, &CEPRSampleDemoDlg::OnBnClickedButtonFreekernel)
	ON_BN_CLICKED(IDC_BUTTON_VERSION_INFO, &CEPRSampleDemoDlg::OnBnClickedButtonVersionInfo)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_NAME, &CEPRSampleDemoDlg::OnBnClickedButtonDeviceName)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_ISLINE, &CEPRSampleDemoDlg::OnBnClickedButtonDeviceIsline)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_SEQUENCE, &CEPRSampleDemoDlg::OnBnClickedButtonDeviceSequence)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_RECOG, &CEPRSampleDemoDlg::OnBnClickedButtonRecog)
	ON_BN_CLICKED(IDC_BTN_PRE, &CEPRSampleDemoDlg::OnBnClickedBtnPre)
	ON_BN_CLICKED(IDC_BTN_NEXT, &CEPRSampleDemoDlg::OnBnClickedBtnNext)
	ON_BN_CLICKED(IDC_BTN_READSIDCARD, &CEPRSampleDemoDlg::OnBnClickedBtnReadsidcard)
	ON_BN_CLICKED(IDC_BTN_BROWSE_DLLPATH, &CEPRSampleDemoDlg::OnBnClickedBtnBrowseDllpath)
	ON_BN_CLICKED(IDC_BTN_PICPATH, &CEPRSampleDemoDlg::OnBnClickedBtnPicpath)
	ON_CBN_SELCHANGE(IDC_COMBO_IDENT, &CEPRSampleDemoDlg::OnCbnSelchangeComboIdent)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CEPRSampleDemoDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_SEQUENCE2, &CEPRSampleDemoDlg::OnBnClickedButtonDeviceSequence2)
	ON_BN_CLICKED(IDC_CHECK_VERIFY, &CEPRSampleDemoDlg::OnBnClickedCheckVerify)
END_MESSAGE_MAP()


// CEPRSampleDemoDlg message handlers

BOOL CEPRSampleDemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	GetClientRect(m_OldRect);
	SetControlInfo(IDC_STATIC_OPERATOR);
	SetControlInfo(IDC_STATIC_CALL_STEP);
	SetControlInfo(IDC_STATIC_USERID);
	SetControlInfo(IDC_EDIT_USERID);
	SetControlInfo(IDC_BUTTON_LOADKERNEL);
	SetControlInfo(IDC_BUTTON_FREEKERNEL);
	SetControlInfo(IDC_BTN_READSIDCARD);
	SetControlInfo(IDC_STATIC_READ_DG);
	SetControlInfo(IDC_CHECK_DG0);
	SetControlInfo(IDC_CHECK_DG1);
	SetControlInfo(IDC_CHECK_DG2);
	SetControlInfo(IDC_CHECK_DG3);
	SetControlInfo(IDC_CHECK_DG4);
	SetControlInfo(IDC_CHECK_DG5);
	SetControlInfo(IDC_CHECK_DG6);
	SetControlInfo(IDC_CHECK_DG7);
	SetControlInfo(IDC_CHECK_DG8);
	SetControlInfo(IDC_CHECK_DG9);
	SetControlInfo(IDC_CHECK_DG10);
	SetControlInfo(IDC_CHECK_DG11);
	SetControlInfo(IDC_CHECK_DG12);
	SetControlInfo(IDC_CHECK_DG13);
	SetControlInfo(IDC_CHECK_DG14);
	SetControlInfo(IDC_CHECK_DG15);
	SetControlInfo(IDC_CHECK_DG16);
	SetControlInfo(IDC_CHECK_DG17);
	SetControlInfo(IDC_STATIC_SAVE_IMAGETYPE);
	SetControlInfo(IDC_CHECK_WHITE);
	SetControlInfo(IDC_CHECK_IR);
	SetControlInfo(IDC_CHECK_UV);
	SetControlInfo(IDC_CHECK_PAGE_HEAD);
	SetControlInfo(IDC_CHECK_CHIP_HEAD);
	SetControlInfo(IDC_STATIC_READ_VIZ);
	SetControlInfo(IDC_CHECK_VIZ);
	SetControlInfo(IDC_STATIC_OTHER_INTERFACE);
	SetControlInfo(IDC_BUTTON_VERSION_INFO);
	SetControlInfo(IDC_BUTTON_DEVICE_NAME);
	SetControlInfo(IDC_BUTTON_DEVICE_ISLINE);
	SetControlInfo(IDC_BUTTON_DEVICE_SEQUENCE);
	SetControlInfo(IDC_BUTTON_DEVICE_SEQUENCE2);
	SetControlInfo(ID_STATIC_RESULT);
	SetControlInfo(IDC_EDIT_RESULT);
	SetControlInfo(IDC_EDIT_DG_RESULT);
	SetControlInfo(IDC_STATIC_IDNUM);
	SetControlInfo(IDC_EDIT_IDNUM);
	SetControlInfo(IDC_BUTTON_RECOG);
	SetControlInfo(IDC_BTN_BROWSE_DLLPATH);
	SetControlInfo(IDC_EDIT_DLLPATH);
	SetControlInfo(IDC_BUTTON_SETTING);
	SetControlInfo(IDC_EDIT_CONFIGPATH);
	SetControlInfo(IDC_COMBO_IDENT);
	SetControlInfo(IDC_STATIC_READ_VIZ2);
	SetControlInfo(IDC_BTN_PICPATH);
	SetControlInfo(IDC_EDIT_IMAGEPATH);
	SetControlInfo(IDC_STATIC_PICTURE);
	SetControlInfo(IDC_BTN_PRE);
	SetControlInfo(IDC_BTN_NEXT);
	SetControlInfo(IDC_EDIT_SDKVERSION);
	SetControlInfo(IDC_EDIT_DEVICENAME);
	SetControlInfo(IDC_EDIT_DEVICESTATUS);
	SetControlInfo(IDC_EDIT_SERIALNUMBER);

	pInitIDCard = NULL;
	pFreeIDCard = NULL;
	pGetRecogResultEx = NULL;
	pSetRecogDG = NULL;
	pSetRecogVIZ = NULL;
	pSetSaveImageType = NULL;
	pResetIDCardID = NULL;
	pAddIDCardID = NULL;
	pDetectDocument = NULL;
	pGetVersionInfo = NULL;
	pCheckDeviceOnline = NULL;
	pGetCurrentDevice = NULL;
	pGetDeviceSN = NULL;
	pSaveImageEx = NULL;
	pGetFieldNameEx = NULL;
	pAutoProcessIDCard = NULL;
	pSetConfigByFile = NULL;
	pAutoVerifyIDCard = NULL;
	/*pGetVerificationClassCount = NULL;
	pGetVerificationClassName = NULL;
	pGetVerificationItemCountInClass = NULL;
	pGetVerificationItem = NULL;
	pGetVerificationItemName = NULL;
	pGetReferencedElementCount = NULL;
	pGetReferencedElement = NULL;*/
	m_strWorkPath = GetWorkPath();
	m_strImagePath = m_strWorkPath;

	CString tmp(_T(""));
	tmp.Format(_T("%d"), m_nIDNum);
	GetDlgItem(IDC_EDIT_IDNUM)->SetWindowText(tmp);
	GetDlgItem(IDC_EDIT_CONFIGPATH)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_DLLPATH)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_IMAGEPATH)->SetWindowText(GetWorkPath());

	((CButton*)GetDlgItem(IDC_CHECK_DG1))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK_DG2))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK_DG11))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK_DG12))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK_WHITE))->SetCheck(1);
	((CButton*)GetDlgItem(IDC_CHECK_IR))->SetCheck(1);

	GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_FREEKERNEL)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_VERSION_INFO)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEVICE_NAME)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEVICE_ISLINE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEVICE_SEQUENCE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEVICE_SEQUENCE2)->EnableWindow(false);
	GetDlgItem(IDC_COMBO_IDENT)->EnableWindow(false);

	wstring wStrAuto = L"Automatic identification";
	wstring wStrManual = L"Manual identification";
	LPCWSTR strAuto = wStrAuto.c_str();
	LPCWSTR strManual = wStrManual.c_str();

	CComboBox* chooseBox = (CComboBox*)GetDlgItem(IDC_COMBO_IDENT);
	chooseBox->AddString(strAuto);
	chooseBox->AddString(strManual);
	chooseBox->SetCurSel(0);

	CString strIdent;
	GetDlgItem(IDC_COMBO_IDENT)->GetWindowText(strIdent);
	if ("Automatic identification" == strIdent)
	{
		GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_READSIDCARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IDNUM)->EnableWindow(FALSE);
	}
	else if ("Manual identification" == strIdent)
	{
		GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_READSIDCARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IDNUM)->EnableWindow(TRUE);
	}
	else
		NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CEPRSampleDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CEPRSampleDemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CEPRSampleDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEPRSampleDemoDlg::OnBnClickedButtonLoadkernel()
{
	GetDlgItem(IDC_EDIT_USERID)->GetWindowText(m_strUserID);

	int nRet = InitCardDll();
	if (0 != nRet)
	{
		m_bInitSuccess = false;
		switch (nRet)
		{
		case 1001:
		{
			m_strErrMsg = _T("Load IDCard.dll failed, GetLastError = ");
			CString str;
			str.Format(_T("%d\n"), GetLastError());
			m_strErrMsg += str;
		}
			break;
		case 1002:
			m_strErrMsg = _T("Export IDCard.dll API failed.\n");
			break;
		case 1:
			m_strErrMsg = _T("UserID error.\n");
			break;
		case 2:
			m_strErrMsg = _T("Device initialization failed.\n");
			break;
		case 3:
			m_strErrMsg = _T("Failed to initialize the certificate core.\n");
			break;
		case 4:
			m_strErrMsg = _T("The authorization file was not found.\n");
			break;
		case 5:
			m_strErrMsg = _T("Failed to load template file.\n");
			break;
		case 6:
			m_strErrMsg = _T("Failed to initialize card reader.\n");
			break;
		default:
			break;
		}
		GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(m_strErrMsg);
		return;
	}
	else
	{
		m_bInitSuccess = true;
		m_strErrMsg = _T("");
		m_strErrMsg += _T("Success to initialize the recognition engine.\r\n");

		GetDlgItem(IDC_BUTTON_LOADKERNEL)->EnableWindow(false);
		GetDlgItem(IDC_COMBO_IDENT)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_FREEKERNEL)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_VERSION_INFO)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_DEVICE_NAME)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_DEVICE_ISLINE)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_DEVICE_SEQUENCE)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_DEVICE_SEQUENCE2)->EnableWindow(true);

		nRet = LoadDll();
		switch (nRet)
		{
		case 0:
			m_strErrMsg += _T("Success to initialize the SID module.\r\n");
			break;
		case -1:
		{
			m_strErrMsg += _T("Load sdtapi.dll failed, GetLastError = ");
			CString str;
			str.Format(_T("%d.\n"), GetLastError());
			m_strErrMsg += str;
		}
			break;
		case -2:
			m_strErrMsg += _T("Export sdtapi.dll API failed.\n");
			break;
		case -3:
		{
			m_strErrMsg += _T("Load WltRS.dll failed, GetLastError = ");
			CString str;
			str.Format(_T("%d.\n"), GetLastError());
			m_strErrMsg += str;
		}
			break;
		case -4:
			m_strErrMsg += _T("Export WltRS.dll API failed.\n");
			break;
		case -5:
			m_strErrMsg += _T("Open port failed.\n");
			break;
		default:
			break;
		}
		GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(m_strErrMsg);
		OnBnClickedButtonVersionInfo();
		OnBnClickedButtonDeviceName();
		OnBnClickedButtonDeviceIsline();
		OnBnClickedButtonDeviceSequence();
		OnBnClickedButtonDeviceSequence2();
	}

	CString strIdent;
	GetDlgItem(IDC_COMBO_IDENT)->GetWindowText(strIdent);
	if ("Automatic identification" == strIdent)
	{
		GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_READSIDCARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IDNUM)->EnableWindow(FALSE);
	}
	else if ("Manual identification" == strIdent)
	{
		GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_READSIDCARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IDNUM)->EnableWindow(TRUE);
	}
	else
		NULL;

	CString strFigPath;
	m_editFigPath.GetWindowText(strFigPath);
	if (!strFigPath.IsEmpty())
	{
		nRet = pSetConfigByFile(strFigPath.AllocSysString());
	}
	//ע�͵�ADDIdcard֮��,IDCard.dll�д��ڡ��Ƿ�������Ҫʶ���֤�����͡����жϣ��ʼ��غ���֮ǰ������������ļ�
	strIdent = "";
	GetDlgItem(IDC_COMBO_IDENT)->GetWindowText(strIdent);
	if ("Automatic identification" == strIdent)
		SetTimer(AUTO_DETECT_PASSPORT, 100, NULL);
	else
		NULL;
}


int CEPRSampleDemoDlg::InitCardDll()
{
	if (m_bInitSuccess)
		return 0;
	USES_CONVERSION;
	CString strDllPath = _T("");
	CString m_strDllPath = _T("");
	GetDlgItem(IDC_EDIT_DLLPATH)->GetWindowTextW(strDllPath);
	if (strDllPath.GetLength())
	{
		m_strDllPath += strDllPath;
		m_strDllPath += _T("IDCard.dll");
		m_hIDCard = LoadLibraryEx(m_strDllPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	}
	else
	{
		m_hIDCard = LoadLibrary(_T("IDCard.dll"));
	}
	if (NULL == m_hIDCard)
		return 1001;

	pInitIDCard = (int (WINAPI*)(LPCTSTR, int, LPCTSTR))GetProcAddress(m_hIDCard, "InitIDCard");
	pFreeIDCard = (void (WINAPI *)())GetProcAddress(m_hIDCard, "FreeIDCard");
	pGetRecogResultEx = (int (WINAPI *)(int, int, LPTSTR, int&))GetProcAddress(m_hIDCard, "GetRecogResultEx");
	pGetFieldNameEx = (int (WINAPI*)(int, int, LPTSTR, int&))GetProcAddress(m_hIDCard, "GetFieldNameEx");
	pSetRecogDG = (void (WINAPI*)(int))GetProcAddress(m_hIDCard, "SetRecogDG");
	pSetSaveImageType = (void (WINAPI*)(int))GetProcAddress(m_hIDCard, "SetSaveImageType");
	pSetRecogVIZ = (void (WINAPI*)(bool))GetProcAddress(m_hIDCard, "SetRecogVIZ");
	pResetIDCardID = (void (WINAPI *)())GetProcAddress(m_hIDCard, "ResetIDCardID");
	pAddIDCardID = (int (WINAPI *)(int, int *, int))GetProcAddress(m_hIDCard, "AddIDCardID");
	pDetectDocument = (int (WINAPI *)())GetProcAddress(m_hIDCard, "DetectDocument");
	pGetVersionInfo = (bool (WINAPI *)(LPCTSTR, int))GetProcAddress(m_hIDCard, "GetVersionInfo");
	pCheckDeviceOnline = (BOOL(WINAPI *)())GetProcAddress(m_hIDCard, "CheckDeviceOnline");
	pGetCurrentDevice = (BOOL(WINAPI *)(LPTSTR, int))GetProcAddress(m_hIDCard, "GetCurrentDevice");
	pGetDeviceSN = (int (WINAPI *)(LPTSTR, int))GetProcAddress(m_hIDCard, "GetDeviceSN");
	pSaveImageEx = (int (WINAPI*)(LPCTSTR, int))GetProcAddress(m_hIDCard, "SaveImageEx");
	pSaveImageRaw = (int (WINAPI*)(LPCWSTR, int))GetProcAddress(m_hIDCard, "SaveImageRaw");
	pAutoProcessIDCard = (int (WINAPI*)(int&))GetProcAddress(m_hIDCard, "AutoProcessIDCard");
	pSetConfigByFile = (int(WINAPI*)(LPCWSTR))GetProcAddress(m_hIDCard, "SetConfigByFile");
	pAutoVerifyIDCard = (int(WINAPI*)(int&))GetProcAddress(m_hIDCard, "AutoVerifyIDCard");

	if (NULL == pInitIDCard || NULL == pFreeIDCard || NULL == pGetRecogResultEx || NULL == pAddIDCardID
		|| NULL == pDetectDocument || NULL == pGetVersionInfo || NULL == pCheckDeviceOnline || NULL == pGetCurrentDevice 
		|| NULL == pGetDeviceSN || NULL == pSaveImageEx || NULL == pAutoProcessIDCard || NULL == pGetFieldNameEx 
		|| NULL == pSetConfigByFile || NULL == pSetRecogDG || NULL == pSetSaveImageType || NULL == pSetRecogVIZ 
		|| NULL == pResetIDCardID || NULL == pAutoVerifyIDCard)
	{
		m_bInitSuccess = false;
		FreeLibrary(m_hIDCard);
		m_hIDCard = NULL;
		return 1002;
	}
	else
	{
		// ע�⣺����Ҫ���鹦�� pInitIDCard��2�β�Ӧ����4
		//       �粻��Ҫ���鹦�� pInitIDCard��2�β�Ӧ����0
		int nRet = pInitIDCard(m_strUserID, 4, strDllPath);
		if (0 != nRet)
		{
			FreeCardDll();
			return nRet;
		}

		m_bInitSuccess = true;
		return 0;
	}
}


void CEPRSampleDemoDlg::OnBnClickedButtonFreekernel()
{
	FreeCardDll();
}

void CEPRSampleDemoDlg::FreeCardDll()
{
	KillTimer(AUTO_DETECT_PASSPORT);
	if (NULL != pFreeIDCard)
		pFreeIDCard();

	if (NULL != m_hIDCard)
		FreeLibrary(m_hIDCard);
	if (m_bLoad)
		fpSDT_ClosePort(m_nOpenPort);
	m_bLoad = false;
	m_hIDCard = NULL;
	m_bInitSuccess = false;
	pInitIDCard = NULL;
	pFreeIDCard = NULL;
	pGetRecogResultEx = NULL;
	pGetFieldNameEx = NULL;
	pSetRecogDG = NULL;
	pSetSaveImageType = NULL;
	pSetRecogVIZ = NULL;
	pResetIDCardID = NULL;
	pAddIDCardID = NULL;
	pDetectDocument = NULL;
	pGetVersionInfo = NULL;
	pCheckDeviceOnline = NULL;
	pGetCurrentDevice = NULL;
	pGetDeviceSN = NULL;
	pSaveImageEx = NULL;
	pAutoProcessIDCard = NULL;
	pSetConfigByFile = NULL;
	pAutoVerifyIDCard = NULL;
	GetDlgItem(IDC_COMBO_IDENT)->EnableWindow(false);
	m_strUserID = _T("");
	m_strResult = _T("");
	m_strDGResult = _T("");
	m_bWhiteImage = false;
	m_bIRImage = false;
	m_bUVImage = false;
	m_bPageHead = false;
	m_bChipHead = false;
	m_bVIZ = false;
	m_OldRect.SetRect(0, 0, 0, 0);
	m_ctrlInfo.RemoveAll();
	m_nCardType = 0;
	m_strErrMsg = _T("");
	m_strWorkPath = _T("");
	m_strImagePath = _T("");

	GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(_T("Success to free the recognition engine."));
	GetDlgItem(IDC_EDIT_DG_RESULT)->SetWindowText(_T(""));
	GetDlgItem(IDC_BUTTON_LOADKERNEL)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_FREEKERNEL)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_VERSION_INFO)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEVICE_NAME)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEVICE_ISLINE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEVICE_SEQUENCE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_DEVICE_SEQUENCE2)->EnableWindow(false);
	GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_SDKVERSION)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_DEVICENAME)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_DEVICESTATUS)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_SERIALNUMBER)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_RFID_SERIALNUMBER)->SetWindowText(_T(""));
	GetDlgItem(IDC_EDIT_IDNUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_READSIDCARD)->EnableWindow(FALSE);
	CComboBox* chooseBox = (CComboBox*)GetDlgItem(IDC_COMBO_IDENT);
	chooseBox->SetCurSel(0);

}

void CEPRSampleDemoDlg::OnBnClickedButtonVersionInfo()
{
	if (!m_bInitSuccess)
		return;

	TCHAR szBuf[1024] = { 0 };
	pGetVersionInfo(szBuf, 1024);
	m_strResult = _T("SDK version:");
	m_strResult += CString(szBuf);
	m_strResult += _T("\r\n");

	GetDlgItem(IDC_EDIT_SDKVERSION)->SetWindowText(m_strResult);
}


void CEPRSampleDemoDlg::OnBnClickedButtonDeviceName()
{
	if (!m_bInitSuccess)
		return;

	TCHAR szBuf[1024] = { 0 };
	if (pGetCurrentDevice(szBuf, 1024))
	{
		m_strResult = _T("Device Name:");
		m_strResult += CString(szBuf);
		m_strResult += _T("\r\n");
	}
	else
		m_strResult = _T("Failed to get Device Name\r\n");

	GetDlgItem(IDC_EDIT_DEVICENAME)->SetWindowText(m_strResult);
}


void CEPRSampleDemoDlg::OnBnClickedButtonDeviceIsline()
{
	if (!m_bInitSuccess)
		return;

	if (pCheckDeviceOnline())
		m_strResult = _T("The device is online.\r\n");
	else
		m_strResult = _T("The device is offline.\r\n");

	GetDlgItem(IDC_EDIT_DEVICESTATUS)->SetWindowText(m_strResult);
}


void CEPRSampleDemoDlg::OnBnClickedButtonDeviceSequence()
{
	if (!m_bInitSuccess)
		return;

	TCHAR szBuf[1024] = { 0 };
	int nRet = pGetDeviceSN(szBuf, 1024);
	if (0 == nRet)
	{
		m_strResult = _T("");
		m_strResult += CString(szBuf);
		m_strResult += _T("\r\n");
	}
	else
		m_strResult = _T("Failed to get Device Sequence\r\n");

	GetDlgItem(IDC_EDIT_SERIALNUMBER)->SetWindowText(m_strResult);
}

int AscllToInt(int nVal)
{
	int n;
	if ((nVal+48) >= '0'&&(nVal+48) <= '9')
		n = nVal + 48;
	//if ((nVal+97) >= 'a'&&(nVal+97) <= 'f')
	//	n = nVal + 97;
	if ((nVal+55) >= 'A'&&(nVal+55) <= 'F')
		n = nVal + 55;
	return n;
}
void CEPRSampleDemoDlg::OnBnClickedButtonDeviceSequence2()
{
	if (!m_bLoad)
		return;

	char szBuf[1024] = { 0 };
	int nRet = fpSDT_GetSAMIDToStr(m_nOpenPort,szBuf,0);
	if (nRet == 0x90)
	{
		m_strResult.Format(_T("%S"),szBuf);
	}
	else
		m_strResult = _T("Failed to get Device Sequence\r\n");

	GetDlgItem(IDC_EDIT_RFID_SERIALNUMBER)->SetWindowText(m_strResult);
	/*****************************************************************/
	unsigned char szHexBuf[64] = { 0 };
	char sHexBufSrc[129] = { 0 };
	nRet = SDT_GetSAMID(m_nOpenPort, szHexBuf, 0);
	if (nRet == 0x90)
	{
		int i = 0;
		for (int j = 0; j < sizeof(szHexBuf); j++)
		{
			int nHex = szHexBuf[j] / 16;
			sHexBufSrc[i++] = AscllToInt(nHex);
			sHexBufSrc[i++] = AscllToInt(szHexBuf[j] % 16);
		}

		//����SDT_GetSAMID��ȡ֮��ת��16��������
		string sHexBufDest(sHexBufSrc);
		string::iterator it;
		for (it = sHexBufDest.end() - 1; it != sHexBufDest.begin(); it--)
		{
			if (*it == '0')
			{
				sHexBufDest.erase(it);
			}
			else
				break;
		}
		return;
	}
}

void CEPRSampleDemoDlg::SetControlInfo(DWORD ID)
{
	m_ctrlInfo.Add(ID);
}

void CEPRSampleDemoDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	if (0 == cx || 0 == cy)
		return;

	CRect WndRect;
	CWnd* pWnd = NULL;
	double x_prop = (double)cx / (double)(m_OldRect.Width());
	double y_prop = (double)cy / (double)(m_OldRect.Height());

	for (int i = 0; i < m_ctrlInfo.GetSize(); i++)
	{
		pWnd = GetDlgItem(m_ctrlInfo[i]);
		if (NULL == pWnd) continue;
		pWnd->GetWindowRect(&WndRect);				// 
		ScreenToClient(&WndRect);
		WndRect.left = (int)(WndRect.left*x_prop);
		WndRect.right = (int)(WndRect.right*x_prop);
		WndRect.top = (int)(WndRect.top*y_prop);
		WndRect.bottom = (int)(WndRect.bottom*y_prop);
		pWnd->MoveWindow(&WndRect);
	}

	GetClientRect(&m_OldRect);
}


void CEPRSampleDemoDlg::OnDestroy()
{
	FreeCardDll();
	CDialogEx::OnDestroy();
}


void CEPRSampleDemoDlg::GetRecogCondition()
{
	m_ReadDGFlag = 0;
	m_SaveImageFlag = 0;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG0))->GetCheck())
		m_ReadDGFlag |= DG0;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG1))->GetCheck())
		m_ReadDGFlag |= DG1;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG2))->GetCheck())
		m_ReadDGFlag |= DG2;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG3))->GetCheck())
		m_ReadDGFlag |= DG3;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG4))->GetCheck())
		m_ReadDGFlag |= DG4;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG5))->GetCheck())
		m_ReadDGFlag |= DG5;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG6))->GetCheck())
		m_ReadDGFlag |= DG6;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG7))->GetCheck())
		m_ReadDGFlag |= DG7;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG8))->GetCheck())
		m_ReadDGFlag |= DG8;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG9))->GetCheck())
		m_ReadDGFlag |= DG9;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG10))->GetCheck())
		m_ReadDGFlag |= DG10;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG11))->GetCheck())
		m_ReadDGFlag |= DG11;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG12))->GetCheck())
		m_ReadDGFlag |= DG12;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG13))->GetCheck())
		m_ReadDGFlag |= DG13;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG14))->GetCheck())
		m_ReadDGFlag |= DG14;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG15))->GetCheck())
		m_ReadDGFlag |= DG15;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG16))->GetCheck())
		m_ReadDGFlag |= DG16;

	if (((CButton*)GetDlgItem(IDC_CHECK_DG17))->GetCheck())
		m_ReadDGFlag |= DG17;

	nImageType = 0;
	if (((CButton*)GetDlgItem(IDC_CHECK_WHITE))->GetCheck())
	{
		m_SaveImageFlag |= WHITEIMAGE;
		nImageType += 1;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_IR))->GetCheck())
	{
		m_SaveImageFlag |= IRIMAGE;
		nImageType += 2;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_UV))->GetCheck())
	{
		m_SaveImageFlag |= UVIMAGE;
		nImageType += 4;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_PAGE_HEAD))->GetCheck())
	{
		m_SaveImageFlag |= PAGEHEAD;
		nImageType += 8;
	}

	if (((CButton*)GetDlgItem(IDC_CHECK_CHIP_HEAD))->GetCheck())
	{
		m_SaveImageFlag |= CHIPHEAD;
		nImageType += 16;
	}


	if (((CButton*)GetDlgItem(IDC_CHECK_VIZ))->GetCheck())
		m_bVIZ = true;
	else
		m_bVIZ = false;
}


void CEPRSampleDemoDlg::ReadCard()
{
	GetRecogCondition();
	pSetRecogDG(m_ReadDGFlag);
	pSetSaveImageType(nImageType);
	pSetRecogVIZ(m_bVIZ);

	m_strResult = _T("");
	m_strDGResult = _T("");
	int nRet = 0;

	m_nCardType = 0;
	nRet = pAutoProcessIDCard(m_nCardType);
	if (nRet > 0||nRet==-1115 || nRet == -8 || nRet == -1117)
	{
		m_strResult = _T("Success to read the card\r\n");
		GetContent();
		if (1 == m_nCardType)
		{
			m_strDGResult = _T("Success to read the card\r\n");
			GetDGContent();
		}
		else
			m_strDGResult = _T("no any DG info");
	}
	else
	{
		m_strResult.Format(_T("%s%d"), _T("Return Value:"), nRet);
		m_strResult += "\r\n";
		m_strResult += _T("fail to read the card\r\n");
	}

	CString strFileName = _T("");
	CString strImagePath = _T("");
	GetDlgItem(IDC_EDIT_IMAGEPATH)->GetWindowTextW(strImagePath);
	if (strImagePath.GetLength() > 1)
		strFileName += strImagePath;
	else
		strFileName += m_strImagePath;
	time_t now = time(0);
	tm ntime;
	gmtime_s(&ntime, &now);
	CString strImgPath;
	strImgPath.Format(_T("%02d%02d%02d%02d%02d.jpg"), ntime.tm_mon + 1, ntime.tm_mday, ntime.tm_hour + 8, ntime.tm_min, ntime.tm_sec);
	strFileName += strImgPath;
	int tmp = pSaveImageEx((LPCTSTR)strFileName, m_SaveImageFlag);
	SaveImagePath(strFileName, nImageType);
	if (1 == m_nCardType || 2 == m_nCardType)
		ShowImage(m_vecImagePath[0]); 
	else 
		GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(FALSE);
	
	UpdateData(TRUE);
	if (nRet>0 && m_bCheckVerity)
	{
		int nRiskFactor = 0;
		nRet = pAutoVerifyIDCard(nRiskFactor);
		m_strResult += _T("==========================\r\n");
		if (nRet == 0)
		{
			CString strResult;
			switch (nRiskFactor)
			{
			case AuthNotOpen:
				strResult = "����δ��";
				break;
			case AuthPassed:
				strResult = "����ͨ��";
				break;
			case AuthFailed:
				strResult = "����δͨ��";
				break;
			case AuthManualCheck:
				strResult = "���˹��˶�";
				break;
			case AuthUnsupported:
				strResult = "���鲻֧��";
				break;
			case AuthInvalidDocument:
				strResult = "��Ч֤��";
				break;
			case OCRFaild:
				strResult = "ʶ��ʧ��";
				break;
			default:
				break;
			}
			m_strResult += _T("��α�����") + strResult;
		}
		else {
			m_strResult += _T("��α���������ʧ��.\r\n1.�鿴�Ƿ�֧�ֺ���׹��������ֹ�ԴͼƬ.");
		}
		// ���������ϸ�����

	}

	GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(m_strResult);
	GetDlgItem(IDC_EDIT_DG_RESULT)->SetWindowText(m_strDGResult);
}

void CEPRSampleDemoDlg::GetContent()
{
	int nIndex = 0;
	while (1)
	{
		int nRet = AddContent(nIndex);
		if (nRet == 1)
			m_strResult += _T("Get Failed\r\n");
		else if (nRet == -1)
			break;
		else
			NULL;
		nIndex++;
	}
}

void CEPRSampleDemoDlg::GetDGContent()
{
	int nIndex = 0;
	while(1)
	{
		int nRet = AddDGContent(nIndex);
		if (nRet == 1)
			m_strDGResult += _T("Get Failed\r\n");
		else if (nRet == -1)
			break;
		else
			NULL;
		nIndex++;
	}
}

int CEPRSampleDemoDlg::AddContent(UINT nIndex)
{
	const int MAX_CH_NUM = 128;
	int len = MAX_CH_NUM * sizeof(TCHAR);
	TCHAR strResult[MAX_CH_NUM * sizeof(TCHAR)] = { 0 };
	TCHAR strName[MAX_CH_NUM * sizeof(TCHAR)] = { 0 };

	pGetFieldNameEx(1, nIndex, strName, len);
	len = MAX_CH_NUM * sizeof(TCHAR);
	int nRet = pGetRecogResultEx(1, nIndex, strResult, len);
	if (3 == nRet)
		return -1;
	else if (0 == nRet)
	{
		m_strResult = m_strResult + strName + _T(":");
		m_strResult += strResult;
		m_strResult += _T("\r\n");
		return 0;
	}
	else
		return 1;
}

int CEPRSampleDemoDlg::AddDGContent(UINT nIndex)
{
	int len = 42000;
	const int MAX_CH_NUM = 256;
	int nBufLen = MAX_CH_NUM * sizeof(TCHAR);
	TCHAR strName[MAX_CH_NUM * sizeof(TCHAR)] = { 0 };
	TCHAR strDGResult[MAX_RESULT_LEN * sizeof(TCHAR)] = { 0 };

	int nRet = pGetRecogResultEx(0, nIndex, strDGResult, len);
	pGetFieldNameEx(0, nIndex, strName, nBufLen);
	
	if (3 == nRet) 
		return -1;
	else if(0 == nRet)
	{
		m_strDGResult = m_strDGResult + strName + _T(":");
		m_strDGResult += strDGResult;
		m_strDGResult += _T("\r\n");
		return 0;
	}
	else
		return 1;
}

CString CEPRSampleDemoDlg::GetWorkPath()
{
	TCHAR szWorkPath[MAX_PATH] = { 0 };
	// _tcscpy_s(szWorkPath,MAX_PATH,_T(""));
	int nRet = 0, nErrorCode = 0;
	nRet = GetModuleFileName(NULL, szWorkPath, MAX_PATH);
	if (0 == nRet)
		return _T("");

	CString strWorkPath(szWorkPath);
	int nPos = strWorkPath.ReverseFind('\\');
	if (-1 != nPos)
		strWorkPath = strWorkPath.Left(nPos + 1);
	else
		strWorkPath.Empty();

	return strWorkPath;
}


void CEPRSampleDemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case AUTO_DETECT_PASSPORT:
	{
		OnBnClickedButtonDeviceIsline();
		int nSignal = pDetectDocument();
		if (1 == nSignal)
		{
			ReadCard();
		}
		break;
	}
	default:
		break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CEPRSampleDemoDlg::OnBnClickedButtonRecog()
{
	if (!m_bInitSuccess)
	{
		m_strResult = _T("Please successful loading recognition engine");
		GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(m_strResult);
		return;
	}

	CString tmp(_T(""));
	GetDlgItem(IDC_EDIT_IDNUM)->GetWindowText(tmp);
	m_nIDNum = _ttoi(tmp);

	if (m_nIDNum < 0) {
		m_strResult = _T("Invalid CardSizeType,please re-enter a valid.");
		GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(m_strResult);
		return;
	}

	int nSubID[1] = { 0 };
	pResetIDCardID();
	pAddIDCardID(m_nIDNum, nSubID, 1);

	ReadCard();
}

/*--------------------------------SID's Code-------------------------------*/

// ����
int CEPRSampleDemoDlg::ReadSIDCard()
{
	if (!m_bLoad)
		return -1;

	unsigned int len = 0;
	unsigned char pucApp[320] = { 0 };
	int nRet = fpSDT_ReadNewAppMsg(m_nOpenPort, pucApp, &len, 0);
	if (0x90 == nRet || 0x91 == nRet)
		return -2;

	USES_CONVERSION;
	unsigned char pucIIN[4] = { 0 };
	nRet = fpSDT_StartFindIDCard(m_nOpenPort, pucIIN, 0);
	if (nRet != 0x9F)
		return -1;
	unsigned char pucSN[8] = { 0 };
	nRet = fpSDT_SelectIDCard(m_nOpenPort, pucSN, 0);
	if (nRet != 0x90)
		return -1;

	m_EditResult.SetWindowTextW(_T(""));
	memset(m_pucCHMsg, 0, 256);//����������Ϣ
	memset(m_pucPHMsg, 0, 1024);//������Ƭ��Ϣ
	memset(m_pucFPMsg, 0, 1024);//����ָ����Ϣ
	m_uiCHMsgLen = 0;
	m_uiPHMsgLen = 0;
	m_uiFPMsgLen = 0;
	int m = fpSDT_ReadBaseFPMsg(m_nOpenPort, m_pucCHMsg, &m_uiCHMsgLen, m_pucPHMsg, &m_uiPHMsgLen, m_pucFPMsg, &m_uiFPMsgLen, 0);
	if (m != 0x90)
	{
		AfxMessageBox(_T("ReadBaseFPMsg failed"));
		return -1;
	}

	static DWORD dwReadCardCount = 1;
	CString strCount = _T("");
	strCount.Format(_T("%d"), dwReadCardCount++);                            
	SetDlgItemText(IDC_EDIT_RESULT, strCount);

	if (0 == m_uiCHMsgLen)
	{
		return -1;
	}
	else
	{
		//DtiTmp[2] = {0};�����ʼ��
		memset(DtiTmp, 0, 2);
		strncpy_s((char*)DtiTmp, _countof(DtiTmp), (char*)(m_pucCHMsg + 248), 2);
		TCHAR wszCHMsg[256] = { 0 };
		wcsncpy_s(wszCHMsg, _countof(wszCHMsg), (TCHAR*)m_pucCHMsg, 128);
		// ��ȫ��locale��Ϊ��������
		locale &loc = locale::global(locale(locale(), "", LC_CTYPE));
		// szTmp[0] = 'I';
		if (0 == strcmp((char*)DtiTmp, "I"))				// ��дI��ʾ����˾ɰ����þ���֤
		{
			m_bSID = false;
			std::wofstream out(L"CHMsg_Prp.txt", std::ios_base::app | std::ios_base::out);
			out << wszCHMsg << std::endl;
			out.close();
			ShowCHMsg_Prp();
		}
		else if (0 == strcmp((char*)DtiTmp, "Y")) { //��дY��ʾ������°����þ���֤
			m_bSID = false;
			std::wofstream out(L"CHMsg_PrpNew.txt", std::ios_base::app | std::ios_base::out);
			out << wszCHMsg << std::endl;
			out.close();
			ShowCHMsg_PrpNew();
		
		}
		else if (0 == strcmp((char*)DtiTmp, "J"))        // ��дJ��ʾ�۰�̨�����ס֤
		{
			m_bSID = false;
			std::wofstream out(L"CHMsg_Rrp.txt", std::ios_base::app | std::ios_base::out);
			out << wszCHMsg << std::endl;
			out.close();
			ShowCHMsg_Rrp();
		}
		else
		{
			m_bSID = true;
			std::wofstream out(L"CHMsg_SID.txt", std::ios_base::app | std::ios_base::out);
			out << wszCHMsg << std::endl;
			out.close();
			ShowCHMsg_SID();
		}
		locale::global(loc);			// ȫ��locale�ָ�ԭ��������
	}

	m_EditDG.SetWindowTextW(_T("no any DG info"));

	CString strHeadPath = _T("");
	CString strImagePath = _T("");
	GetDlgItem(IDC_EDIT_IMAGEPATH)->GetWindowTextW(strImagePath);
	if (strImagePath.GetLength() > 1)
	{
		strHeadPath += strImagePath;
	}
	else
	{
		strHeadPath += m_strImagePath;
	}

	if (m_bSID)
		strHeadPath += _T("head_SID");
	else
		if (0 == strcmp((char*)DtiTmp, "I"))
			strHeadPath += _T("head_PRP");
		else
			strHeadPath += _T("head_RRP");
	SavePhoto((LPCTSTR)strHeadPath, 2);

	// ��ʾͷ�񵽽���
	strHeadPath = strHeadPath + _T(".bmp");
	ShowImage(strHeadPath);
	((CButton*)GetDlgItem(IDC_BTN_PRE))->EnableWindow(FALSE);
	((CButton*)GetDlgItem(IDC_BTN_NEXT))->EnableWindow(FALSE);
	return 0;
}

// ��ʾ����֤������Ϣ������
void CEPRSampleDemoDlg::ShowCHMsg_SID()
{
	CString strTmp = _T("");
	CString strResult = _T("");
	int	nListCtrlRowIndex = 1;

	strTmp = _T("֤�����ƣ�����֤\r\n");
	strResult += strTmp;

	strTmp.Format(_T("%s"), GetName());
	strResult += _T("������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetSex());
	strResult += _T("�Ա�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetPeople());
	strResult += _T("���壺");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetBirthday());
	strResult += _T("�������ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetAddress());
	strResult += _T("סַ��");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetIDCode());
	strResult += _T("������ݺ��룺");
	strResult += strTmp;
	strResult += _T("\r\n");


	strTmp.Format(_T("%s"), GetAuthority());
	strResult += _T("ǩ�����أ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetIssueDay());
	strResult += _T("��Ч����ʼ���ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetExpityDay());
	strResult += _T("��Ч�ڽ�ֹ���ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strResult += _T("ָ����Ϣ��") + GetFingerprintInfo();
	m_EditResult.SetWindowTextW(strResult);
}

// ��ʾ�°����þ�ס֤������Ϣ������
void CEPRSampleDemoDlg::ShowCHMsg_PrpNew()
{
	CString strTmp = _T("");
	CString strResult = _T("");
	int	nListCtrlRowIndex = 1;

	strTmp = _T("֤�����ƣ���������þ������֤2023��\r\n");
	strResult += strTmp;

	strTmp.Format(_T("%s"), GetName());
	strResult += _T("������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetSex());
	strResult += _T("�Ա�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetNumberOfCertificateRenewals());
	strResult += _T("��֤������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetBirthday());
	strResult += _T("�������ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetEnglishName());
	strResult += _T("Ӣ��������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetIDCode());
	strResult += _T("���þ���֤���룺");
	strResult += strTmp;
	strResult += _T("\r\n");

	/*strTmp.Format(_T("%s"), GetAuthority());
	strResult += _T("Ԥ���ռ䣺");
	strResult += strTmp;
	strResult += _T("\r\n");*/

	strTmp.Format(_T("%s"), GetIssueDay());
	strResult += _T("֤��ǩ�����ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetExpityDay());
	strResult += _T("֤����Ч������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetEnglishNameStandBy());
	strResult += _T("Ӣ���������ã�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetCountryOrRegionCode());
	strResult += _T("�������Һ͵������룺");
	strResult += strTmp;
	strResult += _T("\r\n");

	//strTmp.Format(_T("%s"), GetNumberFlag());
	//strResult += _T("֤�����ͱ�־��");
	//strResult += strTmp;
	//strResult += _T("\r\n");

	/*strTmp.Format(_T("%s"), GetNumberAssociation());
	strResult += _T("�����汾��������þ���֤��������");
	strResult += strTmp;
	strResult += _T("\r\n");*/


	strTmp.Format(_T("%s"), GetOldIDCode());
	strResult += _T("�����汾֤�����룺");
	strResult += strTmp;
	strResult += _T("\r\n");

	m_EditResult.SetWindowTextW(strResult);

}

// ��ʾ�ɰ����þ�ס֤������Ϣ������
void CEPRSampleDemoDlg::ShowCHMsg_Prp()
{
	CString strTmp = _T("");
	CString strResult = _T("");
	int	nListCtrlRowIndex = 1;

	strTmp = _T("֤�����ƣ���������þ������֤2017��\r\n");
	strResult += strTmp;

	strTmp.Format(_T("%s"), GetName());
	strResult += _T("������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetSex());
	strResult += _T("�Ա�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetIDCode());
	strResult += _T("���þ���֤���룺");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetPeople());
	strResult += _T("���������ڵ������룺");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s\n"), GetPeopleChineseName());
	strResult += _T("����������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetIssueDay());
	strResult += _T("��Ч����ʼ���ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetExpityDay());
	strResult += _T("��Ч�ڽ�ֹ���ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetBirthday());
	strResult += _T("�������ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetCardVersion());
	strResult += _T("֤���汾�ţ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetAuthority());
	strResult += _T("��������������ش��룺");
	strResult += strTmp;
	strResult += _T("\r\n");


	strResult += _T("֤�����ͱ�ʶ��I\r\n");
//	strResult += strTmp;

	strTmp.Format(_T("%s"), GetReverse());
	strResult += _T("Ԥ���");
	strResult += strTmp;
	strResult += _T("\r\n");

	m_EditResult.SetWindowTextW(strResult);

}

// ��ʾ�۰�̨�����ס֤������Ϣ������
void CEPRSampleDemoDlg::ShowCHMsg_Rrp()
{
	CString strTmp = _T("");
	CString strResult = _T("");
	int	nListCtrlRowIndex = 1;

	strTmp = _T("֤�����ƣ��۰�̨�����ס֤\r\n");
	strResult += strTmp;

	strTmp.Format(_T("%s"), GetName());
	strResult += _T("������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetSex());
	strResult += _T("�Ա�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetReverseGAT(32,2));
	strResult += _T("Ԥ���");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetBirthday());
	strResult += _T("�������ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");
	strTmp.Format(_T("%s"), GetAddress());
	strResult += _T("סַ��");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetPeople());
	strResult += _T("���壺");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetIDCode());
	strResult += _T("�������֤���룺");
	strResult += strTmp;
	strResult += _T("\r\n");


	strTmp.Format(_T("%s"), GetAuthority());
	strResult += _T("ǩ�����أ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetIssueDay());
	strResult += _T("��Ч����ʼ���ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetExpityDay());
	strResult += _T("��Ч�ڽ�ֹ���ڣ�");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetPassNum());
	strResult += _T("ͨ��֤���룺");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetIssueNum());
	strResult += _T("ǩ��������");
	strResult += strTmp;
	strResult += _T("\r\n");

	strTmp.Format(_T("%s"), GetReverseGAT(242,3));
	strResult += _T("Ԥ���");
	strResult += strTmp;
	strResult += _T("\r\n");

	strResult += _T("֤�����ͱ�ʶ��J\r\n");
	strResult += strTmp;

	strTmp.Format(_T("%s"), GetReverseGAT(250,3));
	strResult += _T("Ԥ���");
	strResult += strTmp;
	strResult += _T("\r\n");

	strResult += _T("ָ����Ϣ��") + GetFingerprintInfo();
	m_EditResult.SetWindowTextW(strResult);
}

// ��ȡ����
CString CEPRSampleDemoDlg::GetName(void)
{
	if (0 == m_uiCHMsgLen)
		return _T("");
	TCHAR szName[100] = { 0 };
	if (0 == strcmp((char*)DtiTmp, "J"))
		wcsncpy_s(szName, _countof(szName), (TCHAR*)m_pucCHMsg, 15);
	else if (0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szName, _countof(szName), (TCHAR*)m_pucCHMsg, 60);
	else
		wcsncpy_s(szName, _countof(szName), (TCHAR*)m_pucCHMsg, 15);
	CString str = szName;
	str.TrimRight();
	return str;
}

// ��ȡ�������������
CString CEPRSampleDemoDlg::GetPeopleChineseName()
{

	if (0 == m_uiCHMsgLen)// ������Ϣ���ݳ���
		return _T("");
	TCHAR szName[30] = { 0 };//��������ռ30�ֽڣ���5�ţ�ǰ��4�������ռ158�ֽ�
	if (0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szName, _countof(szName), (TCHAR*)(m_pucCHMsg + 158), 15);// m_pucCHMsg[1280]������Ϣ
	CString str = szName;
	str.TrimRight();
	return str;
}

// ���֤���汾��
CString CEPRSampleDemoDlg::GetCardVersion()
{
	if (0 == m_uiCHMsgLen)
		return _T("");
	TCHAR szVersion[30] = { 0 };//֤���汾��ռ4�ֽڣ���9�ţ�ǰ��8�������ռ236�ֽ�
	if (0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szVersion, _countof(szVersion), (TCHAR*)(m_pucCHMsg + 236), 2);
	CString str = szVersion;
	str.TrimRight();//�����Ҳ����пո�
	return str;
}

// ��ȡԤ����
CString CEPRSampleDemoDlg::GetReverse()
{
	if (0 == m_uiCHMsgLen)
		return _T("");
	TCHAR szTmp[30] = { 0 };
	if (0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 250), 3);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

// ��ȡԤ����
CString CEPRSampleDemoDlg::GetReverseGAT(int nPosition,int nVal)
{
	if (0 == m_uiCHMsgLen)
		return _T("");
	TCHAR szTmp[30] = { 0 };
	if (0 == strcmp((char*)DtiTmp, "J"))
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + nPosition), nVal);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

// ��ȡ�Ա�
CString CEPRSampleDemoDlg::GetSex(void)
{
	if (0 == m_uiCHMsgLen)
		return _T("");

	TCHAR szTmp[30] = { 0 };
	if (0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 120), 1);
	else
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 30), 1);
	CString str = szTmp;
	str.TrimRight();
	if (str == _T("1"))
		return _T("��");
	else
		return _T("Ů");
}

// ��ȡ����
CString CEPRSampleDemoDlg::GetPeople(void)
{
	if (0 == m_uiCHMsgLen)
		return _T("");

	USES_CONVERSION;
	TCHAR szTmp[30] = { 0 };
	CString str = _T("");
	if (m_bSID)
	{
		wcsncat_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 32), 2);
		str = szTmp;
		str.TrimRight();
		int code = atoi(W2A(str.GetBuffer(str.GetLength())));
		str.ReleaseBuffer();

		//���廮��
		switch (code)
		{
		case 01:  return _T("��");
		case 02:  return _T("�ɹ�");
		case 03:  return _T("��");
		case 04:  return _T("��");
		case 05:  return _T("ά���");
		case 06:  return _T("��");
		case 07:  return _T("��");
		case 8:   return _T("׳");
		case 9:   return _T("����");
		case 10:  return _T("����");
		case 11:  return _T("��");
		case 12:  return _T("��");
		case 13:  return _T("��");
		case 14:  return _T("��");
		case 15:  return _T("����");
		case 16:  return _T("����");
		case 17:  return _T("������");
		case 18:  return _T("��");
		case 19:  return _T("��");
		case 20:  return _T("����");
		case 21:  return _T("��");
		case 22:  return _T("�");
		case 23:  return _T("��ɽ");
		case 24:  return _T("����");
		case 25:  return _T("ˮ");
		case 26:  return _T("����");
		case 27:  return _T("����");
		case 28:  return _T("����");
		case 29:  return _T("�¶�����");
		case 30:  return _T("��");
		case 31:  return _T("���Ӷ�");
		case 32:  return _T("����");
		case 33:  return _T("Ǽ");
		case 34:  return _T("����");
		case 35:  return _T("����");
		case 36:  return _T("ë��");
		case 37:  return _T("����");
		case 38:  return _T("����");
		case 39:  return _T("����");
		case 40:  return _T("����");
		case 41:  return _T("������");
		case 42:  return _T("ŭ");
		case 43:  return _T("���α��");
		case 44:  return _T("����˹");
		case 45:  return _T("���¿�");
		case 46:  return _T("�°�");
		case 47:  return _T("����");
		case 48:  return _T("ԣ��");
		case 49:  return _T("��");
		case 50:  return _T("������");
		case 51:  return _T("����");
		case 52:  return _T("���״�");
		case 53:  return _T("����");
		case 54:  return _T("�Ű�");
		case 55:  return _T("���");
		case 56:  return _T("��ŵ");
		case 97:  return _T("����");
		case 98:  return _T("���Ѫͳ�й�����ʿ");
		default: return _T("");
		}
	}
	else
	{
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 152), 3);
		str = szTmp;
		str.TrimRight();
		return str;
	}
}
//��ȡ�°����þ���֤��֤����
CString CEPRSampleDemoDlg::GetNumberOfCertificateRenewals()
{
	if (0 == m_uiCHMsgLen)
		return _T("");

	USES_CONVERSION;
	TCHAR szTmp[30] = { 0 };
	CString str = _T("");
	wcsncat_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 32), 2);
	str = szTmp;
	str.TrimRight();
	return str;

}
//��ȡ�����汾��������þ���֤�����������
CString CEPRSampleDemoDlg::GetNumberAssociation()
{
	if (0 == m_uiCHMsgLen)
		return _T("");

	USES_CONVERSION;
	TCHAR szTmp[30] = { 0 };
	CString str = _T("");
	wcsncat_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 250), 3);
	str = szTmp;
	str.TrimRight();
	return str;

}

//��ȡ�����汾��������þ���֤�������Ƶ�
CString CEPRSampleDemoDlg::GetOldIDCode()
{
	if (0 == m_uiCHMsgLen)
		return _T("");
	CString str = _T("");
	CString strTemporary = _T("");
	CString cstr = _T("");
	
	if (_T("") == GetNumberAssociation().Trim()) {
		return _T("");
	}
	else {
	str = GetCountryOrRegionCode();
	str += GetIDCode().Mid(1,2).Trim();
	str += GetNumberAssociation().Left(2).Trim();
	str += GetIDCode().Mid(8,6).Trim();
	str += GetNumberAssociation().Right(1).Trim();
	strTemporary = str;
	int number = 0;
	int count = 0;
	if (AssignedNumbers(strTemporary.Left(1).Trim()) != 1) {
		number += AssignedNumbers(strTemporary.Left(1).Trim()) * 7;
	}
	if (AssignedNumbers(strTemporary.Mid(1, 1).Trim()) != 1) {
		number += AssignedNumbers(strTemporary.Mid(1, 1).Trim()) * 3;
	}
	if (AssignedNumbers(strTemporary.Mid(2, 1).Trim()) != 1) {
		number += AssignedNumbers(strTemporary.Mid(2, 1).Trim()) * 1;
	}

	count += _ttoi(strTemporary.Mid(3, 1).Trim())*7;
	count += _ttoi(strTemporary.Mid(4, 1).Trim()) * 3;
	count += _ttoi(strTemporary.Mid(5, 1).Trim()) * 1;
	count += _ttoi(strTemporary.Mid(6, 1).Trim()) * 7;
	count += _ttoi(strTemporary.Mid(7, 1).Trim()) * 3;
	count += _ttoi(strTemporary.Mid(8, 1).Trim()) * 1;
	count += _ttoi(strTemporary.Mid(9, 1).Trim()) * 7;
	count += _ttoi(strTemporary.Mid(10, 1).Trim()) * 3;
	count += _ttoi(strTemporary.Mid(11, 1).Trim()) * 1;
	count += _ttoi(strTemporary.Mid(12, 1).Trim()) * 7;
	count += _ttoi(strTemporary.Mid(13, 1).Trim()) * 3;

	cstr.Format(L"%d", (number + count) % 10);
	str += cstr;
		
	
	return str;
	}
}

int CEPRSampleDemoDlg::AssignedNumbers(CString cstr)
{
	if (cstr == _T("A")) {
		return 10;
	}
	else if (cstr == _T("B")) {
		return 11;
	}
	else if (cstr == _T("C")) {
		return 12;
	}
	else if (cstr == _T("D")) {
		return 13;
	}
	else if (cstr == _T("E")) {
		return 14;
	}
	else if (cstr == _T("F")) {
		return 15;
	}
	else if (cstr == _T("G")) {
		return 16;
	}
	else if (cstr == _T("H")) {
		return 17;
	}
	else if (cstr == _T("I")) {
		return 18;
	}
	else if (cstr == _T("J")) {
		return 19;
	}
	else if (cstr == _T("K")) {
		return 20;
	}
	else if (cstr == _T("L")) {
		return 21;
	}
	else if (cstr == _T("M")) {
		return 22;
	}
	else if (cstr == _T("N")) {
		return 23;
	}
	else if (cstr == _T("O")) {
		return 24;
	}
	else if (cstr == _T("P")) {
		return 25;
	}
	else if (cstr == _T("Q")) {
		return 26;
	}
	else if (cstr == _T("R")) {
		return 27;
	}
	else if (cstr == _T("S")) {
		return 28;
	}
	else if (cstr == _T("T")) {
		return 29;
	}
	else if (cstr == _T("U")) {
		return 30;
	}
	else if (cstr == _T("V")) {
		return 31;
	}
	else if (cstr == _T("W")) {
		return 32;
	}
	else if (cstr == _T("X")) {
		return 33;
	}
	else if (cstr == _T("Y")) {
		return 34;
	}
	else if (cstr == _T("Z")) {
		return 35;
	}
	else if (cstr == _T("<")) {
		return 0;
	}
	else {
		return 1;
	}
	
}

//��ȡ�°���������þ���֤����
CString CEPRSampleDemoDlg::GetNumberFlag()
{
	if (0 == m_uiCHMsgLen)
		return _T("");

	USES_CONVERSION;
	TCHAR szTmp[30] = { 0 };
	CString str = _T("");
	wcsncat_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 248), 1);
	str = szTmp;
	str.TrimRight();
	return str;

}

//��ȡ�°����þ���֤�������һ��������
CString CEPRSampleDemoDlg::GetCountryOrRegionCode()
{
	if (0 == m_uiCHMsgLen)
		return _T("");

	USES_CONVERSION;
	TCHAR szTmp[30] = { 0 };
	CString str = _T("");
	wcsncat_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 242), 3);
	str = szTmp;
	str.TrimRight();
	return str;
}
// ��ȡ��������
CString CEPRSampleDemoDlg::GetBirthday(void)
{

	if (m_uiCHMsgLen == 0)
		return _T("");

	TCHAR szTmp[30] = { 0 };
	if(0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szTmp, _countof(szTmp),(TCHAR*)(m_pucCHMsg + 220), 8);
	else
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 36), 8);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

// ��ȡסַ
CString CEPRSampleDemoDlg::GetAddress(void)
{
	if (m_uiCHMsgLen == 0)
		return _T("");

	TCHAR szTmp[70] = { 0 };
	wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 52), 35);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

// ��ȡ�°����þ���֤Ӣ������
CString CEPRSampleDemoDlg::GetEnglishName()
{
	if (m_uiCHMsgLen == 0)
		return _T("");

	TCHAR szTmp[70] = { 0 };
	wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 52), 35);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

// ��ȡǩ������
CString CEPRSampleDemoDlg::GetAuthority(void)
{
	if (m_uiCHMsgLen == 0)
		return _T("");
	TCHAR szTmp[30] = { 0 };
	if (0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 240), 4);
	else 
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 158), 15);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

// ��ȡ���֤��
CString CEPRSampleDemoDlg::GetIDCode(void)
{
	if (m_uiCHMsgLen == 0)
		return _T("");

	TCHAR szTmp[36] = { 0 };
	if(0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 122), 15);
	else
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 122), 18);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

// ��ȡ��Ч����ʼ����
CString CEPRSampleDemoDlg::GetIssueDay(void)
{
	if (m_uiCHMsgLen == 0)
		return _T("");

	TCHAR szTmp[30] = { 0 };
	if (0 == strcmp((char*)DtiTmp, "I"))
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 188), 8);
	else if (0 == strcmp((char*)DtiTmp, "J"))
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 188), 8);
	else
		wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 188), 8);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

// ��ȡ��Ч�ڽ�ֹ����
CString CEPRSampleDemoDlg::GetExpityDay(void)
{
	if (m_uiCHMsgLen == 0)
		return _T("");

	TCHAR szTmp[30] = { 0 };
	wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 204), 8);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

//��ȡ�°����֤Ӣ����������
CString CEPRSampleDemoDlg::GetEnglishNameStandBy()
{
	if (m_uiCHMsgLen == 0)
		return _T("");

	TCHAR szTmp[30] = { 0 };
	wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 220), 11);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

//��ȡͨ��֤����
CString CEPRSampleDemoDlg::GetPassNum(void)
{
	if (0 == m_uiCHMsgLen)
		return _T("");
	TCHAR szTmp[30] = { 0 };
	wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 220), 9);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

//��ȡǩ������
CString CEPRSampleDemoDlg::GetIssueNum(void)
{
	if (0 == m_uiCHMsgLen)
		return _T("");
	TCHAR szTmp[30] = { 0 };
	wcsncpy_s(szTmp, _countof(szTmp), (TCHAR*)(m_pucCHMsg + 238), 2);
	CString str = szTmp;
	str.TrimRight();
	return str;
}

//��ȡָ����Ϣ
CString CEPRSampleDemoDlg::GetFingerprintInfo(void)
{
	CString str;
	if (m_uiFPMsgLen != 0)
		str = "��";
	else
		str = "��";
	return str;
}

// ����λͼͷ��
int CEPRSampleDemoDlg::SavePhoto(LPCTSTR FileName, int nType)
{
	USES_CONVERSION;
	CString strWlt = CString(FileName) + _T(".wlt");
	CFile f;
	f.Open(strWlt, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	f.Write(m_pucPHMsg, m_uiPHMsgLen);
	f.Close();

	if (1 == m_lpGetBmp(W2A(strWlt), nType))
		return 0;
	else
		return -1;
}

//���ض�̬��sdtapi.dll,WltRS.dll
int CEPRSampleDemoDlg::LoadDll(void)
{
	CString strDllPath = _T("");
	CString strSdtapiPath = _T("");
	CString strWltRSPath = _T("");
	GetDlgItem(IDC_EDIT_DLLPATH)->GetWindowTextW(strDllPath);
	if (strDllPath.GetLength())
	{
		strSdtapiPath += strDllPath;
		strSdtapiPath += _T("sdtapi.dll");
		m_hNIDapi = LoadLibraryEx(strSdtapiPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	}
	else
	{
		m_hNIDapi = LoadLibrary(_T("sdtapi.dll"));
	}

	if (!m_hNIDapi)
	{
		return -1;
	}
	//���ض�̬��ɹ���ִ��
	fpSDT_OpenPort = (int (WINAPI *)(int))GetProcAddress(m_hNIDapi, "SDT_OpenPort");
	fpSDT_GetSAMIDToStr = (int (WINAPI *)(int,char*,int))GetProcAddress(m_hNIDapi, "SDT_GetSAMIDToStr");
	SDT_GetSAMID = (int (WINAPI *)(int, unsigned char*, int))GetProcAddress(m_hNIDapi, "SDT_GetSAMID");
	fpSDT_ClosePort = (int (WINAPI *)(int))GetProcAddress(m_hNIDapi, "SDT_ClosePort");
	fpSDT_StartFindIDCard = (int (WINAPI*)(int, unsigned char *, int))GetProcAddress(m_hNIDapi, "SDT_StartFindIDCard");
	fpSDT_SelectIDCard = (int (WINAPI *)(int, unsigned char *, int))GetProcAddress(m_hNIDapi, "SDT_SelectIDCard");
	fpSDT_ReadBaseMsgToFile = (int (WINAPI *)(int, char *, unsigned int*, char *, unsigned int*, char *, unsigned int*, int))GetProcAddress(m_hNIDapi, "SDT_ReadBaseMsgToFile");
	fpSDT_ReadBaseFPMsg = (int (WINAPI *)(int, unsigned char *, unsigned int*, unsigned char *, unsigned int*, unsigned char *, unsigned int*, int))GetProcAddress(m_hNIDapi, "SDT_ReadBaseFPMsg");
	fpSDT_ReadNewAppMsg = (int (WINAPI *)(int, unsigned char *, unsigned int*, int))GetProcAddress(m_hNIDapi, ("SDT_ReadNewAppMsg"));
	if (fpSDT_OpenPort == NULL
		|| fpSDT_ClosePort == NULL
		|| fpSDT_StartFindIDCard == NULL
		|| fpSDT_SelectIDCard == NULL
		|| fpSDT_ReadBaseMsgToFile == NULL
		|| fpSDT_ReadBaseFPMsg == NULL
		|| fpSDT_ReadNewAppMsg == NULL
		|| SDT_GetSAMID == NULL
		|| fpSDT_GetSAMIDToStr == NULL)
	{
		return -2;
	}

	//
	if (strDllPath.GetLength())
	{
		strWltRSPath += strDllPath;
		strWltRSPath += _T("\\WltRS.dll");
		m_hGetBmp = LoadLibraryEx(strWltRSPath, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	}
	else
	{
		m_hGetBmp = LoadLibrary(_T("WltRS.dll"));
	}
	if (!m_hGetBmp)
	{
		return -3;
	}
	m_lpGetBmp = (int (WINAPI*)(char *, int))GetProcAddress(m_hGetBmp, "GetBmp");
	if (!m_hGetBmp || !m_lpGetBmp)
	{
		return -4;
	}
	int nRes = 1;
	for (int iPort = 1001; iPort <= 1016; iPort++)
	{
		nRes = fpSDT_OpenPort(iPort);
		if (nRes == 0x90)
		{
			m_nOpenPort = iPort;//�򿪶˿ڳɹ�
			m_bLoad = true;
			break;
		}
	}
	if (nRes != 0x90)
	{
		return -5;
	}
	return 0;
}

void CEPRSampleDemoDlg::ShowImage(CString strImagePath)
{

	float m_Image_fx, m_Image_fy, /*m_Control_fx, m_Control_fy, m_Control_fScale,*/ m_Image_fScale;//���ؼ��Ŀ�͸��Լ�ͼƬ��͸��йصĲ���
	CRect   rect;//���ڻ�ȡͼƬ�ؼ��Ŀ�͸�
	CImage m_Image;//ΪcimageͼƬ�ഴ��һ������
	HRESULT hImage = m_Image.Load(strImagePath);//���캯�����β���������ͼƬ��·��
	if (S_OK != hImage)
		return;

	m_Image_fx = (float)m_Image.GetWidth();
	m_Image_fy = (float)m_Image.GetHeight();//��ȡͼƬ�Ŀ� ��
	m_Image_fScale = (float)m_Image_fy / m_Image_fx;//���ͼƬ�Ŀ�߱�


	CWnd *pWnd = NULL;
	pWnd = GetDlgItem(IDC_STATIC_PICTURE);
	pWnd->GetClientRect(&rect);

	CDC *pDc = NULL;
	pDc = pWnd->GetDC();
	int ModeOld = SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//����ָ���豸�����е�λͼ����ģʽ

	GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(TRUE);
	m_Image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//��ʾ����
	SetStretchBltMode(pDc->m_hDC, ModeOld);
	ReleaseDC(pDc);//�ͷ�ָ��ռ�
}

void CEPRSampleDemoDlg::SaveImagePath(CString strImagePath, int nType)
{
	m_vecImagePath.clear();
	m_nImageIndex = 0;
	if (nType & 1)
	{
		m_vecImagePath.push_back(strImagePath);
	}
	if (nType & 2)
	{
		CString strIR = strImagePath;
		strIR.Insert(strIR.GetLength() - 4, _T("IR"));
		m_vecImagePath.push_back(strIR);
	}
	if (nType & 4)
	{
		CString strUV = strImagePath;
		strUV.Insert(strUV.GetLength() - 4, _T("UV"));
		m_vecImagePath.push_back(strUV);
	}
	if (nType & 8)
	{
		CString strHead = strImagePath;
		strHead.Insert(strHead.GetLength() - 4, _T("Head"));
		m_vecImagePath.push_back(strHead);
	}
	if (nType & 16)
	{
		CString strHeadEC = strImagePath;
		strHeadEC.Insert(strHeadEC.GetLength() - 4, _T("HeadEC"));
		m_vecImagePath.push_back(strHeadEC);
	}

	if (m_vecImagePath.size() <= 1)
	{
		((CButton*)GetDlgItem(IDC_BTN_PRE))->EnableWindow(FALSE);
		((CButton*)GetDlgItem(IDC_BTN_NEXT))->EnableWindow(FALSE);
	}
	else
	{
		((CButton*)GetDlgItem(IDC_BTN_PRE))->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_BTN_NEXT))->EnableWindow(TRUE);
	}
}

void CEPRSampleDemoDlg::OnBnClickedBtnNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nImageIndex++;
	int nSize = m_vecImagePath.size();
	if (m_nImageIndex > nSize - 1)
	{
		m_nImageIndex = 0;
	}
	ShowImage(m_vecImagePath[m_nImageIndex]);
}


void CEPRSampleDemoDlg::OnBnClickedBtnPre()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nImageIndex--;
	if (m_nImageIndex < 0)
	{
		m_nImageIndex = m_vecImagePath.size() - 1;
	}
	ShowImage(m_vecImagePath[m_nImageIndex]);
}


void CEPRSampleDemoDlg::OnBnClickedBtnReadsidcard()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nRet = ReadSIDCard();
	if(-1 == nRet)
	{
		GetDlgItem(IDC_EDIT_RESULT)->SetWindowText(_T(""));
		GetDlgItem(IDC_EDIT_DG_RESULT)->SetWindowText(_T(""));
		GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(FALSE);
	}
}

BOOL CEPRSampleDemoDlg::BrowseForPath(CString& tPath)
{
	BOOL rc = FALSE;
	//CString tPath = _T("");
	BROWSEINFO bi;
	TCHAR Buffer[MAX_PATH];
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = _T("��ѡ��·��");
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//�����ļ�
	bi.ulFlags = BIF_EDITBOX;//�����ļ�
	bi.lpfn = NULL;
	bi.iImage = IDR_MAINFRAME;

	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		tPath = Buffer;
		if (!PathIsDirectory(tPath))
			CreateDirectory(tPath, NULL);

		if (!tPath.IsEmpty())
		{
			if (tPath.GetAt(tPath.GetLength() - 1) != _T('\\'))
				tPath.Append(_T("\\"));

			rc = TRUE;
		}
		else
			rc = FALSE;
	}
	LPMALLOC lpMalloc;
	if (FAILED(SHGetMalloc(&lpMalloc)))
		return rc;
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
	UpdateData(FALSE);

	return rc;
}

void CEPRSampleDemoDlg::OnCbnSelchangeComboIdent()
{
	CString strIdent;
	GetDlgItem(IDC_COMBO_IDENT)->GetWindowText(strIdent);
	if ("Automatic identification" == strIdent)
	{
		m_EditResult.SetWindowText(_T(""));
		m_EditDG.SetWindowText(_T(""));
		SetTimer(AUTO_DETECT_PASSPORT, 100, NULL);
		GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_READSIDCARD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_IDNUM)->EnableWindow(FALSE);

		CString strFigPath;
		m_editFigPath.GetWindowText(strFigPath);
		if (!strFigPath.IsEmpty())
		{
			int nRet = pSetConfigByFile(strFigPath.AllocSysString());
		}
	}
	else if ("Manual identification" == strIdent)
	{
		m_EditResult.SetWindowText(_T(""));
		m_EditDG.SetWindowText(_T(""));
		GetDlgItem(IDC_STATIC_PICTURE)->ShowWindow(FALSE);
		KillTimer(AUTO_DETECT_PASSPORT);
		GetDlgItem(IDC_BUTTON_RECOG)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_READSIDCARD)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_IDNUM)->EnableWindow(TRUE);
	}
	else
		NULL;
}

void CEPRSampleDemoDlg::OnBnClickedBtnBrowseDllpath()
{
	CString tPath;
	if (BrowseForPath(tPath))
	{
		m_editLibPath.SetWindowText(tPath);
		tPath += "IDCardConfig.ini";
		m_editFigPath.SetWindowText(tPath);
	}
}

void CEPRSampleDemoDlg::OnBnClickedBtnPicpath()
{
	CString tPath;
	if (BrowseForPath(tPath))
	{
		m_editPicPath.SetWindowText(tPath);
	}
}

void CEPRSampleDemoDlg::OnBnClickedButtonSetting()
{
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrInitialDir = _T("C:\\");
	if (IDOK == fileDlg.DoModal())
		m_editFigPath.SetWindowText(fileDlg.GetPathName());
}



void CEPRSampleDemoDlg::OnBnClickedCheckVerify()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_bCheckVerity)
	{
		((CButton*)GetDlgItem(IDC_CHECK_WHITE))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_IR))->SetCheck(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_UV))->SetCheck(TRUE);
	}
}
