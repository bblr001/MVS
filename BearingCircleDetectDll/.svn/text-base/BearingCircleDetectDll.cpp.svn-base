// CircleExtDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "BearingCircleDetectDll.h"
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
		m_Parameters.radius_inner= atoi(value.c_str());
	if(parm=="radius_ext")
		m_Parameters.radius_ext= atoi(value.c_str());
	if(parm=="radius_inner2")
		m_Parameters.radius_inner2= atoi(value.c_str());
	if(parm=="radius_ext2")
		m_Parameters.radius_ext2= atoi(value.c_str());
	////
	if(parm=="enhance_size")
		m_Parameters.radius_ext_empha_size= atoi(value.c_str());
	if(parm=="enhance_xishu")
		m_Parameters.radius_inner2_enhance= atof(value.c_str());
	if(parm=="extract_thred")
		m_Parameters.radius_ext2_thred= atoi(value.c_str());
	if(parm=="ARMin")
		m_Parameters.ARMin = atoi(value.c_str());
	//**************
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
	Hlong m_radius_inner=m_Parameters.radius_inner;
	Hlong m_radius_ext=m_Parameters.radius_ext;

	Hlong m_thred;

	// dev_update_off(...); only in hdevelop
	//Hobject Image=pData->m_Image;
	/////////
	if (m_Parameters.radius_inner>m_Parameters.radius_ext)
	{
		m_thred=m_Parameters.radius_inner;
		m_Parameters.radius_inner=m_Parameters.radius_ext;
		m_Parameters.radius_ext=m_thred;
	}
	if (m_Parameters.radius_inner2>m_Parameters.radius_ext2)
	{
		m_thred=m_Parameters.radius_inner2;
		m_Parameters.radius_inner2=m_Parameters.radius_ext2;
		m_Parameters.radius_ext2=m_thred;
	}
  // Local iconic variables 
  Hobject Image=pData->m_Image;
  // Local iconic variables 
  Hobject   Circle1, Circle2, RegionDifference_ext;
  Hobject  Circle3, Circle4, RegionDifference_inner, ImageReduced_ext;
  Hobject  ImageReduced_inner, ImageEmphasize_inner, ImageEmphasize_ext;
  Hobject  Region_ext, Region_inner, RegionUnion, ConnectedRegions;
  Hobject  SelectedRegions;


  // Local control variables 
  HTuple   Mean_ext, Deviation_ext;
  HTuple  Mean_inner, Deviation_inner, Number;



  // Local control variables 
  try
  {

	   HTuple  Row=pData->m_center_y;
	  HTuple Column= pData->m_center_x;
	  if (pData->m_isFail )
	  {
	  Row=250;
	  Column=330;
	  }
	  gen_circle(&Circle1, Row, Column, m_Parameters.radius_ext);
	  gen_circle(&Circle2, Row, Column, m_Parameters.radius_inner);
	  difference(Circle1, Circle2, &RegionDifference_ext);
	  gen_circle(&Circle3, Row, Column,m_Parameters.radius_ext2);
	  gen_circle(&Circle4, Row, Column, m_Parameters.radius_inner2);
	  difference(Circle3, Circle4, &RegionDifference_inner);
	  //////////////////////////
	  set_color(pData->m_ShowHWindow,"green");
	  disp_region(Circle1,pData->m_ShowHWindow);
	  disp_region(Circle2,pData->m_ShowHWindow);
	  disp_region(Circle3,pData->m_ShowHWindow);
	  disp_region(Circle4,pData->m_ShowHWindow);
	  set_color(pData->m_ShowHWindow,"red");
	  ///////////////////////////////
	  reduce_domain(Image, RegionDifference_ext, &ImageReduced_ext);
	  reduce_domain(Image, RegionDifference_inner, &ImageReduced_inner);

	  //*端面检测**************

	  emphasize(ImageReduced_inner, &ImageEmphasize_inner, m_Parameters.radius_ext_empha_size, m_Parameters.radius_ext_empha_size, m_Parameters.radius_inner2_enhance);
	  emphasize(ImageReduced_ext, &ImageEmphasize_ext, m_Parameters.radius_ext_empha_size, m_Parameters.radius_ext_empha_size, m_Parameters.radius_inner2_enhance);

	  intensity(RegionDifference_ext, Image, &Mean_ext, &Deviation_ext);
	  intensity(RegionDifference_inner, Image, &Mean_inner, &Deviation_inner);
	  threshold(ImageEmphasize_ext, &Region_ext, 0,m_Parameters.radius_ext2_thred );//Mean_ext-30
	  fast_threshold(ImageReduced_inner, &Region_inner, 0,m_Parameters.radius_ext2_thred , 1);//Mean_inner-30
	  union2(Region_ext, Region_inner, &RegionUnion);
	  connection(RegionUnion, &ConnectedRegions);
	  select_shape(ConnectedRegions, &SelectedRegions, "area", "and", m_Parameters.ARMin, 99999);
	  count_obj(SelectedRegions, &Number);
	  /////////////////////////////////////////////////*/
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
		  //disp_circle(pData->m_ShowHWindow,Row,Column,85);
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
