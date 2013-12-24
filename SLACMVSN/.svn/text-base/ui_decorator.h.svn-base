#pragma once
#include <afxwin.h>
#include <atlimage.h>
#include "Resource.h"

struct ui_decorator
{
public:
	ui_decorator()
	{
		HRESULT hr = m_imgReady.Load(_T("ready.png"));
		hr = m_imgRun.Load(_T("run.png"));
		hr = m_imgAlarm.Load(_T("alarm.png"));
		hr = m_imgPause.Load(_T("pause.png"));
		hr = m_imgStop.Load(_T("stop.png"));
	}
	~ui_decorator()
	{
	}

	CImage  m_imgReady;
	CImage  m_imgRun;
	CImage  m_imgAlarm;
	CImage  m_imgPause;
	CImage  m_imgStop;
private:
	ui_decorator(const ui_decorator&);
	ui_decorator& operator=(const ui_decorator&);
};