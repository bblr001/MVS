#pragma once

#include "MData.h"
#include "bounded_buffer.h"
#include "cpp/HalconCpp.h"
using namespace Halcon;

#include "resource.h"
#include "afxwin.h"
#define  NUM 20
class CErrorImageCabinet : public CDialog
{
	DECLARE_DYNAMIC(CErrorImageCabinet)

public:
	CErrorImageCabinet(CWnd* pParent = NULL); 
	virtual ~CErrorImageCabinet();

	enum { IDD = IDD_DISPS };
    void AdjustDispViews(int margin,int *cx,int *cy);

	void ShowErrorLogPic(CMData* pData);
	void UpdateWindow(int i);
	void Init();
protected:
	
	virtual void DoDataExchange(CDataExchange* pDX);
    virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CStatic m_disp1;
	CStatic m_disp2;
	CStatic m_disp3;
	CStatic m_disp4;
	CStatic m_disp5;
	CStatic m_disp6;
	CStatic m_disp7;
	CStatic m_disp8;
	CStatic m_disp9;
	CStatic m_disp10;

	CStatic m_disp11;
	CStatic m_disp12;
	CStatic m_disp13;
	CStatic m_disp14;
	CStatic m_disp15;
	CStatic m_disp16;
	CStatic m_disp17;
	CStatic m_disp18;
	CStatic m_disp19;
	CStatic m_disp20;
private:
	Hlong m_HalconWndID[NUM];
	BOOL	m_bDoubleClieck;
	CRect m_rectList[NUM];
	POINT m_points[5];
	void DrawRec(CRect rect);
	bounded_buffer<CMData> m_errorImgBuffer;
	HPEN  m_Pen;
public:
	CRITICAL_SECTION m_lock;
public:
	afx_msg void OnStnDblclickWnd1();
	afx_msg void OnStnDblclickWnd2();
	afx_msg void OnStnDblclickWnd3();
	afx_msg void OnStnDblclickWnd4();
	afx_msg void OnStnDblclickWnd5();
	afx_msg void OnStnDblclickWnd6();
	afx_msg void OnStnDblclickWnd7();
	afx_msg void OnStnDblclickWnd8();
	afx_msg void OnStnDblclickWnd9();
	afx_msg void OnStnDblclickWnd10();

	afx_msg void OnStnDblclickWnd11();
	afx_msg void OnStnDblclickWnd12();
	afx_msg void OnStnDblclickWnd13();
	afx_msg void OnStnDblclickWnd14();
	afx_msg void OnStnDblclickWnd15();
	afx_msg void OnStnDblclickWnd16();
	afx_msg void OnStnDblclickWnd17();
	afx_msg void OnStnDblclickWnd18();
	afx_msg void OnStnDblclickWnd19();
	afx_msg void OnStnDblclickWnd20();
	afx_msg void OnPaint();

private:
	void DisplayCurrentErrorImage(CMData* pData);
};
