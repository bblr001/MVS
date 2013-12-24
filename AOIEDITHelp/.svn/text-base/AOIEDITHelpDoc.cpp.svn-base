
// AOIEDITHelpDoc.cpp : CAOIEDITHelpDoc 类的实现
//

#include "stdafx.h"
#include "AOIEDITHelp.h"
#include "AOIEDITHelpView.h"
#include "AOIEDITHelpDoc.h"
#include "DoProcess/CMCfgCenter.h"
#include <string>
#include <atlconv.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CObjectData, CObject)

CObjectData::CObjectData()
{
}

CObjectData::~CObjectData()
{
}
// CAOIEDITHelpDoc

IMPLEMENT_DYNCREATE(CAOIEDITHelpDoc, CDocument)

BEGIN_MESSAGE_MAP(CAOIEDITHelpDoc, CDocument)
END_MESSAGE_MAP()


// CAOIEDITHelpDoc 构造/析构

CAOIEDITHelpDoc::CAOIEDITHelpDoc():m_pTiXmlDoc(0),m_pTiXmlDocItem(0),\
m_itemNewElement(0),m_currSelectElem(0)
{
	// TODO: 在此添加一次性构造代码

}
void CAOIEDITHelpDoc::ClearItemList()
{
	ListOperItem::const_iterator it = m_OperItem.begin();
	for (;it!=m_OperItem.end();++it)
	{
		delete (*it);
	}
	m_OperItem.clear();
}
CAOIEDITHelpDoc::~CAOIEDITHelpDoc()
{
	if (0!=m_pTiXmlDoc)
	{
		delete m_pTiXmlDoc;
	}
	if (0!=m_pTiXmlDocItem)
	{
		delete m_pTiXmlDocItem;
	}
	ListOperItem::const_iterator It = m_OperItem.begin();
	for (;It!=m_OperItem.end();++It)
	{
		delete (*It);
	}
	m_OperItem.clear();
}
void CAOIEDITHelpDoc::UPDataTitle(wstring title)
{
	m_dlgbar->SendMessage(MSG_CHGTITLE,(WPARAM)title.c_str(),(LPARAM)0);
}
char*  CAOIEDITHelpDoc::WChar2Ansi(LPCWSTR pwszSrc)
{
	int nLen = WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, NULL, 0, NULL, NULL);

	if (nLen<= 0) return m_MemAString.GetBufferSetLength(0);
	char* pszDst =m_MemAString.GetBufferSetLength(nLen);
	if (NULL == pszDst) return m_MemAString.GetBufferSetLength(0);
	WideCharToMultiByte(CP_ACP, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
	pszDst[nLen -1] = 0;
	return pszDst;
}
WCHAR *CAOIEDITHelpDoc::Ansi2WChar(LPCSTR pszSrc, int nLen)
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
BOOL CAOIEDITHelpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
 
	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
    InitMyDocument();
	return TRUE;
}
void CAOIEDITHelpDoc::SaveFile(RecvSour eRS/* = eCFileTree */)
{
	TiXmlDocument * pTiXmlDoc = 0;
	pTiXmlDoc = (eCFileTree == eRS) ?m_pTiXmlDoc:m_pTiXmlDocItem;
	if(0!=pTiXmlDoc)
	{
		pTiXmlDoc->SaveFile();
	}
}
bool CAOIEDITHelpDoc::loadIni(const char * path,RecvSour eRS)
{
	string strPath(path);
	if(strPath == "")
		return false;

	bool loadOkay = false;
	TiXmlDocument * pTiXmlDoc = 0;
	pTiXmlDoc = (eCFileTree == eRS) ?m_pTiXmlDoc:m_pTiXmlDocItem;
	if(0!=pTiXmlDoc)
	{
		pTiXmlDoc->SaveFile();
		delete pTiXmlDoc;
		pTiXmlDoc = 0;
	}

	USES_CONVERSION;
	if (0==pTiXmlDoc)
	{
		pTiXmlDoc = new TiXmlDocument(path);
		loadOkay = pTiXmlDoc->LoadFile(TIXML_ENCODING_UNKNOWN);
		if (!loadOkay)
		{
			const char * erro = pTiXmlDoc->ErrorDesc();
			if(0 != erro)
			{
				CString cstrErro = CA2T(erro);
				AfxMessageBox(cstrErro,MB_ICONWARNING|MB_OK);
			}
			else
			{
		        AfxMessageBox(_T("Cannot load ini file"),MB_ICONWARNING|MB_OK);
			}
		}
		if(eCFileTree == eRS)m_pTiXmlDoc=pTiXmlDoc;
		else m_pTiXmlDocItem=pTiXmlDoc;
	}
	return loadOkay;
}
TiXmlElement* CAOIEDITHelpDoc::GetRootElem(RecvSour eRS)
{
  if(eCFileTree == eRS)
  {
	  if (0!=m_pTiXmlDoc)
	  {
       ASSERT(0!=m_pTiXmlDoc);
	   return m_pTiXmlDoc->RootElement();
	  }
  }
  else if (0!=m_pTiXmlDocItem)
  {   
	  ASSERT(0!=m_pTiXmlDocItem);
	  return m_pTiXmlDocItem->RootElement();
  }
  return 0;
}
TiXmlElement * CAOIEDITHelpDoc::GetElemByAttr(TiXmlElement* element,std::string attr,std::string name)
{
		TiXmlAttribute *attribute;
		bool bTraverseChild = false;
		TiXmlElement* temp_elem =  element;
		TiXmlElement* pelement  =  element;
		while(pelement)
		{
			for(attribute = pelement->FirstAttribute();attribute;attribute=attribute->Next())
			{
				if(strcmp(attribute->Name(),name.c_str())==0)
				{
					string atrrNo(attribute->Value());
					if(atrrNo == attr) return pelement;
					break;
				}
			}
			if(!bTraverseChild&&pelement->FirstChildElement())
			{ 
				pelement = pelement->FirstChildElement();
				bTraverseChild=false;
			}
			else if (pelement->NextSiblingElement())
			{ 
				pelement = pelement->NextSiblingElement();
				bTraverseChild=false;
			}
		   else
			 {
				 if(pelement->Parent())
				 {
					 pelement = pelement->Parent()->ToElement();
					 bTraverseChild=true; 
					 if(pelement == temp_elem) break;
				 }
				 else
				 {
                     pelement = 0;
				 }
			 }
		}
		return 0;
}
void CAOIEDITHelpDoc::InitMyDocument()
{
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		CView* pView = GetNextView(pos);
		if(pView->IsKindOf(RUNTIME_CLASS(CAOIEDITHelpView)))
		{
		}
	} 
	theApp.m_currentDocument = this;
};


// CAOIEDITHelpDoc 序列化

void CAOIEDITHelpDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		SaveFile(eItemList);
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CAOIEDITHelpDoc 诊断

#ifdef _DEBUG
void CAOIEDITHelpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CAOIEDITHelpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CAOIEDITHelpDoc 命令
