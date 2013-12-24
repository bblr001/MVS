// CenterRegionDetectDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <io.h>
#include "BearingBaoChiJiaDetectDll.h"
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
	m_ProcessName =" center region detect  Dll ";
}

void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="radius_inner")
		m_Parameters.radius_inner= atoi(value.c_str());
	if(parm=="radius_ext")
		m_Parameters.radius_ext= atoi(value.c_str());

	//if(parm=="thred_low")
	//	m_Parameters.thred_low = atoi(value.c_str());
	//if(parm=="thred_high")
	//	m_Parameters.thred_high = atoi(value.c_str());
////
	if(parm=="erosion_size")
		m_Parameters.erosion_size= atof(value.c_str());
	if(parm=="enhance_size")
		m_Parameters.radius_ext_empha_size= atoi(value.c_str());
	if(parm=="enhance_xishu")
		m_Parameters.radius_inner2_enhance= atof(value.c_str());
	if(parm=="extract_thred")
		m_Parameters.radius_ext2_thred= atoi(value.c_str());
	if(parm=="ARMin")
		m_Parameters.ARMin = atoi(value.c_str());
  //**************

	if(!_stricmp(parm.c_str(),"MODEL_REGIST_LOAD"))
	{
		m_Parameters.m_model_path_name = value+".shm";
		if (!_access(m_Parameters.m_model_path_name.c_str(),0))
			read_shape_model(m_Parameters.m_model_path_name.c_str(),&m_Parameters.ModelID);
		else
		{
			wstring msg = _T("Model File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.ModelID=-1;
		}
	}
	//区域读取
	if(!_stricmp(parm.c_str(),"MODEL_REGION_LOAD"))
	{
		m_Parameters.m_region_path_name = value+".reg";
		if (!_access(m_Parameters.m_region_path_name.c_str(),0))
			  read_region(&m_Parameters.RegionUnion_median, m_Parameters.m_region_path_name.c_str());
		else
		{
			wstring msg = _T("Model Region File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.RegionUnion_median=-1;
		}
	}
	/*//字符图片读取
	if(!_stricmp(parm.c_str(),"MODEL_REGION_PICTURE_LOAD"))
	{
		m_Parameters.m_picture_path_name = value+".bmp";
		if (!_access(m_Parameters.m_picture_path_name.c_str(),0))
		read_image(&m_Parameters.ImageReduced_icon, m_Parameters.m_picture_path_name.c_str());
		else
		{
			wstring msg = _T("Model Region Picture File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.ImageReduced_icon=-1;
		}
	}*/
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	Hlong m_radius_inner=m_Parameters.radius_inner;
	Hlong m_radius_ext=m_Parameters.radius_ext;

	Hlong m_thred;

	//
	if (m_radius_inner>m_radius_ext)
	{
		m_thred=m_radius_inner;
		m_radius_inner=m_radius_ext;
		m_radius_ext=m_thred;
	}
	Hobject Image=pData->m_Image;
	// Local iconic variables 
	Hobject  Circle, ImageReduced,Circle_inner;
	Hobject  RegionAffineTrans, RegionErosion, ImageEmphasize;
	Hobject  Region_BaoChiJia_test, Region_BaoChiJia_test2, ConnectedRegions;
	Hobject  SelectedRegions;


	// Local control variables 
	HTuple  Row_baoChiJia, Column_baoChiJia;
	HTuple  Row3, Column3, Angle3, Score3;
	HTuple  HomMat2D, Mean_BaoChiJia, Deviation_BaoChiJia, Number;


	//************** 
	HTuple  Row=pData->m_center_y;
	HTuple Column= pData->m_center_x;
	HTuple m_model_area;
	try
	{


		//read_shape_model("X:/个人资料夹/张磊/应用资料/bearing/bearing_match.shm", &m_Parameters.ModelID);
		//read_region(&m_Parameters.RegionUnion_median, "X:/个人资料夹/张磊/应用资料/bearing/bearing_region.reg");
		//疑似 读取失败，导致匹配不成功。路径不对，读取文件、数据错误。
		//*********************************** //*区域中心可计算
		area_center(m_Parameters.RegionUnion_median,&m_model_area,&Row_baoChiJia,&Column_baoChiJia);
		gen_circle(&Circle, pData->m_center_y, pData->m_center_x, m_radius_ext);
		gen_circle(&Circle_inner, pData->m_center_y, pData->m_center_x, m_radius_inner);
		reduce_domain(Image, Circle, &ImageReduced);
		//**************************************


		find_shape_model(ImageReduced, m_Parameters.ModelID, 0, HTuple(360).Rad(), 0.5, 1, 0.5, "least_squares", 
			0, 0.9, &Row3, &Column3, &Angle3, &Score3);
		////////////////////////////////////////////////
		if (Score3>0.65)
		{
			vector_angle_to_rigid(Row_baoChiJia, Column_baoChiJia, 0, Row3, Column3, Angle3, 
				&HomMat2D);
			affine_trans_region(m_Parameters.RegionUnion_median, &RegionAffineTrans, HomMat2D, "false");
			//************

			//*****************
			erosion_circle(RegionAffineTrans, &RegionErosion, m_Parameters.erosion_size);
			reduce_domain(Image, RegionErosion, &ImageReduced);

			emphasize(ImageReduced, &ImageEmphasize, m_Parameters.radius_ext_empha_size, m_Parameters.radius_ext_empha_size, m_Parameters.radius_inner2_enhance);
			intensity(RegionErosion, Image, &Mean_BaoChiJia, &Deviation_BaoChiJia);
			fast_threshold(ImageEmphasize, &Region_BaoChiJia_test, 0,m_Parameters.radius_ext2_thred , 
				1);//Mean_BaoChiJia*0.6

			//threshold (ImageReduced, Region_BaoChiJia_test2, 0, Mean_BaoChiJia*0.8)

			connection(Region_BaoChiJia_test, &ConnectedRegions);
			select_shape(ConnectedRegions, &SelectedRegions, "area", "and", m_Parameters.ARMin, 99999);

			count_obj(SelectedRegions, &Number);
			if (Number<=0)
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

			}
			set_color(pData->m_ShowHWindow,"red");

			disp_obj(SelectedRegions, pData->m_ShowHWindow);
			set_color(pData->m_ShowHWindow,"green");
			disp_obj(Circle, pData->m_ShowHWindow);
			disp_obj(Circle_inner, pData->m_ShowHWindow);
			disp_obj(RegionAffineTrans, pData->m_ShowHWindow);
			set_color(pData->m_ShowHWindow,"red");
			//copy_image(ImageEmphasize,&(pData->m_TestRegist1));//test
		}
		else
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;

		}


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
