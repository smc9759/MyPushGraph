
// WinMonitorDlg.cpp : 구현 파일
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

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CWinMonitorDlg 대화 상자




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


// CWinMonitorDlg 메시지 처리기

BOOL CWinMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_PushGraph.CreateFromStatic(IDC_STATICGRAPH, this);	
	m_PushGraph.ModifyStyle(0, WS_THICKFRAME);	
	
	m_PushGraph.AddLine( PUSHGRAPH_SYSTEM_LINE,  RGB(0, 255, 0));
	m_PushGraph.AddLine( PUSHGRAPH_PROCESS_LINE, RGB(255, 255, 0));

	OnOk();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWinMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	static CCpuUsage cpu, cpu2;

	int nSystem_CPU_Usage  = cpu.GetCpuUsage();
	int nProcess_CPU_Usage = cpu2.GetCpuUsage(GetCurrentProcessId());

	m_PushGraph.Push(nSystem_CPU_Usage,  PUSHGRAPH_SYSTEM_LINE);
	m_PushGraph.Push(nProcess_CPU_Usage, PUSHGRAPH_PROCESS_LINE);	
	m_PushGraph.Update();

	CDialogEx::OnTimer(nIDEvent);
}
