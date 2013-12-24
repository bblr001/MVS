// CheckBox.cpp : 实现文件
//

#include "stdafx.h"
#include "CheckBox.h"


// CCheckBox

IMPLEMENT_DYNAMIC(CCheckBox, CButton)

CCheckBox::CCheckBox()
{

}

CCheckBox::~CCheckBox()
{
}


BEGIN_MESSAGE_MAP(CCheckBox, CButton)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CCheckBox 消息处理程序

HBRUSH CCheckBox::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetTextColor(RGB(255,255,255));
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	//return (HBRUSH)GetStockObject(NULL_BRUSH);
}


void CCheckBox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	CRect rect;
	GetWindowRect(&rect);
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255,255,255));
	// 不为绘图消息调用 CButton::OnPaint()
}
