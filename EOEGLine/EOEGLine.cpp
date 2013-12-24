// EOEGLine.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "EOEGLine.h"


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

	if(parm=="BlackMaskSize")
		m_Parameters.BlackMaskSize = atof(value.c_str());
	if(parm=="BThresholdLower")
		m_Parameters.BThresholdLower = atoi(value.c_str());
	if(parm=="BThresholdUpper")
		m_Parameters.BThresholdUpper = atoi(value.c_str());
	if(parm=="BDefectSize")
		m_Parameters.BDefectSize = atoi(value.c_str());
	if(parm=="BDefectSizeUpper")
		m_Parameters.BDefectSizeUpper = atoi(value.c_str());

	if(parm=="WhiteMaskSize")
		m_Parameters.WhiteMaskSize = atof(value.c_str());
	if(parm=="WThresholdLower")
		m_Parameters.WThresholdLower = atoi(value.c_str());
	if(parm=="WThresholdUpper")
		m_Parameters.WThresholdUpper = atoi(value.c_str());
	if(parm=="WDefectSize")
		m_Parameters.WDefectSize = atoi(value.c_str());
	if(parm=="WDefectSizeUpper")
		m_Parameters.WDefectSizeUpper = atoi(value.c_str());
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject image = pData->m_Image;
		Hobject  ROI,Circle1,Circle2;

        if((pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth)>0)
			{
				gen_circle(&Circle1, (pData->m_center_y), (pData->m_center_x), (pData->r_real+m_Parameters.Regional_Out));
				gen_circle(&Circle2, (pData->m_center_y), (pData->m_center_x), pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth);
				difference(Circle1, Circle2, &ROI);

				if (pData->m_isDebug&&ShowObject)
				{
					set_color(pData->m_ShowHWindow,"blue");	
					disp_obj(Circle1,pData->m_ShowHWindow);
					set_color(pData->m_ShowHWindow,"green");	
					disp_obj(Circle2,pData->m_ShowHWindow);
				}
						
			 }
		else
			 {
				gen_circle(&ROI, (pData->m_center_y), (pData->m_center_x), (pData->r_real+m_Parameters.Regional_Out));

				if (pData->m_isDebug&&ShowObject)
				{
					set_color(pData->m_ShowHWindow,"blue");	
					disp_obj(ROI,pData->m_ShowHWindow);
				}
			 }
	
		//*======================================================================================================
  
			Hobject ImageTest,ExpandedImage,DerivGauss,ImageReduced1,Regions,ConnectedRegions1,SelectedRegions1,Regions1,ConnectedRegions2,SelectedRegions2,RegionUnion;

			reduce_domain(image, ROI, &ImageTest);

    expand_domain_gray(ImageTest, &ExpandedImage, 2);
    //*===================================================================
	Hobject ImageNew,WhiteLines,SelectedwhiteContours,BlackLines,SelectedBlackContours;
	
	reduce_domain(ExpandedImage, ROI, &ImageNew);
	//scale_image_max (ImageNew, ImageScaleMax2)
	lines_gauss(ImageNew, &BlackLines, m_Parameters.BlackMaskSize, m_Parameters.BThresholdLower, m_Parameters.BThresholdUpper, "dark", "true", "bar-shaped", "true");
	select_contours_xld(BlackLines, &SelectedBlackContours, "contour_length", m_Parameters.BDefectSize, m_Parameters.BDefectSizeUpper, -0.5, 0.5);
	
	HTuple Number;
	HTuple  Index;
	Hobject BlackRegionUnion,ObjectSelected,Region,Dilation,WhiteRegionUnion;
	HTuple Row,Col;

	count_obj(SelectedBlackContours, &Number);
	if(Number>0)
	{
		//pData->m_ErrorRegist = BLACK_POINT;
		pData->m_isFail =true;
		testItem->m_bFailSubTest = true;
		//testItem->m_ErrorMsg = "BlackPoint error";
		//return;
		gen_empty_region(&BlackRegionUnion);
		for (Index=1; Index<=Number; Index+=1)
		{
			select_obj(SelectedBlackContours, &ObjectSelected, Index);
			get_contour_xld(ObjectSelected, &Row, &Col);
			gen_region_polygon(&Region, Row, Col);
			union2(BlackRegionUnion, Region, &BlackRegionUnion);
		}
		if (pData->m_isDebug)
		{
			dilation_circle(BlackRegionUnion,&Dilation,2.5);
			set_color(pData->m_ShowHWindow,"red");
			disp_obj(Dilation,pData->m_ShowHWindow);
		}
	}

	lines_gauss(ImageNew, &WhiteLines, m_Parameters.WhiteMaskSize, m_Parameters.WThresholdLower, m_Parameters.WThresholdUpper, "light", "true", "bar-shaped", "true");
	select_contours_xld(WhiteLines, &SelectedwhiteContours, "contour_length", m_Parameters.WDefectSize, m_Parameters.WDefectSizeUpper, -0.5, 0.5);

	count_obj(SelectedwhiteContours, &Number);
	if(Number>0)
	{
		//pData->m_ErrorRegist = BLACK_POINT;
		pData->m_isFail =true;
		testItem->m_bFailSubTest = true;
		//testItem->m_ErrorMsg = "BlackPoint error";
		//return;
		gen_empty_region(&WhiteRegionUnion);
		for (Index=1; Index<=Number; Index+=1)
		{
			select_obj(SelectedwhiteContours, &ObjectSelected, Index);
			get_contour_xld(ObjectSelected, &Row, &Col);
			gen_region_polygon(&Region, Row, Col);
			union2(WhiteRegionUnion, Region, &WhiteRegionUnion);
		}
		if (pData->m_isDebug)
		{
			dilation_circle(WhiteRegionUnion,&Dilation,2.5);
			set_color(pData->m_ShowHWindow,"yellow");
			disp_obj(Dilation,pData->m_ShowHWindow);
		}
	}


			Hobject RegionUnionWhole;
			union2(BlackRegionUnion,WhiteRegionUnion,&RegionUnion);
			union2(RegionUnion,pData->m_ErrorRegist,&RegionUnionWhole);
			pData->m_ErrorRegist=RegionUnionWhole;


	}
		catch (HException &except) 
		{
			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"green");
				set_tposition( pData->m_ShowHWindow,25, 145);
				#ifdef _ENGLISH
							write_string(pData->m_ShowHWindow,"EOEGLine parameter values error,please re-adjust");
				#else
							write_string(pData->m_ShowHWindow,"EOEGLine程序参数值出错,请重新调节参数");
				#endif
			}
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
		}

}



