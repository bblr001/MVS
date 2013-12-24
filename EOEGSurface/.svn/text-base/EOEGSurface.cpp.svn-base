// CurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "EOEGSurface.h"


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

	if(parm=="BThresholdValue")
		m_Parameters.BThresholdValue = (float)atoi(value.c_str())/1000;

	if(parm=="BDefectSize")
		m_Parameters.BDefectSize = atoi(value.c_str());

	if(parm=="WThresholdValue")
		m_Parameters.WThresholdValue = -(float)atoi(value.c_str())/1000;

	if(parm=="WDefectSize")
		m_Parameters.WDefectSize = atoi(value.c_str());


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

    derivate_gauss(ExpandedImage, &DerivGauss, 5, "mean_curvature");

    reduce_domain(DerivGauss, ROI, &ImageReduced1);



    threshold(ImageReduced1, &Regions, m_Parameters.BThresholdValue, 1);
    connection(Regions, &ConnectedRegions1);
    select_shape(ConnectedRegions1, &SelectedRegions1, "area", "and", m_Parameters.BDefectSize, 99999);

	Hlong error_number;  
	Hobject Dilation;
	count_obj(SelectedRegions1,&error_number);

	if (error_number)
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		if (pData->m_isDebug)
		{

			dilation_circle(SelectedRegions1,&Dilation,2.5);
			set_color(pData->m_ShowHWindow,"red");
			disp_obj(Dilation,pData->m_ShowHWindow);
		}

	}


    threshold(ImageReduced1, &Regions1, -1, m_Parameters.WThresholdValue);
    connection(Regions1, &ConnectedRegions2);
    select_shape(ConnectedRegions2, &SelectedRegions2, "area", "and", m_Parameters.WDefectSize, 99999);

	count_obj(SelectedRegions2,&error_number);

	if (error_number)
	{

		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		if (pData->m_isDebug)
		{
			dilation_circle(SelectedRegions2,&Dilation,2.5);
			set_color(pData->m_ShowHWindow,"yellow");
			disp_obj(Dilation,pData->m_ShowHWindow);
		}

	}


	union2(SelectedRegions2,SelectedRegions1,&RegionUnion);
	Hobject RegionUnionWhole;
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
							write_string(pData->m_ShowHWindow,"EOEGSurface parameter values error,please re-adjust");
				#else
							write_string(pData->m_ShowHWindow,"EOEGSurface程序参数值出错,请重新调节参数");
				#endif
			}
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
		}

}



