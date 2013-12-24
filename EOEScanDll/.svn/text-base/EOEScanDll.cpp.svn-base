// EOEScanDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "EOEScanDll.h"
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
		m_Parameters.ThresholdValue = atof(value.c_str());

	if(parm=="NumChannel")
		m_Parameters.NumChannel = atoi(value.c_str());


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
		Hobject  ROICircle1, ROICircle2, RegionDifference;
		Hobject  ImageNew, ResultCircle;

		// Local control variables 

		HTuple  NumChannel, StepWidth, ResultEnergy, ResultCorrelation;
		HTuple  ResultHomogeneity, ResultContrast, ID;
		HTuple  ResultRadius, IDRadius, Num, Energy, Correlation;
		HTuple  Homogeneity, Contrast, ResultCenterRow, ResultCenterColumn;

    NumChannel = m_Parameters.NumChannel;
    StepWidth = m_Parameters.ROIWidth/(NumChannel-1);
    if (StepWidth<1)
    {
      //set_tposition(WindowHandle, 10, 10);
      //write_string(WindowHandle, "Too much channels");
      StepWidth = 1;
      NumChannel = m_Parameters.ROIWidth;
    }

    ResultEnergy = HTuple();
    ResultCorrelation = HTuple();
    ResultHomogeneity = HTuple();
    ResultContrast = HTuple();
    ID = 0;
    ResultRadius = HTuple();
    IDRadius = 1;
    for (Num=0; Num<=NumChannel-1; Num+=1)
    {
      gen_circle(&ROICircle1, pData->m_center_y, pData->m_center_x, pData->r_real+m_Parameters.Regional_Out-(Num*StepWidth));
      gen_circle(&ROICircle2, pData->m_center_y, pData->m_center_x, pData->r_real+m_Parameters.Regional_Out-1-(Num*StepWidth));
      difference(ROICircle1, ROICircle2, &RegionDifference);
      change_domain(image, RegionDifference, &ImageNew);

      cooc_feature_image(RegionDifference, ImageNew, 6, 0, &Energy, &Correlation, &Homogeneity, &Contrast);
      
	  ResultEnergy[ID] = Energy;
      ResultCorrelation[ID] = Correlation;
      ResultHomogeneity[ID] = Homogeneity;
      ResultContrast[ID] = Contrast;
      ID += 1;
      //*gray_histo (RegionDifference, ImageNew, AbsoluteHisto1, RelativeHisto1)

      //*get_region_points (RegionDifference, Rows, Columns)
      //*get_grayval (ImageNew, Rows, Columns, Grayval)
      if (Correlation*100>m_Parameters.ThresholdValue)
      {
        ResultRadius[IDRadius-1] =pData->r_real+m_Parameters.Regional_Out-(Num*StepWidth);
        IDRadius += 1;
      }

    }

	if(IDRadius>1)
		{
			tuple_gen_const(IDRadius-1, 1, &ResultCenterRow);
			ResultCenterRow = ResultCenterRow*pData->m_center_y;
			tuple_gen_const(IDRadius-1, 1, &ResultCenterColumn);
			ResultCenterColumn = ResultCenterColumn*pData->m_center_x;
		    gen_circle(&ResultCircle, ResultCenterRow, ResultCenterColumn, ResultRadius);
            
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
		
			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(ResultCircle,pData->m_ShowHWindow);
			}

			union2(pData->m_ErrorRegist,ResultCircle,&pData->m_ErrorRegist);
			

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
						write_string(pData->m_ShowHWindow,"EOEScanDLL程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

  }



