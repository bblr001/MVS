// halcon001Dlg.h : header file
//

#if !defined(AFX_HALCON001DLG_H__9A50E3AC_7129_4FB2_B854_2D7E32EDB921__INCLUDED_)
#define AFX_HALCON001DLG_H__9A50E3AC_7129_4FB2_B854_2D7E32EDB921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "cpp\HalconCpp.h"

using namespace Halcon ;



/////////////////////////////////////////////////////////////////////////////
// CHalcon001Dlg dialog

class CHalcon001Dlg : public CDialog
{
// Construction
public:
	Hlong Thred_center2;
	bool Enable_Block(int block_x, int block_y);
	Hlong TR;
	Hlong Tyy;
	Hlong Txx;
	Hlong Thred_center1;

	Hlong Pointer;
	Hobject image;
	Hlong Width;
	Hlong Height;
	Hlong wWindowID;
	Hlong FGHandle;
	CString szGetName;
	void OnFileOpen();
	CHalcon001Dlg(CWnd* pParent = NULL);	// standard constructor

	CStatic m_Test;
	CStatic m_NeedTime;
//	CStatic m_Flag11;
//	HINSTANCE m_hInst;

// Dialog Data
	//{{AFX_DATA(CHalcon001Dlg)
	enum { IDD = IDD_HALCON001_DIALOG };
	CButton	m_pic;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHalcon001Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHalcon001Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void On_Bn_Open();
	afx_msg void On_Bn_Center1();
	afx_msg void OnBnClose();
	afx_msg void OnStaticFlag();
	afx_msg void OnSTATICNeedTime();
	afx_msg void On_Bn_Edge();
	afx_msg void On_Bn_Rut();
	afx_msg void On_Bn_Center2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void On_Bn_Axle();
	afx_msg void On_Bn_WhiteZone();
	afx_msg void On_Bn_Test();
	
	

	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HALCON001DLG_H__9A50E3AC_7129_4FB2_B854_2D7E32EDB921__INCLUDED_)
