// CPGMianXinTest.cpp : 定义 DLL 应用程序的导出函数。
//
#pragma once

#include "stdafx.h"

#include <stdio.h>
#include <iostream>
//#include <Windows.h>
#include <tchar.h>
#include <io.h>
#include "CPGGSurface.h"
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
		

	if(parm=="BThresholdValue")
		m_Parameters.BThresholdValue = (float)atoi(value.c_str())/1000;

	if(parm=="BDefectSize")
		m_Parameters.BDefectSize = atoi(value.c_str());

	if(parm=="WThresholdValue")
		m_Parameters.WThresholdValue = -(float)atoi(value.c_str())/1000;

	if(parm=="WDefectSize")
		m_Parameters.WDefectSize = atoi(value.c_str());



}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject LoadRegion;
		HTuple Num;

		Hobject Test_Regist;
		Test_Regist = m_Parameters.Test_Regist;
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

			set_color(pData->m_ShowHWindow,"red");
			set_tposition( pData->m_ShowHWindow,200, 0);

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGGSurface Region File Reading Error");
#else
			write_string(pData->m_ShowHWindow,"CPGGSurface区域文件读取错误");
#endif
			return;
		}

	
		

		Hobject image=pData->m_Image;

		Hlong error_number;

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
		
	

	Hobject ExpandedImage,DerivGauss,ImageReduced1,Regions,ConnectedRegions1,SelectedRegions1;
	Hobject Regions1,ConnectedRegions2,SelectedRegions2,RegionUnion;

    expand_domain_gray(region_tai, &ExpandedImage, 2);
    //*===================================================================

    derivate_gauss(ExpandedImage, &DerivGauss, 5, "mean_curvature");

    reduce_domain(DerivGauss, RegionScaleTrans, &ImageReduced1);



    threshold(ImageReduced1, &Regions, m_Parameters.BThresholdValue, 1);
    connection(Regions, &ConnectedRegions1);
    select_shape(ConnectedRegions1, &SelectedRegions1, "area", "and", m_Parameters.BDefectSize, 99999);

	Hobject Dilation;
	count_obj(SelectedRegions1,&error_number);

	if (error_number)
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		if (pData->m_isDebug)
		{

			dilation_circle(SelectedRegions1,&Dilation,2.5);
			set_color(pData->m_ShowHWindow,"red");
			disp_obj(Dilation,pData->m_ShowHWindow);
		}

	}


    threshold(ImageReduced1, &Regions1, -1, m_Parameters.WThresholdValue);
    connection(Regions1, &ConnectedRegions2);
    select_shape(ConnectedRegions2, &SelectedRegions2, "area", "and", m_Parameters.WDefectSize, 99999);

	count_obj(SelectedRegions2,&error_number);

	if (error_number)
	{

		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		if (pData->m_isDebug)
		{
			dilation_circle(SelectedRegions2,&Dilation,2.5);
			set_color(pData->m_ShowHWindow,"yellow");
			disp_obj(Dilation,pData->m_ShowHWindow);
		}

	}


	union2(SelectedRegions2,SelectedRegions1,&RegionUnion);
	Hobject RegionUnionWhole;
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
			write_string(pData->m_ShowHWindow,"CPGGSurface parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"CPGGSurface程序参数值出错,请重新调节参数");
#endif
		
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

}

