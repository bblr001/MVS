#pragma once
#include "cpp\HalconCpp.h"
#include "../Inc/MData.h"

using  namespace std;
using namespace Halcon;

// CDrawRegistDialog 对话框

class CDrawRegistDialog : public CDialog
{
	DECLARE_DYNAMIC(CDrawRegistDialog)
	
	CMData m_currentData;
	long m_lDispWndID;
	Hobject m_shape;
	Hobject m_currentRgn;
	CString m_name;
	void RedrawImageAndRegions();
public:
	CDrawRegistDialog(Hobject rgn,CString name, CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrawRegistDialog();

// 对话框数据
	enum { IDD = IDD_DIALOG_DRAW_SHARP };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDrawCircle();
	afx_msg void OnBnClickedButtonDrawEllipse();
	afx_msg void OnBnClickedButtonDrawRectangle();
	afx_msg void OnBnClickedButtonDrawPolygon();
	afx_msg void OnBnClickedButtonDrawUnion();
	afx_msg void OnBnClickedButtonDrawDiff();
	afx_msg void OnBnClickedButtonDrawSave();
};
