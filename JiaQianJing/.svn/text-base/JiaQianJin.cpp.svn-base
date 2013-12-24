// JiaQianJing.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"

#include "JiaQianJin.h"
#include "../Inc/MData.h"





#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

CDoProcess::CDoProcess()
{
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

	if(parm=="Thred_jin_a")
		m_Parameters.Thred_jin_a = atoi(value.c_str());
	if(parm=="Thred_jin_b")
		m_Parameters.Thred_jin_b = atoi(value.c_str());
	if(parm=="Thred_jin_c")
		m_Parameters.Thred_jin_c = atoi(value.c_str());

	if(parm=="Regional_Internal")
		m_Parameters.Regional_Internal = atoi(value.c_str());

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atoi(value.c_str());
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{
	Hlong Tyy = pData->m_center_y;
	Hlong Txx = pData->m_center_x;
	Hlong TR = pData->r_real;
	Hobject image = pData->m_Image;
	int Thred_jin_a = m_Parameters.Thred_jin_a;
	int Thred_jin_b = m_Parameters.Thred_jin_b;
	int Thred_jin_c = m_Parameters.Thred_jin_c;

	//input:  Txx, Tyy, TR;  int Thred_jin_a=1200, Thred_jin_b=800, Thred_jin_c=800;
	//output: Hlong Error_x, Error_y;

	// 将检测区域定义成Object 合并到ProcessImage
	//Regional_Internal
	Hlong Regional_Internal = TR+m_Parameters.Regional_Internal; //检测区域的圆内径
	Hlong Regional_Out = TR+m_Parameters.Regional_Out; //检测区域的圆外径

	if (ShowObject&&pData->m_isDebug)
	{
		if(abs(Regional_Out-Regional_Internal)<=2)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"red");
			HTuple msg  = HTuple("Error=") +"Error QianHuan Define test regist error";

			set_tposition( pData->m_ShowHWindow, 50, 50);				
			write_string(pData->m_ShowHWindow,msg);

			testItem->m_ErrorY = 50;
			testItem->m_ErrorX = 50;
			testItem->m_ErrorR = 6;
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
	
	int Thred_Error_jin=0;
	int i, j, k;
	Hobject PolarTransImage_jin_a, ImageEmphasize_jin_a;
	HTuple T1, T2;
	double tem_jin_a, tem_a[66];
	Hlong Txx_Error_jin_a, Tyy_Error_jin_a;
	Hobject Error_jin_a;

	polar_trans_image_ext (image, &PolarTransImage_jin_a, Tyy-1, Txx-1, 0, 6.6, Regional_Out, Regional_Internal, 264, 9, "bilinear");
	emphasize(PolarTransImage_jin_a, &ImageEmphasize_jin_a, 5, 5, 3);

	for (i=0; i<3; i++)
	{
		tem_a[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<9; k++)
			{
				get_grayval(ImageEmphasize_jin_a, k, j, &tem_jin_a);
				tem_a[i]=tem_a[i]+tem_jin_a;	
			}
		}
	}

	for (i=3; i<66; i++)
	{
		tem_a[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<9; k++)
			{
				get_grayval(ImageEmphasize_jin_a, k, j, &tem_jin_a);
				tem_a[i]=tem_a[i]+tem_jin_a;	
			}	
		}
		if (abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i])>Thred_jin_a)
		{
			Thred_Error_jin=abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i]);
			Txx_Error_jin_a=Txx+(TR-37)*cos(6.6*(j-2)/264);
			Tyy_Error_jin_a=Tyy-(TR-37)*sin(6.6*(j-2)/264);
		}
	}

	if (Thred_Error_jin>Thred_jin_a)
	{
// 		Error_x=Txx_Error_jin_a;
// 		Error_y=Tyy_Error_jin_a;
		testItem->m_bFailSubTest = true;
		pData->m_isFail = true;
		testItem->m_ErrorX = Txx_Error_jin_a;
		testItem->m_ErrorY = Tyy_Error_jin_a;
		return;
	}

	Hobject PolarTransImage_jin_b, ImageEmphasize_jin_b;
	double tem_jin_b, tem_b[62];
	Hlong Txx_Error_jin_b, Tyy_Error_jin_b;
	Hobject Error_jin_b;

	polar_trans_image_ext (image, &PolarTransImage_jin_b, Tyy-1, Txx-1, 0, 6.6, 0.7*Regional_Out+0.3*Regional_Internal-1, 0.38*Regional_Out+0.62*Regional_Internal+1, 248, 10, "bilinear");
	emphasize(PolarTransImage_jin_b, &ImageEmphasize_jin_b, 5, 5, 3);

	for (i=0; i<3; i++)
	{
		tem_b[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<10; k++)
			{
				get_grayval(ImageEmphasize_jin_b, k, j, &tem_jin_b);
				tem_b[i]=tem_b[i]+tem_jin_b;	
			}
		}
	}

	for (i=3; i<62; i++)
	{
		tem_b[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<10; k++)
			{
				get_grayval(ImageEmphasize_jin_b, k, j, &tem_jin_b);
				tem_b[i]=tem_b[i]+tem_jin_b;	
			}	
		}
		if (abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i])>Thred_jin_b)
		{
			Thred_Error_jin=abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i]);
			Txx_Error_jin_b=Txx+(TR-46)*cos(6.6*(j-2)/248);
			Tyy_Error_jin_b=Tyy-(TR-46)*sin(6.6*(j-2)/248);
		}
	}

	if (Thred_Error_jin>Thred_jin_b)
	{
// 
// 		Error_x=Txx_Error_jin_b;
// 		Error_y=Tyy_Error_jin_b;
		testItem->m_bFailSubTest = true;
		pData->m_isFail = true;
		testItem->m_ErrorX = Txx_Error_jin_b;
		testItem->m_ErrorY = Tyy_Error_jin_b;
		return;
	}


	Hobject PolarTransImage_jin_c, ImageEmphasize_jin_c;
	double tem_jin_c, tem_c[60];
	Hlong Txx_Error_jin_c, Tyy_Error_jin_c;
	Hobject Error_jin_c;

	polar_trans_image_ext (image, &PolarTransImage_jin_c, Tyy-1, Txx-1, 0, 6.7, 0.38*Regional_Out+0.62*Regional_Internal-1, 0.19*Regional_Out+0.81*Regional_Internal+1, 243, 7, "bilinear");
	emphasize(PolarTransImage_jin_c, &ImageEmphasize_jin_c, 5, 5, 3);

	for (i=0; i<3; i++)
	{
		tem_c[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<7; k++)
			{
				get_grayval(ImageEmphasize_jin_c, k, j, &tem_jin_c);
				tem_c[i]=tem_c[i]+tem_jin_c;	
			}
		}
	}

	for (i=3; i<60; i++)
	{
		tem_c[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<7; k++)
			{
				get_grayval(ImageEmphasize_jin_c, k, j, &tem_jin_c);
				tem_c[i]=tem_c[i]+tem_jin_c;	
			}	
		}
		if (abs(tem_c[i-1]+tem_c[i-2]+tem_c[i-3]-3*tem_c[i])>Thred_jin_c)
		{
			Thred_Error_jin=abs(tem_c[i-1]+tem_c[i-2]+tem_c[i-3]-3*tem_c[i]);
			Txx_Error_jin_c=Txx+(TR-55)*cos(6.7*(j-2)/243);
			Tyy_Error_jin_c=Tyy-(TR-55)*sin(6.7*(j-2)/243);
		}
	}



	if (Thred_Error_jin<=Thred_jin_c)
	{
		return;
	}

// 	Error_x=Txx_Error_jin_c;
// 	Error_y=Tyy_Error_jin_c;

	testItem->m_bFailSubTest = true;
	pData->m_isFail = true;
	testItem->m_ErrorX = Txx_Error_jin_c;
	testItem->m_ErrorY = Tyy_Error_jin_c;
	
}