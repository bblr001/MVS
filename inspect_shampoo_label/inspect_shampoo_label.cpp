// check_blister_mixed.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "inspect_shampoo_label.h"


#include "cpp\HalconCpp.h"

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

// Default exception handler 
void CPPExpDefaultExceptionHandler(const Halcon::HException& except)
{
	throw except;
}

// Chapter: Graphics / Text
// Short Description: This procedure writes a text message.
void disp_message (Halcon::HTuple WindowHandle, Halcon::HTuple String, Halcon::HTuple CoordSystem, 
				   Halcon::HTuple Row, Halcon::HTuple Column, Halcon::HTuple Color, Halcon::HTuple Box)
{
	using namespace Halcon;

	// Local control variables 
	HTuple  Red, Green, Blue, Row1Part, Column1Part;
	HTuple  Row2Part, Column2Part, RowWin, ColumnWin, WidthWin;
	HTuple  HeightWin, MaxAscent, MaxDescent, MaxWidth, MaxHeight;
	HTuple  R1, C1, FactorRow, FactorColumn, Width, Index, Ascent;
	HTuple  Descent, W, H, FrameHeight, FrameWidth, R2, C2;
	HTuple  DrawMode, Exception, CurrentColor;


	// Install default exception handler 
	HException::InstallHHandler(&CPPExpDefaultExceptionHandler);

	//This procedure displays text in a graphics window.
	//
	//Input parameters:
	//WindowHandle: The WindowHandle of the graphics window, where
	//   the message should be displayed
	//String: A tuple of strings containing the text message to be displayed
	//CoordSystem: If set to 'window', the text position is given
	//   with respect to the window coordinate system.
	//   If set to 'image', image coordinates are used.
	//   (This may be useful in zoomed images.)
	//Row: The row coordinate of the desired text position
	//   If set to -1, a default value of 12 is used.
	//Column: The column coordinate of the desired text position
	//   If set to -1, a default value of 12 is used.
	//Color: defines the color of the text as string.
	//   If set to [], '' or 'auto' the currently set color is used.
	//   If a tuple of strings is passed, the colors are used cyclically
	//   for each new textline.
	//Box: If set to 'true', the text is written within a white box.
	//
	//prepare window
	get_rgb(WindowHandle, &Red, &Green, &Blue);
	get_part(WindowHandle, &Row1Part, &Column1Part, &Row2Part, &Column2Part);
	get_window_extents(WindowHandle, &RowWin, &ColumnWin, &WidthWin, &HeightWin);
	set_part(WindowHandle, 0, 0, HeightWin-1, WidthWin-1);
	//
	//default settings
	if (0 != (Row==-1))
	{
		Row = 12;
	}
	if (0 != (Column==-1))
	{
		Column = 12;
	}
	if (0 != (Color==HTuple()))
	{
		Color = "";
	}
	//
	String = ((""+String)+"").Split("\n");
	//
	//Estimate extentions of text depending on font size.
	get_font_extents(WindowHandle, &MaxAscent, &MaxDescent, &MaxWidth, &MaxHeight);
	if (0 != (CoordSystem==HTuple("window")))
	{
		R1 = Row;
		C1 = Column;
	}
	else
	{
		//transform image to window coordinates
		FactorRow = (1.*HeightWin)/((Row2Part-Row1Part)+1);
		FactorColumn = (1.*WidthWin)/((Column2Part-Column1Part)+1);
		R1 = ((Row-Row1Part)+0.5)*FactorRow;
		C1 = ((Column-Column1Part)+0.5)*FactorColumn;
	}
	//
	//display text box depending on text size
	if (0 != (Box==HTuple("true")))
	{
		//calculate box extents
		String = (" "+String)+" ";
		Width = HTuple();
		for (Index=0; Index<=(String.Num())-1; Index+=1)
		{
			get_string_extents(WindowHandle, HTuple(String[Index]), &Ascent, &Descent, 
				&W, &H);
			Width.Append(W);
		}
		FrameHeight = MaxHeight*(String.Num());
		FrameWidth = (HTuple(0).Concat(Width)).Max();
		R2 = R1+FrameHeight;
		C2 = C1+FrameWidth;
		//display rectangles
		get_draw(WindowHandle, &DrawMode);
		set_draw(WindowHandle, "fill");
		set_color(WindowHandle, "light gray");
		disp_rectangle1(WindowHandle, R1+3, C1+3, R2+3, C2+3);
		set_color(WindowHandle, "white");
		disp_rectangle1(WindowHandle, R1, C1, R2, C2);
		set_draw(WindowHandle, DrawMode);
	}
	else if (0 != (Box!=HTuple("false")))
	{
		Exception = "Wrong value of control parameter Box";
		throw HException(Exception);
	}
	//Write text.
	for (Index=0; Index<=(String.Num())-1; Index+=1)
	{
		CurrentColor = Color[Index%(Color.Num())];
		if (0 != (HTuple(CurrentColor!=HTuple("")).And(CurrentColor!=HTuple("auto"))))
		{
			set_color(WindowHandle, CurrentColor);
		}
		else
		{
			set_rgb(WindowHandle, Red, Green, Blue);
		}
		Row = R1+(MaxHeight*Index);
		set_tposition(WindowHandle, Row, C1);
		write_string(WindowHandle, HTuple(String[Index]));
	}
	//reset changed window settings
	set_rgb(WindowHandle, Red, Green, Blue);
	set_part(WindowHandle, Row1Part, Column1Part, Row2Part, Column2Part);
	return;
}


// Procedures 
// External procedures 
// Chapter: Matching / Shape-Based
// Short Description: Display the results of Shape-Based Matching.
void dev_display_shape_matching_results (Halcon::HTuple ModelID, Halcon::HTuple Color, 
										 Halcon::HTuple Row, Halcon::HTuple Column, Halcon::HTuple Angle, Halcon::HTuple ScaleR, 
										 Halcon::HTuple ScaleC, Halcon::HTuple Model,Halcon::HTuple hwindow)
{
	using namespace Halcon;

	// Local iconic variables 
	Hobject  ModelContours, ContoursAffinTrans;


	// Local control variables 
	HTuple  NumMatches, Index, Match, HomMat2DIdentity;
	HTuple  HomMat2DScale, HomMat2DRotate, HomMat2DTranslate;

	//This procedure displays the results of Shape-Based Matching.
	//
	NumMatches = Row.Num();
	if (0 != (NumMatches>0))
	{
		if (0 != ((ScaleR.Num())==1))
		{
			tuple_gen_const(NumMatches, ScaleR, &ScaleR);
		}
		if (0 != ((ScaleC.Num())==1))
		{
			tuple_gen_const(NumMatches, ScaleC, &ScaleC);
		}
		if (0 != ((Model.Num())==0))
		{
			tuple_gen_const(NumMatches, 0, &Model);
		}
		else if (0 != ((Model.Num())==1))
		{
			tuple_gen_const(NumMatches, Model, &Model);
		}
		for (Index=0; Index<=(ModelID.Num())-1; Index+=1)
		{
			get_shape_model_contours(&ModelContours, HTuple(ModelID[Index]), 1);
			set_color(hwindow,HTuple(Color[Index%(Color.Num())]));
			for (Match=0; Match<=NumMatches-1; Match+=1)
			{
				if (0 != (Index==HTuple(Model[Match])))
				{
					hom_mat2d_identity(&HomMat2DIdentity);
					hom_mat2d_scale(HomMat2DIdentity, HTuple(ScaleR[Match]), HTuple(ScaleC[Match]), 
						0, 0, &HomMat2DScale);
					hom_mat2d_rotate(HomMat2DScale, HTuple(Angle[Match]), 0, 0, &HomMat2DRotate);
					hom_mat2d_translate(HomMat2DRotate, HTuple(Row[Match]), HTuple(Column[Match]), 
						&HomMat2DTranslate);
					affine_trans_contour_xld(ModelContours, &ContoursAffinTrans, HomMat2DTranslate);

					disp_obj(ContoursAffinTrans,hwindow);
				}
			}
		}
	}
	return;
}

CDoProcess::CDoProcess()
{
	ShowObject=false;
	//m_ProcessName ="QinanHuanTest";
	HException::InstallHHandler(&MyHalconExceptionHandler);
}
CDoProcess::~CDoProcess()
{
//  	clear_shape_model(ModelIDLabel1);
//  	clear_shape_model(ModelIDLabel2);
//  	clear_shape_model(ModelIDBottle);
// 	set_system("clip_region", "true");


	//clear_class_gmm(GMMHandle);
}


void CDoProcess::SetParmeter(string parm,string value)
{
	if (parm == "TransImage")
	{
		//load reference image for model preparation
		read_image(&Image, "packaging/shampoo_01");

		//
		//prepare the shape model for matching
		//
		//generate first model region and search ROI
		BottleModelRow = 131;
		BottleModelColumn = 370;
		BottleModelLength1 = 350;
		BottleModelLength2 = 35;
		BottleModelPhi = -0.1093;
		gen_rectangle2(&Rectangle1, BottleModelRow, BottleModelColumn, BottleModelPhi, 
			BottleModelLength1, BottleModelLength2);
		gen_rectangle2(&Rectangle2, BottleModelRow+220, BottleModelColumn, -BottleModelPhi, 
			BottleModelLength1, BottleModelLength2);
		union2(Rectangle1, Rectangle2, &TemplateBottleRegion);
		get_domain(Image, &Domain);
		intersection(TemplateBottleRegion, Domain, &TemplateBottleRegion);
		area_center(TemplateBottleRegion, &Area, &RowBottleRef, &ColumnBottleRef);
		gen_circle(&SearchROIBottle, RowBottleRef, ColumnBottleRef, 40);
		reduce_domain(Image, TemplateBottleRegion, &ImageReduced);
		//
		//create shape model
		create_shape_model(ImageReduced, 5, -(HTuple(3).Rad()), HTuple(6).Rad(), 0, "auto", 
			"use_polarity", 25, 3, &ModelIDBottle);
		//
		//generate second model region and search ROI
		LabelRow1 = 180;
		LabelRow2 = 310;
		LabelColumn1 = 50;
		LabelColumn2 = 470;
		gen_rectangle1(&TemplateLabelRegion, LabelRow1, LabelColumn1, LabelRow2, LabelColumn2);
		area_center(TemplateLabelRegion, &Area1, &RowLabelRef, &ColumnLabelRef);
		gen_circle(&SearchROILabel, RowLabelRef, ColumnLabelRef, 60);
		reduce_domain(Image, TemplateLabelRegion, &ImageReduced);
		inspect_shape_model(ImageReduced, &ModelImages, &ModelRegions, 1, 25);
		//
		//create shape model
		create_shape_model(ImageReduced, 5, HTuple(-3).Rad(), HTuple(6).Rad(), 0, "auto", 
			"use_polarity", 25, 5, &ModelIDLabel1);
		create_shape_model(ImageReduced, 5, HTuple(180-3).Rad(), HTuple(6).Rad(), 0, "auto", 
			"use_polarity", 25, 5, &ModelIDLabel2);
		ModelIDsLabel.Reset();
		ModelIDsLabel.Append(ModelIDLabel1);
		ModelIDsLabel.Append(ModelIDLabel2);
		//
	}
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{
		bool isfail;
		isfail = false;
		set_font (pData->m_ShowHWindow, "-Courier New-14-*-*-*-*-1-");
		set_line_width(pData->m_ShowHWindow,3);

		//read_image(&Image, "blister/blister_"+(Index.ToString("02")));
		Image = pData->m_Image;
		WindowHandle = pData->m_ShowHWindow;

		disp_message(WindowHandle, "检查标签的位置", "window", -1, -1, "black", "true");
		//
		reduce_domain(Image, SearchROIBottle, &ImageReduced);
		find_shape_model(ImageReduced, ModelIDBottle, -(HTuple(3).Rad()), HTuple(6).Rad(), 
				0.7, 1, 0.5, "least_squares", 0, 0.9, &RowBottle, &ColumnBottle, &AngleBottle, 
				&ScoreBottle);
			//prepare search ROIs in search image
		concat_obj(SearchROILabel, SearchROILabel, &SearchROIs);
		add_channels(SearchROIs, Image, &GrayRegions);
			//
			//search shape models
		find_shape_models(GrayRegions, ModelIDsLabel, HTuple(HTuple(-3).Rad()).Concat(HTuple(180-3).Rad()), 
				HTuple(HTuple(6).Rad()).Concat(HTuple(6).Rad()), 0.6, 1, 1, "interpolation", 
				0, 0.9, &Row, &Column, &Angle, &Score, &FoundModel);

		if (0 != (HTuple((Score.Num())!=1).Or((ScoreBottle.Num())!=1)))
		{
			disp_message(WindowHandle, "末找到模板", "window", 40, -1, "red", "true");
			isfail=true;
		}
		else
		{
			if (0 != (HTuple(ModelIDsLabel[FoundModel])==ModelIDLabel2))
			{
				disp_message(WindowHandle, "标签极反180度", "window", 40, -1, "red", 
					"true");
				isfail=true;
			}
			else
			{
				//calculate y deviation
				Diffy = (RowBottle-Row)-(RowBottleRef-RowLabelRef);
				//calculate x deviation
				Diffx = (ColumnBottle-Column)-(ColumnBottleRef-ColumnLabelRef);
				//
				// check the rotation angle of the bottle label
				Diffa = (AngleBottle-Angle).Deg();
				//
				//calculate the time elapsed
				//
				//display results
				Color = "black";
				ModelColor = "forest green";
				if (0 != ((Diffx.Abs())>3))
				{
					Color.Append("red");
					ModelColor = "red";
					isfail=true;
				}
				else
				{
					Color.Append("forest green");
				}
				if (0 != ((Diffy.Abs())>1))
				{
					Color.Append("red");
					ModelColor = "red";
					isfail=true;
				}
				else
				{
					Color.Append("forest green");
				}
				if (0 != ((Diffa.Abs())>1))
				{
					Color.Append("red");
					ModelColor = "red";
					isfail=true;
				}
				else
				{
					Color.Append("forest green");
				}
				dev_display_shape_matching_results(ModelIDsLabel, HTuple("slate blue").Concat(ModelColor), 
					Row, Column, Angle, 1, 1, FoundModel,WindowHandle);
				disp_message(WindowHandle, (((("水平偏差     = "+(Diffx.ToString(" .2"))))).Concat("垂直偏差 = "+(Diffy.ToString(" .2")))).Concat("角度偏差 = "+(Diffa.ToString(" .2"))), 
					"window", 35, -1, Color, "true");
			}
			//

			// stop(); only in hdevelop


			if (isfail)
			{
				pData->m_isFail = true;
				testItem->m_bFailSubTest = true;
			}

		}
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		pData->m_center_x=350;
		pData->m_center_y=250;
		pData->r_real=100;
	}

}




