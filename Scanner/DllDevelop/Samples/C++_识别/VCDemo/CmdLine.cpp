#include "StdAfx.h"
#include "CmdLine.h"

CCmdLine::CCmdLine() : m_lpszCmdLine(::GetCommandLine())
{
	ParseCmdLine();
}

CCmdLine::~CCmdLine()
{
	m_arrArgv.RemoveAll();
}

int CCmdLine::GetCount() const
{
	return m_arrArgv.GetSize();
}

LPCTSTR CCmdLine::GetParam(int nIndex) const
{
	if(0 == m_arrArgv.GetSize()) 
	{
		return NULL;
	}
	if((nIndex >= 0) && (nIndex < m_arrArgv.GetSize()))
	{
		return m_arrArgv.GetAt(nIndex);
	}
	else
	{
		return NULL;
	}	
}

LPTSTR CCmdLine::GetCmdLine() const
{
	return m_lpszCmdLine;
}

void CCmdLine::ParseCmdLine()
{
	if(NULL == m_lpszCmdLine) 
	{
		return;
	}

	// m_lpszCmdLine = "C:\Path\App.exe" /StiDevice:{6BDD1FC6-810F-11D0-BEC7-08002BE2092F}\0001 /StiEvent:{38E8FF61-A867-11d6-AAF8-0050BA1ACA6F}
	CString strCmdLine = m_lpszCmdLine;
	if((-1 == strCmdLine.Find(_T("/StiDevice"))) || (-1 == strCmdLine.Find(_T("/StiEvent"))))
	{
		return;
	}

	int nPos = strCmdLine.Find(_T('/'), 0);
	CString strTemp = strCmdLine.Mid(0, nPos);
	m_arrArgv.Add(strTemp);
	
	strCmdLine = strCmdLine.Mid(nPos);
	int nStart = strCmdLine.Find(_T(':'), 0);
	nStart ++;

	int nEnd   = strCmdLine.ReverseFind(_T('\\'));
	strTemp    = strCmdLine.Mid(nStart, nEnd - nStart);
	m_arrArgv.Add(strTemp);
	
	
	strCmdLine = strCmdLine.Mid(nEnd);
	nStart     = strCmdLine.Find(_T('{'), 0);
	strTemp    = strCmdLine.Mid(nStart);
	m_arrArgv.Add(strTemp);
}