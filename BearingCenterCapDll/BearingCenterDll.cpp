// CenterCapDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "BearingCenterDll.h"
#include "../Inc/MData.h"

#pragma warning(disable:4244)



#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif
// exception handler
void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}
CDoProcess::CDoProcess()
{
	HException::InstallHHandler(&MyHalconExceptionHandler);
	m_ProcessName ="define center of crown-cap Dll ";
}

void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="Thred_Center1")
		m_Parameters.Thred_Center1= atoi(value.c_str());
	if(parm=="Thred_Center2")
		m_Parameters.Thred_Center2= atoi(value.c_str());

	if(parm=="XMax")
		m_Parameters.XMax = atoi(value.c_str());
	if(parm=="XMin")
		m_Parameters.XMin = atoi(value.c_str());
	if(parm=="YMax")
		m_Parameters.YMax = atoi(value.c_str());
	if(parm=="YMin")
		m_Parameters.YMin = atoi(value.c_str());
	if(parm=="ARMax")
		m_Parameters.ARMax = atoi(value.c_str());
	if(parm=="ARMin")
		m_Parameters.ARMin = atoi(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	//有些早，位置不对
	Hlong Thred_center1=m_Parameters.Thred_Center1;
	Hlong Thred_center2=m_Parameters.Thred_Center2;


	//////////////////////////////////////////////
	// Local iconic variables 
	Hlong Width, Height,m_thred;
	Hobject   Rectangle, ImageReduced1, ImageReduced;
	Hobject  ImageZoom, Region, ConnectedRegions, SelectedRegions;
	Hobject  RegionUnion, RegionFillUp,RegionFillUp_ext;
	HTuple  Area, Row, Column, Radius;
	try
	{
		// dev_update_off(...); only in hdevelop
		Hobject Image=pData->m_Image;
		get_image_size(Image,&Width,&Height);
		/////////
		if (m_Parameters.Thred_Center1>m_Parameters.Thred_Center2)
		{
			m_thred=m_Parameters.Thred_Center1;
			m_Parameters.Thred_Center1=m_Parameters.Thred_Center2;
			m_Parameters.Thred_Center2=m_thred;
		}
		gen_rectangle1(&Rectangle, 0, m_Parameters.XMin, Height, m_Parameters.XMax);
		reduce_domain(Image, Rectangle, &ImageReduced1);
		threshold(ImageReduced1, &Region, m_Parameters.Thred_Center1, m_Parameters.Thred_Center2);

		fill_up(Region, &RegionFillUp_ext);
		connection(RegionFillUp_ext, &ConnectedRegions);

		select_shape(ConnectedRegions, &SelectedRegions, "area", "and", m_Parameters.ARMin, m_Parameters.ARMax);
		union1(SelectedRegions, &RegionUnion);
		fill_up(RegionUnion, &RegionFillUp);

		smallest_circle(RegionFillUp, &Row, &Column, &Radius);	//中心点不用这个函数确定
		area_center(RegionFillUp, &Area, &Row, &Column);
		HTuple m_number_center;
		tuple_length(Row,&m_number_center);
		////////////////////////////////////////////
		if ((m_number_center>0)&&(m_Parameters.XMin<Column)&&(Column<m_Parameters.XMax)&&(m_Parameters.YMin<Row)&&(Row<m_Parameters.YMax))
		{
			pData->m_center_x=Column[0].D();  
			pData->m_center_y=Row[0].D();
			pData->r_real=Radius[0].D();
			//pData->m_isFail = false;
			//testItem->m_bFailSubTest = false;
		}
		else
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			pData->m_center_x=330;
			pData->m_center_y=250;
			pData->r_real=185;
			//testItem->m_ErrorMsg = "Error No Find Center";
			testItem->m_ErrorY = 250;
			testItem->m_ErrorX = 350;
			testItem->m_ErrorR = 55;
		}

		set_color(pData->m_ShowHWindow,"red");
		disp_region(RegionFillUp,pData->m_ShowHWindow);
		disp_region(Rectangle,pData->m_ShowHWindow);
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		//testItem->m_ErrorMsg = except.file;
		//testItem->m_ErrorMsg += " ";
		//testItem->m_ErrorMsg += except.line;
		//testItem->m_ErrorMsg += " ";
		//testItem->m_ErrorMsg += except.message;
		testItem->m_ErrorY = 1;
		testItem->m_ErrorX = 1;
		testItem->m_ErrorR = 4;
	}
}
