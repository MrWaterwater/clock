#pragma once


// CRecordsDlg 对话框

class CRecordsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordsDlg)

public:
	CRecordsDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRecordsDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = RECORDS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_records;
};
