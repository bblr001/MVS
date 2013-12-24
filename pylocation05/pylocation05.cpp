// pylocation05.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "pylocation05.h"

#include <vector>
#include <math.h>

using namespace std;
using namespace Halcon;

#ifndef DLLEXPT
#define DLLEXPT __declspec (dllexport)
#endif

#define MAXGRAY 255
#define MINGRAY 0

CDoProcess::CDoProcess()
{
	m_bgnCol            = 630;
	m_dBeginRowLeft     = 430;
	m_dBeginRowRight    = 450;
}

void CDoProcess::SetParmeter(string parm, string value)
{
	if("rect01_col_offset"== parm)
		m_Parameters.rect01_col_offset = atoi(value.c_str());
	if("rect07_col_offset"== parm)
		m_Parameters.rect07_col_offset = atoi(value.c_str());
	if("rect04_col_offset"== parm)
		m_Parameters.rect04_col_offset = atoi(value.c_str());
}

double CDoProcess::CalculateEdgeRow(Hobject& targetRect, bool bFisrtFrame, bool bLastFrame)
{
	Hobject reducedRgn, edges;
	reduce_domain(m_currentImage,targetRect, &reducedRgn);
	
	HTuple Mean, Deviation;
	intensity(targetRect, reducedRgn, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	Hobject rgn;
	threshold(reducedRgn, &rgn, Thresh, 255);

	HTuple row1,col1,row2,col2;
	smallest_rectangle1(rgn,&row1,&col1, &row2, &col2);

	if(bFisrtFrame)
		return row1[0].D() + 5;
	if(bLastFrame)
		return row2[0].D() - 5;

	return 0.0;
}

double  CDoProcess::CalculateBeginColumn()
{
	Hobject tmpRect;
	gen_rectangle1(&tmpRect, 900, 400, 902, 912);
	
	Hobject reducedRgn;
	reduce_domain(m_currentImage,tmpRect, &reducedRgn);

	HTuple Mean, Deviation;
	intensity(tmpRect, reducedRgn, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh > MAXGRAY)
		Thresh = Mean;

	Hobject rgn;
	threshold(reducedRgn, &rgn, Mean, 255);
	
	HTuple row1,col1,row2,col2;
	smallest_rectangle1(rgn,&row1,&col1, &row2, &col2);

	return col1[0].D();
}

double  CDoProcess::CalculateBeginRowLeft(double& LeftCol)
{
	Hobject tmpRect;
	gen_rectangle1(&tmpRect, 420, m_bgnCol + 32, 650, m_bgnCol + 36);

	Hobject reducedRgn;
	reduce_domain(m_currentImage, tmpRect, &reducedRgn);

	HTuple Mean, Deviation;
	intensity(tmpRect, reducedRgn, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh > MAXGRAY)
		Thresh = Mean;
	Hobject rgn;
	threshold(reducedRgn, &rgn, Mean, 255);

	HTuple row1,col1,row2,col2;
	smallest_rectangle1(rgn,&row1,&col1, &row2, &col2);
	LeftCol = col1[0].D();

	return row1[0].D();
}

double  CDoProcess::CalculateBeginRowRight(double& RightCol)
{
	Hobject tmpRect;
	gen_rectangle1(&tmpRect, 420, m_imgWidth - 8, 550, m_imgWidth - 4);

	Hobject reducedRgn;
	reduce_domain(m_currentImage, tmpRect, &reducedRgn);

	HTuple Mean, Deviation;
	intensity(tmpRect, reducedRgn, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh > MAXGRAY)
		Thresh = Mean;

	Hobject rgn;
	threshold(reducedRgn, &rgn, Mean, 255);
	HTuple row1,col1,row2,col2;
	smallest_rectangle1(rgn,&row1,&col1, &row2, &col2);
	RightCol = col1[0].D();

	return row1[0].D();
}

double  CDoProcess::CalculateLastFrameRowLeft(double& LeftCol)
{
	Hobject tmpRect;
	gen_rectangle1(&tmpRect, 420 + 800, m_bgnCol + 32, 650 + 1000, m_bgnCol + 36);

	Hobject reducedRgn;
	reduce_domain(m_currentImage, tmpRect, &reducedRgn);

	HTuple Mean, Deviation;
	intensity(tmpRect, reducedRgn, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh > MAXGRAY)
		Thresh = Mean;
	Hobject rgn;
	threshold(reducedRgn, &rgn, Mean, 255);

	HTuple row1,col1,row2,col2;
	smallest_rectangle1(rgn,&row1,&col1, &row2, &col2);
	LeftCol = col2[0].D();

	return row2[0].D();
}

double  CDoProcess::CalculateLastFrameRowRight(double& RightCol)
{
	Hobject tmpRect;
	gen_rectangle1(&tmpRect, 420 + 800, m_imgWidth - 8, 550 + 1000, m_imgWidth - 4);

	Hobject reducedRgn;
	reduce_domain(m_currentImage, tmpRect, &reducedRgn);

	HTuple Mean, Deviation;
	intensity(tmpRect, reducedRgn, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh > MAXGRAY)
		Thresh = Mean;

	Hobject rgn;
	threshold(reducedRgn, &rgn, Mean, 255);
	HTuple row1,col1,row2,col2;
	smallest_rectangle1(rgn,&row1,&col1, &row2, &col2);
	RightCol = col2[0].D();

	return row2[0].D();
}

WeldRegion CDoProcess::ShufflePoints(double bgnRow, double endRow, PNT pt1, PNT pt2, PNT pt3, PNT pt4)
{
	PNT centerPnt((pt1.m_row + pt2.m_row + pt3.m_row + pt4.m_row)/4, (pt1.m_col + pt2.m_col + pt3.m_col + pt4.m_col)/4);
	std::vector<PNT> vPnt;
	vPnt.push_back(pt1);
	vPnt.push_back(pt2);
	vPnt.push_back(pt3);
	vPnt.push_back(pt4);

	WeldRegion retPnts;
	for(size_t t = 0; t  < 4; t++)
	{
		if((vPnt[t].m_row < centerPnt.m_row) && (vPnt[t].m_col < centerPnt.m_col))
		{
			retPnts.lt = vPnt[t];
		}
		if((vPnt[t].m_row < centerPnt.m_row) && (vPnt[t].m_col > centerPnt.m_col))
		{
			retPnts.rt = vPnt[t];
		}
		if((vPnt[t].m_row > centerPnt.m_row) && (vPnt[t].m_col > centerPnt.m_col))
		{
			retPnts.rb = vPnt[t];
		}
		if((vPnt[t].m_row > centerPnt.m_row) && (vPnt[t].m_col < centerPnt.m_col))
		{
			retPnts.lb = vPnt[t];
		}
	}

	double dSlopeLeft  = (retPnts.lt.m_row - retPnts.lb.m_row) / (retPnts.lt.m_col - retPnts.lb.m_col);
	double dSlopeRight = (retPnts.rt.m_row - retPnts.rb.m_row) / (retPnts.rt.m_col - retPnts.rb.m_col);

	if((retPnts.lt.m_row - bgnRow > 5.0) && fabs(dSlopeLeft) > 0.00001 && fabs(dSlopeLeft) < 573) // 573 ~= tan(89.9)
	{
		retPnts.lt.m_col += (bgnRow - retPnts.lt.m_row) / dSlopeLeft;
	}
	retPnts.lt.m_row = bgnRow;

	if((endRow - retPnts.lb.m_row > 5.0) && fabs(dSlopeLeft) > 0.00001 && fabs(dSlopeLeft) < 573) // 573 ~= tan(89.9)
	{
		retPnts.lb.m_col -= (retPnts.lb.m_row - endRow) / dSlopeLeft;
	}
	retPnts.lb.m_row = endRow;

	if((retPnts.rt.m_row - bgnRow > 5.0) && fabs(dSlopeRight) > 0.00001 && fabs(dSlopeRight) < 573) // 573 ~= tan(89.9)
	{
		retPnts.rt.m_col += (bgnRow - retPnts.rt.m_row) / dSlopeRight;
	}
	retPnts.rt.m_row = bgnRow;

	if((endRow - retPnts.rb.m_row > 5.0) && fabs(dSlopeRight) > 0.00001 &&  fabs(dSlopeRight) < 573) // 573 ~= tan(89.9)
	{
		retPnts.rb.m_col -= (retPnts.rb.m_row - endRow) / dSlopeRight;
	}
	retPnts.rb.m_row = endRow;

	return retPnts;
}
// nWeldColHint为界面设置的参数，为焊缝的大致列坐标
bool  CDoProcess::LocateWeldingLine(int nWeldColHint,WeldRegion& rgnPnts, Hlong hDispWnd)
{
	bool ret = false;
	// Step 1: Determine if this frame is the first/last frame of a sheet
	get_image_size(m_currentImage, &m_imgWidth, &m_imgHeight); 
	Hobject rtRect; // right top rectangle;
	gen_rectangle1(&rtRect, 4, m_imgWidth - 16, 6, m_imgWidth - 14);
	HTuple mean, dev;
	intensity(rtRect, m_currentImage, &mean, &dev);
	bool bFirstFrame = (mean[0].D() < 50.0);

	Hobject rbRect; // right bottom rectangle;
	gen_rectangle1(&rbRect, m_imgHeight - 16, m_imgWidth - 16, m_imgHeight - 14, m_imgWidth - 14);
	intensity(rbRect, m_currentImage, &mean, &dev);
	bool bLastFrame = (mean[0].D() < 50.0);

	// Step 2: Calculate bgnRow and endRow
	double bgnRow, endRow;
	Hobject  targerRect, reducedRgn;
	Hobject edges;
	HTuple max, min;
	HTuple row, col;
	bool bOk = false;
	if(bFirstFrame)
	{
		double leftCol  = 0.0;
		double rightCol = 0.0;
		m_dBeginRowLeft  = CalculateBeginRowLeft(leftCol);
		m_dBeginRowRight = CalculateBeginRowRight(rightCol);
		double dSlope =  (m_dBeginRowRight - m_dBeginRowLeft) / (rightCol - leftCol);
		double dRowHint = m_dBeginRowLeft + dSlope * (nWeldColHint - leftCol);
		bgnRow = dRowHint;
		endRow = m_imgHeight[0].D() - 5.0;
	}
	if(bLastFrame)
	{
		double leftCol  = 0.0;
		double rightCol = 0.0;
		double LastFrameRowLeft  = CalculateLastFrameRowLeft(leftCol);
		double LastFrameRowRight = CalculateLastFrameRowRight(rightCol);
		double dSlope =  (LastFrameRowRight - LastFrameRowLeft) / (rightCol - leftCol);
		double dRowHint = LastFrameRowLeft + dSlope * (nWeldColHint - leftCol);
		bgnRow = 0.0 + 5.0;
		endRow = dRowHint;
	}
	if(!bFirstFrame && !bLastFrame) // middle frame
	{
		bgnRow = 0.0 + 5.0;
		endRow = m_imgHeight[0].D() - 5.0;
	}
	// Step 3: determine the vertical search range -> [nWeldColHint-150, nWeldColHint + 150]， and make sure that the lower limitation is greater than zero
	if(bgnRow < 50 && endRow > 1700)
	{
		gen_rectangle1(&targerRect, 900 - 256, nWeldColHint-60, 900 + 256, nWeldColHint + 60);
	}
	else
	{
		gen_rectangle1(&targerRect, 900 - 256, nWeldColHint-60, 900 + 256, nWeldColHint + 60);
	}
	reduce_domain(m_currentImage, targerRect, &reducedRgn);
	edges_sub_pix(reducedRgn, &edges, "canny", 2.5, 10, 20);

	HTuple lineCounter;

	Hobject contoursSplit;
	segment_contours_xld(edges, &contoursSplit, "lines", 5, 4, 2);
	count_obj(contoursSplit,&lineCounter);
	if(!lineCounter)
		return false;

	Hobject  SelectedContours1, SelectedContours;
	select_contours_xld(contoursSplit, &SelectedContours1, "direction", 1.4, 1.75, -0.5, 0.5);
	count_obj(SelectedContours1,&lineCounter);
	if(!lineCounter)
		return false;

	select_contours_xld(SelectedContours1, &SelectedContours, "contour_length", 200, 1850, -0.5, 0.5);
	count_obj(SelectedContours,&lineCounter);

	Hobject  UnionContours;
	union_straight_contours_xld(SelectedContours, &UnionContours, 200, 0.5, 50, "noparallel", "maximum");
	//disp_obj(UnionContours, hDispWnd);

	Hobject weldLines;
	count_obj(UnionContours,&lineCounter);
	if(lineCounter[0].I() > 2)
	{
		HTuple Area1, Row1, Column1, PointOrder;
		area_center_xld (SelectedContours, &Area1, &Row1, &Column1, &PointOrder);
		HTuple Sorted, Indices;
		tuple_sort(Area1, &Sorted);
		tuple_sort_index(Area1, &Indices);
		HTuple len;
		tuple_length(Indices, &len);
		select_shape_xld(SelectedContours, &weldLines, "area", "and", HTuple(Area1[HTuple(Indices[len-2])])-2, 99999);
		count_obj(weldLines, &lineCounter);
		if(lineCounter[0].I() != 2)
			return false;
		else
			UnionContours = weldLines;
	}
	count_obj(UnionContours, &lineCounter);
	if(lineCounter[0].I() != 2)
		return false;

	HTuple  Nr, Nc, Dist;
	HTuple tmpRowBgn, tmpRowEnd, tmpColBgn, tmpColEnd;
	fit_line_contour_xld(UnionContours, "tukey", -1, 0, 5, 2, &tmpRowBgn, &tmpColBgn, &tmpRowEnd, &tmpColEnd, &Nr, &Nc, &Dist);

	PNT pt1(tmpRowBgn[0].D(), tmpColBgn[0].D());
	PNT pt2(tmpRowBgn[1].D(), tmpColBgn[1].D());
	PNT pt3(tmpRowEnd[0].D(), tmpColEnd[0].D());
	PNT pt4(tmpRowEnd[1].D(), tmpColEnd[1].D());

	rgnPnts = ShufflePoints(bgnRow, endRow, pt1, pt2,pt3, pt4);
	return true;
}

void CDoProcess::GenerateWeldRegion(const WeldRegion& rgnPnts,CMData* pData, int weldIndex, Hlong hDispWnd)
{
	HTuple row, col;
	row.Reset();
	row.Append(rgnPnts.lt.m_row + 2);
	row.Append(rgnPnts.rt.m_row + 2);
	row.Append(rgnPnts.rb.m_row - 2);
	row.Append(rgnPnts.lb.m_row - 2);

	col.Reset();
	col.Append(rgnPnts.lt.m_col + 3);
	col.Append(rgnPnts.rt.m_col - 2);
	col.Append(rgnPnts.rb.m_col - 2);
	col.Append(rgnPnts.lb.m_col + 3);

	Hobject weldRgn;
	gen_region_polygon_filled(&weldRgn, row, col);
	disp_obj(weldRgn, hDispWnd);

	HTuple tmpRow, tmpCol, tmpPhi, tmpLen1, tmpLen2;
	smallest_rectangle2(weldRgn, &tmpRow, &tmpCol, &tmpPhi, &tmpLen1, &tmpLen2);
	if(weldIndex == 1)
	{
		pData->m_orientationPhi = tmpPhi[0].D(); 
		pData->m_center_x       = tmpCol[0].D(); 
		pData->m_center_y       = tmpRow[0].D(); 
		pData->m_vseam1_len1    = tmpLen1[0].D();
		pData->m_vseam1_len2    = tmpLen2[0].D();
	}
	if(weldIndex == 4)
	{
		pData->r_real            = tmpPhi[0].D();    
		pData->m_center_x3       = tmpCol[0].D();   
		pData->m_center_y3       = tmpRow[0].D();  
		pData->m_vseam4_len1     = tmpLen1[0].D();
		pData->m_vseam4_len2     = tmpLen2[0].D();
	}
	if(weldIndex == 7)
	{
		pData->m_orientationPhi3 = tmpPhi[0].D(); 
		pData->m_center_x2       = tmpCol[0].D(); 
		pData->m_center_y2       = tmpRow[0].D(); 
		pData->m_vseam7_len1     = tmpLen1[0].D();
		pData->m_vseam7_len2     = tmpLen2[0].D();
	}
}

void CDoProcess::GenerateCanBodyRegion(const WeldRegion& leftWeldPnts, const WeldRegion& rightWeldPnts,Hobject& canBodyRgn, Hlong hDispWnd)
{
	HTuple row, col;
	row.Reset();
	row.Append(leftWeldPnts.rt.m_row + 2);
	row.Append(rightWeldPnts.lt.m_row + 2);
	row.Append(rightWeldPnts.lb.m_row - 2);
	row.Append(leftWeldPnts.rb.m_row - 2);

	col.Reset();
	col.Append(leftWeldPnts.rt.m_col + 3);
	col.Append(rightWeldPnts.lt.m_col - 2);
	col.Append(rightWeldPnts.lb.m_col - 2);
	col.Append(leftWeldPnts.rb.m_col + 3);
	gen_region_polygon_filled(&canBodyRgn, row, col);
	disp_obj(canBodyRgn, hDispWnd);
}

void CDoProcess::CalculateCenterWeldRegion(const WeldRegion& leftWeldPnts, const WeldRegion& rightWeldPnts, CMData* pData, int weldIndex, Hlong hDispWnd, WeldRegion& retRgn)
{
	retRgn.lt.m_row = (leftWeldPnts.lt.m_row + rightWeldPnts.lt.m_row) / 2;
	retRgn.lt.m_col = (leftWeldPnts.lt.m_col + rightWeldPnts.lt.m_col) / 2;
	retRgn.lt.m_row = (leftWeldPnts.lt.m_row + rightWeldPnts.lt.m_row) / 2;
	retRgn.lt.m_col = (leftWeldPnts.lt.m_col + rightWeldPnts.lt.m_col) / 2;

	retRgn.rt.m_row = (leftWeldPnts.rt.m_row + rightWeldPnts.rt.m_row) / 2;
	retRgn.rt.m_col = (leftWeldPnts.rt.m_col + rightWeldPnts.rt.m_col) / 2;
	retRgn.rt.m_row = (leftWeldPnts.rt.m_row + rightWeldPnts.rt.m_row) / 2;
	retRgn.rt.m_col = (leftWeldPnts.rt.m_col + rightWeldPnts.rt.m_col) / 2;

	retRgn.rb.m_row = (leftWeldPnts.rb.m_row + rightWeldPnts.rb.m_row) / 2;
	retRgn.rb.m_col = (leftWeldPnts.rb.m_col + rightWeldPnts.rb.m_col) / 2;
	retRgn.rb.m_row = (leftWeldPnts.rb.m_row + rightWeldPnts.rb.m_row) / 2;
	retRgn.rb.m_col = (leftWeldPnts.rb.m_col + rightWeldPnts.rb.m_col) / 2;

	retRgn.lb.m_row = (leftWeldPnts.lb.m_row + rightWeldPnts.lb.m_row) / 2;
	retRgn.lb.m_col = (leftWeldPnts.lb.m_col + rightWeldPnts.lb.m_col) / 2;
	retRgn.lb.m_row = (leftWeldPnts.lb.m_row + rightWeldPnts.lb.m_row) / 2;
	retRgn.lb.m_col = (leftWeldPnts.lb.m_col + rightWeldPnts.lb.m_col) / 2;

	GenerateWeldRegion(retRgn, pData, weldIndex, hDispWnd);
}

bool CDoProcess::CalculateLocationBlockCenter(Hobject& src, Hobject& srcRegion, int &estimateCol)
{
	HTuple Num;
	count_obj(srcRegion, &Num);
	if(!Num)
		return false;

	HTuple row, col, phi, len1, len2;
	smallest_rectangle2(srcRegion, &row, &col, &phi, &len1, &len2);

	Hobject reduceImage;
	reduce_domain(src, srcRegion, &reduceImage);

	HTuple Mean, Deviation;
	intensity(srcRegion, reduceImage, &Mean, &Deviation);

	HTuple Thresh = Mean + Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	Hobject fastRegion;
	fast_threshold(reduceImage, &fastRegion, Thresh, MAXGRAY, 10);

	Hobject connRegion;
	connection(fastRegion, &connRegion);

	Hobject selectRegion;
	select_shape(connRegion, &selectRegion, "width", "and", 30, 65);

	count_obj(selectRegion, &Num);
	if(!Num)
		return false;
	
	Hobject selectRegion1;
	select_shape(selectRegion, &selectRegion1, "height", "and", len2, len2*2 + 10);

	count_obj(selectRegion1, &Num);

	Hobject ObjectSelected;
	if(!Num)
		return false;
	if(Num>1)
	{
		HTuple Rectangularity;
		rectangularity(selectRegion1, &Rectangularity);

		HTuple Max;
		tuple_max(Rectangularity, &Max);

		select_shape(selectRegion1, &ObjectSelected, "rectangularity", "and", Max-0.005,  1.0);
	}
	else
		copy_obj(selectRegion1,&ObjectSelected, 1, 1);

	smallest_rectangle2(ObjectSelected, &row, &col, &phi, &len1, &len2);
	estimateCol = col[0].I();

	return true;
}

void CDoProcess::DoProcess(CMData* pData, SubTestResult *testItem)
{	
	try
	{
		m_currentImage = pData->m_Image;
		Hlong hDispWnd = pData->m_ShowHWindow;
		HTuple imgWidth, imgHeight;
		get_image_size(m_currentImage, &imgWidth, &imgHeight);  
		set_color(hDispWnd,"blue");

		Hobject Rect01, Rect04, Rect07;
		gen_rectangle2(&Rect01, 900, m_Parameters.rect01_col_offset, 0, 256, 4);
		gen_rectangle2(&Rect07, 900, m_Parameters.rect07_col_offset, 0, 256, 4);
		gen_rectangle2(&Rect04, 900, m_Parameters.rect04_col_offset, 0, 256, 4);
		
		if(pData->m_isDebug)
		{
			disp_obj(Rect01, pData->m_ShowHWindow);
			disp_obj(Rect07, pData->m_ShowHWindow);
			disp_obj(Rect04, pData->m_ShowHWindow);
		}

		// Locate welding lines
		int estimateCol01 = 0;
		if(!CalculateLocationBlockCenter(m_currentImage, Rect01, estimateCol01))
			estimateCol01 = m_Parameters.rect01_col_offset;

		WeldRegion rgnPnts1;
	    bool bGotSeam1 = LocateWeldingLine(estimateCol01,rgnPnts1,hDispWnd);
		if(bGotSeam1)
		{
			GenerateWeldRegion(rgnPnts1,pData, 1, hDispWnd);
		}
		else
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			return ;
		}

		int estimateCol04 = 0;
		if(!CalculateLocationBlockCenter(m_currentImage, Rect04, estimateCol04))
			estimateCol04 = m_Parameters.rect04_col_offset;

		bool bGotSeam4 = false;
		WeldRegion rgnPnts4;
		
		bGotSeam4 = LocateWeldingLine(estimateCol04, rgnPnts4,hDispWnd);
		if(bGotSeam4)
		{
			GenerateWeldRegion(rgnPnts4, pData, 4, hDispWnd);
		}
		else
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			return ;
		}
		
		// Locate welding lines 07
		int estimateCol07 = 0;
		if(!CalculateLocationBlockCenter(m_currentImage, Rect07, estimateCol07))
			estimateCol07 = m_Parameters.rect07_col_offset;

		WeldRegion rgnPnts7;
		bool bGotSeam7 = LocateWeldingLine(estimateCol07,rgnPnts7,hDispWnd);
		if(bGotSeam7)
		{
			GenerateWeldRegion(rgnPnts7, pData, 7, hDispWnd);
		}
		else
		{
			if(bGotSeam1 && bGotSeam4)
			{
				CalculateCenterWeldRegion(rgnPnts1, rgnPnts4, pData, 7, hDispWnd, rgnPnts7);
				bGotSeam7 = true;
			}
		}
		// Generate can body test regions 
		GenerateCanBodyRegion(rgnPnts1, rgnPnts7, pData->m_TestRegist1, hDispWnd);
		GenerateCanBodyRegion(rgnPnts7, rgnPnts4, pData->m_TestRegist2, hDispWnd);
		
		bool bOk = bGotSeam1 && bGotSeam7 && bGotSeam4;
		
		pData->m_isFail = !bOk;
		testItem->m_bFailSubTest = !bOk;
	}
	catch (...) 
	{
		//if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"pylocation05 SheetIron parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"pylocation05定位算子参数错误");
#endif
		}
		pData->m_isFail          = true;
		testItem->m_bFailSubTest = true;
	}	
}