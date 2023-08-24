#include "2DPushGraph.h"
// WinMonitorDlg.h : ��� ����
//

#pragma once


// CWinMonitorDlg ��ȭ ����
class CWinMonitorDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CWinMonitorDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_WINMONITOR_DIALOG };
// Dialog Data
	//{{AFX_DATA(CC2DPushGraphDlg)
	int		m_nGridSize;
	BOOL	m_bShowGrid;
	BOOL	m_bShowLabels;
	short	m_sInterval;
	int		m_nWaitTime;
	CString	m_strMaxLabel;
	int		m_nMaxPeek;
	CString	m_strMinLabel;
	int		m_nMinPeek;
	BOOL	m_bLine0AsBar;
	BOOL	m_bLine1AsBar;
	//}}AFX_DATA

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;
	virtual void OnOk();

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	C2DPushGraph	m_PushGraph;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
