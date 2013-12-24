// DrawRegistDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEDITHelp.h"
#include "DrawRegistDialog.h"
#include "Tools.h"
#include ".\DoProcess\CMCfgCenter.h"
#include "..\Inc\TypeCent.h"
#include ".\DoProcess\CMCtrolCenter.h"
#include "customproperties.h"
#include "MainFrm.h"
// CDrawRegistDialog 对话框

IMPLEMENT_DYNAMIC(CDrawRegistDialog, CDialog)
CDrawRegistDialog::CDrawRegistDialog(Hobject rgn,CString name,CWnd* pParent /*=NULL*/)
	: CDialog(CDrawRegistDialog::IDD, pParent)
{
	m_name = name;
	m_currentRgn = rgn;
	m_lDispWndID = CMCfgCenter::GetCfgCenter().GetHCWnd();
}

CDrawRegistDialog::~CDrawRegistDialog()
{
}

void CDrawRegistDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDrawRegistDialog, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_CIRCLE, &CDrawRegistDialog::OnBnClickedButtonDrawCircle)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_ELLIPSE, &CDrawRegistDialog::OnBnClickedButtonDrawEllipse)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_RECTANGLE, &CDrawRegistDialog::OnBnClickedButtonDrawRectangle)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_POLYGON, &CDrawRegistDialog::OnBnClickedButtonDrawPolygon)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_UNION, &CDrawRegistDialog::OnBnClickedButtonDrawUnion)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_DIFF, &CDrawRegistDialog::OnBnClickedButtonDrawDiff)
	ON_BN_CLICKED(IDC_BUTTON_DRAW_SAVE, &CDrawRegistDialog::OnBnClickedButtonDrawSave)
END_MESSAGE_MAP()
// CDrawRegistDialog 消息处理程序
void CDrawRegistDialog::OnBnClickedButtonDrawCircle()
{
	//this->EnableWindow(FALSE);
	set_color( m_lDispWndID,"green");
	HTuple  row, column, r,Num;
	draw_circle(m_lDispWndID,&row, &column, &r);
	gen_circle(&m_shape,row, column, r);
	disp_region(m_shape,m_lDispWndID);
	count_obj(m_currentRgn, &Num);
	if(Num==0)
	{
		m_currentRgn = m_shape;
	}	//this->EnableWindow(TRUE);
}
void CDrawRegistDialog::OnBnClickedButtonDrawEllipse()
{this->EnableWindow(FALSE);
	set_color( m_lDispWndID,"green");
	HTuple row1,column1, phi,r1,r2,Num;
	draw_ellipse(m_lDispWndID, &row1, &column1, &phi, &r1, &r2);
	gen_ellipse(&m_shape, row1, column1, phi, r1, r2);
	disp_region(m_shape, m_lDispWndID);
	count_obj(m_currentRgn, &Num);
	if(Num==0)
	{
		m_currentRgn = m_shape;
	}	this->EnableWindow(TRUE);
}
void CDrawRegistDialog::OnBnClickedButtonDrawRectangle()
{this->EnableWindow(FALSE);
	set_color( m_lDispWndID,"green");
	HTuple row1,column1,row2,column2,Num;
	draw_rectangle1(m_lDispWndID, &row1, &column1,&row2, &column2);
	gen_rectangle1(&m_shape,row1,column1,row2,column2);
	count_obj(m_currentRgn, &Num);
	if(Num==0)
	{
		m_currentRgn = m_shape;
	}
	disp_region(m_shape, m_lDispWndID);	this->EnableWindow(TRUE);
}
void CDrawRegistDialog::OnBnClickedButtonDrawPolygon()
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
	disp_region(m_shape, m_lDispWndID);	this->EnableWindow(TRUE);
}

void CDrawRegistDialog::OnBnClickedButtonDrawUnion()
{
	
// 	SHAPE_OPERATION shape;
// 	shape.m_shape = m_shape;
// 	m_shapeTrace.push(shape);

	union2(m_currentRgn,m_shape,&m_currentRgn);
	RedrawImageAndRegions();
}


void CDrawRegistDialog::OnBnClickedButtonDrawDiff()
{
// 	SHAPE_OPERATION shape;
// 	shape.m_shape = m_shape;
// 	shape.m_operationCode = DIFF;
// 	m_shapeTrace.push(shape);
	Hobject intersec;
	intersection(m_shape,m_currentRgn,&intersec);
	difference(m_currentRgn,intersec,&m_currentRgn);

	RedrawImageAndRegions();
}


void CDrawRegistDialog::OnBnClickedButtonDrawSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog   SaveRegDlg(FALSE,NULL, _T("myregion.reg"),OFN_OVERWRITEPROMPT, _T("Test Regist File(*.reg)|*.reg"));//save   as 
	CString defPath;
	defPath.Format(_T("%s\\"),theApp.m_ProgramName.c_str());
	SaveRegDlg.m_ofn.lpstrInitialDir = defPath;
	if(SaveRegDlg.DoModal() == IDOK) 
	{ 
		wstring tmp(SaveRegDlg.GetPathName());
		string fileName = WChar2Ansi(tmp.c_str());
		//button->SetValue(defPath+_T("\\")+SaveRegDlg.GetFileTitle());
		write_region(m_currentRgn,fileName.c_str());
		defPath.Format(_T("%s\\%s.dat"),theApp.m_ProgramName.c_str(),SaveRegDlg.GetFileTitle());

		CString Data;
		Data.Format(_T("%f"),CMCtrlCenter::GetCtrlCenter().m_CurrentData.m_orientationPhi);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModePhi"),Data,defPath); 

		Data.Format(_T("%f"),(float)CMCtrlCenter::GetCtrlCenter().m_CurrentData.m_center_y2);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterRow"),Data,defPath); 

		Data.Format(_T("%f"),(float)CMCtrlCenter::GetCtrlCenter().m_CurrentData.m_center_x2);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterColumn"),Data,defPath); 

		Data.Format(_T("%f"),(float)CMCtrlCenter::GetCtrlCenter().m_CurrentData.r_real);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredRadius"),Data,defPath); 
		
// 		CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
// 
// 		string va = WChar2Ansi(tmp.c_str());
// 		string name = WChar2Ansi(m_name);
// 		pMainFrm->ManualUpdate(name,va);
		
	}
	SaveRegDlg.DestroyWindow();
	this->DestroyWindow();
}

void CDrawRegistDialog::RedrawImageAndRegions()
{
	clear_window(m_lDispWndID);
	//CRect dispRect = m_pConfigCenter->GetDispRect();
	//set_part(m_lDispWndID,dispRect.top, dispRect.left, dispRect.bottom, dispRect.right);
	set_color( m_lDispWndID,"red");
	disp_image(CMCtrlCenter::GetCtrlCenter().m_CurrentData.m_Image,m_lDispWndID);
	//disp_region(m_currentData.m_ErrorRegist,m_lDispWndID);
	disp_region(CMCtrlCenter::GetCtrlCenter().m_CurrentData.m_TestRegist1,m_lDispWndID);
	disp_region(CMCtrlCenter::GetCtrlCenter().m_CurrentData.m_TestRegist2,m_lDispWndID);
	disp_region(m_currentRgn,m_lDispWndID);
	//m_pConfigCenter->SetRoiOfCurrentImage(m_currentRgn);
}