// CurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "EOEShapeDll2.h"
#include "../Inc/MData.h"

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
	m_Parameters.SharpType="area";
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
	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atof(value.c_str());

	if(parm=="ROIWidth")
		m_Parameters.ROIWidth = atoi(value.c_str());

	if(parm=="ThresholdValue")
		m_Parameters.ThresholdValue = atof(value.c_str());

	if(parm=="DefectSize")
		m_Parameters.DefectSize = atoi(value.c_str());

	if(parm=="List_Value")		
		m_Parameters.SharpType = value.c_str();


}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		double Regional_Out =pData->r_real+m_Parameters.Regional_Out;
		double Rtemp;

		Hobject  PolarTransImage,ImageScaleMax, JuanYuanPartitioned, ResultDefect;
		Hobject  BackTransRegion,Circle1,Circle2;

		// Local control variables 
		HTuple  Pointer, Type, WidthOri, HeightOri;
		HTuple  PolarTransImageWidth, PolarTransImageHeight;
		HTuple  i, Exp, Abs, AbsSorted, LocationId, Length;
		HTuple  ResultID,MeanSorted;

		HTuple  Sorted, Uniq,errorValue;


		get_image_pointer1(pData->m_Image, &Pointer, &Type, &WidthOri, &HeightOri);

		if(Regional_Out-m_Parameters.ROIWidth>0)
		{
			Rtemp = Regional_Out-m_Parameters.ROIWidth;
			gen_circle(&Circle1, (pData->m_center_y), (pData->m_center_x), (Regional_Out));
			gen_circle(&Circle2, (pData->m_center_y), (pData->m_center_x), (Regional_Out)-m_Parameters.ROIWidth);
			if (ShowObject)
			{
				set_color(pData->m_ShowHWindow,"blue");	
				disp_obj(Circle1,pData->m_ShowHWindow);
				set_color(pData->m_ShowHWindow,"green");	
				disp_obj(Circle2,pData->m_ShowHWindow);
			}

		}
		else
		{
			Rtemp = 0;
			gen_circle(&Circle1, (pData->m_center_y), (pData->m_center_x), (Regional_Out));
			if (ShowObject)
			{
				set_color(pData->m_ShowHWindow,"blue");	
				disp_obj(Circle1,pData->m_ShowHWindow);
			}
		}

		polar_trans_image_ext(pData->m_Image, &PolarTransImage, pData->m_center_y, pData->m_center_x,  0, HTuple(370).Rad(), 
			Regional_Out, (Regional_Out)-m_Parameters.ROIWidth, ((HTuple(370).Rad())*pData->r_real), 
			m_Parameters.ROIWidth, "bilinear");

		scale_image_max(PolarTransImage, &ImageScaleMax);

		
			Hobject ImageTest,ConnectedThresholdRegion,SelectedRegion,ModelImages,ModelRegions,ExpandedImage;

			inspect_shape_model (ImageScaleMax, &ModelImages, &ModelRegions, 1, m_Parameters.ThresholdValue);
			connection(ModelRegions, &ConnectedThresholdRegion);

			if(m_Parameters.SharpType=="area")		
				select_shape(ConnectedThresholdRegion, &SelectedRegion, "area", "and", m_Parameters.DefectSize,99999);
			if(m_Parameters.SharpType=="height")		
				select_shape(ConnectedThresholdRegion, &SelectedRegion, "height", "and", m_Parameters.DefectSize,99999);
			if(m_Parameters.SharpType=="width")		
				select_shape(ConnectedThresholdRegion, &SelectedRegion, "width", "and", m_Parameters.DefectSize,99999);
			
		Hlong error_number;  
		count_obj(SelectedRegion,&error_number);
		
		if (error_number)
		{
			polar_trans_region_inv(SelectedRegion, &BackTransRegion, pData->m_center_y, pData->m_center_x,  0, HTuple(370).Rad(), 
				Regional_Out, (Regional_Out)-m_Parameters.ROIWidth, 
				((HTuple(370).Rad())*pData->r_real), m_Parameters.ROIWidth, 
				WidthOri, HeightOri, "bilinear");


			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			
			if (pData->m_isDebug)
			{
				Hobject Dilation;
				dilation_circle(BackTransRegion,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}
			
			Hobject RegionUnionWhole;
			union2(BackTransRegion,pData->m_ErrorRegist,&RegionUnionWhole);
			pData->m_ErrorRegist=RegionUnionWhole;

		}



	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"EOEEdgeDLL parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"EOEShapeDll程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

  }





