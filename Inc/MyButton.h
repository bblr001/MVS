
#pragma once
#include "..\Inc\TypeCent.h"

/////////////////////////////////////////////////////////////////////////////
// CMTIButSet window
enum eBUTTON_TYPE {NONE_DEF,BT_ENTER,BT_RUN,BT_PAUSE,BT_ALARM,BT_QUERY,BT_RECOUNT}; 
enum ePANEL_TYPE  {PT_NORMAL = 0, PT_SHEET_INSPECTION};

class CMyPanel;

class CMyButEnter : public CButton
{
// Construction
public:
	CMyButEnter();

public:
	void SetPanelID(const CHANNEL_SETTING& setting)
	{
		m_Station->szStationID   = setting.szStationID;
		m_Station->szProgramName = setting.szProgramName;
		memcpy(&m_Station->m_pi,&setting.m_pi,sizeof(setting.m_pi));
	};
	void SetPanelType(ePANEL_TYPE type = PT_NORMAL)
	{
		m_panelType = type;
	}
	void SetButtonType(eBUTTON_TYPE type)
	{
		m_btnType = type;
	}
	template<class T>
	void SetPanelPoint(T *pPanel)
	{
		m_pPanel = (void*)pPanel;
	}
public:
	virtual ~CMyButEnter();

	// Generated message map functions
protected:
	CHANNEL_SETTING*   m_Station;
	eBUTTON_TYPE  m_btnType;
	ePANEL_TYPE   m_panelType;
	void*         m_pPanel;
	afx_msg void  OnClicked();
	DECLARE_MESSAGE_MAP()
};