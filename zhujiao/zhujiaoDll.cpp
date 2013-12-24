// zhujiao.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include "zhujiaoDll.h"
#include "..\Inc\MData.h"




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

	if(parm=="Thred_jiao")
		m_Parameters.Thred_jiao = atoi(value.c_str());
	if(parm=="Thred_jiao_outer")
		m_Parameters.Thred_jiao_outer = atoi(value.c_str());
	if(parm=="Thred_jiao_inter")
		m_Parameters.Thred_jiao_inter = atoi(value.c_str());
	if(parm=="Thred_no_jiao")
		m_Parameters.Thred_no_jiao= atoi(value.c_str());

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


	//input: int Thred_jiao=350, Thred_jiao_inter=500, Thred_jiao_outer=800; Txx, Tyy, TR;
	//output: 	Hlong TxxError_jiao, TyyError_jiao; bool Jiaogood;

	double TxxError_jiao, TyyError_jiao; //out

	double Txx,Tyy,TR;
	Txx = pData->m_center_x;
	Tyy = pData->m_center_y;
	TR = pData->r_real;


	// 将检测区域定义成Object 合并到ProcessImage
	//Regional_Internal

	double Regional_Internal = TR+m_Parameters.Regional_Internal; //检测区域的圆内径
	double Regional_Out = TR+m_Parameters.Regional_Out; //检测区域的圆外径

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

			testItem->m_ErrorY = 1;
			testItem->m_ErrorX = 1;
			testItem->m_ErrorR = 1;
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


	int Thred_error_jiao=0;
	Hobject PolarTransImage_jiao, ImageEmphasize_jiao, ImageSub_jiao, ImageInvert_jiao;
	double tem_jiao, teml[160], tem_jiao_noglue;
	tem_jiao_noglue=0;
	int i, j, k;
	polar_trans_image_ext (image, &PolarTransImage_jiao, Tyy, Txx, 0, 6.74,Regional_Out-1,  Regional_Internal+1, 640, 12, "bilinear");
	emphasize(PolarTransImage_jiao, &ImageEmphasize_jiao, 5, 5, 3);
	invert_image(PolarTransImage_jiao, &ImageInvert_jiao);
	sub_image(ImageInvert_jiao, ImageEmphasize_jiao, &ImageSub_jiao, 1, 1);
	for (i=0; i<3; i++)
	{
		teml[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=4; k<8; k++)
			{
				get_grayval(ImageSub_jiao, k, j, &tem_jiao);
				teml[i]=teml[i]+tem_jiao;	
			}
		}
	}

	Thred_error_jiao = m_Parameters.Thred_jiao;
	for (i=3; i<160; i++)
	{
		teml[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=4; k<8; k++)
			{
				get_grayval(ImageSub_jiao, k, j, &tem_jiao);
				teml[i]=teml[i]+tem_jiao;	
			}	
		}
		if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_error_jiao)
		{
			Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
			TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
			TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
		}
	}

	if (Thred_error_jiao>m_Parameters.Thred_jiao)
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		testItem->m_ErrorY = TyyError_jiao;
		testItem->m_ErrorX = TxxError_jiao;
		testItem->m_ErrorR = 10;


		//if (ShowObject&&pData->m_isDebug)
		{
			Hobject circle;
			gen_circle(&circle,testItem->m_ErrorY,testItem->m_ErrorX,testItem->m_ErrorR);
			disp_obj(circle,pData->m_ShowHWindow);
		}
	}


	int tem=0;
	for (i=0; i<640; i++)
	{
		for (j=0; j<12; j++)
		{
			get_grayval(PolarTransImage_jiao, j, i, &tem_jiao);
			tem = tem+tem_jiao;
		}
	}
	tem_jiao_noglue=tem/7680;
	if (tem_jiao_noglue>m_Parameters.Thred_no_jiao)
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;

		char msg[MAX_PATH];
		sprintf_s(msg,sizeof(msg),"Error ZhuJiao Test No glue, current_mean_gray=%f,  set_mean_gray=%d",tem_jiao_noglue,m_Parameters.Thred_no_jiao);

		//testItem->m_ErrorMsg = msg;
		testItem->m_ErrorY = 1;
		testItem->m_ErrorX = 1;
		if (ShowObject&&pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"red");

			char msg[MAX_PATH];
			sprintf_s(msg,sizeof(msg),"Error ZhuJiao Test No glue, current_mean_gray=%f,  set_mean_gray=%d",tem_jiao_noglue,m_Parameters.Thred_no_jiao);
			set_tposition( pData->m_ShowHWindow, 35, 200);				
			write_string(pData->m_ShowHWindow,msg);
		}
		//return;
	}

		Thred_error_jiao = m_Parameters.Thred_jiao_inter;
		for (i=0; i<3; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=8; k<12; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}
			}
		}

		for (i=3; i<155; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=8; k<12; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}	
			}
			if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_error_jiao)
			{
				Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
				TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
				TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
			}
		}

		if (Thred_error_jiao>m_Parameters.Thred_jiao_inter)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			testItem->m_ErrorY = TyyError_jiao;
			testItem->m_ErrorX = TxxError_jiao;
			testItem->m_ErrorR = 10;

			if (ShowObject&&pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");

				char msg[MAX_PATH];
				sprintf_s(msg,sizeof(msg),"Error ZhuJiao (inter)Test, CurrentThred=%d,  SettingThred=%d",Thred_error_jiao,m_Parameters.Thred_jiao_inter);

				set_tposition( pData->m_ShowHWindow, 35, 200);				
				write_string(pData->m_ShowHWindow,msg);
			}
		}


	Thred_error_jiao = m_Parameters.Thred_jiao_outer;
	{
		for (i=0; i<3; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<4; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}
			}
		}

		for (i=3; i<155; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<4; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}	
			}
			if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_error_jiao)
			{
				Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
				TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
				TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
			}
		}	
		if (Thred_error_jiao>m_Parameters.Thred_jiao_outer)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;

			testItem->m_ErrorY = TyyError_jiao;
			testItem->m_ErrorX = TxxError_jiao;
			testItem->m_ErrorR = 10;

			if (ShowObject&&pData->m_isDebug)
			{
				char msg[MAX_PATH];
				sprintf_s(msg,sizeof(msg),"Error ZhuJiao (outer)Test, CurrentThred=%d,  SettingThred=%d",Thred_error_jiao,m_Parameters.Thred_jiao_outer);

				set_tposition( pData->m_ShowHWindow, 35, 200);				
				write_string(pData->m_ShowHWindow,msg);

				Hobject circle;
				gen_circle(&circle,testItem->m_ErrorY,testItem->m_ErrorX,testItem->m_ErrorR);
				disp_obj(circle,pData->m_ShowHWindow);
			}
		}

	}


	
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}


}