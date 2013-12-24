// DrawRegistDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "DrawRegionDlg.h"
#include "MConfigCenter.h"
#include "MCtrlCenter.h"
#include <algorithm>
#include <atlconv.h>

// CDrawRegionDlg 对话框

IMPLEMENT_DYNAMIC(CDrawRegionDlg, CDialog)
CDrawRegionDlg::CDrawRegionDlg(Hobject rgn, CWnd* pParent /*=NULL*/)
	: CDialog(CDrawRegionDlg::IDD, pParent)
{
	m_pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	m_currentData = CMCtrlCenter::GetSingletonCtrlCenter()->GetFrameFromReport();
	m_lDispWndID = m_currentData.m_ShowHWindow;
	long test = m_pConfigCenter->GetShowWindowHID();
	m_currentRgn = rgn;
	SHAPE_OPERATION shape;
	shape.m_shape = rgn;
	m_shapeTrace.push(shape);

	CRect* pWndRect = m_pConfigCenter->GetUISize();
	int totalRow    = pWndRect->Height();
	int totalColumn = pWndRect->Width();
	CRect rect;
	rect.top = 0;
	rect.left = 0;
	rect.bottom = totalRow;
	rect.right = totalColumn;
	m_pConfigCenter->SetDispRect(rect);
	
}

CDrawRegionDlg::~CDrawRegionDlg()
{
}

void CDrawRegionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDrawRegionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_CIRCLE, &CDrawRegionDlg::OnBnClickedButtonDrawCircle)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_ELLIPSE, &CDrawRegionDlg::OnBnClickedButtonDrawEllipse)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_RECTANGLE, &CDrawRegionDlg::OnBnClickedButtonDrawRectangle)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_POLYGON, &CDrawRegionDlg::OnBnClickedButtonDrawPolygon)
	ON_BN_CLICKED(IDC_BUTTON_UNION, &CDrawRegionDlg::OnBnClickedButtonUnion)
	ON_BN_CLICKED(IDC_BUTTON_DIFF, &CDrawRegionDlg::OnBnClickedButtonDiff)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CDrawRegionDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_REDRAW, &CDrawRegionDlg::OnBnClickedButtonUndo)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()
// CDrawRegionDlg message handlers
void CDrawRegionDlg::OnBnClickedButtonDrawCircle()
{
	this->EnableWindow(FALSE);
	set_color( m_lDispWndID,"green");
	HTuple  row, column, r,Num;
	draw_circle(m_lDispWndID,&row, &column, &r);
	gen_circle(&m_shape,row, column, r);
	disp_region(m_shape,m_lDispWndID);
	count_obj(m_currentRgn, &Num);
	if(Num==0)
	{
		m_currentRgn = m_shape;
	}	this->EnableWindow(TRUE);
}

void CDrawRegionDlg::OnBnClickedButtonDrawEllipse()
{
	this->EnableWindow(FALSE);
	set_color( m_lDispWndID,"green");
	HTuple row1,column1, phi,r1,r2,Num;
	draw_ellipse(m_lDispWndID, &row1, &column1, &phi, &r1, &r2);
	gen_ellipse(&m_shape, row1, column1, phi, r1, r2);
	disp_region(m_shape, m_lDispWndID);
	count_obj(m_currentRgn, &Num);
	if(Num==0)
	{
		m_currentRgn = m_shape;
	}
	this->EnableWindow(TRUE);
}

void CDrawRegionDlg::OnBnClickedButtonDrawRectangle()
{
	this->EnableWindow(FALSE);
	set_color( m_lDispWndID,"green");
	HTuple row1,column1,row2,column2,Num;
	draw_rectangle1(m_lDispWndID, &row1, &column1,&row2, &column2);
	gen_rectangle1(&m_shape,row1,column1,row2,column2);
	count_obj(m_currentRgn, &Num);
	if(Num==0)
	{
		m_currentRgn = m_shape;
	}
	disp_region(m_shape, m_lDispWndID);
	this->EnableWindow(TRUE);
}

void CDrawRegionDlg::OnBnClickedButtonDrawPolygon()
{
	this->EnableWindow(FALSE);
	HTuple Rows1, Cols1,Tangents,Num;
	HTuple  ControlRows, ControlCols, Knots1;
	Hobject tmp;
	//draw_region(&m_shape,m_lDispWndID);
	set_color( m_lDispWndID,"green");

	draw_nurbs_interp(&tmp, m_lDispWndID, "true", "true", "true", "true", 3, &ControlRows, 
		&ControlCols, &Knots1, &Rows1, &Cols1, &Tangents);
	gen_region_contour_xld (tmp, &m_shape, "filled");
	count_obj(m_currentRgn, &Num);
	if(Num==0)
	{
		m_currentRgn = m_shape;
	}
	disp_region(m_shape, m_lDispWndID);
	this->EnableWindow(TRUE);
}

void CDrawRegionDlg::OnBnClickedButtonUnion()
{
	SHAPE_OPERATION shape;
	shape.m_shape = m_shape;
	m_shapeTrace.push(shape);
	union2(m_currentRgn,m_shape,&m_currentRgn);

	RedrawImageAndRegions();
}

void CDrawRegionDlg::OnBnClickedButtonDiff()
{
	SHAPE_OPERATION shape;
	shape.m_shape = m_shape;
	shape.m_operationCode = DIFF;
	m_shapeTrace.push(shape);

	Hobject intersec;
	intersection(shape.m_shape,m_currentRgn,&intersec);
	difference(m_currentRgn,intersec,&m_currentRgn);

	RedrawImageAndRegions();
}

void CDrawRegionDlg::OnBnClickedButtonUndo()
{
	if(m_shapeTrace.empty())
	{
		return;
	}
	m_shapeTrace.pop();

	if(m_shapeTrace.empty())
	{
		clear_window(m_lDispWndID);
		CRect dispRect = m_pConfigCenter->GetDispRect();
		//set_part(m_lDispWndID,dispRect.top, dispRect.left, dispRect.bottom, dispRect.right);
		set_color( m_lDispWndID,"red");
		disp_image(m_currentData.m_Image,m_lDispWndID);
		//disp_region(m_currentData.m_ErrorRegist,m_lDispWndID);
		disp_region(m_currentData.m_TestRegist1,m_lDispWndID);
		disp_region(m_currentData.m_TestRegist2,m_lDispWndID);
		m_currentRgn.Reset();
		return;
	}
	std::stack<SHAPE_OPERATION> backup = m_shapeTrace;

	std::stack<SHAPE_OPERATION> tmpShapes;
	SHAPE_OPERATION shape;
	while(!m_shapeTrace.empty())
	{
		shape = m_shapeTrace.top();
		tmpShapes.push(shape);
		m_shapeTrace.pop();
	}

	SHAPE_OPERATION so = tmpShapes.top();
	tmpShapes.pop();

    m_currentRgn = so.m_shape;
	while(!tmpShapes.empty())
	{
		so = tmpShapes.top();
		tmpShapes.pop();
		if(so.m_operationCode == UNION)
		{
			union2(m_currentRgn, so.m_shape, &m_currentRgn);
		}
		if(so.m_operationCode == DIFF)
		{
			difference(m_currentRgn,so.m_shape, &m_currentRgn);
		}
	}
	RedrawImageAndRegions();
	std::swap(backup, m_shapeTrace);
}

void CDrawRegionDlg::OnBnClickedButtonSave()
{
	CFileDialog  SaveRegDlg(FALSE,NULL, _T("*.reg"),OFN_OVERWRITEPROMPT, _T("ROI File(*.reg)|*.reg"));
	USES_CONVERSION;
	CString strProgName = A2CT(m_pConfigCenter->GetProgramName().c_str());
	CString defPath;
	defPath.Format(_T("d:\\SLACTST\\%s\\"),strProgName);
	SaveRegDlg.m_ofn.lpstrInitialDir = defPath;
	if(SaveRegDlg.DoModal() == IDOK) 
	{ 
		wstring tmp(SaveRegDlg.GetPathName());
		string fileName = ws2s(tmp);
		write_region(m_currentRgn,fileName.c_str());
		defPath.Format(_T("d:\\SLACTST\\%s\\%s.dat"),strProgName, SaveRegDlg.GetFileTitle());
						 
		CString Data;
		Data.Format(_T("%f"),m_currentData.m_orientationPhi);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModePhi"),Data,defPath); 
						 
		Data.Format(_T("%f"),(float)m_currentData.m_center_y2);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterRow"),Data,defPath); 
						 
		Data.Format(_T("%f"),(float)m_currentData.m_center_x2);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterColumn"),Data,defPath); 
						 
		Data.Format(_T("%f"),(float)m_currentData.r_real);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredRadius"),Data,defPath); 
	}
	SaveRegDlg.DestroyWindow();
	this->DestroyWindow();

}

void CDrawRegionDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDrawRegionDlg::RedrawImageAndRegions()
{
	clear_window(m_lDispWndID);
	CRect dispRect = m_pConfigCenter->GetDispRect();
	//set_part(m_lDispWndID,dispRect.top, dispRect.left, dispRect.bottom, dispRect.right);
	set_color( m_lDispWndID,"red");
	disp_image(m_currentData.m_Image,m_lDispWndID);
	//disp_region(m_currentData.m_ErrorRegist,m_lDispWndID);
	disp_region(m_currentData.m_TestRegist1,m_lDispWndID);
	disp_region(m_currentData.m_TestRegist2,m_lDispWndID);
	disp_region(m_currentRgn,m_lDispWndID);
	m_pConfigCenter->SetRoiOfCurrentImage(m_currentRgn);
}
