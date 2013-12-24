#pragma once

#include "tinyxml.h"
#include "afxwin.h"
#include "afxext.h"
#include "DoProcess/CMData.h"
class CAOIEDITHelpDoc;
// CPropertyFormView 窗体视图
class CFileTree;
class CItemView;
class TiXmlElement;

class CTwoButtonsProp;
class CCreateButtonsProp;
class CLoadButtonsProp;

class CPropertyFormView : public CFormView
{
	DECLARE_DYNCREATE(CPropertyFormView)
protected:
	RecvSour m_recvSource;
	CPropertyFormView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPropertyFormView();

	CMFCPropertyGridCtrl m_wndPropList;
	TiXmlElement * sel_elem ;
	DLLSetParameter m_pFunDllSetParameter;
	int m_orderFun;
	Hobject m_Region;
public:
	CAOIEDITHelpDoc* GetDocument();
	enum { IDD = IDD_FORMVIEW };

	void OnClickLeftButton(CString strValue,CTwoButtonsProp* button);
	void OnClickRightButton(CString strValue,CTwoButtonsProp* button);
	void OnClickCreateButton(CString strValue,CCreateButtonsProp* button);
	void OnClickLoadButton(CString strValue,CLoadButtonsProp* button);

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
private:
	void AddNewItem();
	void SaveFineTuning(TiXmlElement* sel_elem);
	void InitPropList();
	void InitDataPropList(TiXmlElement*);
public:
	void SaveFile();
	virtual void OnInitialUpdate();
	WCHAR *Ansi2WChar(LPCSTR pszSrc, int nLen);
	char * WChar2Ansi(LPCWSTR pwszSrc);
	void ManualUpdate(string name,string mvalue);
protected:
	CString m_MemString;
	CStringA m_MemAString;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	afx_msg int  OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT CPropertyFormView::OnPropertyChanged( WPARAM,LPARAM lParam );
	DECLARE_MESSAGE_MAP()
public:
	bool m_bNewItem;
	bool m_bDraw;
	CStatic m_property_value;
	CBitmapButton m_BtnApp;
	CString m_strSubTestName;
	afx_msg void OnBnClickedButton1();
	
};


