// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (c) Microsoft Corporation.  All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "CustomProperties.h"
#include "Resource.h"
#include "..\AOIEDITHelp\PropertyFormView.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////
// CCheckBoxProp class

CCheckBoxProp::CCheckBoxProp(const CString& strName, BOOL bCheck, LPCTSTR lpszDescr, DWORD dwData):
CMFCPropertyGridProperty(strName, COleVariant((long)bCheck), lpszDescr, dwData)
{
	m_rectCheck.SetRectEmpty();
}



void CCheckBoxProp::OnDrawName(CDC* pDC, CRect rect)
{
	m_rectCheck = rect;
	m_rectCheck.DeflateRect(1, 1);
	m_rectCheck.right = m_rectCheck.left + m_rectCheck.Height();
	rect.left = m_rectCheck.right + 1;

	CMFCPropertyGridProperty::OnDrawName(pDC, rect);
	OnDrawCheckBox(pDC, m_rectCheck, (m_varValue.boolVal));
}



void CCheckBoxProp::OnClickName(CPoint point)
{
	if (m_bEnabled && m_rectCheck.PtInRect(point))
	{
		m_varValue.boolVal = !(m_varValue.boolVal);
		m_pWndList->InvalidateRect(m_rectCheck);
	}
}


BOOL CCheckBoxProp::OnDblClk(CPoint point)
{
	if (m_bEnabled && m_rectCheck.PtInRect(point))
	{
		return TRUE;
	}
	m_varValue.boolVal = !(m_varValue.boolVal);
	m_pWndList->InvalidateRect(m_rectCheck);
	return TRUE;
}

void CCheckBoxProp::OnDrawCheckBox(CDC * pDC, CRect rect, BOOL bChecked)
{
	COLORREF clrTextOld = pDC->GetTextColor();
	CMFCVisualManager::GetInstance()->OnDrawCheckBox(pDC, rect, FALSE, bChecked, m_bEnabled);
	pDC->SetTextColor(clrTextOld);
}

BOOL CCheckBoxProp::PushChar(UINT nChar)
{
	if (nChar == VK_SPACE)
	{
		OnDblClk(CPoint(-1, -1));
	}
	return TRUE;
}



////////////////////////////////////////////////////////////////////////////////

// CPasswordProp class
const TCHAR cPassword = _T('*');
CPasswordProp::CPasswordProp(const CString& strName, const CString& strPassword, LPCTSTR lpszDescr, DWORD dwData)
: CMFCPropertyGridProperty(strName, (LPCTSTR) strPassword, lpszDescr, dwData)
{
}

CWnd* CPasswordProp::CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)

{
	CEdit* pWndEdit = new CEdit;

	DWORD dwStyle = WS_VISIBLE | WS_CHILD | ES_AUTOHSCROLL | ES_PASSWORD;
	if (!m_bEnabled || !m_bAllowEdit)
	{
		dwStyle |= ES_READONLY;
	}
	pWndEdit->Create(dwStyle, rectEdit, m_pWndList, AFX_PROPLIST_ID_INPLACE);
	pWndEdit->SetPasswordChar(cPassword);
	bDefaultFormat = TRUE;
	return pWndEdit;
}



CString CPasswordProp::FormatProperty()

{
	CString strVal = (LPCTSTR)(_bstr_t)m_varValue;
	for (int i = 0; i < strVal.GetLength(); i++)
	{
		strVal.SetAt(i, cPassword);
	}
	return strVal;
}



/////////////////////////////////////////////////////////////////////////////

// CPropSliderCtrl



CPropSliderCtrl::CPropSliderCtrl(CSliderProp* pProp, COLORREF clrBack)

{
	m_clrBack = clrBack;

	m_brBackground.CreateSolidBrush(m_clrBack);

	m_pProp = pProp;
}



CPropSliderCtrl::~CPropSliderCtrl()

{

}



BEGIN_MESSAGE_MAP(CPropSliderCtrl, CSliderCtrl)
	//{{AFX_MSG_MAP(CPropSliderCtrl)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_HSCROLL_REFLECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////

// CPropSliderCtrl message handlers



HBRUSH CPropSliderCtrl::CtlColor(CDC* pDC, UINT/*nCtlColor*/)

{
	pDC->SetBkColor(m_clrBack);
	return m_brBackground;

}



void CPropSliderCtrl::HScroll(UINT/*nSBCode*/, UINT/*nPos*/)

{

	ASSERT_VALID(m_pProp);
	m_pProp->OnUpdateValue();
	m_pProp->Redraw();
}



////////////////////////////////////////////////////////////////////////////////

// CSliderProp class



CSliderProp::CSliderProp(const CString& strName, float nValue, LPCTSTR lpszDescr, DWORD dwData):
CMFCPropertyGridProperty(strName, nValue, lpszDescr, dwData)
{
	m_iMin=0;
	m_iMax=100;
	m_type = IFLOAT;
}
CSliderProp::CSliderProp(const CString& strName, long nValue, LPCTSTR lpszDescr, DWORD dwData):
CMFCPropertyGridProperty(strName, nValue, lpszDescr, dwData)
{
	m_iMin=0;
	m_iMax=100;
	m_type = IINT;
}

CString CSliderProp::FormatProperty()
{
	CMFCPropertyGridProperty::m_strFormatFloat = _T("%.1f");
	return CMFCPropertyGridProperty::FormatProperty();

}

CWnd* CSliderProp::CreateInPlaceEdit(CRect rectEdit, BOOL& bDefaultFormat)
{
	CPropSliderCtrl* pWndSlider = new CPropSliderCtrl(this, m_pWndList->GetBkColor());
	rectEdit.top+=15;
	rectEdit.bottom +=35;
	pWndSlider->Create(WS_VISIBLE | WS_CHILD|TBS_AUTOTICKS , rectEdit, m_pWndList, AFX_PROPLIST_ID_INPLACE);
	
	if (IINT==m_type)
	{
		pWndSlider->SetRange(m_iMin,m_iMax);
		pWndSlider->SetPos(m_varValue.intVal);
	}
	if (IFLOAT==m_type)
	{
		pWndSlider->SetRange(m_iMin*10,m_iMax*10);
		pWndSlider->SetPos(m_varValue.fltVal*10);

	}
	
	bDefaultFormat = TRUE;
	return pWndSlider;
}

void CSliderProp::SetRang(int min,int max)
{
	m_iMin = min;
	m_iMax = max;
}

//******************************************************************************************
BOOL CSliderProp::OnUpdateValue ()
{
	ASSERT_VALID (this);
	ASSERT_VALID (m_pWndInPlace);
	ASSERT_VALID (m_pWndList);
	ASSERT (::IsWindow (m_pWndInPlace->GetSafeHwnd ()));
	CSliderCtrl* pSlider = (CSliderCtrl*) m_pWndInPlace;

	if (IINT==m_type)
	{
		int lCurrValue = m_varValue.intVal ;
		m_varValue.intVal = pSlider->GetPos ();
		if (lCurrValue != m_varValue.intVal)
		{
			m_pWndList->OnPropertyChanged (this);
		}
	}
	if (IFLOAT==m_type)
	{
		float lCurrValue = m_varValue.fltVal;
		m_varValue.fltVal = (float) pSlider->GetPos ()/10.0;
		
		if (lCurrValue != (float) m_varValue.fltVal)
		{
			m_pWndList->OnPropertyChanged (this);
		}
	}
	return TRUE;
}


CTwoButtonsProp::CTwoButtonsProp(CString& strName, CString& strValue,CString& helpDescription,CPropertyFormView* wnd):CMFCPropertyGridProperty(strName, strValue,helpDescription)

{
	CBitmap bmp;
	bmp.LoadBitmap (IDB_BITMAP_PRO_BUTTON);
	m_wnd=wnd;

	m_pStrName = strName;
	m_pStrValue = strValue;

	m_images.Create (14, 14, ILC_MASK | ILC_COLOR8, 0, 0);
	m_images.Add (&bmp, RGB (255, 0, 255));
}

void CTwoButtonsProp::AdjustButtonRect ()
{
	CMFCPropertyGridProperty::AdjustButtonRect ();
	m_rectButton.left -= m_rectButton.Width ();
}

void CTwoButtonsProp::OnClickButton (CPoint point)
{
	BOOL bIsLeft = point.x < m_rectButton.CenterPoint ().x;
	bIsLeft ? m_wnd->OnClickLeftButton(m_pStrValue,this) : m_wnd->OnClickRightButton(m_pStrValue,this);

}

void CTwoButtonsProp::OnDrawButton (CDC* pDC, CRect rectButton)
{
	for (int i = 0; i < 2; i++)
	{
		CMFCToolBarButton button;
		CRect rect = rectButton;
		if (i == 0)
		{
			rect.right = rect.left + rect.Width () / 2;
		}
		else
		{
			rect.left = rect.right - rect.Width () / 2;
		}

		CMFCVisualManager::AFX_BUTTON_STATE state = CMFCVisualManager::ButtonsIsHighlighted;

 		CMFCVisualManager::GetInstance ()->OnFillButtonInterior (pDC,&button, rect, state);

 		m_images.Draw (pDC, i, CPoint (rect.left, rect.top), ILD_NORMAL);
 
 		CMFCVisualManager::GetInstance ()->OnDrawButtonBorder (pDC, &button, rect, state);
	}
}


CCreateButtonsProp::CCreateButtonsProp(CString& strName, CString& strValue,CString& helpDescription,CPropertyFormView* wnd):CMFCPropertyGridProperty(strName, strValue,helpDescription)

{
	CBitmap bmp;
	bmp.LoadBitmap (IDB_BITMAP_CREATE_BUTTON);
	m_wnd=wnd;

	m_pStrName = strName;
	m_pStrValue = strValue;

	m_images.Create (14, 14, ILC_MASK | ILC_COLOR8, 0, 0);
	m_images.Add (&bmp, RGB (255, 0, 255));
}

void CCreateButtonsProp::AdjustButtonRect ()
{
	CMFCPropertyGridProperty::AdjustButtonRect ();
	m_rectButton.left -= m_rectButton.Width ();
}

void CCreateButtonsProp::OnClickButton (CPoint point)
{
	//BOOL bIsLeft = point.x < m_rectButton.CenterPoint ().x;
	m_wnd->OnClickCreateButton(m_pStrValue,this);

}

void CCreateButtonsProp::OnDrawButton (CDC* pDC, CRect rectButton)
{
	for (int i = 0; i < 1; i++)
	{
		CMFCToolBarButton button;

		CRect rect = rectButton;

		rect.left = rect.right - rect.Width () / 2;

		CMFCVisualManager::AFX_BUTTON_STATE state = CMFCVisualManager::ButtonsIsHighlighted;

		CMFCVisualManager::GetInstance ()->OnFillButtonInterior (pDC,&button, rect, state);

		m_images.Draw (pDC, i, CPoint (rect.left, rect.top), ILD_NORMAL);

		CMFCVisualManager::GetInstance ()->OnDrawButtonBorder (pDC, &button, rect, state);
	}
}


CLoadButtonsProp::CLoadButtonsProp(CString& strName, CString& strValue,CString& helpDescription,CPropertyFormView* wnd):CMFCPropertyGridProperty(strName, strValue,helpDescription)
{
	CBitmap bmp;
	bmp.LoadBitmap (IDB_BITMAP_LOAD_BUTTON);
	m_wnd=wnd;

	m_pStrName = strName;
	m_pStrValue = strValue;

	m_images.Create (14, 14, ILC_MASK | ILC_COLOR8, 0, 0);
	m_images.Add (&bmp, RGB (255, 0, 255));
}

void CLoadButtonsProp::AdjustButtonRect ()
{
	CMFCPropertyGridProperty::AdjustButtonRect ();
	m_rectButton.left -= m_rectButton.Width ();
}

void CLoadButtonsProp::OnClickButton (CPoint point)
{
	//BOOL bIsLeft = point.x < m_rectButton.CenterPoint ().x;
	m_wnd->OnClickLoadButton(m_pStrValue,this);

}

void CLoadButtonsProp::OnDrawButton (CDC* pDC, CRect rectButton)
{
	for (int i = 0; i < 1; i++)
	{
		CMFCToolBarButton button;

		CRect rect = rectButton;
		rect.left = rect.right - rect.Width () / 2;

		CMFCVisualManager::AFX_BUTTON_STATE state = CMFCVisualManager::ButtonsIsHighlighted;

		CMFCVisualManager::GetInstance ()->OnFillButtonInterior (pDC,&button, rect, state);

		m_images.Draw (pDC, i, CPoint (rect.left, rect.top), ILD_NORMAL);

		CMFCVisualManager::GetInstance ()->OnDrawButtonBorder (pDC, &button, rect, state);
	}
}
