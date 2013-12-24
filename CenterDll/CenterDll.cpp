// CenterDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CenterDll.h"
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
	int j;


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
	BackGrayVal_left=(BackGrayVal_left+BackGrayVal_right)/2;
	BackGrayVal_right=BackGrayVal_left;
	BackGrayVal_up=(BackGrayVal_up+BackGrayVal_down)/2;
	BackGrayVal_down=BackGrayVal_up;



	double Txx_left[10], Txx_right[10], Tyy_down[10], Tyy_up[10];
	double Txxz[10], Tyyz[10];



	for (j=0; j<10; j++)
	{
		Txx_left[j]=Cxx/2-Cyy/2+3;
		Txx_right[j]=3*Cxx/2+Cyy/2-3;
		Tyy_down[j]=2*Cyy-3;
		Tyy_up[j]=3;

		get_grayval (image, Cyy-50+10*j, Txx_left[j], &tem1);
		while (tem1-BackGrayVal_left<Thred_center1 && Txx_left[j]<Cxx)
		{
			Txx_left[j]=Txx_left[j]+3;
			get_grayval (image, Cyy-50+10*j, Txx_left[j], &tem1);
		}
		get_grayval (image, Cyy-50+10*j, Txx_left[j]-1, &tem1);
		if (tem1-BackGrayVal_left>=Thred_center1)
		{Txx_left[j]=Txx_left[j]-1;
		get_grayval (image, Cyy-50+10*j, Txx_left[j]-1, &tem1);
		if (tem1-BackGrayVal_left>=Thred_center1)
		{Txx_left[j]=Txx_left[j]-1;
		}
		}

		Txx_left[j]=Txx_left[j]+1;


		get_grayval (image, Cyy-50+10*j, Txx_right[j], &tem2);
		while (tem2-BackGrayVal_right<Thred_center1 && Txx_right[j]>Cxx)
		{
			Txx_right[j]=Txx_right[j]-3;
			get_grayval (image, Cyy-50+10*j, Txx_right[j], &tem2);
		}
		get_grayval (image, Cyy-50+10*j, Txx_right[j]+1, &tem2);
		if (tem2-BackGrayVal_right>=Thred_center1)
		{Txx_right[j]=Txx_right[j]+1;	
		get_grayval (image, Cyy-50+10*j, Txx_right[j]+1, &tem2);
		if (tem2-BackGrayVal_right>=Thred_center1)
		{Txx_right[j]=Txx_right[j]+1;
		}
		}

		Txx_right[j]=Txx_right[j]+2;

		get_grayval (image, Tyy_down[j], Cxx-50+10*j, &tem3);
		while (tem3-BackGrayVal_down<Thred_center1 && Tyy_down[j]>Cyy)
		{
			Tyy_down[j]=Tyy_down[j]-3;
			get_grayval (image, Tyy_down[j], Cxx-50+10*j, &tem3);
		}
		get_grayval (image, Tyy_down[j]+1, Cxx-50+10*j, &tem3);
		if (tem3-BackGrayVal_down>=Thred_center1)
		{Tyy_down[j]=Tyy_down[j]+1;
		get_grayval (image, Tyy_down[j]+1, Cxx-50+10*j, &tem3);
		if (tem3-BackGrayVal_down>=Thred_center1)
		{Tyy_down[j]=Tyy_down[j]+1;
		}
		}

		Tyy_down[j]=Tyy_down[j]+2;


		get_grayval (image, Tyy_up[j], Cxx-50+10*j, &tem4);
		while (tem4-BackGrayVal_up<Thred_center1 && Tyy_up[j]<Cyy)
		{
			Tyy_up[j]=Tyy_up[j]+3;
			get_grayval (image, Tyy_up[j], Cxx-50+10*j, &tem4);
		}
		get_grayval (image, Tyy_up[j]-1, Cxx-50+10*j, &tem4);
		if (tem4-BackGrayVal_up>=Thred_center1)
		{Tyy_up[j]=Tyy_up[j]-1;
		get_grayval (image, Tyy_up[j]-1, Cxx-50+10*j, &tem4);
		if (tem4-BackGrayVal_up>=Thred_center1)
		{Tyy_up[j]=Tyy_up[j]-1;
		}
		}

		Tyy_up[j]=Tyy_up[j]+1;


		Txxz[j]=(Txx_left[j]+Txx_right[j])/2;
		Tyyz[j]=(Tyy_up[j]+Tyy_down[j])/2;
	}



	int nn=10;
	bool Flag[10]={1,1,1,1,1,1,1,1,1};
	int loop=50;
	while(loop>1)
	{
		loop--;
		nn=0;
		tem1=0;
		for (int j=0;j<10;j++)
		{
			if (Flag[j])
			{
				tem1=tem1+Txxz[j];
				nn=nn+1;
			}
		}

		tem1=tem1/nn;

		tem3=0;


		for (int j=0;j<10;j++)
		{
			if (Flag[j])
			{
				tem3=tem3+(Txxz[j]-tem1)*(Txxz[j]-tem1);
			}
		}

		tem3=sqrt(tem3/nn);


		if (tem3<2)
		{
			break;
		}


		for (int j=0;j<10;j++)
		{
			if (Flag[j])
			{
				if (abs(Txxz[j]-tem1)>tem3)
				{
					Flag[j]=0;
				}
			}
		}
	}


	nn=0;
	tem1=0;
	for (int j=0;j<10;j++)
	{
		if (Flag[j])
		{
			tem1=tem1+Txxz[j];
			nn=nn+1;
		}
	}
	tem1=tem1/nn;
	int mm;
	Txx=tem1;
	for (int j=0;j<10;j++)
	{
		if (Flag[j])
		{
			mm=j;
			break;
		}
	}

	for (int j=0;j<10;j++)
	{
		Flag[j]=1;
	}


	loop=50;
	while(loop>1)
	{
		loop--;
		nn=0;

		tem2=0;
		for (j=0;j<10;j++)
		{
			if (Flag[j])
			{
				tem2=tem2+Tyyz[j];		
				nn=nn+1;
			}
		}
		tem2=tem2/nn;
		tem4=0;
		for (j=0;j<10;j++)
		{
			if (Flag[j])
			{

				tem4=tem4+(Tyyz[j]-tem2)*(Tyyz[j]-tem2);
			}
		}


		tem4=sqrt(tem4/nn);
		if (tem4<2)
		{
			break;
		}


		for (j=0;j<10;j++)
		{
			if (Flag[j])
			{
				if (abs(Tyyz[j]-tem2)>tem4)
				{
					Flag[j]=0;
				}
			}
		}
	}



	nn=0;

	tem2=0;

	for (j=0;j<10;j++)
	{
		if (Flag[j])
		{

			tem2=tem2+Tyyz[j];		
			nn=nn+1;
		}
	}


	tem2=tem2/nn;



	Tyy=tem2;


	// 	Hobject cCircle;
	// 	set_color(FGHandle,"red");
	// 	gen_circle(&cCircle, Tyy, Txx, 1);
	// 	disp_obj(cCircle, FGHandle);



	for (j=0;j<10;j++)
	{
		if (Flag[j])
		{
			nn=j;

			break;
		}
	}


	TR=sqrt((double)((Txx-(Cxx-50+10*nn))*(Txx-(Cxx-50+10*nn))+(Tyy-Tyy_up[nn])*(Tyy-Tyy_up[nn])));
	Hlong TR_test=sqrt((double)((Txx-Txx_left[mm])*(Txx-Txx_left[mm])+(Tyy-(Cyy-50+10*mm))*(Tyy-(Cyy-50+10*mm))));


	if (abs(TR-TR_test)<4)
	{
		if ((m_Parameters.XMin<Txx)&&(Txx<m_Parameters.XMax)&&(m_Parameters.YMin<Tyy)&&(Tyy<m_Parameters.YMax)&&(TR<m_Parameters.RMax)&&(TR>m_Parameters.RMin))
		{
			pData->m_center_x=Txx;
			pData->m_center_y=Tyy;
			pData->r_real=TR;
			set_color(pData->m_ShowHWindow,"red");
			Hobject circle;
			gen_circle(&circle,pData->m_center_y,pData->m_center_x,pData->r_real);
			disp_obj(circle,pData->m_ShowHWindow);

			//disp_circle(pData->m_ShowHWindow,pData->m_center_y,pData->m_center_x,pData->r_real);
			return;
		}
		else
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			pData->m_center_x=350;
			pData->m_center_y=250;
			pData->r_real=100;
			testItem->m_ErrorY = Tyy;
			testItem->m_ErrorX = Txx;
			testItem->m_ErrorR = TR;
		}

		
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
	Hlong Xlu=TemX+1, Ylu=TemY+1;


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
	Hlong Xrd=TemX+2, Yrd=TemY+2;



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
	TR_test=sqrt((double)((Txx-Xrd)*(Txx-Xrd)+(Tyy-Yrd)*(Tyy-Yrd)));


// 	if (abs(TR-TR_test)<3)
// 	{
// 		pData->m_center_x=Txx;
// 		pData->m_center_y=Tyy;
// 		pData->r_real=TR;
// 		pData->m_isFail = false;
// 		testItem->m_bFailSubTest = false;
// 		return;	
// 	}


//FOR DEBUG //  [2/29/2012 sam]
	
	
	if ((m_Parameters.XMin<Txx)&&(Txx<m_Parameters.XMax)&&(m_Parameters.YMin<Tyy)&&(Tyy<m_Parameters.YMax)&&(TR<m_Parameters.RMax)&&(TR>m_Parameters.RMin))
	{
		pData->m_center_x=Txx;
		pData->m_center_y=Tyy;
		pData->r_real=TR;
	}
	else
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		pData->m_center_x=350;
		pData->m_center_y=250;
		pData->r_real=100;
	}

	set_color(pData->m_ShowHWindow,"red");
	Hobject circle;
	gen_circle(&circle,pData->m_center_y,pData->m_center_x,pData->r_real);
	disp_obj(circle,pData->m_ShowHWindow);
	//disp_circle(pData->m_ShowHWindow,pData->m_center_y,pData->m_center_x,pData->r_real);
}
