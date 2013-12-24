// CanBodyLocation01.cpp : 定义 DLL 应用程序的导出函数。
//
/*
	印刷片料罐身定位算子  
	检测罐身 Reg1, Reg2

	片料印白定位增加
	1.	使用二值分割法来定位罐身的焊缝区域
*/
#include "stdafx.h"
#include "CanBodyLocation01.h"

using namespace std;
using namespace Halcon;

#ifndef DLLEXPT
#define DLLEXPT __declspec (dllexport)
#endif

CDoProcess::CDoProcess()
{
	ShowObject = false;
	printf("CanBodyLocation01 Function\r\n");
	
}

void CDoProcess::SetParmeter(string parm, string value)
{
	if(parm=="SHOWOBJECT")
	{	if (value=="YES")
			ShowObject = true;
		else
			ShowObject = false;
	}

	// CROP_HEIGHT
	if ("CROP_HEIGHT"== parm)
		m_Parameters.CROP_HEIGHT = atoi(value.c_str());
	
	if ("Row1"== parm)
		m_Parameters.Row1 = atoi(value.c_str());	
	if ("Row2"== parm)
		m_Parameters.Row2 = atoi(value.c_str());	
	if ("Row3"== parm)
		m_Parameters.Row3 = atoi(value.c_str());
	if ("Col1"== parm)
		m_Parameters.Col1 = atoi(value.c_str());
	if ("Col2"== parm)
		m_Parameters.Col2 = atoi(value.c_str());
	if ("Col3"== parm)
		m_Parameters.Col3 = atoi(value.c_str());

	if ("Rect01_threshold_min"== parm)
		m_Parameters.Rect01_threshold_min = atoi(value.c_str());	
	if ("Rect02_threshold_min"== parm)
		m_Parameters.Rect02_threshold_min = atoi(value.c_str());	
	if ("Rect03_threshold_min"== parm)
		m_Parameters.Rect03_threshold_min = atoi(value.c_str());	
	if ("Rect04_threshold_min"== parm)
		m_Parameters.Rect04_threshold_min = atoi(value.c_str());
	if ("Rect05_threshold_min"== parm)
		m_Parameters.Rect05_threshold_min = atoi(value.c_str());
	if ("Rect06_threshold_min"== parm)
		m_Parameters.Rect06_threshold_min = atoi(value.c_str());
	if ("Rect07_threshold_min"== parm)
		m_Parameters.Rect07_threshold_min = atoi(value.c_str());

	// ADD LOCATION RECTNGLE ON GUANSHEN BODY INCLUDE LEFT AND RIGHT GUANSHEN BODY
	if ("reg1_Col"== parm)
		m_Parameters.reg1_Col = atoi(value.c_str());
	if ("reg2_Col"== parm)
		m_Parameters.reg2_Col = atoi(value.c_str());

	if ("width_Min"== parm)
		m_Parameters.width_Min = atoi(value.c_str());
	if ("width_Max"== parm)
		m_Parameters.width_Max = atoi(value.c_str());
	if ("height_Min"== parm)
		m_Parameters.height_Min = atoi(value.c_str());
	if ("height_Max"== parm)
		m_Parameters.height_Max = atoi(value.c_str());
}
#define LinesPerFrame 900
void CDoProcess::DoProcess(CMData* pData, SubTestResult *testItem)
{	
	// 添加新的定位部分
	//
	try
	{
		TiledImage01=pData->m_Image;
		get_image_size(TiledImage01, &Width_Tile, &Height_Tile);  
		
		HTuple  rows0,cols0,rows1,cols1;
		HTuple  len0, len1;
		Hobject cirr0, cirr1;
		HTuple  Rec01_width, Rec07_width, Rec04_width;
		// set color type
		set_color(pData->m_ShowHWindow,"blue");
		// 单个罐身或两个罐身 
		if (0 != (Width_Tile<DefaultWidth))
		{
			//ROI 1
			gen_rectangle2(&Rect01, m_Parameters.Row2, m_Parameters.Col1, 0, 200, 50);  // HANFENG 1
			if(ShowObject)
				disp_obj(Rect01,pData->m_ShowHWindow);
			//ROI 2
			gen_rectangle2(&Rect02, m_Parameters.Row1, m_Parameters.reg1_Col, 0, 25*2, 200);
			if(ShowObject)
				disp_obj(Rect02,pData->m_ShowHWindow);
			//ROI 6
			gen_rectangle2(&Rect06, m_Parameters.Row3, m_Parameters.reg1_Col, 0, 25*2, 200);
			if(ShowObject)
				disp_obj(Rect06,pData->m_ShowHWindow);
			//ROI 7
			gen_rectangle2(&Rect07, m_Parameters.Row2, m_Parameters.Col2, 0, 200, 50); // HANFENG 7
			if(ShowObject)
				disp_obj(Rect07,pData->m_ShowHWindow);	
			
			/// location from guanshen body
			bin_threshold(TiledImage01, &Region);
			connection(Region, &ConnectedRegions);
			select_shape(ConnectedRegions, &SelectedRegions, "width", "and", m_Parameters.width_Min, m_Parameters.width_Max);
			select_shape(SelectedRegions, &SelectedRegions1, "height", "and", m_Parameters.height_Min, m_Parameters.height_Max);
			count_obj(SelectedRegions1, &Number);
			// 寻找罐身成功，使用新的罐身定位算法，失败则使用原始算法
			if (0 != (Number>0))
			{

				erosion_rectangle1(SelectedRegions1, &RegionErosion, 5, 5);
				smallest_rectangle2(RegionErosion, &Row, &Column, &Phi, &Length1, &Length2);

				gen_rectangle2(&Rectangle1, HTuple(Row[0]), HTuple(Column[0]), HTuple(Phi[0]), HTuple(Length1[0]), HTuple(Length2[0]));
				
				// 画一个包含两侧焊缝的矩形来计算一个罐身的两侧焊缝
				gen_rectangle2(&Rectangle3, HTuple(Row[0]), HTuple(Column[0]), HTuple(Phi[0]), HTuple(Length1[0])+100, HTuple(Length2[0])-40);
								
				reduce_domain(TiledImage01, Rectangle3, &ImageReduced);
				fast_threshold(ImageReduced, &Region, (m_Parameters.Rect01_threshold_min +m_Parameters.Rect07_threshold_min)/2, 255, 10);
				connection(Region, &ConnectedRegions1);
				erosion_rectangle1(ConnectedRegions1, &RegionErosion1, 5, 5);

				/// AVOID EXCEPTION
				Hobject  SelectedRegions1;
				select_shape (RegionErosion1, &SelectedRegions1, "height", "and", Length2[0].D()*2-100, LinesPerFrame);

				smallest_rectangle2(SelectedRegions1, &Row1, &Column1, &Phi1, &Length11, &Length12);
				

				//****************** hanfeng 7
				han1_row     = Row1[0];    
				han1_col     = Column1[0];
				han1_phi     = Phi1[0];
				han1_hwidth  = Length12[0];
				han1_hheight = HTuple(Length11[0])+40;

				//****************** hanfeng 7
				han7_row     = Row1[0];
				han7_col     = Column1[1];
				han7_phi     = Phi1[1];
				han7_hwidth  = Length12[1];
				han7_hheight = HTuple(Length11[1])+40;

				//******************* 
				// rec01
				pData->m_orientationPhi = han1_phi[0].D(); // hanfeng1 phi
				pData->m_center_x       = han1_col[0].D(); // hanfeng1 center column
				pData->m_center_y       = han1_row[0].D(); // hanfeng1 width
				
				// rec07
				pData->m_orientationPhi3 = han7_phi[0].D(); // hanfeng7 phi
				pData->m_center_x2       = han7_col[0].D(); // hanfeng7 center column
				pData->m_center_y2       = han7_row[0].D(); // hanfeng7 width

				pData->m_TestRegist1     = Rectangle1;      // Reg1 object

				set_color(pData->m_ShowHWindow,"blue");
				if(ShowObject)
					disp_obj(rectangle1,pData->m_ShowHWindow);			
			}
			else
			{
				//**********ROI 1   
				reduce_domain(TiledImage01, Rect01, &RectImage01);
				fast_threshold(RectImage01, &Region01, m_Parameters.Rect01_threshold_min, 255, 10);
				erosion_rectangle1(Region01, &Rec01, 5, 5);
				smallest_rectangle1(Rec01, &Rec01_Row1, &Rec01_Column1, &Rec01_Row2, &Rec01_Column2);
				smallest_rectangle2(Rec01,&Rec01_Row,&Rec01_Column,&Rec01_phi,&Rec01_len1,&Rec01_len2);        // (height, width)
							

				//**********ROI 2
				reduce_domain(TiledImage01, Rect02, &RectImage02);
				fast_threshold(RectImage02, &Region02, m_Parameters.Rect02_threshold_min, 255, 10);
				erosion_rectangle1(Region02, &Rec02, 5, 5);
				smallest_rectangle1(Rec02, &Rec02_Row1, &Rec02_Column1, &Rec02_Row2, &Rec02_Column2);
				smallest_rectangle2(Rec02, &Rec02_Row,  &Rec02_Column,  &Rec02_phi,  &Rec02_len1, &Rec02_len2);  // ADD  (height, width)
				

				//**********ROI 6
				reduce_domain(TiledImage01, Rect06, &RectImage06);
				fast_threshold(RectImage06, &Region06, m_Parameters.Rect06_threshold_min, 255, 10);
				erosion_rectangle1(Region06, &Rec06, 5, 5);
				smallest_rectangle1(Rec06, &Rec06_Row1, &Rec06_Column1, &Rec06_Row2, &Rec06_Column2);
				smallest_rectangle2(Rec06, &Rec06_Row,  &Rec06_Column,  &Rec06_phi,  &Rec06_len1, &Rec06_len2);  // ADD  (height, width)


				//**********ROI 7   
				reduce_domain(TiledImage01, Rect07, &RectImage07);
				fast_threshold(RectImage07, &Region07, m_Parameters.Rect07_threshold_min, 255, 10);
				erosion_rectangle1(Region07, &Rec07, 5, 5);
				smallest_rectangle1(Rec07, &Rec07_Row1, &Rec07_Column1, &Rec07_Row2, &Rec07_Column2);
				smallest_rectangle2(Rec07,&Rec07_Row,&Rec07_Column,&Rec07_phi,&Rec07_len1,&Rec07_len2);          // (height, width)
				
				///// width direction && heigth direction 
				HTuple regLen1 = (Rec07_Column -Rec07_len2) -(Rec01_Column +Rec01_len2);  
				HTuple regLen2 = (Rec06_Row -Rec06_len1) - (Rec02_Row +Rec02_len1);
				
				HTuple reg1_Sin_, reg1_Cos_;
				tuple_sin((Rec01_phi+Rec07_phi)/2, &reg1_Sin_);
				tuple_cos((Rec01_phi+Rec07_phi)/2, &reg1_Cos_);
				
				Reg1_hwidth  = regLen1*reg1_Sin_/2;
				Reg1_hheight = regLen2*reg1_Sin_/2;

				// guanshen region 1 center point axes
				Reg1_row     = (Rec02_Row +Rec02_len1) + Reg1_hheight;
				Reg1_col     = (Rec01_Column +Rec01_len2) + Reg1_hwidth;
				Reg1_phi     = (Rec01_phi + Rec07_phi)/2;
				
				gen_rectangle2(&rectangle1, Reg1_row, Reg1_col, Reg1_phi, Reg1_hheight, Reg1_hwidth);
				
				// compute rec01 axes
				HTuple o1 = regLen1*reg1_Cos_;
				HTuple o2 = o1*reg1_Cos_;
				HTuple o3 = o1*reg1_Sin_;
				
				// 	
				HTuple rec01_ct_col = (Rec01_Column +Rec01_len2) + o2;
				HTuple rec01_ct_row = Reg1_row + o3;
							
				//******************* 
				// rec01
				pData->m_orientationPhi = Rec01_phi[0].D(); // hanfeng1 phi
				pData->m_center_x       = rec01_ct_col[0].D(); // hanfeng1 center column
				pData->m_center_y       = rec01_ct_row[0].D(); // hanfeng1 width
				
				//
				HTuple rec07_ct_col  = (Rec07_Column -Rec07_len2) - o2;
				HTuple rec07_ct_row  = Reg1_row - o3;

				// rec07
				pData->m_orientationPhi3 = Rec07_phi[0].D(); // hanfeng7 phi
				pData->m_center_x2       = rec07_ct_col[0].D(); // hanfeng7 center column
				pData->m_center_y2       = rec07_ct_row[0].D(); // hanfeng7 width

				pData->m_TestRegist1     = rectangle1;      // Reg1 object

				set_color(pData->m_ShowHWindow,"blue");
				disp_obj(rectangle1,pData->m_ShowHWindow);		
			}
		}
		else
		{
			//ROI 1
			gen_rectangle2(&Rect01, m_Parameters.Row2, m_Parameters.Col1, 0, 200, 50); 
			if(ShowObject)
				disp_obj(Rect01,pData->m_ShowHWindow);	
			//ROI 2
			gen_rectangle2(&Rect02, m_Parameters.Row1, m_Parameters.reg1_Col, 0, 25*2, 200);
			if(ShowObject)
				disp_obj(Rect02,pData->m_ShowHWindow);	
			//ROI 3
			gen_rectangle2(&Rect06, m_Parameters.Row3, m_Parameters.reg1_Col, 0, 25*2, 200);
			if(ShowObject)
				disp_obj(Rect06,pData->m_ShowHWindow);	
			//ROI 4
			gen_rectangle2(&Rect07, m_Parameters.Row2, m_Parameters.Col2, 0, 200, 50); 
			if(ShowObject)
				disp_obj(Rect07,pData->m_ShowHWindow);	
			//ROI 5
			gen_rectangle2(&Rect03, m_Parameters.Row1, m_Parameters.reg2_Col, 0, 25*2, 200);
			if(ShowObject)
				disp_obj(Rect03,pData->m_ShowHWindow);	
			//ROI 6
			gen_rectangle2(&Rect05, m_Parameters.Row3, m_Parameters.reg2_Col, 0, 25*2, 200);
			if(ShowObject)
				disp_obj(Rect05,pData->m_ShowHWindow);	
			//ROI 7
			gen_rectangle2(&Rect04, m_Parameters.Row2, m_Parameters.Col3, 0, 200, 50);
			if(ShowObject)
				disp_obj(Rect04,pData->m_ShowHWindow);	
			
			/// location from guanshen body
			bin_threshold(TiledImage01, &Region);
			connection(Region, &ConnectedRegions);
			select_shape(ConnectedRegions, &SelectedRegions, "width", "and", m_Parameters.width_Min, m_Parameters.width_Max);
			select_shape(SelectedRegions, &SelectedRegions1, "height", "and", m_Parameters.height_Min, m_Parameters.height_Max);
			count_obj(SelectedRegions1, &Number);

			// 寻找罐身成功，使用新的罐身定位算法，失败则使用原始算法
			if (0 != (Number>0))
			{
				erosion_rectangle1(SelectedRegions1, &RegionErosion, 5, 5);
				smallest_rectangle2(RegionErosion, &Row, &Column, &Phi, &Length1, &Length2);

				gen_rectangle2(&Rectangle1, HTuple(Row[0]), HTuple(Column[0]), HTuple(Phi[0]), HTuple(Length1[0]), HTuple(Length2[0]));
								
				gen_rectangle2(&Rectangle2, HTuple(Row[1]), HTuple(Column[1]), HTuple(Phi[1]), HTuple(Length1[1]), HTuple(Length2[1]));
								
				
				set_color(pData->m_ShowHWindow,"blue");
				if(ShowObject)
				{
					disp_obj(Rectangle1,pData->m_ShowHWindow);	
					disp_obj(Rectangle2,pData->m_ShowHWindow);	
				}

				//*****
				gen_rectangle2(&Rectangle3, HTuple(Row[0]), HTuple(Column[0]), HTuple(Phi[0]), HTuple(Length1[0])+100, HTuple(Length2[0])-40);
				reduce_domain(TiledImage01, Rectangle3, &ImageReduced);
				fast_threshold(ImageReduced, &Region, (m_Parameters.Rect01_threshold_min+m_Parameters.Rect07_threshold_min)/2, 255, 10);
				connection(Region, &ConnectedRegions1);
				erosion_rectangle1(ConnectedRegions1, &RegionErosion1, 5, 5);
				
				/// AVOID EXCEPTION
				Hobject  SelectedRegions1;
				select_shape (RegionErosion1, &SelectedRegions1, "height", "and", Length2[0].D()*2-100, LinesPerFrame);
				//  RegionErosion1
				smallest_rectangle2(SelectedRegions1, &Row1, &Column1, &Phi1, &Length11, &Length12);
		
				//*****
				gen_rectangle2(&Rectangle4, HTuple(Row[1]), HTuple(Column[1]), HTuple(Phi[1]), HTuple(Length1[1])+100, HTuple(Length2[1])-40);
								
				reduce_domain(TiledImage01, Rectangle4, &ImageReduced1);
				fast_threshold(ImageReduced1, &Region1, (m_Parameters.Rect07_threshold_min+m_Parameters.Rect04_threshold_min)/2, 255, 10);
				connection(Region1, &ConnectedRegions11);
				erosion_rectangle1(ConnectedRegions11, &RegionErosion11, 5, 5);

				/// AVOID EXCEPTION
				Hobject  SelectedRegions2;
				select_shape (RegionErosion11, &SelectedRegions2, "height", "and", Length2[0].D()*2-100, LinesPerFrame);
				// RegionErosion2
				smallest_rectangle2(SelectedRegions2, &Row11, &Column11, &Phi11, &Length121, &Length22);
				
				//****************** hanfeng 1
				han1_row = Row1[0];
				han1_col = Column1[0];
				han1_phi = Phi1[0];
				han1_hwidth = Length12[0];
				han1_hheight = HTuple(Length11[0])+40;
			
				//****************** hanfeng 7
			
				han7_row = (HTuple(Row1[1])+HTuple(Row11[0]))/2;
				han7_col = (HTuple(Column1[1])+HTuple(Column11[0]))/2;
				han7_phi = (HTuple(Phi1[1])+HTuple(Phi11[0]))/2;

				han7_hwidth = (HTuple(Length12[1])+HTuple(Length22[0]))/2;
				han7_hheight = ((HTuple(Length11[1])+HTuple(Length121[0]))/2)+40;
			
				//****************** hanfeng 4
				HTuple han4_row = Row11[1];
				HTuple han4_col = Column11[1];
				HTuple han4_phi = Phi11[1];
				HTuple han4_hwidth = Length22[1];
				HTuple han4_hheight = HTuple(Length121[1])+40;
			
				// rec01 
				pData->m_orientationPhi = han1_phi[0].D();      // hanfeng1 phi
				pData->m_center_x       = han1_col[0].D();      // hanfeng1 center column
				pData->m_center_y       = han1_row[0].D();      // hanfeng1 width
								
				// rec07
				pData->m_orientationPhi3 = han7_phi[0].D();     // hanfeng7 phi
				pData->m_center_x2       = han7_col[0].D();     // hanfeng7 center column
				pData->m_center_y2       = han7_row[0].D();     // hanfeng7 width

				// rec04
				pData->r_real            = han4_phi[0].D();     // hanfeng4 phi
				pData->m_center_x3       = han4_col[0].D();     // hanfeng4 center column
				pData->m_center_y3       = han4_row[0].D();     // hanfeng4 width

				pData->m_TestRegist1     = Rectangle1;          // Reg1 object
				pData->m_TestRegist2     = Rectangle2;          // Reg2 object

				
				
			}
			else
			{
				//**********ROI_1  
				reduce_domain(TiledImage01, Rect01, &RectImage01);
				fast_threshold(RectImage01, &Region01, m_Parameters.Rect01_threshold_min, 255, 10);
				erosion_rectangle1(Region01, &Rec01, 5, 5);
				smallest_rectangle1(Rec01, &Rec01_Row1, &Rec01_Column1, &Rec01_Row2, &Rec01_Column2);
				smallest_rectangle2(Rec01,&Rec01_Row,&Rec01_Column,&Rec01_phi,&Rec01_len1,&Rec01_len2);
				tuple_abs(Rec01_Column2-Rec01_Column1,&Rec01_width); // for test

				//**********ROI_2
				reduce_domain(TiledImage01, Rect02, &RectImage02);
				fast_threshold(RectImage02, &Region02, m_Parameters.Rect02_threshold_min, 255, 10);
				erosion_rectangle1(Region02, &Rec02, 3, 3);
				smallest_rectangle1(Rec02, &Rec02_Row1, &Rec02_Column1, &Rec02_Row2, &Rec02_Column2);
				smallest_rectangle2(Rec02, &Rec02_Row,  &Rec02_Column,&Rec02_phi,&Rec02_len1,&Rec02_len2);

				//**********ROI_6
				reduce_domain(TiledImage01, Rect06, &RectImage06);
				fast_threshold(RectImage06, &Region06, m_Parameters.Rect06_threshold_min, 255, 10);
				erosion_rectangle1(Region06, &Rec06, 3, 3);
				smallest_rectangle1(Rec06, &Rec06_Row1, &Rec06_Column1, &Rec06_Row2, &Rec06_Column2);
				smallest_rectangle2(Rec06, &Rec06_Row,  &Rec06_Column,&Rec06_phi,&Rec06_len1,&Rec06_len2);

				//**********ROI_7 
				reduce_domain(TiledImage01, Rect07, &RectImage07);
				fast_threshold(RectImage07, &Region07, m_Parameters.Rect07_threshold_min, 255, 10);
				erosion_rectangle1(Region07, &Rec07, 5, 5);
				smallest_rectangle1(Rec07, &Rec07_Row1, &Rec07_Column1, &Rec07_Row2, &Rec07_Column2);
				smallest_rectangle2(Rec07,&Rec07_Row,&Rec07_Column,&Rec07_phi,&Rec07_len1,&Rec07_len2);
				tuple_abs(Rec07_Column2-Rec07_Column1,&Rec07_width); //for test

				//**********ROI_3
				reduce_domain(TiledImage01, Rect03, &RectImage03);
				fast_threshold(RectImage03, &Region03, m_Parameters.Rect03_threshold_min, 255, 10);
				erosion_rectangle1(Region03, &Rec03, 3, 3);
				smallest_rectangle1(Rec03, &Rec03_Row1, &Rec03_Column1, &Rec03_Row2, &Rec03_Column2);
				smallest_rectangle2(Rec03,&Rec03_Row,&Rec03_Column,&Rec03_phi,&Rec03_len1,&Rec03_len2);

				//**********ROI_5
				reduce_domain(TiledImage01, Rect05, &RectImage05);
				fast_threshold(RectImage05, &Region05, m_Parameters.Rect05_threshold_min, 255, 10);
				erosion_rectangle1(Region05, &Rec05, 3, 3);
				smallest_rectangle1(Rec05, &Rec05_Row1, &Rec05_Column1, &Rec05_Row2, &Rec05_Column2);
				smallest_rectangle2(Rec05,&Rec05_Row,&Rec05_Column,&Rec05_phi,&Rec05_len1,&Rec05_len2);

				//**********ROI_4  
				reduce_domain(TiledImage01, Rect04, &RectImage04);
				fast_threshold(RectImage04, &Region04, m_Parameters.Rect04_threshold_min, 255, 10);
				erosion_rectangle1(Region04, &Rec04, 5, 5);
				smallest_rectangle1(Rec04, &Rec04_Row1, &Rec04_Column1, &Rec04_Row2, &Rec04_Column2);
				smallest_rectangle2(Rec04,&Rec04_Row,&Rec04_Column,&Rec04_phi,&Rec04_len1,&Rec04_len2);
				tuple_abs(Rec04_Column2-Rec04_Column1,&Rec04_width); // for test

				///// width direction && heigth direction 
				// guanshen 1
				HTuple reg1Len1 = (Rec07_Column -Rec07_len2) -(Rec01_Column +Rec01_len2);  
				HTuple reg1Len2 = (Rec06_Row -Rec06_len1) - (Rec02_Row +Rec02_len1);

				// guanshen 2
				HTuple reg2Len1 = (Rec04_Column -Rec04_len2) -(Rec07_Column +Rec07_len2);  
				HTuple reg2Len2 = (Rec05_Row -Rec05_len1) - (Rec03_Row +Rec03_len1);
				
				// guanshen 1
				HTuple reg1_Sin_, reg1_Cos_;
				tuple_sin((Rec01_phi+Rec07_phi)/2, &reg1_Sin_);
				tuple_cos((Rec01_phi+Rec07_phi)/2, &reg1_Cos_);
				Reg1_hwidth  = reg1Len1*reg1_Sin_/2;
				Reg1_hheight = reg1Len2*reg1_Sin_/2;
				
				// guanshen 2
				HTuple reg2_Sin_, reg2_Cos_;
				tuple_sin((Rec07_phi+Rec04_phi)/2, &reg2_Sin_);
				tuple_cos((Rec07_phi+Rec04_phi)/2, &reg2_Cos_);
				Reg2_hwidth  = reg2Len1*reg1_Sin_/2;
				Reg2_hheight = reg2Len2*reg1_Sin_/2;

				// guanshen region 1 center point axes
				Reg1_row     = (Rec02_Row +Rec02_len1) + Reg1_hheight;
				Reg1_col     = (Rec01_Column +Rec01_len2) + Reg1_hwidth;
				Reg1_phi     = (Rec01_phi + Rec07_phi)/2;
				
				gen_rectangle2(&rectangle1, Reg1_row, Reg1_col, Reg1_phi, Reg1_hheight, Reg1_hwidth);
				
				// guanshen region 2 center point axes
				Reg2_row     = (Rec03_Row +Rec03_len1) + Reg2_hheight;
				Reg2_col     = (Rec07_Column +Rec07_len2) + Reg2_hwidth;
				Reg2_phi     = (Rec07_phi + Rec04_phi)/2;

				gen_rectangle2(&rectangle2, Reg2_row, Reg2_col, Reg2_phi, Reg2_hheight, Reg2_hwidth);
				// compute rec01 axes
				HTuple o1 = reg1Len1*reg1_Cos_;
				HTuple o2 = o1*reg1_Cos_;
				HTuple o3 = o1*reg1_Sin_;

				// rec01 center   
				HTuple rec01_ct_col = (Rec01_Column +Rec01_len2) + o2;
				HTuple rec01_ct_row = Reg1_row + o3;

				// rec01
				pData->m_orientationPhi = Rec01_phi[0].D(); // hanfeng1 phi
				pData->m_center_x       = rec01_ct_col[0].D(); // hanfeng1 center column
				pData->m_center_y       = rec01_ct_row[0].D(); // hanfeng1 width

				// rec07 center
				HTuple rec07_ct_col  = (Rec07_Column -Rec07_len2) - o2;
				HTuple rec07_ct_row  = Reg1_row - o3;

				// rec07
				pData->m_orientationPhi3 = Rec07_phi[0].D(); // hanfeng7 phi
				pData->m_center_x2       = rec07_ct_col[0].D(); // hanfeng7 center column
				pData->m_center_y2       = rec07_ct_row[0].D(); // hanfeng7 width

				pData->m_TestRegist1     = rectangle1;      // Reg1 object

				// compute rec02 axes
				HTuple s1 = reg2Len1*reg1_Cos_;
				HTuple s2 = s1*reg1_Cos_;
				HTuple s3 = s1*reg1_Sin_;
				HTuple rec04_ct_col  = (Rec04_Column -Rec04_len2) - s2;
				HTuple rec04_ct_row  = Reg2_row - s3;

				// rec04  center
				// rec04
				pData->r_real            = Rec07_phi[0].D();        // hanfeng4 phi
				pData->m_center_x3       = rec04_ct_col[0].D();     // hanfeng4 center column
				pData->m_center_y3       = rec04_ct_row[0].D();     // hanfeng4 width

				pData->m_TestRegist2     = rectangle2;

				set_color(pData->m_ShowHWindow,"blue");
				//if(ShowObject)
				{
					disp_obj(rectangle1,pData->m_ShowHWindow);		
					disp_obj(rectangle2,pData->m_ShowHWindow);	
				}
				
			}

		}
	}
	catch (...) 
	{
		//if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow, "green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"CanBodyLocation01SheetIron parameter values error,please re-adjust");
			#else
			write_string(pData->m_ShowHWindow,"CanBodyLocation01罐身定位算子调整出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}	
}

