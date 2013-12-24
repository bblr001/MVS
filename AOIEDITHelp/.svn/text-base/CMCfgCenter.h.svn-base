#pragma once
#include <string>
#include <set>
#include <list>
#include "cpp/HalconCpp.h"
using namespace Halcon;
class CMConfigCenter
{
public:
	static  CMConfigCenter& GetCfgCenter(){
		static CMConfigCenter _CfgCenter;
		return _CfgCenter;
	};
	virtual ~CMConfigCenter(void);
	bool  SetWndID(HWND wnd){m_sourceWndId = wnd;return true;};
	bool  InitWnd(int wndWidth,int wndHeight);
	Hlong GetHCWndID(){return m_hcDispWindowId;}
private:
	Hlong m_hcDispWindowId;
	HWND  m_sourceWndId;
protected:
	friend class CMCtrlCenter;
	CMConfigCenter(void);
};