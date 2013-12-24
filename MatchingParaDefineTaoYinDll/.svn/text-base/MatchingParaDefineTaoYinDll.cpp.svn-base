// CenterRegionDetectDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include <tchar.h>
#include <io.h>
#include "MatchingParaDefineTaoYinDll.h"
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
	m_ProcessName =" center region detect  Dll ";
}

void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="radius_detect")
		m_Parameters.radius_detect= atoi(value.c_str());
		////
	if(parm=="Match_Minscore")
		m_Parameters.Minscore= (float)(atoi(value.c_str())/100.00);//(float)atoi(value.c_str())/10;
	if(parm=="Match_Greediness")
		m_Parameters.Match_Greediness= atof(value.c_str());
	/*if(parm=="thred_low")
		m_Parameters.thred_low = atoi(value.c_str());
	if(parm=="thred_high")
		m_Parameters.thred_high = atoi(value.c_str());

	if(parm=="ARMin")
		m_Parameters.ARMin = atoi(value.c_str());*/
	if(parm=="SHOWOBJECT")
		if (value=="YES")
		{
			ShowObject = true;
		}
		else
		{
			ShowObject = false;
		}
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
	/*//区域读取
	if(!_stricmp(parm.c_str(),"MODEL_REGION_LOAD"))
	{
		m_Parameters.m_region_path_name = value+".reg";
		if (!_access(m_Parameters.m_region_path_name.c_str(),0))
			  read_region(&m_Parameters.RegionDilation_model, m_Parameters.m_region_path_name.c_str());
		else
		{
			wstring msg = _T("Model Region File Not find. Please  the right file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
			m_Parameters.RegionDilation_model=-1;
		}
	}
	//字符区域读取
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
  //适当添加查找模板的匹配参数以及匹配度参数
  //float m_white_para=m_Parameters.thred_high/100.0;
  Hobject Image=pData->m_Image;
 
  Hobject  Circle7, ImageReduced3;

  // Local control variables 

  HTuple   Row_define, Column_define,Angle_define, Score_define;


  //************** 
  HTuple  Row_center=pData->m_center_y;
  HTuple Column_center= pData->m_center_x;
  //HTuple  Row_model_center ;//=pData->m_center_y2
  //HTuple  Column_model_center ;//=pData->m_center_x2
  //HTuple m_model_area;
  try
  {
	  //参数是否正确！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！修改模板提取函数，添加中心点保存(参数不能保存？)
	  //area_center(m_Parameters.RegionDilation_model,&m_model_area,&Row_model_center,&Column_model_center);
	  //缩小区域 匹配图案
	  gen_circle(&Circle7, Row_center, Column_center, m_Parameters.radius_detect);
	  reduce_domain(Image, Circle7, &ImageReduced3);
	  find_shape_model(ImageReduced3, m_Parameters.ModelID, pData->m_orientationPhi3-0.2, pData->m_orientationPhi3+0.2, m_Parameters.Minscore, 1, 0.5,"least_squares", 
		  4, m_Parameters.Match_Greediness, &Row_define, &Column_define, &Angle_define, &Score_define);
	  //
	  Hlong length;
	  tuple_length(Angle_define,&length);
	  if(0==length)
	  {
		  pData->m_isFail =true;
		  testItem->m_bFailSubTest = true;

#ifdef _ENGLISH
		  set_color(pData->m_ShowHWindow,"red");
		  HTuple msg  = HTuple("Matching Fail");
		  set_tposition( pData->m_ShowHWindow, 55, 200);				
		  write_string(pData->m_ShowHWindow,msg);
#else
		  set_color(pData->m_ShowHWindow,"red");
		  HTuple msg  = HTuple("匹配失败");
		  set_tposition( pData->m_ShowHWindow, 55, 200);				
		  write_string(pData->m_ShowHWindow,msg);
#endif
		  return;

	  }
	  //添加判断，满足条件时，再检测//图案中心点不一定是瓶盖中心点
	  //if (Score_define>0.65)
	  //{

		  //set_color(pData->m_ShowHWindow,"green");
		 // disp_obj(ImageEmphasize_no_ocr, pData->m_ShowHWindow);
		 // set_color(pData->m_ShowHWindow,"red");
		 // disp_obj(SelectedRegions_detect, pData->m_ShowHWindow);
		  // 匹配位置
		  pData->m_center_x2=Column_define[0].D();  
		  pData->m_center_y2=Row_define[0].D();
		  pData->m_orientationPhi=Angle_define[0].D();
		  //
	 // }
	 // else
	 // {
		//  pData->m_isFail = true;
		//  testItem->m_bFailSubTest = true;

	  //}
	 if (ShowObject)
	  {
		  set_color(pData->m_ShowHWindow,"green");
		  disp_obj(Circle7, pData->m_ShowHWindow);
		  set_color(pData->m_ShowHWindow,"red");
	  }

  }
  catch (HException &except) 
  {
	  pData->m_isFail = true;
	  testItem->m_bFailSubTest = true;
	  /*//testItem->m_ErrorMsg = except.file;
	  //testItem->m_ErrorMsg += " ";
	  //testItem->m_ErrorMsg += except.line;
	  //testItem->m_ErrorMsg += " ";
	  //testItem->m_ErrorMsg += except.message;
	  testItem->m_ErrorY = 1;
	  testItem->m_ErrorX = 1;
	  testItem->m_ErrorR = 4;*/
	  if (pData->m_isDebug)
	  {
		  set_tposition( pData->m_ShowHWindow, 55, 230);	

#ifdef _ENGLISH
		  write_string(pData->m_ShowHWindow,"MatchingParaDefineDll parameter values error,please re-adjust");
#else
		  write_string(pData->m_ShowHWindow,"MatchingParaDefineDll程序参数设置出错！");
#endif

	  }

  }
}
