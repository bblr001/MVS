// CurlDll4.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CurlDll4.h"
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

	  //* 边缘点的对比度


  if(parm=="WContrast")
	  m_Parameters.m_WContrast = atoi(value.c_str());

  if(parm=="NContrast")
	  m_Parameters.m_NContrast = atoi(value.c_str());

	if(parm=="ROIWidth")
		m_Parameters.ROIWidth = atoi(value.c_str());

	if(parm=="AbsJuanYuanWidth")
		m_Parameters.AbsJuanYuanWidth = atoi(value.c_str());


	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atoi(value.c_str());

	if(parm=="WidthBianYuan_Deviation")
		m_Parameters.WidthBianYuan_Deviation = atof(value.c_str());

	if(parm=="GrayBianYuan_Deviation")
		m_Parameters.GrayBianYuan_Deviation = atoi(value.c_str());



	if(parm=="NBianYuan_SiteDeviationLow")
		m_Parameters.NBianYuan_SiteDeviationLow = atoi(value.c_str());

	if(parm=="NBianYuan_SiteDeviationUp")
		m_Parameters.NBianYuan_SiteDeviationUp = atoi(value.c_str());


	if(parm=="WBianYuan_SiteDeviationLow")
		m_Parameters.WBianYuan_SiteDeviationLow = atoi(value.c_str());

	if(parm=="WBianYuan_SiteDeviationUp")
		m_Parameters.WBianYuan_SiteDeviationUp = atoi(value.c_str());



	if(parm=="NumPart")
		m_Parameters.NumPart = atoi(value.c_str());

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


		float ThresholdValue;
		int  NumPart;
		float Regional_Out, Rtemp;
		Regional_Out =pData->r_real+m_Parameters.Regional_Out;
		NumPart = m_Parameters.NumPart;

		Hlong error_number; 
		error_number = 0;

		Hobject  PolarTransImage,ImageScaleMax, JuanYuanPartitioned, ResultDefect;
		Hobject  BackTransRegion,Circle1,Circle2;

		// Local control variables 

		HTuple  PolarTransImageWidth, PolarTransImageHeight;

		HTuple  i, Exp, Abs, AbsSorted, LocationId, Length;
		HTuple  ResultID1,ResultID2,ResultID3,ResultID4,ResultID41;
		HTuple  LocationId2,ResultID5,ResultID51,ResultID6;
		HTuple  Uniq,errorValue;
		HTuple Pointer,Type,WidthOri,HeightOri;

		Hobject ConstImageInBianYuan;

		get_image_pointer1(pData->m_Image, &Pointer, &Type, &WidthOri, &HeightOri);

		if(Regional_Out-m_Parameters.ROIWidth>0)
			{
					Rtemp = Regional_Out-m_Parameters.ROIWidth;
					gen_circle(&Circle1, (pData->m_center_y), (pData->m_center_x), (Regional_Out));
					gen_circle(&Circle2, (pData->m_center_y), (pData->m_center_x), Rtemp);
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
	  //*测外圈卷边

		  polar_trans_image_ext(pData->m_Image, &PolarTransImage, pData->m_center_y, pData->m_center_x, 
			  0, HTuple(375).Rad(), HTuple(Regional_Out), HTuple(Rtemp), 
			  (HTuple(375).Rad())*HTuple(Regional_Out)/NumPart, m_Parameters.ROIWidth, "bilinear");

		  get_image_size(PolarTransImage, &PolarTransImageWidth, &PolarTransImageHeight);
		  scale_image_max(PolarTransImage, &ImageScaleMax);



		  //* 边缘点

		  //* 只包括边缘点的图像
		  if (pData->m_isDebug)
		  {
			  gen_image_const(&ConstImageInBianYuan, "byte", PolarTransImageWidth, PolarTransImageHeight);
		  }
		  
		
		

  //* 包括边缘点的卷边图像
  //gen_image_const (ConstImageBianYuan, 'byte', PolarTransImageWidth, PolarTransImageHeight)

  //* 边缘宽度
	HTuple WidthBianYuan,WBianYuanP,NBianYuanP;
	HTuple TotalGrayInBianYuan;

	//* 平均灰度
	TotalGrayInBianYuan = 0;

	int WBD,NBD;
	for (int Index1=0; Index1<=PolarTransImageWidth-1; Index1+=1)
	{
		WBD = 0;
		NBD = 0;

		NBianYuanP[Index1] = 0;
		WBianYuanP[Index1] = 0;
		double Grayval,Grayval2,diff;
		for (int Index2=0; Index2<=PolarTransImageHeight-2; Index2+=1)
		{
		  get_grayval(ImageScaleMax, Index2, Index1, &Grayval);
		  get_grayval(ImageScaleMax, Index2+1, Index1, &Grayval2);


		  //*从黑变亮是外边缘点
		  diff = Grayval2-Grayval;
		  if ((diff>m_Parameters.m_WContrast)&&(WBD==0))
		  {
			if (WBD==0)
			{
			  WBD = Index2;
			  //*外边缘点的坐标
			  WBianYuanP[Index1] = Index2;
			  NBD = Index2+1;
			  //*内边缘点的坐标
				NBianYuanP[Index1] = Index2+1;
			}
		  }

		  if (diff<m_Parameters.m_NContrast)
		  {
			NBD = Index2+1;
			//*内边缘点的坐标
			NBianYuanP[Index1] = Index2+1;
		  }

		}
		
		//*边缘宽度
		if (WBD!=0&&NBD!=0)
		{
			WidthBianYuan[Index1] = NBD-WBD;
		}
		else
			WidthBianYuan[Index1] = 0;

		if (pData->m_isDebug)
		{
			if (WBD!=0)
				set_grayval(ConstImageInBianYuan, NBD, Index1, 255);
			if(NBD!=0)
				set_grayval(ConstImageInBianYuan, WBD, Index1, 255);
		}
		

		//*边缘宽度内的灰度值和
		int totalGray = 0;
		for (int Index2=WBD; Index2<=NBD; Index2++)
		{
		  get_grayval(ImageScaleMax, Index2, Index1, &Grayval);
		  totalGray += Grayval;
		}
		TotalGrayInBianYuan[Index1] = totalGray;

	 }
	 if (pData->m_isDebug&&ShowObject) //For Display Error Region when Debug Mode
		 disp_obj(ConstImageInBianYuan,pData->m_ShowHWindow); 
	


	Hlong  WidthBianYuan_Lenght;
  //*检测1 －－－ 边缘宽度绝对大小
  tuple_length(WidthBianYuan, &WidthBianYuan_Lenght);
  
  tuple_abs(WidthBianYuan, &Abs);
  tuple_sort(Abs, &AbsSorted);
  tuple_sort_index(Abs, &LocationId);
  tuple_length(Abs, &Length);

  ResultID1 = HTuple();
  for (i=Length-1; i>=0; i+=-1)
  {
    if (AbsSorted[i].L()<m_Parameters.AbsJuanYuanWidth)
    {
        tuple_first_n(LocationId, i, &ResultID1);
		break;
    }
  }

  ResultID1 += 1;
   if (pData->m_isDebug)
	{
		partition_rectangle(ImageScaleMax, &JuanYuanPartitioned,1, PolarTransImageHeight);
		select_obj(JuanYuanPartitioned, &ResultDefect, ResultID1);
		polar_trans_region_inv(ResultDefect, &BackTransRegion, pData->m_center_y, pData->m_center_x,  0, 
			HTuple(375).Rad(), pData->r_real+m_Parameters.Regional_Out, pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth, 
			((HTuple(375).Rad())*pData->r_real)/NumPart, m_Parameters.ROIWidth,
			WidthOri, HeightOri, "bilinear");

		count_obj(BackTransRegion,&error_number);

		if (error_number)
		{

			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"blue");
				disp_obj(BackTransRegion,pData->m_ShowHWindow);
			}

			Hobject RegionUnionWhole;
			union2(BackTransRegion,pData->m_ErrorRegist,&RegionUnionWhole);
			pData->m_ErrorRegist=RegionUnionWhole;
		}
   }
   


  //*检测2 －－－ 边缘宽度变化率

  HTuple WidthBianYuan_deviation;
  for (i=0; i<=WidthBianYuan_Lenght-2; i+=1)
  {
    tuple_deviation(HTuple(WidthBianYuan[i]).Concat(HTuple(WidthBianYuan[i+1])), 
        &Exp);
    WidthBianYuan_deviation[i] = Exp;
  }

  tuple_abs(WidthBianYuan_deviation, &Abs);
  tuple_sort(Abs, &AbsSorted);
  tuple_sort_index(Abs, &LocationId);
  tuple_length(Abs, &Length);

  ThresholdValue = 1.3;
  for (i=Length-1; i>=0; i+=-1)
  {

    if (0 != (HTuple(AbsSorted[i])<m_Parameters.WidthBianYuan_Deviation))
    {
      if (0 != (i==(Length-1)))
      {
        ResultID2 = HTuple();
        break;
      }
      else
      {
        tuple_last_n(LocationId, i+1, &ResultID2);
        break;
      }
    }
  }

  ResultID2 += 1;

  if (pData->m_isDebug)
  {

	  partition_rectangle(ImageScaleMax, &JuanYuanPartitioned,1, PolarTransImageHeight);
	  select_obj(JuanYuanPartitioned, &ResultDefect, ResultID2);
	  polar_trans_region_inv(ResultDefect, &BackTransRegion, pData->m_center_y, pData->m_center_x,  0, 
		  HTuple(375).Rad(), pData->r_real+m_Parameters.Regional_Out, pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth, 
		  ((HTuple(375).Rad())*pData->r_real)/NumPart, m_Parameters.ROIWidth,
		  WidthOri, HeightOri, "bilinear");

	  count_obj(BackTransRegion,&error_number);

	  if (error_number)
	  {

		  pData->m_isFail = true;
		  testItem->m_bFailSubTest = true;
		  if (pData->m_isDebug)
		  {
			  set_color(pData->m_ShowHWindow,"green");
			  disp_obj(BackTransRegion,pData->m_ShowHWindow);
		  }

		  Hobject RegionUnionWhole;
		  union2(BackTransRegion,pData->m_ErrorRegist,&RegionUnionWhole);
		  pData->m_ErrorRegist=RegionUnionWhole;
	  }
  }
  //*检测3 －－－ 边缘区域灰度和变化率

  HTuple TotalGrayInBianYuan_deviation;
  for (i=0; i<=WidthBianYuan_Lenght-2; i+=1)
  {
    tuple_deviation(HTuple(TotalGrayInBianYuan[i]).Concat(HTuple(TotalGrayInBianYuan[i+1])), 
        &Exp);
    TotalGrayInBianYuan_deviation[i] = Exp;
  }

  tuple_abs(TotalGrayInBianYuan_deviation, &Abs);
  tuple_sort(Abs, &AbsSorted);
  tuple_sort_index(Abs, &LocationId);
  tuple_length(Abs, &Length);

  
  ResultID3 = HTuple();
  for (i=0; i<Length; i++)
  {
    if (AbsSorted[i].L()>m_Parameters.GrayBianYuan_Deviation )
    {
        tuple_last_n(LocationId, i, &ResultID3);
        break;
    }
  }

  ResultID3 += 1;

  if (pData->m_isDebug)
  {
	  partition_rectangle(ImageScaleMax, &JuanYuanPartitioned,1, PolarTransImageHeight);
	  select_obj(JuanYuanPartitioned, &ResultDefect, ResultID3);
	  polar_trans_region_inv(ResultDefect, &BackTransRegion, pData->m_center_y, pData->m_center_x,  0, 
		  HTuple(375).Rad(), pData->r_real+m_Parameters.Regional_Out, pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth, 
		  ((HTuple(375).Rad())*pData->r_real)/NumPart, m_Parameters.ROIWidth,
		  WidthOri, HeightOri, "bilinear");

	  count_obj(BackTransRegion,&error_number);

	  if (error_number)
	  {

		  pData->m_isFail = true;
		  testItem->m_bFailSubTest = true;
		  if (pData->m_isDebug)
		  {
			  set_color(pData->m_ShowHWindow,"yellow");
			  disp_obj(BackTransRegion,pData->m_ShowHWindow);
		  }

		  Hobject RegionUnionWhole;
		  union2(BackTransRegion,pData->m_ErrorRegist,&RegionUnionWhole);
		  pData->m_ErrorRegist=RegionUnionWhole;
	  }
  }
  
  //*检测4 －－－ 内边缘位置波动值


  int step = 7;
  HTuple SiteBianYuan;
  for (i=0; i<=((WidthBianYuan_Lenght-step)-step)-1; i+=1)
  {
    SiteBianYuan[i] = (((((((((((((HTuple(NBianYuanP[i])+HTuple(NBianYuanP[i+1]))+HTuple(NBianYuanP[i+2]))+HTuple(NBianYuanP[i+3]))+HTuple(NBianYuanP[i+4]))+HTuple(NBianYuanP[i+5]))+HTuple(NBianYuanP[i+6]))+HTuple(NBianYuanP[i+8]))+HTuple(NBianYuanP[i+9]))+HTuple(NBianYuanP[i+10]))+HTuple(NBianYuanP[i+11]))+HTuple(NBianYuanP[i+12]))+HTuple(NBianYuanP[i+13]))+HTuple(NBianYuanP[i+14]))-(HTuple(NBianYuanP[i+7])*14);

  }

  tuple_sort(SiteBianYuan, &AbsSorted);
  tuple_sort_index(SiteBianYuan, &LocationId);
  tuple_length(SiteBianYuan, &Length);

  for (i=0; i<Length; i+=1)
  {
    if ((AbsSorted[i].L())<m_Parameters.NBianYuan_SiteDeviationLow)
    {
        tuple_first_n(LocationId, i, &ResultID4);
    }
	
  }

  
  ResultID41 = HTuple();
  for (i=Length-1; i>=0; i+=-1)
  {
    if (AbsSorted[i].L()>m_Parameters.NBianYuan_SiteDeviationUp)
    {
        tuple_last_n(LocationId, i, &ResultID41);      
    }
  }
  tuple_concat(ResultID41, ResultID4, &ResultID4);
  ResultID4 += step;

  if (pData->m_isDebug)
  {

  partition_rectangle(ImageScaleMax, &JuanYuanPartitioned,1, PolarTransImageHeight);
  select_obj(JuanYuanPartitioned, &ResultDefect, ResultID4);
  polar_trans_region_inv(ResultDefect, &BackTransRegion, pData->m_center_y, pData->m_center_x,  0, 
	  HTuple(375).Rad(), pData->r_real+m_Parameters.Regional_Out, pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth, 
	  ((HTuple(375).Rad())*pData->r_real)/NumPart, m_Parameters.ROIWidth,
	  WidthOri, HeightOri, "bilinear");



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

	//*检测5 －－－ 外边缘位置波动值


  step = 7;
  HTuple SiteWBianYuan;
  for (i=0; i<=((WidthBianYuan_Lenght-step)-step)-1; i+=1)
  {
    SiteWBianYuan[i] = (((((((((((((HTuple(WBianYuanP[i])+HTuple(WBianYuanP[i+1]))+HTuple(WBianYuanP[i+2]))+HTuple(WBianYuanP[i+3]))+HTuple(WBianYuanP[i+4]))+HTuple(WBianYuanP[i+5]))+HTuple(WBianYuanP[i+6]))+HTuple(WBianYuanP[i+8]))+HTuple(WBianYuanP[i+9]))+HTuple(WBianYuanP[i+10]))+HTuple(WBianYuanP[i+11]))+HTuple(WBianYuanP[i+12]))+HTuple(WBianYuanP[i+13]))+HTuple(WBianYuanP[i+14]))-(HTuple(WBianYuanP[i+7])*14);

  }

  tuple_sort(SiteWBianYuan, &AbsSorted);
  tuple_sort_index(SiteWBianYuan, &LocationId);
  tuple_length(SiteWBianYuan, &Length);

  for (i=0; i<Length; i+=1)
  {
    if ((AbsSorted[i].L())<m_Parameters.WBianYuan_SiteDeviationLow)
    {
        tuple_first_n(LocationId, i, &ResultID51);
    }
	
  }

  

  for (i=Length-1; i>=0; i+=-1)
  {
    if (AbsSorted[i].L()>m_Parameters.WBianYuan_SiteDeviationUp)
    {
        tuple_last_n(LocationId, i, &ResultID5);      
    }
  }
  tuple_concat(ResultID5, ResultID51, &ResultID5);
  ResultID5 += step;



  if (!pData->m_isDebug)
  {
	  tuple_concat(ResultID1, ResultID2, &ResultID2);
	  tuple_concat(ResultID3, ResultID2, &ResultID3);
	  tuple_concat(ResultID3, ResultID4, &ResultID4);
	  tuple_concat(ResultID4, ResultID5, &ResultID5);
  }
	partition_rectangle(ImageScaleMax, &JuanYuanPartitioned,1, PolarTransImageHeight);
	select_obj(JuanYuanPartitioned, &ResultDefect, ResultID5);
	polar_trans_region_inv(ResultDefect, &BackTransRegion, pData->m_center_y, pData->m_center_x,  0, 
		HTuple(375).Rad(), pData->r_real+m_Parameters.Regional_Out, pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth, 
		((HTuple(375).Rad())*pData->r_real)/NumPart, m_Parameters.ROIWidth,
		WidthOri, HeightOri, "bilinear");



	count_obj(BackTransRegion,&error_number);
		
	if (error_number)
	{

		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"cyan");//青色
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
						write_string(pData->m_ShowHWindow,"CurlDll2程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

  }
