// CPGDianWeiSHM.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"



#include "CPGShapeMatching2.1Sub.h"
#include "../Inc/MData.h"
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
	ShowObject=false;
	HException::InstallHHandler(&MyHalconExceptionHandler);
}


void CDoProcess::SetParmeter(string parm,string value)
{
	if(parm=="SHOWOBJECT")
	{
		if (value=="YES")
		{
			ShowObject = true;
		}
		else
		{
			ShowObject = false;
		}
	}

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atof(value.c_str());

	if(parm=="ROIWidth")
		m_Parameters.ROIWidth = atoi(value.c_str());

	if(parm=="Minscore")
		m_Parameters.Minscore = atof(value.c_str());

	if(parm=="Greediness")
		m_Parameters.Greediness = atof(value.c_str());

	if(!_stricmp(parm.c_str(),"MODEL_REGIST_LOAD"))
	{
		m_Parameters.modelName = value+".shm";
		if (!_access(m_Parameters.modelName.c_str(),0))
			read_shape_model(m_Parameters.modelName.c_str(),&m_Parameters.ModelID);

		else
		{

			//#ifdef _ENGLISH
			//			CString msg = _T("Cannot find Main Model File. Please Reselect");
			//			MessageBox(NULL,msg,_T("Main Model File Reading Error"),MB_OK);
			//#else
			//			CString msg = _T("主要模板文件未找到,请重新选择");
			//			MessageBox(NULL,msg,_T("主要模板文件读取错误"),MB_OK);
			//#endif

			m_Parameters.ModelID=-1;
		}
	}



	if(parm=="MinscoreSub")
		m_Parameters.MinscoreSub = atof(value.c_str());

	if(parm=="GreedinessSub")
		m_Parameters.GreedinessSub = atof(value.c_str());

	if(parm=="LayerSub")
		m_Parameters.LayerSub = atoi(value.c_str());

	if(!_stricmp(parm.c_str(),"MODEL_REGIST_LOAD_SUB"))
	{
		m_Parameters.modelNameSub = value+".shm";
		if (!_access(m_Parameters.modelNameSub.c_str(),0))

			read_shape_model(m_Parameters.modelNameSub.c_str(),&m_Parameters.ModelIDSub);

		else
		{

//#ifdef _ENGLISH
//			CString msg = _T("Cannot find Minor Model File. Please Reselect");
//			MessageBox(NULL,msg,_T("Minor Model File Reading Error"),MB_OK);
//#else
//			CString msg = _T("次要模板文件未找到,请重新选择");
//			MessageBox(NULL,msg,_T("次要模板文件读取错误"),MB_OK);
//#endif

			m_Parameters.ModelIDSub=-1;
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

			set_color(pData->m_ShowHWindow,"orange");
			set_tposition( pData->m_ShowHWindow,120, 0);

			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub Main Model File Reading Error");
			#else
						write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub主要模板文件读取错误");
			#endif
				/*return;*/

		}

		if(m_Parameters.ModelIDSub==-1)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"orange");
			set_tposition( pData->m_ShowHWindow,140, 0);

			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub Minor Model File Reading Error");
			#else
						write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub次要模板文件读取错误");
			#endif
				return;

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

		find_shape_model(ImageTest,m_Parameters.ModelID, HTuple(0).Rad(), HTuple(360).Rad(), 
			m_Parameters.Minscore, 1, 0.5, "least_squares", 0, m_Parameters.Greediness, &Rowfind, &Columnfind, &OrientationPhi, 
			&Scorefind);


		//if (pData->m_isDebug)
		//{
		//	set_color(pData->m_ShowHWindow,"red");	
		//	disp_cross(pData->m_ShowHWindow, Rowfind, Columnfind, 10, 0);
		//}

		Hlong length;
		tuple_length(OrientationPhi,&length);
		if(0==length)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"pink");
			set_tposition( pData->m_ShowHWindow,120, 0);

			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub Main Model Matching Fail");
			#else
						write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub主要模板匹配错误");
			#endif

			return;

		}

		pData->m_orientationPhi =OrientationPhi[0].D();
        pData->m_center_y2 = Rowfind[0].D();
		pData->m_center_x2 = Columnfind[0].D();
 

		find_shape_model(ImageTest,m_Parameters.ModelIDSub, HTuple(0).Rad(), HTuple(360).Rad(), 
			m_Parameters.MinscoreSub, 1, 0.5, "least_squares", m_Parameters.LayerSub, m_Parameters.GreedinessSub, &Rowfind, &Columnfind, &OrientationPhi, 
			&Scorefind);


		//if (pData->m_isDebug)
		//{
		//	set_color(pData->m_ShowHWindow,"red");	
		//	disp_cross(pData->m_ShowHWindow, Rowfind, Columnfind, 10, 0);
		//}

		tuple_length(OrientationPhi,&length);
		if(0==length)
		{
			pData->m_isFail =true;
			testItem->m_bFailSubTest = true;

			set_color(pData->m_ShowHWindow,"pink");
			set_tposition( pData->m_ShowHWindow,140, 0);

#ifdef _ENGLISH
			write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub Minor Model Matching Fail");
#else
			write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub次要模板匹配错误");
#endif

			return;

		}

		pData->m_orientationPhi3 =OrientationPhi[0].D();
		pData->m_center_y3 = Rowfind[0].D();
		pData->m_center_x3 = Columnfind[0].D();




	}
	catch (HException &except) 
	{
		if (pData->m_isDebug)
		{
			set_color(pData->m_ShowHWindow,"green");
			set_tposition( pData->m_ShowHWindow,25, 145);
			#ifdef _ENGLISH
						write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub parameter values error,please re-adjust");
			#else
						write_string(pData->m_ShowHWindow,"CPGShapeMatching2.1Sub程序参数值出错,请重新调节参数");
			#endif
		}
		pData->m_isFail =true;
		testItem->m_bFailSubTest = true;
		pData->m_orientationPhi=0;
		pData->m_orientationPhi3=0;
	}
}


