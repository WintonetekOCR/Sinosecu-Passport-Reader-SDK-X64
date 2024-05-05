// VCDemoDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <vector>
using std::vector;

//add manually
CONST int MAX_LABEL_COUNT = 18;
class CSetMainSubIdDlg;

// CVCDemoDlg dialog
class CVCDemoDlg : public CDialog
{
// Construction
public:
	CVCDemoDlg(CWnd* pParent = NULL);	// standard constructor
	~CVCDemoDlg();
	
// Dialog Data
	enum { IDD = IDD_VCDEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	CString GetRunPath();
	
// Implementation
public:
	HICON m_hIcon;
	
	HMODULE m_hIDCard;

	BOOL m_bIsInitSuccess;
	//all pointers of the function
	int   (WINAPI *fpInitIDCard)(LPCTSTR lpUserID, int nType,LPCTSTR lpDirectory);
	void (WINAPI *fpFreeIDCard)();
	//AcquireImage
	bool (WINAPI *fpSetAcquireImageType)(int nLightType,int nImageType);
	int (WINAPI *fpAcquireImage)(int nImageSizeType);	
	bool (WINAPI *fpSetUserDefinedImageSize)(int nWidth, int nHeight);
	bool (WINAPI *fpSetAcquireImageResolution)(int nResolutionX, int nResolutionY);
		
	int  (WINAPI *fpResetIDCardID)();
	int (WINAPI *fpAddIDCardID)(int nMainID,int nSubID[],int nSubIdCount);
	int (WINAPI *fpSetIDCardRejectType)(int nCardType, bool bSet);

	/****Recog****/
	int (WINAPI *fpRecogIDCard)();
	int (WINAPI *fpRecogIDCardEx)(int nMainID ,int nSubID);
	
	/****GetResult****/
	int (WINAPI *fpGetRecogResult)(int nIndex, LPTSTR lpBuffer, int &nBufferLen);
	int (WINAPI *fpGetFieldName)(int nIndex, LPTSTR lpBuffer, int &nBufferLen);
	int (WINAPI *fpGetSubId)();
	int (WINAPI *fpGetResultType)(int nIndex);
	int (WINAPI *fpGetIDCardName)(LPTSTR lpBuffer, int&nBufferLen);

	/*SaveImage*/
	int (WINAPI *fpSaveImage)(LPCTSTR lpFileName);
	int (WINAPI *fpSaveHeadImage)(LPCTSTR );
	
	/*Special*/
	bool (WINAPI *fpCheckDeviceOnlineEx)();
	void  (WINAPI *fpGetVersionInfo)(LPCTSTR ,int );
	BOOL (WINAPI *fpGetCurrentDevice)(LPCTSTR, int);
	int (WINAPI *fpGetDeviceSN)(LPCTSTR,int);
	int (WINAPI *fpWriteDeviceSI)(LPCTSTR, int);
	int (WINAPI *fpCheckDeviceSI)(LPCTSTR, int);

	/****BussinessCard****/
	int (WINAPI *pRecogBusinessCard)(int nCardType);
	int (WINAPI *pGetBusinessCardResult)(int nID,int nIndex,LPWSTR lpBuffer,int &nBufferLen);
	int (WINAPI *pGetBusinessCardPosition)(int nID,int nIndex,int &nLeft,int &nRight,int &nTop, int &nBottom);
	int (WINAPI *pGetBusinessCardFieldName)(int nID,LPWSTR lpBuffer,int &nBufferLen);
	int (WINAPI *pGetBusinessCardResultCount)(int nID);
	
	virtual BOOL OnInitDialog();

	BOOL LoadKernal();
	void UnLoadKernal();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_ctlCardTypeCombox;

	CString m_strResult;
	int m_nCarDTypeID;
	int m_nImgSizeType;
	int m_nImagCustomSize;
	CString m_strUserID;
	int m_nLightType;
	int m_nImageType;
	int m_nImageWidth;
	int m_nImageHeight;
	int m_nHoriResolution;
	int m_nVertResolution;

	void UpdateDeviceInfo();
	

	afx_msg void OnClose();
	/*afx_msg void OnBnClickedBtnGetDeviceSn();
	afx_msg void OnBnClickedBtnChecksi();
	afx_msg void OnBnClickedBtnWritesi();*/
	/*afx_msg void OnBnClickedBtnGetVersion();
	afx_msg void OnBnClickedBtnSetAcquireImgType();
	afx_msg void OnBnClickedBtnCheckDeviceOnLine();
	afx_msg void OnBnClickedBtnGetDeviceName();*/
	afx_msg void OnBnClickedBtnLoadKernal();
	afx_msg void OnBnClickedBtnRecogImgInMemory();
	afx_msg void OnBnClickedBtnUnloadKernel();	
	afx_msg void OnBnClickedBtnSetUserDefineImgSize();
	afx_msg void OnBnClickedBtnSetAcquireImgResolution();
	afx_msg void OnBnClickedBtnAcimage();
};
