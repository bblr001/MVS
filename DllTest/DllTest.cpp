// DllTest.cpp : 定义 DLL 应用程序的导出函数。
//


#include "stdafx.h"
#include "dllTest.h"
#include <stdio.h>
#include <iostream>
//#include <Windows.h>
#include <tchar.h>
#include <io.h>

using namespace std;

#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

CDoProcess::CDoProcess()
{
	ShowObject=false;
}

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

	if(!_stricmp(parm.c_str(),"TEST_REGIST"))
	{
		string regname = value+".reg";
		if (!_access(regname.c_str(),0))
			read_region(&m_Parameters.Test_Regist,value.c_str());
		else
		{
			wstring msg = _T("Dll Set Test Regist Error.Can't read file");
			//msg +=value;
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

		}
// 		StoredModePhi = -0.213736;
// 		StoredModelCenterRow = 267.512;
// 		StoredModelCenterColumn = 414.091;

		if (!_stricmp(parm.c_str(),"LIST_TEST"))
		{
			if(!_stricmp(value.c_str(),"XMAX"))
			{
				m_Parameters.iList = XMAX;
			}
			if(!_stricmp(value.c_str(),"YMAX"))
			{
				m_Parameters.iList = YMAX;
			}
			if(!_stricmp(value.c_str(),"XMIN"))
			{
				m_Parameters.iList = XMIN;
			}
			if(!_stricmp(value.c_str(),"YMIN"))
			{
				m_Parameters.iList = YMIN;
			}
		}
		
		
	}
}

void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	//printf("Dll Call Do Process Function");
	//printf("x=%d y=%d",m_Parameters.x,m_Parameters.y);

	Hobject image = pData->m_Image;

	// 将检测区域定义成Object 合并到ProcessImage
	//Regional_Internal
	

	// 	  //*第五部分读取区域与转换区域

//  	 StoredModePhi = -0.213736;
//  	 StoredModelCenterRow = 267.512;
//  	 StoredModelCenterColumn = 414.091;
	  ////*以下数据固定，这些数据是在第一次创建模型时所得的铆钉中心位置以及拉环区域所对应的角度
	  ////*当创建以下三个固定参数时，必须同时建立模型，使得模型与旋转参数一一对应
	HTuple    HomMat2DRotate;
	Hobject  RegionAffineTrans;
	vector_angle_to_rigid(StoredModelCenterRow, StoredModelCenterColumn, StoredModePhi,pData->m_center_y, pData->m_center_x,  pData->m_orientationPhi
		, &HomMat2DRotate);
	affine_trans_region(m_Parameters.Test_Regist, &RegionAffineTrans, HomMat2DRotate, "false");
	
	//if (ShowObject&&pData->m_isDebug)
	{
		set_color(pData->m_ShowHWindow,"red");
		disp_obj(RegionAffineTrans,pData->m_ShowHWindow);	
	}
	
	

	 ////*第五部分读取区域与转换区域
	  //read_region(&OutputOwnMadeRegion, "E:/Halcon/001.reg");
	  //affine_trans_region(OutputOwnMadeRegion, &RegionAffineTrans, HomMat2DRotate, "false");
	  //if (HDevWindowStack::IsOpen())
	  //disp_obj(RegionAffineTrans, HDevWindowStack::GetActive());


	int b,c;
	c=1.569;
	for(int i=0; i<10;i++)
		for(int j=0; j<10;j++)
			for(int x=0; x<28;x++)
				for(int y=0; y<10;y++)
				{
					b = i+j+x+y;
					double d=b/c;
					//Sleep(1);
					//std::cout<<d<<b;
					//printf("x=%d y=%d",d,b);
				}
	c=b;

// 	Hobject  MianXinMean, MianXinDynThresh, MianXinConnected;
// 	Hobject  OrientationInterested, OrientationDilation, OrientationSelected;
// 	Hobject  OrientationUnion, OutputOwnMadeRegion;
// 
// 
// 	// Local control variables 
// 	HTuple  Index, Width, Height, WindowHandle, CenterRow;
// 	HTuple  CenterColumn, CenterRadius, OrientationPhi, StoredModePhi;
// 	HTuple  StoredModelCenterRow, StoredModelCenterColumn;



	pData->m_isFail = true;
	testItem->m_bFailSubTest = true;


	switch(m_Parameters.iList)
	{
		case XMAX:
			{

				break;
			}
		case YMAX:
			{

				break;
			}
		case XMIN:
			{

				break;
			}
		case YMIN:
			{
				break;
			}
	}
}