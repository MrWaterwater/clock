// UpateClockDlg.cpp: 实现文件
//

#include "pch.h"
#include "frontend.h"
#include "UpateClockDlg.h"
#include "afxdialogex.h"
#include "ClockManage.h"


// UpateClockDlg 对话框

IMPLEMENT_DYNAMIC(UpateClockDlg, CDialogEx)

UpateClockDlg::UpateClockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(UPDATE_DLG, pParent)
	, m_clockName(_T(""))
	, m_clockID(0)
{

}

UpateClockDlg::~UpateClockDlg()
{
}

void UpateClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_clockName);
	DDX_Control(pDX, IDC_COMBO1, m_loopType);
	DDX_Control(pDX, IDC_COMBO4, m_min);
	DDX_Control(pDX, COMBOX_HOUR, m_hour);
	DDX_Control(pDX, COMBOX_DAY, m_day);
	DDX_Control(pDX, IDC_COMBO5, m_duration);
	DDX_Control(pDX, IDC_COMBO6, m_musicType);
	DDX_Text(pDX, IDC_EDIT3, m_clockID);
}


BEGIN_MESSAGE_MAP(UpateClockDlg, CDialogEx)
	ON_BN_CLICKED(BTN_UPDATE_CLOCK, &UpateClockDlg::OnBnClickedUpdateClock)
	ON_CBN_SELCHANGE(IDC_COMBO1, &UpateClockDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(BTN_GETINFO, &UpateClockDlg::OnBnClickedGetinfo)
END_MESSAGE_MAP()


// UpateClockDlg 消息处理程序


void UpateClockDlg::OnBnClickedUpdateClock()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	string tempName;
	eLOOP_TYPE eloopType;
	short day, hour, min, duration;
	eMUSIC_TYPE eMusicType;
	bool weeks[7] = { 0,0,0,0,0,0,0 };

	tempName = CT2A(m_clockName.GetBuffer());
	char* clockName = (char*)tempName.data();
	day = m_day.GetCurSel() + 1;
	hour = m_hour.GetCurSel();
	min = m_min.GetCurSel();
	duration = m_duration.GetCurSel() + 1;
	int loopIndex = m_loopType.GetCurSel();
	int musicIndex = m_musicType.GetCurSel();
	switch (loopIndex)
	{
	case 0:
	{
		eloopType = single;
		break;
	}
	case 1:
	{
		eloopType = hourCycle;
		break;
	}
	case 2:
	{
		eloopType = dayCycle;
		break;
	}
	case 3:
	{
		eloopType = weekCycle;
		break;
	}
	case 4:
	{
		eloopType = monthCycle;
		break;

	}
	default:
		break;
	}
	switch (musicIndex)
	{
	case 0:
	{
		eMusicType = dida;
		break;
	}
	case 1:
	{
		eMusicType = kuaimen;
		break;
	}
	case 2:
	{
		eMusicType = zhuanhuan;
		break;
	}
	default:
		break;
	}
	weeks[0] = ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck();
	weeks[1] = ((CButton*)GetDlgItem(IDC_CHECK2))->GetCheck();
	weeks[2] = ((CButton*)GetDlgItem(IDC_CHECK3))->GetCheck();
	weeks[3] = ((CButton*)GetDlgItem(IDC_CHECK4))->GetCheck();
	weeks[4] = ((CButton*)GetDlgItem(IDC_CHECK5))->GetCheck();
	weeks[5] = ((CButton*)GetDlgItem(IDC_CHECK6))->GetCheck();
	weeks[6] = ((CButton*)GetDlgItem(IDC_CHECK7))->GetCheck();
	list<CClockOfToday>::iterator it;
	int flag1 = 0;
	for (it = clockManage.GetMLstClockTrigger().begin(); it != clockManage.GetMLstClockTrigger().end(); it++)
	{
		if (m_clockID == it->GetMSrtClock().GetMNClockId())
		{
			flag1 = 1;
			break;
		}
	}
	if (flag1 == 1)
	{
		MessageBox(_T("闹钟正在触发禁止更新！"), _T("更新失败"), MB_ICONEXCLAMATION);
		EndDialog(0);
	}
	else
	{
		if (tempName.length() <= 18)
		{
			int flag2 = clockManage.UpdateClock(m_clockID, clockName, eloopType, min, hour, day, weeks, duration, eMusicType);
			if (flag2 == 1)
			{
				MessageBox(_T("更新成功！"), _T("更新成功"));
				EndDialog(0);
			}
			else
			{
				MessageBox(_T("更新失败！"), _T("更新失败"), MB_ICONEXCLAMATION);
				EndDialog(0);
			}
		}
		else
		{
			MessageBox(_T("闹钟名太长！"), _T("更新失败"), MB_ICONEXCLAMATION);
		}
	}
}


BOOL UpateClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	GetDlgItem(STATIC_HOUR)->ShowWindow(true);
	GetDlgItem(STATIC_DAY)->ShowWindow(false);
	GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
	GetDlgItem(COMBOX_DAY)->ShowWindow(false);

	GetDlgItem(STATIC_WEEK)->ShowWindow(false);
	GetDlgItem(CHECK_0)->ShowWindow(false);
	GetDlgItem(CHECK_1)->ShowWindow(false);
	GetDlgItem(CHECK_2)->ShowWindow(false);
	GetDlgItem(CHECK_3)->ShowWindow(false);
	GetDlgItem(CHECK_4)->ShowWindow(false);
	GetDlgItem(CHECK_5)->ShowWindow(false);
	GetDlgItem(CHECK_6)->ShowWindow(false);

	m_loopType.AddString(_T("单次循环"));
	m_loopType.AddString(_T("小时循环"));
	m_loopType.AddString(_T("天循环"));
	m_loopType.AddString(_T("周循环"));
	m_loopType.AddString(_T("月循环"));
	m_loopType.SetCurSel(0);

	for (int i = 1; i <= 31; i++)
	{
		CString temp;
		temp.Format(_T("%d"), i);
		m_day.AddString(temp);
	}
	m_day.SetCurSel(0);
	for (int i = 0; i < 24; i++)
	{
		CString temp;
		temp.Format(_T("%d"), i);
		m_hour.AddString(temp);
	}
	m_hour.SetCurSel(0);
	for (int i = 0; i < 60; i++)
	{
		CString temp;
		temp.Format(_T("%d"), i);
		m_min.AddString(temp);
	}
	m_min.SetCurSel(0);
	m_musicType.AddString(_T("铃声一"));
	m_musicType.AddString(_T("铃声二"));
	m_musicType.AddString(_T("铃声三"));
	m_musicType.SetCurSel(0);

	for (int i = 1; i <= 5; i++)
	{
		CString temp;
		temp.Format(_T("%d"), i);
		m_duration.AddString(temp);
	}
	m_duration.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void UpateClockDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	int loopIndex = m_loopType.GetCurSel();
	switch (loopIndex)
	{
	case 0:
	{
		GetDlgItem(STATIC_HOUR)->ShowWindow(true);
		GetDlgItem(STATIC_DAY)->ShowWindow(false);
		GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
		GetDlgItem(COMBOX_DAY)->ShowWindow(false);

		GetDlgItem(STATIC_WEEK)->ShowWindow(false);
		GetDlgItem(CHECK_0)->ShowWindow(false);
		GetDlgItem(CHECK_1)->ShowWindow(false);
		GetDlgItem(CHECK_2)->ShowWindow(false);
		GetDlgItem(CHECK_3)->ShowWindow(false);
		GetDlgItem(CHECK_4)->ShowWindow(false);
		GetDlgItem(CHECK_5)->ShowWindow(false);
		GetDlgItem(CHECK_6)->ShowWindow(false);
		break;
	}
	case 1:
	{
		GetDlgItem(STATIC_DAY)->ShowWindow(false);
		GetDlgItem(COMBOX_DAY)->ShowWindow(false);
		GetDlgItem(STATIC_HOUR)->ShowWindow(false);
		GetDlgItem(COMBOX_HOUR)->ShowWindow(false);
		GetDlgItem(STATIC_WEEK)->ShowWindow(false);
		GetDlgItem(CHECK_0)->ShowWindow(false);
		GetDlgItem(CHECK_1)->ShowWindow(false);
		GetDlgItem(CHECK_2)->ShowWindow(false);
		GetDlgItem(CHECK_3)->ShowWindow(false);
		GetDlgItem(CHECK_4)->ShowWindow(false);
		GetDlgItem(CHECK_5)->ShowWindow(false);
		GetDlgItem(CHECK_6)->ShowWindow(false);
		break;
	}
	case 2:
	{
		GetDlgItem(STATIC_HOUR)->ShowWindow(true);
		GetDlgItem(STATIC_DAY)->ShowWindow(false);
		GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
		GetDlgItem(COMBOX_DAY)->ShowWindow(false);

		GetDlgItem(STATIC_WEEK)->ShowWindow(false);
		GetDlgItem(CHECK_0)->ShowWindow(false);
		GetDlgItem(CHECK_1)->ShowWindow(false);
		GetDlgItem(CHECK_2)->ShowWindow(false);
		GetDlgItem(CHECK_3)->ShowWindow(false);
		GetDlgItem(CHECK_4)->ShowWindow(false);
		GetDlgItem(CHECK_5)->ShowWindow(false);
		GetDlgItem(CHECK_6)->ShowWindow(false);
		break;
	}
	case 3:
	{
		GetDlgItem(STATIC_HOUR)->ShowWindow(true);
		GetDlgItem(STATIC_DAY)->ShowWindow(false);
		GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
		GetDlgItem(COMBOX_DAY)->ShowWindow(false);
		GetDlgItem(STATIC_WEEK)->ShowWindow(true);
		GetDlgItem(CHECK_0)->ShowWindow(true);
		GetDlgItem(CHECK_1)->ShowWindow(true);
		GetDlgItem(CHECK_2)->ShowWindow(true);
		GetDlgItem(CHECK_3)->ShowWindow(true);
		GetDlgItem(CHECK_4)->ShowWindow(true);
		GetDlgItem(CHECK_5)->ShowWindow(true);
		GetDlgItem(CHECK_6)->ShowWindow(true);
		break;
	}
	case 4:
	{
		GetDlgItem(STATIC_HOUR)->ShowWindow(true);
		GetDlgItem(STATIC_DAY)->ShowWindow(true);
		GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
		GetDlgItem(COMBOX_DAY)->ShowWindow(true);

		GetDlgItem(STATIC_WEEK)->ShowWindow(false);
		GetDlgItem(CHECK_0)->ShowWindow(false);
		GetDlgItem(CHECK_1)->ShowWindow(false);
		GetDlgItem(CHECK_2)->ShowWindow(false);
		GetDlgItem(CHECK_3)->ShowWindow(false);
		GetDlgItem(CHECK_4)->ShowWindow(false);
		GetDlgItem(CHECK_5)->ShowWindow(false);
		GetDlgItem(CHECK_6)->ShowWindow(false);
		break;
	}
	default:
		break;
	}
}


void UpateClockDlg::OnBnClickedGetinfo()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	int flag1 = clockManage.ClockExit(m_clockID);
	if (flag1 == 1)
	{
		CClock clock = clockManage.GetClockByID(m_clockID);
		m_clockName = clock.GetMChszClockName();
		eLOOP_TYPE eLoopType = clock.GetMELoopType();
		eMUSIC_TYPE eMusicType = clock.GetMEMusicType();
		short sMin = clock.GetMSMin();
		short sHour = clock.GetMSHour();
		short sDay = clock.GetMSDay();
		short sDuration = clock.GetMSDuration();
		bool* bWeek = clock.GetMEszWeek();

		switch (eLoopType)
		{
		case single:
		{
			m_loopType.SetCurSel(0);
			break;
		}
		case hourCycle:
		{
			m_loopType.SetCurSel(1);
			break;
		}
		case dayCycle:
		{
			m_loopType.SetCurSel(2);
			break;
		}
		case weekCycle:
		{
			m_loopType.SetCurSel(3);
			break;
		}
		case monthCycle:
		{
			m_loopType.SetCurSel(4);
			break;
		}
		default: 
		{
			break;
		}
		}
		int loopIndex = m_loopType.GetCurSel();
		switch (loopIndex)
		{
		case 0:
		{
			GetDlgItem(STATIC_HOUR)->ShowWindow(true);
			GetDlgItem(STATIC_DAY)->ShowWindow(false);
			GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
			GetDlgItem(COMBOX_DAY)->ShowWindow(false);

			GetDlgItem(STATIC_WEEK)->ShowWindow(false);
			GetDlgItem(CHECK_0)->ShowWindow(false);
			GetDlgItem(CHECK_1)->ShowWindow(false);
			GetDlgItem(CHECK_2)->ShowWindow(false);
			GetDlgItem(CHECK_3)->ShowWindow(false);
			GetDlgItem(CHECK_4)->ShowWindow(false);
			GetDlgItem(CHECK_5)->ShowWindow(false);
			GetDlgItem(CHECK_6)->ShowWindow(false);
			break;
		}
		case 1:
		{
			GetDlgItem(STATIC_HOUR)->ShowWindow(false);
			GetDlgItem(COMBOX_HOUR)->ShowWindow(false);
			GetDlgItem(STATIC_WEEK)->ShowWindow(false);
			GetDlgItem(CHECK_0)->ShowWindow(false);
			GetDlgItem(CHECK_1)->ShowWindow(false);
			GetDlgItem(CHECK_2)->ShowWindow(false);
			GetDlgItem(CHECK_3)->ShowWindow(false);
			GetDlgItem(CHECK_4)->ShowWindow(false);
			GetDlgItem(CHECK_5)->ShowWindow(false);
			GetDlgItem(CHECK_6)->ShowWindow(false);
			break;
		}
		case 2:
		{
			GetDlgItem(STATIC_HOUR)->ShowWindow(true);
			GetDlgItem(STATIC_DAY)->ShowWindow(false);
			GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
			GetDlgItem(COMBOX_DAY)->ShowWindow(false);

			GetDlgItem(STATIC_WEEK)->ShowWindow(false);
			GetDlgItem(CHECK_0)->ShowWindow(false);
			GetDlgItem(CHECK_1)->ShowWindow(false);
			GetDlgItem(CHECK_2)->ShowWindow(false);
			GetDlgItem(CHECK_3)->ShowWindow(false);
			GetDlgItem(CHECK_4)->ShowWindow(false);
			GetDlgItem(CHECK_5)->ShowWindow(false);
			GetDlgItem(CHECK_6)->ShowWindow(false);
			break;
		}
		case 3:
		{
			GetDlgItem(STATIC_HOUR)->ShowWindow(true);
			GetDlgItem(STATIC_DAY)->ShowWindow(false);
			GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
			GetDlgItem(COMBOX_DAY)->ShowWindow(false);
			GetDlgItem(STATIC_WEEK)->ShowWindow(true);
			GetDlgItem(CHECK_0)->ShowWindow(true);
			GetDlgItem(CHECK_1)->ShowWindow(true);
			GetDlgItem(CHECK_2)->ShowWindow(true);
			GetDlgItem(CHECK_3)->ShowWindow(true);
			GetDlgItem(CHECK_4)->ShowWindow(true);
			GetDlgItem(CHECK_5)->ShowWindow(true);
			GetDlgItem(CHECK_6)->ShowWindow(true);
			break;
		}
		case 4:
		{
			GetDlgItem(STATIC_HOUR)->ShowWindow(true);
			GetDlgItem(STATIC_DAY)->ShowWindow(true);
			GetDlgItem(COMBOX_HOUR)->ShowWindow(true);
			GetDlgItem(COMBOX_DAY)->ShowWindow(true);

			GetDlgItem(STATIC_WEEK)->ShowWindow(false);
			GetDlgItem(CHECK_0)->ShowWindow(false);
			GetDlgItem(CHECK_1)->ShowWindow(false);
			GetDlgItem(CHECK_2)->ShowWindow(false);
			GetDlgItem(CHECK_3)->ShowWindow(false);
			GetDlgItem(CHECK_4)->ShowWindow(false);
			GetDlgItem(CHECK_5)->ShowWindow(false);
			GetDlgItem(CHECK_6)->ShowWindow(false);
			break;
		}
		default:
			break;
		}
		switch (eMusicType)
		{
		case dida:
		{
			m_musicType.SetCurSel(0);
			break;
		}
		case kuaimen:
		{
			m_musicType.SetCurSel(1);
			break;
		}
		case zhuanhuan:
		{
			m_musicType.SetCurSel(2);
			break;
		}
		default: 
		{
			break;
		}
		}
		m_min.SetCurSel(sMin);
		m_hour.SetCurSel(sHour);
		m_day.SetCurSel(sDay-1);
		if (bWeek[0])
		{
			((CButton*)GetDlgItem(IDC_CHECK1))->SetCheck(true);
		}
		if (bWeek[1])
		{
			((CButton*)GetDlgItem(IDC_CHECK2))->SetCheck(true);
		}
		if (bWeek[2])
		{
			((CButton*)GetDlgItem(IDC_CHECK3))->SetCheck(true);
		}
		if (bWeek[3])
		{
			((CButton*)GetDlgItem(IDC_CHECK4))->SetCheck(true);
		}
		if (bWeek[4])
		{
			((CButton*)GetDlgItem(IDC_CHECK5))->SetCheck(true);
		}
		if (bWeek[5])
		{
			((CButton*)GetDlgItem(IDC_CHECK6))->SetCheck(true);
		}
		if (bWeek[6])
		{
			((CButton*)GetDlgItem(IDC_CHECK7))->SetCheck(true);
		}
		UpdateData(false);
	}
	else
	{
		MessageBox(_T("获取失败，闹钟不存在！"), _T("获取失败"), MB_ICONEXCLAMATION);
	}
}
