// CanBodyLocation01v1.0.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CanBodyLocation01v1.0.h"

using namespace std;
using namespace Halcon;

#ifndef DLLEXPT
#define DLLEXPT __declspec (dllexport)
#endif
#define LinesPerFrame 900
#define MAXGRAY 255
#define MINGRAY 0

#define EPS 0.1
#define DELTA 0.001
CDoProcess::CDoProcess():
Row1(450), 
Row2(900),
Row3(1350),
Len1(256),
Len2(128)
{
	ShowObject = false;
	printf("CanBodyLocation01v1.0 Function\r\n");
}

void CDoProcess::SetParmeter(string parm, string value)
{
	if(parm=="SHOWOBJECT")
	{	if (value=="YES")
			ShowObject = true;
		else
			ShowObject = false;
	}

	if ("Col1"== parm)
		m_Parameters.Col1 = atoi(value.c_str());	
	if ("Col2"== parm)
		m_Parameters.Col2 = atoi(value.c_str());	
	if ("Col3"== parm)
		m_Parameters.Col3 = atoi(value.c_str());
	if ("Col4"== parm)
		m_Parameters.Col4 = atoi(value.c_str());
	if ("Col5"== parm)
		m_Parameters.Col5 = atoi(value.c_str());

}

void CDoProcess::GenLocationBlock(Hobject& locationBlock, int row, int col, int len1, int len2, CMData* pData)
{
	gen_rectangle2(&locationBlock, row, col, 0, len1, len2); 
	if(pData->m_isDebug && ShowObject)
		disp_obj(locationBlock,pData->m_ShowHWindow);
}

void CDoProcess::ComputeWeldingLineCenter(Hobject& Image, Hobject& Region, double& row, double& col, double& phi)
{
	Hobject ImageReduced;
	reduce_domain(Image, Region, &ImageReduced);

	HTuple Mean, Deviation;
	intensity(Region, ImageReduced, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	Hobject ThreshedRegion;
	fast_threshold(ImageReduced, &ThreshedRegion, Thresh, 255, 10);

	Hobject ConnRegion;
	connection(ThreshedRegion, &ConnRegion);

	HTuple Area, Row, Col;
	area_center(ConnRegion, &Area, &Row, &Col);

	HTuple MaxSize;
	tuple_max(Area, &MaxSize);

	Hobject SelectRegion;
	select_shape(ConnRegion, &SelectRegion, "area", "and", MaxSize - 0.5, MaxSize + 0.5);

	HTuple Phi, Len1, Len2;
	smallest_rectangle2(SelectRegion, &Row, &Col, &Phi, &Len1, &Len2);

	row  = Row[0].D();
	col  = Col[0].D();
	phi  = Phi[0].D();
}

bool CDoProcess::ComputeCanBody(Hobject& image, Hobject& locationCan, double& len1, double& len2, Hobject& canBody)
{
	Hobject ImageCan1;
	reduce_domain(image, locationCan, &ImageCan1);

	HTuple Mean, Deviation;
	intensity(locationCan, ImageCan1, &Mean, &Deviation);
	
	HTuple Thresh = Mean + Deviation;
	if(Thresh > MAXGRAY)
		Thresh = Mean;
	Hobject Can1Region;
	fast_threshold(ImageCan1, &Can1Region, 0, Thresh, 20);

	Hobject Can1Connected;
	connection(Can1Region, &Can1Connected);

	HTuple Area, Row, Col;
	area_center(Can1Connected, &Area, &Row, &Col);

	HTuple MaxSize;
	tuple_max(Area, &MaxSize);

	Hobject objSelect;
	select_shape(Can1Connected, &objSelect, "area", "and",  MaxSize - 0.5, MaxSize + 0.5);

	Hobject objFill;
	fill_up(objSelect, &objFill);

	HTuple tmprow, tmpcol, tmpphi, tmplen1, tmplen2;
	smallest_rectangle2(objFill, &tmprow, &tmpcol, &tmpphi, &tmplen1, &tmplen2);

	gen_rectangle2(&canBody, tmprow, tmpcol, tmpphi, tmplen1, tmplen2);
	HTuple Num;
	count_obj(canBody, &Num);
	if(Num>0)
		return true;
	else
		return false;
}

void CDoProcess::ComputeHorizonSeam(Hobject& image, Hobject& canbody, Hobject& upperHorizonSeam, Hobject& lowerHorizonSeam, CMData* pData)
{
	HTuple row, col, phi, len1, len2;
	smallest_rectangle2(canbody, &row, &col, &phi, &len1, &len2);

	Hobject rectangleSmall, rectangleBig;
	gen_rectangle2(&rectangleSmall, row, col, phi, len1 - 30, len2 - 5);
	gen_rectangle2(&rectangleBig,   row, col, phi, len1 - 30, len2 + 30);

	Hobject rectangleDiff;
	difference(rectangleBig, rectangleSmall, &rectangleDiff);

	Hobject rectangleConn;
	connection(rectangleDiff, &rectangleConn);

	HTuple Area, Row, Col;
	area_center(rectangleConn, &Area, &Row, &Col);

	HTuple Min, Max;
	tuple_min(Row, &Min);
	tuple_max(Row, &Max);

	Hobject RectangleUpper, RectangleLower;
	select_shape(rectangleConn, &RectangleUpper, "row", "and", Min - 0.5, Min + 0.5);
	select_shape(rectangleConn, &RectangleLower, "row", "and", Max - 0.5, Max + 0.5);
	
	HTuple n1, n2;
	count_obj(RectangleUpper, &n1);
	count_obj(RectangleLower, &n2);
	Hobject ImageUpper;
	reduce_domain(image, RectangleUpper, &ImageUpper);

	HTuple Mean, Deviation;
	intensity(RectangleUpper, ImageUpper, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	fast_threshold(ImageUpper, &upperHorizonSeam, Thresh, MAXGRAY, 10);

	Hobject ImageLower;
	reduce_domain(image, RectangleLower, &ImageLower);

	intensity(RectangleLower, ImageLower, &Mean, &Deviation);
	Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	fast_threshold(ImageLower, &lowerHorizonSeam, Thresh, MAXGRAY, 10);
}

void CDoProcess::LocationFramePostion(Hobject& image, Hobject& locationBlockUp, Hobject& locationBlockDown, double& weldingLineRow, double& weldingLineRow1, bool& isFirstFrame, bool& isLastFrame,  CMData* pData)
{
	HTuple Row, Col, Phi, Len1, Len2;
	smallest_rectangle2(locationBlockUp, &Row, &Col, &Phi, &Len1, &Len2);

	double NewRow  = (Row[0].D() - Len2[0].D() + weldingLineRow)/ 2;
	double NewLen2 = (weldingLineRow - (Row[0].D() - Len2[0].D()))/ 2;

	Hobject NewBlock;
	gen_rectangle2(&NewBlock, NewRow, Col[0].D(), Phi[0].D(), Len1[0].D(), NewLen2 - 30);

	Hobject ReducedImage;
	reduce_domain(image, NewBlock, &ReducedImage);

	HTuple Mean, Deviation;
	intensity(NewBlock, ReducedImage, &Mean, &Deviation);

	if(Mean < 20)
		isFirstFrame = true;
	else 
		isFirstFrame = false;

	smallest_rectangle2(locationBlockDown, &Row, &Col, &Phi, &Len1, &Len2);
	NewRow  = (Row[0].D() + Len2[0].D() + weldingLineRow1)/ 2;
	NewLen2 = ((Row[0].D() + Len2[0].D())- weldingLineRow1)/ 2;

	Hobject NewBlock1;
	gen_rectangle2(&NewBlock1, NewRow, Col[0].D(), Phi[0].D(), Len1[0].D(), NewLen2 - 30);

	reduce_domain(image, NewBlock1, &ReducedImage);
	intensity(NewBlock1, ReducedImage, &Mean, &Deviation);

	if(Mean < 20)
		isLastFrame = true;
	else 
		isLastFrame = false;
}

void CDoProcess::ComputeVerticalSeam(Hobject& image, Hobject& canbody, Hobject& leftVerticalSeam, Hobject& rightVerticalSeam, CMData* pData)
{
	HTuple row, col, phi, len1, len2;
	smallest_rectangle2(canbody, &row, &col, &phi, &len1, &len2);

	Hobject rectangleSmall, rectangleBig;
	gen_rectangle2(&rectangleSmall, row, col, phi, len1 - 20, len2 - 20);
	gen_rectangle2(&rectangleBig,   row, col, phi, len1 + 60, len2 - 30);
	
	Hobject rectangleDiff;
	difference(rectangleBig, rectangleSmall, &rectangleDiff);
	
	Hobject rectangleConn;
	connection(rectangleDiff, &rectangleConn);

	HTuple Area, Row, Col;
	area_center(rectangleConn, &Area, &Row, &Col);

	HTuple Min, Max;
	tuple_min(Col, &Min);
	tuple_max(Col, &Max);

	Hobject RectangleLeft, RectangleRight;
	select_shape(rectangleConn, &RectangleLeft,  "column", "and", Min - 0.5, Min + 0.5);
	select_shape(rectangleConn, &RectangleRight, "column", "and", Max - 0.5, Max + 0.5);

	Hobject ImageLeft;
	reduce_domain(image, RectangleLeft, &ImageLeft);

	HTuple Mean, Deviation;
	intensity(RectangleLeft, ImageLeft, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY) Thresh = Mean;
		
	fast_threshold(ImageLeft, &leftVerticalSeam, Thresh, MAXGRAY, 10);

	Hobject ImageRight;
	reduce_domain(image, RectangleRight, &ImageRight);

	intensity(RectangleRight, ImageRight, &Mean, &Deviation);
	Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY) Thresh = Mean;
		
	fast_threshold(ImageRight, &rightVerticalSeam, Thresh, MAXGRAY, 10);
}

static void ComputeSeam(Hobject& image, Hobject& srcBlock, Hobject& dstBlock, Hlong& handle)
{
	HTuple row, col, phi, len1, len2;
	smallest_rectangle2(srcBlock, &row, &col, &phi, &len1, &len2);
	
	HTuple absPhi;
	tuple_abs(phi, &absPhi);
	HTuple len;
	if(absPhi < 0.1)
		len = len2;
	else 
		len = len1;
	Hobject ImageReduced;
	reduce_domain(image, srcBlock, &ImageReduced);

	Hobject Edges;
	edges_sub_pix(ImageReduced, &Edges, "canny", 1, 20, 40);
	
	Hobject ContoursSplit;
	segment_contours_xld(Edges, &ContoursSplit, "lines_circles", 5, 4, 2);
	
	Hobject SelectedContours;
	select_contours_xld(ContoursSplit, &SelectedContours, "direction", 1.4, 1.75, -0.5, 0.5);

	Hobject SelectedContours1;
	select_contours_xld(SelectedContours, &SelectedContours1, "contour_length", len*2 - 10, len*2 + 10, -0.5, 0.5);

	HTuple NumLines;
	count_obj(SelectedContours1, &NumLines);
	if(NumLines == 2)
	{
		Hobject ObjectSelected;
		select_obj(SelectedContours1, &ObjectSelected, 1);

		HTuple RowBegin, ColBegin, RowEnd, ColEnd, Nr, Nc, Dist;
        fit_line_contour_xld(ObjectSelected, "tukey", -1, 0, 5, 2, &RowBegin, &ColBegin, &RowEnd, &ColEnd, &Nr, &Nc, &Dist);
		
		HTuple temp = HTuple();
		temp.Reset();
		if(RowBegin > RowEnd)
		{
			temp     = RowBegin;
			RowBegin = RowEnd;
			RowEnd   = temp;

			temp     = ColBegin;
			ColBegin = ColEnd;
			ColEnd   = temp;
		}

		Hobject ObjectSelected1;
        select_obj(SelectedContours1, &ObjectSelected1, 2);

		HTuple RowBegin1, ColBegin1, RowEnd1, ColEnd1, Nr1, Nc1, Dist1;
        fit_line_contour_xld(ObjectSelected1, "tukey", -1, 0, 5, 2, &RowBegin1, &ColBegin1, &RowEnd1, &ColEnd1, &Nr1, &Nc1, &Dist1);
		temp.Reset();
		if(RowBegin1 > RowEnd1)
		{
			temp      = RowBegin1;
			RowBegin1 = RowEnd1;
			RowEnd1   = temp;

			temp      = ColBegin1;
			ColBegin1 = ColEnd1;
			ColEnd1   = temp;
		}

		HTuple fRow = HTuple();
        fRow.Reset();
        fRow.Append(RowBegin);
        fRow.Append(RowEnd);
        fRow.Append(RowEnd1);
        fRow.Append(RowBegin1);
        
		HTuple fCol = HTuple();
        fCol.Reset();
        fCol.Append(ColBegin);
        fCol.Append(ColEnd);
        fCol.Append(ColEnd1);
        fCol.Append(ColBegin1);

        gen_region_polygon_filled(&dstBlock, fRow, fCol);
	}
	else if (NumLines == 1)
	{
		HTuple Row, Column, Phi, Length1,  Length2;
		smallest_rectangle2_xld(SelectedContours1, &Row, &Column, &Phi, &Length1,  &Length2);

		HTuple absPhi;
		tuple_abs(Phi, &absPhi);
		Hobject RectangleSmall, RectangleBig;
		if(absPhi < 0.1)
		{
			gen_rectangle2(&RectangleSmall, Row, Column, Phi, Length1, Length2 + 10);
			gen_rectangle2(&RectangleBig,   Row, Column, Phi, Length1 + 45, Length2);
		}
		else
		{
			gen_rectangle2(&RectangleSmall, Row, Column, Phi, Length1 + 10, Length2);
			gen_rectangle2(&RectangleBig,   Row, Column, Phi, Length1, Length2 + 45);
		}
		
		Hobject RegionDifference;
        difference(RectangleBig, RectangleSmall, &RegionDifference);

		Hobject ConnectedRegions;
        connection(RegionDifference, &ConnectedRegions);

		Hobject ImageConnReduced;
        reduce_domain(ImageReduced, ConnectedRegions, &ImageConnReduced);

		HTuple Mean, Deviation;
        intensity(ConnectedRegions, ImageConnReduced, &Mean, &Deviation);

		HTuple Length;
        tuple_length(Mean, &Length);
		
		HTuple Sorted;
        tuple_sort(Mean, &Sorted);

		HTuple Indices;
        tuple_sort_index(Mean, &Indices);
       
		Hobject ObjectSelected;
        select_obj(ConnectedRegions, &ObjectSelected, HTuple(Indices[Length-1])+1);

		Hobject ImageReducedObjSelected;
        reduce_domain(image, ObjectSelected, &ImageReducedObjSelected);
        intensity(ObjectSelected, ImageReducedObjSelected, &Mean, &Deviation);

        HTuple Thresh = Mean + Deviation;
        if (0 != (Thresh>=255)) Thresh = Mean;
          
		Hobject SelectedRegion;
        fast_threshold(ImageReducedObjSelected, &SelectedRegion, Thresh, 255, 10);
        smallest_rectangle2(SelectedRegion, &Row, &Column, &Phi, &Length1, &Length2);

        gen_rectangle2(&dstBlock, Row, Column, Phi, Length1, Length2);
	}
	else 
	{
		HTuple Mean, Deviation;
		intensity(srcBlock, ImageReduced, &Mean, &Deviation);

        HTuple Thresh = Mean + Deviation;
		if(Thresh >= 255) Thresh = Mean;

		Hobject RegionReduced;
        fast_threshold(ImageReduced, &RegionReduced, Thresh, 255, 10);

		Hobject ConnectedRegions;
        connection(RegionReduced, &ConnectedRegions);

		HTuple Area, Row, Column;
        area_center(ConnectedRegions, &Area, &Row, &Column);

		HTuple MaxSize;
        tuple_max(Area, &MaxSize);

		Hobject SelectedRegions;
        select_shape(ConnectedRegions, &SelectedRegions, "area", "and", MaxSize-0.5, MaxSize+0.5);
        smallest_rectangle2(SelectedRegions, &row, &col, &phi, &len1, &len2);

        gen_rectangle2(&dstBlock, row, col, phi, len1, len2);
	}
}

void CDoProcess::ComputeVerticalSeamV2(Hobject& image, Hobject& canbody, Hobject& leftVerticalSeam, Hobject& rightVerticalSeam, Hlong& wHandle)
{
	HTuple row, col, phi, len1, len2;
	smallest_rectangle2(canbody, &row, &col, &phi, &len1, &len2);

	Hobject rectangleSmall, rectangleBig;
	gen_rectangle2(&rectangleSmall, row, col, phi, len1 - 20, len2 - 20);
	gen_rectangle2(&rectangleBig,   row, col, phi, len1 + 60, len2 - 30);
	
	Hobject rectangleDiff;
	difference(rectangleBig, rectangleSmall, &rectangleDiff);
	
	Hobject rectangleConn;
	connection(rectangleDiff, &rectangleConn);

	HTuple Area, Row, Col;
	area_center(rectangleConn, &Area, &Row, &Col);

	HTuple Min, Max;
	tuple_min(Col, &Min);
	tuple_max(Col, &Max);

	Hobject RectangleLeft, RectangleRight;
	select_shape(rectangleConn, &RectangleLeft,  "column", "and", Min - 0.5, Min + 0.5);
	select_shape(rectangleConn, &RectangleRight, "column", "and", Max - 0.5, Max + 0.5);

	ComputeSeam(image, RectangleLeft, leftVerticalSeam, wHandle);
	ComputeSeam(image, RectangleRight, rightVerticalSeam, wHandle);

}

bool CDoProcess::GetCanBody(Hobject& srcCanBody, Hobject& dstCanBody)
{
	HTuple Num;
	count_obj(srcCanBody, &Num);
	if(Num == 0)
		return false;
	else
		copy_obj(srcCanBody, &dstCanBody, 1, Num);

	return true;
}

void CDoProcess::GetVerticalSeam(Hobject& verticalSeam,  HTuple& row, HTuple& col, HTuple& phi, HTuple& len1, HTuple& len2)
{
	HTuple Row, Col, Phi, Len1, Len2;
	smallest_rectangle2(verticalSeam, &Row, &Col, &Phi, &Len1, &Len2);

	row  = Row;
	col  = Col;
	phi  = Phi;
	len1 = Len1;
	len2 = Len2;
}

static void ReviseVerticalPhi(Hobject& image, double& srcRow, double& srcCol, double& srcPhi, double& dstPhi, Hlong& handle, bool& isDebug)
{
	Hobject testBlock;
	gen_rectangle2(&testBlock, srcRow, srcCol, srcPhi, 200, 60);
	if(isDebug )
		disp_obj(testBlock, handle);

	Hobject imageReduced;
	reduce_domain(image, testBlock, &imageReduced);

	HTuple Mean, Deviation;
	intensity(testBlock, imageReduced, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	Hobject ThreshedRegion;
	fast_threshold(imageReduced, &ThreshedRegion, Thresh, 255, 10);

	Hobject connRegion;
	connection(ThreshedRegion, &connRegion);

	HTuple area, row, col;
	area_center(connRegion, &area, &row, &col);

	HTuple maxSize;
	tuple_max(area, &maxSize);

	Hobject selectObj;
	select_shape(connRegion, &selectObj, "area", "and", maxSize -0.5, maxSize +0.5);

	HTuple phi, len1, len2;
	smallest_rectangle2(selectObj, &row, &col, &phi, &len1, &len2);

	dstPhi = phi[0].D();

}

static void ComputeCanBodyPhi(Hobject& image, Hobject& locationCan, HTuple& Phi)
{
	Hobject ImageCan1;
	reduce_domain(image, locationCan, &ImageCan1);

	Hobject Can1Region;
	bin_threshold(ImageCan1, &Can1Region);

	Hobject Can1Connected;
	connection(Can1Region, &Can1Connected);

	HTuple Area, Row, Col;
	area_center(Can1Connected, &Area, &Row, &Col);

	HTuple MaxSize;
	tuple_max(Area, &MaxSize);

	Hobject objSelect;
	select_shape(Can1Connected, &objSelect, "area", "and",  MaxSize - 0.5, MaxSize + 0.5);

	Hobject objFill;
	fill_up(objSelect, &objFill);

	HTuple tmprow, tmpcol, tmpphi, tmplen1, tmplen2;
	smallest_rectangle2(objFill, &tmprow, &tmpcol, &Phi, &tmplen1, &tmplen2);

}

static void ReviseCanBody(Hobject& image, Hobject& srcCanBody, double& srcRow, double& srcCol, double& srcLen1, double& srcLen2, Hobject& dstCanBody)
{
	HTuple row, col, phi, len1, len2;
	smallest_rectangle2(srcCanBody, &row, &col, &phi, &len1, &len2);

	gen_rectangle2(&dstCanBody, srcRow, srcCol, phi[0].D(), srcLen1- 20, srcLen2 - 20);
}

static void ComputeWeldingLineInfo(Hobject& Image, Hobject& Region, double& row, double& col, double& phi, double& len1, double& len2)
{
	Hobject ImageReduced;
	reduce_domain(Image, Region, &ImageReduced);

	HTuple Mean, Deviation;
	intensity(Region, ImageReduced, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	Hobject ThreshedRegion;
	fast_threshold(ImageReduced, &ThreshedRegion, Thresh, 255, 10);

	Hobject ConnRegion;
	connection(ThreshedRegion, &ConnRegion);

	HTuple Area, Row, Col;
	area_center(ConnRegion, &Area, &Row, &Col);

	HTuple MaxSize;
	tuple_max(Area, &MaxSize);

	Hobject SelectRegion;
	select_shape(ConnRegion, &SelectRegion, "area", "and", MaxSize - 0.5, MaxSize + 0.5);

	smallest_rectangle2(SelectRegion, &row, &col, &phi, &len1, &len2);
}

static void ComputeCanBodyV2(Hobject& image, Hobject& Block, HTuple& phi)
{
	Hobject ReducedImage;
	reduce_domain(image, Block, &ReducedImage);

	HTuple Mean, Deviation;
	intensity(Block, ReducedImage, &Mean, &Deviation);

	Hobject fastRegion;
	fast_threshold(ReducedImage, &fastRegion, 0, Mean + Deviation, 10);
	
	Hobject connRegion;
	connection(fastRegion, &connRegion);

	HTuple Area, Row, Col;
	area_center(connRegion, &Area, &Row, &Col);

	HTuple MaxSize;
	tuple_max(Area, &MaxSize);

	Hobject selectRegion;
	select_shape(connRegion, &selectRegion, "area", "and", MaxSize -0.5, MaxSize +0.5);

	Hobject fillRegion;
	fill_up(selectRegion, &fillRegion);

	HTuple Len1, Len2;
	smallest_rectangle2(fillRegion, &Row, &Col, &phi, &Len1, &Len2);
}

void CDoProcess::DoProcess(CMData* pData, SubTestResult *testItem)
{	
	try
	{
		Hobject Image = pData->m_Image;

		HTuple Width, Height;
		get_image_size(Image, &Width, &Height);  
		set_color(pData->m_ShowHWindow,"blue");
		
		bool isTwoCan = !(Width[0].D() < DefaultWidth);

		///// STEP1 location block
		GenLocationBlock(Rect01, Row2, m_Parameters.Col1, Len1 + 150, Len2, pData); // 1
		GenLocationBlock(Rect07, Row2, m_Parameters.Col3, Len1 + 150, Len2, pData); // 3
		GenLocationBlock(Rect02, Row1, m_Parameters.Col2, Len2, Len1 + 100, pData); // 2
		GenLocationBlock(Rect06, Row3, m_Parameters.Col2, Len2, Len1 + 100, pData); // 2

		if(isTwoCan)
		{
			GenLocationBlock(Rect03, Row1,  m_Parameters.Col4, Len2, Len1 + 100, pData); // 4
			GenLocationBlock(Rect05, Row3,  m_Parameters.Col4, Len2, Len1 + 100, pData); // 4
			GenLocationBlock(Rect04, Row2 , m_Parameters.Col5, Len1 + 150, Len2, pData); // 5
		}

		///// STEP2 compute welding line center axes
		ComputeWeldingLineInfo(Image, Rect01, Rect01_row, Rect01_col, Rect01_phi, Rect01_len1, Rect01_len2);
		ComputeWeldingLineInfo(Image, Rect07, Rect07_row, Rect07_col, Rect07_phi, Rect07_len1, Rect07_len2);
		ComputeWeldingLineInfo(Image, Rect02, Rect02_row, Rect02_col, Rect02_phi, Rect02_len1, Rect02_len2);
		ComputeWeldingLineInfo(Image, Rect06, Rect06_row, Rect06_col, Rect06_phi, Rect06_len1, Rect06_len2);
		if(isTwoCan)
		{
			ComputeWeldingLineInfo(Image, Rect03, Rect03_row, Rect03_col, Rect03_phi, Rect03_len1, Rect03_len2);
			ComputeWeldingLineInfo(Image, Rect05, Rect05_row, Rect05_col, Rect05_phi, Rect05_len1, Rect05_len2);
			ComputeWeldingLineInfo(Image, Rect04, Rect04_row, Rect04_col, Rect04_phi, Rect04_len1, Rect04_len2);
		}
		///// STEP3 comptue canbody
		///// initial value for can body
		tmpCan1_row  = (Rect02_row + Rect06_row)/ 2;
		tmpCan1_col  = (Rect01_col + Rect07_col)/ 2;
		tmpCan1_phi  = (Rect01_phi + Rect07_phi)/ 2;
		tmpCan1_len1 = (Rect07_col - Rect01_col)/ 2 + 20;
		tmpCan1_len2 = (Rect06_row - Rect02_row)/ 2 + 20;
		tuple_abs(tmpCan1_phi, &absPhi);
		if(absPhi>EPS)
		{
			gen_rectangle2(&tmpCan1, tmpCan1_row, tmpCan1_col, tmpCan1_phi, tmpCan1_len2, tmpCan1_len1);
		}
		else
		{
			gen_rectangle2(&tmpCan1, tmpCan1_row, tmpCan1_col, tmpCan1_phi, tmpCan1_len1, tmpCan1_len2);	
		}

		if(isTwoCan)
		{
			tmpCan2_row  = (Rect03_row + Rect05_row)/ 2;
			tmpCan2_col  = (Rect07_col + Rect04_col)/ 2;
			tmpCan2_phi  = (Rect07_phi + Rect04_phi)/ 2;
			tmpCan2_len1 = (Rect04_col - Rect07_col)/ 2 + 20;
			tmpCan2_len2 = (Rect05_row - Rect03_row)/ 2 + 20;
			tuple_abs(tmpCan2_phi, &absPhi);
			if(absPhi>EPS)
			{
				gen_rectangle2(&tmpCan2, tmpCan2_row, tmpCan2_col, tmpCan2_phi, tmpCan2_len2, tmpCan2_len1);
			}
			else
			{
				gen_rectangle2(&tmpCan2, tmpCan2_row, tmpCan2_col, tmpCan2_phi, tmpCan2_len1, tmpCan2_len2);	
			}
		}
		
		ComputeCanBodyV2(Image, tmpCan1, Can1_phi);
		if(isTwoCan)
			ComputeCanBodyV2(Image, tmpCan2, Can2_phi);

		tuple_abs(Can1_phi, &absPhi);
		tuple_sin(absPhi, &sinn);
		tuple_cos(absPhi, &coss);
		if(absPhi>EPS)
		{
			len1 = ((Rect07_col - Rect01_col)*sinn - Rect01_len2 - Rect07_len2)/ 2;
			len2 = ((Rect06_row - Rect02_row)*sinn - Rect02_len2 - Rect06_len2)/ 2;
			row  = (Rect02_len2 + len2)*sinn + Rect02_row;
			col  = (Rect01_len2 + len1)*sinn + Rect01_col;
			gen_rectangle2(&Can1Body, row, col, Can1_phi, len2, len1);
		}
		else
		{
			len1 = ((Rect07_col - Rect01_col)*coss - Rect01_len2 - Rect07_len2)/2;
			len2 = ((Rect06_row - Rect02_row)*coss - Rect02_len2 - Rect06_len2)/2;
			row  = (Rect02_len2 + len2)*coss + Rect02_row ;
			col  = (Rect01_len2 + len1)*coss + Rect01_col ;
			gen_rectangle2(&Can1Body, row, col, Can1_phi, len1, len2);
		}
		disp_obj(Can1Body, pData->m_ShowHWindow);
		if(isTwoCan)
		{
			tuple_abs(Can2_phi, &absPhi);
			tuple_sin(absPhi, &sinn);
			tuple_cos(absPhi, &coss);
			if(absPhi>EPS)
			{
				len1 = ((Rect04_col - Rect07_col)*sinn - Rect04_len2 - Rect07_len2)/ 2;
				len2 = ((Rect05_row - Rect03_row)*sinn - Rect05_len2 - Rect03_len2)/ 2;
				row  = (Rect03_len2 + len2)*sinn + Rect03_row;
				col  = (Rect07_len2 + len1)*sinn + Rect07_col;
				gen_rectangle2(&Can1Body, row, col, Can1_phi, len2, len1);
			}
			else
			{
				len1 = ((Rect04_col - Rect07_col)*coss - Rect04_len2 - Rect07_len2)/2;
				len2 = ((Rect05_row - Rect03_row)*coss - Rect05_len2 - Rect03_len2)/2;
				row  = (Rect03_len2 + len2)*coss + Rect03_row;
				col  = (Rect07_len2 + len1)*coss + Rect07_col;
				gen_rectangle2(&Can2Body, row, col, Can1_phi, len1, len2);
			}
			disp_obj(Can2Body, pData->m_ShowHWindow);
		}
	
		///// STEP4 compute vertical seam
		Hobject Can1LeftSeam, Can1RightSeam;
		Hobject Can2LeftSeam, Can2RightSeam;
		ComputeVerticalSeamV2(Image, Can1Body, Can1LeftSeam, Can1RightSeam, pData->m_ShowHWindow);
		if(isTwoCan)
		{
			ComputeVerticalSeamV2(Image, Can2Body, Can2LeftSeam, Can2RightSeam, pData->m_ShowHWindow);
		}
		
		///// STEP5 copy operator and output result
		HTuple han1_row, han1_col, han1_phi, han1_len1, han1_len2;
		GetVerticalSeam(Can1LeftSeam, han1_row, han1_col, han1_phi, han1_len1, han1_len2);
		
		HTuple han7_row, han7_col, han7_phi, han7_len1, han7_len2;
		GetVerticalSeam(Can1RightSeam, han7_row, han7_col, han7_phi, han7_len1, han7_len2);
		
		HTuple han4_row, han4_col, han4_phi, han4_len1, han4_len2;
		if(isTwoCan)
		{
			GetVerticalSeam(Can2RightSeam, han4_row, han4_col, han4_phi, han4_len1, han4_len2);
		}

		pData->m_orientationPhi  = han1_phi[0].D();  // 1
		pData->m_center_x        = han1_col[0].D();
		pData->m_center_y        = han1_row[0].D(); 
		pData->m_vseam1_len1	 = han1_len1[0].D();
		pData->m_vseam1_len2     = han1_len2[0].D();
		
		pData->m_orientationPhi3 = han7_phi[0].D();  // 7
		pData->m_center_x2       = han7_col[0].D();
		pData->m_center_y2       = han7_row[0].D();
		pData->m_vseam7_len1	 = han7_len1[0].D();
		pData->m_vseam7_len2     = han7_len2[0].D();

		pData->m_TestRegist1     = Can1Body;  
		set_color(pData->m_ShowHWindow, "red");
		
		if(isTwoCan)
		{
			pData->r_real         = han4_phi[0].D();  // 3
			pData->m_center_x3    = han4_col[0].D(); 
			pData->m_center_y3    = han4_row[0].D(); 
			pData->m_vseam4_len1  = han4_len1[0].D();
			pData->m_vseam4_len2  = han4_len2[0].D();

			pData->m_TestRegist2  = Can2Body;      
		}
	}
	catch (...) 
	{
		//if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"CanBodyLocation01v1.0SheetIron parameter values error,please re-adjust");
			#else
			write_string(pData->m_ShowHWindow,"CanBodyLocation01v1.0罐身定位算子调整出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}	
}

