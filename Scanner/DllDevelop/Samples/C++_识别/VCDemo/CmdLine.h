#pragma once

#ifndef LIXF_COMMANDLINE_H
#define LIXF_COMMANDLINE_H

// ���ܣ�����������
// ���ߣ���ѩ��
// ʱ�䣺2006-05-22  
#define USE_A600
//#define USE_D800

class CCmdLine
{
public:
	// ���ܣ����캯��
	// �������ޡ�
	// ����ֵ���ޡ�
	CCmdLine(void);

	// ���ܣ���������
	// �������ޡ�
	// ����ֵ���ޡ�
	~CCmdLine(void);

public:
	// ���ܣ�ȡ�������еĲ�������	
	// �������ޡ�
	// ����ֵ��
	//        �����в����ĸ����� 
	int GetCount(void) const;

	// ���ܣ�ȡ��ĳ�������в���
	// ������
	//     [in]nIndex: �ڼ�����������СֵΪ0
	// ����ֵ��
	//     ��nIndex�������в�����
	LPCTSTR GetParam(int nIndex) const;

	// ���ܣ�ȡ������������
	// �������ޡ�
	// ����ֵ��
	//     ����������
	LPTSTR GetCmdLine(void) const;

private:
	// ���ܣ�����������
	// �������ޡ�
	// ����ֵ���ޡ� 
	void ParseCmdLine(void);
	
private:
	// ����������
	LPTSTR m_lpszCmdLine;

	// ������������в�������
	CStringArray m_arrArgv;

private:
	CCmdLine(const CCmdLine &);
	const CCmdLine& operator=(const CCmdLine &);
};

#endif