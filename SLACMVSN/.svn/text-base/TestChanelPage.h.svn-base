#pragma once
// CTestChanelPage 对话框
#include "MyLabel.h"
#include "MyButton.h"
#include "afxwin.h"
#include <stdio.h>
#include <string>
#include "cpp\HalconCpp.h"
#include "..\slacmvsn\Resource.h"
#include "TypeCent.h"
#include "TestChanelPage.h"
using namespace std;
using namespace Halcon;

class CTestChanelPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTestChanelPage)

public:
	CTestChanelPage(wstring szStationID);
	virtual ~CTestChanelPage();
    void SetDBName(char * pcdbname,int len);
// 对话框数据
	enum { IDD = IDD_PROPPAGE_CHANGEL };
protected:
	 CRect   m_rcBtnMyKV;
	 CMyLabel m_lbStatus;
	 CMyLabel m_lbInfoMsg;
	 CMyLabel m_lbPragramName;

public:
	 CMyLabel m_lbTotalNum;
	 CMyLabel m_lbFautyNum;
	 CMyLabel m_lbOkNum;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
    virtual BOOL OnInitDialog();
	//{{AFX_MSG(CTestChanelPage)
	afx_msg int OnCreate(LPCREATESTRUCT);
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC,CWnd* pWnd,UINT nCtlColor);


	//}}
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOnline();
	afx_msg void OnBnClickedBtnOffline();
	afx_msg void OnBnClickedBtnNopic();
	afx_msg void OnBnClickedBtnOkpic();
	afx_msg void OnBnClickedBtnQuery();
	afx_msg void OnBnClickedBtnWarning();
	BOOL Init();

	void InsertRecord(CString test,CString subTest,CString IsTest);
	void UpdateRecord(int Item,CString connect);
	void UpdateTotalRecord(CString ReciveCount,CString TotalFailCount);
	void InitRecordLog();

	CMyLabel m_lbNUM_01;
	CMyLabel m_lbNUM_02;
	CMyLabel m_lbNUM_03;
    CBitmapButton m_btnHistoryData;
	CBitmapButton m_btnLoad;
	CBitmapButton m_btnOffLine;
	CBitmapButton m_btnOnLine;

	CBitmapButton m_btnOkPic;
	CBitmapButton m_btnNoPic;
	CBitmapButton m_btnOpen;

	CBitmapButton m_btnWarning;
	afx_msg void OnCbnSelchangeCombo2();
	CComboBox m_cbxProName;
	CListCtrl m_ltcTestItem;

public:
	void SetMonitorImage(Hobject * image,bool st);
	void SetState(eMTI_GUI_STATE state);

	VOID SetProgramName(const wchar_t * strName,COLORREF GRDColor=RGB(180,180,180),COLORREF TxtColor=RGB(0,0,0));
	VOID SetMsg(const wchar_t * strMsg,COLORREF TxtColor=RGB(0,0,255));

private:
	wstring m_StationID;
	Hlong m_ErrorDisplayWinID_Halcon;
	Hlong m_LogDisplayWinID_Halcon;
	CStatic m_MonitorPhoto;
    char    m_strDbname[256];
public:
	afx_msg void OnBnClickedBtnOpen();
};
