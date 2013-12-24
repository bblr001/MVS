// CircleExtDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "BearingTryDetectDll.h"
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
	if(parm=="radius_inner")
		m_Parameters.radius_inner_mean_size= atoi(value.c_str());
	if(parm=="radius_ext")
		m_Parameters.radius_ext_empha_size= atoi(value.c_str());
	if(parm=="radius_inner2")
		m_Parameters.radius_inner2_enhance= atof(value.c_str());
	if(parm=="radius_ext2")
		m_Parameters.radius_ext2_thred= atoi(value.c_str());
	if(parm=="dyn_dark")
		m_Parameters.dyn_dark_thred= atoi(value.c_str());
	if(parm=="dyn_light")
		m_Parameters.dyn_light_thred= atoi(value.c_str());
	//区域读取
	if(!_stricmp(parm.c_str(),"MODEL_REGION_LOAD"))
	{
		m_Parameters.m_region_path_name = value+".reg";
	}
	//if(parm=="XMax")
	//	m_Parameters.XMax = atoi(value.c_str());
	if(parm=="ARMin")
		m_Parameters.ARMin = atoi(value.c_str());
	//if(parm=="YMax")
	//	m_Parameters.YMax = atoi(value.c_str());
	//if(parm=="YMin")
	//	m_Parameters.YMin = atoi(value.c_str());
	//if(parm=="RMax")
	//	m_Parameters.RMax = atoi(value.c_str());
	//if(parm=="RMin")
	//	m_Parameters.RMin = atoi(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	Hlong m_thred;

	// dev_update_off(...); only in hdevelop
	//Hobject Image=pData->m_Image;
	/////////
    Hobject Image=pData->m_Image;
	// Local iconic variables 
	Hobject  Region_draw, ImageReduced_draw;
	Hobject  ImageMean_draw, ImageEmphasize_draw, RegionDynThresh_draw;
	Hobject  Region_dark, RegionUnion_dark, ConnectedRegions,RegionDynThresh_draw_light;
	Hobject  SelectedRegions;


	// Local control variables 
	HTuple  Number;
	// Local control variables 
	try
	{
		read_region(&Region_draw, m_Parameters.m_region_path_name.c_str());
		//draw_region(&Region_draw, pData->m_ShowHWindow);
		reduce_domain(Image, Region_draw, &ImageReduced_draw);

		mean_image(ImageReduced_draw, &ImageMean_draw, m_Parameters.radius_inner_mean_size, m_Parameters.radius_inner_mean_size);
		emphasize(ImageReduced_draw, &ImageEmphasize_draw, m_Parameters.radius_ext_empha_size, m_Parameters.radius_ext_empha_size, m_Parameters.radius_inner2_enhance);
		      dyn_threshold(ImageReduced_draw, ImageMean_draw, &RegionDynThresh_draw, m_Parameters.dyn_dark_thred, "dark");
		dyn_threshold(ImageReduced_draw, ImageMean_draw, &RegionDynThresh_draw_light, m_Parameters.dyn_light_thred, "light");
		union2(RegionDynThresh_draw, RegionDynThresh_draw_light, &RegionDynThresh_draw);
		fast_threshold(ImageEmphasize_draw, &Region_dark, 0, m_Parameters.radius_ext2_thred, 1);
		union2(RegionDynThresh_draw, Region_dark, &RegionUnion_dark);
		connection(RegionUnion_dark, &ConnectedRegions);
		select_shape(ConnectedRegions, &SelectedRegions, "area", "and", m_Parameters.ARMin, 99999);

		count_obj(SelectedRegions, &Number);
		/////////////////////////////////////////////////
		// Number_QiPao=1;
		if ((Number<=0))
		{
			;
			//pData->m_isFail= false;
			//testItem->m_bFailSubTest = false;
		}
		else
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "Error No Find Center";
			//testItem->m_ErrorY = 250;
			//testItem->m_ErrorX = 350;
			//testItem->m_ErrorR = 55;
			set_color(pData->m_ShowHWindow,"red");
			disp_region(SelectedRegions,pData->m_ShowHWindow);

		}	
		set_color(pData->m_ShowHWindow,"green");
		disp_region(Region_draw,pData->m_ShowHWindow);
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
