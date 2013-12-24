// zhujiao.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include "CPGDianWeiROI200Dll.h"
#include "..\Inc\MData.h"




#ifndef   DLLEXPT
#define DLLEXPT __declspec (dllexport )
#endif

CDoProcess::CDoProcess()
{
	m_ProcessName ="ZhouXianDianWei 200";

}



void CDoProcess::SetParmeter(string parm,string value)
{

	if(parm=="Thred_jiao")
		m_Parameters.Thred_jiao = atoi(value.c_str());
	if(parm=="Thred_no_jiao")
		m_Parameters.Thred_no_jiao= atoi(value.c_str());

	if(parm=="Regional_Internal")
		m_Parameters.Regional_Internal = atoi(value.c_str());

	if(parm=="Regional_Out")
		m_Parameters.Regional_Out = atoi(value.c_str());
}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	

	testItem->m_ErrorMsg = "No Error";
	//testItem->SubTestName = m_ProcessName;
	testItem->SubTestName = "ZhuJiaoTest";
	Hobject image=pData->m_Image;


	Hlong TxxError_jiao, TyyError_jiao; //out

	Hlong Txx,Tyy,TR;
	Txx = pData->Center_x;
	Tyy = pData->Center_y;
	TR = pData->r_real;


	// Local iconic variables 
	
	Hobject  MianXinCircle, MianXinDomain;
	Hobject  MianXinMean, MianXinDynThresh, MianXinConnected;
	Hobject  OrientationInterested, OrientationDilation, OrientationSelected;
	Hobject  OrientationUnion, OutputOwnMadeRegion, RegionAffineTrans;


	// Local control variables 
	HTuple  Index, Width, Height, WindowHandle, CenterRow;
	HTuple  CenterColumn, CenterRadius, OrientationPhi, StoredModePhi;
	HTuple  StoredModelCenterRow, StoredModelCenterColumn, HomMat2DRotate;


	gen_circle(&MianXinCircle, Tyy, Txx, 124);
	change_domain(image, MianXinCircle, &MianXinDomain);
	mean_image(MianXinDomain, &MianXinMean, 23, 23);
	dyn_threshold(MianXinDomain, MianXinMean, &MianXinDynThresh, 10, "light");
	connection(MianXinDynThresh, &MianXinConnected);

  //===================================================================
  //*第三部分选择拉环区域角度，以及计算仿射变换矩阵
  select_shape(MianXinConnected, &OrientationInterested, (HTuple("area").Append("rectangularity")),"and", (HTuple(200).Append(0.6)), (HTuple(500).Append(1)));
  dilation_circle(OrientationInterested, &OrientationDilation, 5.5);
  select_shape(OrientationDilation, &OrientationSelected, "outer_radius", "and", 30, 200);
  union1(OrientationSelected, &OrientationUnion);
  orientation_region(OrientationUnion, &OrientationPhi);
  pData->OrientationPhi = OrientationPhi;


  StoredModePhi = -0.213736;
  StoredModelCenterRow = 267.512;
  StoredModelCenterColumn = 414.091;
  //*以下数据固定，这些数据是在第一次创建模型时所得的铆钉中心位置以及拉环区域所对应的角度
  //*当创建以下三个固定参数时，必须同时建立模型，使得模型与旋转参数一一对应
  vector_angle_to_rigid(StoredModelCenterRow, StoredModelCenterColumn, StoredModePhi,CenterRow, CenterColumn, OrientationPhi, &HomMat2DRotate);
  //===================================================================


  ////*第五部分读取区域与转换区域
  //read_region(&OutputOwnMadeRegion, "E:/Halcon/001.reg");
  //affine_trans_region(OutputOwnMadeRegion, &RegionAffineTrans, HomMat2DRotate, "false");
  //if (HDevWindowStack::IsOpen())
  //disp_obj(RegionAffineTrans, HDevWindowStack::GetActive());





}