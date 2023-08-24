
// WinMonitorDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "WinMonitor.h"
#include "WinMonitorDlg.h"
#include "afxdialogex.h"
#include "CpuUsage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PUSHGRAPH_SYSTEM_LINE    0
#define PUSHGRAPH_PROCESS_LINE   1

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWinMonitorDlg ��ȭ ����




CWinMonitorDlg::CWinMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWinMonitorDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CC2DPushGraphDlg)
	m_nGridSize = 15;
	m_bShowGrid = TRUE;
	m_bShowLabels = TRUE;
	m_sInterval = 5;
	m_nWaitTime = 250;
	m_strMaxLabel = _T("100%");
	m_nMaxPeek = 100;
	m_strMinLabel = _T("0%");
	m_nMinPeek = 0;
	m_bLine0AsBar = FALSE;
	m_bLine1AsBar = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWinMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, &CWinMonitorDlg::OnOk)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CWinMonitorDlg �޽��� ó����

BOOL CWinMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_PushGraph.CreateFromStatic(IDC_STATICGRAPH, this);	
	m_PushGraph.ModifyStyle(0, WS_THICKFRAME);	
	
	m_PushGraph.AddLine( PUSHGRAPH_SYSTEM_LINE,  RGB(0, 255, 0));
	m_PushGraph.AddLine( PUSHGRAPH_PROCESS_LINE, RGB(255, 255, 0));

	OnOk();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CWinMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CWinMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CWinMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinMonitorDlg::OnOk()
{
	UpdateData();

	KillTimer(0);
	SetTimer(0, m_nWaitTime, NULL);

	m_PushGraph.ShowGrid( m_bShowGrid ? true : false );
	m_PushGraph.ShowLabels( m_bShowLabels ? true : false  );

	m_PushGraph.ShowAsBar(0, m_bLine0AsBar ? true : false );
	m_PushGraph.ShowAsBar(1, m_bLine1AsBar ? true : false );

	m_PushGraph.SetInterval( m_sInterval );
	m_PushGraph.SetGridSize( (USHORT)m_nGridSize );

	m_PushGraph.SetLabelForMax( m_strMaxLabel );
	m_PushGraph.SetLabelForMin( m_strMinLabel );

	m_PushGraph.SetPeekRange( m_nMinPeek, m_nMaxPeek );	
	
	
	m_PushGraph.RedrawWindow();
}


void CWinMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	static CCpuUsage cpu, cpu2;

	int nSystem_CPU_Usage  = cpu.GetCpuUsage();
	int nProcess_CPU_Usage = cpu2.GetCpuUsage(GetCurrentProcessId());

	m_PushGraph.Push(nSystem_CPU_Usage,  PUSHGRAPH_SYSTEM_LINE);
	m_PushGraph.Push(nProcess_CPU_Usage, PUSHGRAPH_PROCESS_LINE);	
	m_PushGraph.Update();

	CDialogEx::OnTimer(nIDEvent);
}
