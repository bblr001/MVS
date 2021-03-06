// CenterDllHS.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"



#include "CenterDllHS.h"
#include "..\Inc\MData.h"



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
	//m_ProcessName ="QinanHuanTest";
	HException::InstallHHandler(&MyHalconExceptionHandler);
}


void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="SHOWOBJECT")
		if (value=="YES")
		{
			ShowObject = true;
		}
		else
		{
			ShowObject = false;
		}
	if(parm=="LongAxis")
		m_Parameters.LongAxis = atoi(value.c_str());
	if(parm=="ShortAxis")
		m_Parameters.ShortAxis = atoi(value.c_str());

	if(parm=="Graylowerlimit")
		m_Parameters.Graylowerlimit = atoi(value.c_str());
	if(parm=="OutlierRemover")
		m_Parameters.OutlierRemover = atoi(value.c_str());

	if(parm=="XMax")
		m_Parameters.XMax = atoi(value.c_str());
	if(parm=="XMin")
		m_Parameters.XMin = atoi(value.c_str());
	if(parm=="YMax")
		m_Parameters.YMax = atoi(value.c_str());
	if(parm=="YMin")
		m_Parameters.YMin = atoi(value.c_str());
	if(parm=="RMax")
		m_Parameters.RMax = atoi(value.c_str());
	if(parm=="RMin")
		m_Parameters.RMin = atoi(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{
		Hobject  Ellipse, ImageReduced, EllipseObj,threshed;
		Hobject  RegionFillUp, RegionOpening, RegionUnion;

	  // Local control variables 
	  HTuple  Width, Height, WindowHandle; 
	  double  CenterColumn, CenterRadius,CenterRow;

	  get_image_size(pData->m_Image, &Width, &Height);
		  
	  gen_ellipse(&EllipseObj, Height/2, Width/2, 0, m_Parameters.LongAxis, m_Parameters.ShortAxis);
	  if (ShowObject&&pData->m_isDebug)
	  {
		  set_color(pData->m_ShowHWindow,"yellow");	
		  disp_obj(EllipseObj,pData->m_ShowHWindow);
	  }
	  reduce_domain(pData->m_Image, EllipseObj, &ImageReduced);

	  //===================================================================
	  //*90和255都是可调参数，一个是灰度阀值下限Graylowerlimit，另一个为上限GrayUpperLimit
	  threshold(ImageReduced, &threshed, m_Parameters.Graylowerlimit, 255);
	  fill_up(threshed, &RegionFillUp);
	  union1(RegionFillUp, &RegionUnion);
	  opening_circle(RegionUnion, &RegionOpening, m_Parameters.OutlierRemover+0.5);
	  smallest_circle(RegionOpening, &CenterRow, &CenterColumn, &CenterRadius);

	  Hobject circle;
	  
	  if ((m_Parameters.XMin<CenterColumn)&&(CenterColumn<m_Parameters.XMax)&&(m_Parameters.YMin<CenterRow)&&(CenterRow<m_Parameters.YMax)&&(CenterRadius<m_Parameters.RMax)&&(CenterRadius>m_Parameters.RMin))
		{
			pData->m_center_x=CenterColumn;
			pData->m_center_y=CenterRow;
			pData->r_real=CenterRadius;

			set_color(pData->m_ShowHWindow,"cyan");
			gen_circle(&circle, pData->m_center_y, pData->m_center_x, pData->r_real);
			disp_obj(circle,pData->m_ShowHWindow);
		}
	else
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			pData->m_center_x=50;
			pData->m_center_y=50;
			pData->r_real=40;

			set_color(pData->m_ShowHWindow,"red");
			gen_circle(&circle, pData->m_center_y, pData->m_center_x, pData->r_real);
			disp_obj(circle,pData->m_ShowHWindow);

			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"green");
				set_tposition( pData->m_ShowHWindow,5, 145);
				#ifdef _ENGLISH
								write_string(pData->m_ShowHWindow,"Fitted shell center not match the qualifications");
				#else
								write_string(pData->m_ShowHWindow,"拟合得到的圆的中心坐标及半径与限定条件不符");
				#endif

			}
		}

	//if (pData->m_isDebug&&ShowObject)
	//{
	//	set_color(pData->m_ShowHWindow,"red");
	//	//disp_circle(pData->m_ShowHWindow,pData->m_center_y,pData->m_center_x,pData->r_real);
	//	Hobject circle,ContCircle;
	//	gen_circle(&circle, pData->m_center_y, pData->m_center_x, pData->r_real);
	//	//gen_circle_contour_xld (&ContCircle, pData->m_center_y, pData->m_center_x, pData->r_real, 0, 6.28318, "positive", 1);
	//	//gen_region_contour_xld (ContCircle, &circle, "filled");

	//	disp_obj(circle,pData->m_ShowHWindow);
	//}

	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"CenterDLLHS parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"CenterDLLHS程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		pData->m_center_x=50;
		pData->m_center_y=50;
		pData->r_real=40;
	}

}
