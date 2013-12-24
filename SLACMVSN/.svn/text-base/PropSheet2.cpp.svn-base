

#include "stdafx.h"
#include "resource.h"
#include "propsheet2.h"

IMPLEMENT_DYNAMIC(CModelessSettingPropSheet, CPropertySheet)

BEGIN_MESSAGE_MAP(CModelessSettingPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CModelessSettingPropSheet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CModelessSettingPropSheet::CModelessSettingPropSheet(CWnd* pWndParent)
: CPropertySheet(IDS_IDS_ProshTitle, pWndParent)
{
	AddPage(&m_userManager);
}

void CModelessSettingPropSheet::PostNcDestroy()
{
	CPropertySheet::PostNcDestroy();
	delete this;
}

void CModelessSettingPropSheet::SetSheetPropsFromShape(int* pShape)
{
	//m_stylePage.m_nShapeStyle = pShape->m_shapestyle;
	//	m_userManaPage.SetModified(FALSE);

	//m_colorPage.m_nColor = pShape->m_shapecolor;
	//m_colorPage.SetModified(FALSE);

	// Reflect the new shape properties in the controls of the
	// currently active property page.
	GetActivePage()->UpdateData(FALSE);
}

void CModelessSettingPropSheet::SetShapePropsFromSheet(int* pShape)
{
	//pShape->m_shapecolor = m_colorPage.m_nColor;
	//pShape->m_shapestyle = (SHAPE_STYLE)m_stylePage.m_nShapeStyle;

	//m_colorPage.SetModified(FALSE);
	//m_userManaPage.SetModified(FALSE);
}