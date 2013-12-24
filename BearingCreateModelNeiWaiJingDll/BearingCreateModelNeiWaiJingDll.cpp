// CreateModelDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <io.h>
#include "BearingCreateModelNeiWaiJingDll.h"
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
	m_ProcessName ="Create shape model Dll ";
}

void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="region_erosion1")
		m_Parameters.region_erosion1_size= atoi(value.c_str());
	if(parm=="region_erosion2")
		m_Parameters.region_erosion2_size= atoi(value.c_str());
	if(parm=="radius_inner_thred")
		m_Parameters.radius_inner_thred= atoi(value.c_str());
	if(parm=="radius_ext_extract_size")
		m_Parameters.radius_ext_extract_size= atoi(value.c_str());
	if(parm=="thred_low1")
		m_Parameters.m_thred_low1= atoi(value.c_str());
	if(parm=="thred_high1")
		m_Parameters.m_thred_high1= atoi(value.c_str());
	if(parm=="thred_low2")
		m_Parameters.m_thred_low2= atoi(value.c_str());
	if(parm=="thred_high2")
		m_Parameters.m_thred_high2= atoi(value.c_str());
	if(!_stricmp(parm.c_str(),"MODEL_REGIST_CREATE"))
	{
		m_Parameters.CenterOcrModelName = value+".shm";
	}
	//
	if(!_stricmp(parm.c_str(),"MODEL_MODEL_REGION"))
	{
		m_Parameters.CenterOcrModelRegion = value+".reg";
	}
	//
	if(!_stricmp(parm.c_str(),"MODEL_DETECT_REGION1"))
	{
		m_Parameters.CenterOcrModelRegion1 = value+".reg";
	}
	//
	if(!_stricmp(parm.c_str(),"MODEL_DETECT_REGION2"))
	{
		m_Parameters.CenterOcrModelRegion2 = value+".reg";
	}
	if(parm=="XMax1")
		m_Parameters.XMax1 = atoi(value.c_str());
	if(parm=="XMin1")
		m_Parameters.XMin1 = atoi(value.c_str());
	if(parm=="YMax1")
		m_Parameters.YMax1 = atoi(value.c_str());
	if(parm=="YMin1")
		m_Parameters.YMin1 = atoi(value.c_str());
	if(parm=="XMax2")
		m_Parameters.XMax2 = atoi(value.c_str());
	if(parm=="XMin2")
		m_Parameters.XMin2 = atoi(value.c_str());
	if(parm=="YMax2")
		m_Parameters.YMax2 = atoi(value.c_str());
	if(parm=="YMin2")
		m_Parameters.YMin2 = atoi(value.c_str());
	//if(parm=="RMax")
	//	m_Parameters.RMax = atoi(value.c_str());
	//if(parm=="RMin")
	//	m_Parameters.RMin = atoi(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	 
	// Local iconic variables 
	Hobject Image=pData->m_Image;
	Hlong m_thred_low1=m_Parameters.m_thred_low1;
	Hlong m_thred_high1=m_Parameters.m_thred_high1;
	Hlong m_thred_low2=m_Parameters.m_thred_low2;
	Hlong m_thred_high2=m_Parameters.m_thred_high2;

	Hlong m_thred;
	/////////
	if (m_thred_low1>m_thred_high1)
	{
		m_thred=m_thred_low1;
		m_thred_low1=m_thred_high1;
		m_thred_high1=m_thred;
	}
	if (m_thred_low2>m_thred_high2)
	{
		m_thred=m_thred_low2;
		m_thred_low2=m_thred_high2;
		m_thred_high2=m_thred;
	}

	///////////////////////////////////////////////////////
	// Local iconic variables 
	Hobject  Region, ConnectedRegions, SelectedRegions;
	Hobject  RegionUnion, RegionFillUp, Contours, Rectangle1;
	Hobject  Rectangle2, ImageReduced1, ImageReduced2, Region1;
	Hobject  Region2, RegionDilation1, RegionErosion1, RegionDilation2;
	Hobject  RegionErosion2;


	// Local control variables 
	HTuple  ModelID,Area;//Row1, Column1, Radius1;
	HTuple  Row11, Column11, Row12, Column12;
	HTuple  Row21, Column21, Row22, Column22;
	////////////////////////////////////////////////////////////
	// Local control variables 
	HTuple  Row;
	HTuple Column;
	// dev_update_off(...); only in hdevelop
	try
	{
		///Row_model_center = 237.659;
		//Column_model_center = 339.212;

		/*gen_circle(&Circle5, Row, Column,m_Parameters.radius_ext);
		gen_circle(&Circle6, Row, Column,m_Parameters.radius_inner);
		difference(Circle5, Circle6, &RegionDifference_median);
		reduce_domain(Image, RegionDifference_median, &ImageReduced_median);
		intensity(RegionDifference_median, Image, &Mean_median, &Deviation_median);
		fast_threshold(ImageReduced_median, &Region_median, m_Parameters.radius_inner_thred, 255, 1);//Mean_median*1.2
		connection(Region_median, &ConnectedRegions_median);
		select_shape(ConnectedRegions_median, &SelectedRegions_median, "area", "and", m_Parameters.radius_ext_extract_size, 
		99999);
		union1(SelectedRegions_median, &RegionUnion_median);
		area_center(RegionUnion_median, &Area_baoChiJia, &Row_baoChiJia, &Column_baoChiJia);*/

		//**********************************************************
		threshold(Image, &Region, 0,  m_Parameters.radius_inner_thred);
		connection(Region, &ConnectedRegions);
		select_shape(ConnectedRegions, &SelectedRegions, "area", "and", m_Parameters.radius_ext_extract_size, 149999);
		union1(SelectedRegions, &RegionUnion);
		fill_up(RegionUnion, &RegionFillUp);
		area_center(RegionFillUp, &Area, &Row, &Column);
		///////////////////////////////////
		/*if (!_access(m_Parameters.CenterOcrModelRegion.c_str(),0))
		{
			wstring msg = _T("Set Region already Exit.OverWrite or Not?");

			if (MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK||MB_CANCELTRYCONTINUE)==IDOK)
			{
				write_region(RegionFillUp,m_Parameters.CenterOcrModelRegion.c_str());
			}

		}
		else*/
			write_region(RegionFillUp,m_Parameters.CenterOcrModelRegion.c_str());
		/////////////////////////////////////////
		gen_contour_region_xld(RegionFillUp, &Contours, "border");

		create_shape_model_xld(Contours, 1, -0.69, 0.79, "auto", "auto", "ignore_local_polarity", 
			5, &ModelID);

		//匹配数据

		/*if (!_access(m_Parameters.CenterOcrModelName.c_str(),0))
		{
			wstring msg = _T("Set Model already Exit.OverWrite or Not?");

			if (MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK||MB_CANCELTRYCONTINUE)==IDOK)
			{
				write_shape_model(ModelID,m_Parameters.CenterOcrModelName.c_str());
			}

		}
		else*/
			write_shape_model(ModelID,m_Parameters.CenterOcrModelName.c_str());	



		//*****************************************************************
		Row11=m_Parameters.YMin1;
		Row12=m_Parameters.YMin1+m_Parameters.YMax1;
		Column11=m_Parameters.XMin1;
		Column12=m_Parameters.XMin1+m_Parameters.XMax1;
		Row21=m_Parameters.YMin2;
		Row22=m_Parameters.YMin2+m_Parameters.YMax2;
		Column21=m_Parameters.XMin2;
		Column22=m_Parameters.XMin2+m_Parameters.XMax2;
		gen_rectangle1(&Rectangle1, Row11, Column11, Row12, Column12);

		gen_rectangle1(&Rectangle2, Row21, Column21, Row22, Column22);

		reduce_domain(Image, Rectangle1, &ImageReduced1);


		reduce_domain(Image, Rectangle2, &ImageReduced2);


		threshold(ImageReduced1, &Region1, m_Parameters.m_thred_low1, m_Parameters.m_thred_high1);
		threshold(ImageReduced2, &Region2, m_Parameters.m_thred_low2, m_Parameters.m_thred_high2);
		dilation_circle(Region1, &RegionDilation1, 3.5);
		erosion_circle(RegionDilation1, &RegionErosion1, m_Parameters.region_erosion1_size);

		dilation_circle(Region2, &RegionDilation2, 3.5);
		erosion_circle(RegionDilation2, &RegionErosion2, m_Parameters.region_erosion2_size);

		//创建模板时 保存区域和区域图片。在提取区域时，因为正常运行时每次都要用，不能使用
		/*if (!_access(m_Parameters.CenterOcrModelRegion1.c_str(),0))
		{
			wstring msg = _T("Set Region already Exit.OverWrite or Not?");

			if (MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK||MB_CANCELTRYCONTINUE)==IDOK)
			{
				write_region(RegionErosion1,m_Parameters.CenterOcrModelRegion1.c_str());
			}

		}
		else*/
			write_region(RegionErosion1,m_Parameters.CenterOcrModelRegion1.c_str());
		/*if (!_access(m_Parameters.CenterOcrModelRegion2.c_str(),0))
		{
			wstring msg = _T("Set Region already Exit.OverWrite or Not?");

			if (MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK||MB_CANCELTRYCONTINUE)==IDOK)
			{
				write_region(RegionErosion2,m_Parameters.CenterOcrModelRegion2.c_str());
			}

		}
		else*/
			write_region(RegionErosion2,m_Parameters.CenterOcrModelRegion2.c_str());
		/////////////////////////////////////////////////
		// Number_QiPao=1;
		if (1)
		{

			//pData->m_isFail= false;
			//testItem->m_bFailSubTest = false;
			pData->m_center_y2=Row[0].D();
			pData->m_center_x2=Column[0].D();
		}
		else
		{

			//testItem->m_ErrorMsg = "Error No Find Center";
			//testItem->m_ErrorY = 250;
			//testItem->m_ErrorX = 350;
			//testItem->m_ErrorR = 55;
			//set_color(pData->m_ShowHWindow,"red");
			//disp_region(SelectedRegions_qiPao_extract,pData->m_ShowHWindow);
			//disp_circle(pData->m_ShowHWindow,Row_center,Column_center,85);
		}
		set_color(pData->m_ShowHWindow,"blue");
		disp_obj(Contours,pData->m_ShowHWindow);
		set_color(pData->m_ShowHWindow,"green");
		disp_region(Rectangle1,pData->m_ShowHWindow);
		disp_region(Rectangle2,pData->m_ShowHWindow);
		disp_region(RegionErosion1,pData->m_ShowHWindow);
		disp_region(RegionErosion2,pData->m_ShowHWindow);
		set_color(pData->m_ShowHWindow,"red");
		///////

	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		pData->m_orientationPhi=0;
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
