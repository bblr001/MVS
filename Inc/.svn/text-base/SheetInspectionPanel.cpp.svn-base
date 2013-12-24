#include "StdAfx.h"
#include <algorithm>
#include "PanelManager.h"
#include "SheetInspectionPanel.h"
#include "..\slacmvsn\MainFrm.h"

using namespace std;


#ifdef SHEET_INSPECTION

SheetInspectionPanel::SheetInspectionPanel(CPanelManager* pPanelManager)
{
	m_pPanelManager = pPanelManager;
	m_bExit         = false;
	m_displayWndID  = 0;

	m_font.CreateFont(
		16,                        // nHeight
		0,                         // nWidth
		0,                         // nEscapement
		0,                         // nOrientation
		FW_NORMAL,	                // nWeight
		FALSE,                     // bItalic
		FALSE,                     // bUnderline
		0,                         // cStrikeOut
		ANSI_CHARSET,              // nCharSet
		OUT_DEFAULT_PRECIS,        // nOutPrecision
		CLIP_DEFAULT_PRECIS,       // nClipPrecision
		DEFAULT_QUALITY,           // nQuality
		DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
		_T("Arial"));

	m_bStarted = false;
}

SheetInspectionPanel::~SheetInspectionPanel(void)
{
}

void SheetInspectionPanel::Init()
{
	int iWidth  = 1400;
	int iHeight = 750;

	RECT rect;
	rect.left = 10;
	rect.top =  10;
	rect.right = rect.left + iWidth;
	rect.bottom = rect.top + iHeight;

	CWnd* pMainView  = ((CMainFrame*)AfxGetMainWnd())->SOverViewWnd;
	//将逻辑坐标转换为物理坐标
	CClientDC   dc(pMainView);   
	dc.LPtoDP(&rect);    

	CString strPanel = _T("Sheet Inspection");
	Create(strPanel,WS_CHILD|WS_VISIBLE|BS_GROUPBOX,rect,pMainView,331);
	SetOwner(pMainView);
	
	m_sStateIndicator.Create(_T(""), WS_CHILD|WS_VISIBLE,CRect(20,30,138,143), this);
	m_sStateIndicator.SetColor(RGB(10,10,115),RGB(200,220,250));
	m_sStateIndicator.Invalidate();
	m_sStateIndicator.SetPtr2UiDecorator(&m_ui_decorator);
	m_sStateIndicator.UpdateSytemStatusSymbol(MTI_GUI_IDLE);

	CString tmp;
#ifdef _ENGLISH
	tmp = _T("Run");
#else
	tmp = _T("运行");
#endif
	m_btnRun.Create(tmp,WS_CHILD|WS_VISIBLE,CRect(40,160,110,230),this,NULL);
	m_btnRun.SetFont(&m_font);
	m_btnRun.SetButtonType(BT_RUN);
	m_btnRun.SetPanelType(PT_SHEET_INSPECTION);
	m_btnRun.SetPanelPoint(this);

#ifdef _ENGLISH
	tmp = _T("Pause");
#else
	tmp = _T("暂停");
#endif
	m_btnPause.Create(tmp,WS_CHILD|WS_VISIBLE,CRect(40,240,110,310),this,NULL);
	m_btnPause.SetFont(&m_font);
	m_btnPause.SetButtonType(BT_PAUSE);
	m_btnPause.SetPanelType(PT_SHEET_INSPECTION);
	m_btnPause.SetPanelPoint(this);

	CRect imgRect(180, 50, 1400, 700);
	m_ctrlSheetImage.Create( _T("Sheet Inspection"), WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS | SS_BITMAP ,imgRect,this);

    Hobject  initIimage;
	int width  = 600;
	int height = 580;
	unsigned char  image[348000];

	for (int r = 0; r < height; r++)
		for (int c = 0; c < width; c++)
			image[r * height + c] = c % 255;

	gen_image1(&initIimage,"byte",600,580,(long)image);
	set_check("~father");
	open_window(0,0,imgRect.Width(),imgRect.Height(),(Hlong)m_ctrlSheetImage.m_hWnd, "visible", "", &m_displayWndID);	
	set_check("father");
	set_draw(m_displayWndID,"margin"); //margin or fill
	disp_obj(initIimage, m_displayWndID);
	set_line_width(m_displayWndID,HTuple(1));
}

UINT SheetInspectionPanel::Main()
{
	m_bExit = false;
	while(!m_bExit)
	{
		if(m_pPanelManager->GetSheetImageReadyFlag())
		{
			Hobject sheetImage;
			std::vector<Hobject> errorRgns;
			if(m_pPanelManager->ProcessChannelInspectionResult(sheetImage, errorRgns))
			{
				clear_window(m_displayWndID);
				disp_obj(sheetImage, m_displayWndID);
				set_color(m_displayWndID,"red");
				std::for_each(errorRgns.begin(), errorRgns.end(), [&](Hobject& errorMark)
				{
					disp_obj(errorMark, m_displayWndID);
				});
				m_pPanelManager->SetNewLoopBeginFlag(true);
				m_pPanelManager->ResetSheetImageReadyFlag();
				m_pPanelManager->EnableWriteTestFailFlag();
			}
			else
			{
				clear_window(m_displayWndID);
				set_color(m_displayWndID, "red");
				set_tposition(m_displayWndID, 145, 145);
				write_string(m_displayWndID,"CanBody concat failure, please Wait!\n");
			}
		}
		Sleep(20);
	}
	return 0;
}

bool SheetInspectionPanel::ClickedRun()
{
	m_sStateIndicator.UpdateSytemStatusSymbol(MTI_GUI_RUN);

	if(m_pPanelManager != nullptr)
	{
		if(!m_bStarted)
		{
			m_pPanelManager->TriggerAllChannels();
			m_bStarted = true;
		}
		else
		{
			auto pPanels = m_pPanelManager->GetPanelContainerPtr();
			std::for_each(pPanels->begin(), pPanels->end(),[&](CMyPanel* pPanel)
			{
				pPanel->ClickedRun();
			});
		}
		return true;
	}
	return false;
}

bool SheetInspectionPanel::ClickedPause()
{
	m_sStateIndicator.UpdateSytemStatusSymbol(MTI_GUI_PAUSE);

	if(m_pPanelManager != nullptr)
	{
		auto pPanels = m_pPanelManager->GetPanelContainerPtr();
		size_t sz = pPanels->size();
		std::for_each(pPanels->begin(), pPanels->end(),[&](CMyPanel* pPanel)
		{
			pPanel->ClickedPause();
		});
		return true;
	}
	return false;
}

void SheetInspectionPanel::Stop()
{
	if(m_pPanelManager != nullptr)
	{
		auto pPanels = m_pPanelManager->GetPanelContainerPtr();
		std::for_each(pPanels->begin(), pPanels->end(),[&](CMyPanel* pPanel)
		{
			pPanel->Stop();
		});
	}
}

#endif
