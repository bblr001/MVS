#pragma once

#include "afxribbonbutton.h"
#include <afxcmn.h>
#ifdef _AFX_PACKING
#pragma pack(push, _AFX_PACKING)
#endif

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, off)
#endif
class CRibbonPager : public CMFCRibbonButton
{
	DECLARE_DYNCREATE(CRibbonPager)
	// Construction:
public:
	CRibbonPager():m_pagerCtrl(0){ m_pagerCtrl = new CPagerCtrl;}
	virtual ~CRibbonPager(){if(0!=m_pagerCtrl)delete m_pagerCtrl;}
private:
	 CPagerCtrl *m_pagerCtrl;
};


#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, on)
#endif

#ifdef _AFX_PACKING
#pragma pack(pop)
#endif