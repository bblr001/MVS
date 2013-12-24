// MTIButton.cpp : implementation file
//

#include "stdafx.h"
#include "Tools.h"
#include "MyButton.h"
#include "MyPanel.h"
#include "SheetInspectionPanel.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMTIButSet
CMyButEnter::CMyButEnter()
{
//	m_iPanelID=0;
	m_Station = new CHANNEL_SETTING;
}

CMyButEnter::~CMyButEnter()
{
	delete m_Station;
}


BEGIN_MESSAGE_MAP(CMyButEnter, CButton)
	//{{AFX_MSG_MAP(CMTIButSet)
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMTIButSet message handlers
void CMyButEnter::OnClicked() 
{
	CMyPanel*             pNormalPanel = nullptr;
	if(m_panelType == PT_NORMAL)
	{
		pNormalPanel = (CMyPanel*)m_pPanel;
	}
#ifdef SHEET_INSPECTION
	SheetInspectionPanel* pSheetPanel  = nullptr;
	if(m_panelType == PT_SHEET_INSPECTION)
	{
		pSheetPanel = (SheetInspectionPanel*)m_pPanel;
	}
#endif
	if(pNormalPanel != nullptr)
	{
		switch(m_btnType)
		{
			case BT_ENTER:
// 				if (CMI_ControlCenter::GetInstance().GetIsFullScreen())
// 				{
// 					return;
// 				}
				AfxGetMainWnd()->SendMessage(WM_MI_ENTER_MESSAGE,(int)m_Station);
				break;
			case BT_PAUSE:
				pNormalPanel->ClickedPause();
				AfxGetMainWnd()->SendMessage(WM_MI_PAUSE_MESSAGE,(int)m_Station);
				break;
			case BT_RUN:
				pNormalPanel->ClickedRun();
				AfxGetMainWnd()->SendMessage(WM_MI_RUN_MESSAGE,(int)m_Station);
				break;
			case BT_ALARM:
				pNormalPanel->ClickedAlarm();
				AfxGetMainWnd()->SendMessage(WM_MI_ALARM_MESSAGE,(int)m_Station);
				break;
			case BT_QUERY:
				pNormalPanel->ClickedQuery();
				AfxGetMainWnd()->SendMessage(WM_MI_QUERY_MESSAGE,(int)m_Station);
				break;
			case BT_RECOUNT:
				pNormalPanel->ClickedRecount();
				AfxGetMainWnd()->SendMessage(WM_MI_RECOUNT_MESSAGE,(int)m_Station);
				break;
			}
	}
#ifdef SHEET_INSPECTION
	if(pSheetPanel != nullptr)
	{
		switch(m_btnType)
		{
			case BT_PAUSE:
				pSheetPanel->ClickedPause();
				AfxGetMainWnd()->SendMessage(WM_MI_PAUSE_MESSAGE,(int)m_Station);
				break;
			case BT_RUN:
				pSheetPanel->ClickedRun();
				AfxGetMainWnd()->SendMessage(WM_MI_RUN_MESSAGE,(int)m_Station);
				break;
			default:
				break;
		}
	}
#endif
}


