
// ForceCode.h : ForceCode Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CForceCodeApp:
// �йش����ʵ�֣������ ForceCode.cpp
//

class CForceCodeApp : public CWinAppEx
{
public:
	CForceCodeApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��

public:
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	int FindFile(CString Curdir);
};

extern CForceCodeApp theApp;
