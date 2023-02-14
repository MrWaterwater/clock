// CClocksDlg.cpp: 实现文件
//

#include "pch.h"
#include "frontend.h"
#include "CClocksDlg.h"
#include "afxdialogex.h"
#include "ClockManage.h"
#include "DeleteClockDlg.h"
#include "AddClockDlg.h"
#include "UpateClockDlg.h"
#include "OpenOrCloseClockDlg.h"
// CClocksDlg 对话框

IMPLEMENT_DYNAMIC(CClocksDlg, CDialogEx)

CClocksDlg::CClocksDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(CLOCKS_DLG, pParent)
{

}

CClocksDlg::~CClocksDlg()
{
}

void CClocksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LIST_CLOCKS, m_hourClocks);
	DDX_Control(pDX, LIST_DAY_CLOCKS, m_singleOrDayClocks);
	DDX_Control(pDX, LIST_WEEK_CLOCKS, m_weekClocks);
	DDX_Control(pDX, LIST_MONTH_CLOCKS, m_monthClocks);
	DDX_Control(pDX, IDC_COMBO1, m_combBoxRule);
}


BEGIN_MESSAGE_MAP(CClocksDlg, CDialogEx)
	ON_BN_CLICKED(BTN_ADD, &CClocksDlg::OnBnClickedAdd)
	ON_BN_CLICKED(BTN_DELETE, &CClocksDlg::OnBnClickedDelete)
	ON_BN_CLICKED(BTN_UPDATE, &CClocksDlg::OnBnClickedUpdate)
	ON_BN_CLICKED(BTN_SORT, &CClocksDlg::OnBnClickedCloseOrOpen)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CClocksDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CClocksDlg 消息处理程序


BOOL CClocksDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CClockManage& clockManage = CClockManage::GetClockManageInstance();

	m_hourClocks.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_singleOrDayClocks.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_weekClocks.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_monthClocks.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	m_hourClocks.SetTextBkColor(RGB(224, 238, 238));
	m_singleOrDayClocks.SetTextBkColor(RGB(224, 238, 238));
	m_weekClocks.SetTextBkColor(RGB(224, 238, 238));
	m_monthClocks.SetTextBkColor(RGB(224, 238, 238));

	m_hourClocks.InsertColumn(0, _T("闹钟ID"), LVCFMT_LEFT, 120);
	m_hourClocks.InsertColumn(1, _T("闹钟名"), LVCFMT_LEFT, 120);
	m_hourClocks.InsertColumn(2, _T("闹钟创建/修改时间"), LVCFMT_LEFT, 200);
	m_hourClocks.InsertColumn(3, _T("分"), LVCFMT_LEFT, 100);
	m_hourClocks.InsertColumn(4, _T("开启状态"), LVCFMT_LEFT, 100);
	m_hourClocks.InsertColumn(5, _T("闹铃类型"), LVCFMT_LEFT, 95);
	m_hourClocks.InsertColumn(6, _T("闹铃时长"), LVCFMT_LEFT, 95);

	m_singleOrDayClocks.InsertColumn(0, _T("闹钟ID"), LVCFMT_LEFT, 100);
	m_singleOrDayClocks.InsertColumn(1, _T("闹钟名"), LVCFMT_LEFT, 100);
	m_singleOrDayClocks.InsertColumn(2, _T("闹钟创建/修改时间"), LVCFMT_LEFT, 195);
	m_singleOrDayClocks.InsertColumn(3, _T("闹钟类型"), LVCFMT_LEFT, 95);
	m_singleOrDayClocks.InsertColumn(4, _T("时"), LVCFMT_LEFT, 45);
	m_singleOrDayClocks.InsertColumn(5, _T("分"), LVCFMT_LEFT, 45);
	m_singleOrDayClocks.InsertColumn(6, _T("开启状态"), LVCFMT_LEFT, 80);
	m_singleOrDayClocks.InsertColumn(7, _T("闹铃类型"), LVCFMT_LEFT, 80);
	m_singleOrDayClocks.InsertColumn(8, _T("闹铃时长"), LVCFMT_LEFT, 80);

	m_weekClocks.InsertColumn(0, _T("闹钟ID"), LVCFMT_LEFT,100);
	m_weekClocks.InsertColumn(1, _T("闹钟名"), LVCFMT_LEFT, 100);
	m_weekClocks.InsertColumn(2, _T("闹钟创建/修改时间"), LVCFMT_LEFT, 195);
	m_weekClocks.InsertColumn(3, _T("周循环日期"), LVCFMT_LEFT, 95);
	m_weekClocks.InsertColumn(4, _T("时"), LVCFMT_LEFT, 45);
	m_weekClocks.InsertColumn(5, _T("分"), LVCFMT_LEFT, 45);
	m_weekClocks.InsertColumn(6, _T("开启状态"), LVCFMT_LEFT, 80);
	m_weekClocks.InsertColumn(7, _T("闹铃类型"), LVCFMT_LEFT, 80);
	m_weekClocks.InsertColumn(8, _T("闹铃时长"), LVCFMT_LEFT, 80);

	m_monthClocks.InsertColumn(0, _T("闹钟ID"), LVCFMT_LEFT, 100);
	m_monthClocks.InsertColumn(1, _T("闹钟名"), LVCFMT_LEFT, 100);
	m_monthClocks.InsertColumn(2, _T("闹钟创建/修改时间"), LVCFMT_LEFT, 200);
	m_monthClocks.InsertColumn(3, _T("日"), LVCFMT_LEFT, 50);
	m_monthClocks.InsertColumn(4, _T("时"), LVCFMT_LEFT, 50);
	m_monthClocks.InsertColumn(5, _T("分"), LVCFMT_LEFT, 50);
	m_monthClocks.InsertColumn(6, _T("开启状态"), LVCFMT_LEFT, 90);
	m_monthClocks.InsertColumn(7, _T("闹铃类型"), LVCFMT_LEFT, 90);
	m_monthClocks.InsertColumn(8, _T("闹铃时长"), LVCFMT_LEFT, 90);

	m_combBoxRule.AddString(_T("状态"));
	m_combBoxRule.AddString(_T("ID"));
	m_combBoxRule.AddString(_T("名称"));
	m_combBoxRule.SetCurSel(0);

	ShowClocksList();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CClocksDlg::ShowClocksList()
{
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	int nIndex = m_combBoxRule.GetCurSel();
	eRULE eSortRule = byFlag;
	switch (nIndex)
	{
	case 0:
	{
		eSortRule = byFlag;
		break;
	}
	case 1:
	{
		eSortRule = byID;
		break;
	}
	case 2:
	{
		eSortRule = byName;
		break;
	}
	default:
		break;
	}
	clockManage.SetMESelectRule(eSortRule);
	clockManage.SortByRule();
	list<CClock>::iterator it;
	int index = 0;
	for (it = clockManage.GetMLstClockAll().begin(); it != clockManage.GetMLstClockAll().end(); it++)
	{
		CString strClockID, strClockName, strCreateOrChangeTime, strLoopType, strDay, strHour, strMin, strFlag, strMusicType, strDuration, strWeeks;
		CString strMusics[] = { _T("铃声一"), _T("铃声二"), _T("铃声三") };
		int nClockID = it->GetMNClockId();
		std::string clockName = it->GetMChszClockName();
		CTime cTime = it->GetMTCreateOrChangeTime();
		eLOOP_TYPE eLoopType = it->GetMELoopType();
		short sDay = it->GetMSDay();
		short sHour = it->GetMSHour();
		short sMin = it->GetMSMin();
		bool bFlag = it->GetMBFlag();
		eMUSIC_TYPE eMusicType = it->GetMEMusicType();
		short sDuration = it->GetMSDuration();
		bool* weeks = it->GetMEszWeek();

		strClockID.Format(_T("%d"), nClockID);
		strClockName = clockName.c_str();
		strCreateOrChangeTime = cTime.Format("%Y年%m月%d日 %X");
		strDay.Format(_T("%d"), sDay);
		strHour.Format(_T("%d"), sHour);
		strMin.Format(_T("%d"), sMin);
		if (bFlag)
		{
			strFlag = _T("开启");
		}
		else
		{
			strFlag = _T("关闭");
		}
		strMusicType = strMusics[eMusicType];
		strDuration.Format(_T("%d"), sDuration);
		switch (eLoopType)
		{
		case single:
		{
			strLoopType = _T("单次循环");
			m_singleOrDayClocks.InsertItem(0, strClockID);
			m_singleOrDayClocks.SetItemText(index, 1, strClockName);
			m_singleOrDayClocks.SetItemText(index, 2, strCreateOrChangeTime);
			m_singleOrDayClocks.SetItemText(index, 3, strLoopType);
			m_singleOrDayClocks.SetItemText(index, 4, strHour);
			m_singleOrDayClocks.SetItemText(index, 5, strMin);
			m_singleOrDayClocks.SetItemText(index, 6, strFlag);
			m_singleOrDayClocks.SetItemText(index, 7, strMusicType);
			m_singleOrDayClocks.SetItemText(index, 8, strDuration);
			break;
		}
		case hourCycle:
		{
			m_hourClocks.InsertItem(0, strClockID);
			m_hourClocks.SetItemText(index, 1, strClockName);
			m_hourClocks.SetItemText(index, 2, strCreateOrChangeTime);
			m_hourClocks.SetItemText(index, 3, strMin);
			m_hourClocks.SetItemText(index, 4, strFlag);
			m_hourClocks.SetItemText(index, 5, strMusicType);
			m_hourClocks.SetItemText(index, 6, strDuration);
			break;
		}
		case dayCycle:
		{
			strLoopType = _T("日循环");
			m_singleOrDayClocks.InsertItem(0, strClockID);
			m_singleOrDayClocks.SetItemText(index, 1, strClockName);
			m_singleOrDayClocks.SetItemText(index, 2, strCreateOrChangeTime);
			m_singleOrDayClocks.SetItemText(index, 3, strLoopType);
			m_singleOrDayClocks.SetItemText(index, 4, strHour);
			m_singleOrDayClocks.SetItemText(index, 5, strMin);
			m_singleOrDayClocks.SetItemText(index, 6, strFlag);
			m_singleOrDayClocks.SetItemText(index, 7, strMusicType);
			m_singleOrDayClocks.SetItemText(index, 8, strDuration);
			break;
		}
		case weekCycle:
		{
			CString strszWeeks[] = { _T("日 "), _T("一 "), _T("二 "), _T("三 "), _T("四 "), _T("五 "), _T("六 ") };
			for (int i = 0; i < 7; i++)
			{
				CString temp;
				if (weeks[i])
				{
					temp = strszWeeks[i];
					strWeeks += temp;
				}
			}
			m_weekClocks.InsertItem(0, strClockID);
			m_weekClocks.SetItemText(index, 1, strClockName);
			m_weekClocks.SetItemText(index, 2, strCreateOrChangeTime);
			m_weekClocks.SetItemText(index, 3, strWeeks);
			m_weekClocks.SetItemText(index, 4, strHour);
			m_weekClocks.SetItemText(index, 5, strMin);
			m_weekClocks.SetItemText(index, 6, strFlag);
			m_weekClocks.SetItemText(index, 7, strMusicType);
			m_weekClocks.SetItemText(index, 8, strDuration);
			break;
		}
		case monthCycle:
		{
			m_monthClocks.InsertItem(0, strClockID);
			m_monthClocks.SetItemText(index, 1, strClockName);
			m_monthClocks.SetItemText(index, 2, strCreateOrChangeTime);
			m_monthClocks.SetItemText(index, 3, strDay);
			m_monthClocks.SetItemText(index, 4, strHour);
			m_monthClocks.SetItemText(index, 5, strMin);
			m_monthClocks.SetItemText(index, 6, strFlag);
			m_monthClocks.SetItemText(index, 7, strMusicType);
			m_monthClocks.SetItemText(index, 8, strDuration);
			break;
		}
		default:
			break;
		}

	}
}



void CClocksDlg::OnBnClickedAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	AddClockDlg addDlg;
	addDlg.DoModal();
	m_hourClocks.DeleteAllItems();
	m_singleOrDayClocks.DeleteAllItems();
	m_weekClocks.DeleteAllItems();
	m_monthClocks.DeleteAllItems();
	ShowClocksList();
}


void CClocksDlg::OnBnClickedDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	DeleteClockDlg deleteDlg;
	deleteDlg.DoModal();
	m_hourClocks.DeleteAllItems();
	m_singleOrDayClocks.DeleteAllItems();
	m_weekClocks.DeleteAllItems();
	m_monthClocks.DeleteAllItems();
	ShowClocksList();

}


void CClocksDlg::OnBnClickedUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpateClockDlg updateDlg;
	updateDlg.DoModal();
	m_hourClocks.DeleteAllItems();
	m_singleOrDayClocks.DeleteAllItems();
	m_weekClocks.DeleteAllItems();
	m_monthClocks.DeleteAllItems();
	ShowClocksList();
}


void CClocksDlg::OnBnClickedCloseOrOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	OpenOrCloseClockDlg openOrCloseClock;
	openOrCloseClock.DoModal();
	m_hourClocks.DeleteAllItems();
	m_singleOrDayClocks.DeleteAllItems();
	m_weekClocks.DeleteAllItems();
	m_monthClocks.DeleteAllItems();
	ShowClocksList();
}


void CClocksDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	int nIndex = m_combBoxRule.GetCurSel();
	eRULE eSortRule = byFlag;
	switch (nIndex)
	{
	case 0:
	{
		eSortRule = byFlag;
		break;
	}
	case 1:
	{
		eSortRule = byID;
		break;
	}
	case 2:
	{
		eSortRule = byName;
		break;
	}
	default:
		break;
	}
	clockManage.SetMESelectRule(eSortRule);
	clockManage.SortByRule();
	m_hourClocks.DeleteAllItems();
	m_singleOrDayClocks.DeleteAllItems();
	m_weekClocks.DeleteAllItems();
	m_monthClocks.DeleteAllItems();
	ShowClocksList();
}
