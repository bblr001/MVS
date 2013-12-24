// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "AOIEditVer3.h"

#include "customproperties.h"
#include "DrawRegionDlg.h"
#include "MCtrlCenter.h"
#include <fstream>
#include <assert.h>
#include <atlconv.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable: 4001)
/////////////////////////////////////////////////////////////////////////////
void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}
/////////////////////////////////////////////////////////////////////////////

CPropertiesWnd::CPropertiesWnd(int nPaneType):
    m_pConfigCenter(CMConfigCenter::GetSingletonConfigCenter()),
    m_pCtrlCenter(CMCtrlCenter::GetSingletonCtrlCenter()),
	m_nPaneType(nPaneType),
	m_CurrentData(nullptr),
	m_pLightCtrlParam(nullptr),
	m_pTestNamePro(nullptr),
	m_pSubtestNamePro(nullptr)
{
	assert(m_pConfigCenter != nullptr);
	assert(m_pCtrlCenter != nullptr);
	HException::InstallHHandler(&MyHalconExceptionHandler);

	QueryPerformanceFrequency(&large_interger);  
	dff = large_interger.QuadPart; 
	LastTime=0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTY_ADD_BTN, OnAddTestList)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);
	int cyCmb = 0;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width()-1, rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(IDR_PROPERTIES, 0, 0, TRUE);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);
	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);
	InitPropList();
	AdjustLayout();
	SetControlBarStyle(AFX_CBRS_RESIZE|AFX_CBRS_AUTOHIDE|AFX_CBRS_FLOAT);
	return 0;
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook(FALSE);
	m_wndPropList.MarkModifiedProperties();
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* pCmdUI)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnAddTestList()
{
	if(m_nPaneType == LIGHT_PANE)
	{
		return;
	}
	if (m_CurrentData == nullptr || m_CurrentData->GetType() != SUBTEST)
	{
		return;
	}
	CMainFrame* pMainFrame= (CMainFrame*)AfxGetMainWnd();
	STLSDATA_SUBTEST *subTest = m_CurrentData->GetDataSubtest();
	subTest->RunTest = "Yes";

 	pMainFrame->SetTestListWnd(m_CurrentData);
 	pMainFrame->ReflashTestListWnd(subTest->order);
	m_wndPropList.RemoveAll();
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	m_wndToolBar.EnableWindow(FALSE);
}

void CPropertiesWnd::SetPropertyList(CTlsData* pData)
{
	m_wndToolBar.EnableWindow(TRUE);
 	m_CurrentData = pData;
 	InitPropList();
    m_wndPropList.RemoveAll();
	m_wndPropList.MarkModifiedProperties();
 	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Property"));
 	
 	switch (pData->GetType())
 	{
#pragma region COMMON case
 	case COMMON:
 		{
 			STLSDATA_COMMON* pCommon = pData->GetDataCommon();
 			for (auto proIt = pCommon->property_.begin();proIt!=pCommon->property_.end();proIt++)
 			{
 				CString name((*proIt).first.c_str());
 				CString value((*proIt).second.c_str());
 				CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(name, value, _T("Common Infomation"));
 				pProp->Enable(FALSE);
 				pGroup1->AddSubItem(pProp);
 			}
 			m_wndPropList.AddProperty(pGroup1);
 			break;
 		}
#pragma endregion COMMON case

#pragma region TEST case
 	case TEST:
 		{
 			STLSDATA_TEST* pTest = pData->GetDataTest();
 			CString help(pTest->helpDesc.c_str());
 			for (auto proIt = pTest->property_.begin();proIt!=pTest->property_.end();proIt++)
 			{
 				CString name((*proIt).first.c_str());
 				CString value((*proIt).second.c_str());				
 				CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(name, value, help);
 				pProp->Enable(FALSE);
 				pGroup1->AddSubItem(pProp);
 			}
 			m_wndPropList.AddProperty(pGroup1);
 			break;
 		}
#pragma endregion TEST case

#pragma region SUBTEST case
 	case SUBTEST: 
 		{
 			STLSDATA_SUBTEST* pSubtest = pData->GetDataSubtest();
			string str_tmp = pSubtest->helpDesc;
 			CString help(s2ws(str_tmp).c_str());

			str_tmp = pSubtest->testName;
 			CString value(s2ws(str_tmp).c_str());
			
 			CMFCPropertyGridProperty* pTestProp = new CMFCPropertyGridProperty(_T("TestName"), value, help);
			m_pTestNamePro = pTestProp;
 			value = s2ws(pSubtest->m_strSubTestName).c_str();
 			CMFCPropertyGridProperty* pSubTestProp = new CMFCPropertyGridProperty(_T("SubTestName"),value , help);
			m_pSubtestNamePro = pSubTestProp;
 			eUSER_GROUP group = m_pConfigCenter->GetUserGroup();
 			pTestProp->Enable(!(group == OPERATOR));
 			//pSubTestProp->Enable(!(group == OPERATOR));
			pSubTestProp->Enable(FALSE);
 			pGroup1->AddSubItem(pTestProp);
 			pGroup1->AddSubItem(pSubTestProp);
 			for (auto proIt = pSubtest->property_.begin();proIt!=pSubtest->property_.end();proIt++)
 			{
				string str_tmp=(*proIt).first;
 				CString name(s2ws(str_tmp).c_str());
				str_tmp = (*proIt).second;
 				CString value(s2ws(str_tmp).c_str());		

 				CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(name, value, help);
 				pProp->Enable(FALSE);
 				pGroup1->AddSubItem(pProp);
 			}
 			m_wndPropList.AddProperty(pGroup1);
 
			std::vector<STLSDATA_PARAMETER> parameter = pSubtest->m_vParameters;
 
 			int max = 100, min = 10;
 			for (auto parameterIt = parameter.begin();parameterIt!=parameter.end();parameterIt++)
 			{
				string str_tmp = (*parameterIt).parameterName;
 				CString parameterName = s2ws(str_tmp).c_str();
				str_tmp = (*parameterIt).parameterDesc;
				CString parameterDesc = s2ws(str_tmp).c_str();
				
				CString helpDescription = s2ws((*parameterIt).helpDesc).c_str();
				CString InterFace,UserPower;
 				for (auto propertyit = (*parameterIt).property_.begin();propertyit!=(*parameterIt).property_.end();propertyit++)
 				{
					string str_tmp = (*propertyit).first;
 					CString name = s2ws(str_tmp).c_str();
					str_tmp = (*propertyit).second;
					CString value = s2ws(str_tmp).c_str();
 					if (!name.CompareNoCase(_T("max")))
 					{
 						max = _ttoi(value);
 					}
 					if (!name.CompareNoCase(_T("min")))
 					{
 						min = _ttoi(value);
 					}
 					if (!name.CompareNoCase(_T("interface")))
 					{
 						InterFace = value;
 					}
					if (!name.CompareNoCase(_T("visibility")))
					{
						UserPower = value;
					}
				}

				//pGroup2->AddSubItem(pProperty);
				if (UserPower.MakeUpper()=="GURU")
				{
					eUSER_GROUP group = m_pConfigCenter->GetUserGroup();
					if(group != SADMIN)
					{
						
						continue;
					}
				}

				CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(parameterDesc);

 				if (!InterFace.CompareNoCase(_T("iint")))
 				{
					string str_tmp = (*parameterIt).settingValue;
 					CString value = s2ws(str_tmp).c_str();
 					long settingv=_ttoi(value);
 					if (settingv < min) settingv = min;
 					if (settingv > max) settingv = max;

 					CSliderProp *sliderProp = new CSliderProp(parameterName, (long)settingv, helpDescription,true);
 					sliderProp->SetRang(min,max);
 					eUSER_GROUP group = m_pConfigCenter->GetUserGroup();
					sliderProp->Enable(!(group == OPERATOR));
	
 					pGroup2->AddSubItem(sliderProp);
 				}
 				else if(!InterFace.CompareNoCase(_T("ifloat")))
 				{
					string str_tmp = (*parameterIt).settingValue;
					CString value = s2ws(str_tmp).c_str();
 					float settingv=_tstof(value);
 					if (settingv < min) settingv = min;
 					if (settingv > max) settingv = max;

 					CSliderProp *sliderProp = new CSliderProp(parameterName, settingv, helpDescription);
 					sliderProp->SetRang(min,max);
 					eUSER_GROUP group = m_pConfigCenter->GetUserGroup();
                    sliderProp->Enable(!(group == OPERATOR));
 					pGroup2->AddSubItem(sliderProp);
 				}
 				else if(!InterFace.CompareNoCase(_T("ilist")))
 				{
					string str_tmp = (*parameterIt).settingValue;
					CString value = s2ws(str_tmp).c_str();	
 					CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(parameterName , value,helpDescription);
 					for(auto it = (*parameterIt).valueList.begin();it!=(*parameterIt).valueList.end();it++)
 					{
 						pProp->AddOption(s2ws(*it).c_str());
 					}
  					pProp->AllowEdit(FALSE);
					eUSER_GROUP group = m_pConfigCenter->GetUserGroup();
                    pProp->Enable(!(group == OPERATOR));
  					pGroup2->AddSubItem(pProp);
 				}
 				else if(!InterFace.CompareNoCase(_T("iobject")))
 				{
					string str_tmp = (*parameterIt).settingValue;
					CString value = s2ws(str_tmp).c_str();
 					CTwoButtonsProp *ButtonProp = new CTwoButtonsProp(parameterName, value,helpDescription,this);
 					eUSER_GROUP group = m_pConfigCenter->GetUserGroup();
                    ButtonProp->Enable(!(group == OPERATOR));
 					pGroup2->AddSubItem(ButtonProp);
 				}
 				else if(!InterFace.CompareNoCase(_T("iobjectcreate")))
 				{
					string str_tmp = (*parameterIt).settingValue;
					CString value = s2ws(str_tmp).c_str();
 					CCreateButtonsProp *ButtonProp = new CCreateButtonsProp(parameterName, value,helpDescription,this);
 					eUSER_GROUP group = m_pConfigCenter->GetUserGroup();
                    ButtonProp->Enable(!(group == OPERATOR));
 					pGroup2->AddSubItem(ButtonProp);
 				}
 				else if(!InterFace.CompareNoCase(_T("iobjectload")))
 				{
					string str_tmp = (*parameterIt).settingValue;
					CString value = s2ws(str_tmp).c_str();
 					CLoadButtonsProp *ButtonProp = new CLoadButtonsProp(parameterName, value,helpDescription,this);
 					eUSER_GROUP group = m_pConfigCenter->GetUserGroup();
					ButtonProp->Enable(!(group == OPERATOR));
 					pGroup2->AddSubItem(ButtonProp);
 				}
 				else
 					continue;
				str_tmp = pSubtest->testName;
				CString value = s2ws(str_tmp).c_str();
 				this->SetWindowText(value);
 				m_wndPropList.SetFocus();
				m_wndPropList.AddProperty(pGroup2);
 			}
 			break;
 		}
#pragma endregion SUBTEST case
 	}

	m_pCtrlCenter->UpdateTestItemParameter();
	if(m_pConfigCenter->GetHasFrameFlag())
	{
		m_pCtrlCenter->RecvOneFrame();
	}
}

void CPropertiesWnd::SetLightParameters(std::vector<LightCtrlInfo>* pInfos)
{
	if(pInfos == nullptr || pInfos->empty())
		return;
	m_pLightCtrlParam = pInfos;

	m_wndToolBar.EnableWindow(TRUE);
	m_wndPropList.RemoveAll();
    InitPropList();

	USES_CONVERSION;

	for(size_t t = 0; t < pInfos->size(); ++t)
	{
		auto lightCtrlInfo = (*pInfos)[t];
		CString controllerName = A2CT(lightCtrlInfo.m_lightCtrlName.c_str());
		CMFCPropertyGridProperty* pController = new CMFCPropertyGridProperty(controllerName);
		m_wndPropList.AddProperty(pController);

		auto vParam = lightCtrlInfo.m_vParameters;
 		for (auto parameterIt = vParam.begin();parameterIt != vParam.end(); parameterIt++)
 		{
			string tmp = (*parameterIt).parameterDesc;
			CString parameterDesc = A2CT(tmp.c_str());

			tmp = (*parameterIt).parameterName;
			CString paramName = A2CT(tmp.c_str());
			
			tmp = (*parameterIt).helpDesc;
			CString helpDesc = A2CT(tmp.c_str());
			CMFCPropertyGridProperty* pParam = new CMFCPropertyGridProperty(parameterDesc);
			pController->AddSubItem(pParam);
 			CString InterFace;
			int max = 0;
			int min = 0;
			CString strInterface;
 			for (auto propertyit = (*parameterIt).property_.begin();propertyit != (*parameterIt).property_.end();propertyit++)
 			{
				string strTmp = (*propertyit).first;
 				CString name = A2CT(strTmp.c_str());
				strTmp = (*propertyit).second;
				CString value = A2CT(strTmp.c_str());
 				if (!name.CompareNoCase(_T("max")))
 				{
 					max = _ttoi(value);
 				}
 				if (!name.CompareNoCase(_T("min")))
 				{
 					min = _ttoi(value);
 				}
 				if (!name.CompareNoCase(_T("interface")))
 				{
 					strInterface = value;
 				}
			}

			if (!strInterface.CompareNoCase(_T("iint")) || !strInterface.CompareNoCase(_T("ifloat")))
 			{
				string strTmp = (*parameterIt).settingValue;
 				CString value = A2CT(strTmp.c_str());
 				long settingv = _ttoi(value);
 				if (settingv < min) settingv = min;
 				if (settingv > max) settingv = max;

 				CSliderProp *sliderProp = new CSliderProp(paramName, (long)settingv, helpDesc,true);
 				sliderProp->SetRang(min,max);
 				pParam->AddSubItem(sliderProp);
 			}
		}
	}

	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rectProp;
	m_wndPropList.GetWindowRect(rectProp);
	ScreenToClient(rectProp);

	rectProp.InflateRect(1, 1);
	dc.Draw3dRect(rectProp, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;
	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
}

void CPropertiesWnd::OnClickCreateButton(CString strValue,CCreateButtonsProp* button)
{
	if (!m_pConfigCenter->GetDebugModeFlag())
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("Please Run in Debug Model."));
#else
		AfxMessageBox(_T("请在Debug 模式下并Run后进行测试"));
#endif
		return;
	}

	CFileDialog   SaveRegDlg(FALSE,NULL, _T("mymodel.shm"),OFN_OVERWRITEPROMPT, _T("Test Regist File(*.shm)|*.shm"));//save   as 
	CString defPath;
	defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(m_pConfigCenter->GetProgramName())).c_str());
	SaveRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(SaveRegDlg.DoModal()==IDOK) 
	{ 
		//button->SetValue(SaveRegDlg.GetFileName());
		button->SetValue(defPath+_T("\\")+SaveRegDlg.GetFileTitle());

	}
	SaveRegDlg.DestroyWindow();
}

void CPropertiesWnd::OnClickLoadButton(CString strValue,CLoadButtonsProp* button)
{
	if (!m_pConfigCenter->GetDebugModeFlag())
	{
		#ifdef _ENGLISH
				AfxMessageBox(_T("Please Run in Debug Model."));
		#else
				AfxMessageBox(_T("请在Debug 模式下并Run后进行测试"));
		#endif

		return;
	}
	CFileDialog   OpenRegDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test Model File(*.shm)|*.shm"));//save   as 
	CString defPath;
	defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(m_pConfigCenter->GetProgramName())).c_str());
	OpenRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(OpenRegDlg.DoModal()==IDOK) 
	{ 
		button->SetValue(defPath+OpenRegDlg.GetFileTitle());
	}
	OpenRegDlg.DestroyWindow();

}

void CPropertiesWnd::OnClickLeftButton(CString strValue,CTwoButtonsProp* button)
{
	if (!m_pConfigCenter->GetDebugModeFlag())
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("Please Run in Debug Model."));
#else
		AfxMessageBox(_T("请在Debug 模式下并Run后进行测试"));
#endif

		return;
	}
	CFileDialog   OpenRegDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test Regist File(*.reg)|*.reg"));//save   as 
	CString defPath;
	defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(m_pConfigCenter->GetProgramName())).c_str());
	OpenRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(OpenRegDlg.DoModal()==IDOK) 
	{ 
		button->SetValue(defPath+OpenRegDlg.GetFileTitle());
		Hobject regist;
		wstring fileName = OpenRegDlg.GetPathName().GetBuffer();
		read_region(&regist,(ws2s(fileName)).c_str());
		set_color(m_pConfigCenter->GetShowWindowHID(),"red");
		disp_obj(regist,m_pConfigCenter->GetShowWindowHID());
	}
	OpenRegDlg.DestroyWindow();

}

void CPropertiesWnd::OnClickRightButton(CString strValue,CTwoButtonsProp* button)
{
	if (!m_pConfigCenter->GetDebugModeFlag())
	{
#ifdef _ENGLISH
		AfxMessageBox(_T("Please Run in Debug Model."));
#else
		AfxMessageBox(_T("请在Debug 模式下并Run后进行测试"));
#endif

		return;
	}
	CMData data;
	if (m_pConfigCenter->GetHasFrameFlag())
	{
		data = m_pCtrlCenter->GetFrameFromReport();
	}
	else
	{
		#ifdef _ENGLISH
				AfxMessageBox(_T("Please read the image and then tested on the image area selection."));
		#else
				AfxMessageBox(_T("请先读取图片再在图片上进行检测区域选择"));
		#endif


		return;
	}
	//if (data.m_orientationPhi ==0||data.m_center_x == 100||data.m_center_y==100)
	//{
	//	AfxMessageBox(_T("请先进行找圆心及定位的算子"));
	//	return;
	//}
	try
	{

		strValue += _T(".reg");
		wstring tmp = strValue.GetBuffer();
		read_region(&m_Region,ws2s(tmp).c_str());
		set_color( data.m_ShowHWindow,"red");
		disp_obj(data.m_Image,data.m_ShowHWindow);
		disp_obj(data.m_ErrorRegist,data.m_ShowHWindow);
		disp_obj(m_Region,data.m_ShowHWindow);

	}

	catch (HException &except) 
	{
		
		#ifdef _ENGLISH
				AfxMessageBox(_T("Read Region File Error"));
		#else
				AfxMessageBox(_T("读取区域文件错误"));
		#endif
		
	}

	CDrawRegionDlg* pToolDlg = new CDrawRegionDlg(m_Region);
	pToolDlg->Create(IDD_DIALOG_DRAW_SHAPE);
	pToolDlg->ShowWindow(SW_SHOW);
}

void CPropertiesWnd::OnLightParamPanePropertyChanged(LPARAM lParam)
{
	CSliderProp* pSlider = (CSliderProp*)lParam;
	CString paramName;

	USES_CONVERSION;

	if(m_pLightCtrlParam != nullptr && pSlider != nullptr)
	{
		int intensityValue = 0;
		int chIndex = -1;
		bool bIntensityChanged = false;
		paramName = pSlider->GetName();
		std::for_each(m_pLightCtrlParam->begin(), m_pLightCtrlParam->end(), [&](LightCtrlInfo& lightCtrlInfo)
		{
			if(m_pCtrlCenter->m_VLproxy.TryConnectToUSB())
			{
				for(auto it = lightCtrlInfo.m_vParameters.begin(); it != lightCtrlInfo.m_vParameters.end(); ++it)
				{
					if(paramName == A2CT((*it).parameterName.c_str()))
					{
						const COleVariant &oleValue = pSlider->GetValue();//获得子项值
 						CStringW strTmp = (CStringW)oleValue;
 						CString strValue = W2CT(strTmp); 
						(*it).settingValue = T2CA(strValue);
						intensityValue = (byte)_ttoi(strValue);
						chIndex = _ttoi(A2CT((*it).channelIndex.c_str()));
						try
						{
//  							CString msg;
//  							msg.Format(_T("lightCtrlInfo.m_iaddress =%i,chIndex = %i,intensityValue=%i "),lightCtrlInfo.m_iaddress,chIndex,intensityValue);
//  							AfxMessageBox(msg);
							byte err_code = m_pCtrlCenter->m_VLproxy.SelectAdd((byte)lightCtrlInfo.m_iaddress); //
 							err_code = m_pCtrlCenter->m_VLproxy.SetCHMode(chIndex, 1); // select channel to be adjusted
							m_pCtrlCenter->m_VLproxy.SetConstInt(intensityValue); // set intensity of the selected channel
						}
						catch(...)
						{
							//AfxMessageBox(_T("Error"));
							bIntensityChanged = false;
							m_pCtrlCenter->m_VLproxy.SetConnectedFlag(false);
							return;
						}
						bIntensityChanged = true;
					}
				}
			}
		});
		if(bIntensityChanged && pSlider->GetEndEditFlag())
		{
			m_pCtrlCenter->TriggerCamera();
			pSlider->SetEndEditFlag(false);
			bIntensityChanged = false;
		}
	}
}

void CPropertiesWnd::OnAlgorithmParamPanePropertyChanged(LPARAM lParam)
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;
	STLSDATA_SUBTEST* pSubtest = m_CurrentData->GetDataSubtest();
	if(m_CurrentData->GetType() == SUBTEST)
	{
		CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
		CString paramName = pProp->GetName();
 		if (paramName == _T("TestName"))
 		{
 			const COleVariant &strValue=pProp->GetValue();//获得子项值
 			CStringW strTmp = (CStringW)strValue;
 			CStringA strTmpa(strTmp.GetBuffer(0)); 
 			strTmp.ReleaseBuffer();
 			pSubtest->testName = strTmpa.GetBuffer(0);

 			pMainFrame->ReflashTestListWnd(pSubtest->order);
 		}
 		if (paramName ==  _T("SubTestName"))
 		{
 			const COleVariant &strValue=pProp->GetValue();//获得子项值
 			CStringW strTmp =(CStringW)strValue;
 			CStringA strTmpa(strTmp.GetBuffer(0)); 
 			strTmp.ReleaseBuffer();
 			pSubtest->m_strSubTestName = strTmpa.GetBuffer(0);
 			pMainFrame->ReflashTestListWnd(pSubtest->order);
 		}
		std::for_each(pSubtest->m_vParameters.begin(),pSubtest->m_vParameters.end(),[&](STLSDATA_PARAMETER& param)
		{
			CString name(s2ws(param.parameterName.c_str()).c_str());
			if(paramName == name)
			{
 				const COleVariant &strValue=pProp->GetValue();//获得子项值
 				CStringW strTmp =(CStringW)strValue;
 				CStringA strTmpa(strTmp.GetBuffer(0)); 
 				strTmp.ReleaseBuffer();
 				param.settingValue = strTmpa.GetBuffer(0);

 				m_pCtrlCenter->UpdateTestItemParameter(pSubtest->order,param.parameterName);
				if(m_pConfigCenter->GetHasFrameFlag())
				{
					CSliderProp* pSlider = dynamic_cast<CSliderProp*>(pProp);
					if(pSlider != nullptr && pSlider->GetEndEditFlag())
					{
						m_pCtrlCenter->RecvOneFrame();
						pSlider->SetEndEditFlag(false);
					}
				}
			}
		});
	}
}

LRESULT CPropertiesWnd::OnPropertyChanged( WPARAM,LPARAM lParam )
{
	if(m_nPaneType == ALGORITHM_PANE)
	{
		OnAlgorithmParamPanePropertyChanged(lParam);
	}
	if(m_nPaneType == LIGHT_PANE)
	{
		OnLightParamPanePropertyChanged(lParam);
	}
	return 0;
}

BOOL CPropertiesWnd::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	return CDockablePane::OnNotify(wParam, lParam, pResult);
}

HRESULT CPropertiesWnd::get_accSelection(VARIANT *pvarChildren)
{
	return CDockablePane::get_accSelection(pvarChildren);
}

void CPropertiesWnd::EnableEditTestName(BOOL flag)
{
	if(m_CurrentData == nullptr )
	{
		return;
	}
	if(m_pTestNamePro != nullptr)
	{
		m_pTestNamePro->AllowEdit(flag);
	}
	if(m_pSubtestNamePro != nullptr)
	{
		//m_pSubtestNamePro->AllowEdit(flag);
		m_pSubtestNamePro->AllowEdit(false);
	}
}
