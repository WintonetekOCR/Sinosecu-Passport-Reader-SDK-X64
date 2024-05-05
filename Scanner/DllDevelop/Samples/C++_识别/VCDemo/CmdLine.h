#pragma once

#ifndef LIXF_COMMANDLINE_H
#define LIXF_COMMANDLINE_H

// 功能：解析命令行
// 作者：李雪峰
// 时间：2006-05-22  
#define USE_A600
//#define USE_D800

class CCmdLine
{
public:
	// 功能：构造函数
	// 参数：无。
	// 返回值：无。
	CCmdLine(void);

	// 功能：析构函数
	// 参数：无。
	// 返回值：无。
	~CCmdLine(void);

public:
	// 功能：取得命令行的参数个数	
	// 参数：无。
	// 返回值：
	//        命令行参数的个数。 
	int GetCount(void) const;

	// 功能：取得某个命令行参数
	// 参数：
	//     [in]nIndex: 第几个参数，最小值为0
	// 返回值：
	//     第nIndex个命令行参数。
	LPCTSTR GetParam(int nIndex) const;

	// 功能：取得整个命令行
	// 参数：无。
	// 返回值：
	//     整个命令行
	LPTSTR GetCmdLine(void) const;

private:
	// 功能：解析命令行
	// 参数：无。
	// 返回值：无。 
	void ParseCmdLine(void);
	
private:
	// 整个命令行
	LPTSTR m_lpszCmdLine;

	// 解析后的命令行参数数组
	CStringArray m_arrArgv;

private:
	CCmdLine(const CCmdLine &);
	const CCmdLine& operator=(const CCmdLine &);
};

#endif