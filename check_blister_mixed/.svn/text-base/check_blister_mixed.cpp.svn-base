// check_blister_mixed.cpp : ¶¨Òå DLL Ó¦ÓÃ³ÌÐòµÄµ¼³öº¯Êý¡£
//

#include "stdafx.h"
#include "check_blister_mixed.h"


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

bool display_results (Halcon::Hobject ImageAffinTrans, Halcon::Hobject LeftOvers, 
					  Halcon::Hobject FinalClasses, Halcon::Hobject WrongPills, Halcon::HTuple CountFinalClass, 
					  Halcon::HTuple PillTypeCount, Halcon::HTuple WindowHandle)
{
	using namespace Halcon;

	// Local iconic variables 
	Hobject  RedLeftOvers, ObjectSelected;


	// Local control variables 
	HTuple  ThereWereErrors, Number;

	ThereWereErrors = 0;
	disp_obj(ImageAffinTrans, WindowHandle);
	set_draw(WindowHandle,"margin");
	set_line_width(WindowHandle,4);
	set_color(WindowHandle,"red");
	dilation_circle(LeftOvers, &RedLeftOvers, 2.5);
	disp_obj(RedLeftOvers, WindowHandle);
	//
	set_line_width(WindowHandle,3);
	select_obj(FinalClasses, &ObjectSelected, 1);
	set_color(WindowHandle,"goldenrod");
	disp_obj(ObjectSelected, WindowHandle);
	select_obj(FinalClasses, &ObjectSelected, 3);
	set_color(WindowHandle,"medium forest green");
	disp_obj(ObjectSelected, WindowHandle);
	select_obj(FinalClasses, &ObjectSelected, 2);
	set_color(WindowHandle,"firebrick");
	disp_obj(ObjectSelected, WindowHandle);
	//
	if (0 != (HTuple(CountFinalClass[0])!=HTuple(PillTypeCount[0])))
	{
		disp_message(WindowHandle, "# \"»ÆÉ«\"½ºÄÒ :", "window", 10, 10, "black", 
			"true");
		disp_message(WindowHandle, HTuple(CountFinalClass[0]), "window", 10, 10+150, 
			"red", "true");
		ThereWereErrors = 1;
	}
	else
	{
		disp_message(WindowHandle, "# \"»ÆÉ«\"½ºÄÒ :"+HTuple(CountFinalClass[0]), 
			"window", 10, 10, "black", "true");
	}
	//
	if (0 != (HTuple(CountFinalClass[2])!=HTuple(PillTypeCount[2])))
	{
		disp_message(WindowHandle, "# \"ÂÌÉ«\"½ºÄÒ :", "window", 10+20, 10, "black", 
			"true");
		disp_message(WindowHandle, HTuple(CountFinalClass[2]), "window", 10+20, 10+150, 
			"red", "true");
		ThereWereErrors = 1;
	}
	else
	{
		disp_message(WindowHandle, "# \"ÂÌÉ«\"½ºÄÒ :"+HTuple(CountFinalClass[2]), 
			"window", 10+20, 10, "black", "true");
	}
	//
	//
	if (0 != (HTuple(CountFinalClass[1])!=HTuple(PillTypeCount[1])))
	{
		disp_message(WindowHandle, "# \"ºìÉ«\"½ºÄÒ :", "window", 10+40, 10, "black", 
			"true");
		disp_message(WindowHandle, HTuple(CountFinalClass[1]), "window", 10+40, 10+150, 
			"red", "true");
		ThereWereErrors = 1;
	}
	else
	{
		disp_message(WindowHandle, "# \"ºìÉ«\"½ºÄÒ :"+HTuple(CountFinalClass[1]), 
			"window", 10+40, 10, "black", "true");
	}
	//
	count_obj(WrongPills, &Number);
	if (0 != (Number>0))
	{
		disp_message(WindowHandle, "# ´íÎó½ºÄÒ :"+Number, "window", 10+60, 
			10, "red", "true");
		ThereWereErrors = 1;
	}
	if (0 != ThereWereErrors)
	{
		disp_message(WindowHandle, "Not OK", "window", 10, 600, "red", "true");
		return true;
	}
	else
	{
		disp_message(WindowHandle, "OK", "window", 10, 600, "forest green", "true");
		return false;
	}


}

// Local procedures 
void extract_pill_types (Halcon::Hobject Image, Halcon::Hobject *Chambers, Halcon::Hobject *ChambersUnion, 
						 Halcon::Hobject *Classes, Halcon::HTuple *PhiRef, Halcon::HTuple *RowRef, Halcon::HTuple *ColumnRef, 
						 Halcon::HTuple *PillTypeCount)
{
	using namespace Halcon;

	// Local iconic variables 
	Hobject  Region, ConnectedRegions, SelectedRegions;
	Hobject  Blister, Rectangle, Pattern, PillType1, PillType2;
	Hobject  PillType3, ImageReduced, ImageR, ImageG, ImageB;
	Hobject  ImageInvert, RegionHysteresis2, RegionHysteresis3;


	// Local control variables 
	HTuple  I, Row, J, Column, Area;

	threshold(Image, &Region, 90, 255);
	connection(Region, &ConnectedRegions);
	select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 5000, 999999);
	shape_trans(SelectedRegions, &Blister, "convex");
	gen_empty_region(&(*Chambers));
	for (I=0; I<=4; I+=1)
	{
		Row = 107+(I*70);
		for (J=0; J<=2; J+=1)
		{
			Column = 177+(J*150);
			gen_rectangle2(&Rectangle, Row, Column, 0, 64, 30);
			concat_obj((*Chambers), Rectangle, &(*Chambers));
		}
	}
	difference(Blister, (*Chambers), &Pattern);
	union1((*Chambers), &(*ChambersUnion));
	orientation_region(Blister, &(*PhiRef));
	(*PhiRef) = (HTuple(180).Rad())+(*PhiRef);
	area_center(Blister, &Area, &(*RowRef), &(*ColumnRef));
	//
	//
	// +++ extract pattern for classification +++
	select_shape((*Chambers), &PillType1, "row", "and", 1, 145);
	union1(PillType1, &PillType1);
	select_shape((*Chambers), &PillType2, "row", "and", 145, 270);
	union1(PillType2, &PillType2);
	select_shape((*Chambers), &PillType3, "row", "and", 270, 390);
	union1(PillType3, &PillType3);
	//
	//
	//extract color space of yellow pills
	reduce_domain(Image, PillType1, &ImageReduced);
	decompose3(ImageReduced, &ImageR, &ImageG, &ImageB);
	threshold(ImageB, &Region, 60, 95);
	//
	//extract color space of red pills
	reduce_domain(Image, PillType2, &ImageReduced);
	decompose3(ImageReduced, &ImageR, &ImageG, &ImageB);
	invert_image(ImageB, &ImageInvert);
	hysteresis_threshold(ImageInvert, &RegionHysteresis2, 190, 200, 5);
	//
	//extract color space of green pills
	reduce_domain(Image, PillType3, &ImageReduced);
	decompose3(ImageReduced, &ImageR, &ImageG, &ImageB);
	invert_image(ImageB, &ImageInvert);
	hysteresis_threshold(ImageInvert, &RegionHysteresis3, 180, 200, 10);
	//
	intersection(Region, PillType1, &PillType1);
	intersection(RegionHysteresis2, PillType2, &PillType2);
	(*PillTypeCount).Reset();
	(*PillTypeCount)[0] = 3;
	(*PillTypeCount)[1] = 6;
	(*PillTypeCount)[2] = 6;
	intersection(RegionHysteresis3, PillType3, &PillType3);
	concat_obj(PillType1, PillType2, &(*Classes));
	concat_obj((*Classes), PillType3, &(*Classes));
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
	//clear_class_gmm(GMMHandle);
}


void CDoProcess::SetParmeter(string parm,string value)
{
	if (parm == "TransImage")
	{
		read_image(&Image, "blister/blister_mixed_reference");

		extract_pill_types(Image, &Chambers, &ChambersUnion, &Classes, &PhiRef, &RowRef, 
			&ColumnRef, &PillTypeCount);
		NumClasses = PillTypeCount.Num();
		create_class_gmm(3, 3, (HTuple(1).Append(5)), "spherical", "normalization", 10, 
			42, &GMMHandle);
		add_samples_image_class_gmm(Image, Classes, GMMHandle, 0);
		train_class_gmm(GMMHandle, 100, 0.001, "training", 0.0001, &Centers, &Iter);		
	}



}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{
		set_font (pData->m_ShowHWindow, "-Courier New-14-*-*-*-*-1-");
		set_line_width(pData->m_ShowHWindow,3);

		//read_image(&Image, "blister/blister_"+(Index.ToString("02")));
		Image = pData->m_Image;
		
		
		threshold(Image, &Region, 90, 255);
		connection(Region, &ConnectedRegions);
		select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 5000, 9999999);
		shape_trans(SelectedRegions, &RegionTrans, "convex");
		orientation_region(RegionTrans, &Phi);
		if (0 != ((Phi.Abs())>(HTuple(90).Rad())))
		{
			Phi = (HTuple(180).Rad())+Phi;
		}
		area_center(RegionTrans, &Area1, &Row, &Column);
		vector_angle_to_rigid(Row, Column, Phi, RowRef, ColumnRef, PhiRef, &HomMat2D);
		affine_trans_image(Image, &ImageAffinTrans, HomMat2D, "constant", "false");
		reduce_domain(ImageAffinTrans, ChambersUnion, &ImageReduced);
		decompose3(ImageAffinTrans, &ImageR, &ImageG, &ImageB);
		//
		//classify pill type for each chamber
		classify_image_class_gmm(ImageReduced, &ClassRegions, GMMHandle, 0.005);
		//
		count_obj(ClassRegions, &Number);
		gen_empty_obj(&FinalClasses);
		connection(Chambers, &ChambersRemaining);
		for (Index=Number; Index>=1; Index+=-1)
		{
			select_obj(ClassRegions, &Region, Index);
			intersection(ChambersRemaining, Region, &Region);
			select_shape(Region, &PillsOfOneType, (HTuple("area").Append("width")), "and", 
				(HTuple(200).Append(40)), (HTuple(3000).Append(68)));
			difference(ChambersUnion, PillsOfOneType, &RegionDifference);
			connection(RegionDifference, &ConnectedRegions);
			select_shape(ConnectedRegions, &SelectedRegions, "area", "and", 0, 7868);
			shape_trans(SelectedRegions, &SelectedRegions, "convex");
			union1(SelectedRegions, &SelectedRegions);
			difference(ChambersRemaining, SelectedRegions, &ChambersRemaining);
			concat_obj(SelectedRegions, FinalClasses, &FinalClasses);
		}
		//
		//
		//check for right combination
		gen_empty_obj(&MissingPills);
		gen_empty_obj(&WrongPills);
		gen_empty_obj(&WrongNumberOfPills);
		difference(ChambersUnion, FinalClasses, &LeftOvers);
		area_center(LeftOvers, &Area, &Row1, &Column1);
		if (0 != (Area>0))
		{
			connection(LeftOvers, &LeftOvers);
			count_obj(LeftOvers, &Number);
			for (Index=1; Index<=Number; Index+=1)
			{
				select_obj(LeftOvers, &ObjectSelected, Index);
				intensity(ObjectSelected, ImageB, &Mean, &Deviation);
				if (0 != (Deviation>40))
				{
					concat_obj(WrongPills, ObjectSelected, &WrongPills);
				}
				else
				{
					concat_obj(MissingPills, ObjectSelected, &MissingPills);
				}
			}
		}
		//
		//compute histogram
		CountFinalClass = HTuple();
		for (Index=1; Index<=NumClasses; Index+=1)
		{
			select_obj(FinalClasses, &ObjectSelected, Index);
			connection(ObjectSelected, &ObjectSelected);
			count_obj(ObjectSelected, &Size);
			CountFinalClass.Append(Size);
		}
		//
		//display classification results and output allover statistic
		bool isfail = display_results(ImageAffinTrans, LeftOvers, FinalClasses, WrongPills, CountFinalClass, 
			PillTypeCount, pData->m_ShowHWindow);

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
	}

}




