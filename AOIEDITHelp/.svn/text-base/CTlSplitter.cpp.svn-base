#include "stdafx.h"
#include "CTLSplitter.h"
/////////////////////////////////////////////////////////////////////////////
//
BEGIN_MESSAGE_MAP(CExSplitWnd, CSplitterWnd)
	//{{AFX_MSG_MAP(CExSplitWnd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

IMPLEMENT_DYNAMIC(CExSplitWnd, CSplitterWnd)

CExSplitWnd::CExSplitWnd()
{
}

CExSplitWnd::~CExSplitWnd()
{
}

CWnd* CExSplitWnd::GetActivePane(int* /*pRow*/, int* /*pCol*/)
{
	ASSERT_VALID(this);

	// attempt to use active view of frame window
	CWnd* pView = NULL;
	CFrameWnd* pFrameWnd = GetParentFrame();
	ASSERT_VALID(pFrameWnd);
	pView = pFrameWnd->GetActiveView();

	// failing that, use the current focus
	if (pView == NULL)
		pView = GetFocus();

	return pView;
}