// CenterRegionDetectDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <io.h>
#include "BearingNeiWaiJingDetectDll.h"
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
	//if(parm=="thred_low")
	//	m_Parameters.thred_low = atoi(value.c_str());
	//if(parm=="thred_high")
	//	m_Parameters.thred_high = atoi(value.c_str());
	////
	if(parm=="enhance_size")
		m_Parameters.radius_ext_empha_size= atoi(value.c_str());
	if(parm=="enhance_xishu")
		m_Parameters.radius_inner2_enhance= atof(value.c_str());
	if(parm=="extract_thred")
		m_Parameters.radius_ext2_thred= atoi(value.c_str());
	if(parm=="ARMin")
		m_Parameters.ARMin = atoi(value.c_str());
	//
	if(parm=="enhance_size2")
		m_Parameters.radius_ext_empha_size2= atoi(value.c_str());
	if(parm=="enhance_xishu2")
		m_Parameters.radius_inner2_enhance2= atof(value.c_str());
	if(parm=="extract_thred2")
		m_Parameters.radius_ext2_thred2= atoi(value.c_str());
	if(parm=="ARMin2")
		m_Parameters.ARMin2 = atoi(value.c_str());
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
	if(!_stricmp(parm.c_str(),"MODEL_MODEL_LOAD"))
	{
		m_Parameters.m_region_path_name = value+".reg";
		if (!_access(m_Parameters.m_region_path_name.c_str(),0))
			read_region(&m_Parameters.RegionModel, m_Parameters.m_region_path_name.c_str());
		else
		{
			wstring msg = _T("Model Region File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.RegionModel=-1;
		}
	}
	//区域读取
	if(!_stricmp(parm.c_str(),"MODEL_REGION1_LOAD"))
	{
		m_Parameters.m_region1_path_name = value+".reg";
		if (!_access(m_Parameters.m_region1_path_name.c_str(),0))
			read_region(&m_Parameters.RegionUnion1, m_Parameters.m_region1_path_name.c_str());
		else
		{
			wstring msg = _T("Model Region File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.RegionUnion1=-1;
		}
	}
	//区域读取2
	if(!_stricmp(parm.c_str(),"MODEL_REGION2_LOAD"))
	{
		m_Parameters.m_region2_path_name = value+".reg";
		if (!_access(m_Parameters.m_region2_path_name.c_str(),0))
			read_region(&m_Parameters.RegionUnion2, m_Parameters.m_region2_path_name.c_str());
		else
		{
			wstring msg = _T("Model Region File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.RegionUnion2=-1;
		}
	}
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	Hlong m_thred;

	//
	Hobject Image=pData->m_Image;
	// Local iconic variables 
	Hobject  Circle, ImageReduced1,ImageReduced2;
	Hobject  RegionAffineTrans,RegionAffineTrans1,RegionAffineTrans2, RegionErosion, ImageEmphasize;
	Hobject  Region_BaoChiJia_test, Region_BaoChiJia_test2, ConnectedRegions;
	Hobject  SelectedRegions, SelectedRegions1,SelectedRegions2;


	// Local control variables 
	HTuple  Row_baoChiJia, Column_baoChiJia;
	HTuple  Row3, Column3, Angle3, Score3;
	HTuple  HomMat2D, Mean_BaoChiJia, Deviation_BaoChiJia, Number1,Number2;


	//************** 
	//HTuple  Row=pData->m_center_y;
	//HTuple Column= pData->m_center_x;
	HTuple m_model_area;
	try
	{
		//
		read_shape_model(m_Parameters.m_model_path_name.c_str(),&m_Parameters.ModelID);
		read_region(&m_Parameters.RegionModel, m_Parameters.m_region_path_name.c_str());
		read_region(&m_Parameters.RegionUnion1, m_Parameters.m_region1_path_name.c_str());
		read_region(&m_Parameters.RegionUnion2, m_Parameters.m_region2_path_name.c_str());

		//

		find_shape_model(Image, m_Parameters.ModelID, 0, HTuple(360).Rad(), 0.5, 1, 0.5, "least_squares", 
			0, 0.9, &Row3, &Column3, &Angle3, &Score3);
		////////////////////////////////////////////////
		if (Score3>0.65)
		{

			//*********************************** //*区域中心可计算
			area_center(m_Parameters.RegionModel,&m_model_area,&Row_baoChiJia,&Column_baoChiJia);
			vector_angle_to_rigid(Row_baoChiJia, Column_baoChiJia, 0, Row3, Column3, Angle3, 
				&HomMat2D);
			//模板图像其它检测区域，直接使用参数进行处理//
			pData->m_center_y2=Row_baoChiJia[0].D();
			pData->m_center_x2=Column_baoChiJia[0].D();
			pData->m_center_y3=Row3[0].D();
			pData->m_center_x3=Column3[0].D();
			pData->m_orientationPhi3=Angle3[0].D();
			////
			affine_trans_region(m_Parameters.RegionModel, &RegionAffineTrans, HomMat2D, "false");
			affine_trans_region(m_Parameters.RegionUnion1, &RegionAffineTrans1, HomMat2D, "false");
			affine_trans_region(m_Parameters.RegionUnion2, &RegionAffineTrans2, HomMat2D, "false");
			//************
			reduce_domain(Image, RegionAffineTrans1, &ImageReduced1);
			reduce_domain(Image, RegionAffineTrans2, &ImageReduced2);
			///////////////////////////////////////////

			emphasize(ImageReduced1, &ImageEmphasize, m_Parameters.radius_ext_empha_size, m_Parameters.radius_ext_empha_size, m_Parameters.radius_inner2_enhance);
			intensity(RegionErosion, Image, &Mean_BaoChiJia, &Deviation_BaoChiJia);
			fast_threshold(ImageEmphasize, &Region_BaoChiJia_test, 0,m_Parameters.radius_ext2_thred , 
				1);//Mean_BaoChiJia*0.6

			//threshold (ImageReduced, Region_BaoChiJia_test2, 0, Mean_BaoChiJia*0.8)

			connection(Region_BaoChiJia_test, &ConnectedRegions);
			select_shape(ConnectedRegions, &SelectedRegions1, "area", "and", m_Parameters.ARMin, 99999);

			count_obj(SelectedRegions1, &Number1);
			//////////////////////////////////////////////
			///////////////////////////////////////////

			emphasize(ImageReduced2, &ImageEmphasize, m_Parameters.radius_ext_empha_size2, m_Parameters.radius_ext_empha_size2, m_Parameters.radius_inner2_enhance2);
			intensity(RegionErosion, Image, &Mean_BaoChiJia, &Deviation_BaoChiJia);
			fast_threshold(ImageEmphasize, &Region_BaoChiJia_test, 0,m_Parameters.radius_ext2_thred2 , 
				1);//Mean_BaoChiJia*0.6

			//threshold (ImageReduced, Region_BaoChiJia_test2, 0, Mean_BaoChiJia*0.8)

			connection(Region_BaoChiJia_test, &ConnectedRegions);
			select_shape(ConnectedRegions, &SelectedRegions2, "area", "and", m_Parameters.ARMin2, 99999);

			count_obj(SelectedRegions2, &Number2);
			///////////////////////////////////////////

			if ((Number1<=0)&&(Number2<=0))
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
			set_color(pData->m_ShowHWindow,"green");
			disp_obj(RegionAffineTrans, pData->m_ShowHWindow);
			disp_obj(RegionAffineTrans1, pData->m_ShowHWindow);
			disp_obj(RegionAffineTrans2, pData->m_ShowHWindow);
			set_color(pData->m_ShowHWindow,"red");
			disp_obj(SelectedRegions1, pData->m_ShowHWindow);
			disp_obj(SelectedRegions2, pData->m_ShowHWindow);
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
