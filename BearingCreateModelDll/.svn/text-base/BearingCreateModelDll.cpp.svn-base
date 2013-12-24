// CreateModelDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <io.h>
#include "BearingCreateModelDll.h"
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
	if(parm=="radius_inner")
		m_Parameters.radius_inner= atoi(value.c_str());
	if(parm=="radius_ext")
		m_Parameters.radius_ext= atoi(value.c_str());
	if(parm=="radius_inner_thred")
		m_Parameters.radius_inner_thred= atoi(value.c_str());
	if(parm=="radius_ext_extract_size")
		m_Parameters.radius_ext_extract_size= atoi(value.c_str());
	if(parm=="contrast_low")
		m_Parameters.m_contrast_low= atoi(value.c_str());
	if(parm=="contrast_high")
		m_Parameters.m_contrast_high= atoi(value.c_str());

	if(!_stricmp(parm.c_str(),"MODEL_REGIST_CREATE"))
	{
		m_Parameters.CenterOcrModelName = value+".shm";
	}
	//
	if(!_stricmp(parm.c_str(),"MODEL_OCR_REGION"))
	{
		m_Parameters.CenterOcrModelRegion = value+".reg";
	}
	//
	if(!_stricmp(parm.c_str(),"MODEL_REGIST_PICTURE"))
	{
		m_Parameters.CenterOcrModelPicture = value+".bmp";
	}
	//if(parm=="XMax")
	//	m_Parameters.XMax = atoi(value.c_str());
	//if(parm=="XMin")
	//	m_Parameters.XMin = atoi(value.c_str());
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
	// Local iconic variables 
	Hobject Image=pData->m_Image;
	Hlong m_contrast_low1=m_Parameters.m_contrast_low;
	Hlong m_contrast_high1=m_Parameters.m_contrast_high;


	Hlong m_thred;
	/////////
	if (m_contrast_low1>m_contrast_high1)
	{
		m_thred=m_contrast_low1;
		m_contrast_low1=m_contrast_high1;
		m_contrast_high1=m_thred;
	}
	if (m_Parameters.radius_inner>m_Parameters.radius_ext)
	{
		m_thred=m_Parameters.radius_inner;
		m_Parameters.radius_inner=m_Parameters.radius_ext;
		m_Parameters.radius_ext=m_thred;
	}
	Hobject  Circle5, Circle6, RegionDifference_median,ModelContours;
	Hobject  ImageReduced_median, Region_median, ConnectedRegions_median;
	Hobject  SelectedRegions_median, RegionUnion_median, ImageReduced_median_extract;
	Hobject  ModelImages, ModelRegions;


	// Local control variables 
	HTuple   Mean_median, Deviation_median;
	HTuple  Area_baoChiJia, Row_baoChiJia, Column_baoChiJia;
	HTuple  ModelID, Row2, Column2, Angle2, Score2;
	// Local control variables 
	HTuple  Row=pData->m_center_y;
	HTuple Column= pData->m_center_x;
	// dev_update_off(...); only in hdevelop
	try
	{
		///Row_model_center = 237.659;
		//Column_model_center = 339.212;

		gen_circle(&Circle5, Row, Column,m_Parameters.radius_ext);
		gen_circle(&Circle6, Row, Column,m_Parameters.radius_inner);
		difference(Circle5, Circle6, &RegionDifference_median);
		reduce_domain(Image, RegionDifference_median, &ImageReduced_median);
		intensity(RegionDifference_median, Image, &Mean_median, &Deviation_median);
		fast_threshold(ImageReduced_median, &Region_median, m_Parameters.radius_inner_thred, 255, 1);//Mean_median*1.2
		connection(Region_median, &ConnectedRegions_median);
		select_shape(ConnectedRegions_median, &SelectedRegions_median, "area", "and", m_Parameters.radius_ext_extract_size, 
			99999);
		union1(SelectedRegions_median, &RegionUnion_median);
		area_center(RegionUnion_median, &Area_baoChiJia, &Row_baoChiJia, &Column_baoChiJia);
		//创建模板时 保存区域和区域图片。在提取区域时，因为正常运行时每次都要用，不能使用
		/*if (!_access(m_Parameters.CenterOcrModelRegion.c_str(),0))
		{
			wstring msg = _T("Set Region already Exit.OverWrite or Not?");

			if (MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK||MB_CANCELTRYCONTINUE)==IDOK)
			{
				write_region(RegionUnion_median,m_Parameters.CenterOcrModelRegion.c_str());
			}

		}
		else*/
			write_region(RegionUnion_median,m_Parameters.CenterOcrModelRegion.c_str());

		reduce_domain(Image, RegionUnion_median, &ImageReduced_median_extract);

		//write_image(ImageReduced_median_extract, "bmp", 0, "D:/SLACTST/CH1.101/模板字符区域图片.bmp");
		//
		/*if (!_access(m_Parameters.CenterOcrModelPicture.c_str(),0))
		{
		wstring msg = _T("Set Picture already Exit.OverWrite or Not?");

		if (MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK||MB_CANCELTRYCONTINUE)==IDOK)
		{
		write_image(ImageReduced_median_extract, "bmp", 0,m_Parameters.CenterOcrModelPicture.c_str());
		}

		}
		else
		write_image(ImageReduced_median_extract, "bmp", 0,m_Parameters.CenterOcrModelPicture.c_str());	*/
		//匹配数据
		inspect_shape_model(ImageReduced_median_extract, &ModelImages, &ModelRegions, 1, 
			25);
		create_shape_model(ImageReduced_median_extract, 4, 0, HTuple(360).Rad(), "auto", 
			"auto", "use_polarity", m_contrast_high1, m_contrast_low1, &ModelID);
		find_shape_model(Image, ModelID, 0, HTuple(360).Rad(), 0.5, 1, 0.5, "least_squares", 
			0, 0.9, &Row2, &Column2, &Angle2, &Score2);

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
		//*查看模板提取效果
		set_shape_model_origin(ModelID, -Row_baoChiJia, -Column_baoChiJia);
		get_shape_model_contours(&ModelContours, ModelID, 1);
		/////////////////////////////////////////////////*/
		// Number_QiPao=1;
		if (1)
		{

			//pData->m_isFail= false;
			//testItem->m_bFailSubTest = false;
			pData->m_center_y2=Row_baoChiJia[0].D();
			pData->m_center_x2=Column_baoChiJia[0].D();
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
		disp_obj(ModelContours,pData->m_ShowHWindow);
		set_color(pData->m_ShowHWindow,"green");
		disp_region(RegionUnion_median,pData->m_ShowHWindow);
		disp_region(Circle5,pData->m_ShowHWindow);
		disp_region(Circle6,pData->m_ShowHWindow);
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
