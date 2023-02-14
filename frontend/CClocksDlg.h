#pragma once


// CClocksDlg 对话框

class CClocksDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CClocksDlg)

public:
	CClocksDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CClocksDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = CLOCKS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListCtrl m_hourClocks;
	CListCtrl m_singleOrDayClocks;
	CListCtrl m_weekClocks;
	CListCtrl m_monthClocks;
	void ShowClocksList();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnBnClickedDelete();
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedCloseOrOpen();
	CComboBox m_combBoxRule;
	afx_msg void OnCbnSelchangeCombo1();
};
