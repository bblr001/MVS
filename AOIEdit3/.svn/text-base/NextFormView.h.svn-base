#if !defined(AFX_NEXTFORMVIEW_H__0208450D_FB06_4F58_A083_080FA0D61D67__INCLUDED_)
#define AFX_NEXTFORMVIEW_H__0208450D_FB06_4F58_A083_080FA0D61D67__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CNextFormView form view

#ifndef __AFXEXT_H__
#include <afxext.h>
#endif
#include "resource.h"
#include "afxwin.h"
#include "ErrorImageDispWnd.h"
#include "../inc/ShareMem.h"
#include "cpp/HalconCpp.h"
using namespace Halcon;

class CNextFormView : public CFormView
{
protected:
	DECLARE_DYNCREATE(CNextFormView)
public:
	CNextFormView();   
	enum { IDD = IDD_NEXTFORM };

	void ShowErrorLogPic(CMData* pData);
	CPagerCtrl m_pagerctrl;	
private:

	CErrorImageCabinet     m_errorImgPanel;
	CToolBar m_toolbar;
	int m_pageHeight;

	string m_tlsfilename;
	string m_programname;
	string m_imagefilename;
	IPC_CMD_BUS_DEPRECATED m_cmdProxy;
public:
	void OpenHelpTool();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate();

protected:
	virtual ~CNextFormView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void CNextFormView::OnCalcSize(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void CNextFormView::OnPGScroll(NMHDR * pNotifyStruct, LRESULT * result);
	afx_msg void CNextFormView::OnHotItemChg(NMHDR * pNotifyStruct, LRESULT * result);//

	DECLARE_MESSAGE_MAP()
public:
	HWND GetWinID(){ return m_grabPicture.m_hWnd;}
private:
	CStatic m_grabPicture;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEXTFORMVIEW_H__0208450D_FB06_4F58_A083_080FA0D61D67__INCLUDED_)
