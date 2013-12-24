#pragma once

#include<vector>
#include<stack>
#include "cpp\HalconCpp.h"
#include "../Inc/MData.h"

using  namespace std;
using namespace Halcon;

const int UNION = 1;
const int DIFF  = -1;

struct SHAPE_OPERATION
{
	Hobject m_shape;
	int m_operationCode; // 1:union operation; -1:difference operation; others are invalid
	SHAPE_OPERATION():m_operationCode(UNION)
	{
	}
	SHAPE_OPERATION(const SHAPE_OPERATION& other)
	{
		m_shape = other.m_shape;
		m_operationCode = other.m_operationCode;
	}

	SHAPE_OPERATION& operator=(const SHAPE_OPERATION& other)
	{
		if(this == &other)
			return *this;
		m_shape = other.m_shape;
		m_operationCode = other.m_operationCode;
		return *this;
	}
};

// CDrawRegionDlg 对话框
class CMConfigCenter;
class CMData;

class CDrawRegionDlg : public CDialog
{
	DECLARE_DYNAMIC(CDrawRegionDlg)

public:
	CDrawRegionDlg(Hobject rgn,CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrawRegionDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_DRAW_SHAPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDrawCircle();
	afx_msg void OnBnClickedButtonDrawEllipse();
	afx_msg void OnBnClickedButtonDrawRectangle();
	afx_msg void OnBnClickedButtonDrawPolygon();
	afx_msg void OnBnClickedButtonUnion();
	afx_msg void OnBnClickedButtonDiff();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonUndo();

private:
	CMConfigCenter* m_pConfigCenter;
	Hobject m_currentRgn;
	std::stack<SHAPE_OPERATION> m_shapeTrace;
	CMData m_currentData;
	long m_lDispWndID;
	Hobject m_shape;
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

private:
	void RedrawImageAndRegions();
};
