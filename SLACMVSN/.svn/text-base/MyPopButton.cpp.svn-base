                       // MyPopButton.cpp : implementation file
//

#include "stdafx.h"
#include "SLACMVSN.h"
#include "MyPopButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
       
/////////////////////////////////////////////////////////////////////////////
// CMyPopButton

CMyPopButton::CMyPopButton()
{
}

CMyPopButton::~CMyPopButton()
{
}


BEGIN_MESSAGE_MAP(CMyPopButton, CBitmapButton)
	//{{AFX_MSG_MAP(CMyPopButton)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_CONTROL_REFLECT(BN_CLICKED, OnClicked)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPopButton message handlers
void CMyPopButton::OnClicked() 
{
	// TODO: Add your control notification handler code here
	CMenu mnuPop;
	mnuPop.LoadMenu(IDR_MENU_MYKV);
	CMenu *popup = mnuPop.GetSubMenu(0);

	CRect rcClient;
	GetWindowRect(&rcClient);
	popup->TrackPopupMenu(TPM_LEFTALIGN, rcClient.left, rcClient.bottom-1, this);
}
