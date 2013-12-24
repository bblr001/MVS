// CenterCapDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <io.h>
#include "CenterCapExtDll.h"
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
	ShowObject=false;
	HException::InstallHHandler(&MyHalconExceptionHandler);
	m_ProcessName ="define center of crown-cap Dll ";
}

void CDoProcess::SetParmeter(string parm,string value)
{

	if(parm=="XMin")
		m_Parameters.XMin = atoi(value.c_str());
	if(parm=="XMax")
		m_Parameters.XMax = atoi(value.c_str());
	if(parm=="YMin")
		m_Parameters.YMin = atoi(value.c_str());
	if(parm=="YMax")
		m_Parameters.YMax = atoi(value.c_str());
	if(parm=="RADIUS")
	{
		m_Parameters.m_radius= atoi(value.c_str());
	}
	//
	if(parm=="OFFSET_ROW")
		m_Parameters.OffSet_Row = atoi(value.c_str());
	if(parm=="OFFSET_COLUMN")
		m_Parameters.OffSet_Column = atoi(value.c_str());
	if(parm=="Greediness")
		m_Parameters.Greediness = atof(value.c_str());
	if(parm=="MinScore")
		m_Parameters.MinScore =atoi(value.c_str())/100.0;

	// 隐藏变量

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
	 HTuple  DxfStatus;
	if(!_stricmp(parm.c_str(),"MODEL_XLD_LOAD"))
	{
		m_Parameters.m_xld_path_name = value+".dxf";
		if (!_access(m_Parameters.m_xld_path_name.c_str(),0))
			read_contour_xld_dxf(&m_Parameters.Model_XLD_Contours,  m_Parameters.m_xld_path_name.c_str(), HTuple(), 
			HTuple(), &DxfStatus);
		else
		{
			wstring msg = _T("Model Region File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.Model_XLD_Contours=-1;
		}
	}
	//字符区域读取
	if(!_stricmp(parm.c_str(),"REGION_MODEL_CENTER_LOAD"))
	{
		m_Parameters.m_tuple_path_name = value+".tup";
		if (!_access(m_Parameters.m_tuple_path_name.c_str(),0))
			read_tuple( m_Parameters.m_tuple_path_name.c_str(),&m_Parameters.Region_Model_center);
		else
		{
			wstring msg = _T("Model Region Picture File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.Region_Model_center=-1;
		}
	}
	//////////////////////////////
	if(parm=="SHOWOBJECT")
		if (value=="YES")
		{
			ShowObject = true;
		}
		else
		{
			ShowObject = false;
		}
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	Hobject  Image2, Rectangle2, ImageReduced2;
	Hobject  ImageMedian2, ContoursAffinTrans, Circle3;


	// Local control variables 
	HTuple  Row_M, Column_M, Angle_M, Score_M, HomMat2D;
	HTuple  Define_Center_Row, Define_Center_Column;

	try
	{
		Hobject Image2=pData->m_Image;
		//////////////////////////////////////////////////

		gen_rectangle1(&Rectangle2, m_Parameters.YMin, m_Parameters.XMin, m_Parameters.YMax, m_Parameters.XMax);
		reduce_domain(Image2, Rectangle2, &ImageReduced2);

		if(ShowObject)
		{
			disp_obj(Rectangle2,pData->m_ShowHWindow);
		}
		//median_image (ImageReduced2, ImageMedian2, 'circle', 1, 'mirrored')
		find_shape_model(ImageReduced2,m_Parameters.ModelID , -0.49, 0.49, 0.5, 1, 0.5, "least_squares", 
			4, m_Parameters.Greediness, &Row_M, &Column_M, &Angle_M, &Score_M);
		if (0 != (Score_M>m_Parameters.MinScore))
		{
			vector_angle_to_rigid(m_Parameters.Region_Model_center[2], m_Parameters.Region_Model_center[3], 
				0, Row_M, Column_M, Angle_M, &HomMat2D);
			affine_trans_point_2d(HomMat2D, m_Parameters.Region_Model_center[0], m_Parameters.Region_Model_center[1], 
				&Define_Center_Row, &Define_Center_Column);
			//
			tuple_add(Define_Center_Row,m_Parameters.OffSet_Row, &Define_Center_Row);
			tuple_add(Define_Center_Column,m_Parameters.OffSet_Column, &Define_Center_Column);
			//
			//gen_circle(&Circle3, Define_Center_Row, Define_Center_Column, m_Parameters.m_radius);
			////
			pData->m_center_x=Define_Center_Column[0].D();  
			pData->m_center_y=Define_Center_Row[0].D();
			pData->r_real=m_Parameters.m_radius;


			if(ShowObject)
			{
				set_color(pData->m_ShowHWindow,"red");
				disp_circle(pData->m_ShowHWindow,pData->m_center_y,pData->m_center_x,pData->r_real);
				affine_trans_contour_xld(m_Parameters.Model_XLD_Contours, &ContoursAffinTrans, HomMat2D);
				set_color(pData->m_ShowHWindow,"green");
				disp_xld(ContoursAffinTrans,pData->m_ShowHWindow);
				set_color(pData->m_ShowHWindow,"red");
			}

		}
		else
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			pData->m_center_x=350;
			pData->m_center_y=250;
			pData->r_real=105;
			//testItem->m_ErrorMsg = "Error No Find Center";
			testItem->m_ErrorY = 250;
			testItem->m_ErrorX = 350;
			testItem->m_ErrorR = 55;
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
