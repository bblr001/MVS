#pragma once
#ifndef __RIBBONPAGER_H__
#define __RIBBONPAGER_H__

#include "afxcontrolbarutil.h"
#include "afxbaseribbonelement.h"

#ifdef _AFX_PACKING
#pragma pack(push, _AFX_PACKING)
#endif

#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, off)
#endif

#define AFX_RIBBON_IMAGE_AUTO 9999

class CMRibbonPage : public CMFCRibbonBaseElement
{
	DECLARE_DYNCREATE(CMRibbonPage)

public:
	CMRibbonPage();
	~CMRibbonPage();

protected:
	virtual void OnDraw(CDC* pDC);
	virtual CSize GetRegularSize(CDC* pDC);
private:
	BOOL InitCTRL(CRect &rt);
    BOOL m_bInit;
};
#ifdef _AFX_MINREBUILD
#pragma component(minrebuild, on)
#endif

#ifdef _AFX_PACKING
#pragma pack(pop)
#endif
#endif