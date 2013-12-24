// CurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "EOEGCountersink.h"


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
  
			Hobject ImageTest,DerivGauss,Regions,ConnectedRegions1,SelectedRegions1,Regions1,ConnectedRegions2,SelectedRegions2,RegionUnion;

			reduce_domain(image, ROI, &ImageTest);

    //*===================================================================

    derivate_gauss(ImageTest, &DerivGauss, 5, "det");


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
							write_string(pData->m_ShowHWindow,"EOEGSurface parameter values error,please re-adjust");
				#else
							write_string(pData->m_ShowHWindow,"EOEGCountersink程序参数值出错,请重新调节参数");
				#endif
			}
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
		}

}




