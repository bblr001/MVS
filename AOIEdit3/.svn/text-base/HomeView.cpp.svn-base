// NextFormView.cpp : implementation file
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "HomeView.h"
#include "MainFrm.h"
#include <assert.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHomeFormView
void MyHalconExceptionHandlerOnDraw(const Halcon::HException& except)
{
	throw except;	
}

IMPLEMENT_DYNCREATE(CHomeFormView, CFormView)

CHomeFormView::CHomeFormView()
: CFormView(CHomeFormView::IDD),
  m_pConfigCenter(CMConfigCenter::GetSingletonConfigCenter()),
  m_pCtrlCenter(CMCtrlCenter::GetSingletonCtrlCenter()),
  m_dRatio(1.0)
{
	assert(m_pConfigCenter != nullptr);
	assert(m_pCtrlCenter != nullptr);
	HException::InstallHHandler(&MyHalconExceptionHandlerOnDraw);
}
CHomeFormView::~CHomeFormView()
{
}
void CHomeFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CHomeFormView, CFormView)
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomeFormView diagnostics

#ifdef _DEBUG
void CHomeFormView::AssertValid() const
{
	CFormView::AssertValid();
}
void CHomeFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CHomeFormView message handlers

void CHomeFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_pConfigCenter->SetUIWindowID((Hlong)this->m_hWnd);
}


BOOL CHomeFormView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(nFlags != MK_CONTROL)
		return FALSE;
	if(m_pConfigCenter->GetDebugModeFlag() == false)
		return FALSE;

	CMData data = CMCtrlCenter::GetSingletonCtrlCenter()->m_reportCenter.GetCurrentData();
	HTuple imgWidth, imgHeight;
	get_image_size(data.m_Image, &imgWidth, &imgHeight);

	using namespace Halcon;
	Hlong hWndHandle = m_pConfigCenter->GetShowWindowHID();
	HTuple tmpRow, tmpCol, tmpWidth, tmpHeight;
	get_window_extents(hWndHandle, &tmpRow, &tmpCol, &tmpWidth, &tmpHeight);

	int totalRow    = tmpHeight[0].I();
	int totalColumn = tmpWidth[0].I();

	double xRatio = (double)tmpWidth[0].I()/imgWidth[0].I();
	double yRatio = (double)tmpHeight[0].I() / imgHeight[0].I();
	int deltaColumn = (pt.x - tmpCol[0].I()) / xRatio;
	int deltaRow    = (pt.y - tmpRow[0].I()) / yRatio;

	if(zDelta > 0) // Zoom in he image
	{
		if(m_dRatio < 10.4)
		{
			m_dRatio += 0.4;
		}
	}
	else // Zoom out the image
	{
		if(m_dRatio > 1.0)
		{
			m_dRatio -= 0.4;
		}
		else
		{
			return TRUE;
		}
	}

	int rowBgn = deltaRow * (1 - 1/m_dRatio);
	int rowEnd = deltaRow + (imgHeight[0].I() - deltaRow) * (1/m_dRatio);

	int columnBgn  = deltaColumn *(1 - 1/m_dRatio);
	int columnEnd = deltaColumn +  (imgWidth[0].I() - deltaColumn) * (1/m_dRatio);

	CRect dispRgn;
	dispRgn.top    = rowBgn;
	dispRgn.left   = columnBgn;
	dispRgn.right  = columnEnd;
	dispRgn.bottom = rowEnd;
	m_pConfigCenter->SetDispRect(dispRgn);

	clear_window(hWndHandle);
	set_part(hWndHandle,rowBgn, columnBgn, rowEnd-1, columnEnd-1);
	disp_image(data.m_Image,hWndHandle);
	disp_region(data.m_ErrorRegist,hWndHandle);
	disp_region(data.m_TestRegist1,hWndHandle);
	disp_region(data.m_TestRegist2,hWndHandle);
	disp_region(m_pConfigCenter->GetRoiOfCurrentImage(),hWndHandle);
	return TRUE;
}


void CHomeFormView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CFormView::OnKeyDown(nChar, nRepCnt, nFlags);
}
