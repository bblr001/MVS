// CPGUVPuTu.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "CPGUVPuTu.h"
#include "../Inc/MData.h"

#include <stdio.h>
#include <iostream>
//#include <Windows.h>
#include <tchar.h>
#include <io.h>
using namespace std;
#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif


std::wstring s2ws(const std::string& s)
{
	wstring retwstr = _T("");
	size_t sz = s.size();
	if(sz <= 0) 
		return retwstr;

	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)s.c_str(),-1, 0, 0);
	if(nSize <= 0) 
		return retwstr;

	std::vector<wchar_t> pwszDst(nSize, 0);

	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)s.c_str(), sz, &pwszDst[0], nSize*sizeof(wchar_t));

	if( pwszDst[0] == 0xFEFF)
	{// skip Oxfeff
		retwstr.assign(pwszDst.begin() + 1, pwszDst.end());
	}
	else
	{
		retwstr.assign(pwszDst.begin(), pwszDst.end());
	}
	return retwstr;
}


// exception handler
void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;
}

CDoProcess::CDoProcess()
{
	ShowObject=false;
	HException::InstallHHandler(&MyHalconExceptionHandler);
}

void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="SHOWOBJECT")
		if (value=="YES")
		{
			ShowObject = true;
		}
		else
		{
			ShowObject = false;
		}
	if(parm=="Width")
		m_Parameters.Width = atoi(value.c_str());

	if(parm=="ThresholdValue")
		m_Parameters.ThresholdValue = ((float)(atof(value.c_str())));
	

	if(parm=="NumPart")
		m_Parameters.NumPart = atoi(value.c_str());

// 	if(parm=="Regional_Internal")
// 		m_Parameters.Regional_Internal = ((float)(atoi(value.c_str())))/10.0;
// 	//m_Parameters.Regional_Internal = -5;

	if(parm=="Thred_no_butu")
		m_Parameters.Thred_no_butu= atoi(value.c_str());

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = (atof(value.c_str()));
	//m_Parameters.Regional_Out = -1;

	if(parm=="Thred_Sing_MeanGray_LowLimit")
		m_Parameters.Thred_Sing_MeanGrayLowerLimit = (atoi(value.c_str()));
	

	

	if(!_stricmp(parm.c_str(),"NOTEST_REGIST"))
	{
		string regname = value+".reg";
		if (!_access(regname.c_str(),0))
			read_region(&m_Parameters.Test_Regist,value.c_str());
		else
		{
			wstring msg = _T("Set Test Regist Error.Can't read file");
			MessageBox(NULL,msg.c_str(),_T("ReadFile Error"),MB_OK);
		}

		string datname = value+".dat";
		if (!_access(datname.c_str(),0))
		{
			TCHAR vv[64];
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModePhi"),_T("0.0"),vv,sizeof(vv),(s2ws(datname)).c_str());
			StoredModePhi= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterRow"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredModelCenterRow= _tstof(vv);
			GetPrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterColumn"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredModelCenterColumn= _tstof(vv);

			GetPrivateProfileString(_T("StoredDATA"),_T("StoredRadius"),_T("0.0"),vv,sizeof(vv),s2ws(datname).c_str());
			StoredRadius= _tstof(vv);
		}
	}
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	try
	{
		Hobject image = pData->m_Image;
		HTuple  OuterJuanYuanWidth;

		HTuple ThresholdValue;//,ThresholdValue22;

		HTuple  NumPart;

		float Regional_Out;

		Regional_Out =pData->r_real+m_Parameters.Regional_Out;

		OuterJuanYuanWidth = m_Parameters.Width;

		NumPart = m_Parameters.NumPart;

		ThresholdValue = m_Parameters.ThresholdValue;
		HTuple errorValue;


		// 将检测区域定义成Object 合并到ProcessImage
		
		Hlong error_number; 
		error_number = 0;
	
	  HTuple  ResultID;//, PolarTransImageWidth22, PolarTransImageHeight22;
	  //HTuple  Mean22, Deviation22, Mean_Lenght22, Mean_deviation22;
	  //HTuple  Exp22, Abs22, AbsSorted22, LocationId22, Length22;
	  //HTuple  ResultID22;

	  	get_image_pointer1(image, &Pointer, &Type, &WidthOri, &HeightOri);

		HTuple    HomMat2DRotate;
		Hobject  RegionAffineTrans,region_tai;
		vector_angle_to_rigid(StoredModelCenterRow, StoredModelCenterColumn, StoredModePhi,pData->m_center_y, pData->m_center_x,  pData->m_orientationPhi
			, &HomMat2DRotate);
		affine_trans_region(m_Parameters.Test_Regist, &RegionAffineTrans, HomMat2DRotate, "false");

		HTuple HomMat2DIdentity,HomMat2DScale;
		HTuple AffineTransArea,AffineTransRow,AffineTransColumn;
		Hobject RegionScaleTrans;


		double Index=pData->r_real/StoredRadius;
		hom_mat2d_identity (&HomMat2DIdentity);

		area_center (RegionAffineTrans, &AffineTransArea, &AffineTransRow, &AffineTransColumn);

		hom_mat2d_scale (HomMat2DIdentity, Index, Index, AffineTransRow, AffineTransColumn, &HomMat2DScale);


		affine_trans_region (RegionAffineTrans, &RegionScaleTrans, HomMat2DScale, "false");

		//get_image_pointer1(image, &Pointer, &Type, &WidthOri, &HeightOri);

		gen_circle(&Circle1, HTuple(pData->m_center_y), HTuple(pData->m_center_x), HTuple(Regional_Out));
		gen_circle(&Circle2, HTuple(pData->m_center_y), HTuple(pData->m_center_x), (HTuple(Regional_Out)-OuterJuanYuanWidth));
		difference(Circle1, Circle2, &CheckRegion);

		intersection(CheckRegion,RegionScaleTrans,&RegionIntersection);
		difference(CheckRegion,RegionIntersection,&TestRegion);



		polar_trans_image_ext(image, &PolarTransImage, pData->m_center_y, pData->m_center_x, HTuple(360).Rad(), 
			0, HTuple(Regional_Out), HTuple(Regional_Out-OuterJuanYuanWidth),  (HTuple(360).Rad())*HTuple(Regional_Out), OuterJuanYuanWidth, "nearest_neighbor");


		Hobject CodeRegionCircular;
		polar_trans_region(TestRegion, &CodeRegionCircular, pData->m_center_y, pData->m_center_x, HTuple(360).Rad(), 
			0, HTuple(Regional_Out), HTuple(Regional_Out-OuterJuanYuanWidth), (HTuple(360).Rad())*HTuple(Regional_Out), OuterJuanYuanWidth,"nearest_neighbor");

		reduce_domain(PolarTransImage, CodeRegionCircular, &JuanYuanDomain);

		get_image_size(JuanYuanDomain, &PolarTransImageWidth, &PolarTransImageHeight);


		//计算区域平均灰度值. 并判断是否有补涂

		int tem=0;
		HTuple twidth = (HTuple(360).Rad()*Regional_Out);
		double tem_tu;
		double tem_nobutu=0;
		int count=0;
		for (int i=0; i<twidth[0].L();  i++)
		{
			for (int j=0; j< OuterJuanYuanWidth; j++)
			{
				get_grayval(JuanYuanDomain, j, i, &tem_tu);
				if (tem_tu==0)
				{
					continue;
				}
				tem = tem+tem_tu;
				count++;
			}
		}
		tem_nobutu=tem/count;
		if (tem_nobutu<m_Parameters.Thred_no_butu)
		{
			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");
				HTuple msg  = HTuple("No BuTu");
				set_tposition( pData->m_ShowHWindow, 35, 200);				
				write_string(pData->m_ShowHWindow,msg);
			}
			//return;
		}




		//mean_image(JuanYuanDomain1, &JuanYuanDomain, 3, 3);

		if (ShowObject&&pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"blue");	
			disp_obj(TestRegion,pData->m_ShowHWindow);
		}
		//*======================================================================================================
		//*测外圈卷边
		partition_rectangle(JuanYuanDomain, &JuanYuanPartitioned, PolarTransImageWidth/NumPart,PolarTransImageHeight);
		intensity(JuanYuanPartitioned, JuanYuanDomain, &Mean, &Deviation);
		tuple_length(Mean, &Mean_Lenght);
		Mean_deviation = HTuple();
		for (int i=0; i<=Mean_Lenght-2; i++)
		{
			if (HTuple(Mean[i+2])==0)
			{
				Mean_deviation[i] = 0;
				continue;
			}
			if (HTuple(Mean[i+1])==0)
			{
				Mean_deviation[i] = 0;
				continue;
			}

			if (i>1)
			{
				if (HTuple(Mean[i-1])==0)
				{
					Mean_deviation[i] = 0;
					continue;
				}
			}

 			if (i>2)
 			{
 				if (HTuple(Mean[i-2])==0)
 				{
 					Mean_deviation[i] = 0;
 					continue;
 				}
 			}

			if (Mean[i].D()<m_Parameters.Thred_no_butu)
			{
				Mean_deviation[i]=900;
				continue;
			}

			tuple_deviation(HTuple(Mean[i]).Concat(HTuple(Mean[i+1])), &Exp);
			Mean_deviation[i] = Exp;

		}

		tuple_abs(Mean_deviation, &Abs);
		tuple_sort(Abs, &AbsSorted);
		tuple_sort_index(Abs, &LocationId);
		tuple_length(Abs, &Length);
		errorValue = AbsSorted[Length-1];
		for (i=Length-1; i>=0; i+=-1)
		{
		  if (0 != (HTuple(AbsSorted[i])<m_Parameters.Thred_Sing_MeanGrayLowerLimit))
		  {
			//  errorValue = AbsSorted[i];
			if (0 != (i==(Length-1)))
			{
			  ResultID = HTuple();
			  break;
			}
			else
			{
			  tuple_last_n(LocationId, i+1, &ResultID);
			  break;
			}
		  }
		}
		ResultID += 1;
		select_obj(JuanYuanPartitioned, &ResultDefect, ResultID);
		polar_trans_region_inv(ResultDefect, &BackTransRegion, pData->m_center_y, pData->m_center_x, 
			HTuple(360).Rad(), 0, HTuple(Regional_Out), HTuple(Regional_Out)-OuterJuanYuanWidth, 
			(HTuple(360).Rad())*HTuple(Regional_Out), OuterJuanYuanWidth, WidthOri, HeightOri, 
			"nearest_neighbor");

		count_obj(BackTransRegion,&error_number);
		
		if (error_number)
		{

			pData->m_isFail = true;
			testItem->m_bFailSubTest = true;
			Hlong Area;
			double yy,xx;
			area_center(BackTransRegion,&Area,&yy,&xx);
			testItem->m_ErrorY = yy;
			testItem->m_ErrorX = xx;
			if (pData->m_isDebug)
			{			
				set_color(pData->m_ShowHWindow,"yellow");
				disp_obj(BackTransRegion,pData->m_ShowHWindow);		
			}
		}

	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		testItem->m_bFailSubTest = true;
		
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 200);
			write_string(pData->m_ShowHWindow,"CPGUVPuTu程序参数值出错,请重新调节参数");
		}
	}

  }
