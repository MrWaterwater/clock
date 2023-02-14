#pragma once


// DeleteClockDlg 对话框

class DeleteClockDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DeleteClockDlg)

public:
	DeleteClockDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DeleteClockDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = DELETE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_clockID;
	afx_msg void OnBnClickedButton1();
};
