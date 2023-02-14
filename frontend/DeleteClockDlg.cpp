// DeleteClockDlg.cpp: 实现文件
//

#include "pch.h"
#include "frontend.h"
#include "DeleteClockDlg.h"
#include "afxdialogex.h"
#include "ClockManage.h"

// DeleteClockDlg 对话框

IMPLEMENT_DYNAMIC(DeleteClockDlg, CDialogEx)

DeleteClockDlg::DeleteClockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DELETE_DLG, pParent)
	, m_clockID(0)
{

}

DeleteClockDlg::~DeleteClockDlg()
{
}

void DeleteClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, CLOCKID, m_clockID);
}


BEGIN_MESSAGE_MAP(DeleteClockDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &DeleteClockDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// DeleteClockDlg 消息处理程序


void DeleteClockDlg::OnBnClickedButton1()
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
		MessageBox(_T("闹钟正在触发禁止删除！"), _T("删除失败"), MB_ICONEXCLAMATION);
		EndDialog(0);
	}
	else
	{
		int flag2 = clockManage.DeleteClock(m_clockID);
		if (flag2 == 1)
		{
			MessageBox(_T("删除成功！"), _T("删除成功"));
			EndDialog(0);
		}
		else
		{
			MessageBox(_T("删除失败！"), _T("删除失败"), MB_ICONEXCLAMATION);
			EndDialog(0);
		}
	}
}
