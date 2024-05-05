
// EPRSampleDemoDlg.h : header file
//

#pragma once
#include<list>
#include<vector>
#include<string>
#include<iostream>
#include "afxwin.h"

using namespace std;

// CEPRSampleDemoDlg dialog
class CEPRSampleDemoDlg : public CDialogEx
{
// Construction
public:
	CEPRSampleDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EPRSAMPLEDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	typedef enum
	{
		AuthNotOpen = -1, // Not opened
		AuthPassed,      // passed
		AuthFailed,      // failed
		AuthManualCheck, // needs manual check
		AuthUnsupported, // not supported item
		AuthInvalidDocument,  // invalid docoment
		OCRFaild
	} AuthResultType;
	CRect m_OldRect;
	CDWordArray m_ctrlInfo;
	HINSTANCE m_hIDCard;
	CString m_strErrMsg;
	CString m_strUserID;
	CString m_strResult;
	CString GetWorkPath();
	CString m_strDGResult;
	CString m_strImagePath;

	UINT m_ReadDGFlag;
	UINT m_SaveImageFlag;
	int m_nCardType;		// 1:带芯片,2:普通MRZ证件,3:不含MRZ证件
	int m_nIDNum;

	bool m_bInitSuccess;
	bool m_bWhiteImage;
	bool m_bIRImage;
	bool m_bUVImage;
	bool m_bPageHead;
	bool m_bChipHead;
	bool m_bVIZ;
	
	int InitCardDll();
	void FreeCardDll();
	void GetRecogCondition();
	void ReadCard(); 
	void GetContent();
	void GetDGContent();
	void SetControlInfo(DWORD ID);
	int AddDGContent(UINT);
	int AddContent(UINT);
	BOOL BrowseForPath(CString& tPath);
	
	afx_msg void OnBnClickedButtonLoadkernel();
	afx_msg void OnBnClickedButtonFreekernel();
	afx_msg void OnBnClickedButtonVersionInfo();
	afx_msg void OnBnClickedButtonDeviceName();
	afx_msg void OnBnClickedButtonDeviceIsline();
	afx_msg void OnBnClickedButtonDeviceSequence();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonRecog();

	int (WINAPI *pInitIDCard)(LPCTSTR lpUserID, int nType,LPCTSTR lpDirectory);
	void (WINAPI *pFreeIDCard)();
	int (WINAPI *pGetRecogResultEx)(int  nAttribute,int nIndex, LPTSTR lpBuffer,int &nBufferLen);
	int (WINAPI *pGetFieldNameEx)(int nAttribute, int nIndex, LPTSTR lpBuffer, int &nBufferLen);
	void (WINAPI *pResetIDCardID)();
	int (WINAPI *pAddIDCardID)(int nMainID,int nSubID[],int nSubIdCount);
	void (WINAPI *pSetRecogDG)(int);
	void (WINAPI *pSetSaveImageType)(int);
	void (WINAPI *pSetRecogVIZ)(bool);
	int (WINAPI *pDetectDocument)();
	bool (WINAPI *pGetVersionInfo)(LPCTSTR lpBuffer,int nBufferLen);
	int (WINAPI *pGetDeviceSN)(LPTSTR ,int );
	int (WINAPI *pSaveImageEx)(LPCTSTR lpFileName,int nType);
	int (WINAPI *pSaveImageRaw)(LPCWSTR lpFileName, int nType);
	int (WINAPI *pAutoProcessIDCard)(int &nCardType);
	int (WINAPI *pSetConfigByFile)(LPCWSTR lpConfigFile);
	BOOL(WINAPI *pCheckDeviceOnline)();
	BOOL(WINAPI *pGetCurrentDevice)(LPTSTR deviceName, int nBufferLenth);
	int (WINAPI *pAutoVerifyIDCard)(int& nRiskFactor);
	/*int (WINAPI *pGetVerificationClassCount)();
	int (WINAPI *pGetVerificationClassName)(int nClassType, wchar_t* wClassName, int& nSizeOfName);
	int (WINAPI *pGetVerificationItemCountInClass)(int nClassType);
	int (WINAPI *pGetVerificationItem)(int nClassType, int nItemIndex, int& nVerifyResult, wchar_t* wRemark, int& nSizeOfRemark);
	int (WINAPI *pGetVerificationItemName)(int nClassType, int nItemIndex, wchar_t* wName, int& nSizeOfName);
	int (WINAPI *pGetReferencedElementCount)(int nClassType, int nItemIndex, int& nRefCount);
	int (WINAPI *pGetReferencedElement)(
		int nClassType,
		int nItemIndex,
		int nRefIndex,
		wchar_t* wFieldName,
		int& nSizeOfName,
		int& nOrigin,
		int  vCoordinates[],
		int& nCoordinateCount,
		wchar_t* wFieldContent,
		int& nSizeOfContent,
		wchar_t* wNotes,
		int& nSizeOfNotes
	);*/

	/*---------------------The Followed is SID's code.(Second generation resident ID card)------------------*/
private:
	HMODULE m_hNIDapi;
	HMODULE	m_hGetBmp;

	int (WINAPI *fpSDT_OpenPort)(int iPort);		// 打开端口
	int (WINAPI *fpSDT_ClosePort)(int iPort);		// 关闭端口
	int (WINAPI *fpSDT_StartFindIDCard)(int iPort, unsigned char *pRAPDU, int iIfOpen);						// 找卡
	int (WINAPI *fpSDT_SelectIDCard)(int iPort, unsigned char *pRAPDU, int iIfOpen);							// 选卡
	int (WINAPI *fpSDT_ReadBaseMsgToFile)(int iPort,
		char* pcCHMsgFileName, unsigned int* pm_uiCHMsgFileLen,
		char* pcPHMsgFileName, unsigned int* pm_uiPHMsgFileLen,
		char* pcFPMsgFileName, unsigned int* pm_uiFPMsgFileLen, int iIfOpen);	                                // 读取基本信息到文件
	int (WINAPI *fpSDT_ReadBaseFPMsg)(int iPort,
		unsigned char* pcCHMsg, unsigned int* pm_uiCHMsgLen,
		unsigned char* pcPHMsg, unsigned int* pm_uiPHMsgLen,
		unsigned char* pcFPMsg, unsigned int* pm_uiFPMsgLen, int iIfOpen);		                             // 读取基本信息
	int (WINAPI *fpSDT_ReadNewAppMsg)(int iPortID, unsigned char * pucAppMsg,
		unsigned int *puiAppMsgLen, int iIfOpen);															// 判读卡是否已经读过
																											// 获取位图头像数据接口
	int (WINAPI *m_lpGetBmp)(char * wltfile, int nType);
	int (WINAPI *fpSDT_GetSAMIDToStr)(int iPortID, char *pcSAMID, int iIfOpen);
	int (WINAPI *SDT_GetSAMID)(int iPortID, unsigned char *pucSAMID, int iIfOpen);

	CString GetName(void);							// 获取姓名
	CString GetSex(void);							// 获取性别
	CString GetPeople(void);						// 获取民族
	CString GetBirthday(void);						// 获取出生日期
	CString GetAddress(void);						// 获取住址
	CString GetAuthority(void);						// 获取签发机关
	CString GetIDCode(void);						// 获取身份证号
	CString GetIssueDay(void);						// 获取有效期起始日期
	CString GetExpityDay(void);						// 获取有效期截止日期
	CString GetPassNum(void);                       //获取通行证号码
	CString GetIssueNum(void);                      //获取签发次数
	CString GetFingerprintInfo();                   //获取指纹信息
	CString GetPeopleChineseName();					// 获取外国人中文姓名
	CString GetOldIDCode();							//根据新版推导老版外国人永久居留证号码
	int AssignedNumbers(CString cstr);						//赋予的数字值
	CString GetCardVersion();						// 获得证件版本号
	CString GetReverse();							// 获取预留项
	CString GetReverseGAT(int nPosition,int nVal);					// 获取预留项
	CString GetNumberOfCertificateRenewals();//获取新版永久居留证换证次数
	CString GetEnglishName();//获取新版永久居留证英文姓名
	CString GetEnglishNameStandBy();//获取新版永久居留证英文姓名备用
	CString GetCountryOrRegionCode();//获取新版永久居留证所属国家或地区代码
	CString GetNumberAssociation();//获取既往版本外国人永久居留证件号码关联项
	CString GetNumberFlag();//获取新版永久居留证证件类型标志
	void	ShowCHMsg_SID();						// 显示二代证文字信息到界面
	void	ShowCHMsg_PrpNew();						// 显示新版永久居住证文字信息到界面
	void	ShowCHMsg_Prp();						// 显示旧版永久居住证文字信息到界面
	void    ShowCHMsg_Rrp();                        // 显示港澳台居民居住证文字信息到界面
	int		SavePhoto(LPCTSTR FileName, int nType);	// 保存位图头像
	int		LoadDll(void);							// 加载sdtapi.dll,WltRS.dll
	int 	ReadSIDCard();								// 二代证读卡

	bool			m_bLoad;						// 是否成功加载dll
	int				m_nOpenPort;					// 保存打开的端口号
	bool			m_bSID;							// 是否为二代证
	unsigned char	m_pucCHMsg[1280];				// 文字信息
	unsigned char	m_pucPHMsg[1024];				// 照片信息
	unsigned char	m_pucFPMsg[1024];				// 指纹信息
	unsigned char   DtiTmp[2];                      //证件类型信息
	unsigned int	m_uiCHMsgLen;					// 文字信息数据长度
	unsigned int	m_uiPHMsgLen;					// 照片信息数据长度
	unsigned int	m_uiFPMsgLen;					// 指纹信息数据长度
	CString			m_strWorkPath;					// exe所在目录
public:
	CEdit m_editPicPath;
	CEdit m_editLibPath;
	CEdit m_editFigPath;
	CEdit m_EditResult;
	CEdit m_EditDG;
	vector<CString> m_vecImagePath;
	int nImageType;
	int m_nImageIndex;
	void ShowImage(CString strImagePath);
	void SaveImagePath(CString strImagePath, int nType);

	afx_msg void OnBnClickedBtnPre();
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnReadsidcard();
	afx_msg void OnBnClickedBtnBrowseDllpath();
	afx_msg void OnBnClickedBtnPicpath();
	afx_msg void OnCbnSelchangeComboIdent();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonDeviceSequence2();
	// 是否开启验伪
	BOOL m_bCheckVerity;
	afx_msg void OnBnClickedCheckVerify();
};
