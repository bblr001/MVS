// CPGMianXinTest.cpp : 定义 DLL 应用程序的导出函数。
//
#pragma once

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
//#include <Windows.h>
#include <tchar.h>
#include <io.h>
#include "CPGDynThreshed2.1Sub.h"
#include "../Inc/MData.h"


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
	//m_ProcessName ="MianXinTestAuto";
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
//====================================================================================


		Hobject  EmptyRegion;
		gen_empty_region(&EmptyRegion);


	if(!_stricmp(parm.c_str(),"TEST_REGIST"))
	{
		string regname = value+".reg";
		if (!_access(regname.c_str(),0))
			read_region(&m_Parameters.Test_Regist,value.c_str());
		else
		{
//#ifdef _ENGLISH
//			wstring msg = _T("Set Main Test Regist Error.Can't read file");
//			MessageBox(NULL,msg.c_str(),_T("Read Main File Error"),MB_OK);
//#else
//			wstring msg = _T("请选择合适的主要检测区域文件");
//			MessageBox(NULL,msg.c_str(),_T("读取主文件错误"),MB_OK);
//#endif
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
//================================================================================

	if(!_stricmp(parm.c_str(),"TEST_REGIST_SUB"))
	{
		string regname = value+".reg";
		if (!_access(regname.c_str(),0))
			read_region(&m_Parameters.Test_Regist_Sub,value.c_str());
		else
		{
//#ifdef _ENGLISH
//			wstring msg = _T("Set Minor Test Regist Error.Can't read file");
//			MessageBox(NULL,msg.c_str(),_T("Read Minor File Error"),MB_OK);
//#else
//			wstring msg = _T("请选择合适的次要检测区域文件");
//			MessageBox(NULL,msg.c_str(),_T("读取次文件错误"),MB_OK);
//#endif
			m_Parameters.Test_Regist_Sub=EmptyRegion;
		}

		string datname = value+".dat";
		if (!_access(datname.c_str(),0))
		{
			TCHAR vv[64];
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModePhi"),_T("0.0"),vv,sizeof(vv),(s2ws(datname)).c_str());
			StoredModePhiSub= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterRow"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredModelCenterRowSub= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterColumn"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredModelCenterColumnSub= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredRadius"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredRadiusSub= _tstof(vv);
		}
	}

	//====================================================================================
	if(parm=="BlackMaskSize")
		m_Parameters.BlackMaskSize= atoi(value.c_str());
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
	if(parm=="WhitePointDynThresh")
		m_Parameters.WhitePointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="WhitePointSize")
		m_Parameters.WhitePointSize=atoi(value.c_str());
	if(parm=="SeriousWhitePointDynThresh")
		m_Parameters.SeriousWhitePointDynThresh= ((float)(atof(value.c_str())));
	if(parm=="SeriousWhitePointSize")
		m_Parameters.SeriousWhitePointSize=atoi(value.c_str());


	//if(parm=="ZoomRegion")
	//	m_Parameters.ZoomRegion= atoi(value.c_str());


	//if(parm=="ZoomSubRegion")
	//	m_Parameters.ZoomSubRegion= atoi(value.c_str());

	if(parm=="erosion")
		m_Parameters.erosion= atof(value.c_str());
	if(parm=="ShapeThreshold")
		m_Parameters.ShapeThreshold= atoi(value.c_str());
	if(parm=="ShapeSize")
		m_Parameters.ShapeSize= atoi(value.c_str());


}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		
		Hobject LoadRegion;
		HTuple Num;

		Hobject Test_Regist,SubTest_Regist;
		Test_Regist = m_Parameters.Test_Regist;
		SubTest_Regist = m_Parameters.Test_Regist_Sub;
		//if (m_Parameters.ZoomRegion>0)
		//{
		//	dilation_circle (m_Parameters.Test_Regist, &Test_Regist, m_Parameters.ZoomRegion);
		//}
		//if (m_Parameters.ZoomRegion<0)
		//{
		//	erosion_circle (m_Parameters.Test_Regist, &Test_Regist, -m_Parameters.ZoomRegion);
		//}

		select_shape(Test_Regist, &LoadRegion, "area", "and", 1, 9999999);

		count_obj(LoadRegion, &Num);
		if(Num==0)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"cyan");
			set_tposition( pData->m_ShowHWindow,160, 0);

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGDynThreshed2.1Sub Main Region File Reading Error");
#else
			write_string(pData->m_ShowHWindow,"CPGDynThreshed2.1Sub主要区域文件读取错误");
#endif
			return;
		}



		//if (m_Parameters.ZoomSubRegion>0)
		//{
		//	dilation_circle (m_Parameters.Test_Regist_Sub, &SubTest_Regist, m_Parameters.ZoomSubRegion);
		//}
		//if (m_Parameters.ZoomSubRegion<0)
		//{
		//	erosion_circle (m_Parameters.Test_Regist_Sub, &SubTest_Regist, -m_Parameters.ZoomSubRegion);
		//}


		select_shape(SubTest_Regist, &LoadRegion, "area", "and", 1, 9999999);
		count_obj(LoadRegion, &Num);
		if(Num==0)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"cyan");
			set_tposition( pData->m_ShowHWindow,180, 0);
#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGDynThreshed2.1Sub Minor Region File Reading Error");
#else
			write_string(pData->m_ShowHWindow,"CPGDynThreshed2.1Sub次要区域文件读取错误");
#endif
			return;
		}


		
		Hobject image=pData->m_Image;

		Hlong error_number;
		HTuple   HomMat2DRotate;
		Hobject  RegionAffineTrans,region_tai;

		HTuple HomMat2DIdentity,HomMat2DScale;
		HTuple AffineTransArea,AffineTransRow,AffineTransColumn;
		Hobject RegionScaleTrans,RegionScaleTransSub;
		double Index;
//=========================================================================================================
		vector_angle_to_rigid(StoredModelCenterRow, StoredModelCenterColumn, StoredModePhi,pData->m_center_y2, pData->m_center_x2, pData->m_orientationPhi,&HomMat2DRotate);
		affine_trans_region(Test_Regist, &RegionAffineTrans, HomMat2DRotate, "false");
		Index=pData->r_real/StoredRadius;
		hom_mat2d_identity (&HomMat2DIdentity);
		area_center (RegionAffineTrans, &AffineTransArea, &AffineTransRow, &AffineTransColumn);
		hom_mat2d_scale (HomMat2DIdentity, Index, Index, AffineTransRow, AffineTransColumn, &HomMat2DScale);
		affine_trans_region (RegionAffineTrans, &RegionScaleTrans, HomMat2DScale, "false");
//==========================================================================================================
		vector_angle_to_rigid(StoredModelCenterRowSub, StoredModelCenterColumnSub, StoredModePhiSub,pData->m_center_y3, pData->m_center_x3, pData->m_orientationPhi3,&HomMat2DRotate);
		affine_trans_region(SubTest_Regist, &RegionAffineTrans, HomMat2DRotate, "false");
		Index=pData->r_real/StoredRadiusSub;
		hom_mat2d_identity (&HomMat2DIdentity);
		area_center (RegionAffineTrans, &AffineTransArea, &AffineTransRow, &AffineTransColumn);
		hom_mat2d_scale (HomMat2DIdentity, Index, Index, AffineTransRow, AffineTransColumn, &HomMat2DScale);
		affine_trans_region (RegionAffineTrans, &RegionScaleTransSub, HomMat2DScale, "false");

		difference(RegionScaleTrans, RegionScaleTransSub, &RegionScaleTrans);

		if (ShowObject&&pData->m_isDebug)
		{
			{
				set_color(pData->m_ShowHWindow,"green");
				disp_obj(RegionScaleTrans,pData->m_ShowHWindow);
			}
		}

		reduce_domain (image, RegionScaleTrans, &region_tai);
		
		
	

		Hobject  BlackImageMean,WhiteImageMean;
		Hobject  BlackPointDynThresh, BLACK_POINT, SeriousBlackPointDynThresh;
		Hobject  SeriousBlackConnected, SERIOUS_BlackPoint;
		Hobject  WhitePointDynThresh, WHITE_POINT, SeriousWhitePointDynThresh;
		Hobject  SeriousWhiteConnected, SERIOUS_WhitePoint;
		Hlong    Number;
		Hobject  Dilation;


	//*===================================================================

		mean_image(region_tai, &BlackImageMean, m_Parameters.BlackMaskSize, m_Parameters.BlackMaskSize);


  dyn_threshold(region_tai, BlackImageMean, &BlackPointDynThresh,m_Parameters.BlackPointDynThresh, "dark");
  select_shape(BlackPointDynThresh, &BLACK_POINT, "area", "and", m_Parameters.BlackPointSize, 99999);
  count_obj(BLACK_POINT, &Number);
  if (Number)
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
  //*找单一块极黑缺陷，适用于伤的比较深，污点比较黑的情况
  dyn_threshold(region_tai, BlackImageMean, &SeriousBlackPointDynThresh,m_Parameters.SeriousBlackPointDynThresh, "dark");
  connection(SeriousBlackPointDynThresh, &SeriousBlackConnected);
  select_shape(SeriousBlackConnected, &SERIOUS_BlackPoint, "area", "and",m_Parameters.SeriousBlackPointSize, 99999);
  count_obj(SERIOUS_BlackPoint, &Number);
  if (Number)
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
  mean_image(region_tai, &WhiteImageMean, m_Parameters.WhiteMaskSize, m_Parameters.WhiteMaskSize);

  //*找大范围白缺陷
  dyn_threshold(region_tai, WhiteImageMean, &WhitePointDynThresh, m_Parameters.WhitePointDynThresh, "light");
  select_shape(WhitePointDynThresh, &WHITE_POINT, "area", "and", m_Parameters.WhitePointSize, 99999);
  count_obj(WHITE_POINT, &Number);
  if (Number)
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
  //*找单一块极白污点

  dyn_threshold(region_tai, WhiteImageMean, &SeriousWhitePointDynThresh, m_Parameters.SeriousWhitePointDynThresh, "light");
  connection(SeriousWhitePointDynThresh, &SeriousWhiteConnected);
  select_shape(SeriousWhiteConnected, &SERIOUS_WhitePoint, "area", "and",m_Parameters.SeriousWhitePointSize, 99999);
  count_obj(SERIOUS_WhitePoint, &Number);
  if (Number)
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




		Hobject RegionErosion, ImageReduced2,ModelImages1,ModelRegions1,ConnectedRegions2,SelectedRegions2;

		erosion_circle(RegionScaleTrans, &RegionErosion, m_Parameters.erosion);
		reduce_domain(image, RegionErosion, &ImageReduced2);
		inspect_shape_model(ImageReduced2, &ModelImages1, &ModelRegions1, 1, m_Parameters.ShapeThreshold);
		connection(ModelRegions1, &ConnectedRegions2);
		select_shape(ConnectedRegions2, &SelectedRegions2, "area", "and", m_Parameters.ShapeSize, 99999);
		


		count_obj(SelectedRegions2,&error_number);
		if (error_number)
		{
			//pData->m_ErrorRegist = SERIOUS_WhitePoint;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "SeriousWhitePoint error";
				  if (pData->m_isDebug)
			{
				dilation_circle(SelectedRegions2,&Dilation,2.5);
				set_color(pData->m_ShowHWindow,"blue");
				disp_obj(Dilation,pData->m_ShowHWindow);
			}
		}




		Hobject RegionUnionBlack,RegionUnionWhite,RegionUnionWhole,Union;
		union2(BLACK_POINT, SERIOUS_BlackPoint, &RegionUnionBlack);
		union2(WHITE_POINT, SERIOUS_WhitePoint, &RegionUnionWhite);
		union2(RegionUnionBlack, RegionUnionWhite, &Union);
		union2(Union, SelectedRegions2, &RegionUnionWhole);
		union2(RegionUnionWhole, pData->m_ErrorRegist, &RegionUnionWhole);

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
			write_string(pData->m_ShowHWindow,"CPGDynThreshed2.1Sub parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"CPGDynThreshed2.1Sub程序参数值出错,请重新调节参数");
#endif
		
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

}
