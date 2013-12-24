// bottle.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include "bottle.h"

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

		SmoothX = 501;
		ThresholdOffset = 25;
		MinDefectSize = 50;
		//
		//initialization
		PolarResolution = 640;
		RingSize = 70;
		
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

		//
		//Part 1: Use basic morphology to detect bottle
		auto_threshold(Image, &Regions, 2);
		select_obj(Regions, &DarkRegion, 1);
		opening_circle(DarkRegion, &RegionOpening, 3.5);
		closing_circle(RegionOpening, &RegionClosing, 25.5);
		fill_up(RegionClosing, &RegionFillUp);
		boundary(RegionFillUp, &RegionBorder, "outer");
		dilation_circle(RegionBorder, &RegionDilation, 3.5);
		reduce_domain(Image, RegionDilation, &ImageReduced);
		//
		//Find the bottle center by fitting a circle to extracted edges
		edges_sub_pix(ImageReduced, &Edges, "canny", 0.5, 20, 40);
		segment_contours_xld(Edges, &ContoursSplit, "lines_circles", 5, 4, 2);
		union_cocircular_contours_xld(ContoursSplit, &UnionContours, 0.9, 0.5, 0.5, 200,50, 50, "true", 1);
		length_xld(UnionContours, &Length);
		select_obj(UnionContours, &LongestContour, HTuple((Length.SortIndex())[(Length.Num())-1])+1);
		fit_circle_contour_xld(LongestContour, "ahuber", -1, 0, 0, 3, 2, &Row, &Column, 
			&Radius, &StartPhi, &EndPhi, &PointOrder);
		//
		//Part 2: Transform the ring-shaped bottle neck region to a rectangle
		gen_circle(&Circle, Row, Column, Radius);
		dilation_circle(Circle, &RegionDilation, 5);
		erosion_circle(Circle, &RegionErosion, RingSize-5);
		difference(RegionDilation, RegionErosion, &RegionDifference);
		reduce_domain(Image, RegionDifference, &ImageReduced);
		polar_trans_image(ImageReduced, &ImagePolar, Row, Column, PolarResolution, Radius+5);
		//
		//Part 3: Find defects with a dynamic threshold
		//Note the strong smoothing in x-direction in the transformed image.
		crop_part(ImagePolar, &ImagePart, Radius-RingSize, 0, PolarResolution, RingSize);
		scale_image_max(ImagePart, &ImageScaleMax);
		mean_image(ImageScaleMax, &ImageMean, SmoothX, 3);
		dyn_threshold(ImageScaleMax, ImageMean, &Regions1, 50, "not_equal");
		connection(Regions1, &Connection);
		select_shape(Connection, &SelectedRegions, "height", "and", 9, 99999);
		//ignore noise regions
		closing_rectangle1(SelectedRegions, &RegionClosing1, 10, 20);
		union1(RegionClosing1, &RegionUnion);
		//re-transform defect regions for visualization
		polar_trans_region_inv(RegionUnion, &XYTransRegion, Row, Column, 6.28319, 0, 
			Radius-RingSize, Radius, 640, RingSize, 1280, 1024, "nearest_neighbor");
			//
			//Part 4: Display results
			//display original image with results
		disp_obj(RegionDifference, WindowHandle);
		set_color(WindowHandle,"red");
		disp_obj(XYTransRegion, WindowHandle);
		//display polar transformed inspected region with results
		//The image and resulting region are rotated by 90 degrees
		//only for visualization purposes! (I.e. to fit better on the screen)
		//The rotation is NOT necessary for the detection algorithm.
// 		rotate_image(ImagePart, &ImageRotate, 90, "constant");
// 		disp_obj(ImageRotate, WindowHandle);
		count_obj(RegionUnion, &Number);
		if (0 != (Number>0))
		{
			mirror_region(RegionUnion, &RegionMirror, "diagonal", PolarResolution);
			mirror_region(RegionMirror, &RegionMirror, "row", PolarResolution);
			//disp_obj(RegionMirror, WindowHandle);
			disp_message(WindowHandle, "Not OK", "window", -1, -1, "red", "false");
			isfail=true;
		}
		else
		{
			isfail=false;
			disp_message(WindowHandle, "OK", "window", -1, -1, "forest green", "false");
		}
		//Reset system parameters

		if (isfail)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
		}

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







