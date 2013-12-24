//2012-02-29 更新解图片整体向右下角偏的问题. 主要是在新的管路上出现左边细右边粗的现象

// CenterDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "../Inc/MData.h"
#include "CenterDll.h"




#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

CDoProcess::CDoProcess()
{
	m_ProcessName ="Find Circal Center";
}

void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="Thred_Center1")
		m_Parameters.Thred_Center1= atoi(value.c_str());
	if(parm=="Thred_Center2")
		m_Parameters.Thred_Center2= atoi(value.c_str());

	if(parm=="XMax")
		m_Parameters.XMax = atoi(value.c_str());
	if(parm=="XMin")
		m_Parameters.XMin = atoi(value.c_str());
	if(parm=="YMax")
		m_Parameters.YMax = atoi(value.c_str());
	if(parm=="YMin")
		m_Parameters.YMin = atoi(value.c_str());
	if(parm=="RMax")
		m_Parameters.RMax = atoi(value.c_str());
	if(parm=="RMin")
		m_Parameters.RMin = atoi(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	testItem->SubTestName = m_ProcessName;
	testItem->m_ErrorMsg = "No Error";
	Hlong Thred_center1=m_Parameters.Thred_Center1;
	Hlong Thred_center2=m_Parameters.Thred_Center2;

	Hobject image=pData->m_Image;



//Start....
	Hlong Pointer, Width, Height;
	//for out...
	Hlong Txx, Tyy, TR;

	char lpcsType[MAX_STRING];
	get_image_pointer1(image, &Pointer, lpcsType, &Width, &Height);


	//初始化

// 	Hobject Circle1, Circle2;
// 	long Cx=(long) Width/2;
// 	long Cy=(long) Height/2;
// 
// 	gen_circle(&Circle1, Cy, Cx, Cy+60);
// 	gen_circle(&Circle2, Cy, Cx, 120);

	double BackGrayVal_up, BackGrayVal_down, BackGrayVal_left, BackGrayVal_right, tem1,tem2,tem3,tem4;

	Hlong Cxx=Width/2;
	Hlong Cyy=Height/2;
	int i, j;


	BackGrayVal_left=0;
	BackGrayVal_right=0;
	BackGrayVal_up=0;
	BackGrayVal_down=0;

	for (int i=0; i<5; i++)
	{
		get_grayval (image, Cyy+5*i-10, Cxx-Cyy, &tem1);
		get_grayval (image, Cyy+5*i-10, Cxx+Cyy, &tem2);
		get_grayval (image, 3, Cxx+5*i-10, &tem3);
		get_grayval (image, 2*Cyy-3, Cxx+5*i-10, &tem4);
		BackGrayVal_left=BackGrayVal_left+tem1;
		BackGrayVal_right=BackGrayVal_right+tem2;
		BackGrayVal_up=BackGrayVal_up+tem3;
		BackGrayVal_down=BackGrayVal_down+tem4;
		get_grayval (image, Cyy+5*i-10, Cxx-Cyy+3,  &tem1);
		get_grayval (image, Cyy+5*i-10, Cxx+Cyy-3,  &tem2);
		get_grayval (image, 6, Cxx+5*i-10,  &tem3);
		get_grayval (image, 2*Cyy-6, Cxx+5*i-10, &tem4);
		BackGrayVal_left=BackGrayVal_left+tem1;
		BackGrayVal_right=BackGrayVal_right+tem2;
		BackGrayVal_up=BackGrayVal_up+tem3;
		BackGrayVal_down=BackGrayVal_down+tem4;
		get_grayval (image, Cyy+5*i-10, Cxx-Cyy+6,  &tem1);
		get_grayval (image, Cyy+5*i-10, Cxx+Cyy-6,  &tem2);
		get_grayval (image, 9, Cxx+5*i-10,  &tem3);
		get_grayval (image, 2*Cyy-9, Cxx+5*i-10, &tem4);
		BackGrayVal_left=BackGrayVal_left+tem1;
		BackGrayVal_right=BackGrayVal_right+tem2;
		BackGrayVal_up=BackGrayVal_up+tem3;
		BackGrayVal_down=BackGrayVal_down+tem4;
	}

	BackGrayVal_left=BackGrayVal_left/15;
	BackGrayVal_right=BackGrayVal_right/15;
	BackGrayVal_up=BackGrayVal_up/15;
	BackGrayVal_down=BackGrayVal_down/15;



	Hlong Txx_left[5], Txx_right[5], Tyy_down[5], Tyy_up[5];
	Hlong Txxz[5], Tyyz[5];



	for (i=0; i<5; i++)
	{
		Txx_left[i]=Cxx-Cyy+3;
		Txx_right[i]=Cxx+Cyy-3;
		Tyy_down[i]=2*Cyy-3;
		Tyy_up[i]=3;

		get_grayval (image, Cyy-10+5*i, Txx_left[i], &tem1);
		while (tem1-BackGrayVal_left<Thred_center1 && Txx_left[i]<Cxx)
		{
			Txx_left[i]=Txx_left[i]+3;
			get_grayval (image, Cyy-10+5*i, Txx_left[i], &tem1);
		}
		get_grayval (image, Cyy-10+5*i, Txx_left[i]-1, &tem1);
		if (tem1-BackGrayVal_left>=Thred_center1)
		{Txx_left[i]=Txx_left[i]-1;
		get_grayval (image, Cyy-10+5*i, Txx_left[i]-1, &tem1);
		if (tem1-BackGrayVal_left>=Thred_center1)
		{Txx_left[i]=Txx_left[i]-1;
		}
		}

		Txx_left[i]=Txx_left[i];


		get_grayval (image, Cyy-10+5*i, Txx_right[i], &tem2);
		while (tem2-BackGrayVal_right<Thred_center1 && Txx_right[i]>Cxx)
		{
			Txx_right[i]=Txx_right[i]-3;
			get_grayval (image, Cyy-10+5*i, Txx_right[i], &tem2);
		}
		get_grayval (image, Cyy-10+5*i, Txx_right[i]+1, &tem2);
		if (tem2-BackGrayVal_right>=Thred_center1)
		{Txx_right[i]=Txx_right[i]+1;	
		get_grayval (image, Cyy-10+5*i, Txx_right[i]+1, &tem2);
		if (tem2-BackGrayVal_right>=Thred_center1)
		{Txx_right[i]=Txx_right[i]+1;
		}
		}

		Txx_right[i]=Txx_right[i]+2;

		get_grayval (image, Tyy_down[i], Cxx-10+5*i, &tem3);
		while (tem3-BackGrayVal_down<Thred_center1 && Tyy_down[i]>Cyy)
		{
			Tyy_down[i]=Tyy_down[i]-3;
			get_grayval (image, Tyy_down[i], Cxx-10+5*i, &tem3);
		}
		get_grayval (image, Tyy_down[i]+1, Cxx-10+5*i, &tem3);
		if (tem3-BackGrayVal_down>=Thred_center1)
		{Tyy_down[i]=Tyy_down[i]+1;
		get_grayval (image, Tyy_down[i]+1, Cxx-10+5*i, &tem3);
		if (tem3-BackGrayVal_down>=Thred_center1)
		{Tyy_down[i]=Tyy_down[i]+1;
		}
		}

		Tyy_down[i]=Tyy_down[i]+2;


		get_grayval (image, Tyy_up[i], Cxx-10+5*i, &tem4);
		while (tem4-BackGrayVal_up<Thred_center1 && Tyy_up[i]<Cyy)
		{
			Tyy_up[i]=Tyy_up[i]+3;
			get_grayval (image, Tyy_up[i], Cxx-10+5*i, &tem4);
		}
		get_grayval (image, Tyy_up[i]-1, Cxx-10+5*i, &tem4);
		if (tem4-BackGrayVal_up>=Thred_center1)
		{Tyy_up[i]=Tyy_up[i]-1;
		get_grayval (image, Tyy_up[i]-1, Cxx-10+5*i, &tem4);
		if (tem4-BackGrayVal_up>=Thred_center1)
		{Tyy_up[i]=Tyy_up[i]-1;
		}
		}

		Tyy_up[i]=Tyy_up[i];


		Txxz[i]=(Txx_left[i]+Txx_right[i])/2;
		Tyyz[i]=(Tyy_up[i]+Tyy_down[i])/2;


	}


	////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////计算//////////////////


	Txx=Txxz[3];
	Tyy=Tyyz[3];

	TR=sqrt((double)((Txx-Txx_left[3])*(Txx-Txx_left[3])+(Tyy-Cyy)*(Tyy-Cyy)));
	Hlong TR_test=sqrt((double)((Txx-Cxx)*(Txx-Cxx)+(Tyy-Tyy_up[3])*(Tyy-Tyy_up[3])));


	if (abs(TR-TR_test)<3)
	{
		pData->Center_x=Txx;
		pData->Center_y=Tyy;
		pData->r_real=TR;
		return;
	}





	double BackGrayVal_right_up, BackGrayVal_left_down, BackGrayVal_left_up, BackGrayVal_right_down;

	get_grayval (image, 3, Cxx-Cyy+3, &tem1);
	get_grayval (image, 3, Cxx+Cyy-3, &tem2);
	get_grayval (image, 2*Cyy-3, Cxx+Cyy-3, &tem3);
	get_grayval (image, 2*Cyy-3, Cxx-Cyy+3, &tem4);
	BackGrayVal_left_up=tem1;
	BackGrayVal_right_up=tem2;
	BackGrayVal_right_down=tem3;
	BackGrayVal_left_down=tem4;
	get_grayval (image, 6, Cxx-Cyy+6, &tem1);
	get_grayval (image, 6, Cxx+Cyy-6, &tem2);
	get_grayval (image, 2*Cyy-6, Cxx+Cyy-6, &tem3);
	get_grayval (image, 2*Cyy-6, Cxx-Cyy+6, &tem4);
	BackGrayVal_left_up=BackGrayVal_left_up+tem1;
	BackGrayVal_right_up=BackGrayVal_right_up+tem2;
	BackGrayVal_right_down=BackGrayVal_right_down+tem3;
	BackGrayVal_left_down=BackGrayVal_left_down+tem4;
	get_grayval (image, 9, Cxx-Cyy+9, &tem1);
	get_grayval (image, 9, Cxx+Cyy-9, &tem2);
	get_grayval (image, 2*Cyy-9, Cxx+Cyy-9, &tem3);
	get_grayval (image, 2*Cyy-9, Cxx-Cyy+9, &tem4);
	BackGrayVal_left_up=BackGrayVal_left_up+tem1;
	BackGrayVal_right_up=BackGrayVal_right_up+tem2;
	BackGrayVal_right_down=BackGrayVal_right_down+tem3;
	BackGrayVal_left_down=BackGrayVal_left_down+tem4;
	BackGrayVal_left_up=BackGrayVal_left_up/3;
	BackGrayVal_right_up=BackGrayVal_right_up/3;
	BackGrayVal_right_down=BackGrayVal_right_down/3;
	BackGrayVal_left_down=BackGrayVal_left_down/3;


	Hlong TemX=Cxx-Cyy+3, TemY=3;
	get_grayval (image, TemY, TemX, &tem1);
	while (tem1-BackGrayVal_left_up<Thred_center2 && TemX<Cxx-60 && TemY<Cyy-60)
	{
		TemX=TemX+3;
		TemY=TemY+3;
		get_grayval (image, TemY, TemX, &tem1);
	}
	get_grayval (image, TemY-1, TemX-1, &tem1);
	if (tem1-BackGrayVal_left_up>=Thred_center2)
	{
		TemY=TemY-1;
		TemX=TemX-1;
		get_grayval (image, TemY-1, TemX-1, &tem1);
		if (tem1-BackGrayVal_left_up>=Thred_center2)
		{
			TemY=TemY-1;
			TemX=TemX-1;
		}
	}
	Hlong Xlu=TemX, Ylu=TemY;


	TemX=Cxx+Cyy-3, TemY=3;
	get_grayval (image, TemY, TemX, &tem1);
	while (tem1-BackGrayVal_right_up<Thred_center2 && TemX>Cxx+60 && TemY<Cyy-60)
	{
		TemX=TemX-3;
		TemY=TemY+3;
		get_grayval (image, TemY, TemX, &tem1);
	}
	get_grayval (image, TemY-1, TemX+1, &tem1);
	if (tem1-BackGrayVal_right_up>=Thred_center2)
	{
		TemY=TemY-1;
		TemX=TemX+1;
		get_grayval (image, TemY-1, TemX+1, &tem1);
		if (tem1-BackGrayVal_right_up>=Thred_center2)
		{
			TemY=TemY-1;
			TemX=TemX+1;
		}
	}
	Hlong Xru=TemX, Yru=TemY;



	TemX=Cxx+Cyy-3, TemY=2*Cyy-3;	 
	get_grayval (image, TemY, TemX, &tem1);
	while (tem1-BackGrayVal_right_down<Thred_center2 && TemX>Cxx+60 && TemY>Cyy+60)
	{
		TemX=TemX-3;
		TemY=TemY-3;
		get_grayval (image, TemY, TemX, &tem1);
	}
	get_grayval (image, TemY+1, TemX+1, &tem1);
	if (tem1-BackGrayVal_right_down>=Thred_center2)
	{
		TemY=TemY+1;
		TemX=TemX+1;
		get_grayval (image, TemY+1, TemX+1, &tem1);
		if (tem1-BackGrayVal_right_down>=Thred_center2)
		{
			TemY=TemY+1;
			TemX=TemX+1;
		}
	}
	Hlong Xrd=TemX+1, Yrd=TemY+1;



	TemX=Cxx-Cyy+3, TemY=2*Cyy-3;	 
	get_grayval (image, TemY, TemX, &tem1);
	while (tem1-BackGrayVal_left_down<Thred_center2 && TemX<Cxx-60 && TemY>Cyy+60)
	{
		TemX=TemX+3;
		TemY=TemY-3;
		get_grayval (image, TemY, TemX, &tem1);
	}
	get_grayval (image, TemY+1, TemX-1, &tem1);
	if (tem1-BackGrayVal_left_down>=Thred_center2)
	{
		TemY=TemY+1;
		TemX=TemX-1;
		get_grayval (image, TemY+1, TemX-1, &tem1);
		if (tem1-BackGrayVal_left_down>=Thred_center2)
		{
			TemY=TemY+1;
			TemX=TemX-1;
		}
	}
	Hlong Xld=TemX, Yld=TemY;


	Txx=(Xlu+Xru+Xrd+Xld+Ylu-Yru+Yrd-Yld)/4;
	Tyy=(Xlu-Xru+Xrd-Xld+Yld+Ylu+Yrd+Yru)/4;

	TR=sqrt((double)((Txx-Xlu)*(Txx-Xlu)+(Tyy-Ylu)*(Tyy-Ylu)));


//FOR DEBUG //  [2/29/2012 sam]
	set_color(pData->m_ShowHWindow,"red");
	HTuple msg  = HTuple("FindCenter 2");
	set_tposition( pData->m_ShowHWindow, 5, 200);				
	write_string(pData->m_ShowHWindow,msg);
	

	if ((m_Parameters.XMin<Txx)&&(Txx<m_Parameters.XMax)&&(m_Parameters.YMin<Tyy)&&(Tyy<m_Parameters.YMax)&&(TR<m_Parameters.RMax)&&(TR>m_Parameters.RMin))
	{


		pData->Center_x=Txx;
		pData->Center_y=Tyy;
		pData->r_real=TR;
		pData->isFail = false;
		testItem->isFailSubTest = false;
	}
	else
	{
		pData->isFail = true;
		testItem->isFailSubTest = true;
		pData->Center_x=350;
		pData->Center_y=250;
		pData->r_real=100;
		testItem->m_ErrorMsg = "Error No Find Center";
		testItem->m_ErrorY = Tyy;
		testItem->m_ErrorX = Txx;
		testItem->m_ErrorR = TR;


	}


	



}
