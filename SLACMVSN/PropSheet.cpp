
//
#include "stdafx.h"
#include "PropSheet.h"
IMPLEMENT_DYNAMIC(CModalSettingPropSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CModalSettingPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModalShapePropSheet)
	ON_COMMAND(ID_APPLY_NOW, OnApplyNow)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CModalSettingPropSheet::CModalSettingPropSheet(CWnd* pWndParent)
	: CPropertySheet(IDS_IDS_ProshTitle, pWndParent)
{
	AddPage(&m_userManaPage);
}

BOOL CModalSettingPropSheet::OnInitDialog()
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	// add the preview window to the property sheet.
	CRect rectWnd;
	GetWindowRect(rectWnd);
	SetWindowPos(NULL, 0, 0,
		rectWnd.Width() + 100,
		rectWnd.Height(),
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	CenterWindow();
	return bResult;
}
void CModalSettingPropSheet::OnApplyNow()
{
	Default();

	CFrameWnd* pFrameWnd = STATIC_DOWNCAST(CFrameWnd, AfxGetMainWnd());
	CView* pView = pFrameWnd->GetActiveFrame()->GetActiveView();
  //pView->SendMessage(WM_USER_CHANGE_OBJECT_PROPERTIES, 0, 0);
	m_userManaPage.SetModified(FALSE);
	SendMessage(PSM_CANCELTOCLOSE);
}
