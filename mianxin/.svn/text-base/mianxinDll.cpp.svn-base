// mianxin.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"



#include "mianxinDll.h"
#include "..\Inc\MData.h"



#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}

CDoProcess::CDoProcess()
{
	HException::InstallHHandler(&MyHalconExceptionHandler);
	ShowObject=false;
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

	if(parm=="Thred_white")
		m_Parameters.Thred_white = atoi(value.c_str());
	if(parm=="Thred_black")
		m_Parameters.Thred_black= atoi(value.c_str());
 	if(parm=="Thred_white_point")
 		m_Parameters.Thred_white_point= atoi(value.c_str());
 	if(parm=="Thred_black_point")
 		m_Parameters.Thred_black_point= atoi(value.c_str());
	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atoi(value.c_str());
	if(parm=="Regional_Internal")
		m_Parameters.Regional_Internal = atoi(value.c_str());
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hlong Thred_white=m_Parameters.Thred_white;
		Hlong Thred_black=m_Parameters.Thred_black;
		Hlong Thred_white_point=m_Parameters.Thred_white_point;
		Hlong Thred_black_point=m_Parameters.Thred_black_point;

		Hobject image=pData->m_Image;

		Hlong Tyy,Txx,TR;
		Hlong error_number;

		Tyy = pData->m_center_y;
		Txx = pData->m_center_x;
		TR = pData->r_real;

		Hlong Regional_Internal=0;
		
		//Regional_Internal
		Hlong Regional_Out = TR+m_Parameters.Regional_Out; //检测区域的圆外径
		if (m_Parameters.Regional_Internal!=0)
		{
			Regional_Internal = TR+m_Parameters.Regional_Internal; //检测区域的圆内径
			if (Regional_Internal<=0)
			{
				Regional_Internal=0;
			}

		}
		
		
		if (ShowObject&&pData->m_isDebug)
		{
			// 将检测区域定义成Object 合并到ProcessImage


			if(Regional_Out<5||Regional_Out>TR)
			{
				pData->m_isFail = true;
				testItem->m_bFailSubTest = true;
				set_color(pData->m_ShowHWindow,"red");
				HTuple msg  = HTuple("Error=") +"Error Define test regist error";

				set_tposition( pData->m_ShowHWindow, 100, 100);				
				write_string(pData->m_ShowHWindow,msg);

				testItem->m_ErrorY = 1;
				testItem->m_ErrorX = 1;
				testItem->m_ErrorR = 1;
				return;
			}

			set_color(pData->m_ShowHWindow,"blue");
			Hobject regional;
			gen_circle(&regional,Tyy,Txx,Regional_Out);
			disp_obj(regional,pData->m_ShowHWindow);

			set_color(pData->m_ShowHWindow,"green");
			gen_circle(&regional,Tyy,Txx,Regional_Internal);
			disp_obj(regional,pData->m_ShowHWindow);
		}

		Hobject taiOut,taiInternal,RegionDifference, region_tai, mean_tai, white_tai, connect_tai, select_tai,em_tai, union_tai, dila_tai, ske_tai, error_tai, err;

		Hobject c1, c2, diff_taia, region_taia;

		gen_circle(&taiOut, Tyy, Txx, Regional_Out-2);
		if (Regional_Internal!=0)
		{
			gen_circle(&taiInternal, Tyy, Txx, Regional_Internal);
			difference(taiOut, taiInternal, &RegionDifference);
			change_domain (image, RegionDifference, &region_tai);
		}

		else
		{
			change_domain (image, taiOut, &region_tai);
		}
		
		mean_image (region_tai, &mean_tai, 2, 2);
		threshold (mean_tai, &white_tai, Thred_white, 255);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &select_tai, "area", "and", 10, 1000);
		union1 (select_tai, &union_tai);
		dilation_circle (union_tai, &dila_tai, 2);
		skeleton (dila_tai, &ske_tai);
		connection (ske_tai, &error_tai);
		select_shape (error_tai, &err, "outer_radius", "and", 10, 10000);

		count_obj(err, &error_number);

		if (error_number)
		{
			set_color(pData->m_ShowHWindow,"white");
			pData->m_ErrorRegist = err;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			disp_obj(err,pData->m_ShowHWindow);
			//return;
		}

		// //////////////////////////////////////////////////////////////////////////////black

		threshold (mean_tai, &white_tai, 0, Thred_black);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &select_tai, "area", "and", 50, 1000);
		union1 (select_tai, &union_tai);
		dilation_circle (union_tai, &dila_tai, 1);
		skeleton (dila_tai, &ske_tai);
		connection (ske_tai, &error_tai);
		select_shape (error_tai, &err, "outer_radius", "and", 15, 10000);

		count_obj(err, &error_number);

		if (error_number)
		{
			set_color(pData->m_ShowHWindow,"black");
			pData->m_ErrorRegist = err;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			disp_obj(err,pData->m_ShowHWindow);
			//return;
		}
		/////////////////////////////////////////////////////////////////////////////////point


		threshold (mean_tai, &white_tai, 0, Thred_black_point);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &err, "area", "and", 3, 1000);
		count_obj(err, &error_number);

		if (error_number)
		{
			set_color(pData->m_ShowHWindow,"blue");
			pData->m_ErrorRegist = err;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			disp_obj(err,pData->m_ShowHWindow);
			//return;
		}


		////////////////////////////////////////////////////////////////////////////////press

		threshold (mean_tai, &white_tai, Thred_white_point,255);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &err, "area", "and", 3, 1000);

		count_obj(err, &error_number);

		if (error_number)
		{
			set_color(pData->m_ShowHWindow,"green");
			pData->m_ErrorRegist = err;
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			disp_obj(err,pData->m_ShowHWindow);
			//return;
		}

	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		testItem->m_ErrorY = 1;
		testItem->m_ErrorX = 1;
		testItem->m_ErrorR = 4;
	}

}