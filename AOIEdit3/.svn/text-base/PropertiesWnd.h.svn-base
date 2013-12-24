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

#pragma once
#include "..\Inc\TlsFileParser.h"
#include "cpp\HalconCpp.h"
#include <vector>
#include <memory>

using namespace std;
using namespace Halcon;
class CTwoButtonsProp;
class CCreateButtonsProp;
class CLoadButtonsProp;
class CMConfigCenter;
class CMCtrlCenter;

const int LIGHT_PANE     = 0;
const int ALGORITHM_PANE = 1;

class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// 构造
public:
	CPropertiesWnd(int nPaneType);
	void AdjustLayout();
	void SetPropertyList(CTlsData *pData);
	void SetLightParameters(std::vector<LightCtrlInfo>* pInfos);
    void SetPropListFont();
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
	CPropertiesToolBar   m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;
	CTlsData* m_CurrentData;
	std::vector<LightCtrlInfo>* m_pLightCtrlParam;

	Hobject m_Region;
private:
	void InitPropList();
// 实现
public:
	virtual ~CPropertiesWnd();
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnAddTestList();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	afx_msg LRESULT OnPropertyChanged( WPARAM,LPARAM lParam );
	DECLARE_MESSAGE_MAP()
	LARGE_INTEGER  large_interger;  
	double dff;  
	__int64  LastTime;
	__int64  nowTime;

private:
	CMConfigCenter* m_pConfigCenter;
    CMCtrlCenter* m_pCtrlCenter;
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
	virtual HRESULT get_accSelection(VARIANT *pvarChildren);
	void EnableEditTestName(BOOL flag);
private:
	int m_nPaneType; // use this flag to indicate if this pane is a Light Controller Pane or Algorithm Parameter Pane
	                // 0 : Light Parameter Pane;
	                // 1 : Algorithm Parameter Pane;
	void OnLightParamPanePropertyChanged(LPARAM lParam);
	void OnAlgorithmParamPanePropertyChanged(LPARAM lParam);

	CMFCPropertyGridProperty* m_pTestNamePro;
	CMFCPropertyGridProperty* m_pSubtestNamePro;
};

