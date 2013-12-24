// check_blister.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "check_blister.h"


#include "..\Inc\MData.h"



#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

using namespace Halcon;

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
	if (parm == "TransImage")
	{
		read_image(&ImageOrig, "blister/blister_reference");
		//read_image(&ImageOrig,value.c_str());
		// 	dev_open_window_fit_image(ImageOrig, 0, 0, -1, -1, &WindowHandle);
		// 	set_display_font(WindowHandle, 14, "mono", "true", "false");
		//	set_draw(HDevWindowStack::GetActive(),"margin");
		//	set_line_width(HDevWindowStack::GetActive(),3);
		//
		//In the first step, we create a pattern to cut out the chambers in the
		//subsequent blister images easily.
		threshold(ImageOrig, &Region, 90, 255);
		shape_trans(Region, &Blister, "convex");
		orientation_region(Blister, &Phi);
		area_center(Blister, &Area1, &Row, &Column);
		vector_angle_to_rigid(Row, Column, Phi, Row, Column, 0, &HomMat2D);
		affine_trans_image(ImageOrig, &Image2, HomMat2D, "constant", "false");
		gen_empty_obj(&Chambers);
		for (I=0; I<=4; I+=1)
		{
			Row = 88+(I*70);
			for (J=0; J<=2; J+=1)
			{
				Column = 163+(J*150);
				gen_rectangle2(&Rectangle, Row, Column, 0, 64, 30);
				concat_obj(Chambers, Rectangle, &Chambers);
			}
		}
		affine_trans_region(Blister, &Blister, HomMat2D, "false");
		difference(Blister, Chambers, &Pattern);
		union1(Chambers, &ChambersUnion);
		orientation_region(Blister, &PhiRef);
		PhiRef = (HTuple(180).Rad())+PhiRef;
		area_center(Blister, &Area2, &RowRef, &ColumnRef);
	}
	


}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{
		set_font (pData->m_ShowHWindow, "-Courier New-18-*-*-*-*-1-");
		set_line_width(pData->m_ShowHWindow,3);

		//read_image(&Image, "blister/blister_"+(Index.ToString("02")));
		Image = pData->m_Image;
		threshold(Image, &Region, 90, 255);
		connection(Region, &ConnectedRegions);
		select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 5000, 9999999);
		shape_trans(SelectedRegions, &RegionTrans, "convex");
		//
		//align pattern along blister of image
		orientation_region(RegionTrans, &Phi);
		area_center(RegionTrans, &Area3, &Row, &Column);
		vector_angle_to_rigid(Row, Column, Phi, RowRef, ColumnRef, PhiRef, &HomMat2D);
		affine_trans_image(Image, &ImageAffinTrans, HomMat2D, "constant", "false");
		//
		//segment pills
		reduce_domain(ImageAffinTrans, ChambersUnion, &ImageReduced);
		decompose3(ImageReduced, &ImageR, &ImageG, &ImageB);
		var_threshold(ImageB, &Region, 7, 7, 0.2, 2, "dark");
		connection(Region, &ConnectedRegions0);
		closing_rectangle1(ConnectedRegions0, &ConnectedRegions, 3, 3);
		fill_up(ConnectedRegions, &RegionFillUp);
		select_shape(RegionFillUp, &SelectedRegions, "area", "and", 1000, 99999);
		opening_circle(SelectedRegions, &RegionOpening, 4.5);
		connection(RegionOpening, &ConnectedRegions);
		select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 1000, 99999);
		shape_trans(SelectedRegions, &Pills, "convex");
		//
		//classify segmentation results and display statistics
		count_obj(Chambers, &Number);
		gen_empty_obj(&WrongPill);
		gen_empty_obj(&MissingPill);
		for (I=1; I<=Number; I+=1)
		{
			select_obj(Chambers, &Chamber, I);
			intersection(Chamber, Pills, &Pill);
			area_center(Pill, &Area, &Row1, &Column1);
			if (0 != (Area>0))
			{
				min_max_gray(Pill, ImageB, 0, &Min, &Max, &Range);
				if (0 != (HTuple(Area<3800).Or(Min<60)))
				{
					concat_obj(WrongPill, Pill, &WrongPill);
				}
			}
			else
			{
				concat_obj(MissingPill, Chamber, &MissingPill);
			}
		}
		//
// 			if (HDevWindowStack::IsOpen())
// 				clear_window(HDevWindowStack::GetActive());
		disp_obj(ImageAffinTrans, pData->m_ShowHWindow);
		set_color(pData->m_ShowHWindow,"forest green");
		count_obj(Pills, &NumberP);
		count_obj(WrongPill, &NumberWP);
		count_obj(MissingPill, &NumberMP);
		disp_obj(Pills, pData->m_ShowHWindow);
		if (0 != (HTuple(NumberMP>0).Or(NumberWP>0)))
		{
			set_color(pData->m_ShowHWindow,"red");
			set_tposition( pData->m_ShowHWindow, 10, 600);				
			write_string(pData->m_ShowHWindow, "错误");
			pData->m_isFail = true;
		}
		else
		{
			set_color(pData->m_ShowHWindow,"forest green");
			set_tposition( pData->m_ShowHWindow, 10, 600);				
			write_string(pData->m_ShowHWindow, "好的");
		}

		set_color(pData->m_ShowHWindow,"red");
		set_tposition( pData->m_ShowHWindow, 10, 10);		
		HTuple msg = "# 正确胶囊数:"+(NumberP-NumberWP);
		write_string(pData->m_ShowHWindow, msg);

		set_tposition( pData->m_ShowHWindow, 35, 10);		
		msg = "# 错误胶囊数:"+NumberWP;
		write_string(pData->m_ShowHWindow, msg);

// 		if (0 != (NumberWP>0))
// 		{
// 			set_color(pData->m_ShowHWindow,"red");
// 			set_tposition( pData->m_ShowHWindow, 35, 190);		
// 			msg = NumberWP;
// 			write_string(pData->m_ShowHWindow, msg);
// 		}

		set_color(pData->m_ShowHWindow,"red");
		set_tposition( pData->m_ShowHWindow, 60, 10);		
		msg = "# 缺少胶囊数:"+NumberMP;
		write_string(pData->m_ShowHWindow, msg);

// 		if (0 != (NumberMP>0))
// 		{
// 			set_color(pData->m_ShowHWindow,"red");
// 			set_tposition( pData->m_ShowHWindow, 60, 190);		
// 			msg = NumberMP;
// 			write_string(pData->m_ShowHWindow, msg);
// 		}
		set_color(pData->m_ShowHWindow,"red");
		disp_obj(WrongPill, pData->m_ShowHWindow);
		disp_obj(MissingPill, pData->m_ShowHWindow);


	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		pData->m_center_x=350;
		pData->m_center_y=250;
		pData->r_real=100;
		testItem->m_ErrorX = 1;
		testItem->m_ErrorY = 1  ;
		testItem->m_ErrorR = 4;
	}

}




