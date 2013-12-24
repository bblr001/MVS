// CanCurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CPGGCountersink.h"
#include "\slacmvs\trunk\Inc\MData.h"

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
		ShowObject=false;
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

	if(parm=="DriftAngle1")
		m_Parameters.DriftAngle1 = atof(value.c_str());
	if(parm=="DriftAngle2")
		m_Parameters.DriftAngle2 = atof(value.c_str());

	if(parm=="BThresholdValue")
		m_Parameters.BThresholdValue = -(float)atoi(value.c_str())/100;

	if(parm=="BDefectSize")
		m_Parameters.BDefectSize = atoi(value.c_str());

	if(parm=="WThresholdValue")
		m_Parameters.WThresholdValue = (float)atoi(value.c_str())/100;

	if(parm=="WDefectSize")
		m_Parameters.WDefectSize = atoi(value.c_str());


}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{


		Hobject image = pData->m_Image;

		double Regional_Out;

		Regional_Out =pData->r_real+m_Parameters.Regional_Out;

		HTuple  WidthOri, HeightOri;;


	    get_image_size (image, &WidthOri, &HeightOri);

	//*==================================================================================================	
		/*OrientationPhi = (HTuple(180).Rad()[0].D())+pData->m_orientationPhi;*/

		if (pData->m_isDebug)
		{
			if (0 != (m_Parameters.DriftAngle1==m_Parameters.DriftAngle2))
			{
				set_color(pData->m_ShowHWindow,"green");
				set_tposition( pData->m_ShowHWindow,5, 145);
				#ifdef _ENGLISH
								write_string(pData->m_ShowHWindow,"Drift angle values are the ​​same, please re-adjust the parameters");
				#else
								write_string(pData->m_ShowHWindow,"偏移角度相同,请重新调节偏移角度");
				#endif
				return;
			}
		}

		//*======================================================================================================
		double Rtemp;
		if(Regional_Out-m_Parameters.ROIWidth>=0)
			{
				Rtemp = Regional_Out-m_Parameters.ROIWidth;
			}
		else
			{
				Rtemp = 0;
			}

		Hobject Rectangle1,ROI,ImageReduced;
		
		gen_rectangle1(&Rectangle1, 0, 0, m_Parameters.ROIWidth, WidthOri-1);
		polar_trans_region_inv(Rectangle1, &ROI, pData->m_center_y, pData->m_center_x, 
			pData->m_orientationPhi+(m_Parameters.DriftAngle1.Rad()), pData->m_orientationPhi+(m_Parameters.DriftAngle2.Rad()), Regional_Out, 
			Rtemp, WidthOri, m_Parameters.ROIWidth+1, WidthOri, HeightOri, "nearest_neighbor");

		if (ShowObject&&pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"blue");	
			disp_obj(ROI,pData->m_ShowHWindow);
		}



		reduce_domain(image, ROI, &ImageReduced);
        
		Hobject DerivGauss,Regions,ConnectedRegions1,SelectedRegions1,Regions1,ConnectedRegions2,SelectedRegions2,RegionUnion;

		derivate_gauss(ImageReduced, &DerivGauss, 5, "det");


		threshold(DerivGauss, &Regions, m_Parameters.WThresholdValue, 1);
		connection(Regions, &ConnectedRegions1);
		select_shape(ConnectedRegions1, &SelectedRegions1, "area", "and", m_Parameters.WDefectSize, 99999);


		threshold(DerivGauss, &Regions1, -1, m_Parameters.BThresholdValue);
		connection(Regions1, &ConnectedRegions2);
		select_shape(ConnectedRegions2, &SelectedRegions2, "area", "and", m_Parameters.BDefectSize, 99999);


		union2(SelectedRegions2,SelectedRegions1,&RegionUnion);



	Hlong error_number;  
	count_obj(RegionUnion,&error_number);

		if (error_number)
		{

			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;

			if (pData->m_isDebug)
			{
				Hobject Dilation;
				dilation_circle(RegionUnion,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}

			Hobject RegionUnionWhole;
			union2(RegionUnion,pData->m_ErrorRegist,&RegionUnionWhole);
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
						write_string(pData->m_ShowHWindow,"CPGGCountersink parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"CPGGCountersink程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

  }
