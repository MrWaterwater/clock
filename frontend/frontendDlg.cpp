
// frontendDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "frontend.h"
#include "frontendDlg.h"
#include "afxdialogex.h"
#include "ClockManage.h"
#include "CClocksDlg.h"
#include "CRecordsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CfrontendDlg 对话框



CfrontendDlg::CfrontendDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FRONTEND_DIALOG, pParent)
	, m_delayTime(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CfrontendDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LIST_TRIGGER_CLOCKS, m_triggerClocks);
	DDX_Text(pDX, IDC_EDIT2, m_delayTime);
}

BEGIN_MESSAGE_MAP(CfrontendDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(BTN_RECORDS, &CfrontendDlg::OnBnClickedRecords)
	ON_BN_CLICKED(BTN_CLOCKS, &CfrontendDlg::OnBnClickedClocks)
	ON_BN_CLICKED(IDC_BUTTON4, &CfrontendDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CfrontendDlg::OnBnClickedButton3)
END_MESSAGE_MAP()

// CfrontendDlg 消息处理程序
BOOL CfrontendDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作+		this	0x0000003c28cff610 {hWnd=0x000000000027080c {unused=??? }}	CfrontendDlg *

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	cfont.CreatePointFont(200, _T("黑体"), NULL);
	GetDlgItem(STATIC_HOUR)->SetFont(&cfont);
	GetDlgItem(STATIC_MIN)->SetFont(&cfont);
	GetDlgItem(IDC_STATIC)->SetFont(&cfont);
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	clockManage.start();
	clockManage.UpdateMPqClockWait();
	
	ShowTime();

	m_triggerClocks.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_triggerClocks.SetTextBkColor(RGB(224, 238, 238));
	m_triggerClocks.InsertColumn(0, _T("闹钟ID"), LVCFMT_LEFT, 100);
	m_triggerClocks.InsertColumn(1, _T("闹钟名"), LVCFMT_LEFT, 100);
	m_triggerClocks.InsertColumn(2, _T("闹钟类型"), LVCFMT_LEFT, 80);
	m_triggerClocks.InsertColumn(3, _T("闹铃类型"), LVCFMT_LEFT, 80);
	m_triggerClocks.InsertColumn(4, _T("闹铃时长"), LVCFMT_LEFT, 95);
	SetTimer(0, 1000, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CfrontendDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CfrontendDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CfrontendDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CfrontendDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	switch (nIDEvent)
	{
	case 0:
	{
		m_triggerClocks.DeleteAllItems();

		clockManage.GetMNLimitNum();

		//显示时间
		ShowTime();

		/*记录日志，维护延时队列*/
		clockManage.Record();

		/*响铃控制*/
		clockManage.ClockRing();

		/*触发列表显示*/
		ShowTriggerClocks();

		//HANDLE hWnd = ::FindWindowEx(NULL,NULL,NULL,"");

		break;
	}
	default:
	{
		break;
	}
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CfrontendDlg::OnBnClickedRecords()
{
	// TODO: 在此添加控件通知处理程序代码
	CRecordsDlg recordsDlg;
	recordsDlg.DoModal();
}


void CfrontendDlg::OnBnClickedClocks()
{
	// TODO: 在此添加控件通知处理程序代码
	CClocksDlg clocksDlg;
	clocksDlg.DoModal();
}

void CfrontendDlg::ShowTime()
{
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	clockManage.GetNowTime();
	CString strTime, strWeek, strHour, strMin;
	CString strWeeks[] = { _T("星期日"), _T("星期一"), _T("星期二"), _T("星期三"), _T("星期四"), _T("星期五"), _T("星期六") };
	CTime cTime;
	cTime = clockManage.m_tCurrentTime;
	strTime = cTime.Format("%Y年%m月%d日");
	strWeek = strWeeks[cTime.GetDayOfWeek() - 1];
	strHour = cTime.Format("%H");
	strMin = cTime.Format("%M");
	if (clockManage.m_tCurrentTime % 2 == 0) {
		GetDlgItem(IDC_STATIC)->ShowWindow(true);
	}
	else {
		GetDlgItem(IDC_STATIC)->ShowWindow(false);
	}
	SetDlgItemText(STATIC_TIME, strTime);
	SetDlgItemText(STATIC_WEEK, strWeek);
	SetDlgItemText(STATIC_HOUR, strHour);
	SetDlgItemText(STATIC_MIN, strMin);

	if (clockManage.GetMNLimitNum() == 0)
	{
		GetDlgItem(IDC_PICTURE1)->ShowWindow(true);
		GetDlgItem(IDC_PICTURE3)->ShowWindow(false);
	}
	else
	{
		GetDlgItem(IDC_PICTURE1)->ShowWindow(false);
		GetDlgItem(IDC_PICTURE3)->ShowWindow(true);
	}
	if (!clockManage.GetMLstClockTrigger().empty())
	{
		GetDlgItem(IDC_EDIT2)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(true);
		GetDlgItem(IDC_BUTTON4)->ShowWindow(true);
	}
	else
	{
		GetDlgItem(IDC_EDIT2)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(false);
		GetDlgItem(IDC_BUTTON4)->ShowWindow(false);
	}
}

void CfrontendDlg::ShowTriggerClocks()
{
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	if (!clockManage.GetMLstClockTrigger().empty()) {
		CString strClockID, strClockName, strLoopType, strMusicType, strDuration;
		int nClockID = clockManage.GetMLstClockTrigger().back().GetMSrtClock().GetMNClockId();
		std::string clockName = clockManage.GetMLstClockTrigger().back().GetMSrtClock().GetMChszClockName();
		eLOOP_TYPE eLoopType = clockManage.GetMLstClockTrigger().back().GetMSrtClock().GetMELoopType();
		eMUSIC_TYPE eMusicType = clockManage.GetMLstClockTrigger().back().GetMSrtClock().GetMEMusicType();
		short sDuration = clockManage.GetMLstClockTrigger().back().GetMSrtClock().GetMSDuration();
		strClockID.Format(_T("%d"), nClockID);
		strClockName = clockName.c_str();
		switch (eLoopType)
		{
		case single:
		{
			strLoopType = _T("单次循环");
			break;
		}
		case hourCycle:
		{
			strLoopType = _T("小时循环");
			break;
		}
		case dayCycle:
		{
			strLoopType = _T("日循环");
			break;
		}
		case weekCycle:
		{
			strLoopType = _T("周循环");
			break;
		}
		case monthCycle:
		{
			strLoopType = _T("月循环");
			break;
		}
		default:
			break;
		}
		switch (eMusicType)
		{
		case dida:
		{
			strMusicType = _T("铃声一");
			break;
		}
		case kuaimen:
		{
			strMusicType = _T("铃声二");
			break;
		}
		case zhuanhuan:
		{
			strMusicType = _T("铃声三");
			break;
		}
		default:
			break;
		}
		strDuration.Format(_T("%d"), sDuration);
		m_triggerClocks.InsertItem(0, strClockID);
		m_triggerClocks.SetItemText(0, 1, strClockName);
		m_triggerClocks.SetItemText(0, 2, strLoopType);
		m_triggerClocks.SetItemText(0, 3, strMusicType);
		m_triggerClocks.SetItemText(0, 4, strDuration);

		if (clockManage.m_tCurrentTime % 2 == 0)
		{
			GetDlgItem(IDC_PICTURE3)->ShowWindow(true);
		}
		else
		{
			GetDlgItem(IDC_PICTURE3)->ShowWindow(false);
		}
		m_delayTime = clockManage.GetMLstClockTrigger().back().GetMSDelay();
		if (clockManage.m_bFlagShow)
		{
			UpdateData(false);
			clockManage.m_bFlagShow = false;
		}
	}
}


void CfrontendDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	clockManage.m_bFlagShow = true;
	int flag = clockManage.UserConfirm();
	if (flag == 1)
	{
		MessageBox(_T("确认成功！"), _T("确认成功"));
	}
	else
	{
		MessageBox(_T("确认失败！"), _T("确认失败"), MB_ICONEXCLAMATION);
	}
}


void CfrontendDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	clockManage.m_bFlagShow = true;
	if (m_delayTime < 10 || m_delayTime >= 60)
	{
		MessageBox(_T("时间不合法！"), _T("时间不合法"), MB_ICONEXCLAMATION);
	}
	else 
	{
		int flag = clockManage.UserDelay(m_delayTime);
		if (flag == 1)
		{
			MessageBox(_T("延时成功！"), _T("延时成功"));
		}
		else if (flag == 2) 
		{
			MessageBox(_T("延时次数到达上限，自动确认！"), _T("延时失败"), MB_ICONEXCLAMATION);
		}
		else
		{
			MessageBox(_T("延时失败！"), _T("延时失败"), MB_ICONEXCLAMATION);
		}
	}
}
