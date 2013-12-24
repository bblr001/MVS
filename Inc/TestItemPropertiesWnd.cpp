
#include "stdafx.h"

#include "TestItemPropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "AOIEdit.h"

#include "MCtrlCenter.h"
#include "customproperties.h"
#include "DrawRegistDialog.h"
#include "MCtrlCenter.h"
#include <fstream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
using namespace std;

// exception handler
void MyHalconExceptionHandler(const Halcon::HException& except)
{
	throw except;	
}
/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CTestItemPropertiesWnd::CTestItemPropertiesWnd()
{
	m_CurrentData=NULL;
	m_bChanged=0;
	m_bDraw=false;
	HException::InstallHHandler(&MyHalconExceptionHandler);

	QueryPerformanceFrequency(&large_interger);  
	dff = large_interger.QuadPart; 
	LastTime=0;


}

CTestItemPropertiesWnd::~CTestItemPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CTestItemPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES_APPLY, OnAddTestList)
	//ON_COMMAND(ID_PROPERTIES_SAVE, OnSaveTestList)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CTestItemPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient,rectCombo;
	GetClientRect(rectClient);

	//m_wndObjectCombo.GetWindowRect(&rectCombo);

	int cyCmb = 0;//rectCombo.Size().cy;
	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	//m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), 200, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + cyCmb + cyTlb, rectClient.Width(), rectClient.Height() -(cyCmb+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}


void CTestItemPropertiesWnd::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rectProp;
	m_wndPropList.GetWindowRect(rectProp);
	ScreenToClient(rectProp);

	rectProp.InflateRect(1, 1);
	dc.Draw3dRect(rectProp, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CTestItemPropertiesWnd::EnableTools(bool disableTools)
{
	m_wndToolBar.EnableWindow(disableTools);
}

int CTestItemPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->dwExStyle =WS_CHILD | WS_VISIBLE ;
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

// 	// 创建组合:
 	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
 
//  	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
//  	{
//  		TRACE0("未能创建属性组合 \n");
//  		return -1;      // 未能创建
//  	}
// 
//  	m_wndObjectCombo.AddString(_T("应用程序"));
//  	m_wndObjectCombo.AddString(_T("属性窗口"));
//  	m_wndObjectCombo.SetFont(CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT)));
//  	m_wndObjectCombo.SetCurSel(0);

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	//SetPropertyList();

 	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_ITEMPROPERTIES_TOOLS);
 	m_wndToolBar.LoadToolBar(IDR_ITEMPROPERTIES_TOOLS, 0, 0, TRUE /* 已锁定*/);
 	m_wndToolBar.CleanUpLockedImages();
 	m_wndToolBar.LoadBitmap(IDB_ITEMPROPERTIES_TOOLS_HC, 0, 0, TRUE /* 锁定*/);
 
 	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS );
 //	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
 	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);
	AdjustLayout();
	return 0;
}

void CTestItemPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}


void CTestItemPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}


void CTestItemPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CTestItemPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CTestItemPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* pCmdUI)
{
}

// void CTestItemPropertiesWnd::OnSaveTestList()
// {
// 	m_wndPropList.RemoveAll();
// 	m_CurrentData=NULL;
// 	m_wndPropList.EnableHeaderCtrl(FALSE);
// 	m_wndPropList.EnableDescriptionArea();
// 	m_wndPropList.SetVSDotNetLook();
// 	m_wndPropList.MarkModifiedProperties();
// }

void CTestItemPropertiesWnd::OnAddTestList()
{
	if (m_CurrentData==NULL)
	{
		return;
	}
	if (!(m_CurrentData->GetType()==SUBTEST))
	{
		return;
	}

	CMainFrame* pMainFrame= (CMainFrame*)AfxGetMainWnd();
	STLSDATA_SUBTEST *subTest = m_CurrentData->GetDataSubtest();
	subTest->RunTest = "Yes";

	pMainFrame->SetTestListWnd(m_CurrentData);
	pMainFrame->ReflashTestListWnd(subTest->order);
	m_wndPropList.RemoveAll();
	m_CurrentData=NULL;
	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	
}

void CTestItemPropertiesWnd::SetPropertyList(CTlsData* pData)
{
	m_CurrentData = pData;
	SetPropListFont();
	m_wndPropList.RemoveAll();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	//m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();


	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Property"));
	
	switch (pData->GetType())
	{
	case COMMON:
		{
			STLSDATA_COMMON* pCommon = pData->GetDataCommon();

			for (map<string,string>::iterator proIt = pCommon->property.begin();proIt!=pCommon->property.end();proIt++)
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
	case TEST:
		{
			STLSDATA_TEST* pTest = pData->GetDataTest();
			CString help(pTest->helpDesc.c_str());
			for (map<string,string>::iterator proIt = pTest->property.begin();proIt!=pTest->property.end();proIt++)
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
	case ROOT:
		{
			STLSDATA_ROOT* pRoot = pData->GetDataRoot();
			CString name(pRoot->name.c_str());
			CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("RootName"), name, _T("Root Infomation"));
			pProp->Enable(FALSE);
			pGroup1->AddSubItem(pProp);

			m_wndPropList.AddProperty(pGroup1);
			break;
		}
	case SUBTEST:
		{
			STLSDATA_SUBTEST* pSubtest = pData->GetDataSubtest();
			CString help(pSubtest->helpDesc.c_str());

			CString value = (s2ws(pSubtest->testName)).c_str();
			CMFCPropertyGridProperty* pTestProp = new CMFCPropertyGridProperty(_T("TestName"), value, help);			
			value = (s2ws(pSubtest->subTestName)).c_str();
			CMFCPropertyGridProperty* pSubTestProp = new CMFCPropertyGridProperty(_T("SubTestName"),value , help);
			eUSER_GROUP group = CMConfigCenter::GetConfigCenter().GetUserGroup();
			switch(group)
			{
			case OPERATOR:
				pTestProp->Enable(FALSE);
				pSubTestProp->Enable(FALSE);
				break;
			case ENGUSER:
				pTestProp->Enable(TRUE);
				pSubTestProp->Enable(TRUE);
				break;
			case ADMIN:
				pTestProp->Enable(TRUE);
				pSubTestProp->Enable(TRUE);
				break;
			case SADMIN:
				pTestProp->Enable(TRUE);
				pSubTestProp->Enable(TRUE);
				break;
			}
			pGroup1->AddSubItem(pTestProp);
			pGroup1->AddSubItem(pSubTestProp);

			for (map<string,string>::iterator proIt = pSubtest->property.begin();proIt!=pSubtest->property.end();proIt++)
			{
				CString name((*proIt).first.c_str());
				CString value((*proIt).second.c_str());				
				CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(name, value, help);
				pProp->Enable(FALSE);
				pGroup1->AddSubItem(pProp);
			}
			m_wndPropList.AddProperty(pGroup1);

			list<STLSDATA_PARAMETER*> parameter = pSubtest->parameter;

			int max=100,min=10;
			for (list<STLSDATA_PARAMETER*>::iterator parameterIt = parameter.begin();parameterIt!=parameter.end();parameterIt++)
			{
				CString parameterName((*parameterIt)->parameterName.c_str());
				CString parameterDesc((*parameterIt)->parameterDesc.c_str());
				CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(parameterDesc);

				CString InterFace;
				CString UserPower;
				
				CMFCPropertyGridProperty* pProperty = new CMFCPropertyGridProperty(_T("属性"));

				for (map<string,string>::iterator propertyit = (*parameterIt)->property.begin();propertyit!=(*parameterIt)->property.end();propertyit++)
				{
					CString name((*propertyit).first.c_str());
					CString value((*propertyit).second.c_str());				
	
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

					CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(name, value, help);
					
					pProp->Enable(FALSE);
					pProperty->AddSubItem(pProp);
					pProperty->Expand(FALSE);

				}

				pGroup2->AddSubItem(pProperty);

				if (UserPower.MakeUpper()=="GURU")
				{
					eUSER_GROUP group = CMConfigCenter::GetConfigCenter().GetUserGroup();
					switch(group)
					{
					case OPERATOR:
						{
							continue;
							break;
						}
					case ENGUSER:
						{
							continue;
							break;
						}
					case ADMIN:
						{
							continue;
							break;
						}
					}

				}

				CString helpDescription((*parameterIt)->helpDesc.c_str());
				if (!InterFace.CompareNoCase(_T("iint")))
				{
					CString value((*parameterIt)->settingValue.c_str());
					long settingv=_ttoi(value);
					if (settingv<min)
					{
						settingv=min;
					}
					if (settingv>max)
					{
						settingv=max;
					}

					CSliderProp *sliderProp = new CSliderProp(parameterName, (long)settingv, helpDescription,true);
					sliderProp->SetRang(min,max);
					eUSER_GROUP group = CMConfigCenter::GetConfigCenter().GetUserGroup();
					switch(group)
					{
					case OPERATOR:
						sliderProp->Enable(FALSE);
						break;
					case ENGUSER:
						sliderProp->Enable(TRUE);
						break;
					case ADMIN:
						sliderProp->Enable(TRUE);
						break;
					}
					pGroup2->AddSubItem(sliderProp);
				}
				else if(!InterFace.CompareNoCase(_T("ifloat")))
				{
					CString value((*parameterIt)->settingValue.c_str());
					float settingv=_tstof(value);
					if (settingv<min)
					{
						settingv=min;
					}
					if (settingv>max)
					{
						settingv=max;
					}
					CSliderProp *sliderProp = new CSliderProp(parameterName, settingv, helpDescription);
					sliderProp->SetRang(min,max);
					eUSER_GROUP group = CMConfigCenter::GetConfigCenter().GetUserGroup();
					switch(group)
					{
					case OPERATOR:
						sliderProp->Enable(FALSE);
						break;
					case ENGUSER:
						sliderProp->Enable(TRUE);
						break;
					case ADMIN:
						sliderProp->Enable(TRUE);
						break;
					case SADMIN:
						sliderProp->Enable(TRUE);
						break;
					}
					pGroup2->AddSubItem(sliderProp);
				}
				else if(!InterFace.CompareNoCase(_T("ilist")))
				{

					CString value((*parameterIt)->settingValue.c_str());
					
					CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(parameterName , value,helpDescription);

					for(list<string>::iterator it = (*parameterIt)->valueList.begin();it!=(*parameterIt)->valueList.end();it++)
					{

						pProp->AddOption(s2ws(*it).c_str());
					}
// 					pProp->AddOption(_T("None"));
// 
// 					pProp->AddOption(_T("Thin"));
// 
// 					pProp->AddOption(_T("Resizable"));
// 
// 					pProp->AddOption(_T("Dialog Frame"));

					pProp->AllowEdit(FALSE);



// 					CString value((*parameterIt)->settingValue.c_str());
// 					float settingv=_tstof(value);
// 					if (settingv<min)
// 					{
// 						settingv=min;
// 					}
// 					if (settingv>max)
// 					{
// 						settingv=max;
// 					}
// 					CStringList lstIconNames;   
// 					lstIconNames.AddTail (_T("Icon 1"));   
// 					lstIconNames.AddTail (_T("Icon 2"));   
// 					lstIconNames.AddTail (_T("Icon 3"));   
// 					lstIconNames.AddTail (_T("Icon 4"));   
// 					lstIconNames.AddTail (_T("Icon 5"));   
// 					lstIconNames.AddTail (_T("Icon 6"));   
// 					lstIconNames.AddTail (_T("Icon 7"));   
// 					lstIconNames.AddTail (_T("Icon 8"));   
// 					lstIconNames.AddTail (_T("Icon 9"));   
// 					lstIconNames.AddTail (_T("Icon 10"));   
// 					lstIconNames.AddTail (_T("Icon 11")); 
// 					CIconListProp *comboxProp = new CIconListProp(parameterName, 0,&lstIconNames);
// 					eUSER_GROUP group = CMConfigCenter::GetConfigCenter().GetUserGroup();
// 					switch(group)
// 					{
// 					case OPERATOR:
// 						comboxProp->Enable(FALSE);
// 						break;
// 					case ENGUSER:
// 						comboxProp->Enable(TRUE);
// 						break;
// 					case ADMIN:
// 						comboxProp->Enable(TRUE);
// 						break;		
// 					case SADMIN:
// 						comboxProp->Enable(TRUE);
// 						break;
// 					}
 					pGroup2->AddSubItem(pProp);
				}
				else if(!InterFace.CompareNoCase(_T("iobject")))
				{
					CString value((*parameterIt)->settingValue.c_str());
					CTwoButtonsProp *ButtonProp = new CTwoButtonsProp(parameterName, value,helpDescription,this);
					eUSER_GROUP group = CMConfigCenter::GetConfigCenter().GetUserGroup();
					switch(group)
					{
					case ENGUSER:
						ButtonProp->Enable(TRUE);
						break;
					case ADMIN:
						ButtonProp->Enable(TRUE);
						break;
					case SADMIN:
						ButtonProp->Enable(TRUE);
						break;

					default:
						ButtonProp->Enable(FALSE);
						break;
					}
					pGroup2->AddSubItem(ButtonProp);
				}
				else if(!InterFace.CompareNoCase(_T("iobjectcreate")))
				{
					CString value((*parameterIt)->settingValue.c_str());
					CCreateButtonsProp *ButtonProp = new CCreateButtonsProp(parameterName, value,helpDescription,this);
					eUSER_GROUP group = CMConfigCenter::GetConfigCenter().GetUserGroup();
					switch(group)
					{
					case ENGUSER:
						ButtonProp->Enable(TRUE);
						break;
					case ADMIN:
						ButtonProp->Enable(TRUE);
						break;
					case SADMIN:
						ButtonProp->Enable(TRUE);
						break;
					default:
						ButtonProp->Enable(FALSE);
						break;
					}
					pGroup2->AddSubItem(ButtonProp);
				}
				else if(!InterFace.CompareNoCase(_T("iobjectload")))
				{
					CString value((*parameterIt)->settingValue.c_str());
					CLoadButtonsProp *ButtonProp = new CLoadButtonsProp(parameterName, value,helpDescription,this);
					eUSER_GROUP group = CMConfigCenter::GetConfigCenter().GetUserGroup();
					switch(group)
					{
					case ENGUSER:
						ButtonProp->Enable(TRUE);
						break;
					case ADMIN:
						ButtonProp->Enable(TRUE);
						break;
					case SADMIN:
						ButtonProp->Enable(TRUE);
						break;
					default:
						ButtonProp->Enable(FALSE);
						break;
					}
					pGroup2->AddSubItem(ButtonProp);
				}
				else
				{
					continue;
				}
				
				this->SetWindowText((s2ws(pSubtest->testName)).c_str());
				m_wndPropList.SetFocus();
				m_wndPropList.AddProperty(pGroup2);
			}
			
			break;
		}
	}
}

void CTestItemPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CTestItemPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CTestItemPropertiesWnd::SetPropListFont()
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

void CTestItemPropertiesWnd::OnClickCreateButton(CString strValue,CCreateButtonsProp* button)
{
	if ((CMConfigCenter::GetConfigCenter().GetWorkModel()!=DEBUG_MODEL)&&(CMConfigCenter::GetConfigCenter().GetStates()!=MTI_GUI_RUN))
	{
		AfxMessageBox(_T("请在Debug 模式下并Run后进行测试"));
		return;
	}

	CFileDialog   SaveRegDlg(FALSE,NULL, _T("mymodel.shm"),OFN_OVERWRITEPROMPT, _T("Test Regist File(*.shm)|*.shm"));//save   as 
	CString defPath;
	defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(CMConfigCenter::GetConfigCenter().GetProgramName())).c_str());
	SaveRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(SaveRegDlg.DoModal()==IDOK) 
	{ 
		//button->SetValue(SaveRegDlg.GetFileName());
		button->SetValue(defPath+_T("\\")+SaveRegDlg.GetFileTitle());

	}
	SaveRegDlg.DestroyWindow();
}

void CTestItemPropertiesWnd::OnClickLoadButton(CString strValue,CLoadButtonsProp* button)
{
	if ((CMConfigCenter::GetConfigCenter().GetWorkModel()!=DEBUG_MODEL)&&(CMConfigCenter::GetConfigCenter().GetStates()!=MTI_GUI_RUN))
	{
		AfxMessageBox(_T("请在Debug 模式下并Run后进行测试"));
		return;
	}
	CFileDialog   OpenRegDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test Model File(*.shm)|*.shm"));//save   as 
	CString defPath;
	defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(CMConfigCenter::GetConfigCenter().GetProgramName())).c_str());
	OpenRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(OpenRegDlg.DoModal()==IDOK) 
	{ 
		button->SetValue(defPath+OpenRegDlg.GetFileTitle());
// 		read_region(&regist,(ws2s(fileName)).c_str());
// 		disp_obj(regist,CMConfigCenter::GetConfigCenter().GetShowWindowHID());

	}
	OpenRegDlg.DestroyWindow();

}


void CTestItemPropertiesWnd::OnClickLeftButton(CString strValue,CTwoButtonsProp* button)
{
	if ((CMConfigCenter::GetConfigCenter().GetWorkModel()!=DEBUG_MODEL)&&(CMConfigCenter::GetConfigCenter().GetStates()!=MTI_GUI_RUN))
	{
		AfxMessageBox(_T("请在Debug 模式下并Run后进行测试"));
		return;
	}
	CFileDialog   OpenRegDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test Regist File(*.reg)|*.reg"));//save   as 
	CString defPath;
	defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(CMConfigCenter::GetConfigCenter().GetProgramName())).c_str());
	OpenRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(OpenRegDlg.DoModal()==IDOK) 
	{ 

		button->SetValue(defPath+OpenRegDlg.GetFileTitle());

		Hobject regist;
		wstring fileName = OpenRegDlg.GetPathName().GetBuffer();
		
		
		read_region(&regist,(ws2s(fileName)).c_str());
		disp_obj(regist,CMConfigCenter::GetConfigCenter().GetShowWindowHID());
		
	}
	OpenRegDlg.DestroyWindow();

}
void CTestItemPropertiesWnd::OnClickRightButton(CString strValue,CTwoButtonsProp* button)
{
	if ((CMConfigCenter::GetConfigCenter().GetWorkModel()!=DEBUG_MODEL)&&(CMConfigCenter::GetConfigCenter().GetStates()!=MTI_GUI_RUN))
	{
		AfxMessageBox(_T("请在Debug 模式下并Run后进行测试"));
		return;
	}
	if(m_bDraw)
	{
		return;
	}

	Hobject image;
	HTuple  Row1, Column1, Row2, Column2;

	CMData *pData;
	if (CMConfigCenter::GetConfigCenter().GetHasFrame())
	{
		pData = CMCtrlCenter::GetCtrlCenter().GetFrameFromReport();
	}
	else
	{
		AfxMessageBox(_T("请先读取图片再在图片上进行检测区域选择"));
		return;
	}

	if (pData->OrientationPhi ==0||pData->Center_x == 100||pData->Center_y==100)
	{
		AfxMessageBox(_T("请先进行找圆心及定位的算子"));
		return;
	}

	m_bDraw=true;
	CDrawRegistDialog drawRegist;
	if (drawRegist.DoModal()!=IDOK)
	{
		drawRegist.DestroyWindow();
		delete drawRegist;
		m_bDraw=false;
		return;
	}

	switch(CMConfigCenter::GetConfigCenter().GetDrawSharp())
	{
		case DRAW_CIRCLE:
			{
				try
				{
					double Row, Column, R;
					draw_circle(CMConfigCenter::GetConfigCenter().GetShowWindowHID(),&Row, &Column, &R);
					gen_circle(&image,Row, Column, R);
					break;
				}
				catch (HException &except) 
				{
					//AfxMessageBox(_T("Drow Region Error."));
				}
			}
		case DRAW_ELLIPSE:
			{
				try
				{
					double Row, Column, Phi, Radius1, Radius2;
					draw_ellipse(CMConfigCenter::GetConfigCenter().GetShowWindowHID(),&Row, &Column, &Phi, &Radius1, &Radius2);
					gen_ellipse(&image,Row, Column, Phi, Radius1, Radius2);
					break;
				}
				catch (HException &except) 
				{
					//AfxMessageBox(_T("Drow Region Error."));
				}
			}
			
		case DRAW_RECTANGLE:
			{
				try
				{
					double Row1, Column1,Row2, Column2;
					draw_rectangle1(CMConfigCenter::GetConfigCenter().GetShowWindowHID(),&Row1, &Column1,&Row2, &Column2);
					gen_rectangle1(&image,Row1,Column1,Row2,Column2);
					break;		
				}
				catch (HException &except) 
				{
					//AfxMessageBox(_T("Drow Region Error."));
				}
			}
		case DRAW_POLYGON:
			{
				try
				{
					draw_region(&image,CMConfigCenter::GetConfigCenter().GetShowWindowHID());

					break;
				}
				catch (...) 
				{
					//AfxMessageBox(_T("Drow Region Error."));
				}
					//draw_polygon(&image,CMConfigCenter::GetConfigCenter().GetShowWindowHID());

				
			}
		default:
			return;
	}

	//clear_window(CMConfigCenter::GetConfigCenter().GetShowWindowHID());
 	//disp_obj(image,CMConfigCenter::GetConfigCenter().GetShowWindowHID());

	CFileDialog   SaveRegDlg(FALSE,NULL, _T("myregion.reg"),OFN_OVERWRITEPROMPT, _T("Test Regist File(*.reg)|*.reg"));//save   as 
	CString defPath;
	defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(CMConfigCenter::GetConfigCenter().GetProgramName())).c_str());
	SaveRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(SaveRegDlg.DoModal()==IDOK) 
	{ 
		wstring tmp(SaveRegDlg.GetPathName());
		string fileName= ws2s(tmp);
		//button->SetValue(SaveRegDlg.GetFileName());
		button->SetValue(defPath+_T("\\")+SaveRegDlg.GetFileTitle());
		//*strValue = tmp.c_str();
		write_region(image,fileName.c_str());
		
		
		defPath.Format(_T("d:\\SLACTST\\%s\\%s.dat"),(s2ws(CMConfigCenter::GetConfigCenter().GetProgramName())).c_str(),SaveRegDlg.GetFileTitle());

// 		StoredModePhi = -0.213736;
// 		StoredModelCenterRow = 267.512;
// 		StoredModelCenterColumn = 414.091;
		
		CString Data;
		Data.Format(_T("%f"),pData->OrientationPhi);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModePhi"),Data,defPath); 

		Data.Format(_T("%f"),(float)pData->Center_y);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterRow"),Data,defPath); 

		Data.Format(_T("%f"),(float)pData->Center_x);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredModelCenterColumn"),Data,defPath); 


		Data.Format(_T("%f"),(float)pData->r_real);
		WritePrivateProfileString(_T("StoredDATA"),_T("StoredRadius"),Data,defPath); 


	}
	SaveRegDlg.DestroyWindow();
	m_bDraw=false;
}

LRESULT CTestItemPropertiesWnd::OnPropertyChanged( WPARAM,LPARAM lParam )
{

	QueryPerformanceCounter(&large_interger);  
	nowTime = large_interger.QuadPart;  

	if ( ((nowTime - LastTime) * 1000 / dff) <= 300)
		return 0;

	QueryPerformanceCounter(&large_interger);  
	LastTime = large_interger.QuadPart; 

	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;

	switch (m_CurrentData->GetType())
	{	

	case SUBTEST:
		{
			CString name=_T("TestName");
			if (pProp->GetName()==name)
			{
				const COleVariant &strValue=pProp->GetValue();//获得子项值
				CStringW strTmp =(CStringW)strValue;
				CStringA strTmpa(strTmp.GetBuffer(0)); 
				strTmp.ReleaseBuffer();
				m_CurrentData->GetDataSubtest()->testName = 	strTmpa.GetBuffer(0);

				
				CMainFrame* pMainFrame= (CMainFrame*)AfxGetMainWnd();
				pMainFrame->ReflashTestListWnd(m_CurrentData->GetDataSubtest()->order);
				break;
			}

			name=_T("SubTestName");
			if (pProp->GetName()==name)
			{
				const COleVariant &strValue=pProp->GetValue();//获得子项值
				CStringW strTmp =(CStringW)strValue;
				CStringA strTmpa(strTmp.GetBuffer(0)); 
				strTmp.ReleaseBuffer();
				m_CurrentData->GetDataSubtest()->subTestName = 	strTmpa.GetBuffer(0);
				CMainFrame* pMainFrame= (CMainFrame*)AfxGetMainWnd();
				pMainFrame->ReflashTestListWnd(m_CurrentData->GetDataSubtest()->order);
				break;
			}


			STLSDATA_SUBTEST* pSubtest = m_CurrentData->GetDataSubtest();
			list<STLSDATA_PARAMETER*> parameter = pSubtest->parameter;
			for (list<STLSDATA_PARAMETER*>::iterator parameterIt = parameter.begin();parameterIt!=parameter.end();parameterIt++)
			{
				CString name((*parameterIt)->parameterName.c_str());
				if(pProp->GetName()==name)
				{
//  					CStringW oldValue((*parameterIt)->settingValue.c_str());
//  					AfxMessageBox(oldValue);

					const COleVariant &strValue=pProp->GetValue();//获得子项值
					CStringW strTmp =(CStringW)strValue;
					CStringA strTmpa(strTmp.GetBuffer(0)); 
					strTmp.ReleaseBuffer();
					(*parameterIt)->settingValue = 	strTmpa.GetBuffer(0);
// 					CString newValue(((*parameterIt)->settingValue.c_str()));
// 					AfxMessageBox(newValue);
					if(CMConfigCenter::GetConfigCenter().GetStates()==MTI_GUI_RUN)
					{
						if (CMConfigCenter::GetConfigCenter().GetSource()==FILE_SOURCE)
						{
							//if ((time(NULL)-m_tm)>1)
							{
								CMConfigCenter::GetConfigCenter().SetWorkModel(DEBUG_MODEL);
								CMCtrlCenter::GetCtrlCenter().UpdateTestItemParmeter();
								CMCtrlCenter::GetCtrlCenter().RecvOneFrame();
							}
							//m_tm = time(NULL);
						}
						if (CMConfigCenter::GetConfigCenter().GetSingleFrameModel())
						{
							if(CMConfigCenter::GetConfigCenter().GetHasFrame())
							{
								//if ((time(NULL)-m_tm)>1)
								{
									CMConfigCenter::GetConfigCenter().SetWorkModel(DEBUG_MODEL);
									CMCtrlCenter::GetCtrlCenter().UpdateTestItemParmeter();
									CMCtrlCenter::GetCtrlCenter().RecvOneFrame();
								}
								//m_tm = time(NULL);

							}
						}

					}
				}
			}

			break;
		}
	}
	return 0;
}



