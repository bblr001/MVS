// CurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "EOEShapeDll.h"
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
		m_Parameters.ThresholdValue = atoi(value.c_str());

	if(parm=="DefectSize")
		m_Parameters.DefectSize = atoi(value.c_str());


}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject image = pData->m_Image;
		Hobject  ROI,Circle1,Circle2,ContCircle1,ContCircle2,ContCircle;

		if((pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth)>0)
		{
			gen_circle(&Circle1, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out));
			//gen_circle_contour_xld (&ContCircle1, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out), 0, 6.28318, "positive", 1);
			//gen_region_contour_xld (ContCircle1, &Circle1, "filled");
			gen_circle(&Circle2, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth));
			//gen_circle_contour_xld (&ContCircle2, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth), 0, 6.28318, "positive", 1);
			//gen_region_contour_xld (ContCircle2, &Circle2, "filled");

			difference(Circle1, Circle2, &ROI);

			if (ShowObject&&pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"blue");	
				disp_obj(Circle1,pData->m_ShowHWindow);
				set_color(pData->m_ShowHWindow,"green");	
				disp_obj(Circle2,pData->m_ShowHWindow);
			}

		}
		else
		{
			gen_circle(&ROI, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out));
			//gen_circle_contour_xld (&ContCircle, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out), 0, 6.28318, "positive", 1);
			//gen_region_contour_xld (ContCircle, &ROI, "filled");

			if (ShowObject&&pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"blue");	
				disp_obj(ROI,pData->m_ShowHWindow);
			}
		}
	
		//*======================================================================================================
  
			Hobject ImageTest,ConnectedThresholdRegion,SelectedRegion,ModelImages,ModelRegions,ExpandedImage;

			
			reduce_domain(image, ROI, &ImageTest);
			expand_domain_gray(ImageTest, &ExpandedImage, 2);
			reduce_domain(ExpandedImage, ROI, &ImageTest);
            //Hobject  ExpandedImage, ImageMean, ImageExpandedReduced;
			//HTuple MaskSize;
			//MaskSize = 3;
			//expand_domain_gray(ImageTest, &ExpandedImage, 2);
			//mean_image(ExpandedImage, &ImageMean, MaskSize, MaskSize);
			//reduce_domain(ImageMean, ROI, &ImageExpandedReduced);

			//HTuple MaskSize;
			//Hobject ExpandedImage,ImageMean;

			//MaskSize = 3;

			//expand_domain_gray(ImageTest, &ExpandedImage, 2);
			//mean_image(ExpandedImage, &ImageMean, MaskSize, MaskSize);
			//reduce_domain(ImageMean, ROI, &ImageTest);


			inspect_shape_model (ImageTest, &ModelImages, &ModelRegions, 1, m_Parameters.ThresholdValue);

			connection(ModelRegions, &ConnectedThresholdRegion);
			select_shape(ConnectedThresholdRegion, &SelectedRegion, "area", "and", m_Parameters.DefectSize, 
				99999);

		Hlong error_number;  
		count_obj(SelectedRegion,&error_number);
		
		if (error_number)
		{

			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			//HTuple Area,yy,xx;
			//area_center(SelectedRegion,&Area,&yy,&xx);
			//testItem->m_ErrorY = yy[0].D();
			//testItem->m_ErrorX = xx[0].D();
			//char msg[MAX_PATH];
			//sprintf_s(msg,MAX_PATH-1,"EOE Edge Error");
			//testItem->m_ErrorMsg = msg;
			
			if (pData->m_isDebug)
			{
				Hobject Dilation;
				dilation_circle(SelectedRegion,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}

			Hobject RegionUnionWhole;
			union2(SelectedRegion,pData->m_ErrorRegist,&RegionUnionWhole);
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





