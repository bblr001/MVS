// CenterHC.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"



#include "CenterHC.h"
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
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.LongAxis = nValue;
		return;
	}
	if(parm=="ShortAxis")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.ShortAxis = nValue;
		return;
	}

	if(parm=="Thred_Contrast")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.m_Contrast = nValue;
		return;
	}
	if(parm=="Select_Shape_Size")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.Select_Shape_Size = nValue;
		return;
	}

	if(parm=="XMax")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.XMax = nValue;
		return;
	}
	if(parm=="XMin")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.XMin = nValue;
		return;
	}
	if(parm=="YMax")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.YMax = nValue;
		return;
	}
	if(parm=="YMin")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.YMin = nValue;
		return;
	}
	if(parm=="RMax")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.RMax = nValue;
		return;
	}
	if(parm=="RMin")
	{
		int nValue =  atoi(value.c_str());
		m_Parameters.RMin = nValue;
		return;
	}
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{
		Hobject   FindImage,ImageReduced,EllipseObj;
		Hobject  ModelRegions, ConnectedRegions, SelectedRegions,ModelImages,SelectedRegionsSize,RegionUnion;
		Hlong Contrast = m_Parameters.m_Contrast;

		HTuple Row2, Column2, Radius2;

		Hobject regional_Internal,regional_Out;


		get_image_size (pData->m_Image, &Column2, &Row2);
		gen_ellipse(&EllipseObj, Row2/2, Column2/2, 0, m_Parameters.LongAxis, m_Parameters.ShortAxis);
		if (ShowObject&&pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"yellow");	
			disp_obj(EllipseObj,pData->m_ShowHWindow);
		}
		reduce_domain(pData->m_Image, EllipseObj, &ImageReduced);
		inspect_shape_model(ImageReduced, &ModelImages, &ModelRegions, 1, Contrast);
		connection(ModelRegions, &ConnectedRegions);
		//**==============================================================
		//	**选择区域这条更改，原来默认是700，现在我想改成可调的，我现在就设的40
		select_shape(ConnectedRegions, &SelectedRegionsSize, "area", "and", m_Parameters.Select_Shape_Size, 99999);

		//	** 添加这句union1
		union1(SelectedRegionsSize, &RegionUnion);

		Hlong TempNumber;		  

		count_obj(RegionUnion,&TempNumber);

		  if (TempNumber<1)
		  {  
			  pData->m_isFail = true;
			  testItem->m_bFailSubTest = true;

			  if (pData->m_isDebug)
			  {
				  set_color(pData->m_ShowHWindow,"green");
				  set_tposition( pData->m_ShowHWindow,120, 0);
				#ifdef _ENGLISH
							  write_string(pData->m_ShowHWindow,"Shell center not found");
				#else
							  write_string(pData->m_ShowHWindow,"圆中心未找到");
				#endif
			  }
			  //pData->m_center_x=50;
			  //pData->m_center_y=50;
			  //pData->r_real=40;
			  //return;
		  }
		  
		//*==============================================================
		double  CenterRow, CenterColumn, CenterRadius;
		smallest_circle(RegionUnion, &CenterRow, &CenterColumn, &CenterRadius);


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

			//return;
			}
		}
		//if (pData->m_isDebug&&ShowObject)
		//{
		//	set_color(pData->m_ShowHWindow,"green");
		//	Hobject circle;
		//	gen_circle(&circle, pData->m_center_y, pData->m_center_x, pData->r_real);
		//	disp_obj(circle,pData->m_ShowHWindow);
		//}
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		pData->m_center_x=50;
		pData->m_center_y=50;
		pData->r_real=40;

		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CenterHC parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"CenterHC程序参数值出错,请重新调节参数");
#endif
		}

	
	}

}
