
#pragma once
#include "..\Inc\AnalyzeTLS.h"
#include "..\Inc\tinxml\tinyxml.h"

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};
class CTwoButtonsProp;
class CCreateButtonsProp;
class CLoadButtonsProp;

class CTestItemPropertiesWnd : public CDockablePane
{
// 构造
public:
	CTestItemPropertiesWnd();

	void AdjustLayout();
	void SetPropertyList(CTlsData *pData);
	void EnableTools(bool disableTools);

	void OnClickLeftButton(CString strValue,CTwoButtonsProp* button);
	void OnClickRightButton(CString strValue,CTwoButtonsProp* button);

	void OnClickCreateButton(CString strValue,CCreateButtonsProp* button);
	void OnClickLoadButton(CString strValue,CLoadButtonsProp* button);

// 属性
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	//CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

	long m_bChanged;


	CTlsData *m_CurrentData;
// 实现
public:
	virtual ~CTestItemPropertiesWnd();

protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();

	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	
	//afx_msg void OnSaveTestList();
	afx_msg void OnAddTestList();
	
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT CTestItemPropertiesWnd::OnPropertyChanged( WPARAM,LPARAM lParam );

	//int HitTest(CPoint point, BOOL bDetectCaption = FALSE);
	DECLARE_MESSAGE_MAP()

	LARGE_INTEGER  large_interger;  
	double dff;  
	__int64  LastTime;
	__int64  nowTime;

	
	bool m_bDraw;

	void SetPropListFont();
};

