#pragma once


// CModalDlg 对话框

class CModalDlg : public CDialog
{
	DECLARE_DYNAMIC(CModalDlg)

public:
	CModalDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CModalDlg();

// 对话框数据
	enum { IDD = IDD_DialogCener };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCenterhal();
	void CenterSelectValue(int* CentSel);
private:
	int* sel;
public:
	afx_msg void OnBnClickedCenterc();
};
