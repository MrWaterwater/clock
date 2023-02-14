#pragma once


// OpenOrCloseClock 对话框

class OpenOrCloseClockDlg : public CDialogEx
{
	DECLARE_DYNAMIC(OpenOrCloseClockDlg)

public:
	OpenOrCloseClockDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~OpenOrCloseClockDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = CLOCK_OPEN_CLOSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	int m_clockID;
};
