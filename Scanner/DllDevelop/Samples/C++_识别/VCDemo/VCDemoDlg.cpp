// VCDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VCDemo.h"
#include "VCDemoDlg.h"
#include<string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <math.h>


#define  ID_CHECK_BUTTON_DOWN_TIMER 1
#define  ID_PASSPORT_READER_TIMER 1001
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CVCDemoDlg dialog

CVCDemoDlg::CVCDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVCDemoDlg::IDD, pParent)
	, m_strResult(_T(""))
	, m_nCarDTypeID(2)
	, m_nImgSizeType(2)
	, m_strUserID(_T(""))
	, m_nLightType(1)
	, m_nImageType(1)
	, m_nImageWidth(0)
	, m_nImageHeight(0)
	, m_nHoriResolution(300)
	, m_nVertResolution(300)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nImagCustomSize = 20;
	//init the variables
	fpInitIDCard = NULL;
	fpFreeIDCard = NULL;

	fpCheckDeviceOnlineEx = NULL;

	fpAcquireImage = NULL;
	fpSetAcquireImageType = NULL;
	fpSetUserDefinedImageSize = NULL;
	fpSetAcquireImageResolution = NULL;

	fpResetIDCardID = NULL;
	fpAddIDCardID = NULL;
	fpSetIDCardRejectType = NULL;

	fpRecogIDCard = NULL;
	fpRecogIDCardEx = NULL;
	fpGetRecogResult = NULL;
	fpGetFieldName = NULL;
	fpGetResultType = NULL;
	fpGetSubId = NULL;
	fpGetIDCardName = NULL;
	
	fpSaveImage = NULL;
	fpSaveHeadImage = NULL;
	
	fpGetCurrentDevice = NULL;
	fpGetVersionInfo = NULL;
	fpGetDeviceSN=NULL;
	
	/*��Ƭ*/
	pRecogBusinessCard = NULL;
	pGetBusinessCardResultCount = NULL;
	pGetBusinessCardResult = NULL;
	pGetBusinessCardFieldName = NULL;
	
	m_bIsInitSuccess = FALSE;
	m_hIDCard = NULL;
}

//unload the DLL
CVCDemoDlg::~CVCDemoDlg()
{
	//KillTimer(ID_PASSPORT_READER_TIMER);
}

void CVCDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);	
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
	DDX_Text(pDX, IDC_EDIT_CARD_TYPE, m_nCarDTypeID);
	DDX_Text(pDX, IDC_EDIT_SCAN_SIZE_TYPE, m_nImgSizeType);
	DDX_Text(pDX, IDC_EDIT_USER_ID, m_strUserID);
	DDX_Text(pDX, IDC_EDIT_IMAGE_WIDTH, m_nImageWidth);
	DDX_Text(pDX, IDC_EDIT_IMAGE_HEIGHT, m_nImageHeight);
	DDX_Text(pDX, IDC_EDIT_HORI_RESOLUTION, m_nHoriResolution);
}

BEGIN_MESSAGE_MAP(CVCDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_COPYDATA()
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_LOAD_KERNAL, &CVCDemoDlg::OnBnClickedBtnLoadKernal)
	ON_BN_CLICKED(IDC_BTN_RECOG_IMG_IN_MEMORY, &CVCDemoDlg::OnBnClickedBtnRecogImgInMemory)
	ON_BN_CLICKED(IDC_BTN_UNLOAD_KERNEL, &CVCDemoDlg::OnBnClickedBtnUnloadKernel)
	ON_BN_CLICKED(IDC_BTN_SET_USER_DEFINE_IMG_SIZE, &CVCDemoDlg::OnBnClickedBtnSetUserDefineImgSize)
	ON_BN_CLICKED(IDC_BTN_SET_ACQUIRE_IMG_RESOLUTION, &CVCDemoDlg::OnBnClickedBtnSetAcquireImgResolution)
	ON_BN_CLICKED(IDC_BTN_ACIMAGE, &CVCDemoDlg::OnBnClickedBtnAcimage)
END_MESSAGE_MAP()


// CVCDemoDlg message handlers

BOOL CVCDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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

	// TODO: Add extra initialization here
	SetWindowText(_T("ɨ���ǲ�����"));
	GetDlgItem(IDC_EDIT_DLLPATH)->SetWindowText(_T("../../../../lib"));
   
	//����Ĭ��ֵ
	m_nCarDTypeID = 2;
	m_nImgSizeType = 2;
	UpdateData(TRUE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVCDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVCDemoDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVCDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVCDemoDlg::OnBnClickedBtnLoadKernal()
{
	//load id card  kernel
	//��Ӧ�ó�������ʱ����һ�μ��غ��ģ�����ʶ��һ�μ���һ�Ρ�
	UpdateData(TRUE);
	if(!m_bIsInitSuccess)
	{
	    LoadKernal();
	}
	else
	{
		m_strResult = _T("ʶ������ѳɹ�����");
	}
	UpdateDeviceInfo();
	UpdateData(FALSE);
}

/*
 *load kernel
 */
BOOL CVCDemoDlg::LoadKernal()
{
	
	CString strDllPath = _T("");
	GetDlgItem(IDC_EDIT_DLLPATH)->GetWindowTextW(strDllPath);
	if (strDllPath == _T(""))
	{
		m_hIDCard = LoadLibrary(_T("IDCard.dll"));
	}
	else
	{
		m_hIDCard = ::LoadLibraryEx(strDllPath + _T("\\IDCard.dll"), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
	}

	if(m_hIDCard == NULL)
	{
		m_strResult=_T("LoadLibrary����");
		return FALSE;
	}

	fpInitIDCard = (int (WINAPI *)(LPCTSTR, int ,LPCTSTR))GetProcAddress(m_hIDCard, "InitIDCard");
	fpFreeIDCard = (void (WINAPI *)())GetProcAddress(m_hIDCard, "FreeIDCard");
	/**********AcquireImage**************/
	fpSetAcquireImageType = (bool (WINAPI*)(int, int))GetProcAddress(m_hIDCard, "SetAcquireImageType");	
	fpSetUserDefinedImageSize = (bool (WINAPI *)(int, int))GetProcAddress(m_hIDCard, "SetUserDefinedImageSize");
	fpSetAcquireImageResolution = (bool (WINAPI *)(int, int))GetProcAddress(m_hIDCard, "SetAcquireImageResolution");
	fpAcquireImage = (int (WINAPI *)(int))GetProcAddress(m_hIDCard, "AcquireImage");	
	/**********Recog**************/
	fpResetIDCardID = (int  (WINAPI *)())GetProcAddress(m_hIDCard, "ResetIDCardID");
	fpAddIDCardID= (int (WINAPI *)(int ,int *,int ))GetProcAddress(m_hIDCard, "AddIDCardID");
	fpSetIDCardRejectType = (int (WINAPI *)(int,bool))GetProcAddress(m_hIDCard, "SetIDCardRejectType");
	fpRecogIDCard = (int (WINAPI *)())GetProcAddress(m_hIDCard, "RecogIDCard");	
	fpRecogIDCardEx = (int (WINAPI *)(int,int))GetProcAddress(m_hIDCard, "RecogIDCardEX");
	fpGetFieldName = (int (WINAPI *)(int, LPTSTR, int&))GetProcAddress(m_hIDCard, "GetFieldName");
	fpGetRecogResult = (int (WINAPI *)(int, LPTSTR, int&))GetProcAddress(m_hIDCard, "GetRecogResult");
	fpGetResultType = (int (WINAPI *)(int))GetProcAddress(m_hIDCard, "GetResultType");
	fpGetSubId = (int (WINAPI *)())GetProcAddress(m_hIDCard, "GetSubID");
	fpGetIDCardName = (int (WINAPI *)(LPTSTR, int&))GetProcAddress(m_hIDCard, "GetIDCardName");
	/**********SaveImage**************/
	fpSaveImage = (int (WINAPI*)(LPCTSTR))GetProcAddress(m_hIDCard, "SaveImage");
	fpSaveHeadImage = (int (WINAPI *)(LPCTSTR ))GetProcAddress(m_hIDCard, "SaveHeadImage");
	/**********Special**************/
	fpGetVersionInfo = (void (WINAPI *)(LPCTSTR, int))GetProcAddress(m_hIDCard, "GetVersionInfo");
	fpCheckDeviceOnlineEx = (bool (WINAPI *)())GetProcAddress(m_hIDCard, "CheckDeviceOnlineEx");
	fpGetCurrentDevice = (BOOL (WINAPI *)(LPCTSTR, int))GetProcAddress(m_hIDCard, "GetCurrentDevice");
	fpGetDeviceSN = (int(WINAPI *)(LPCTSTR,int))GetProcAddress(m_hIDCard,"GetDeviceSN");
	/**********BusinessCard**************/
	pRecogBusinessCard =(int (WINAPI *)(int nCardType))GetProcAddress(m_hIDCard,"RecogBusinessCard");
	pGetBusinessCardResult=(int (WINAPI *)(int nID,int nIndex,LPWSTR lpBuffer,int &nBufferLen))GetProcAddress(m_hIDCard,"GetBusinessCardResult");
	pGetBusinessCardPosition=(int (WINAPI *)(int nID,int nIndex,int &nLeft,int &nRight,int &nTop, int &nBottom))GetProcAddress(m_hIDCard,"GetBusinessCardPosition");
	pGetBusinessCardFieldName=(int (WINAPI * )(int nID,LPWSTR lpBuffer,int &nBufferLen))GetProcAddress(m_hIDCard,"GetBusinessCardFieldName");
	pGetBusinessCardResultCount=(int (WINAPI *)(int nID))GetProcAddress(m_hIDCard,"GetBusinessCardResultCount");
	
	fpCheckDeviceSI = (int(WINAPI*)(LPCWSTR, int))GetProcAddress(m_hIDCard, "CheckDeviceSI");
	fpWriteDeviceSI=(int(WINAPI*)(LPCWSTR, int))GetProcAddress(m_hIDCard,"WriteDeviceSI");
	if( fpInitIDCard == NULL 
		|| fpFreeIDCard == NULL
		|| fpSetAcquireImageType == NULL
		|| fpSetUserDefinedImageSize == NULL
		|| fpSetAcquireImageResolution == NULL
		|| fpAcquireImage == NULL
		|| fpSaveImage == NULL
		|| fpSaveHeadImage == NULL
		|| fpRecogIDCard == NULL
		|| fpCheckDeviceOnlineEx == NULL
		|| fpGetRecogResult == NULL
		|| fpGetFieldName == NULL
		|| fpGetIDCardName == NULL
		|| fpGetCurrentDevice == NULL
		|| fpGetVersionInfo == NULL
		|| fpGetSubId == NULL
		|| fpResetIDCardID == NULL
		|| fpAddIDCardID == NULL
		|| fpRecogIDCardEx == NULL
		|| fpGetSubId == NULL
		|| fpResetIDCardID==NULL
		|| fpAddIDCardID==NULL
		|| fpGetDeviceSN == NULL
		|| fpCheckDeviceSI == NULL
		|| fpWriteDeviceSI == NULL)
	{
		::FreeLibrary(m_hIDCard);
		m_hIDCard = NULL;
		return FALSE;
	}

	m_bIsInitSuccess = FALSE;

	//init the id card
	int nRet = 0;
	if (strDllPath == _T(""))
	{
		nRet =  fpInitIDCard(m_strUserID, 1, NULL);
	}
	else
	{
		nRet = fpInitIDCard(m_strUserID, 1, strDllPath);
	}
	CString strRetCode;
	strRetCode.Format(_T("����ֵ��%d\r\n"),nRet);
	m_strResult = strRetCode;
	if (nRet==0)
	{
		m_bIsInitSuccess = TRUE;
		m_strResult = _T("ʶ����ļ��سɹ�");
		return TRUE;
	}
	else if (nRet==1)
	{
		m_bIsInitSuccess = FALSE;
		m_strResult += _T("��Ч���û�ID");
	}
	else
	{
		m_bIsInitSuccess = FALSE;
		m_strResult += _T("���ļ���ʧ��");

	}
	return FALSE;
}

//unload kernel
void CVCDemoDlg::UnLoadKernal()
{
	if(fpFreeIDCard!=NULL)
	{
        fpFreeIDCard();
	}
	if(m_hIDCard != NULL)
	{
		FreeLibrary(m_hIDCard);
		m_hIDCard = NULL;
	}
	fpInitIDCard = NULL;
	fpFreeIDCard = NULL;

	fpSetAcquireImageType = NULL;
	fpSetUserDefinedImageSize = NULL;
	fpSetAcquireImageResolution = NULL;
	fpAcquireImage = NULL;

	fpSaveImage = NULL;
	fpSaveHeadImage = NULL;

	fpResetIDCardID = NULL;
	fpAddIDCardID = NULL;
	fpSetIDCardRejectType = NULL;
	fpRecogIDCard = NULL;
	fpRecogIDCardEx = NULL;

	fpGetRecogResult = NULL;
	fpGetResultType = NULL;
	fpGetFieldName = NULL;
	fpGetSubId = NULL;
	fpGetIDCardName = NULL;

	fpGetDeviceSN =NULL;
	fpGetVersionInfo = NULL;
	fpGetCurrentDevice = NULL;
	fpCheckDeviceOnlineEx = NULL;

	pRecogBusinessCard =NULL;
	pGetBusinessCardResult=NULL;
	pGetBusinessCardPosition=NULL;
	pGetBusinessCardFieldName=NULL;
	pGetBusinessCardResultCount=NULL;
}


/* 
 * recognize image in memory
 */
void CVCDemoDlg::OnBnClickedBtnRecogImgInMemory()
{
	if(!m_bIsInitSuccess)
	{
		m_strResult = _T("δ�ɹ�����ʶ����ģ����ܽ���ʶ��");
		UpdateData(FALSE);
		return;
	}
	
	//1���Ȳɼ�ͼ��
	UpdateData(TRUE);
	//�жϲɼ�ͼ������Ƿ���ȷ
	if (m_nImgSizeType<0)
	{
		m_strResult = _T("��Ч��֤���ߴ�����");
		UpdateData(FALSE);
		return;
	}
	//����ͼ��ɼ��ӿڻ�ȡ�ڴ�ͼ��
	int nRet = fpAcquireImage(m_nImgSizeType);

	if(nRet != 0)
	{ 
		CString strErrCode;
		strErrCode.Format(_T("����ֵ��%d\r\n"),nRet);
		m_strResult = strErrCode;
		m_strResult += _T("�ɼ�ͼ��ʧ��\r\n");
		UpdateData(FALSE);
		return;
	}

	//2������Ҫ���Ա���ɼ���ͼ���֤��ͷ��
	//����ɼ���ͼ�񵽱��أ��˽ӿڵ���ǰ�����ȵ��òɼ��ӿ�fpAcquireImage��ȡͼ��
	CString strRunPath = GetRunPath();
	CString strSrcImg = strRunPath;
	strSrcImg += _T("IDCard.jpg");
	nRet = fpSaveImage(strSrcImg);
	//����ʶ���ȡ��ͷ�񵽱���
	CString strHeadImg = strRunPath;
	strHeadImg += _T("IDCard_Head.jpg");
	fpSaveHeadImage(strHeadImg);
	if (nRet != 0)
	{
		CString strErrCode;
		strErrCode.Format(_T("����ֵ��%d\r\n"), nRet);
		m_strResult = strErrCode;
		m_strResult += _T("ͼƬ����ʧ��\r\n");
		UpdateData(FALSE);
	}

	//3��ʶ��
	//�ж�ʶ������Ƿ���ȷ
	if (m_nCarDTypeID<0)
	{
		m_strResult = _T("��Ч��֤�����ͣ�������������Ч��֤������");
		UpdateData(FALSE);
		return;
	}
	//����ʶ��ӿڽ���ʶ��
	//m_nCarDTypeID���Ա�ʾһ��֤������1��ʾһ��֤��2��ʾ����֤��3��ʾ����֤����
	//m_nCarDTypeID=1��ʾʶ��һ��֤
	if (m_nCarDTypeID==1010)
	{
		int nRet = pRecogBusinessCard(1);
		if (nRet==0)
		{
			m_strResult = _T("ʶ��ɹ�\r\n");
			int i=0;
			while(true)
			{
				TCHAR strResult[100];
				memset(strResult,0,sizeof(TCHAR)*100);
				int nLenth=100;
				nRet = pGetBusinessCardFieldName(i,strResult,nLenth);
				if (nRet>0)
				{
					int nCount =pGetBusinessCardResultCount(i);
					CString fieldname=strResult;
					if (nCount==0)
					{
						m_strResult+=fieldname;
						m_strResult+= _T(" : ");
						m_strResult+=_T("\r\n");
					}
					for (int j=0;j<nCount;j++)
					{
						m_strResult+=fieldname;
						m_strResult+= _T(" : ");
						pGetBusinessCardResult(i,j,strResult,nLenth);
						CString Resultname=strResult;
						m_strResult+= Resultname;
						m_strResult+=_T("\r\n");
					}
					i++;
				}
				else if(nRet<=0)
					break;
			}
		}
	}
	else
	{	
		/*RecogtIDCard()����*/
		int tmp[1]={0};
		fpResetIDCardID();	
		/* ��һ�������ö���Ҫʶ���֤������ */
		fpAddIDCardID(m_nCarDTypeID,tmp,1);
		fpAddIDCardID(25, tmp, 1);
		fpAddIDCardID(26, tmp, 1);
		fpSetIDCardRejectType(m_nCarDTypeID,true);
		nRet = fpRecogIDCard();

		//RecogIDCardEX()���ã�����ʶ����ѡһ����
		//����ʶ��ӿ�ǰ����ʶ�������Ƿ��ʶ
		//nRet = fpSetIDCardRejectType(m_nCarDTypeID,true);
		//nRet = fpRecogIDCardEx(m_nCarDTypeID,0);

		if(nRet <= 0)
		{
			CString strErrCode;
			strErrCode.Format(_T("����ֵ��%d\r\n"),nRet);
			m_strResult = strErrCode;
			m_strResult += _T("ʶ��ʧ��\r\n");
			UpdateData(FALSE);
			return ;
		}

		//��ȡʶ����

		CONST int MAX_CH_NUM = 256;
		TCHAR szFieldValue[MAX_CH_NUM];
		TCHAR szFieldName[MAX_CH_NUM];
		TCHAR szCardName[MAX_CH_NUM];
		int nBufLen = MAX_CH_NUM * sizeof(TCHAR);
		int nIndex = 1;
		m_strResult = _T("ʶ��ɹ�\r\n");
		memset(szCardName, 0, nBufLen);
		fpGetIDCardName(szCardName, nBufLen);
		m_strResult += _T("֤������ ��");
		m_strResult += szCardName;
		m_strResult = _T("\r\n");
		while(TRUE)
		{
			memset(szFieldValue,0,sizeof szFieldValue);
			memset(szFieldName,0, sizeof szFieldName);
			
			//��ȡnIndex��Ӧ��ʶ������

			nBufLen = MAX_CH_NUM * sizeof(TCHAR);
			nRet = fpGetRecogResult(nIndex, szFieldValue, nBufLen);
			if(nRet == 3)
				break;
			nBufLen = MAX_CH_NUM * sizeof(TCHAR);
			//��ȡʶ����ֶ�����,nIndex��Ӧ���ֶ����ƿ��Բ鿪���ĵ�
			
			fpGetFieldName(nIndex, szFieldName, nBufLen);
			
			std::string strRet = std::to_string(fpGetResultType(nIndex));
			++nIndex;

			//������ʾ
			CString strTmp = _T("");
			strTmp = (CString(szFieldName) + CString("(")+ CString(strRet.c_str()) + CString(")") + _T(" : "));
			strTmp += (CString(szFieldValue) + _T("\r\n"));
			m_strResult += strTmp;
		}
		//ʶ��ɹ������GetSubID�ӿ�
		nRet = fpGetSubId();
		m_strResult += _T("֤�������ͣ�");
		std::string str = std::to_string(nRet);
		m_strResult += str.c_str();
	}
	
	UpdateData(FALSE);

}


/*
 *	unload id card 
 */
void CVCDemoDlg::OnBnClickedBtnUnloadKernel()
{
	if(m_bIsInitSuccess)
		UnLoadKernal();
	m_bIsInitSuccess = FALSE;
	m_strResult = _T("ж�غ������\r\n");
	UpdateData(FALSE);
}


/*
 * Set custom size to acquire image
 */
void CVCDemoDlg::OnBnClickedBtnSetUserDefineImgSize()
{
	if(!m_bIsInitSuccess)
	{
		m_strResult = _T("����ǰ�����ȳɹ�����ʶ�����");
		UpdateData(FALSE);
		return ;
	}
	UpdateData(TRUE);
	if (m_nImageWidth<=0||m_nImageHeight<=0)
	{
		m_strResult = _T("�Զ���ĳߴ���Ч�������¶���");
		UpdateData(FALSE);
		return ;

	}

	BOOL bRet = fpSetUserDefinedImageSize(m_nImageWidth, m_nImageHeight);
	if(!bRet)
		m_strResult = (_T("�����Զ���ɼ��ĳߴ�ʧ��"));
	else
		m_strResult = (_T("�����Զ���ɼ��ĳߴ�ɹ�"));
	UpdateData(FALSE);
	
}

/*
 * Set AcImage's resolution
 */
void CVCDemoDlg::OnBnClickedBtnSetAcquireImgResolution()
{
	if(!m_bIsInitSuccess)
	{
		m_strResult = _T("����ǰ�����ȳɹ�����ʶ�����");
		UpdateData(FALSE);
		return ;
	}
	// 
	UpdateData(TRUE);
	m_nVertResolution = m_nHoriResolution;
	BOOL bRet = fpSetAcquireImageResolution(m_nHoriResolution, m_nVertResolution);

	if(!bRet)
		m_strResult = _T("�����Զ���ɼ��ķֱ���ʧ��");
	else
		m_strResult = _T("�����Զ���ɼ��ķֱ��ʳɹ�");
	UpdateData(FALSE);


 }

CString CVCDemoDlg::GetRunPath()
{
	CString  sWorkPath , strTemp;
	sWorkPath.Empty();
	strTemp.Empty();
	int nRet = 0,nErrorCode = 0;
	nRet = GetModuleFileName(NULL,sWorkPath.GetBufferSetLength (MAX_PATH+1),MAX_PATH);
	if(0 == nRet)
	{
         return _T("");
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

void CVCDemoDlg::UpdateDeviceInfo()
{
	if (!m_bIsInitSuccess)
	{
		//m_strResult = _T("����ǰ�����ȳɹ�����ʶ�����");
		AfxMessageBox(_T("����ǰ�����ȳɹ�!����ʶ�����"));
		UpdateData(FALSE);
		return;
	}

	//get the version
	TCHAR szVersion[128];
	memset(szVersion, '\0', sizeof(szVersion));
	fpGetVersionInfo(szVersion, 128);


	//check device on line 
	if (!fpCheckDeviceOnlineEx())
	{
		AfxMessageBox(_T("�����豸�Ƿ�����������"));
		return;
	}

	//get the device name
	TCHAR szDeviceName[128];
	memset(szDeviceName, '\0', sizeof(szDeviceName));
	
	//get the serialnumber
	TCHAR szSn[128];
	memset(szSn, '\0', sizeof(szSn));
	if (fpGetDeviceSN(szSn, 16))
	{
		AfxMessageBox(_T("��ȡ�豸���к�ʧ�ܣ�"));
		return;
	}

	BOOL bRet = fpGetCurrentDevice(szDeviceName, 128);
	if (!bRet)
	{
		AfxMessageBox(_T("��ȡ�豸��ʧ�ܣ�"));
		return;
	}
	USES_CONVERSION_EX;
	std::string strRes = CW2A(CString(szVersion));
	strRes = strRes.substr(strRes.find_last_of(" ") + 1, strRes.size());
	CString strWindowTitle = _T("");
	strWindowTitle = (_T("ɨ���ǲ�����")+ CString(_T("_")) + CString(strRes.c_str()) + CString(_T("_")) + CString(szDeviceName)+ _T("(") + CString(szSn) + _T(")"));
	SetWindowText(strWindowTitle);

	return;
}

void CVCDemoDlg::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	UnLoadKernal();
	KillTimer(ID_PASSPORT_READER_TIMER);
	CDialog::OnClose();
}

void CVCDemoDlg::OnBnClickedBtnAcimage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (!m_bIsInitSuccess)
	{
		m_strResult = _T("δ�ɹ�����ʶ����ģ����ܽ���ʶ��\r\n");
		UpdateData(FALSE);
		return;
	}

	//�ɼ�ͼ��
	int nRet = fpAcquireImage(m_nImagCustomSize);
	if (nRet != 0)
	{
		CString strErrCode;
		strErrCode.Format(_T("����ֵ��%d\r\n"), nRet);
		m_strResult = strErrCode;
		m_strResult += _T("�ɼ�ͼ��ʧ��\r\n");
		UpdateData(FALSE);
		return;
	}
	else
	{
		m_strResult += _T("�ɼ�ͼ��ɹ�\r\n");
	}
	//����ɼ���ͼ�񵽱��أ��˽ӿڵ���ǰ�����ȵ��òɼ��ӿ�fpAcquireImage��ȡͼ��
	CString strRunPath = GetRunPath();
	CString strSrcImg = strRunPath;
	strSrcImg += _T("IDCard.jpg");
	nRet = fpSaveImage(strSrcImg);
	if (nRet != 0)
	{
		CString strErrCode;
		strErrCode.Format(_T("����ֵ��%d\r\n"), nRet);
		m_strResult = strErrCode;
		m_strResult += _T("����ͼ��ʧ��\r\n");
		UpdateData(FALSE);
	}
	else
	{
		m_strResult += _T("����ͼ��ɹ�\r\n");
		UpdateData(FALSE);
	}
	//����ʶ���ȡ��ͷ�񵽱���
	CString strHeadImg = strRunPath;
	strHeadImg += _T("IDCard_Head.jpg");
	fpSaveHeadImage(strHeadImg);

}
