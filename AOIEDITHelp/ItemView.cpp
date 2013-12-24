// ItemView.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEDITHelp.h"
#include "ItemView.h"
#include "AOIEDITHelpDoc.h"
#include "MainFrm.h"
#include "FileTree.h"
#include "PropertyFormView.h"
#include ".\DoProcess\CMCtrolCenter.h"
#include <atlconv.h>
// CItemView

IMPLEMENT_DYNCREATE(CItemView, CView)
static CString STR_ITEMIDX[]=
{L"01",L"02",L"03",L"04",L"05",L"06",L"07",L"08",L"09",L"10",L"11",L"12",L"13",L"14",\
 L"15",L"16",L"17",L"18",L"19",L"20",L"21",L"22",L"23",L"24",L"25",L"26",L"27",L"28",\
 L"29",L"30",L"31",L"32",L"33",L"34",L"35",L"36",L"37",L"38",L"39",L"40",L"41",L"42"};
/*當列表中的項，沒有全部加載DLL時，用到Id的轉換數組*/
static int ItemID_CONVER[] =
{   
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,\
	0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
CItemView::CItemView():m_ItemCollCnt(0),m_ItemElement(0),m_bIsFileBind(true)
{
  for (int i=0;i<ItemCNT;++i)
  {
	  nItemResFail[i] = false;
  }
}

CItemView::~CItemView()
{
}

BEGIN_MESSAGE_MAP(CItemView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_MESSAGE(ON_WM_DBROWCLICK,OnGridListDbCk)
	ON_MESSAGE(ON_WM_ENDEDITTXT,OnGridListEndEdit)
	ON_COMMAND(ID_ITEM_DELETE, &CItemView::OnItemDelete)
	ON_COMMAND(ID_ITEM_UP, &CItemView::OnItemUp)
	ON_COMMAND(ID_ITEM_DOWN, &CItemView::OnItemDown)
END_MESSAGE_MAP()


// CItemView 绘图
LRESULT CItemView::OnGridListEndEdit(WPARAM wp,LPARAM lp)
{
    UINT  nRow  = (UINT)lp;
	UINT  nCol  = (UINT)wp;
    CString ItemText= m_itemList.GetItemText(nRow,nCol);
	DWORD_PTR pData = m_itemList.GetItemData(nRow);
	TiXmlElement * elem = (TiXmlElement*)pData;
	if (elem)
	{
		CAOIEDITHelpDoc* pDoc = GetDocument() ;
		char * value = pDoc->WChar2Ansi(ItemText.GetBuffer());

		elem->SetAttribute("subtestid",value);
	}
	return 0;
}
LRESULT CItemView::OnGridListDbCk(WPARAM wp,LPARAM lp)
{
	UINT nItem = (UINT)wp;
	if(m_itemList.GetCellImage(nItem,1)==m_nStateImageIdx+1)
	{
		DWORD_PTR pData = m_itemList.GetItemData(nItem);
		TiXmlElement * elem = (TiXmlElement*)pData;
		if(elem)
		{
			CAOIEDITHelpDoc* pDoc = GetDocument() ;
			ASSERT(0!=pDoc);
			pDoc->SetSelectElem(elem);
			ListOperItem& mListItem = pDoc->GetItemList();
			list<STSetParameter>& m_pSetParameterList = pDoc->GetParameterFun();
			CObjectData *pass_object = pDoc->GetPassObject();
			if(pass_object==0)return 0;
			STSetParameter& funSetParameter = pass_object->stSTSetParameter;
			funSetParameter.parameter = 0;
			funSetParameter.order = -1;
			ListOperItem::iterator It = mListItem.begin();
			wchar_t buff_Test[256];
			wchar_t buff_SubTest[256];
			wchar_t buff_ProgName[256];
			//设定不显示检测区域
			int index=0;
			for (It = mListItem.begin();It!=mListItem.end();++It)
			{
				(*It)->stSTSetParameter.parameter((*It)->stSTSetParameter.order,"SHOWOBJECT","NO");
				index++;
			}
			/*查找算子列表項，取得參數調整函數指針。*/
			index=0;
			
			for (It = mListItem.begin();It!=mListItem.end();++It)
			{
				m_itemList.GetItemText(nItem,2,buff_Test,255);
				m_itemList.GetItemText(nItem,3,buff_SubTest,255);
				m_itemList.GetItemText(nItem,5,buff_ProgName,255);
				wstring appName(buff_ProgName);
				wstring appTest(buff_Test);
				wstring appSubTest(buff_SubTest);
				if ((*It)->testName==appTest)
				{
					if ((*It)->subTestName==appSubTest)
					{
						if ((*It)->AppName==appName)
						{
							  if ((*It)->ItemId == nItem)
							  {
								  (*It)->stSTSetParameter.parameter((*It)->stSTSetParameter.order,"SHOWOBJECT","YES");
								  funSetParameter.parameter = (*It)->stSTSetParameter.parameter;
								  funSetParameter.order = (*It)->stSTSetParameter.order;
								  break;
							  }
						}
					}
				}
				index++;
			}
			pDoc->UpdateAllViews(this,UPD_DBSELECTOBJECTVIEW,pass_object);

			CMCtrlCenter::GetCtrlCenter().ShotGrab();
		 }
	}
	else
	{
		 AfxMessageBox(_T("请打开此测试项，再进行参数调整！"),MB_OK|MB_ICONWARNING);
	}
	return 0;
}
void CItemView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}
bool CItemView::AppOperItem()
{
   CAOIEDITHelpDoc* pDoc = GetDocument() ;
   int ItemCnt = m_itemList.GetItemCount();
   wchar_t buff_ProgName[256];
   wchar_t buff_Item[256];
   wchar_t buff_Test[256];
   wchar_t buff_SubTest[256];
   wchar_t buff_Version[256];
   pDoc->ClearItemList();
   ListOperItem& lstOperItm = pDoc->GetItemList();
   int * pId = ItemID_CONVER;
   for (int i=0;i<ItemCnt;++i)
   {
	   if(m_itemList.GetCellImage(i,1)==m_nStateImageIdx+1)
	   {
		   m_itemList.GetItemText(i,5,buff_ProgName,255);
		   m_itemList.GetItemText(i,6,buff_Version,255);
		   m_itemList.GetItemText(i,1,buff_Item,255);
		   m_itemList.GetItemText(i,2,buff_Test,255);
		   m_itemList.GetItemText(i,3,buff_SubTest,255);
		   wstring AppName(buff_ProgName);
		   wstring ItmTest(buff_Test);
		   wstring ItmSubTest(buff_SubTest);
		   int  ItemID = _wtoi(buff_Item);
		   ItemID = ItemID>0?ItemID-1:0;
		   /*查找到重複加載的算子，並用order變量累計*/
		   ListOperItem::iterator It = lstOperItm.begin();
		   int order = 0;
		   for (;It!=lstOperItm.end();++It)
		   {
              if((*It)->AppName == AppName /*&& (*It)->testName == ItmTest*/)
			  {
                      ++order;
			  }
		   }
           STLSDATA_SUBITM *Item = new STLSDATA_SUBITM(ItemID,AppName,ItmTest,ItmSubTest,order);
		   /*記錄要加載的DLL在列表中的項*/
		   *pId++ = ItemID;
		   TiXmlElement * elem = (TiXmlElement *)m_itemList.GetItemData(i);
		   const char* settingV = "0";
		   const char* name = "";
		   if(elem)
		   {
               elem = elem->FirstChildElement("parameter");
			   for(;elem;elem=elem->NextSiblingElement())
			   {
				   TiXmlAttribute* attri = elem->FirstAttribute();
				   for (;attri;attri->Next())
				   {
					   if (strcmp(attri->Name(),"name")==0)
					   {
                           name = attri->Value();
						   TRACE("\n  ==%s== ",name);
						   break;
					   }
				   }
				   TiXmlElement * elem_setting = elem->FirstChildElement("setting");
				   if (elem_setting)
				   {
					   settingV = elem_setting->GetText()==0?"0":elem_setting->GetText();
					   TRACE("\n  ==%s== ",settingV);
				   }
				   wstring nameS(pDoc->Ansi2WChar(name,strlen(name)));
				   wstring valueS(pDoc->Ansi2WChar(settingV,strlen(settingV)));
				   Item->propertyV[nameS] = valueS;
				   
			   }
		   }
		   lstOperItm.push_back(Item);
	   }
   }
   return true;
}
void CItemView::DisplayResult(int nItem,bool bResFail)
{
	    nItem = nItem<0?0:nItem;
	if(nItemResFail[nItem]!=bResFail)
	{
		nItemResFail[nItem] = bResFail;
		BOOL bReturn = m_itemList.SetItemText(ItemID_CONVER[nItem],4,bResFail ?_T("Detect"):_T("OK")); 
		if(bReturn)
		{
			m_itemList.SetCellImage(ItemID_CONVER[nItem],4, bResFail ? 1:0);	
		} 
	}
}
CAOIEDITHelpDoc* CItemView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAOIEDITHelpDoc)));
	return (CAOIEDITHelpDoc*) m_pDocument;
}
void CItemView::AddNewItem(TiXmlElement* element)
{
	CAOIEDITHelpDoc* pDoc = GetDocument() ;
	ASSERT(0!=pDoc);
	TiXmlAttribute *attribute ;
	const char* nameType = element->Value();
	if(strcmp(nameType,arrNameType[2])==0)
	{
		TiXmlElement *parent_elem = element->Parent()->ToElement();
		const char * testNameAttrV = "";
		if(parent_elem)
		{
			attribute = parent_elem->FirstAttribute();
			for (;attribute;attribute=attribute->Next())
			{
				if (strcmp(attribute->Name(),"testid")==0)
				{
					testNameAttrV = attribute->Value();
					break;
				}
			}
		}
		CString TestName(pDoc->Ansi2WChar(testNameAttrV,strlen(testNameAttrV)));
		attribute = element->FirstAttribute();
		for (;attribute;attribute=attribute->Next())
		{
			if (strcmp(attribute->Name(),"subtestid")==0)
			{
				testNameAttrV = attribute->Value();
				break;
			}
		}
		CString m_strSubTestName(pDoc->Ansi2WChar(testNameAttrV,strlen(testNameAttrV)));
		TiXmlElement* exe_elem = element->FirstChildElement("exe");
		const char* AppName = "";
		const char* AppVers = "";
		TiXmlElement* child_elem = exe_elem->FirstChildElement("exename");
		if (child_elem)
		{
			AppName = child_elem->GetText()==0?"":child_elem->GetText();
		}
		child_elem = exe_elem->FirstChildElement("exeversion");
		if (child_elem)
		{
			AppVers = child_elem->GetText()==0?"":child_elem->GetText();
		}
		CString SubAppName(pDoc->Ansi2WChar(AppName,strlen(AppName)));
		CString SubAppVers(pDoc->Ansi2WChar(AppVers,strlen(AppVers)));//runtest
		TiXmlElement* run_elem = element->FirstChildElement("runtest");
		const char* RunYesNo= "";
		if (run_elem)
		{
			RunYesNo = run_elem->GetText()==0?"":run_elem->GetText();
		}
		TiXmlElement* order_elem = element->FirstChildElement("order");
		const char* Order = "00";
		if (order_elem)
		{
			Order = order_elem->GetText()==0?"":order_elem->GetText();
		}
		CListItem_DataModel& m_DataModel = pDoc->GetDataModel();
		vector<CListCtrl_DataRecord>& data_vector = m_DataModel.GetRecords();
		int nItem = m_itemList.GetItemCount();
		if (m_bIsFileBind)
		{
			int nItem =atoi(Order);
			nItem = nItem>42?m_DataModel.GetRowIds()-1:nItem;
			nItem = nItem<1?0:nItem - 1;
		}
		data_vector.push_back( CListCtrl_DataRecord(
			STR_ITEMIDX[nItem],TestName, m_strSubTestName,_T("Ok"), SubAppName, SubAppVers));
		m_DataModel.InitDataModel();
		nItem = m_DataModel.GetRowIds()-1;
		nItem = m_itemList.InsertItem(nItem, m_DataModel.GetCellText(nItem,0));
		m_itemList.SetItemData(nItem, (DWORD_PTR)element);
		int ColNum = m_DataModel.GetColCount();
		for(int col = 0; col < ColNum; ++col)
		{
			int nCellCol = col+1;	// +1 because of hidden column
			const CString& strCellText = m_DataModel.GetCellText(nItem, col);
			if (nCellCol==1)
			{
				m_itemList.SetItemText(nItem, nCellCol, strCellText);
				if (stricmp((RunYesNo),"YES")==0)
					m_itemList.SetCellImage(nItem, nCellCol, m_nStateImageIdx+1);	// unchecked
				else
					m_itemList.SetCellImage(nItem, nCellCol, m_nStateImageIdx);	// checked
			}else
			if (nCellCol==4)
			{
				m_itemList.SetCellImage(nItem, nCellCol, 0);	// checked
				m_itemList.SetItemText(nItem, nCellCol,_T("Ok"));//Defect
			}
			else{
                m_itemList.SetItemText(nItem, nCellCol, strCellText);
			}
		}
	}
}
void CItemView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	CAOIEDITHelpDoc* pDoc = GetDocument() ;
	if ( lHint & UPD_DBSELECTOBJECTVIEW)
	{
		if(pSender->IsKindOf(RUNTIME_CLASS(CPropertyFormView)))
		{
			CPropertyFormView* pSendVw = (CPropertyFormView*)pSender;
			TiXmlElement *element = 0;
			TiXmlElement *parent_elem = 0;
			/*當來自原文件新加的算子項時，要特別處理*/
			if (lHint & UPD_DBADDNEWOBJECTVIEW)
			{
				/*得到原文件中算子項的父項的屬性*/
				TiXmlElement *source_elem = pDoc->GetSelectElem();
				TiXmlElement *source_parent_elem = 0;
				const char * STR_ID="";
				if(source_elem)
				{
					source_parent_elem = source_elem->Parent()->ToElement();
					if (source_parent_elem)
					{
                       TiXmlAttribute * attri = source_parent_elem->FirstAttribute();
                       if (strcmp(attri->Name(),"testid")==0)
                       {
						   STR_ID = attri->Value()==0?"":attri->Value();
                       }
					}
				}
				////////////////////////////////////////////////////
				/*在當前程序算子項中查找是否有原文件中對應的父項*/
				TiXmlElement * root_elem  = pDoc->GetRootElem(eItemList);
				if(!root_elem)return;
				if(root_elem)
				{
					element = 0;
					parent_elem=0;
					TiXmlElement * elist_elem = root_elem->FirstChildElement("test");
					for(;elist_elem;elist_elem=elist_elem->NextSiblingElement())
					{
						element = pDoc->GetElemByAttr(elist_elem,string(STR_ID),"testid");
						if (element)
						{
                             break;
						}
					}
					if (element)
					{
						if (elist_elem)
						{
                          parent_elem = elist_elem;
						}
					}
				/////////////////////////////////////////////////////////
				/*如果沒有對應的父項，則新加一條父項*/
					if (0==parent_elem)
					{
                        if(source_elem&&source_parent_elem)
						{
                            TiXmlElement * new_parent_elem = new TiXmlElement(*source_parent_elem);
							TiXmlElement *elem = new_parent_elem->FirstChildElement();
							for (;elem;)
							{ /*刪除其他無關項，只保留當前項*/
                               if (elem!=source_elem)
                               {
								   TiXmlElement * remove_elem = elem;
								   elem=elem->NextSiblingElement();
								   new_parent_elem->RemoveChild(remove_elem);
                               }
							}
                           if (root_elem)
                           {
							   root_elem->LinkEndChild(new_parent_elem);
							   parent_elem = new_parent_elem;
                           }
						}
					}

				}

			}
			else
			{
				TiXmlElement *element = pDoc->GetSelectElem();
				if(element)
				{
					parent_elem = element->Parent()->ToElement();
				}
			}
					
			if(parent_elem)
			{
			  TiXmlElement * NewElm = pDoc->GetNewElem();
			  if(NewElm)
			  {
				  parent_elem->LinkEndChild(NewElm);
				  pDoc->SetSelectElem(NewElm);
			  }
			}
			element = pDoc->GetSelectElem();
			if(!element)return;
			m_bIsFileBind = false;
			AddNewItem(element);
		}
				
	}
	else if(lHint & UPD_ITEMRELOAD)
	{
          OnFileBind(pDoc->GetItemFilePath().c_str());
     }
}
int  CItemView::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CView::OnCreate(lpcs)==-1)
	{
		return -1;
	}
	CRect rectDummy;
	rectDummy.SetRect(0,0,12,12);
	if (!m_itemList.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT, rectDummy, this, 5))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}
	DWORD dwStyle2 = m_itemList.GetExtendedStyle();
	dwStyle2 |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle2 |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle2 |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	dwStyle2 |=LVS_EX_INFOTIP;
	m_itemList.SetExtendedStyle(dwStyle2);
	m_itemList.ModifyStyle(0,LVS_SHOWSELALWAYS);
    return 0;
}
void CItemView::InitItemHeader()
{
	m_ImageList.Create(16, 16, ILC_COLOR16 | ILC_MASK, 1, 0);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_OK));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_FAULTY));
    m_nStateImageIdx = CGridColumnTraitImage::AppendStateImages(m_itemList, m_ImageList);	// Add checkboxes
	m_itemList.SetImageList(&m_ImageList, LVSIL_SMALL);
	m_itemList.m_nStateImageIdx = m_nStateImageIdx;
	m_itemList.SetCellMargin(1.2);
	CGridRowTraitXP* pRowTrait = new CGridRowTraitXP;
	m_itemList.SetDefaultRowTrait(pRowTrait);
	m_itemList.InsertHiddenLabelColumn();	// Requires one never uses column 0
	CAOIEDITHelpDoc* pDoc = GetDocument() ;
	CListItem_DataModel m_DataModel = pDoc->GetDataModel();
	m_ItemCollCnt= m_DataModel.GetColCount();
	CGridColumnTrait* pTrait ;
	for(int col = 0; col < m_ItemCollCnt ; ++col)
	{
		const CString& title = m_DataModel.GetColTitle(col);
		if (col+1==1)	// Year won
		{
			CGridColumnTraitImage* pTraitImage = new CGridColumnTraitImage();
			pTraitImage->AddImageIndex(m_nStateImageIdx);		// Unchecked (and not editable)
			pTraitImage->AddImageIndex(m_nStateImageIdx+1);	// Checked (and editable)
			pTraitImage->SetToggleSelection(false);
			pTrait = pTraitImage;
		}else if (col+1==2/*||col+1==3*/)
		{
			CGridColumnTraitEdit *pTraitEdit = new CGridColumnTraitEdit();
			pTrait = pTraitEdit;
		}
		else
		{
          	CGridColumnTraitText* pTraitText = new CGridColumnTraitText();
			pTrait = pTraitText;
		}
		m_itemList.InsertColumnTrait(col+1, title, LVCFMT_LEFT, 100, col, pTrait);
	}
}
void CItemView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	if (m_itemList.GetSafeHwnd())
	{
		CRect rc ;
		m_itemList.GetWindowRect( &rc ) ;
		ScreenToClient( &rc ) ;
		m_itemList.SetWindowPos( NULL, 1, 1, cx-2, cy - rc.top - 2,
			SWP_NOACTIVATE|SWP_NOZORDER ) ;
		for (int i=1;i<=m_ItemCollCnt;++i)
		{
			m_itemList.SetColumnWidth(i,(cx-2)/m_ItemCollCnt);
		}
	}
}

void CItemView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	InitItemHeader();
	CAOIEDITHelpDoc* pDoc = GetDocument() ;
}
void CItemView::OnFileBind(string path)
{
	if(path == "")
		return;

	CAOIEDITHelpDoc* pDoc =  GetDocument() ;
	ASSERT(0!=pDoc);
	if (0!=pDoc)
	{
		 if(0<m_itemList.GetItemCount())
          m_itemList.DeleteAllItems();
		 strcpy_s(path_buff,MAX_PATH,path.c_str());
		 bool bRet = pDoc->loadIni(path_buff,eItemList);
		 if (!bRet) return;
		 TiXmlElement * elem = pDoc->GetRootElem(eItemList);
		 elem = elem->FirstChildElement("test");
		 m_ItemElement = elem;
		 TiXmlElement * child_elem = 0;
		 CListItem_DataModel& m_DataModel = pDoc->GetDataModel();
		 vector<CListCtrl_DataRecord>& data_vector = m_DataModel.GetRecords();
		 data_vector.erase(data_vector.begin(),data_vector.end());
		 for (;elem;elem=elem->NextSiblingElement())
		 {
			 child_elem= elem->FirstChildElement();
			 for(;child_elem;child_elem=child_elem->NextSiblingElement())
			 {
				 AddNewItem(child_elem);
			 }
		 }
		 m_itemList.SortColumn(1,true);
		 if(0!=child_elem) pDoc->SetSelectElem(child_elem);
		 m_bIsFileBind = true;
	}
}
void CItemView::SaveFile()
{
	CAOIEDITHelpDoc* pDoc =  GetDocument() ;
	ASSERT(0!=pDoc);
	if (0!=pDoc)
	{
		int ItemCnt = m_itemList.GetItemCount();
		for (int nItem=0;nItem<ItemCnt;++nItem)
		{
			char* RunYesNo= "NO";
			if(m_itemList.GetCellImage(nItem,1)==m_nStateImageIdx+1)
			{
                RunYesNo= "YES";
			}
			CStringA Order(m_itemList.GetItemText(nItem,1).GetBuffer());
			DWORD_PTR pData = m_itemList.GetItemData(nItem);
			TiXmlElement * elem = (TiXmlElement*)pData;
			if(elem)
			{
				TiXmlElement* run_elem = elem->FirstChildElement("runtest");
				TiXmlElement item_run( "runtest" );
				item_run.LinkEndChild( new TiXmlText( RunYesNo ));
				if (run_elem)
				{
					elem->ReplaceChild(run_elem,item_run);
				}
				else
				{
					elem->InsertEndChild(item_run);
				}
				TiXmlElement* order_elem = elem->FirstChildElement("order");
				TiXmlElement item_order( "order" );
				const char* czOrder = Order.GetBuffer();
				item_order.LinkEndChild( new TiXmlText( czOrder ));
				if (order_elem)
				{
					elem->ReplaceChild(order_elem,item_order);
				}
				else
				{
                    elem->InsertEndChild(item_order);
				}

			}
		}
	}
}
// CItemView 诊断

#ifdef _DEBUG
void CItemView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CItemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CItemView 消息处理程序

void CItemView::OnItemDelete()
{
	// TODO: 在此添加命令处理程序代码
	 int nRow = m_itemList.m_iRow;
	 if (nRow>=0)
	 {
	   TiXmlElement *element = (TiXmlElement *)m_itemList.GetItemData(nRow);
       BOOL bRet = m_itemList.DeleteItem(nRow);
	   if (!bRet)
	   {
		   return;
	   }
	   CString nItemText;
	   for (int nCnt = m_itemList.GetItemCount();nCnt>nRow;--nCnt)
	   {
		   m_itemList.SetItemText(nCnt-1,1,STR_ITEMIDX[nCnt-1]);
	   }
	   TiXmlElement *parent_elem = 0;
	   if(element)
	   {
		   parent_elem = element->Parent()->ToElement();
		   if(parent_elem)
		   {
             parent_elem->RemoveChild(element);
		   }
	   }
	}
}

void CItemView::OnItemUp()
{
	// TODO: 在此添加命令处理程序代码
	int nRow = m_itemList.m_iRow;
	if(nRow>=1)
	{
		m_itemList.SetItemText(nRow,1,STR_ITEMIDX[nRow-1]);
		m_itemList.SetItemText(nRow-1,1,STR_ITEMIDX[nRow]);
		m_itemList.SortColumn(1,true);
	}
}

void CItemView::OnItemDown()
{
	// TODO: 在此添加命令处理程序代码
	int nRow = m_itemList.m_iRow;
	if(nRow <  m_itemList.GetItemCount()-1)
	{
		m_itemList.SetItemText(nRow,1,STR_ITEMIDX[nRow+1]);
		m_itemList.SetItemText(nRow+1,1,STR_ITEMIDX[nRow]);
        m_itemList.SortColumn(1,true);
	}
}
