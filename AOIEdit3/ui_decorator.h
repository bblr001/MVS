#pragma once
#include <afxwin.h>
#include <atlimage.h>

struct ui_decorator
{
public:
	ui_decorator():m_nMarginWidth(16)
	{
		m_brushFrame.CreateSolidBrush(RGB(15,105,165));
		m_brushBk.CreateSolidBrush(RGB(11,122,193));
		HRESULT hr = m_imgOkBlack.Load(_T("accept_32_2.png"));
		hr = m_imgDenyBlack.Load(_T("deny_32_2.png"));
	}
	~ui_decorator()
	{
		//m_imgOkBlack.ReleaseDC();
		//m_imgDenyBlack.ReleaseDC();
	}

	CBrush  m_brushFrame;
	CBrush  m_brushBk; // background brush
	CImage  m_imgOkBlack;
	CImage  m_imgDenyBlack;

	int m_nMarginWidth;  // pixels

private:
	ui_decorator(const ui_decorator&);
	ui_decorator& operator=(const ui_decorator&);
};