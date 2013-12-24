#include "stdafx.h"
#include "CMCfgCenter.h"

CMCfgCenter::CMCfgCenter(void):
	m_sourceWndId(0),
	m_hcDispWindowId(0),
	m_wndHeight(600),
	m_wndWidth(800)
{
}

CMCfgCenter::~CMCfgCenter()
{
	if(m_hcDispWindowId!=0)
	{
		Halcon::close_window(m_hcDispWindowId);
	}
}
void CMCfgCenter::InitWnd(int wndWidth,int wndHeight)
{
	if(m_hcDispWindowId == 0 && m_sourceWndId != 0)
	{
		Halcon::set_check("~father");

	    if (m_imgHeight >= wndHeight||m_imgWidth >= wndWidth)
		{
			double r = (1.0 * m_imgHeight / wndHeight, 1.0 * m_imgWidth / wndWidth);
			m_imgHeight /= r;
			m_imgWidth /= r;
		}
		Halcon::open_window(0,0,m_imgWidth,m_imgHeight,(Hlong)m_sourceWndId,"visible","",&m_hcDispWindowId);
	  
		Halcon::set_check("father");
		Halcon::set_window_attr("border_width",0);
		//Halcon::set_part(m_hcDispWindowId,0,0,m_imgHeight-1,m_imgWidth-1);
		Halcon::set_draw(m_hcDispWindowId,"margin");
		Halcon::set_color((m_hcDispWindowId),"green");
		Halcon::set_line_width(m_hcDispWindowId,1);
		
  }
}