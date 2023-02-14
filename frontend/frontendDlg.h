
// frontendDlg.h: 头文件
//

#pragma once


// CfrontendDlg 对话框
class CfrontendDlg : public CDialogEx
{
// 构造
public:
	CfrontendDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FRONTEND_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CFont cfont;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedRecords();
	afx_msg void OnBnClickedClocks();

	void ShowTime();
	CListCtrl m_triggerClocks;
	void ShowTriggerClocks();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
	int m_delayTime;
};
