
// WinMonitor.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CWinMonitorApp:
// �� Ŭ������ ������ ���ؼ��� WinMonitor.cpp�� �����Ͻʽÿ�.
//

class CWinMonitorApp : public CWinApp
{
public:
	CWinMonitorApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CWinMonitorApp theApp;