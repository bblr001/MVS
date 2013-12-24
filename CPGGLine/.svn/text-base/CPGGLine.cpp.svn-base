// CPGMianXinTest.cpp : 定义 DLL 应用程序的导出函数。
//
#pragma once

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
//#include <Windows.h>
#include <tchar.h>
#include <io.h>
#include "CPGGLine.h"
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

	if(!_stricmp(parm.c_str(),"TEST_REGIST"))
	{
		string regname = value+".reg";
		if (!_access(regname.c_str(),0))
			read_region(&m_Parameters.Test_Regist,value.c_str());
		else
		{

//#ifdef _ENGLISH
//			wstring msg = _T("Set Test Regist Error.Can't read file");
//			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
//#else
//			wstring msg = _T("请选择合适的检测区域文件");
//			MessageBox(NULL,msg.c_str(),_T("读取错误"),MB_OK);
//#endif
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
		m_Parameters.BlackMaskSize = atof(value.c_str());
	if(parm=="BThresholdLower")
		m_Parameters.BThresholdLower = atoi(value.c_str());
	if(parm=="BThresholdUpper")
		m_Parameters.BThresholdUpper = atoi(value.c_str());
	if(parm=="BDefectSize")
		m_Parameters.BDefectSize = atoi(value.c_str());
	if(parm=="BDefectSizeUpper")
		m_Parameters.BDefectSizeUpper = atoi(value.c_str());

	if(parm=="WhiteMaskSize")
		m_Parameters.WhiteMaskSize = atof(value.c_str());
	if(parm=="WThresholdLower")
		m_Parameters.WThresholdLower = atoi(value.c_str());
	if(parm=="WThresholdUpper")
		m_Parameters.WThresholdUpper = atoi(value.c_str());
	if(parm=="WDefectSize")
		m_Parameters.WDefectSize = atoi(value.c_str());
	if(parm=="WDefectSizeUpper")
		m_Parameters.WDefectSizeUpper = atoi(value.c_str());



}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject LoadRegion;
		HTuple Num;

		Hobject Test_Regist;
		Test_Regist = m_Parameters.Test_Regist;

		select_shape(Test_Regist, &LoadRegion, "area", "and", 1, 9999999);
		count_obj(LoadRegion, &Num);
		if(Num==0)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"red");
			set_tposition( pData->m_ShowHWindow,200, 0);

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGGLine Region File Reading Error");
#else
			write_string(pData->m_ShowHWindow,"CPGGLine区域文件读取错误");
#endif
			return;
		}

	
		

		Hobject image=pData->m_Image;

		HTuple    HomMat2DRotate;
		Hobject  RegionAffineTrans,region_tai;
		vector_angle_to_rigid(StoredModelCenterRow, StoredModelCenterColumn, StoredModePhi,pData->m_center_y2, pData->m_center_x2,  pData->m_orientationPhi
			, &HomMat2DRotate);
		affine_trans_region(Test_Regist, &RegionAffineTrans, HomMat2DRotate, "false");




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
				set_color(pData->m_ShowHWindow,"green");
				disp_obj(RegionScaleTrans,pData->m_ShowHWindow);
			}
		}

		reduce_domain (image, RegionScaleTrans, &region_tai);
		
	
    Hobject ExpandedImage;
    expand_domain_gray(region_tai, &ExpandedImage, 2);
    //*===================================================================
	Hobject ImageNew,WhiteLines,SelectedwhiteContours,BlackLines,SelectedBlackContours;
	
	reduce_domain(ExpandedImage,  RegionScaleTrans, &ImageNew);
	//scale_image_max (ImageNew, ImageScaleMax2)
	lines_gauss(ImageNew, &BlackLines, m_Parameters.BlackMaskSize, m_Parameters.BThresholdLower, m_Parameters.BThresholdUpper, "dark", "true", "bar-shaped", "true");
	select_contours_xld(BlackLines, &SelectedBlackContours, "contour_length", m_Parameters.BDefectSize, m_Parameters.BDefectSizeUpper, -0.5, 0.5);
	
	HTuple Number;
	HTuple  i;
	Hobject BlackRegionUnion,ObjectSelected,Region,Dilation,WhiteRegionUnion;
	HTuple Row,Col;

	count_obj(SelectedBlackContours, &Number);
	if(Number>0)
	{
		//pData->m_ErrorRegist = BLACK_POINT;
		pData->m_isFail =true;
		testItem->m_bFailSubTest = true;
		//testItem->m_ErrorMsg = "BlackPoint error";
		//return;
		gen_empty_region(&BlackRegionUnion);
		for (i=1; i<=Number; i+=1)
		{
			select_obj(SelectedBlackContours, &ObjectSelected, i);
			get_contour_xld(ObjectSelected, &Row, &Col);
			gen_region_polygon(&Region, Row, Col);
			union2(BlackRegionUnion, Region, &BlackRegionUnion);
		}
		if (pData->m_isDebug)
		{
			dilation_circle(BlackRegionUnion,&Dilation,2.5);
			set_color(pData->m_ShowHWindow,"red");
			disp_obj(Dilation,pData->m_ShowHWindow);
		}
	}

	lines_gauss(ImageNew, &WhiteLines, m_Parameters.WhiteMaskSize, m_Parameters.WThresholdLower, m_Parameters.WThresholdUpper, "light", "true", "bar-shaped", "true");
	select_contours_xld(WhiteLines, &SelectedwhiteContours, "contour_length", m_Parameters.WDefectSize, m_Parameters.WDefectSizeUpper, -0.5, 0.5);

	count_obj(SelectedwhiteContours, &Number);
	if(Number>0)
	{
		//pData->m_ErrorRegist = BLACK_POINT;
		pData->m_isFail =true;
		testItem->m_bFailSubTest = true;
		//testItem->m_ErrorMsg = "BlackPoint error";
		//return;
		gen_empty_region(&WhiteRegionUnion);
		for (i=1; i<=Number; i+=1)
		{
			select_obj(SelectedwhiteContours, &ObjectSelected, i);
			get_contour_xld(ObjectSelected, &Row, &Col);
			gen_region_polygon(&Region, Row, Col);
			union2(WhiteRegionUnion, Region, &WhiteRegionUnion);
		}
		if (pData->m_isDebug)
		{
			dilation_circle(WhiteRegionUnion,&Dilation,2.5);
			set_color(pData->m_ShowHWindow,"yellow");
			disp_obj(Dilation,pData->m_ShowHWindow);
		}
	}


			Hobject RegionUnionWhole,RegionUnion;
			union2(BlackRegionUnion,WhiteRegionUnion,&RegionUnion);
			union2(RegionUnion,pData->m_ErrorRegist,&RegionUnionWhole);
			pData->m_ErrorRegist=RegionUnionWhole;

	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 200);
#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGGLine parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"CPGGLine程序参数值出错,请重新调节参数");
#endif
		
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

}
