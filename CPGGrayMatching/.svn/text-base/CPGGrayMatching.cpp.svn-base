// CPGGrayMatching.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"



#include "CPGGrayMatching.h"
#include "..\Inc\MData.h"
#include <io.h>
#include <tchar.h>

#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

// exception handler
void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}

CDoProcess::CDoProcess()
{
	//m_ProcessName ="QinanHuanTest";
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

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atof(value.c_str());

	if(parm=="ROIWidth")
		m_Parameters.ROIWidth = atoi(value.c_str());

	if(parm=="Score")
		m_Parameters.Score = atof(value.c_str());


	if(!_stricmp(parm.c_str(),"MODEL_REGIST_LOAD"))
	{
		m_Parameters.modelName = value+".ncm";
		if (!_access(m_Parameters.modelName.c_str(),0))

			read_ncc_model(m_Parameters.modelName.c_str(),&m_Parameters.ModelID);

		else
		{

			#ifdef _ENGLISH
					wstring msg = _T("Model File Not find. Please Reselect");
					MessageBox(NULL,msg.c_str(),_T("File Reading Error"),MB_OK);
			#else
					wstring msg = _T("模板文件未找到,请重新选择");
					MessageBox(NULL,msg.c_str(),_T("文件读取错误"),MB_OK);
			#endif

			m_Parameters.ModelID=-1;
		}
	}
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{

		Hobject  ModelCircle,ModelDomain;

		HTuple   OrientationPhi;
		if(m_Parameters.ModelID==-1)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			set_color(pData->m_ShowHWindow,"red");
			set_tposition( pData->m_ShowHWindow,160, 0);

			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"File Reading Error");
			#else
						write_string(pData->m_ShowHWindow,"文件读取错误");
			#endif
		}


		Hobject image = pData->m_Image;
		Hobject  ROI,Circle1,Circle2,ContCircle1,ContCircle2,ContCircle;

		if((pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth)>0)
		{
			gen_circle(&Circle1, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out));
			gen_circle(&Circle2, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out-m_Parameters.ROIWidth));
			difference(Circle1, Circle2, &ROI);

			if (pData->m_isDebug&&ShowObject)
			{
				set_color(pData->m_ShowHWindow,"yellow");	
				disp_obj(Circle1,pData->m_ShowHWindow);
				set_color(pData->m_ShowHWindow,"yellow");	
				disp_obj(Circle2,pData->m_ShowHWindow);
			}

		}
		else
		{
			gen_circle(&ROI, pData->m_center_y, pData->m_center_x,(pData->r_real+m_Parameters.Regional_Out));

			if (pData->m_isDebug&&ShowObject)
			{
				set_color(pData->m_ShowHWindow,"yellow");	
				disp_obj(ROI,pData->m_ShowHWindow);
			}
		}
	
		//*======================================================================================================
  
			Hobject ImageTest;
			
			reduce_domain(image, ROI, &ImageTest);

		HTuple Rowfind,Columnfind,Scorefind;
//HTuple t1,t2,t3;
//count_seconds(&t1);
		find_ncc_model(ImageTest,  m_Parameters.ModelID, HTuple(0).Rad(), HTuple(360).Rad(), m_Parameters.Score, 1, 
			0.5, "true", 0, &Rowfind, &Columnfind, &OrientationPhi, &Scorefind);
//count_seconds(&t2);		
//	t3=t2-t1;
//
//
//	t3 = HTuple("find_ncc_model=") + HTuple(1000*(t2 - t1))  + HTuple("ms");
//				set_color(pData->m_ShowHWindow,"red");	
//	set_tposition( pData->m_ShowHWindow, 30, 200);				
//	write_string(pData->m_ShowHWindow,t3);


		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"red");	
			disp_cross(pData->m_ShowHWindow, Rowfind, Columnfind, 10, 0);
		}

		Hlong length;
		tuple_length(OrientationPhi,&length);
		if(0==length)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;
			if (pData->m_isDebug)
			{
				set_color(pData->m_ShowHWindow,"red");
				set_tposition( pData->m_ShowHWindow,160, 0);

				#ifdef _ENGLISH
							write_string(pData->m_ShowHWindow,"Matching Fail");
				#else
							write_string(pData->m_ShowHWindow,"匹配错误");
				#endif
			}
			return;
		}

		pData->m_orientationPhi =OrientationPhi[0].D();


	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"CPGGrayMatching parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"CPGGrayMatching程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail = true;
		pData->m_orientationPhi=0;
		testItem->m_bFailSubTest = true;
	}
}
