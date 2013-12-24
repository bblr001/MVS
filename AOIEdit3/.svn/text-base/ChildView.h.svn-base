// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

// ChildView.h : CChildView 类的接口
//


#pragma once
#include "cpp/HalconCpp.h"

// CChildView 窗口

class CChildView : public CWnd
{
// 构造
public:
	CChildView();

// 属性
public:

// 操作
public:
	void InitImageWindow(Halcon::Hobject& objImg);
	void InitImageWindow(Halcon::HByteImage& byteImg);
	void InitHalconWindow();
// 重写
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CChildView();

	// 生成的消息映射函数
protected:
	int m_wndWidth;
	int m_wndHeigth;
	Halcon::HWindow m_hoHWindCLS;
    bool m_bInitHalconW;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void  OnClose();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

