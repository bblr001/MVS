#include "stdafx.h"


#include "CPGDianWeiROI.h"
#include "..\Inc\MData.h"




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
	//m_ProcessName ="QinanHuanTest";
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

	if(parm=="MaskSize")
		m_Parameters.MaskSize = atoi(value.c_str());
	if(parm=="DynThreshold")
		m_Parameters.DynThreshold= ((float)(atoi(value.c_str())))/10.0;

	if(parm=="AreaLowlimit")
		m_Parameters.AreaLowlimit = atoi(value.c_str());

	if(parm=="AreaUpperLimit")
		m_Parameters.AreaUpperLimit = atoi(value.c_str());

	if(parm=="RECLowLimit")
		m_Parameters.RECLowLimit = ((float)(atoi(value.c_str())))/100.0;

	if(parm=="BlockRadiusLowLimit")
		m_Parameters.BlockRadiusLowLimit = atoi(value.c_str());

}


void CDoProcess::DoProcess(CMData* pData,SubTestResult *testItem)
{	
	try
	{
		Hobject image=pData->m_Image;

		double Txx,Tyy,TR;
		Txx = pData->m_center_x;
		Tyy = pData->m_center_y;
		TR = pData->r_real;

		// Local iconic variables 
		
		Hobject  MianXinCircle,MianXinCircle2,MianXinCircleDiff, MianXinDomain;
		Hobject  MianXinMean, MianXinDynThresh, MianXinConnected;
		Hobject  OrientationInterested, OrientationDilation, OrientationSelected;
		Hobject  OrientationUnion, OutputOwnMadeRegion, RegionAffineTrans;


		HTuple   OrientationPhi;
		HTuple   HomMat2DRotate;

		gen_circle(&MianXinCircle, Tyy, Txx, TR*0.65);
		gen_circle(&MianXinCircle2, Tyy, Txx, TR*0.25);
		difference(MianXinCircle,MianXinCircle2,&MianXinCircleDiff);

		change_domain(image, MianXinCircleDiff, &MianXinDomain);

		mean_image(MianXinDomain, &MianXinMean, m_Parameters.MaskSize, m_Parameters.MaskSize);
		dyn_threshold(MianXinDomain, MianXinMean, &MianXinDynThresh, m_Parameters.DynThreshold, "light");
		connection(MianXinDynThresh, &MianXinConnected);


	  //===================================================================
	  //*第三部分选择拉环区域角度，以及计算仿射变换矩阵
	  select_shape(MianXinConnected, &OrientationInterested, (HTuple("area").Append("rectangularity")),"and", (HTuple(m_Parameters.AreaLowlimit).Append(m_Parameters.RECLowLimit)), (HTuple(m_Parameters.AreaUpperLimit).Append(1)));
	  dilation_circle(OrientationInterested, &OrientationDilation, 5.5);
	  select_shape(OrientationDilation, &OrientationSelected, "outer_radius", "and", m_Parameters.BlockRadiusLowLimit, m_Parameters.BlockRadiusUpperLimit);
	  union1(OrientationSelected, &OrientationUnion);
	  orientation_region(OrientationUnion, &OrientationPhi);
	  if (pData->m_isDebug)
	  {
		  set_color(pData->m_ShowHWindow,"yellow");
		  disp_obj(MianXinCircle,pData->m_ShowHWindow);
		  set_color(pData->m_ShowHWindow,"green");
		  disp_obj(MianXinDynThresh,pData->m_ShowHWindow);
		  set_color(pData->m_ShowHWindow,"blue");
		  disp_obj(OrientationInterested,pData->m_ShowHWindow);
		  
		  set_color(pData->m_ShowHWindow,"red");
		  disp_obj(OrientationUnion,pData->m_ShowHWindow);
	  }


	  pData->m_orientationPhi = OrientationPhi[0].D();

	  //StoredModePhi = -0.213736;
	  //StoredModelCenterRow = 267.512;
	  //StoredModelCenterColumn = 414.091;
	  ////*以下数据固定，这些数据是在第一次创建模型时所得的铆钉中心位置以及拉环区域所对应的角度
	  ////*当创建以下三个固定参数时，必须同时建立模型，使得模型与旋转参数一一对应
	  //vector_angle_to_rigid(StoredModelCenterRow, StoredModelCenterColumn, StoredModePhi,pData->m_center_y, pData->m_center_x, OrientationPhi, &HomMat2DRotate);
	  ////===================================================================


	  ////*第五部分读取区域与转换区域
	  //read_region(&OutputOwnMadeRegion, "E:/Halcon/001.reg");
	  //affine_trans_region(OutputOwnMadeRegion, &RegionAffineTrans, HomMat2DRotate, "false");
	  //if (HDevWindowStack::IsOpen())
	  //disp_obj(RegionAffineTrans, HDevWindowStack::GetActive());
	}
	catch (HException &except) 
	{
		pData->m_isFail = true;
		pData->m_orientationPhi=0;
		testItem->m_bFailSubTest = true;
		set_tposition( pData->m_ShowHWindow, 55, 230);				
		write_string(pData->m_ShowHWindow,except.message);
	}
}