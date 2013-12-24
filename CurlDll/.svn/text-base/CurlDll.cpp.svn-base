// CurlDll.cpp : 定义 DLL 应用程序的导出函数。
//


#include "stdafx.h"
#include "CurlDll.h"
#include "../Inc/MData.h"





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
	//printf("Dll Call Function\r\n");
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

	if(parm=="Thred_Curl")
		m_Parameters.Thred_Curl = atoi(value.c_str())*100;

	if(parm=="Regional_Internal")
		m_Parameters.Regional_Internal = ((float)(atoi(value.c_str())))/10.0;
	//m_Parameters.Regional_Internal = -5;

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = ((float)(atoi(value.c_str())))/10.0;
	//m_Parameters.Regional_Out = -1;
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{

	double Tyy = pData->m_center_y;
	double Txx = pData->m_center_x;
	double TR = pData->r_real;
	Hobject image = pData->m_Image;
	Hlong ThredCurl = m_Parameters.Thred_Curl;

	//output: Hlong TxxError, TyyError; int CurlPosition; if CurlPosition>90, good curl;


	// 将检测区域定义成Object 合并到ProcessImage
	//Regional_Internal
	double Regional_Internal = TR+m_Parameters.Regional_Internal; //检测区域的圆内径
	double Regional_Out = TR+m_Parameters.Regional_Out; //检测区域的圆外径

	//int Regional_Internal = pData->r_real-5; //检测区域的圆内径
	//int Regional_Out = pData->r_real-1; //检测区域的圆外径

	if (ShowObject&&pData->m_isDebug)
	{
		if(abs(Regional_Out-Regional_Internal)<=2||Regional_Out<5||Regional_Internal<5)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			
			set_color(pData->m_ShowHWindow,"red");
			HTuple msg  = HTuple("Error=") +"Error Define test regist error";
			set_tposition( pData->m_ShowHWindow, 100, 100);				
			write_string(pData->m_ShowHWindow,msg);
			return;
		}

		Hobject regional1,regional2;
		set_color(pData->m_ShowHWindow,"green");
		gen_circle(&regional1,Tyy,Txx,Regional_Internal);
		disp_obj(regional1,pData->m_ShowHWindow);
		set_color(pData->m_ShowHWindow,"blue");
		gen_circle(&regional2,Tyy,Txx,Regional_Out);
		disp_obj(regional2,pData->m_ShowHWindow);

	}



	double TxxError, TyyError;
	Hobject PolarTransImage_juan, CircleCurlError;
	int i, j, k;
	int CurlPosition=200;
	double tem1;
	int tem[140];
	polar_trans_image_ext (image, &PolarTransImage_juan, Tyy, Txx, 0, 7, Regional_Internal, Regional_Out, 1400, 5, "bilinear");
	for (i=0; i<10; i++)
	{
		tem[i]=0;
		for (j=i*10; j<10+i*10; j++)
		{
			for (k=0; k<5; k++)
			{
				get_grayval(PolarTransImage_juan, k, j, &tem1);
				if (tem1>200)
				{
					tem1=200;
				}
				tem[i]=tem[i]+tem1;
			}
		}
	}
	for (i=10; i<140; i++)
	{
		tem[i]=0;
		for (j=i*10; j<10+i*10; j++)
		{
			for (k=0; k<5; k++)
			{
				get_grayval(PolarTransImage_juan, k, j, &tem1);
				if (tem1>200)
				{
					tem1=200;
				}
				tem[i]=tem[i]+tem1;
			}
		}
		if (abs(tem[i-10]+tem[i-9]+tem[i-8]+tem[i-7]-8*tem[i-5]+tem[i-3]+tem[i-2]+tem[i-1]+tem[i])>ThredCurl)
		{
			ThredCurl=abs(tem[i-10]+tem[i-9]+tem[i-8]+tem[i-7]-8*tem[i-5]+tem[i-3]+tem[i-2]+tem[i-1]+tem[i]);
			CurlPosition=i-5;
		}
	}
	if (abs(tem[58]+tem[57]+tem[0]+tem[59]-8*tem[2]+tem[6]+tem[7]+tem[4]+tem[5])>ThredCurl)
	{
		ThredCurl=abs(tem[58]+tem[57]+tem[0]+tem[59]-8*tem[2]+tem[6]+tem[7]+tem[4]+tem[5]);
		CurlPosition=2;
	}
	if (abs(tem[58]+tem[1]+tem[0]+tem[59]-8*tem[3]+tem[6]+tem[7]+tem[8]+tem[5])>ThredCurl)
	{
		ThredCurl=abs(tem[58]+tem[1]+tem[0]+tem[59]-8*tem[3]+tem[6]+tem[7]+tem[8]+tem[5]);
		CurlPosition=3;
	}
	if (abs(tem[2]+tem[1]+tem[0]+tem[59]-8*tem[4]+tem[6]+tem[7]+tem[8]+tem[9])>ThredCurl)
	{
		ThredCurl=abs(tem[2]+tem[1]+tem[0]+tem[59]-8*tem[4]+tem[6]+tem[7]+tem[8]+tem[9]);
		CurlPosition=4;
	}

	if (CurlPosition>190)
	{
		//AfxMessageBox("good juanbian");
		return;

	}

	TxxError=Txx+TR*cos(6.3*CurlPosition/126);
	TyyError=Tyy-TR*sin(6.3*CurlPosition/126);

	pData->m_isFail = true;
	testItem->m_bFailSubTest = true;
	testItem->m_ErrorX = TxxError;
	testItem->m_ErrorY = TyyError;

	if (pData->m_isDebug)
	{
		Hobject circle;
		gen_circle(&circle,testItem->m_ErrorY,testItem->m_ErrorX,testItem->m_ErrorR);
		disp_obj(circle,pData->m_ShowHWindow);
	}
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		//if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 200);
			write_string(pData->m_ShowHWindow,"程序参数值出错,请重新调节参数");
		}
	}

}

