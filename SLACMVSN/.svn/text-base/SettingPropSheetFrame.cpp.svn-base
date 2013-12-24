
#include "stdafx.h"

#include "resource.h"
#include "SettingPropSheetFrame.h"
#include "PropSheet2.h"
#include "MainFrm.h"
BEGIN_MESSAGE_MAP(CSettingPropSheetFrame, CMiniFrameWnd)
	//{{AFX_MSG_MAP(CShapePropSheetFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_WM_SETFOCUS()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CSettingPropSheetFrame::CSettingPropSheetFrame()
{
	m_pModelessSettingPropSheet = NULL;
}
int CSettingPropSheetFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMiniFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	try
	{
		m_pModelessSettingPropSheet = new CModelessSettingPropSheet(this);
		if (!m_pModelessSettingPropSheet->Create(this,
			WS_CHILD | WS_VISIBLE, 0))
		{
			delete m_pModelessSettingPropSheet;
			m_pModelessSettingPropSheet = NULL;
			return -1;
		}

	}
	catch (CException* e)
	{
		e->ReportError();
	}
	// Resize the mini frame so that it fits around the child property
	// sheet.
	CRect rectClient, rectWindow;
	m_pModelessSettingPropSheet->GetWindowRect(rectClient);
	rectWindow = rectClient;

	// CMiniFrameWnd::CalcWindowRect adds the extra width and height
	// needed from the mini frame.
	CalcWindowRect(rectWindow);
	SetWindowPos(NULL, rectWindow.left, rectWindow.top,
		rectWindow.Width(), rectWindow.Height(),
		SWP_NOZORDER | SWP_NOACTIVATE);
	m_pModelessSettingPropSheet->SetWindowPos(NULL, 0, 0,
		rectClient.Width(), rectClient.Height(),
		SWP_NOZORDER | SWP_NOACTIVATE);

	return 0;
}

void CSettingPropSheetFrame::OnClose()
{
	// Instead of closing the modeless property sheet, just hide it.
	//CMainFrame* pMainFrame = STATIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	//pMainFrame->HideModelessPropSheet();
	/*if (m_pShapePropFrame != NULL)*/
	/*m_pShapePropFrame->*/ShowWindow(SW_HIDE);
}

void CSettingPropSheetFrame::OnSetFocus(CWnd* /*pOldWnd*/)
{
	// Forward focus to the embedded property sheet
	ASSERT_VALID(m_pModelessSettingPropSheet);
	m_pModelessSettingPropSheet->SetFocus();
}

void CSettingPropSheetFrame::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CMiniFrameWnd::OnActivate(nState, pWndOther, bMinimized);

	// Forward any WM_ACTIVATEs to the property sheet...
	// Like the dialog manager itself, it needs them to save/restore the focus.
	ASSERT_VALID(m_pModelessSettingPropSheet);

	// Use GetCurrentMessage to get unmodified message data.
	const MSG* pMsg = GetCurrentMessage();
	ASSERT(pMsg->message == WM_ACTIVATE);
	m_pModelessSettingPropSheet->SendMessage(pMsg->message, pMsg->wParam,
		pMsg->lParam);
}