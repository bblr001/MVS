// HorizonSeamDetect01.cpp : 定义 DLL 应用程序的导出函数。
//
/*
	印刷片料罐身横边缺陷检测
*/
#include "stdafx.h"
#include "HorizonSeamDetect01.h"

using namespace std;
using namespace Halcon;

#ifndef DLLEXPT
#define DLLEXPT __declspec (dllexport)
#endif

#define MAXGRAY 255
#define MINGRAY 0

CDoProcess::CDoProcess()
{
	ShowObject = false;
	printf("HorizonSeamDetect01 Function\r\n");
}

void CDoProcess::SetParmeter(string parm, string value)
{
	if(parm=="SHOWOBJECT")
	{	if (value=="YES")
			ShowObject = true;
		else
			ShowObject = false;
	}
	// 罐身区域横边2，3，5，6
	if (!_stricmp(parm.c_str(),"List_Value"))
	{
		if(!_stricmp(value.c_str(),"Reg01"))
		{
			m_ListReg = CAN1;
		}
		if(!_stricmp(value.c_str(),"Reg02"))
		{
			m_ListReg = CAN2;
		}
		
	}	
	if("len1"== parm)
		m_Parameters.len1 = atoi(value.c_str());
	if("len2"== parm)
		m_Parameters.len2 = atoi(value.c_str());
	if("meanSize"== parm)
		m_Parameters.meanSize = atoi(value.c_str());
	if("dynThreshold"== parm)
		m_Parameters.dynThreshold = atoi(value.c_str());
	if("regShapSize"== parm)
		m_Parameters.regShapSize = atoi(value.c_str());
}

void CDoProcess::JudgeFramePosition(Hobject& image, bool& firstFrame, bool& lastFrame, CMData* pData)
{
	HTuple Width, Height;
	get_image_size(image, &Width, &Height);

	double LocationCol = Width[0].D()/2 - 40;
	double RowUp   = 20;
	double RowDown = Height[0].D() - 20;
	Hobject UpRect, DownRect;
	gen_rectangle2(&UpRect,   RowUp,   LocationCol, 0, 2, 8);
	gen_rectangle2(&DownRect, RowDown, LocationCol, 0, 2, 8);
	if(pData->m_isDebug && ShowObject)
	{
		disp_obj(UpRect, pData->m_ShowHWindow);
		disp_obj(DownRect, pData->m_ShowHWindow);
	}

	Hobject ImageUp, ImageDown;
	reduce_domain(image, UpRect, &ImageUp);
	reduce_domain(image, DownRect, &ImageDown);

	HTuple Mean, Deviation;
	intensity(UpRect, ImageUp, &Mean, &Deviation);
	if(Mean < 50)
		firstFrame = true;
	else 
		firstFrame = false;

	intensity(DownRect, ImageDown, &Mean, &Deviation);
	if(Mean < 50)
		lastFrame = true;
	else
		lastFrame = false;
}

///// comptue horizon seam 
void CDoProcess::ComputeHorizonSeam(Hobject& image, Hobject& canbody, Hobject& upSeam, Hobject& downSeam, CMData* pData)
{
	HTuple Row, Col, Phi, Len1, Len2;
	smallest_rectangle2(canbody, &Row, &Col, &Phi, &Len1, &Len2);

	Hobject rectangleSmall, rectangleBig;
	gen_rectangle2(&rectangleSmall, Row, Col, Phi, Len1 - 25, Len2 - 5);
	gen_rectangle2(&rectangleBig,   Row, Col, Phi, Len1 - 30, Len2 + 30);
	
	Hobject rectangleDiff;
	difference(rectangleBig, rectangleSmall, &rectangleDiff);
	
	Hobject rectangleConn;
	connection(rectangleDiff, &rectangleConn);

	HTuple Area;
	area_center(rectangleConn, &Area, &Row, &Col);

	HTuple Min, Max;
	tuple_min(Row, &Min);
	tuple_max(Row, &Max);

	Hobject RectangleUpper, RectangleLower;
	select_shape(rectangleConn, &RectangleUpper, "row", "and", Min - 0.5, Min + 0.5);
	select_shape(rectangleConn, &RectangleLower, "row", "and", Max - 0.5, Max + 0.5);
	//disp_obj(RectangleUpper, pData->m_ShowHWindow);
	//disp_obj(RectangleLower, pData->m_ShowHWindow);

	Hobject ImageUpper;
	reduce_domain(image, RectangleUpper, &ImageUpper);

	HTuple Mean, Deviation;
	intensity(RectangleUpper, ImageUpper, &Mean, &Deviation);

	HTuple Thresh = Mean - Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	Hobject upperHorizonSeam;
	fast_threshold(ImageUpper, &upperHorizonSeam, Thresh, MAXGRAY, 5);

	Hobject connHor1, connHor2;
	connection(upperHorizonSeam, &connHor1);
	
	area_center(connHor1, &Area, &Row, &Col);
	tuple_max(Area, &Max);
	///// the finally up seam
	Hobject selectHor1;
	select_shape(connHor1, &upSeam, "area", "and", Max -0.5, Max +0.5);
	//disp_obj(upSeam, pData->m_ShowHWindow);

	Hobject ImageLower;
	reduce_domain(image, RectangleLower, &ImageLower);

	intensity(RectangleLower, ImageLower, &Mean, &Deviation);
	Thresh = Mean - Deviation;
	if(Thresh >= MAXGRAY)
		Thresh = Mean;

	Hobject lowerHorizonSeam;
	fast_threshold(ImageLower, &lowerHorizonSeam, Thresh, MAXGRAY, 5);

	connection(lowerHorizonSeam, &connHor2);
	area_center(connHor2, &Area, &Row, &Col);
	tuple_max(Area, &Max);
	///// the finally up seam
	Hobject selectHor2;
	select_shape(connHor2, &downSeam, "area", "and", Max -0.5, Max +0.5);
	
}

void CDoProcess::GetProcessSeam(Hobject& upSeam, Hobject& downSeam, bool& ff, bool& lf, Hobject& outputSeam)
{
	Hobject ErosionRectangle;
	if(ff )       /// first frame
	{
		erosion_rectangle1(upSeam, &ErosionRectangle, 1, 11);
		copy_obj(ErosionRectangle, &outputSeam, 1, 1);
	}	
	else if(lf )  /// last frame
	{
		erosion_rectangle1(downSeam, &ErosionRectangle, 1, 11);
		copy_obj(ErosionRectangle, &outputSeam, 1, 1);
	}
	else         /// median frame
	{
		erosion_rectangle1(upSeam, &ErosionRectangle, 1, 9);
		copy_obj(ErosionRectangle, &outputSeam, 1, 1);
	}
}

void CDoProcess::DetectHorizonSeamDefect(Hobject& image, Hobject& processBlock, int& srclen1, int& srclen2, int& meanSize, int& dynThresh, int& shapeSize, Hobject& defect, HTuple& defectNum, Hlong& handle, bool& isDebug)
{
	HTuple row, col, phi, len1, len2;
	smallest_rectangle2(processBlock, &row, &col, &phi, &len1, &len2);
	
	Hobject processBlockA;
	gen_rectangle2(&processBlockA, row, col, phi, len1 + srclen1, len2 + srclen2);
	if(isDebug && ShowObject)
		disp_obj(processBlockA, handle);

	Hobject ImageReduced;
	reduce_domain(image, processBlockA, &ImageReduced);
	
	Hobject ImageMean;
	mean_image(ImageReduced, &ImageMean, meanSize, meanSize);

	Hobject RegionDynThresh;
	dyn_threshold(ImageReduced, ImageMean, &RegionDynThresh, dynThresh, "dark");

	Hobject ConnectedRegions;
	connection(RegionDynThresh, &ConnectedRegions);

	select_shape(ConnectedRegions, &defect, "area", "and", shapeSize, 999999);
	count_obj(defect, &defectNum);
}

void CDoProcess::DoProcess(CMData* pData, SubTestResult *testItem)
{	
	try
	{
		Hobject Image = pData->m_Image;
		
		get_image_size(Image, &Width, &Height);  
		bool isTwoCan = !(Width[0].D() < DefaultWidth);
		
		HTuple Num;
		Can1Body = pData->m_TestRegist1;
		count_obj(Can1Body, &Num);
		if(Num == 0)
			return ;

		if(isTwoCan)
		{
			Can2Body = pData->m_TestRegist2;
			count_obj(Can2Body, &Num);
			if(Num == 0)
				return ;
		}

		ComputeHorizonSeam(Image,  Can1Body, Can1UpSeam, Can1DownSeam, pData);
		if(isTwoCan)
			ComputeHorizonSeam(Image, Can2Body, Can2UpSeam, Can2DownSeam, pData);

		JudgeFramePosition(Image, FirstFrame, LastFrame, pData);
		GetProcessSeam(Can1UpSeam, Can1DownSeam, FirstFrame, LastFrame, Can1ProcessSeam);
		if(isTwoCan)
		{
			GetProcessSeam(Can2UpSeam, Can2DownSeam, FirstFrame, LastFrame, Can2ProcessSeam);
		}
		
		
		Hobject Can1Def, Can2Def;
		HTuple  Can1DefNo, Can2DefNo;
		switch(m_ListReg)
		{
		case CAN1:
			DetectHorizonSeamDefect(Image, Can1ProcessSeam, m_Parameters.len1, m_Parameters.len2, m_Parameters.meanSize, m_Parameters.dynThreshold, m_Parameters.regShapSize, CanHorizonSeamDef, errNum, pData->m_ShowHWindow, pData->m_isDebug);
			break;
		case CAN2:
			DetectHorizonSeamDefect(Image, Can2ProcessSeam, m_Parameters.len1, m_Parameters.len2, m_Parameters.meanSize, m_Parameters.dynThreshold, m_Parameters.regShapSize, CanHorizonSeamDef, errNum, pData->m_ShowHWindow, pData->m_isDebug);
			break;
		}
		Hobject UnionErrRegion;
		if (0 != errNum)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;

			//if(pData->isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(CanHorizonSeamDef, pData->m_ShowHWindow);
				//pData->m_ErrorRegist = CanHorizonSeamDef;
				union2(pData->m_ErrorRegist, CanHorizonSeamDef, &UnionErrRegion);
				pData->m_ErrorRegist = UnionErrRegion;
			}
			
			HTuple areaSize,row,col;
			area_center(CanHorizonSeamDef,&areaSize,&row,&col);

			HTuple radius;
			tuple_sqrt(areaSize/PI, &radius);
			
			ERROR_RGN_INFO errorRgn;
			for(int i = 0; i<errNum ;i++)
			{
				errorRgn.m_row  = (long)row[i].D();
				errorRgn.m_col  = (long)col[i].D();
				errorRgn.m_r    = (long)radius[i].D() +5;
				pData->m_errorRgns.push_back(errorRgn);
			}
		}
		
	}
	catch (...) 
	{
		//if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"HorizonSeamDetect01SheetIron parameter values error,please re-adjust");
			#else
			write_string(pData->m_ShowHWindow,"HorizonSeamDetect01罐身横边检测算子调整出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		
	}	
}


