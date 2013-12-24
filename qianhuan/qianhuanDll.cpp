// qianhuan.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "../Inc/MData.h"
#include "qianhuanDll.h"




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

// 	if(parm=="Thred_qian_a")
// 		m_Parameters.Thred_qian_a= atoi(value.c_str());
	if(parm=="Thred_qian_b")
		m_Parameters.Thred_qian_b= atoi(value.c_str())*10;

	if(parm=="Regional_Internal")
		m_Parameters.Regional_Internal = atoi(value.c_str());

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atoi(value.c_str());
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject image=pData->m_Image;
		//input: Txx, Tyy, TR, int Thred_qian_a=1000, Thred_qian_b=2000;
		//output: 	Hlong Txx_Error_qian, Tyy_Error_qian;
		Hlong Txx_Error_qian, Tyy_Error_qian; //out
		double Txx,Tyy,TR;
		Txx = pData->m_center_x;
		Tyy = pData->m_center_y;
		TR = pData->r_real;
	//	Hlong Thred_qian_a = m_Parameters.Thred_qian_a;
		Hlong Thred_qian_b= m_Parameters.Thred_qian_b;

		// 将检测区域定义成Object 合并到ProcessImage
		//Regional_Internal
		Hlong Regional_Internal = TR+m_Parameters.Regional_Internal; //检测区域的圆内径
		Hlong Regional_Out = TR+m_Parameters.Regional_Out; //检测区域的圆外径



	// 	double S_circle=(Regional_Out*Regional_Out-Regional_Internal*Regional_Internal)*3.1416;
	// 	Thred_qian_b=Thred_qian_b*S_circle/30000;
		


		if (ShowObject&&pData->m_isDebug)
		{
			if(abs(Regional_Out-Regional_Internal)<=2||Regional_Out<5||Regional_Internal<5)
			{
				pData->m_isFail = true;
				testItem->m_bFailSubTest = true;
				set_color(pData->m_ShowHWindow,"red");
				HTuple msg  = HTuple("Error=") +"Error QianHuan Define test regist error";
		
				set_tposition( pData->m_ShowHWindow, 50, 50);				
				write_string(pData->m_ShowHWindow,msg);
				return;
			}

			set_color(pData->m_ShowHWindow,"green");
			Hobject regional1,regional2;
			gen_circle(&regional1,Tyy,Txx,Regional_Internal);
			disp_obj(regional1,pData->m_ShowHWindow);
			set_color(pData->m_ShowHWindow,"blue");
			gen_circle(&regional2,Tyy,Txx,Regional_Out);
			disp_obj(regional2,pData->m_ShowHWindow);

		}

		Hlong Txx_Error_qian_b, Tyy_Error_qian_b;
		int i, j, k;
		int Thred_Error_qian=0;/////////////////////////////////////////////////////////////////////////////////
		Hobject PolarTransImage_qian_b, ImageEmphasize_qian_b;
		double tem_qian_b, tem_b[150];
		polar_trans_image_ext (image, &PolarTransImage_qian_b, Tyy-1, Txx-1, 0, 6.667, Regional_Out-1, Regional_Internal+1, 600, 30, "bilinear");
		emphasize(PolarTransImage_qian_b, &ImageEmphasize_qian_b, 5, 5, 3);
		for (i=0; i<3; i++)
		{
			tem_b[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<30; k++)
				{
					get_grayval(ImageEmphasize_qian_b, k, j, &tem_qian_b);
					tem_b[i]=tem_b[i]+tem_qian_b;	
				}
			}
		}

		for (i=3; i<145; i++)
		{
			tem_b[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<30; k++)
				{
					get_grayval(ImageEmphasize_qian_b, k, j, &tem_qian_b);
					tem_b[i]=tem_b[i]+tem_qian_b;	
				}	
			}
			if (abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i])>Thred_qian_b)
			{
				Thred_Error_qian=abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i]);
				Txx_Error_qian_b=Txx+(Regional_Internal+4)*cos(6.667*(j-2)/600);
				Tyy_Error_qian_b=Tyy-(Regional_Internal+4)*sin(6.667*(j-2)/600);


				if (pData->m_isDebug)
				{
					set_color(pData->m_ShowHWindow,"red");
					disp_circle(pData->m_ShowHWindow,Tyy_Error_qian_b,Txx_Error_qian_b,8);
				}

			}
		}

		Txx_Error_qian=Txx_Error_qian_b;
		Tyy_Error_qian=Tyy_Error_qian_b;

		if (Thred_Error_qian>Thred_qian_b)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;

			testItem->m_ErrorY = Tyy_Error_qian;
			testItem->m_ErrorX = Txx_Error_qian;
			testItem->m_ErrorR = 4;
	//		return;
		}
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}

	
// 	double tem_qian_a, tem_a[140];
// 	Hlong Txx_Error_qian_a, Tyy_Error_qian_a;
// 	Hobject Error_qian_a;
// 	Hobject PolarTransImage_qian_a, ImageEmphasize_qian_a;
// 	polar_trans_image_ext (image, &PolarTransImage_qian_a, Tyy-1, Txx-1, 0, 6.59, Regional_Out-8, Regional_Internal+1, 560, 6, "bilinear");
// 	emphasize(PolarTransImage_qian_a, &ImageEmphasize_qian_a, 5, 5, 3);
// 	for (i=0; i<3; i++)
// 	{
// 		tem_a[i]=0;
// 		for (j=4*i; j<4*i+4; j++)
// 		{
// 			for (k=0; k<6; k++)
// 			{
// 				get_grayval(ImageEmphasize_qian_a, k, j, &tem_qian_a);
// 				tem_a[i]=tem_a[i]+tem_qian_a;	
// 			}
// 		}
// 	}
// 
// 	for (i=3; i<137; i++)
// 	{
// 		tem_a[i]=0;
// 		for (j=4*i; j<4*i+4; j++)
// 		{
// 			for (k=0; k<6; k++)
// 			{
// 				get_grayval(ImageEmphasize_qian_a, k, j, &tem_qian_a);
// 				tem_a[i]=tem_a[i]+tem_qian_a;	
// 			}	
// 		}
// 		if (abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i])>Thred_qian_a)
// 		{
// 			Thred_Error_qian=abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i]);
// 			Txx_Error_qian_a=Txx+(TR-29)*cos(6.59*(j-2)/560);
// 			Tyy_Error_qian_a=Tyy-(TR-29)*sin(6.59*(j-2)/560);
// 		}
// 	}
// 
// 	Txx_Error_qian=Txx_Error_qian_a;
// 	Tyy_Error_qian=Tyy_Error_qian_a;
// 
// 
// 	if (Thred_Error_qian<=Thred_qian_a)
// 	{
// 		return;
// 	}

// 
// 	pData->m_isFail = true;
// 	testItem->m_bFailSubTest = true;
// 	testItem->m_ErrorMsg = "Error QianHuan Test";
// 	testItem->m_ErrorY = Tyy_Error_qian;
// 	testItem->m_ErrorX = Txx_Error_qian;
// 	testItem->m_ErrorR = 6;


}
