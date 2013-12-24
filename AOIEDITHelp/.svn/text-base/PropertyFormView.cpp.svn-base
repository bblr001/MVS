// PropertyFormView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEDITHelp.h"
#include "PropertyFormView.h"
#include "AOIEDITHelpDoc.h"
#include "MainFrm.h"
#include "Resource.h"
#include "FileTree.h"
#include "ItemView.h"
#include ".\DoProcess\CMCfgCenter.h"
#include "Tools.h"
#include "customproperties.h"
#include ".\DoProcess\CMCtrolCenter.h"
#include "DrawRegistDialog.h"
#include <string>

// CPropertyFormView
std::wstring ItemLayerName[] = {L"TestName",L"m_strSubTestName"};
IMPLEMENT_DYNCREATE(CPropertyFormView, CFormView)
CPropertyFormView::CPropertyFormView()
	: CFormView(CPropertyFormView::IDD),m_bNewItem(false),sel_elem(0)
	,m_recvSource(NONE),m_pFunDllSetParameter(0),m_orderFun(0)
{

}

int CPropertyFormView::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CFormView::OnCreate(lpcs)==-1)
	{
		return -1;
	}
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}
	InitPropList();
	return 0;
}
void CPropertyFormView::OnDestroy()
{
	CFormView::OnDestroy();
}
CPropertyFormView::~CPropertyFormView()
{
}
void CPropertyFormView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	if (m_wndPropList.GetSafeHwnd())
	{
		CRect rc ;
		m_wndPropList.GetWindowRect( &rc ) ;
		ScreenToClient( &rc ) ;
		m_wndPropList.SetWindowPos( NULL, 4, 25, cx-8, cy - rc.top - 15,
			SWP_NOACTIVATE|SWP_NOZORDER ) ;
		if (m_BtnApp.GetSafeHwnd())
		{
			m_BtnApp.SetWindowPos( NULL, 4,2, cx-7,23,SWP_NOACTIVATE|SWP_NOZORDER);
		}
	}
}
WCHAR *CPropertyFormView::Ansi2WChar(LPCSTR pszSrc, int nLen)
{
	int nSize = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pszSrc, nLen, 0, 0);
	if(nSize <= 0) return NULL;

	WCHAR *pwszDst = m_MemString.GetBufferSetLength(nSize+1);
	if( NULL == pwszDst) return NULL;

	MultiByteToWideChar(CP_ACP, 0,(LPCSTR)pszSrc, nLen, pwszDst, nSize);
	pwszDst[nSize] = 0;
	if( pwszDst[0] == 0xFEFF)                    
		for(int i = 0; i < nSize; i ++) 
			pwszDst[i] = pwszDst[i+1]; 
	return pwszDst;
}
void CPropertyFormView::InitPropList()
{
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook(FALSE);
	m_wndPropList.MarkModifiedProperties();
}
void CPropertyFormView::SaveFile()
{
	  if(sel_elem)
	  {
		  SaveFineTuning(sel_elem);
	  }
}
void CPropertyFormView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	SetScrollSizes( MM_TEXT, CSize(1,1) ) ;
}
void CPropertyFormView::InitDataPropList(TiXmlElement* element)
{ 
    m_wndPropList.RemoveAll();
	CMFCPropertyGridProperty* pProp;
	CMFCPropertyGridProperty* pProp2;
    TiXmlElement*parent_elem = element->Parent()->ToElement();
	const char* nameDesc = "";
	TiXmlAttribute *attribute =0;
	if (parent_elem)
	{
        attribute = parent_elem->FirstAttribute();
		if(attribute)nameDesc = attribute->Value()==0?"":attribute->Value();
	}
	CString TestName(Ansi2WChar(nameDesc,strlen(nameDesc)));
    attribute = element->FirstAttribute();
	const char* nameType = element->Value();
	if(attribute)nameDesc = attribute->Value()==0?"":attribute->Value();
	m_strSubTestName = (Ansi2WChar(nameDesc,strlen(nameDesc)));
	m_BtnApp.SetWindowText( m_strSubTestName);
	if (strcmp(nameType,arrNameType[0])==0)
	{
		CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Property"));
		m_wndPropList.AddProperty(pGroup1);
		element = element->FirstChildElement();
		for (;element;element=element->NextSiblingElement())
		{
		  const char * name = element->Value();
		  const char * text = element->GetText();
		  const char *pv= "Common Infomation";
          attribute= element->FirstAttribute();
		  if(attribute)
		  {
            if(strcmp(attribute->Name(),"desc")==0)
			{
				pv = attribute->Value();
			}
		  }
		  pProp = new CMFCPropertyGridProperty(CString(Ansi2WChar(name,strlen(name))), \
			                                   CString(Ansi2WChar(text,strlen(text))), \
			                                   CString(Ansi2WChar(pv,strlen(pv))));
		  pProp->Enable(FALSE);
		  pGroup1->AddSubItem(pProp);
		}
	}
	else if (strcmp(nameType,arrNameType[1])==0)
	{
		CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("Property"));
		m_wndPropList.AddProperty(pGroup1);
		element = element->FirstChildElement();
		for (;element;element=element->NextSiblingElement())
		{
			const char * name = element->Value();
			if(strcmp(name,arrNameType[2])==0)continue;
			else{
				const char * text = element->GetText()==0?"":element->GetText();
				const char *pv= "Common Infomation";
				attribute= element->FirstAttribute();
				if(attribute)
				{
					if(strcmp(attribute->Name(),"desc")==0)
					{
						pv = attribute->Value();
					}
				}
				pProp = new CMFCPropertyGridProperty(CString(Ansi2WChar(name,strlen(name))), \
					CString(Ansi2WChar(text,strlen(text))), \
					CString(Ansi2WChar(text,strlen(text))));
				pProp->Enable(FALSE);
				pGroup1->AddSubItem(pProp);
			}
		}
	}
	else if (strcmp(nameType,arrNameType[2])==0)
	{
		TiXmlElement *_elem = element->LastChild("helpdescription")->ToElement();
		CString SubDesc;
		if(_elem)
		{
		   const char * name = _elem->GetText()==0?"":_elem->GetText();
           SubDesc = CString(Ansi2WChar(name,strlen(name)));
		}
		element = element->FirstChildElement();
		for (;element;element=element->NextSiblingElement())
		{
			const char * name = element->Value();
			if(strcmp(name,"parameter")==0)
			{
				TiXmlElement *_elem = element->LastChild("helpdescription")->ToElement();
				CString SubDesc;
				if(_elem)
				{
					const char * name = _elem->GetText()==0?"":_elem->GetText();
					SubDesc = CString(Ansi2WChar(name,strlen(name)));
				}
				const char * name_desc = "属性";
				const char * name_seting = "value";
				TiXmlAttribute *attri = element->FirstAttribute();
				for(;attri;attri=attri->Next()){
					if(strcmp(attri->Name(),"parameterDesc")==0)name_desc = attri->Value();
					else 
						if (strcmp(attri->Name(),"name")==0)
						{
							name_seting = attri->Value();
						}
				}
				TiXmlElement *elem_property = element->FirstChildElement();
				while (1)
				{
					const char * name = elem_property->Value();
					CString dataType;
					CString MinV;
					CString MaxV;
	
					if(strcmp(name,"property")==0)
					{
						
						CString UserPower;
						TiXmlElement *_elem = elem_property->FirstChildElement();
						for (;_elem;_elem=_elem->NextSiblingElement())
						{
							const char * name = _elem->Value();
							const char * text = _elem->GetText()==0?"":_elem->GetText();
							const char *pv= "";
							attribute= _elem->FirstAttribute();
							if(attribute)
							{
								if(strcmp(attribute->Name(),"desc")==0)
								{
									pv = attribute->Value();
								}
							}
						
							if(strcmp(name,"interface")==0)
							{
                               dataType = CString(Ansi2WChar(text,strlen(text))); 
							}
							else if(strcmp(name,"max")==0)
							{
                               MaxV = CString(Ansi2WChar(text,strlen(text)));
							}
							else if(strcmp(name,"min")==0)
							{
                              MinV = CString(Ansi2WChar(text,strlen(text)));
							}else if(strcmp(name,"visibility")==0)
							{

								UserPower = CString(Ansi2WChar(text,strlen(text)));
							}
						}
                        
						if (UserPower==_T("GURU"))
						{
							if (theApp.m_user!=L"sadmin")
							{
								break;
							}
						}
						CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(CString(Ansi2WChar(name_desc,strlen(name_desc))));
						m_wndPropList.AddProperty(pGroup1);


                        TiXmlElement *setting_elem = element->LastChild("setting")->ToElement();
						if(setting_elem){
							const char * value = "50";
							value = setting_elem->GetText()==0?"":setting_elem->GetText();
							CString settingV(Ansi2WChar(value,strlen(value)));
							if (dataType.CompareNoCase(_T("iint"))==0)
							{
								int min=10,max = 100,setting_value = 50;
								max = _ttoi(MaxV);
								min = _ttoi(MinV);
								setting_value = _ttoi(settingV);
								if (setting_value<min)
								{
									setting_value=min;
								}
								if (setting_value>max)
								{
									setting_value=max;
								}
								CSliderProp *sliderProp = new CSliderProp(CString(Ansi2WChar(name_seting,strlen(name_seting))), \
								(long)setting_value, CString(Ansi2WChar(name_desc,strlen(name_desc))),true);
								sliderProp->SetRang(min,max);
								pGroup1->AddSubItem(sliderProp);
								pGroup1->Expand(FALSE);

							}
							else if(!dataType.CompareNoCase(_T("ilist")))
							{
								CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(CString(Ansi2WChar(name_seting,strlen(name_seting))) , \
									settingV,CString(Ansi2WChar(name_desc,strlen(name_desc))));
								if (elem_property)
								{
                                      TiXmlElement *elem = elem_property->FirstChild("listvalue")->ToElement();
									  if (elem)
									  {
										  for (elem = elem->FirstChildElement();elem;elem=elem->NextSiblingElement())
										  {
											  pProp->AddOption(Ansi2WChar(elem->Value(),strlen(elem->Value())));
										  }
									  }
								}
								pProp->AllowEdit(FALSE);
								pGroup1->AddSubItem(pProp);
							}
							else if(!dataType.CompareNoCase(_T("ifloat")))
							{
								float min=10,max = 100,settingv = 50.0;
								max = _tstof(MaxV);
								min = _tstof(MinV);
								settingv =_tstof(settingV);
								if (settingv - min<0.01)
								{
									settingv=min;
								}
								if (max - settingv<0.01)
								{
									settingv=max;
								}
								CSliderProp *sliderProp = new CSliderProp(CString(Ansi2WChar(name_seting,strlen(name_seting))),\
																						settingv, CString(Ansi2WChar(name_desc,strlen(name_desc))));
								sliderProp->SetRang(min,max);
								pGroup1->AddSubItem(sliderProp);
							}
							else if(!dataType.CompareNoCase(_T("iobject")))
							{
								CTwoButtonsProp *ButtonProp = new CTwoButtonsProp(CString(Ansi2WChar(name_seting,strlen(name_seting))),\
																				settingV,CString(Ansi2WChar(name_desc,strlen(name_desc))),this);
								pGroup1->AddSubItem(ButtonProp);
							}
							else if(!dataType.CompareNoCase(_T("iobjectcreate")))
							{
								CCreateButtonsProp *ButtonProp = new CCreateButtonsProp(CString(Ansi2WChar(name_seting,strlen(name_seting))),\
									settingV,CString(Ansi2WChar(name_desc,strlen(name_desc))),this);
								pGroup1->AddSubItem(ButtonProp);
							}
							else if(!dataType.CompareNoCase(_T("iobjectload")))
							{
		
								CLoadButtonsProp *ButtonProp = new CLoadButtonsProp(CString(Ansi2WChar(name_seting,strlen(name_seting))),\
									settingV,CString(Ansi2WChar(name_desc,strlen(name_desc))),this);
								pGroup1->AddSubItem(ButtonProp);
							}
							else
							{
								// TODO:Cleanup all resources here
								continue;
							}
						
							pGroup1->Expand(TRUE);
						}
	
			        }
					
					elem_property=elem_property->NextSiblingElement();
					if(0==elem_property)break;
				}
			}
			else continue;
		}
	}
}
void CPropertyFormView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	if ( lHint & UPD_DBSELECTOBJECTVIEW)
	{
		BOOL _bFromFileTree = pSender->IsKindOf(RUNTIME_CLASS(CFileTree));
		BOOL _bFromItemList = pSender->IsKindOf(RUNTIME_CLASS(CItemView));
		if(_bFromFileTree||_bFromItemList)
		{
			if(_bFromFileTree)m_recvSource = eCFileTree;
			if(_bFromItemList)m_recvSource = eItemList;
			CAOIEDITHelpDoc* pDoc = GetDocument() ;
			if(eItemList==m_recvSource)
			{
				  if(sel_elem)
				  {
                   	 SaveFineTuning(sel_elem);
				  }
				  if(pHint->IsKindOf(RUNTIME_CLASS(CObjectData)))
				  {
					  CObjectData *pass_object = (CObjectData *)pHint;
					  m_pFunDllSetParameter = pass_object->stSTSetParameter.parameter;
					  m_orderFun = pass_object->stSTSetParameter.order;
				  }
			}
			sel_elem = pDoc->GetSelectElem();
			InitDataPropList(sel_elem);
			MapFineValue& _mapValue = pDoc->GetFineValue();
			_mapValue.erase(_mapValue.begin(),_mapValue.end());
			m_bNewItem = true;
		}
	}
}
void CPropertyFormView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VALUE, m_property_value);
	DDX_Control(pDX, IDC_BUTTON1, m_BtnApp);
}

LRESULT CPropertyFormView::OnPropertyChanged( WPARAM,LPARAM lParam )
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;
	CAOIEDITHelpDoc* pDoc = GetDocument() ;
	std::wstring _value((CString)(pProp->GetValue()));
	std::wstring _name(pProp->GetName());
    pDoc->SetFineValue(_name,_value);
	if (eItemList == m_recvSource)
	{
		if (0 != m_pFunDllSetParameter)
		{
			string name(WChar2Ansi(_name.c_str()));
			string value(WChar2Ansi(_value.c_str()));
			(*m_pFunDllSetParameter)(m_orderFun,name,value);
			CMCtrlCenter::GetCtrlCenter().ShotGrab();
			CMCtrlCenter::GetCtrlCenter().m_bParamChanged = true;
			CMCtrlCenter::GetCtrlCenter().m_bSaveBtnClicked = false;
		}
	}
	return 0;
}
BEGIN_MESSAGE_MAP(CPropertyFormView, CFormView)
	//{{AFX_MSG_MAP(CPropertyFormView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	//}}AFX_MSG_MAP
	//ON_BN_CLICKED(IDC_BUTTON1, &CPropertyFormView::OnBnClickedButton1)
END_MESSAGE_MAP()

CAOIEDITHelpDoc* CPropertyFormView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAOIEDITHelpDoc)));
	return (CAOIEDITHelpDoc*) m_pDocument;
}
// CPropertyFormView 诊断

#ifdef _DEBUG
void CPropertyFormView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPropertyFormView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPropertyFormView 消息处理程序
char*  CPropertyFormView::WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);

	if (nLen<= 0) return m_MemAString.GetBufferSetLength(0);
	char* pszDst =m_MemAString.GetBufferSetLength(nLen);
	if (NULL == pszDst) return m_MemAString.GetBufferSetLength(0);
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	return pszDst;
}
void CPropertyFormView::AddNewItem()
{

	CAOIEDITHelpDoc*  pDoc = GetDocument() ;
	MapFineValue& _mapValue = pDoc->GetFineValue();
	typedef MapFineValue::const_iterator CNT_IT;
	CNT_IT It_TestName = _mapValue.find(ItemLayerName[0]);
	CNT_IT It_SubTName = _mapValue.find(ItemLayerName[1]);
	CNT_IT It_End = _mapValue.end();
	TiXmlElement *elem = pDoc->GetSelectElem();
	if(elem)
	{
		TiXmlElement * elemNew = new TiXmlElement( *(elem));
		if(elemNew)
		{
			if (It_TestName!=It_End)
			{
				elem = elem->Parent()->ToElement();
				if (elem)
				{
					elem->SetAttribute("testid",WChar2Ansi(It_TestName->second.c_str()));
				}
			}
			else if (It_SubTName!=It_End)
			{
					
				elemNew->SetAttribute("subtestid",WChar2Ansi(It_SubTName->second.c_str()));

			}
				
			pDoc->SetNewElem(elemNew);
		}
	}
}
void CPropertyFormView::SaveFineTuning(TiXmlElement* sel_elem)
{
	if(0==sel_elem) return;
    CAOIEDITHelpDoc*   pDoc = GetDocument() ;
	MapFineValue& _mapValue = pDoc->GetFineValue();
	typedef MapFineValue::const_iterator CNT_IT;
	CString LogMsg=_T("\r\n          ");
    TiXmlElement * exe_elem = sel_elem->FirstChildElement("exe");
	if (exe_elem)
	{ /*取得所調整的算子的DLL名稱，後作為參數調整記錄名稱*/
		exe_elem = exe_elem->FirstChildElement("exename");
		if (exe_elem)
		{
           const char* pv = exe_elem->GetText()==0?" ":exe_elem->GetText();
		   LogMsg.AppendFormat(_T("%s"),Ansi2WChar(pv,strlen(pv)));
		}
	}
	for (CNT_IT it = _mapValue.begin();it!=_mapValue.end();++it)
	{
		 const wchar_t* parameter_name = it->first.c_str();
		 TiXmlElement * element = pDoc->GetElemByAttr(sel_elem,WChar2Ansi(parameter_name));
		 if (element)
		 {
			 TiXmlElement * child_elem = element->LastChild("setting")->ToElement();
			 if (child_elem)
			 {
				const char* old_value = child_elem->GetText()==0?"0":child_elem->GetText();
				const wchar_t* new_value = it->second.c_str();
				if(strcmp(old_value,WChar2Ansi(new_value))==0) continue;
				LogMsg.AppendFormat(_T("\r\n                  %s: %s   %s"),parameter_name,\
					Ansi2WChar(old_value,strlen(old_value)),new_value);
			    TiXmlElement *elemEnd = child_elem->NextSiblingElement();
				element->RemoveChild(child_elem);
				TiXmlElement item( "setting" );
				item.LinkEndChild( new TiXmlText(WChar2Ansi(new_value)));
				if(elemEnd)
				{
                  element->InsertBeforeChild(elemEnd,item);
				}
				else{
                  element->InsertEndChild(item);
				}
			 }
		 }
	} /*把參數變動記錄到日誌裡面*/
	TLOG_RECORD(_T("%s"),LogMsg.GetBuffer());
}
void CPropertyFormView::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_bNewItem)
	{
		LPARAM lParam = 0;
		CAOIEDITHelpDoc*  pDoc = GetDocument() ;
		if(eCFileTree==m_recvSource)
		{
            lParam = UPD_DBSELECTOBJECTVIEW|UPD_DBADDNEWOBJECTVIEW;
		}
		else if (eItemList==m_recvSource)
		{
			lParam = UPD_DBSELECTOBJECTVIEW;
		}
		AddNewItem();
		SaveFineTuning(pDoc->GetNewElem());
		m_wndPropList.RemoveAll();
		m_wndPropList.MarkModifiedProperties();
		pDoc->UpdateAllViews( this, lParam ) ;
		m_bNewItem = false;
   }
}



void CPropertyFormView::OnClickCreateButton(CString strValue,CCreateButtonsProp* button)
{
	CFileDialog   SaveRegDlg(FALSE,NULL, _T("mymodel.shm"),OFN_OVERWRITEPROMPT, _T("Test Regist File(*.shm)|*.shm"));//save   as 
	CString defPath;
	defPath.Format(_T("%s"),(theApp.m_ProgramName.c_str()));
	SaveRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(SaveRegDlg.DoModal()==IDOK) 
	{ 
		button->SetValue(defPath+_T("\\")+SaveRegDlg.GetFileTitle());
	}
	SaveRegDlg.DestroyWindow();
}

void CPropertyFormView::OnClickLoadButton(CString strValue,CLoadButtonsProp* button)
{
	
	CFileDialog   OpenRegDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test Model File(*.shm)|*.shm"));//save   as 
	CString defPath;
	defPath.Format(_T("%s"),theApp.m_ProgramName.c_str());
	OpenRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(OpenRegDlg.DoModal()==IDOK) 
	{ 
		button->SetValue(defPath+OpenRegDlg.GetFileTitle());
	}
	OpenRegDlg.DestroyWindow();

}


void CPropertyFormView::OnClickLeftButton(CString strValue,CTwoButtonsProp* button)
{


	CFileDialog   OpenRegDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Test Regist File(*.reg)|*.reg"));//save   as 
	CString defPath;
	defPath.Format(_T("%s"),theApp.m_ProgramName.c_str());
	OpenRegDlg.m_ofn.lpstrInitialDir=defPath;
	if(OpenRegDlg.DoModal()==IDOK) 
	{ 
		button->SetValue(defPath+OpenRegDlg.GetFileTitle());
		Hobject regist;
		wstring fileName = OpenRegDlg.GetPathName().GetBuffer();
		read_region(&regist,(WChar2Ansi(fileName.c_str())));
		disp_obj(regist,CMCfgCenter::GetCfgCenter().GetHCWnd());
	}
	OpenRegDlg.DestroyWindow();

}
void CPropertyFormView::ManualUpdate(string name,string mvalue)
{
// 	if (0 != m_pFunDllSetParameter)
// 	{
// 		//CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;
// 		CAOIEDITHelpDoc* pDoc = GetDocument() ;
// 		const char* na = "";
// 		na = name.c_str();
// 		std::wstring _value = Ansi2WChar(na,strlen(na));
// 		na = mvalue.c_str();
// 		std::wstring _name(Ansi2WChar(na,strlen(na)));
// 		pDoc->SetFineValue(_name,_value);
// 
// 		(*m_pFunDllSetParameter)(m_orderFun,name,mvalue);
// 		CMCtrlCenter::GetCtrlCenter().ShotGrab();
// 		CMCtrlCenter::GetCtrlCenter().m_bParamChanged = true;
// 		CMCtrlCenter::GetCtrlCenter().m_bSaveBtnClicked = false;
// 	}
}
void CPropertyFormView::OnClickRightButton(CString strValue,CTwoButtonsProp* button)
{
	try
	{
		strValue += _T(".reg");
		wstring tmp = strValue.GetBuffer();
		read_region(&m_Region,ws2s(tmp).c_str());
		set_color( CMCfgCenter::GetCfgCenter().GetHCWnd(),"red");
		disp_obj(CMCtrlCenter::GetCtrlCenter().m_CurrentData.m_Image,CMCfgCenter::GetCfgCenter().GetHCWnd());
		//disp_obj(CMCtrlCenter::GetCtrlCenter().m_CurrentData.m_ErrorRegist,CMCfgCenter::GetCfgCenter().GetHCWnd());
		disp_obj(m_Region,CMCfgCenter::GetCfgCenter().GetHCWnd());
		

	}

	catch (HException &except) 
	{

#ifdef _ENGLISH
		AfxMessageBox(_T("Read Region File Error"));
#else
		AfxMessageBox(_T("读取区域文件错误"));
#endif

	}

	CDrawRegistDialog* pToolDlg = new CDrawRegistDialog(m_Region,button->GetName());
	pToolDlg->Create(IDD_DIALOG_DRAW_SHARP);
	pToolDlg->ShowWindow(SW_SHOW);

	
	
}