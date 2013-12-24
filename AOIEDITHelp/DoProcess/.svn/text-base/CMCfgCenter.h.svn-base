#pragma once
#include <string>
#include <set>
#include <list>
#include "CMData.h"
#include "..\..\Inc\TypeCent.h"
using namespace Halcon;
class CMCfgCenter
{
public:
	static  CMCfgCenter& GetCfgCenter()
	{
		static CMCfgCenter _CfgCenter;
		return _CfgCenter;
	};
	virtual ~CMCfgCenter(void);
	bool  SetWndID(HWND wnd){m_sourceWndId = wnd;return true;};
	HWND  GetWndID(){return m_sourceWndId;}
	Hlong GetHCWnd(){return m_hcDispWindowId;}
	void  InitWnd(int wndWidth,int wndHeight);
	void  SetFilePath(string path){m_file_path = path;}
	const string& GetFilePath() const { return m_file_path;}

	eDRAW_SHAPE GetDrawShape(){return m_DrawShape;};
	void SetDrawShape(eDRAW_SHAPE shape){m_DrawShape=shape;};

	void GetImageSize(long& width, long& height)
	{
		width = m_imgWidth;
		height = m_imgHeight;
	}

	void SetImageSize(long width, long height)
	{
		m_imgWidth = width;
		m_imgHeight = height;
	}

private:
	HWND m_sourceWndId;
	Hlong m_hcDispWindowId;
	int   m_wndWidth;
	int   m_wndHeight;
	string m_file_path;
	eDRAW_SHAPE m_DrawShape;
	long m_imgHeight;
	long m_imgWidth;
protected:
	friend class CMCtrlCenter;
	CMCfgCenter(void);
};