#pragma once


// UpateClockDlg 对话框

class UpateClockDlg : public CDialogEx
{
	DECLARE_DYNAMIC(UpateClockDlg)

public:
	UpateClockDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~UpateClockDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = UPDATE_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUpdateClock();
	virtual BOOL OnInitDialog();
	CString m_clockName;
	CComboBox m_loopType;
	CComboBox m_min;
	CComboBox m_hour;
	CComboBox m_day;
	CComboBox m_duration;
	CComboBox m_musicType;
	int m_clockID;
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedGetinfo();
};
