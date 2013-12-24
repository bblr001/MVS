// CurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CurlDll5.h"
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
	if(parm=="ROIWidth")
		m_Parameters.ROIWidth = atoi(value.c_str());

	if(parm=="ThresholdValue")
		m_Parameters.ThresholdValue = atof(value.c_str());

	if(parm=="WindowSize")
		m_Parameters.WindowSize = atoi(value.c_str());

	if(parm=="PartSize")
		m_Parameters.PartSize = atoi(value.c_str());

	if(parm=="MaxGray")
		m_Parameters.MaxGray = atoi(value.c_str());

	 
	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atof(value.c_str());

	if(parm=="SHOWOBJECT")
		if (value=="YES")
		{
			ShowObject = true;
		}
		else
		{
			ShowObject = false;
		}

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		double Regional_Out =pData->r_real+m_Parameters.Regional_Out;
		double Rtemp;
		Hlong error_number; 
		error_number = 0;

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
			Regional_Out, (Regional_Out)-m_Parameters.ROIWidth, ((HTuple(370).Rad())*pData->r_real)/m_Parameters.PartSize, 
			m_Parameters.ROIWidth, "bilinear");

		get_image_size(PolarTransImage, &PolarTransImageWidth, &PolarTransImageHeight);
		scale_image_max(PolarTransImage, &ImageScaleMax);

		HTuple sum_gray = HTuple();
		HTuple tem1 = HTuple();
		for (HTuple Index1=0; Index1<=PolarTransImageWidth-1; Index1+=1)
		{
			sum_gray[Index1] = 0;
			for (HTuple Index2=0; Index2<=PolarTransImageHeight-1; Index2+=1)
			{
				get_grayval(ImageScaleMax, Index2, Index1, &tem1);
				if (tem1>m_Parameters.MaxGray)
				{
					tem1 = m_Parameters.MaxGray;
					set_grayval(ImageScaleMax, Index2, Index1, m_Parameters.MaxGray);
				}
				sum_gray[Index1] = HTuple(sum_gray[Index1])+tem1;
			}
		}
		//stop ()
		HTuple WidthBianYuan_Lenght = HTuple();
		tuple_length(sum_gray, &WidthBianYuan_Lenght);

		HTuple TotalGrayInBianYuan_deviation3 = HTuple();
		HTuple window_deviation;
		for (i=0; i<=(WidthBianYuan_Lenght-(m_Parameters.WindowSize*2))-1; i+=1)
		{
	
			window_deviation=0;
			for (HTuple window=i; window<=(i+m_Parameters.WindowSize)-1; window+=1)
			{
				window_deviation = (window_deviation+HTuple(sum_gray[window]))+HTuple(sum_gray[(window+m_Parameters.WindowSize)+1]);
			}

			if (0 != (window_deviation==0))
			{
				TotalGrayInBianYuan_deviation3[i] = 0;
			}
			else
			{

				TotalGrayInBianYuan_deviation3[i] = ((((HTuple(sum_gray[i])*100)*m_Parameters.WindowSize)*2)/window_deviation)-100;
			}

		}

		tuple_abs(TotalGrayInBianYuan_deviation3, &Abs);
		tuple_sort(Abs, &AbsSorted);
		tuple_sort_index(Abs, &LocationId);
		tuple_length(Abs, &Length);

		
		for (i=Length-1; i>=0; i+=-1)
		{

			if (0 != (HTuple(AbsSorted[i])<m_Parameters.ThresholdValue))
			{
				if (0 != (i==(Length-1)))
				{
					ResultID = HTuple();
					break;
				}
				else
				{
					tuple_last_n(LocationId, i+1, &ResultID);
					break;
				}
			}
		}
		ResultID += m_Parameters.PartSize;
		HTuple Number;
		tuple_length(ResultID, &Number);

		if (0 != (Number>0))
		{
			partition_rectangle(ImageScaleMax, &JuanYuanPartitioned, 1, PolarTransImageHeight);
			select_obj(JuanYuanPartitioned, &ResultDefect, ResultID);
			polar_trans_region_inv(ResultDefect, &BackTransRegion, pData->m_center_y, pData->m_center_x,  0, HTuple(370).Rad(), 
				 Regional_Out, (Regional_Out)-m_Parameters.ROIWidth, 
				((HTuple(370).Rad())*pData->r_real)/m_Parameters.PartSize, m_Parameters.ROIWidth, 
				WidthOri, HeightOri, "bilinear");

			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			if (ShowObject)
			{
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(BackTransRegion,pData->m_ShowHWindow);
			}

			Hobject RegionUnionWhole;
			union2(BackTransRegion,pData->m_ErrorRegist,&RegionUnionWhole);
			pData->m_ErrorRegist=RegionUnionWhole;
			
		}

	}
	catch (HException &except) 
	{
		if (ShowObject)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef ENGLISH_VERSION
						write_string(pData->m_ShowHWindow,"CurlDll5 parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"CurlDll5程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		
	}

  }
