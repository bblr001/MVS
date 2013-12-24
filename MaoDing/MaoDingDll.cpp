// zhujiao.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include "MaodingDll.h"
#include "..\Inc\MData.h"




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
	if(parm=="Thred_qian_a")
		m_Parameters.Thred_qian_a = atoi(value.c_str());
	if(parm=="Thred_qian_b")
		m_Parameters.Thred_qian_b= atoi(value.c_str());
	if(parm=="Thred_qian_b")
		m_Parameters.Thred_Error_qian= atoi(value.c_str());

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atoi(value.c_str());
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{
		Hobject image=pData->m_Image;

		Hlong Txx,Tyy,TR;
		Txx = pData->m_center_x;
		Tyy = pData->m_center_y;
		TR = pData->r_real;

		int Thred_Center = m_Parameters.Thred_Center;

		// 将检测区域定义成Object 合并到ProcessImage
		Hlong Regional_Out = TR+m_Parameters.Regional_Out; //检测区域的圆外径

		Hobject Circle_Range;
		gen_circle(&Circle_Range, Tyy, Txx, 16);

		int Thred_Error_qian=m_Parameters.Thred_Error_qian, Thred_qian_a=m_Parameters.Thred_qian_a, Thred_qian_b=m_Parameters.Thred_qian_b;

		///////////////////////////////////////////////////////////////////////
		///////////////////////////////////run////in a////out b////
		int i, j, k;
		Hlong NumC;

		Hobject Range_Center, Region_CenterOut, Region_CenterIn, Region_Closed, Region_Opened, CircleDing;
		Hobject PolarTransImage_qian_b, ImageEmphasize_qian_b;

		double tem_qian_b, tem_b[150], tem, ave=0;
		Hlong Txx_Error_qian_b, Tyy_Error_qian_b;
		double Ty, Tx, Tr;
		Hobject Error_qian_b;

		reduce_domain(image, Circle_Range, &Range_Center);

		for (i=0; i<8; i++)
		{
			get_grayval(image, Tyy+3*sin(i*3.1416/4), Txx+3*cos(i*3.1416/4), &tem);
			ave=ave+tem;
			get_grayval(image, Tyy+6*sin(i*3.1416/4), Txx+6*cos(i*3.1416/4), &tem);
			ave=ave+tem;
		}

		ave=ave/16;

		get_grayval(image, Tyy, Txx+i, &tem);
		while (abs(ave-tem)<Thred_Center)
		{
			i++;
			get_grayval(image, Tyy, Txx+i, &tem);
		}
		Tr=i;
		Tx=Txx+i-1;
		i=7;
		get_grayval(image, Tyy, Txx-i, &tem);
		while (abs(ave-tem)<Thred_Center)
		{
			i++;
			get_grayval(image, Tyy, Txx-i, &tem);
		}
		Tx=(Txx-i+1+Tx)/2;
		Tr=Tr+i;
		i=7;
		get_grayval(image, Tyy+i, Txx, &tem);
		while (abs(ave-tem)<Thred_Center)
		{
			i++;
			get_grayval(image, Tyy+i, Txx, &tem);
		}
		Ty=Tyy+i-1;
		Tr=Tr+i;
		i=7;
		get_grayval(image, Tyy-i, Txx, &tem);
		while (abs(ave-tem)<Thred_Center)
		{
			i++;
			get_grayval(image, Tyy-i, Txx, &tem);
		}
		Ty=(Tyy-i+1+Ty)/2;
		Tr=(Tr+i)/4+1;


		bin_threshold(Range_Center, &Region_CenterOut);

		connection(Region_CenterOut, &Region_Opened);

		polar_trans_image_ext (image, &PolarTransImage_qian_b, Tyy, Txx, 0, 6.667, TR-21, TR-25, 600, 5, "bilinear");

		emphasize(PolarTransImage_qian_b, &ImageEmphasize_qian_b, 5, 5, 3);

		for (i=0; i<3; i++)
		{
			tem_b[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<5; k++)
				{
					get_grayval(ImageEmphasize_qian_b, k, j, &tem_qian_b);
					tem_b[i]=tem_b[i]+tem_qian_b;	
				}
			}
		}

		// unroll this loop for improving performance
		for (i=3; i<145; i++)
		{
			tem_b[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				get_grayval(ImageEmphasize_qian_b, 0, j, &tem_qian_b);
				tem_b[i]=tem_b[i]+tem_qian_b;

				get_grayval(ImageEmphasize_qian_b, 1, j, &tem_qian_b);
				tem_b[i]=tem_b[i]+tem_qian_b;

				get_grayval(ImageEmphasize_qian_b, 2, j, &tem_qian_b);
				tem_b[i]=tem_b[i]+tem_qian_b;

				get_grayval(ImageEmphasize_qian_b, 3, j, &tem_qian_b);
				tem_b[i]=tem_b[i]+tem_qian_b;

				get_grayval(ImageEmphasize_qian_b, 4, j, &tem_qian_b);
				tem_b[i]=tem_b[i]+tem_qian_b;
			}
			if (abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i])>Thred_qian_b)
			{
				Thred_Error_qian=abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i]);
				Txx_Error_qian_b=Txx+(TR-22)*cos(6.667*(j-2)/600);
				Tyy_Error_qian_b=Tyy-(TR-22)*sin(6.667*(j-2)/600);
				gen_circle(&Error_qian_b, Tyy_Error_qian_b, Txx_Error_qian_b, 4);
			}
		}

		select_shape(Region_Opened, &Region_CenterOut, "outer_radius", "and", 12, 13);
		//	disp_obj(ImageEmphasize_qian_b, FGHandle);

		closing_circle(Region_CenterOut, &Region_CenterIn, 2);

		count_obj(Region_CenterIn, &NumC);

		if (NumC-1)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef ENGLISH_VERSION
						write_string(pData->m_ShowHWindow,"Error MaoDing Test Error Center");
			#else
						write_string(pData->m_ShowHWindow,"铆钉中心错误");
			#endif

			testItem->m_ErrorY = Ty;
			testItem->m_ErrorX = Tx;
			testItem->m_ErrorR = 10;
			return;
		}
		//	smallest_circle (Region_CenterIn, &Ty, &Tx, &Tr);
		if (abs(Ty-Tyy)>2)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "Error MaoDing Test Ty-Tyy >2";
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"Error MaoDing Test Ty-Tyy >2");
#else
			write_string(pData->m_ShowHWindow,"铆钉错误 Ty-Tyy >2");
#endif
			testItem->m_ErrorY = Ty;
			testItem->m_ErrorX = Tx;
			testItem->m_ErrorR = 10;
			return;
		}
		if (abs(Tx-Txx)>2)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			//testItem->m_ErrorMsg = "Error MaoDing Test Tx-Txx >2";
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"Error MaoDing Test Error Center");
#else
			write_string(pData->m_ShowHWindow,"铆钉错误， Tx-Txx >2");
#endif
			testItem->m_ErrorY = Ty;
			testItem->m_ErrorX = Tx;
			testItem->m_ErrorR = 10;
			return;
		}

		if (abs(Tr-12.5)>1)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"Error MaoDing Test Tr-12.5 >1");
#else
			write_string(pData->m_ShowHWindow,"铆钉错误  Tr-12.5 >1");
#endif

			testItem->m_ErrorY = Ty;
			testItem->m_ErrorX = Tx;
			testItem->m_ErrorR = 10;
			return;
		}
		gen_circle(&CircleDing, Ty, Tx, Tr);
	
		pData->m_center_y=Ty+1;
		pData->m_center_x=Tx+1;
		gen_circle(&CircleDing, Tyy, Txx, TR);

		if (Thred_Error_qian>Thred_qian_b)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"MaoDing Test Thred_Error_qian > Thred_qian_b");
#else
			write_string(pData->m_ShowHWindow,"铆钉错误，hred_Error_qian > Thred_qian_b");
#endif

			testItem->m_ErrorY = Ty;
			testItem->m_ErrorX = Tx;
			testItem->m_ErrorR = 10;
			return;
		}

		////////////////////////////////////////////////////////////
		///////////////////////////a

		double tem_qian_a, tem_a[140];
		Hlong Txx_Error_qian_a, Tyy_Error_qian_a;
		Hobject Error_qian_a;

		Hobject PolarTransImage_qian_a, ImageEmphasize_qian_a;

		polar_trans_image_ext (image, &PolarTransImage_qian_a, Tyy-1, Txx-1, 0, 6.59, TR-31, TR-26, 560, 6, "bilinear");

		emphasize(PolarTransImage_qian_a, &ImageEmphasize_qian_a, 5, 5, 3);

		for (i=0; i<3; i++)
		{
			tem_a[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<6; k++)
				{
					get_grayval(ImageEmphasize_qian_a, k, j, &tem_qian_a);
					tem_a[i]=tem_a[i]+tem_qian_a;	
				}
			}
		}

		for (i=3; i<137; i++)
		{
			tem_a[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				get_grayval(ImageEmphasize_qian_a, 0, j, &tem_qian_a);
				tem_a[i]=tem_a[i]+tem_qian_a;

				get_grayval(ImageEmphasize_qian_a, 1, j, &tem_qian_a);
				tem_a[i]=tem_a[i]+tem_qian_a;

				get_grayval(ImageEmphasize_qian_a, 2, j, &tem_qian_a);
				tem_a[i]=tem_a[i]+tem_qian_a;

				get_grayval(ImageEmphasize_qian_a, 3, j, &tem_qian_a);
				tem_a[i]=tem_a[i]+tem_qian_a;

				get_grayval(ImageEmphasize_qian_a, 4, j, &tem_qian_a);
				tem_a[i]=tem_a[i]+tem_qian_a;

				get_grayval(ImageEmphasize_qian_a, 5, j, &tem_qian_a);
				tem_a[i]=tem_a[i]+tem_qian_a;
			}
			if (abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i])>Thred_qian_a)
			{
				Thred_Error_qian=abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i]);
				Txx_Error_qian_a=Txx+(TR-29)*cos(6.59*(j-2)/560);
				Tyy_Error_qian_a=Tyy-(TR-29)*sin(6.59*(j-2)/560);
				gen_circle(&Error_qian_a, Tyy_Error_qian_a, Txx_Error_qian_a, 4);
			}
		}

		for (i=0; i<36; i++)
		{
			Txx_Error_qian_a=Txx+(TR-29)*cos(6.59*(i-2)/560);
			Tyy_Error_qian_a=Tyy-(TR-29)*sin(6.59*(i-2)/560);
			disp_line(pData->m_ShowHWindow, Ty+Tr*sin(i*3.1416/18), Tx+Tr*cos(i*3.1416/18), Tyy+TR*sin(i*3.1416/18), Txx+TR*cos(i*3.1416/18));
		}
	}

	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		if (pData->m_isDebug)
		{
				set_color(pData->m_ShowHWindow,"green");
				set_tposition( pData->m_ShowHWindow,25, 145);
		#ifdef ENGLISH_VERSION
				write_string(pData->m_ShowHWindow,"Error MaoDing Test Error ");
		#else
				write_string(pData->m_ShowHWindow,"铆钉程式参数错误");
		#endif
		}
	}

}