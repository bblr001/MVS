// CPGMianXinTest.cpp : 定义 DLL 应用程序的导出函数。
//
#pragma once

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
//#include <Windows.h>
#include <tchar.h>
#include <io.h>
#include "CPGMianXinTest.h"
#include "..\Inc\MData.h"


using namespace std;

std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, "C");
	return result;
}



#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}

CDoProcess::CDoProcess()
{
	ShowObject=false;
	//m_ProcessName ="MianXinTestAuto";
	HException::InstallHHandler(&MyHalconExceptionHandler);

}


void CDoProcess::SetParmeter(string parm,string value)
{
	if(!_stricmp(parm.c_str(),"TEST_REGIST"))
	{
		string regname = value+".reg";
		if (!_access(regname.c_str(),0))
			read_region(&m_Parameters.Test_Regist,value.c_str());
		else
		{
			//wstring msg = _T("Set Test Regist Error.Can't read file");
			//MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);

			Hobject  EmptyRegion;
			gen_empty_region(&EmptyRegion);

			m_Parameters.Test_Regist=EmptyRegion;
		}

		string datname = value+".dat";
		if (!_access(datname.c_str(),0))
		{
			TCHAR vv[64];
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModePhi"),_T("0.0"),vv,sizeof(vv),(s2ws(datname)).c_str());
			StoredModePhi= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterRow"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredModelCenterRow= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterColumn"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredModelCenterColumn= _tstof(vv);

			GetPrivateProfileString(_T("StoredDATA"),_T("StoredRadius"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredRadius= _tstof(vv);
		}
	}
		
	if(parm=="BlackMaskSize")
		m_Parameters.BlackMaskSize= atoi(value.c_str());
	if(parm=="BlackLineDynThresh")
		m_Parameters.BlackLineDynThresh= ((float)(atof(value.c_str())));
	if(parm=="BlackLinesLength")
		m_Parameters.BlackLinesLength= atoi(value.c_str());
	if(parm=="BlackPointDynThresh")
		m_Parameters.BlackPointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="BlackPointSize")
		m_Parameters.BlackPointSize= atoi(value.c_str());
	if(parm=="SeriousBlackPointDynThresh")
		m_Parameters.SeriousBlackPointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="SeriousBlackPointSize")
		m_Parameters.SeriousBlackPointSize= atoi(value.c_str());


	if(parm=="WhiteMaskSize")
		m_Parameters.WhiteMaskSize= atoi(value.c_str());
	if(parm=="WhiteLineDynThresh")
		m_Parameters.WhiteLineDynThresh= ((float)(atof(value.c_str())));
	if(parm=="WhiteLinesLength")
		m_Parameters.WhiteLinesLength= atoi(value.c_str());
	if(parm=="WhitePointDynThresh")
		m_Parameters.WhitePointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="WhitePointSize")
		m_Parameters.WhitePointSize=atoi(value.c_str());
	if(parm=="SeriousWhitePointDynThresh")
		m_Parameters.SeriousWhitePointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="SeriousWhitePointSize")
		m_Parameters.SeriousWhitePointSize=atoi(value.c_str());

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
		
		Hobject LoadRegion;
		HTuple Num;

		select_shape(m_Parameters.Test_Regist, &LoadRegion, "area", "and", 1, 99999);
		count_obj(LoadRegion, &Num);
		if(Num==0)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"red");
			set_tposition( pData->m_ShowHWindow,200, 0);

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGMianXinTest Region File Reading Error");
#else
			write_string(pData->m_ShowHWindow,"CPGMianXinTest区域文件读取错误");
#endif
		}
		
		
		
		Hobject image=pData->m_Image;

		Hlong error_number;

		HTuple    HomMat2DRotate;
		Hobject  RegionAffineTrans,region_tai;
		vector_angle_to_rigid(StoredModelCenterRow, StoredModelCenterColumn, StoredModePhi,pData->m_center_y, pData->m_center_x,  pData->m_orientationPhi
			, &HomMat2DRotate);
		affine_trans_region(m_Parameters.Test_Regist, &RegionAffineTrans, HomMat2DRotate, "false");

		HTuple HomMat2DIdentity,HomMat2DScale;
		HTuple AffineTransArea,AffineTransRow,AffineTransColumn;
		Hobject RegionScaleTrans;


		double Index=pData->r_real/StoredRadius;
		hom_mat2d_identity (&HomMat2DIdentity);

		area_center (RegionAffineTrans, &AffineTransArea, &AffineTransRow, &AffineTransColumn);
		
		hom_mat2d_scale (HomMat2DIdentity, Index, Index, AffineTransRow, AffineTransColumn, &HomMat2DScale);

		affine_trans_region (RegionAffineTrans, &RegionScaleTrans, HomMat2DScale, "false");


		if (ShowObject&&pData->m_isDebug)
		{
			{
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(RegionScaleTrans,pData->m_ShowHWindow);
			}
		}
		reduce_domain (image, RegionScaleTrans, &region_tai);

		Hobject  Ellipse, ImageReduced, ModelImages;
		Hobject  ModelRegions, ConnectedRegions, SelectedRegions;
		Hobject  Circle, MianXinCircle, BlackImageMean;
		Hobject  BlackDynThresh, BlackConnectedRegions, InterestBlackRegion;
		Hobject  BlackRegionDilation, BlackSkeleton, BLACK, BlackPointDynThresh;
		Hobject  BlackPointConnected, BLACK_POINT, SeriousBlackPointDynThresh;
		Hobject  SeriousBlackPointConnected,SeriousWhitePointConnected;
		Hobject  SERIOUS_BlackPoint, WhiteImageMean, WhiteDynThresh;
		Hobject  WhiteConnectedRegions, InterestWhiteRegion, WhiteRegionDilation;
		Hobject  WhiteSkeleton, WHITE, WhitePointDynThresh, WhitePointConnected;
		Hobject  WHITE_POINT, SeriousWhitePointDynThresh, SERIOUS_WhitePoint;

		Hobject  Dilation;


			//*===================================================================
		//*找黑色划痕与污点

		//*对图像进行均值化处理，
		//*若盖面光源打黑，建议使用数值3，3，对于盖面打白建议使用数值9，9至23，23
		//*若盖面光源打白，相反取值
		//*简言之，对于黑盖面找黑时，需均匀度很高用3，3，白盖面黑白对比度大，无需很高的均匀性
		mean_image(region_tai, &BlackImageMean, m_Parameters.BlackMaskSize, m_Parameters.BlackMaskSize);

		//*找划痕
		//*黑色划痕动态阀值，建议选取值3.5以上
		dyn_threshold(region_tai, BlackImageMean, &BlackDynThresh, m_Parameters.BlackLineDynThresh, "dark");
		connection(BlackDynThresh, &BlackConnectedRegions);
		select_shape(BlackConnectedRegions, &InterestBlackRegion, "area", "and", 5, 99999);
		count_obj(InterestBlackRegion,&error_number);
		if (error_number)
		{
			dilation_circle(InterestBlackRegion, &BlackRegionDilation, 3.5);
			skeleton(BlackRegionDilation, &BlackSkeleton);

			//*划痕大小，建议8个像素值，可根据需要选取更小或者更大，但越小发生误排的概率也越大
			select_shape(BlackSkeleton, &BLACK, "area", "and", m_Parameters.BlackLinesLength, 99999);
			count_obj(BLACK,&error_number);
			if(error_number)
			{
				//pData->m_ErrorRegist = BLACK;
				pData->m_isFail =true;
				testItem->m_bFailSubTest = true;
				//testItem->m_ErrorMsg = "BlackLines error";
				//return;
				if (pData->m_isDebug)
				{
					dilation_circle(BLACK,&Dilation,2.5);
					set_color(pData->m_ShowHWindow,"red");
					disp_obj(Dilation,pData->m_ShowHWindow);
				}
			}

		}
	    
		//*找黑污点
		//*黑污点动态阀值，建议选取值3.5以上，最好能比黑色划痕动态阀值大，以便清晰的提取点
		dyn_threshold(region_tai, BlackImageMean, &BlackPointDynThresh, m_Parameters.BlackPointDynThresh, "dark");
		/*connection(BlackPointDynThresh, &BlackPointConnected);*/
		//*黑污点大小，建议5个像素值以上，可根据需要选取更小或者更大，但越小发生误排的概率也越大
		select_shape(BlackPointDynThresh, &BLACK_POINT, "area", "and", m_Parameters.BlackPointSize, 99999);
		count_obj(BLACK_POINT,&error_number);
		if(error_number)
		{
			//pData->m_ErrorRegist = BLACK_POINT;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "BlackPoint error";
			//return;
			if (pData->m_isDebug)
			{
				dilation_circle(BLACK_POINT,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}
		}

		//*找极黑污点
		//*极黑污点动态阀值 ,建议选取数值20以上
		dyn_threshold(region_tai, BlackImageMean, &SeriousBlackPointDynThresh, m_Parameters.SeriousBlackPointDynThresh, "dark");
		//*极黑点大小，建议选1开始
		connection(SeriousBlackPointDynThresh, &SeriousBlackPointConnected);
		select_shape(SeriousBlackPointConnected, &SERIOUS_BlackPoint, "area", "and",m_Parameters.SeriousBlackPointSize, 99999);
		count_obj(SERIOUS_BlackPoint,&error_number);
		if(error_number)
		{
			//pData->m_ErrorRegist = SERIOUS_BlackPoint;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "SeriousBlackPoint error";
			//return;
			if (pData->m_isDebug)
			{
				dilation_circle(SERIOUS_BlackPoint,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}
		}


		//*===================================================================
		//*找白色划痕与污点

		//*对图像进行均值化处理，
		//*若盖面光源打黑，建议使用数值9，9至23，23，对于盖面打白建议使用数值3，3
		//*若盖面光源打白，相反取值
		//*简言之，对于白盖面找白时，需均匀度很高用3，3，黑盖面黑白对比度大，无需很高的均匀性
		mean_image(region_tai, &WhiteImageMean, m_Parameters.WhiteMaskSize,m_Parameters.WhiteMaskSize);
		//*找划痕

		//*白色划痕动态阀值，建议选取值3.5以上
		dyn_threshold(region_tai, WhiteImageMean, &WhiteDynThresh, m_Parameters.WhiteLineDynThresh, "light");
		connection(WhiteDynThresh, &WhiteConnectedRegions);

		select_shape(WhiteConnectedRegions, &InterestWhiteRegion, "area", "and", 5, 99999);
		count_obj(InterestWhiteRegion,&error_number);
		 if (error_number)
		 {
			 dilation_circle(InterestWhiteRegion, &WhiteRegionDilation, 3.5);
			 skeleton(WhiteRegionDilation, &WhiteSkeleton);
			 //*划痕大小，建议8个像素值，可根据需要选取更小或者更大，但越小发生误排的概率也越大
			 select_shape(WhiteSkeleton, &WHITE, "area", "and", m_Parameters.WhiteLinesLength, 99999);
			 count_obj(WHITE,&error_number);
			 if (error_number)
			 {
				 //pData->m_ErrorRegist = WHITE;
				 pData->m_isFail =true;
				 testItem->m_bFailSubTest = true;
				 //testItem->m_ErrorMsg = "WhiteLines error";
				 //return;
				 if (pData->m_isDebug)
				 {
					 dilation_circle(WHITE,&Dilation,2.5);
					 set_color(pData->m_ShowHWindow,"yellow");
					 disp_obj(Dilation,pData->m_ShowHWindow);
				 }
			 }

		 }

		//*找白污点
		//*白污点动态阀值，建议选取值3.5以上，最好能比白色划痕动态阀值大，以便清晰的提取点
		dyn_threshold(region_tai, WhiteImageMean, &WhitePointDynThresh, m_Parameters.WhitePointDynThresh, "light");
		/*connection(WhitePointDynThresh, &WhitePointConnected);*/
		//*白污点大小，建议5个像素值以上，可根据需要选取更小或者更大，但越小发生误排的概率也越大
		select_shape(WhitePointDynThresh, &WHITE_POINT, "area", "and", m_Parameters.WhitePointSize, 99999);
		count_obj(WHITE_POINT,&error_number);
		if (error_number)
		{
			//pData->m_ErrorRegist = WHITE_POINT;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "WhitePoint error";
		if (pData->m_isDebug)
		 {
			 dilation_circle(WHITE_POINT,&Dilation,2.5);
			 set_color(pData->m_ShowHWindow,"yellow");
			 disp_obj(Dilation,pData->m_ShowHWindow);
		 }
		}

		//*找极白污点

		//*极白污点动态阀值 ,建议选取数值20以上
		dyn_threshold(region_tai, WhiteImageMean, &SeriousWhitePointDynThresh, m_Parameters.SeriousWhitePointDynThresh, "light");
		//*极白点大小，建议选1开始
		connection(SeriousWhitePointDynThresh, &SeriousWhitePointConnected);		
		select_shape(SeriousWhitePointConnected, &SERIOUS_WhitePoint, "area", "and", m_Parameters.SeriousWhitePointSize, 99999);
		count_obj(SERIOUS_WhitePoint,&error_number);
		if (error_number)
		{
			//pData->m_ErrorRegist = SERIOUS_WhitePoint;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "SeriousWhitePoint error";
			if (pData->m_isDebug)
			{
				dilation_circle(SERIOUS_WhitePoint,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"yellow");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}
		}

		Hobject RegionUnionBlack,RegionUnionWhite,RegionUnionWhole,Union;
		union2(BLACK,BLACK_POINT,&Union);
		union2(Union, SERIOUS_BlackPoint, &RegionUnionBlack);
		union2(WHITE,WHITE_POINT,&Union);
		union2(Union, SERIOUS_WhitePoint, &RegionUnionWhite);
		union2(RegionUnionBlack, RegionUnionWhite, &RegionUnionWhole);
		union2(pData->m_ErrorRegist, RegionUnionWhole, &RegionUnionWhole);
		//dilation_circle(RegionUnionWhole, &RegionDilation, 2.5);
		pData->m_ErrorRegist=RegionUnionWhole;

	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 200);
#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGMianXinTest parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"CPGMianXinTest程序参数值出错,请重新调节参数");
#endif

		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;

   }
}