// VCDemo.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
//#include "MySti.h"

// CVCDemoApp:
// See VCDemo.cpp for the implementation of this class
//

class CVCDemoApp : public CWinApp
{
public:
	CVCDemoApp();

// Overrides
	public:
	virtual BOOL InitInstance();
	//CMySti m_MySti;

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CVCDemoApp theApp;