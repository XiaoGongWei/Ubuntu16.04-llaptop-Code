
// ReadImage2Pix.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CReadImage2PixApp:
// �йش����ʵ�֣������ ReadImage2Pix.cpp
//

class CReadImage2PixApp : public CWinApp
{
public:
	CReadImage2PixApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CReadImage2PixApp theApp;