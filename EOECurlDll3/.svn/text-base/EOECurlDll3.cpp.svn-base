// CurlDll2.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "EOECurlDll3.h"
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
	if(parm=="ROIWidth")
		m_Parameters.ROIWidth = atoi(value.c_str());

	if(parm=="UpperThresholdValue")
		m_Parameters.UpperThresholdValue = atof(value.c_str());
	if(parm=="LowerThresholdValue")
		m_Parameters.LowerThresholdValue = atof(value.c_str());

	if(parm=="GrayValue")
		m_Parameters.GrayValue = atoi(value.c_str());

	if(parm=="NumPart")
		m_Parameters.NumPart = atoi(value.c_str());

	if(parm=="NumNeighbor")
		m_Parameters.NumNeighbor = atoi(value.c_str());

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atof(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject image = pData->m_Image;
		int ROIWidth;
		int  NumPart;
		double Regional_Out, Rtemp;
		Regional_Out =pData->r_real+m_Parameters.Regional_Out;
		ROIWidth = m_Parameters.ROIWidth;
		NumPart = m_Parameters.NumPart;

		Hlong error_number; 
		error_number = 0;

		  Hobject  PolarTransImage,ImageScaleMax, JuanYuanPartitioned, ResultDefect;
		  Hobject  BackTransRegion,Circle1,Circle2;

		  // Local control variables 
		  HTuple  Pointer, Type, WidthOri, HeightOri;
		  HTuple  PolarTransImageWidth, PolarTransImageHeight;
		  HTuple  Mean, Deviation, Mean_Lenght, Mean_deviation;
		  HTuple  i, Exp, Abs, AbsSorted, LocationId, Length;
		  HTuple  ResultID,MeanSorted;
		  HTuple  LocationId2, Length1, ResultID2, ResultID3,ResultIDFinal;
		  HTuple  Sorted, Uniq,errorValue;
		  HTuple  TempNeighbor,j, SumNeighbor;

		get_image_pointer1(image, &Pointer, &Type, &WidthOri, &HeightOri);

		if(Regional_Out-ROIWidth>0)
			{
					Rtemp = Regional_Out-ROIWidth;
					gen_circle(&Circle1, (pData->m_center_y), (pData->m_center_x), (Regional_Out));
					gen_circle(&Circle2, (pData->m_center_y), (pData->m_center_x), (Regional_Out)-ROIWidth);
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
					Rtemp = 0;
					gen_circle(&Circle1, (pData->m_center_y), (pData->m_center_x), (Regional_Out));
					if (ShowObject&&pData->m_isDebug)
						{
							set_color(pData->m_ShowHWindow,"blue");	
							disp_obj(Circle1,pData->m_ShowHWindow);
						}
			}

		

		//*======================================================================================================
	    polar_trans_image_ext(image, &PolarTransImage, pData->m_center_y, pData->m_center_x, 
			0, HTuple(360).Rad(), HTuple(Regional_Out), HTuple(Rtemp), 
			(HTuple(360).Rad())*HTuple(Regional_Out), ROIWidth, "nearest_neighbor");
		//polar_trans_image_ext(image, &PolarTransImage, pData->m_center_y, pData->m_center_x, 
		//	0, HTuple(360).Rad(), HTuple(Regional_Out), HTuple(Rtemp), 
		//	HTuple(WidthOri), ROIWidth, "nearest_neighbor");
		get_image_size(PolarTransImage, &PolarTransImageWidth, &PolarTransImageHeight);

		scale_image_max(PolarTransImage, &ImageScaleMax);
		partition_rectangle(ImageScaleMax, &JuanYuanPartitioned, PolarTransImageWidth/NumPart, 
			PolarTransImageHeight);

		intensity(JuanYuanPartitioned, ImageScaleMax, &Mean, &Deviation);

		tuple_length(Mean, &Mean_Lenght);

		Mean_deviation = HTuple();

		for (i=0; i<=Mean_Lenght-1; i+=1)
		{

			TempNeighbor = HTuple();

			for (j=1; j<=m_Parameters.NumNeighbor; j+=1)
			{
				if (0 != (HTuple((i-j)<0).And((i+j)<=(Mean_Lenght-1))))
				{
					TempNeighbor[j-1] = HTuple(Mean[i+j])+HTuple(Mean[Mean_Lenght+(i-j)]);
				}
				if (0 != (HTuple((i-j)>=0).And((i+j)<=(Mean_Lenght-1))))
				{
					TempNeighbor[j-1] = HTuple(Mean[i+j])+HTuple(Mean[i-j]);
				}
				if (0 != (HTuple((i-j)>=0).And((i+j)>(Mean_Lenght-1))))
				{
					TempNeighbor[j-1] = HTuple(Mean[(i+j)-Mean_Lenght])+HTuple(Mean[i-j]);
				}
			}
			tuple_sum(TempNeighbor, &SumNeighbor);
      Exp = ((HTuple(Mean[i])*2)*m_Parameters.NumNeighbor)-SumNeighbor;
      //tuple_deviation ([Mean[i]*2*NumNeighbor,SumNeighbor], Exp)
      Mean_deviation[i] = Exp;
    }

    //tuple_abs (Mean_deviation, Abs)
    tuple_sort(Mean_deviation, &AbsSorted);
    tuple_sort_index(Mean_deviation, &LocationId);
    tuple_length(Mean_deviation, &Length);
    //*======================================================================================================


    for (i=Length-1; i>=0; i+=-1)
    {

      if (0 != (HTuple(AbsSorted[i])<m_Parameters.UpperThresholdValue))
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

    ResultID += 1;

    //*======================================================================================================

    for (i=0; i<=Length-1; i+=1)
    {

      if (0 != (HTuple(AbsSorted[i])>m_Parameters.LowerThresholdValue))
      {
        if (0 != (i==0))
        {
          ResultID2 = HTuple();
          break;
        }
        else
        {
          tuple_first_n(LocationId, i-1, &ResultID2);
          break;
        }
      }
    }

    ResultID2 += 1;
    //*======================================================================================================
    tuple_sort(Mean, &MeanSorted);
    tuple_sort_index(Mean, &LocationId2);
    tuple_length(Mean, &Length1);


    ResultID3 = HTuple();
    for (i=0; i<=Length1-1; i+=1)
    {

      if (0 != (HTuple(MeanSorted[i])<m_Parameters.GrayValue))
      {

        ResultID3[i] = HTuple(LocationId2[i]);

      }
      else
      {
        break;

      }
    }
    ResultID3 += 1;

    tuple_concat(ResultID, ResultID2, &ResultIDFinal);
    tuple_concat(ResultIDFinal, ResultID3, &ResultIDFinal);
    tuple_sort(ResultIDFinal, &Sorted);
    tuple_uniq(Sorted, &Uniq);
    select_obj(JuanYuanPartitioned, &ResultDefect, Uniq);

		polar_trans_region_inv(ResultDefect, &BackTransRegion, pData->m_center_y, pData->m_center_x, 
			0, HTuple(360).Rad(), HTuple(Regional_Out), HTuple(Rtemp), 
			(HTuple(360).Rad())*HTuple(Regional_Out), ROIWidth, WidthOri, HeightOri, 
			"nearest_neighbor");

		count_obj(BackTransRegion,&error_number);
		
		if (error_number)
		{

			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			if (pData->m_isDebug)
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
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"CurlDll2 parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"EOECurlDll3程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

  }


