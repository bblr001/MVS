
// AOIEDITHelpDoc.h : CAOIEDITHelpDoc 类的接口
//


#pragma once
#include <string>
#include <vector>
#include <list>
#include <map>
#include "tinyxml.h"
#include "GridList_DataModel.h"
#include "DoProcess/CMData.h"
#include "DlgBar.h"
class CObjectData : public CObject
{
	DECLARE_DYNCREATE(CObjectData)
public:
	CObjectData() ;
	virtual ~CObjectData() ;
	STSetParameter stSTSetParameter;
} ;
typedef std::map<std::wstring,std::wstring> MapFineValue;
struct STLSDATA_SUBITM
{
	STLSDATA_SUBITM(int item,std::wstring& appNm,std::wstring& test,\
		std::wstring& subtest,int order_):ItemId(item),AppName(appNm),testName(test),subTestName(subtest),order(order_)
	{};
	int ItemId;
	std::wstring AppName;
	std::wstring testName;
	std::wstring subTestName;
	STSetParameter stSTSetParameter;
	STDoProcess   stSTDoPorceess;
	int order;
	MapFineValue propertyV;
};
typedef std::list<STLSDATA_SUBITM*> ListOperItem;
class CAOIEDITHelpDoc : public CDocument
{
protected: // 仅从序列化创建
	CAOIEDITHelpDoc();
	DECLARE_DYNCREATE(CAOIEDITHelpDoc)
	CString m_TiXmlDocErrorMsg;
	TiXmlDocument * m_pTiXmlDoc;
	TiXmlDocument * m_pTiXmlDocItem;
	TiXmlElement  * m_itemNewElement;
    TiXmlElement  * m_currSelectElem;
	CListItem_DataModel m_DataModel;
	MapFineValue m_vFineValue;
    MapFineValue m_vAppOperItem;
    ListOperItem m_OperItem;
	CObjectData m_pass_object;
	list<STDoProcess> m_pDoProcessList;
	list<STSetParameter> m_pSetParameterList;
	string m_itemfile_path;
	CDlgBar * m_dlgbar;
// 属性
public:
	void SetBarTileHWND(CDlgBar * dlg){m_dlgbar = dlg;}
	void UPDataTitle(wstring);
	string & GetItemFilePath(){return m_itemfile_path;}
	void SetItemFilePath(string & path){m_itemfile_path = path;}
	list<STDoProcess>& GetDoProcess(){return m_pDoProcessList;}
	list<STSetParameter>& GetParameterFun(){return m_pSetParameterList;}
	CObjectData* GetPassObject(){return &m_pass_object;}
	ListOperItem& GetItemList(){return m_OperItem;}
	void ClearItemList();
	void SetOperItem(std::wstring& name,std::wstring& value)
	{ 
		m_vAppOperItem[name] = value ;
	}
	void SetFineValue(std::wstring& name,std::wstring& value)
	{ 
		m_vFineValue[name] = value ;
	}
	MapFineValue & GetOperItem() { return m_vAppOperItem ; }
	MapFineValue & GetFineValue(){ return m_vFineValue ; }
	CListItem_DataModel& GetDataModel(){return m_DataModel;}
	void SetNewElem(TiXmlElement  * elem){ASSERT(0!=elem);m_itemNewElement = elem;}
	TiXmlElement  * GetNewElem(){return m_itemNewElement;}
	void SetSelectElem(TiXmlElement  * elem){ASSERT(0!=elem);m_currSelectElem = elem;}
	TiXmlElement  * GetSelectElem(){return m_currSelectElem;}
    bool loadIni(const char * path= "E:\\C\\Prog\\AAA\\slacmvs2\\trunk\\Release\\MasterTls\\Master_TestItem.mas",RecvSour eRS= eCFileTree);
	TiXmlElement* GetRootElem(RecvSour eRS= eCFileTree);
	TiXmlElement * GetElemByAttr(TiXmlElement*,std::string attr,std::string name="name");
	void SaveFile(RecvSour eRS= eCFileTree);
// 操作
public:
	WCHAR *Ansi2WChar(LPCSTR pszSrc, int nLen);
	char * WChar2Ansi(LPCWSTR pwszSrc);
protected:
	CString m_MemString;
	CStringA m_MemAString;

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// 实现
public:
	virtual ~CAOIEDITHelpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HWND m_PaintWndID;
    void InitMyDocument(); 
// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};


