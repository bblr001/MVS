#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include <string>
#include "ProgramSelectorDlg.h"
#include "TlsFileParser.h"
#include "cpp\HalconCpp.h"

using namespace std;

class CMConfigCenter;

// CProgramSelectorDlg 对话框

class CProgramSelectorDlg : public CDialog
{
	DECLARE_DYNAMIC(CProgramSelectorDlg)

public:
	CProgramSelectorDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProgramSelectorDlg();
	enum { IDD = IDD_DIALOG_OPENPRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();

	void InitProgramList();
	
	DECLARE_MESSAGE_MAP()
	Hlong m_HWindowID;
public:
	CMFCListCtrl m_ProgramList;
	CStatic m_PicLog;
	CButton m_bOK;

private:
	wstring m_programName;

	afx_msg void OnNMClickListProgram(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
