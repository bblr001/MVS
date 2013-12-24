#if !defined(AFX_DLGSHOWHISTORYDATA_H__F28CECE4_8896_4923_B280_3E367FFD5779__INCLUDED_)
#define AFX_DLGSHOWHISTORYDATA_H__F28CECE4_8896_4923_B280_3E367FFD5779__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgShowHistoryData.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgShowHistoryData dialog
#include "GridList.h"
#include "afxcmn.h"
#include "SqliteDB.h"
#include "DBControl.h"
#include "CppSQLite3.h"
#include "afxdtctl.h"
#include "afxwin.h"
#include "MyLabel.h"
class CDlgShowHistoryData : public CDialog
{
	// Construction
public:
	CDlgShowHistoryData(CWnd* pParent = NULL);   // standard constructor
	~CDlgShowHistoryData();
	void SetDbName(char * pcdbname,int len);
    void InitConnect();
	// Dialog Data
	//{{AFX_DATA(CDlgShowHistoryData)
	enum { IDD = IDD_DIALOG_SHOWDATA };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgShowHistoryData)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

	// Implementation
protected:
	CGridListCtrl   m_gridListVw;
	char m_dbname[256];
	CDBControl<CppSQLite3Query>* m_db;
	bool m_bIsConnect;
	UINT m_nPrevStyle;
	// Generated message map functions
	//{{AFX_MSG(CDlgShowHistoryData)
	// NOTE: the ClassWizard will add member functions here
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnQuery();
	CDateTimeCtrl m_dttmStart;
	CDateTimeCtrl m_dttmEnd;
	CDateTimeCtrl m_dttmTimeStart;
	CDateTimeCtrl m_dttmEndTime;
	CMyLabel m_lbTotalNum;
	CMyLabel m_lbFautyNum;
	CMyLabel m_lbPercent;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSHOWHISTORYDATA_H__F28CECE4_8896_4923_B280_3E367FFD5779__INCLUDED_)