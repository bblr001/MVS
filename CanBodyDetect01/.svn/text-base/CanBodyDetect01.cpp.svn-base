// CanBodyDetect01.cpp : 定义 DLL 应用程序的导出函数。
/*
	印刷片料罐身缺陷检测
	罐身检测 Reg1, Reg2
*/
#include "stdafx.h"
#include "CanBodyDetect01.h"
#include <time.h>
using namespace std;
using namespace Halcon;

#ifndef DLLEXPT
#define DLLEXPT __declspec (dllexport)
#endif

CDoProcess::CDoProcess()
{
	ShowObject = false;
}

void CDoProcess::SetParmeter(string parm, string value)
{
	if(parm=="SHOWOBJECT")
	{	if (value=="YES")
			ShowObject = true;
		else
			ShowObject = false;
	}

	if (!_stricmp(parm.c_str(),"List_Value"))
	{
		if(!_stricmp(value.c_str(),"Reg1"))
		{
			m_ListReg = REG_1;
		}
		if(!_stricmp(value.c_str(),"Reg2"))
		{
			m_ListReg = REG_2;
		}
	}

	if(parm=="Width_offset")
		m_Parameters.Width_offset = atoi(value.c_str());
	if(parm=="Height_offset")
		m_Parameters.Height_offset= atoi(value.c_str());
	if(parm=="MakeSize")
		m_Parameters.MakeSize = atoi(value.c_str());
	if(parm=="ThresholdValue")
		m_Parameters.ThresholdValue = atoi(value.c_str());
	if(parm=="ErrorSize")
		m_Parameters.ErrorSize = atoi(value.c_str());
	// 罐身缺印
	if(parm=="losePrintGrayValue")
		m_Parameters.losePrintGrayValue = atoi(value.c_str());

}

void CDoProcess::DoProcess(CMData* pData, SubTestResult *testItem)
{	
	try
	{
		switch(m_ListReg)
		{
		case REG_1:
			rect = pData->m_TestRegist1;
			
			break;
		case REG_2:
			rect = pData->m_TestRegist2;
			
			break;
		}
		
		HTuple Num;
		count_obj(rect, &Num);
		if(!Num)
			return ;
		
		erosion_rectangle1 (rect, &m_TestRegion, m_Parameters.Width_offset, m_Parameters.Height_offset);
			
		if (pData->m_isDebug && ShowObject)
		{
			disp_obj(m_TestRegion,pData->m_ShowHWindow);
		}

		change_domain(pData->m_Image, m_TestRegion, &MianXinDomain);
		mean_image(MianXinDomain, &ImageMean, m_Parameters.MakeSize, m_Parameters.MakeSize);
		dyn_threshold(MianXinDomain, ImageMean, &DynThresh, m_Parameters.ThresholdValue,"dark");
		connection(DynThresh,&ThreshConnect);
		select_shape(ThreshConnect, &PointDynThresh, "area", "and", m_Parameters.ErrorSize, 999999);
		count_obj(PointDynThresh, &Number);
		
		HTuple areaSize,row,col;
		HTuple radius;
		ERROR_RGN_INFO errorRgn;
		Hobject UnionErrRegion;
		if (0 != Number)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			 
			//if (pData->isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(PointDynThresh,pData->m_ShowHWindow);
				union2(pData->m_ErrorRegist, PointDynThresh, &UnionErrRegion);
				pData->m_ErrorRegist = UnionErrRegion;
			}
			
			area_center(PointDynThresh,&areaSize,&row,&col);
			tuple_sqrt(areaSize/PI, &radius);
			
			for(int i = 0; i<Number ;i++)
			{
				errorRgn.m_row  = (long)row[i].D();
				errorRgn.m_col  = (long)col[i].D();
				errorRgn.m_r    = (long)radius[i].D();
				pData->m_errorRgns.push_back(errorRgn);
			}
		}
		
		
		// 存在罐身缺印的情况
		// 罐身区域的大小--传递过来的罐身区域
		HTuple areasize, tmpRow, tmpCol;
		area_center(m_TestRegion, &areasize, &tmpRow, &tmpCol);

		fast_threshold(MianXinDomain, &testRegion, m_Parameters.losePrintGrayValue , 255, 10);
		
		Hobject connRegion;
		connection(testRegion, &connRegion);
		
		area_center(connRegion, &testArea, &testRow, &testColumn);
		tuple_length(testArea, &testNumber);

		Hobject losePrintRegion;
		gen_empty_obj(&losePrintRegion);

		int countErr = 0;
		for(int i=0; i<testNumber; i++)
		{
			if(testArea[i] > areasize*0.2)	
			{
				Hobject selectObj;
				select_obj(connRegion, &selectObj, i+1);	
				
				Hobject unionedObj;
				union2(losePrintRegion, selectObj, &losePrintRegion);
				union2(pData->m_ErrorRegist, selectObj, &UnionErrRegion);
				pData->m_ErrorRegist = UnionErrRegion;
				++countErr;
			}
		}

		if(countErr != 0)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;

			//if (pData->isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");
				disp_obj(testRegion,pData->m_ShowHWindow);
				pData->m_ErrorRegist = losePrintRegion;
			}
			
			area_center(losePrintRegion,&areaSize,&row,&col);
			tuple_sqrt(areaSize/PI, &radius);
			
			//for(int i = 0; i<testNumber ;i++)
			{
				errorRgn.m_row  = (long)row[0].D();
				errorRgn.m_col  = (long)col[0].D();
				errorRgn.m_r    = (long)radius[0].D();
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
						write_string(pData->m_ShowHWindow,"CanBodyDetect01 parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"CanBodyDetect01程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
	}	
}

