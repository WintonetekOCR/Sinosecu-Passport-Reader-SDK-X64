
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
	int m_nCardType;		// 1:��оƬ,2:��ͨMRZ֤��,3:����MRZ֤��
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

	int (WINAPI *fpSDT_OpenPort)(int iPort);		// �򿪶˿�
	int (WINAPI *fpSDT_ClosePort)(int iPort);		// �رն˿�
	int (WINAPI *fpSDT_StartFindIDCard)(int iPort, unsigned char *pRAPDU, int iIfOpen);						// �ҿ�
	int (WINAPI *fpSDT_SelectIDCard)(int iPort, unsigned char *pRAPDU, int iIfOpen);							// ѡ��
	int (WINAPI *fpSDT_ReadBaseMsgToFile)(int iPort,
		char* pcCHMsgFileName, unsigned int* pm_uiCHMsgFileLen,
		char* pcPHMsgFileName, unsigned int* pm_uiPHMsgFileLen,
		char* pcFPMsgFileName, unsigned int* pm_uiFPMsgFileLen, int iIfOpen);	                                // ��ȡ������Ϣ���ļ�
	int (WINAPI *fpSDT_ReadBaseFPMsg)(int iPort,
		unsigned char* pcCHMsg, unsigned int* pm_uiCHMsgLen,
		unsigned char* pcPHMsg, unsigned int* pm_uiPHMsgLen,
		unsigned char* pcFPMsg, unsigned int* pm_uiFPMsgLen, int iIfOpen);		                             // ��ȡ������Ϣ
	int (WINAPI *fpSDT_ReadNewAppMsg)(int iPortID, unsigned char * pucAppMsg,
		unsigned int *puiAppMsgLen, int iIfOpen);															// �ж����Ƿ��Ѿ�����
																											// ��ȡλͼͷ�����ݽӿ�
	int (WINAPI *m_lpGetBmp)(char * wltfile, int nType);
	int (WINAPI *fpSDT_GetSAMIDToStr)(int iPortID, char *pcSAMID, int iIfOpen);
	int (WINAPI *SDT_GetSAMID)(int iPortID, unsigned char *pucSAMID, int iIfOpen);

	CString GetName(void);							// ��ȡ����
	CString GetSex(void);							// ��ȡ�Ա�
	CString GetPeople(void);						// ��ȡ����
	CString GetBirthday(void);						// ��ȡ��������
	CString GetAddress(void);						// ��ȡסַ
	CString GetAuthority(void);						// ��ȡǩ������
	CString GetIDCode(void);						// ��ȡ���֤��
	CString GetIssueDay(void);						// ��ȡ��Ч����ʼ����
	CString GetExpityDay(void);						// ��ȡ��Ч�ڽ�ֹ����
	CString GetPassNum(void);                       //��ȡͨ��֤����
	CString GetIssueNum(void);                      //��ȡǩ������
	CString GetFingerprintInfo();                   //��ȡָ����Ϣ
	CString GetPeopleChineseName();					// ��ȡ�������������
	CString GetOldIDCode();							//�����°��Ƶ��ϰ���������þ���֤����
	int AssignedNumbers(CString cstr);						//���������ֵ
	CString GetCardVersion();						// ���֤���汾��
	CString GetReverse();							// ��ȡԤ����
	CString GetReverseGAT(int nPosition,int nVal);					// ��ȡԤ����
	CString GetNumberOfCertificateRenewals();//��ȡ�°����þ���֤��֤����
	CString GetEnglishName();//��ȡ�°����þ���֤Ӣ������
	CString GetEnglishNameStandBy();//��ȡ�°����þ���֤Ӣ����������
	CString GetCountryOrRegionCode();//��ȡ�°����þ���֤�������һ��������
	CString GetNumberAssociation();//��ȡ�����汾��������þ���֤�����������
	CString GetNumberFlag();//��ȡ�°����þ���֤֤�����ͱ�־
	void	ShowCHMsg_SID();						// ��ʾ����֤������Ϣ������
	void	ShowCHMsg_PrpNew();						// ��ʾ�°����þ�ס֤������Ϣ������
	void	ShowCHMsg_Prp();						// ��ʾ�ɰ����þ�ס֤������Ϣ������
	void    ShowCHMsg_Rrp();                        // ��ʾ�۰�̨�����ס֤������Ϣ������
	int		SavePhoto(LPCTSTR FileName, int nType);	// ����λͼͷ��
	int		LoadDll(void);							// ����sdtapi.dll,WltRS.dll
	int 	ReadSIDCard();								// ����֤����

	bool			m_bLoad;						// �Ƿ�ɹ�����dll
	int				m_nOpenPort;					// ����򿪵Ķ˿ں�
	bool			m_bSID;							// �Ƿ�Ϊ����֤
	unsigned char	m_pucCHMsg[1280];				// ������Ϣ
	unsigned char	m_pucPHMsg[1024];				// ��Ƭ��Ϣ
	unsigned char	m_pucFPMsg[1024];				// ָ����Ϣ
	unsigned char   DtiTmp[2];                      //֤��������Ϣ
	unsigned int	m_uiCHMsgLen;					// ������Ϣ���ݳ���
	unsigned int	m_uiPHMsgLen;					// ��Ƭ��Ϣ���ݳ���
	unsigned int	m_uiFPMsgLen;					// ָ����Ϣ���ݳ���
	CString			m_strWorkPath;					// exe����Ŀ¼
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
	// �Ƿ�����α
	BOOL m_bCheckVerity;
	afx_msg void OnBnClickedCheckVerify();
};
