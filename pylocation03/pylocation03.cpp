// pylocation03.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "pylocation03.h"

#include <vector>

using namespace std;
using namespace Halcon;

#ifndef DLLEXPT
#define DLLEXPT __declspec (dllexport)
#endif
#define MAXGRAYVALUE 255
CDoProcess::CDoProcess()
{
	ShowObject = false;
	printf("SheetIronDetect  Function\r\n");
}

void CDoProcess::SetParmeter(string parm, string value)
{
	if(parm=="SHOWOBJECT")
	{	if (value=="YES")
			ShowObject = true;
		else
			ShowObject = false;
	}

	if("rect01_col_offset"== parm)
		m_Parameters.rect01_col_offset = atoi(value.c_str());
	if("rect07_col_offset"== parm)
		m_Parameters.rect07_col_offset = atoi(value.c_str());
	if("rect04_col_offset"== parm)
		m_Parameters.rect04_col_offset = atoi(value.c_str());

	if("rect01_thresh_Min"== parm)
		m_Parameters.rect01_thresh_Min = atoi(value.c_str());
	if("rect07_thresh_Min"== parm)
		m_Parameters.rect07_thresh_Min = atoi(value.c_str());
	if("rect04_thresh_Min"== parm)
		m_Parameters.rect04_thresh_Min = atoi(value.c_str());
}

CalPoint CDoProcess::computeAxes(HTuple &row, HTuple &col, HTuple &phi, HTuple &height, HTuple &width)
{
	HTuple tmp_Sin, tmp_Cos, tmp_Tan;
	tuple_sin(phi, &tmp_Sin);
	tuple_cos(phi, &tmp_Cos);
	tuple_tan(phi, &tmp_Tan);
	
	HTuple tmpRow, tmpCol;
	HTuple pt2_row = row - (height - width/tmp_Tan) * tmp_Sin;
	HTuple pt2_col = col + width/tmp_Sin + (height - width/tmp_Tan) * tmp_Cos;
	
	HTuple pt1_row = pt2_row - 2 * width * tmp_Cos;
	HTuple pt1_col = pt2_col - 2 * width * tmp_Sin;
	
	HTuple pt4_row = 2*row - pt2_row;
	HTuple pt4_col = 2*col - pt2_col;

	HTuple pt3_row = 2*row - pt1_row;
	HTuple pt3_col = 2*col - pt1_col;
	
	
	HTuple rowArray, colArray;
	rowArray.Reset();
	rowArray.Append(pt1_row);
	rowArray.Append(pt2_row);
	rowArray.Append(pt3_row);
	rowArray.Append(pt4_row);

	colArray.Reset();
	colArray.Append(pt1_col);
	colArray.Append(pt2_col);
	colArray.Append(pt3_col);
	colArray.Append(pt4_col);
	
	HTuple rowLen;
	tuple_length(rowArray, &rowLen);

	HTuple upArray, downArray;
	upArray.Reset();
	downArray.Reset();
	for(int i = 0; i< rowLen; i++)
	{
		if(rowArray[i]< row)
		{
			upArray.Append(i);
		}
		else
		{
			downArray.Append(i);
		}
	}
	
	HTuple maxIndex_up, minIndex_up;
	tuple_max(upArray, &maxIndex_up);  
	tuple_min(upArray, &minIndex_up);  
	if(colArray[maxIndex_up] < colArray[minIndex_up])
	{
		pt1_row = rowArray[maxIndex_up];
		pt1_col = colArray[maxIndex_up];
		
		pt2_row = rowArray[minIndex_up];
		pt2_col = colArray[minIndex_up];
	}
	else
	{
		pt1_row = rowArray[minIndex_up];
		pt1_col = colArray[minIndex_up];
		
		pt2_row = rowArray[maxIndex_up];
		pt2_col = colArray[maxIndex_up];
	}

	HTuple maxIndex_down, minIndex_down;
	tuple_max(downArray, &maxIndex_down);
	tuple_min(downArray, &minIndex_down);
	if(colArray[maxIndex_down] < colArray[minIndex_down])
	{
		pt3_row = rowArray[minIndex_down];
		pt3_col = colArray[minIndex_down];
		
		pt4_row = rowArray[maxIndex_down];
		pt4_col = colArray[maxIndex_down];
	}
	else
	{
		pt3_row = rowArray[maxIndex_down];
		pt3_col = colArray[maxIndex_down];
		
		pt4_row = rowArray[minIndex_down];
		pt4_col = colArray[minIndex_down];
	}

	CalPoint retPoint;
	retPoint.pt1.row = pt1_row;
	retPoint.pt1.col = pt1_col;

	retPoint.pt2.row = pt2_row;
	retPoint.pt2.col = pt2_col;

	retPoint.pt3.row = pt3_row;
	retPoint.pt3.col = pt3_col;

	retPoint.pt4.row = pt4_row;
	retPoint.pt4.col = pt4_col;

	return retPoint;
}

bool  CDoProcess::computeLocationBlock(Hobject& srcObj, Hobject& rect, double param, Hobject& retRect, Hlong& hw, HTuple& thresh)
{
	HTuple row, col, phi, len1, len2;
	smallest_rectangle2(rect, &row, &col, &phi, &len1, &len2); // input location block

	Hobject ImageReduced;
	reduce_domain(srcObj, rect, &ImageReduced);
	
	Hobject Region;
	fast_threshold(ImageReduced, &Region, 100, 255, 10);

	Hobject lightBlock;
	reduce_domain(ImageReduced, Region, &lightBlock);
	
	HTuple Mean, Deviation;
	intensity (Region, lightBlock, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if (Thresh>= MAXGRAYVALUE)
	{
		Thresh = Mean;
	}

	Hobject fastRegion;
	fast_threshold (lightBlock, &fastRegion, Thresh, 255, 10);
	
	// first 'open '  remove points on the side of vertical seam 
	Hobject RegionOpening;
	opening_rectangle1(fastRegion, &RegionOpening, 3, 5);
	
	// second 'close' connect vertical direction block on vertical seam 
    Hobject RegionClosing;
    closing_rectangle1(RegionOpening, &RegionClosing, 5, 13);

	Hobject ConnectedRegions1;
	connection(RegionClosing, &ConnectedRegions1);

	Hobject RegionFilled;
	fill_up(ConnectedRegions1, &RegionFilled);
	
	Hobject ConnectedRegions2;
	connection(RegionFilled, &ConnectedRegions2);

 	HTuple hanW = 50;
 	Hobject RegionSelected;
	select_shape(ConnectedRegions2, &RegionSelected, "height", "and", len2*2 - 40, len2*2 + 40);

	Hobject HanfengSelected;
	select_shape(RegionSelected, &HanfengSelected, "width", "and", hanW-25, hanW+10);

	disp_obj(HanfengSelected, hw);

	HTuple Number;
	count_obj(HanfengSelected, &Number);
	
	HTuple rect_row, rect_col, rect_phi, rect_Length1, rect_Length2;
	HTuple Area1, Row1, Column1;
	if (0 == Number)
	{
		count_obj(ConnectedRegions1, &Number);
		area_center(ConnectedRegions1, &Area1, &Row1, &Column1);
		
		HTuple Mean1;
		tuple_mean(Area1, &Mean1);
		
		HTuple Deviation1;
		tuple_deviation(Area1, &Deviation1);

		Hobject SelectedRegions1;
		select_shape(ConnectedRegions1, &SelectedRegions1, "area", "and", Mean1+Deviation1, 99999);
		
		Hobject RegionUnion;
		union1(SelectedRegions1, &RegionUnion);
		smallest_rectangle2(RegionUnion, &rect_row, &rect_col, &rect_phi, &rect_Length1, &rect_Length2);
	}
	else if(1 == Number)
	{
		Hobject SelectedRegions2;
		select_shape(HanfengSelected, &SelectedRegions2, "rectangularity", "and", 0.5, 1);
		smallest_rectangle2(SelectedRegions2, &rect_row, &rect_col, &rect_phi, &rect_Length1, &rect_Length2);

	}
	else // exist two or more block match the select condition, and this need reject other part
	{

		HTuple Rectangularity;
		rectangularity (HanfengSelected, &Rectangularity);
		HTuple rectyMean;
		tuple_mean(Rectangularity, &rectyMean);
		HTuple rectyMax;
		tuple_mean(Rectangularity, &rectyMax);

		Hobject SelectObj;
		select_shape(HanfengSelected, &SelectObj, "rectangularity", "and", rectyMax, 1);
		smallest_rectangle2(SelectObj, &rect_row, &rect_col, &rect_phi, &rect_Length1, &rect_Length2);
	}
	//disp_obj(HanfengSelected, hw);
	
	HTuple tempLen;
	if(rect_Length1<rect_Length2)
	{
		tempLen       = rect_Length1;
		rect_Length1  = rect_Length2;
		rect_Length2  = tempLen;
	}
	//gen_rectangle2(&retRect, rect_row, rect_col, rect_phi, 1000, rect_Length2);
	err =gen_rectangle2(&retRect, rect_row, rect_col, rect_phi, 1000, rect_Length2);
	// debug code 
	HTuple cNum;
	count_obj(retRect, &cNum);

	thresh  = Mean + Deviation ;

	return rect_phi[0].D()!= 0.0;
}

bool CDoProcess::computeVirticalSeam(Hobject& srcObj, Hobject& rect, double param, Hobject& retRect, HTuple& center_row, HTuple& center_col, HTuple& phi, HTuple& len1, HTuple& len2)
{
	Hobject ImageReduced;
	reduce_domain(srcObj, rect, &ImageReduced);

	Hobject Region;
	fast_threshold(ImageReduced, &Region, param, 255, 10);
	
	Hobject RegionErosion;
	erosion_rectangle1(Region, &RegionErosion, 5, 5);
	smallest_rectangle2(RegionErosion, &center_row, &center_col, &phi, &len1, &len2);
	gen_rectangle2(&retRect, center_row, center_col, phi, len1, len2);	

	return phi[0].D()!=0.0 ;
}

void CDoProcess::locateCanBody(CalPoint& src1Point, CalPoint& src2Point, Hobject& retObj)
{
	HTuple test_row, test_col;
	test_row.Reset();
	test_row.Append(src1Point.pt2.row);
	test_row.Append(src2Point.pt1.row);
	test_row.Append(src2Point.pt4.row);
	test_row.Append(src1Point.pt3.row);

	test_col.Reset();
	test_col.Append(src1Point.pt2.col);
	test_col.Append(src2Point.pt1.col);
	test_col.Append(src2Point.pt4.col);
	test_col.Append(src1Point.pt3.col);
		
	gen_region_polygon_filled(&retObj, test_row, test_col);
}
void CDoProcess::DoProcess(CMData* pData, SubTestResult *testItem)
{	
	try
	{
		TiledImage = pData->m_Image;
		get_image_size(TiledImage, &tile_Width, &tile_Height);  
		set_color(pData->m_ShowHWindow,"blue");

		bool bTwoCan = !(tile_Width < DefaultWidth);

		fast_threshold(TiledImage, &Region, 80, 255, 10);
		connection(Region, &ConnectedRegions);
		select_shape(ConnectedRegions, &SelectedRegions, "area", "and", ((tile_Width*tile_Height)*0.6)-10000, tile_Width*tile_Height);
		erosion_rectangle1(SelectedRegions, &RegionErosion1, 5, 5);
		
		reduce_domain(TiledImage, RegionErosion1, &MainBlock);

		gen_rectangle2(&Rect01, 900, m_Parameters.rect01_col_offset, 0, 150*2, 100);
		gen_rectangle2(&Rect07, 900, m_Parameters.rect07_col_offset, 0, 150*2, 100);
		if(pData->m_isDebug && ShowObject)
		{
			disp_obj(Rect01, pData->m_ShowHWindow);
			disp_obj(Rect07, pData->m_ShowHWindow);
		}
		HTuple rect01_thresh, rect07_thresh, rect04_thresh;
		computeLocationBlock(TiledImage, Rect01, m_Parameters.rect01_thresh_Min, Rectangle1, pData->m_ShowHWindow, rect01_thresh);
		computeLocationBlock(TiledImage, Rect07, m_Parameters.rect07_thresh_Min, Rectangle7, pData->m_ShowHWindow, rect07_thresh);
		//disp_obj(Rectangle1, pData->m_ShowHWindow);
		//disp_obj(Rectangle7, pData->m_ShowHWindow);

		if(bTwoCan)
		{
			gen_rectangle2(&Rect04, 900, m_Parameters.rect04_col_offset, 0, 150*2, 100);
			if(pData->m_isDebug && ShowObject)
				disp_obj(Rect04, pData->m_ShowHWindow);
			
			computeLocationBlock(TiledImage, Rect04, m_Parameters.rect04_thresh_Min, Rectangle4, pData->m_ShowHWindow, rect04_thresh);
			//disp_obj(Rectangle4, pData->m_ShowHWindow);
		}
	
		computeVirticalSeam(MainBlock, Rectangle1, m_Parameters.rect01_thresh_Min, rect01_disp, rec01_Row, rec01_Column, rec01_Phi, rec01_Length1, rec01_Length2);
		disp_obj(rect01_disp, pData->m_ShowHWindow);

		computeVirticalSeam(MainBlock, Rectangle7, m_Parameters.rect07_thresh_Min, rect07_disp, rec07_Row, rec07_Column, rec07_Phi, rec07_Length1, rec07_Length2);
		disp_obj(rect07_disp, pData->m_ShowHWindow);

		if(bTwoCan)
		{
			computeVirticalSeam(MainBlock, Rectangle4, m_Parameters.rect04_thresh_Min, rect04_disp, rec04_Row, rec04_Column, rec04_Phi, rec04_Length1, rec04_Length2);
			disp_obj(rect04_disp, pData->m_ShowHWindow);
		}	

		CalPoint rec01_pt, rec07_pt, rec04_pt;

		rec01_pt = computeAxes(rec01_Row, rec01_Column, rec01_Phi, rec01_Length1, rec01_Length2);
		rec07_pt = computeAxes(rec07_Row, rec07_Column, rec07_Phi, rec07_Length1, rec07_Length2);

		if(bTwoCan)
		{
			rec04_pt = computeAxes(rec04_Row, rec04_Column, rec04_Phi, rec04_Length1, rec04_Length2);
		}

		locateCanBody(rec01_pt, rec07_pt, testRegion01);
				
		pData->m_orientationPhi = rec01_Phi[0].D(); 
		pData->m_center_x       = rec01_Column[0].D(); 
		pData->m_center_y       = rec01_Row[0].D(); 
		pData->m_vseam1_len1    = rec01_Length1[0].D();
		pData->m_vseam1_len2    = rec01_Length2[0].D();

		pData->m_orientationPhi3 = rec07_Phi[0].D(); 
		pData->m_center_x2       = rec07_Column[0].D(); 
		pData->m_center_y2       = rec07_Row[0].D(); 
		pData->m_vseam7_len1     = rec07_Length1[0].D();
		pData->m_vseam7_len2     = rec07_Length2[0].D();

		pData->m_TestRegist1     = testRegion01;

		disp_obj(testRegion01, pData->m_ShowHWindow);

		if(bTwoCan)
		{
			locateCanBody(rec07_pt, rec04_pt, testRegion02);

			pData->r_real            = rec04_Phi[0].D();    
			pData->m_center_x3       = rec04_Column[0].D();   
			pData->m_center_y3       = rec04_Row[0].D();  
			pData->m_vseam4_len1     = rec04_Length1[0].D();
			pData->m_vseam4_len2     = rec04_Length2[0].D();

			pData->m_TestRegist2     = testRegion02;
			disp_obj(testRegion02, pData->m_ShowHWindow);
		}
	}
	catch (...) 
	{/// 
		
		//if (pData->m_isDebug/* &&err != H_MSG_TRUE*/)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			//get_error_text((long)err,message);
			//sprintf(stderr,"my error message: %s\n",message);
#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"pylocation03 SheetIron parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"pylocation03定位算子参数错误");
#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;

		
		
	}	
}