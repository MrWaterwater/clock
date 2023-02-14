// CRecordsDlg.cpp: 实现文件
//

#include "pch.h"
#include "frontend.h"
#include "CRecordsDlg.h"
#include "afxdialogex.h"
#include "ClockManage.h"

// CRecordsDlg 对话框

IMPLEMENT_DYNAMIC(CRecordsDlg, CDialogEx)

CRecordsDlg::CRecordsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(RECORDS_DLG, pParent)
{

}

CRecordsDlg::~CRecordsDlg()
{
}

void CRecordsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, LIST_RECORDS, m_records);
}


BEGIN_MESSAGE_MAP(CRecordsDlg, CDialogEx)
END_MESSAGE_MAP()


// CRecordsDlg 消息处理程序


BOOL CRecordsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	list<_RECORD>::iterator it;
	File file;
	list<_RECORD> records;
	file.GetRecordsFromFile(records);
	CRect rectL;
	m_records.GetWindowRect(&rectL);
	int widL = rectL.right - rectL.left;
	int nColL = widL / 4;
	m_records.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_records.SetTextBkColor(RGB(224, 238, 238));
	m_records.InsertColumn(0, _T("记录时间"), LVCFMT_LEFT, nColL);
	m_records.InsertColumn(1, _T("闹钟ID"), LVCFMT_LEFT, nColL);
	m_records.InsertColumn(2, _T("闹钟名"), LVCFMT_LEFT, nColL);
	m_records.InsertColumn(3, _T("操作"), LVCFMT_LEFT, nColL);
	
	int index = 0;
	for (it = records.begin(); it != records.end(); it++)
	{	
		CString strRecordTime, strClockID, strClockName, strOperate ,strIndex;
		CTime ctime = it->tRecordTime;
		int nClockID = it->nClockID;
		std::string clockName = it->chszClockName;
		bool bOperate = it->bOperate;
		strRecordTime = ctime.Format("%Y年%m月%d日 %X");
		strClockID.Format(_T("%d"), nClockID);
		strClockName = clockName.c_str();
		if (it->bOperate)
		{
			strOperate = _T("确认");
		}
		else
		{
			strOperate = _T("延时");
		}
		m_records.InsertItem(0, strRecordTime);
		m_records.SetItemText(index, 1, strClockID);
		m_records.SetItemText(index, 2, strClockName);
		m_records.SetItemText(index, 3, strOperate);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
