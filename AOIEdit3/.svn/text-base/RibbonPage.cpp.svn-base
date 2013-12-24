#include "stdafx.h"
#include "afxribboncategory.h"
#include "RibbonPage.h"
#include "afxglobals.h"
#include "afxvisualmanager.h"
#include "resource.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
IMPLEMENT_DYNCREATE(CMRibbonPage, CMFCRibbonBaseElement)

CMRibbonPage::CMRibbonPage():m_bInit(FALSE)
{
}
CMRibbonPage::~CMRibbonPage()
{
}
BOOL CMRibbonPage::InitCTRL(CRect& rt)
{
	BOOL nRet= TRUE;
	CMainFrame* pMainWnd = (CMainFrame*)AfxGetMainWnd();
    pMainWnd->SendMessage(ON_WM_RIBBON_HEADER,(WPARAM)0,(LPARAM)&rt);
	m_bInit=nRet;
	return nRet;
}
void CMRibbonPage::OnDraw(CDC* pDC)
{
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);
    return;
	if (m_rect.IsRectEmpty())
	{
		return;
	}
	CRect rect = m_rect;
	CBasePane* pParentBar = NULL;

	if (m_pParentMenu != NULL)
	{
		pParentBar = m_pParentMenu;
	}
	else
	{
		pParentBar = GetTopLevelRibbonBar();
	}

	if (pParentBar != NULL)
	{
		BOOL bDisableSideBarInXPMode = FALSE;

		if (m_bIsDefaultMenuLook && m_pParentMenu != NULL)
		{
			bDisableSideBarInXPMode = m_pParentMenu->m_bDisableSideBarInXPMode;
			rect.left += 2 * CMFCVisualManager::GetInstance()->GetMenuImageMargin() + 2;
			m_pParentMenu->m_bDisableSideBarInXPMode = FALSE;
		}
		if (m_pParentMenu != NULL)
		{
			m_pParentMenu->m_bDisableSideBarInXPMode = bDisableSideBarInXPMode;
		}
	}
}
CSize CMRibbonPage::GetRegularSize(CDC* pDC)
{
	ASSERT_VALID(this);
	return CSize(32, 32);
}