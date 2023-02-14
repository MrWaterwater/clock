// OpenOrCloseClock.cpp: 实现文件
//

#include "pch.h"
#include "frontend.h"
#include "OpenOrCloseClockDlg.h"
#include "afxdialogex.h"
#include "ClockManage.h"


// OpenOrCloseClock 对话框

IMPLEMENT_DYNAMIC(OpenOrCloseClockDlg, CDialogEx)

OpenOrCloseClockDlg::OpenOrCloseClockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(CLOCK_OPEN_CLOSE, pParent)
	, m_clockID(0)
{

}

OpenOrCloseClockDlg::~OpenOrCloseClockDlg()
{
}

void OpenOrCloseClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_clockID);
}


BEGIN_MESSAGE_MAP(OpenOrCloseClockDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &OpenOrCloseClockDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &OpenOrCloseClockDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// OpenOrCloseClock 消息处理程序


void OpenOrCloseClockDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	
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
		MessageBox(_T("闹钟正在触发禁止关闭！"), _T("关闭失败"), MB_ICONEXCLAMATION);
	}
	else
	{
		int flag2 = clockManage.CloseClock(m_clockID);
		if (flag2 == 1)
		{
			MessageBox(_T("关闭成功！"), _T("关闭成功"));
		}
		else
		{
			MessageBox(_T("关闭失败！"), _T("关闭失败"), MB_ICONEXCLAMATION);
		}
	}
}


void OpenOrCloseClockDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CClockManage& clockManage = CClockManage::GetClockManageInstance();
	int flag = clockManage.OpenClock(m_clockID);
	if (flag == 1)
	{
		MessageBox(_T("开启成功！"), _T("开启成功"));
	}
	else
	{
		MessageBox(_T("开启失败！"), _T("开启失败"), MB_ICONEXCLAMATION);
	}
}
