// CurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "MianXinFFT.h"
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

	if(parm=="WThresholdValue")
		m_Parameters.WThresholdValue = atof(value.c_str());

	if(parm=="BThresholdValue")
		m_Parameters.BThresholdValue = atof(value.c_str());

	if(parm=="WDefectSize")
		m_Parameters.WDefectSize = atoi(value.c_str());

	if(parm=="BDefectSize")
		m_Parameters.BDefectSize = atoi(value.c_str());


}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		image = pData->m_Image;
        if((pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth)>0)
			{
				gen_circle(&Circle1, (pData->m_center_y), (pData->m_center_x), (pData->r_real+m_Parameters.Regional_Out));
				gen_circle(&Circle2, (pData->m_center_y), (pData->m_center_x), pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth);
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
				gen_circle(&ROI, (pData->m_center_y), (pData->m_center_x), (pData->r_real+m_Parameters.Regional_Out));

					if (ShowObject&&pData->m_isDebug)
					{
						set_color(pData->m_ShowHWindow,"blue");	
						disp_obj(ROI,pData->m_ShowHWindow);
					}
			 }
	
		//*======================================================================================================

		
		reduce_domain(image, ROI, &ImageTest);

		derivate_gauss(ImageTest, &ImageGauss, 2.0, "laplace");
		
		threshold(ImageGauss, &Defects, m_Parameters.WThresholdValue, 1000);
		connection (Defects, &DefectsConnectedRegions);
		select_shape (DefectsConnectedRegions, &SelectedRegion1, "area", "and", m_Parameters.WDefectSize, 99999);

		threshold(ImageGauss, &Defects, -1000, m_Parameters.BThresholdValue);
		connection (Defects, &DefectsConnectedRegions);
		select_shape (DefectsConnectedRegions, &SelectedRegion2, "area", "and", m_Parameters.BDefectSize, 99999);

		union2(SelectedRegion1, SelectedRegion2, &Defects);

		count_obj(Defects,&error_number);
		
		if (error_number)
		{

			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"blue");	
				disp_obj(Defects,pData->m_ShowHWindow);
			}
			union2(pData->m_ErrorRegist, Defects,&Defects);
			pData->m_ErrorRegist=Defects;
		}



	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		except.message;
		testItem->m_ErrorY = 1;
		testItem->m_ErrorX = 1;
		testItem->m_ErrorR = 4;

		if (ShowObject&&pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 200);
			write_string(pData->m_ShowHWindow,"EOEEdgeDLL程序参数值出错,请重新调节参数");

			set_tposition( pData->m_ShowHWindow,50, 200);
			write_string(pData->m_ShowHWindow,except.message);

			
		}
	}

  }



