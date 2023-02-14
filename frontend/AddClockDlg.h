#pragma once


// AddClockDlg 对话框

class AddClockDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddClockDlg)

public:
	AddClockDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddClockDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = ADDCLOCKS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_clockName;
	CComboBox m_loopType;
	CComboBox m_day;
	CComboBox m_hour;
	CComboBox m_min;
	CComboBox m_musicType;
	CComboBox m_duration;
	afx_msg void OnBnClickedAddClock();
	afx_msg void OnCbnSelchangeCombo1();
};
