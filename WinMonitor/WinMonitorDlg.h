#include "2DPushGraph.h"
// WinMonitorDlg.h : 헤더 파일
//

#pragma once


// CWinMonitorDlg 대화 상자
class CWinMonitorDlg : public CDialogEx
{
// 생성입니다.
public:
	CWinMonitorDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.
// 대화 상자 데이터입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;
	virtual void OnOk();

	// 생성된 메시지 맵 함수
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
