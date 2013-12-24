#include "stdafx.h"
#include "ErrorImageDispWnd.h"
#include "MConfigCenter.h"
#include "MainFrm.h"
#include <algorithm>

using namespace std;

IMPLEMENT_DYNAMIC(CErrorImageCabinet, CDialog)

CErrorImageCabinet::CErrorImageCabinet(CWnd* pParent /*=NULL*/)
	:CDialog(CErrorImageCabinet::IDD, pParent),
	 m_errorImgBuffer(NUM)
{
    m_Pen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
	InitializeCriticalSection(&m_lock);
	m_bDoubleClieck=FALSE;
}

CErrorImageCabinet::~CErrorImageCabinet()
{
	DeleteCriticalSection(&m_lock);
}

void CErrorImageCabinet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WND1, m_disp1);
	DDX_Control(pDX, IDC_WND2, m_disp2);
	DDX_Control(pDX, IDC_WND3, m_disp3);
	DDX_Control(pDX, IDC_WND4, m_disp4);
	DDX_Control(pDX, IDC_WND5, m_disp5);
	DDX_Control(pDX, IDC_WND6, m_disp6);
	DDX_Control(pDX, IDC_WND7, m_disp7);
	DDX_Control(pDX, IDC_WND8, m_disp8);
	DDX_Control(pDX, IDC_WND9, m_disp9);
	DDX_Control(pDX, IDC_WND10, m_disp10);

	DDX_Control(pDX, IDC_WND11, m_disp11);
	DDX_Control(pDX, IDC_WND12, m_disp12);
	DDX_Control(pDX, IDC_WND13, m_disp13);
	DDX_Control(pDX, IDC_WND14, m_disp14);

	DDX_Control(pDX, IDC_WND15, m_disp15);
	DDX_Control(pDX, IDC_WND16, m_disp16);
	DDX_Control(pDX, IDC_WND17, m_disp17);
	DDX_Control(pDX, IDC_WND18, m_disp18);
	DDX_Control(pDX, IDC_WND19, m_disp19);
	DDX_Control(pDX, IDC_WND20, m_disp20);
	
}

BOOL CErrorImageCabinet::OnInitDialog()
{
	BOOL nRet = CDialog::OnInitDialog();
	return nRet;
}

void CErrorImageCabinet::AdjustDispViews(int margin,int *cx,int *cy)
{
   int intrDis = 2;
   int dim = *cx;
   int dimCy = dim * 3 / 4;
   int downMargin = margin;
   m_rectList[0].SetRect(margin,0,margin+dim,dimCy);
   m_disp1.MoveWindow(m_rectList[0]);
   margin += dim + intrDis;
   m_rectList[1].SetRect(margin,0,margin+dim,dimCy);
   m_disp2.MoveWindow(m_rectList[1]);
   margin += dim + intrDis;
    m_rectList[2].SetRect(margin,0,margin+dim,dimCy);
   m_disp3.MoveWindow(m_rectList[2]);
   margin += dim + intrDis;
    m_rectList[3].SetRect(margin,0,margin+dim,dimCy);
   m_disp4.MoveWindow(m_rectList[3]);
   margin += dim + intrDis;
    m_rectList[4].SetRect(margin,0,margin+dim,dimCy);
   m_disp5.MoveWindow(m_rectList[4]);
   margin += dim + intrDis;
    m_rectList[5].SetRect(margin,0,margin+dim,dimCy);
   m_disp6.MoveWindow(m_rectList[5]);

   margin += dim + intrDis;
    m_rectList[6].SetRect(margin,0,margin+dim,dimCy);
   m_disp7.MoveWindow(m_rectList[6]);

   margin += dim + intrDis;
   m_rectList[7].SetRect(margin,0,margin+dim,dimCy);
   m_disp8.MoveWindow(m_rectList[7]);

   margin += dim + intrDis;
   m_rectList[8].SetRect(margin,0,margin+dim,dimCy);
   m_disp9.MoveWindow(m_rectList[8]);

   margin += dim + intrDis;
   m_rectList[9].SetRect(margin,0,margin+dim,dimCy);
   m_disp10.MoveWindow(m_rectList[9]);

   int LineDis = 4;
  
   m_rectList[10].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp11.MoveWindow(m_rectList[10]);

   downMargin += dim + intrDis;
   m_rectList[11].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp12.MoveWindow(m_rectList[11]);
   downMargin += dim + intrDis;

   m_rectList[12].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp13.MoveWindow(m_rectList[12]);
   downMargin += dim + intrDis;
   
   m_rectList[13].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp14.MoveWindow(m_rectList[13]);
   downMargin += dim + intrDis;
   
   m_rectList[14].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp15.MoveWindow(m_rectList[14]);
   downMargin += dim + intrDis;
   m_rectList[15].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp16.MoveWindow(m_rectList[15]);
   
   downMargin += dim + intrDis;
   m_rectList[16].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp17.MoveWindow(m_rectList[16]);
   

   downMargin += dim + intrDis;
   m_rectList[17].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp18.MoveWindow(m_rectList[17]);

   downMargin += dim + intrDis;
   m_rectList[18].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp19.MoveWindow(m_rectList[18]);


   downMargin += dim + intrDis;
   m_rectList[19].SetRect(downMargin,dimCy + LineDis,downMargin+dim,dimCy*2 + LineDis);
   m_disp20.MoveWindow(m_rectList[19]);

   *cx = dim;
   *cy = dimCy;


   CRect rec;
   rec.SetRectEmpty();

   set_check("~father");
   m_disp1.GetWindowRect(&rec);
   open_window(0,0,m_rectList[0].Width(),m_rectList[0].Height(),(Hlong)m_disp1.m_hWnd,"visible","",&m_HalconWndID[0]);
   set_color(m_HalconWndID[0],"red");
   set_check("father");

   set_check("~father");
   m_disp2.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp2.m_hWnd,"visible","",&m_HalconWndID[1]);
   set_color(m_HalconWndID[1],"red");
   set_check("father");

   set_check("~father");
   m_disp3.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp3.m_hWnd,"visible","",&m_HalconWndID[2]);
   set_color(m_HalconWndID[2],"red");
   set_check("father");

   set_check("~father");
   m_disp4.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp4.m_hWnd,"visible","",&m_HalconWndID[3]);
   set_color(m_HalconWndID[3],"red");
   set_check("father");

   set_check("~father");
   m_disp5.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp5.m_hWnd,"visible","",&m_HalconWndID[4]);
   set_color(m_HalconWndID[4],"red");
   set_check("father");

   set_check("~father");
   m_disp6.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp6.m_hWnd,"visible","",&m_HalconWndID[5]);
   set_color(m_HalconWndID[5],"red");
   set_check("father");

   set_check("~father");
   m_disp7.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp7.m_hWnd,"visible","",&m_HalconWndID[6]);
   set_color(m_HalconWndID[6],"red");
   set_check("father");

   set_check("~father");
   m_disp8.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp8.m_hWnd,"visible","",&m_HalconWndID[7]);
   set_color(m_HalconWndID[7],"red");
   set_check("father");

   set_check("~father");
   m_disp9.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp9.m_hWnd,"visible","",&m_HalconWndID[8]);
   set_color(m_HalconWndID[8],"red");
   set_check("father");

   set_check("~father");
   m_disp10.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp10.m_hWnd,"visible","",&m_HalconWndID[9]);
   set_color(m_HalconWndID[9],"red");
   set_check("father");

   set_check("~father");
   m_disp11.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp11.m_hWnd,"visible","",&m_HalconWndID[10]);
   set_color(m_HalconWndID[10],"red");
   set_check("father");

   set_check("~father");
   m_disp12.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp12.m_hWnd,"visible","",&m_HalconWndID[11]);
   set_color(m_HalconWndID[11],"red");
   set_check("father");

   set_check("~father");
   m_disp13.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp13.m_hWnd,"visible","",&m_HalconWndID[12]);
   set_color(m_HalconWndID[12],"red");
   set_check("father");

   set_check("~father");
   m_disp14.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp14.m_hWnd,"visible","",&m_HalconWndID[13]);
   set_color(m_HalconWndID[13],"red");
   set_check("father");

   set_check("~father");
   m_disp15.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp15.m_hWnd,"visible","",&m_HalconWndID[14]);
   set_color(m_HalconWndID[14],"red");
   set_check("father");

   set_check("~father");
   m_disp16.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp16.m_hWnd,"visible","",&m_HalconWndID[15]);
   set_color(m_HalconWndID[15],"red");
   set_check("father");

   set_check("~father");
   m_disp17.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp17.m_hWnd,"visible","",&m_HalconWndID[16]);
   set_color(m_HalconWndID[16],"red");
   set_check("father");

   set_check("~father");
   m_disp18.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp18.m_hWnd,"visible","",&m_HalconWndID[17]);
   set_color(m_HalconWndID[17],"red");
   set_check("father");

   set_check("~father");
   m_disp19.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp19.m_hWnd,"visible","",&m_HalconWndID[18]);
   set_color(m_HalconWndID[18],"red");
   set_check("father");

   set_check("~father");
   m_disp20.GetWindowRect(&rec);
   open_window(0,0,rec.Width(),rec.Height(),(Hlong)m_disp20.m_hWnd,"visible","",&m_HalconWndID[19]);
   set_color(m_HalconWndID[19],"red");
   set_check("father");
}

BEGIN_MESSAGE_MAP(CErrorImageCabinet, CDialog)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_STN_DBLCLK(IDC_WND1, &CErrorImageCabinet::OnStnDblclickWnd1)
	ON_STN_DBLCLK(IDC_WND2, &CErrorImageCabinet::OnStnDblclickWnd2)

	ON_STN_DBLCLK(IDC_WND3, &CErrorImageCabinet::OnStnDblclickWnd3)
	ON_STN_DBLCLK(IDC_WND4, &CErrorImageCabinet::OnStnDblclickWnd4)
	ON_STN_DBLCLK(IDC_WND5, &CErrorImageCabinet::OnStnDblclickWnd5)
	ON_STN_DBLCLK(IDC_WND6, &CErrorImageCabinet::OnStnDblclickWnd6)
	ON_STN_DBLCLK(IDC_WND7, &CErrorImageCabinet::OnStnDblclickWnd7)
	ON_STN_DBLCLK(IDC_WND8, &CErrorImageCabinet::OnStnDblclickWnd8)
	ON_STN_DBLCLK(IDC_WND9, &CErrorImageCabinet::OnStnDblclickWnd9)
	ON_STN_DBLCLK(IDC_WND10, &CErrorImageCabinet::OnStnDblclickWnd10)
	ON_STN_DBLCLK(IDC_WND11, &CErrorImageCabinet::OnStnDblclickWnd11)
	ON_STN_DBLCLK(IDC_WND12, &CErrorImageCabinet::OnStnDblclickWnd12)
	ON_STN_DBLCLK(IDC_WND13, &CErrorImageCabinet::OnStnDblclickWnd13)
	ON_STN_DBLCLK(IDC_WND14, &CErrorImageCabinet::OnStnDblclickWnd14)
	ON_STN_DBLCLK(IDC_WND15, &CErrorImageCabinet::OnStnDblclickWnd15)
	ON_STN_DBLCLK(IDC_WND16, &CErrorImageCabinet::OnStnDblclickWnd16)
	ON_STN_DBLCLK(IDC_WND17, &CErrorImageCabinet::OnStnDblclickWnd17)
	ON_STN_DBLCLK(IDC_WND18, &CErrorImageCabinet::OnStnDblclickWnd18)
	ON_STN_DBLCLK(IDC_WND19, &CErrorImageCabinet::OnStnDblclickWnd19)
	ON_STN_DBLCLK(IDC_WND20, &CErrorImageCabinet::OnStnDblclickWnd20)

END_MESSAGE_MAP()

// CErrorImageCabinet 消息处理程序
void CErrorImageCabinet::OnPaint()
{
	CPaintDC dc(this);
	CDialog::OnPaint();
}

void CErrorImageCabinet::DrawRec(CRect rect)
{
	CDC* pDC = GetDC();

	RedrawWindow();
	m_points[0].x = rect.left;
	m_points[0].y = rect.top;
	m_points[1].x = rect.right-1;
	m_points[1].y = rect.top;
	m_points[2].x = rect.right-1;
	m_points[2].y = rect.bottom-1;
	m_points[3].x = rect.left;
	m_points[3].y = rect.bottom-1;
	m_points[4].x = rect.left;
	m_points[4].y = rect.top;

	pDC-> SelectObject(m_Pen);
	pDC->SetDCPenColor(RGB(0xFF,0,0));
	pDC->Polyline(m_points,5);	
}

void CErrorImageCabinet::DisplayCurrentErrorImage(CMData* pData)
{
	Hlong wndID = CMConfigCenter::GetSingletonConfigCenter()->GetLogWindowHID();
	set_color(wndID,"red");
	disp_obj(pData->m_Image,wndID);	
#ifdef EOE_INSPECTION
	dilation_circle(pData->m_ErrorRegist,&pData->m_ErrorRegist,2.5);
#endif

#ifdef SHEET_INSPECTION
	dilation_circle(pData->m_ErrorRegist,&pData->m_ErrorRegist,25);
#endif
	disp_obj(pData->m_ErrorRegist,wndID);
	std::for_each(pData->m_vSubTestResult.begin(), pData->m_vSubTestResult.end(), [&](SubTestResult& result)
	{
		if(result.m_bFailSubTest)
		{
			disp_circle(wndID, result.m_ErrorY, result.m_ErrorX, result.m_ErrorR);
		}
	});
}

void CErrorImageCabinet::ShowErrorLogPic(CMData* pData)
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();

	if(pConfigCenter->GetErrorImgPausedFlag() == false)
	{
		DisplayCurrentErrorImage(pData);
	}

	IMAGE_SIZE size = pConfigCenter->GetImageSize();

	if(!m_errorImgBuffer.is_not_full())
	{
		CMData ret;
		m_errorImgBuffer.pop_back(&ret);
	}
	EnterCriticalSection(&m_lock);
	m_errorImgBuffer.push_front(*pData);
	LeaveCriticalSection(&m_lock);
	

	HTuple Millisecond,Second,Minute,Hour,Day,YDay,Month,Year;
	int imgCount = m_errorImgBuffer.size();
	for(int t = 0; t < imgCount; t++)
	{
		HTuple Millisecond,Second,Minute,Hour,Day,YDay,Month,Year;
		get_image_time(m_errorImgBuffer[t].m_Image,&Millisecond,&Second,&Minute,&Hour,&Day,&YDay,&Month,&Year);
		set_part(m_HalconWndID[t],0,0,size.m_ImageHeight-1,size.m_ImageWidth-1);
		disp_obj(m_errorImgBuffer[t].m_Image,m_HalconWndID[t]);
		set_tposition(m_HalconWndID[t], 3, 45);
		write_string(m_HalconWndID[t], Hour +HTuple(":") + Minute + HTuple(":") + Second);
	}
};

void CErrorImageCabinet::UpdateWindow(int i)
{
	int temp = i;
	if(temp > m_errorImgBuffer.size() - 1)
	{		
		return;
	}
	CMConfigCenter::GetSingletonConfigCenter()->SetErrorImgPausedFlag(true);
	//EnterCriticalSection(&m_lock);
	//CMData data = m_errorImgBuffer[temp];
	//LeaveCriticalSection(&m_lock);


	Hlong wndID = CMConfigCenter::GetSingletonConfigCenter()->GetLogWindowHID();
	set_color(wndID,"red");
	disp_obj(m_errorImgBuffer[temp].m_Image,wndID);	
#ifdef EOE_INSPECTION
	dilation_circle(m_errorImgBuffer[temp].m_ErrorRegist,&m_errorImgBuffer[temp].m_ErrorRegist,2.5);
#endif

#ifdef SHEET_INSPECTION
	dilation_circle(m_errorImgBuffer[temp].m_ErrorRegist,&m_errorImgBuffer[temp].m_ErrorRegist,25);
#endif
	disp_obj(m_errorImgBuffer[temp].m_ErrorRegist,wndID);
// 	std::for_each(m_errorImgBuffer[temp].m_vSubTestResult.begin(), m_errorImgBuffer[temp].m_vSubTestResult.end(), [&](SubTestResult& result)
// 	{
// 		if(result.m_bFailSubTest)
// 		{
// 			disp_circle(wndID, result.m_ErrorY, result.m_ErrorX, result.m_ErrorR);
// 		}
// 	});
	
	CMConfigCenter::GetSingletonConfigCenter()->SetLogWindowImage(m_errorImgBuffer[temp].m_Image);

	DrawRec(m_rectList[temp]);
	CMainFrame* pMainFrm = (CMainFrame*)(AfxGetApp()->m_pMainWnd); 
	pMainFrm->OneShotGrabErrPic();
}

#pragma region Window Event
void CErrorImageCabinet::OnStnDblclickWnd1()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(0);
	LeaveCriticalSection(&m_lock);
}

void CErrorImageCabinet::OnStnDblclickWnd2()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(1);
	LeaveCriticalSection(&m_lock);	
}

void CErrorImageCabinet::OnStnDblclickWnd3()
{

	EnterCriticalSection(&m_lock);
	UpdateWindow(2);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd4()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(3);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd5()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(4);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd6()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(5);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd7()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(6);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd8()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(7);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd9()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(8);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd10()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(9);
	LeaveCriticalSection(&m_lock);
}
void CErrorImageCabinet::OnStnDblclickWnd11()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(10);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd12()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(11);
	LeaveCriticalSection(&m_lock);
}
void CErrorImageCabinet::OnStnDblclickWnd13()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(12);
	LeaveCriticalSection(&m_lock);
}
void CErrorImageCabinet::OnStnDblclickWnd14()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(13);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd15()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(14);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd16()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(15);
	LeaveCriticalSection(&m_lock);
}
void CErrorImageCabinet::OnStnDblclickWnd17()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(16);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd18()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(17);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd19()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(18);
	LeaveCriticalSection(&m_lock);	
}
void CErrorImageCabinet::OnStnDblclickWnd20()
{
	EnterCriticalSection(&m_lock);
	UpdateWindow(19);
	LeaveCriticalSection(&m_lock);	
}

#pragma endregion Window Event
