#pragma once
#include "IMActiveObj.h"
#include "MyButton.h"
#include "../SLACMVSN/ui_decorator.h"
#include <cpp/HalconCpp.h>

class CPanelManager;

#ifdef SHEET_INSPECTION

class SheetInspectionPanel :public CButton,public IMActiveObj
{
public:
	SheetInspectionPanel(CPanelManager* pPanelManager);
	virtual ~SheetInspectionPanel(void);

	virtual void Pause()
	{
		IMActiveObj::Pause();
	}
	virtual void Resume()
	{
		IMActiveObj::Resume();
	}
	void Stop();
	virtual UINT Main();
	bool ClickedRun();
	bool ClickedPause();
	int GetDisplayWndID()
	{
		return m_displayWndID;
	}
	void Init();

private:
	CPanelManager* m_pPanelManager;

	ui_decorator  m_ui_decorator;
	CMyLabel      m_sStateIndicator;
	CMyButEnter   m_btnRun;
	CMyButEnter   m_btnPause;
	CStatic       m_ctrlSheetImage; // image display window
	Hlong         m_displayWndID;
	bool          m_bExit;
	bool          m_bStarted;
	CFont         m_font;
};

#endif

