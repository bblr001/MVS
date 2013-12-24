#include "stdafx.h"
#include "CMCfgCenter.h"

CMConfigCenter::CMConfigCenter(void):m_sourceWndId(0)
{}
CMConfigCenter::~CMConfigCenter(){
	if (0!=m_hcDispWindowId)
	{
		Halcon::close_window(m_hcDispWindowId);
	}
}
bool CMConfigCenter::InitWnd(int wndWidth,int wndHeight)
{
  bool bRet = false;
  ASSERT(0!=m_sourceWndId);
  if (0!=m_sourceWndId)
  {
	  Halcon::set_check("~father");
	  Halcon::open_window(0,0,wndWidth,wndHeight,(Hlong)m_sourceWndId,"visible","",&(m_hcDispWindowId));
	  Halcon::set_check("father");
	  bRet = true;
  }
  return bRet;
}