// pyVerticalSeamDetect01.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "pyVerticalSeamDetect01.h"

using namespace std;
using namespace Halcon;

#ifndef DLLEXPT
#define DLLEXPT __declspec (dllexport)
#endif
#define Pi 3.1415926
CDoProcess::CDoProcess()
{
	printf("SheetIronDetect  Function\r\n");
	m_ProcessName="SheetIronDetect  TEST";

	//m_Parameters.DefaultWidth  = 4096;
}

void CDoProcess::SetParmeter(string parm, string value)
{
	if (!_stricmp(parm.c_str(),"List_Value"))
	{
		if(!_stricmp(value.c_str(),"Reg01"))
		{
			m_ListReg = REG01;
		}
		if(!_stricmp(value.c_str(),"Reg04"))
		{
			m_ListReg = REG04;
		}
		if(!_stricmp(value.c_str(),"Reg07"))
		{
			m_ListReg = REG07;
		}
	}

	// ADD  pt1 and pt2
	if("hwidth_offset"== parm)
		m_Parameters.hwidth_offset = atoi(value.c_str());

	if("hheight_offset"== parm)
		m_Parameters.hheight_offset = atoi(value.c_str());

	if("templateSize"== parm)
		m_Parameters.templateSize = atoi(value.c_str());

	if("tmpDynThreshold"== parm)
		m_Parameters.tmpDynThreshold = atoi(value.c_str());

	if("tmpRegShap_min"== parm)
		m_Parameters.tmpRegShap_min = atoi(value.c_str());
}

void CDoProcess::DoProcess(CMData* pData, SubTestResult *testItem)
{	
	try
	{

		currentImg = pData->m_Image;
		get_image_size(currentImg, &currentImg_Width, &currentImg_Height);  

		//  REVISED FOF NEW LOCATION METHOD
		pt1_row  = pData->m_center_y;
		pt1_col  = pData->m_center_x;
		pt1_phi  = pData->m_orientationPhi;
		pt1_len1 = pData->m_vseam1_len1;
		pt1_len2 = pData->m_vseam1_len2;

		pt2_row  = pData->m_center_y2;
		pt2_col  = pData->m_center_x2;
		pt2_phi  = pData->m_orientationPhi3;
		pt2_len1 = pData->m_vseam7_len1;
		pt2_len2 = pData->m_vseam7_len2;

		if (!(currentImg_Width<DefaultWidth))
		{
			pt3_row  = pData->m_center_y3;
			pt3_col  = pData->m_center_x3;
			pt3_phi  = pData->r_real;
			pt3_len1 = pData->m_vseam4_len1;
			pt3_len2 = pData->m_vseam4_len2;

		}

		HTuple testCol, testWidth;
		switch(m_ListReg)
		{
		case REG01:
			tmpRow    = pt1_row;
			tmpColumn = pt1_col;
			tmpPhi    = pt1_phi;
			tmplen1   = pt1_len1 + m_Parameters.hwidth_offset;
			tmplen2   = pt1_len2 + m_Parameters.hheight_offset;
			break;

		case REG04:
			tmpRow    = pt3_row;
			tmpColumn = pt3_col;
			tmpPhi    = pt3_phi;
			tmplen1   = pt3_len1 + m_Parameters.hwidth_offset;
			tmplen2   = pt3_len2 + m_Parameters.hheight_offset;
			break;

		case REG07:
			tmpRow    = pt2_row;
			tmpColumn = pt2_col;
			tmpPhi    = pt2_phi;
			tmplen1   = pt2_len1 + m_Parameters.hwidth_offset;
			tmplen2   = pt2_len2 + m_Parameters.hheight_offset;
			break;

		}
		
		gen_rectangle2(&tmpRectangle,tmpRow,tmpColumn,tmpPhi,tmplen1,tmplen2); 
		if(pData->m_isDebug)
			disp_obj(tmpRectangle,pData->m_ShowHWindow);
		reduce_domain(currentImg,tmpRectangle,&ImageReduced2);
				
		//----------------------------
		mean_image(ImageReduced2, &ImageMean, m_Parameters.templateSize, m_Parameters.templateSize);
		dyn_threshold(ImageReduced2, ImageMean, &RegionDynThresh1, m_Parameters.tmpDynThreshold, "dark");
		//----------------------------
		connection(RegionDynThresh1, &tmpConDefect);
		select_shape(tmpConDefect, &tmpSelected_defect, "area", "and", m_Parameters.tmpRegShap_min, 9999999);	
		count_obj(tmpSelected_defect, &tmpErrorNum);
		if (0 != tmpErrorNum)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;

			//if (pData->isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(tmpSelected_defect,pData->m_ShowHWindow);
			}
			
			HTuple areaSize,row,col;
			area_center(tmpSelected_defect,&areaSize,&row,&col);

			HTuple radius;
			tuple_sqrt(areaSize/PI, &radius);
			
			ERROR_RGN_INFO errorRgn;
			for(int i = 0; i<tmpErrorNum ;i++)
			{
				errorRgn.m_row  = (long)row[i].D();
				errorRgn.m_col  = (long)col[i].D();
				errorRgn.m_r    = (long)radius[i].D();
				pData->m_errorRgns.push_back(errorRgn);
			}

		}

	}
	catch (...) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
#ifdef ENGLISH_VERSION
			write_string(pData->m_ShowHWindow,"SheetIron parameter values error,please re-adjust");
#else
			write_string(pData->m_ShowHWindow,"罐身焊缝检测算子RegionDetect_v03程序参数值出错,请重新调节参数");
#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		
	}	
}

