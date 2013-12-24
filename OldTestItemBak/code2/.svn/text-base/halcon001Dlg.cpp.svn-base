// halcon001Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "halcon001.h"
#include "halcon001Dlg.h"
#include "HalconCpp.h"
#include "Halcon.h"
#include "cpp\HCPPGlobal.h"
//#pragma   comment(lib, "C1.lib ")


using namespace Halcon ;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP

}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHalcon001Dlg dialog

CHalcon001Dlg::CHalcon001Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHalcon001Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHalcon001Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hInst=NULL;  
}


void CHalcon001Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHalcon001Dlg)
	DDX_Control(pDX, IDC_BUTTON1, m_pic);
	DDX_Control(pDX, IDC_STATIC_TEST,m_Test);
	DDX_Control(pDX, IDC_STATIC_NeedTime,m_NeedTime);
   // DDX_Control(pDX, IDC_STATIC_FLAG,m_Flag11);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHalcon001Dlg, CDialog)
	//{{AFX_MSG_MAP(CHalcon001Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, On_Bn_Open)
	ON_BN_CLICKED(IDC_BUTTON2, On_Bn_Step1)
	ON_BN_CLICKED(IDC_Bn_Close, OnBnClose)
	ON_BN_CLICKED(IDC_STATIC_FLAG, OnStaticFlag)
	ON_BN_CLICKED(IDC_STATIC_NeedTime, OnSTATICNeedTime)
	ON_BN_CLICKED(IDC_Bn_Juanbian, On_Bn_Juanbian)
	ON_BN_CLICKED(IDC_Bn_jiao, On_Bn_jiao)
	ON_BN_CLICKED(IDC_Bn_qian, On_Bn_qian)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Bn_jin, &CHalcon001Dlg::On_Bn_jin)
	ON_BN_CLICKED(IDC_Bn_tai, &CHalcon001Dlg::OnBnClickedBntai)
	ON_BN_CLICKED(IDC_Bn_Test, &CHalcon001Dlg::On_Bn_Test)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHalcon001Dlg message handlers

BOOL CHalcon001Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
 

	



	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHalcon001Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CHalcon001Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CHalcon001Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHalcon001Dlg::On_Bn_Open() 
{
	// TODO: Add your control notification handler code here


	OnFileOpen();

// 	HImage Mandrill(szGetName);
// 	HWindow w;
// 	Mandrill.Display(w);
// 	w.Click();

	read_image(&image, szGetName);
	
	CRect    rect;	
	
	m_Test.GetClientRect(&rect);
	
	wWindowID = (Hlong)m_Test.m_hWnd;
	set_check("~father");
	open_window(0,0,rect.Width(),rect.Height(),wWindowID,"visible","",&FGHandle);
	set_check("father");
	
	
	set_draw(FGHandle,"margin");

	char lpcsType[MAX_STRING];

	
//	get_image_size(image, &Width, &Height);
	get_image_pointer1(image, &Pointer, lpcsType, &Width, &Height);
	
	disp_obj(image, FGHandle);
	



}

void CHalcon001Dlg::On_Bn_Step1() 
{
	
	// TODO: Add your control notification handler code here    
//初始化


	HTuple T1, T2;

	Hobject Circle1, Circle2;
	long Cx=(long) Width/2;
	long Cy=(long) Height/2;


	gen_circle(&Circle1, Cy, Cx, Cy+60);
	gen_circle(&Circle2, Cy, Cx, 120);

	disp_obj(Circle1, FGHandle);
	disp_obj(Circle2, FGHandle);

count_seconds(&T1);

	Hlong area, obj_no;
	double Ayy,  Axx;
	HTuple TR, Tyy, Txx;
	
	
Hobject RegionDifference, ImageReduced, ImageSmooth, threshed, ConnectedRegions, RegionDilation, Skeleton, SelectedRegions, RegionUnion;

difference (Circle1, Circle2, &RegionDifference);
reduce_domain (image, RegionDifference, &ImageReduced);

smooth_image (ImageReduced, &ImageSmooth, "deriche2", 0.5);

threshold (ImageReduced, &threshed, 80, 255);
connection (threshed, &ConnectedRegions);
dilation_circle (ConnectedRegions, &RegionDilation, 2.5);
skeleton (RegionDilation, &Skeleton);

count_obj (Skeleton, &obj_no);

select_shape (Skeleton, &SelectedRegions, ("outer_radius"), "and", (225), (400));





count_obj (SelectedRegions, &obj_no);

union1 (Skeleton, &RegionUnion);

smallest_circle (RegionUnion, &Tyy, &Txx, &TR);


double Ty =Tyy[0];
double Tx=Txx[0];
double Tr=TR[0];
set_color(FGHandle,"red");
gen_circle(&Circle1, Ty, Tx, Tr);
disp_obj(Circle1, FGHandle);


























///////////////////////////////////////////////////////////////////
/////////////////////////////////////圆心 法一

// 	count_seconds(&T1);
// 
// 	double BackGrayVal_up, BackGrayVal_down, BackGrayVal_left, BackGrayVal_right, tem1,tem2,tem3,tem4;
// 
// 	Thred_center1=35;
// 	Hlong Cxx=Width/2;
// 	Hlong Cyy=Height/2;
//     get_grayval (image, Cyy, Cxx-Cyy, &tem1);
// 	get_grayval (image, Cyy, Cxx+Cyy, &tem2);
// 	get_grayval (image, 3, Cxx, &tem3);
// 	get_grayval (image, 2*Cyy-3, Cxx, &tem4);
// 	BackGrayVal_left=tem1;
// 	BackGrayVal_right=tem2;
// 	BackGrayVal_up=tem3;
// 	BackGrayVal_down=tem4;
//     get_grayval (image, Cyy, Cxx-Cyy+3,  &tem1);
// 	get_grayval (image, Cyy, Cxx+Cyy-3,  &tem2);
// 	get_grayval (image, 6, Cxx,  &tem3);
// 	get_grayval (image, 2*Cyy-6, Cxx, &tem4);
// 	BackGrayVal_left=BackGrayVal_left+tem1;
// 	BackGrayVal_right=BackGrayVal_right+tem2;
// 	BackGrayVal_up=BackGrayVal_up+tem3;
// 	BackGrayVal_down=BackGrayVal_down+tem4;
// 	get_grayval (image, Cyy, Cxx-Cyy+6,  &tem1);
// 	get_grayval (image, Cyy, Cxx+Cyy-6,  &tem2);
// 	get_grayval (image, 9, Cxx,  &tem3);
// 	get_grayval (image, 2*Cyy-9, Cxx, &tem4);
// 	BackGrayVal_left=BackGrayVal_left+tem1;
// 	BackGrayVal_right=BackGrayVal_right+tem2;
// 	BackGrayVal_up=BackGrayVal_up+tem3;
// 	BackGrayVal_down=BackGrayVal_down+tem4;
// 	BackGrayVal_left=BackGrayVal_left/3;
// 	BackGrayVal_right=BackGrayVal_right/3;
// 	BackGrayVal_up=BackGrayVal_up/3;
// 	BackGrayVal_down=BackGrayVal_down/3;
// 	
// 
// 	Hlong Txx_left=Cxx-Cyy+3;
//     get_grayval (image, Cyy, Txx_left, &tem1);
// 	while (tem1-BackGrayVal_left<Thred && Txx_left<Cxx)
// 	{
// 		Txx_left=Txx_left+3;
// 		get_grayval (image, Cyy, Txx_left, &tem1);
// 	}
// 	get_grayval (image, Cyy, Txx_left-1, &tem1);
// 	if (tem1-BackGrayVal_left>=Thred)
// 		{Txx_left=Txx_left-1;
// 		get_grayval (image, Cyy, Txx_left-1, &tem1);
//     	if (tem1-BackGrayVal_left>=Thred)
// 			{Txx_left=Txx_left-1;
// 			}
// 		}
// 	Txx_left=Txx_left+2;
// 
// 	Hlong Txx_right=Cxx+Cyy-3;
// 	get_grayval (image, Cyy, Txx_right, &tem2);
// 	while (tem2-BackGrayVal_right<Thred && Txx_right>Cxx)
// 	{
// 		Txx_right=Txx_right-3;
// 		get_grayval (image, Cyy, Txx_right, &tem2);
// 	}
// 	get_grayval (image, Cyy, Txx_right+1, &tem2);
// 	if (tem2-BackGrayVal_right>=Thred)
// 		{Txx_right=Txx_right+1;	
// 		get_grayval (image, Cyy, Txx_right+1, &tem2);
// 		if (tem2-BackGrayVal_right>=Thred)
// 			{Txx_right=Txx_right+1;
// 			}
// 		}
// 	Txx_right=Txx_right+2;
// 
// 	Hlong Tyy_down=2*Cyy-3;
//     get_grayval (image, Tyy_down, Cxx, &tem3);
// 	while (tem3-BackGrayVal_down<Thred && Tyy_down>Cyy)
// 	{
// 		Tyy_down=Tyy_down-3;
// 		get_grayval (image, Tyy_down, Cxx, &tem3);
// 	}
// 	get_grayval (image, Tyy_down+1, Cxx, &tem3);
// 	if (tem3-BackGrayVal_down>=Thred)
// 		{Tyy_down=Tyy_down+1;
// 		get_grayval (image, Tyy_down+1, Cxx, &tem3);
// 		if (tem3-BackGrayVal_down>=Thred)
// 			{Tyy_down=Tyy_down+1;
// 			}
// 		}
// 	Tyy_down=Tyy_down+2;
// 
// 	Hlong Tyy_up=3;
//     get_grayval (image, Tyy_up, Cxx, &tem4);
// 	while (tem4-BackGrayVal_up<Thred && Tyy_up<Cyy)
// 	{
// 		Tyy_up=Tyy_up+3;
// 		get_grayval (image, Tyy_up, Cxx, &tem4);
// 	}
// 	get_grayval (image, Tyy_up, Cxx-1, &tem4);
// 	if (tem4-BackGrayVal_up>=Thred)
// 		{Tyy_up=Tyy_up-1;
// 		get_grayval (image, Tyy_up, Cxx-1, &tem4);
// 		if (tem4-BackGrayVal_up>=Thred)
// 			{Tyy_up=Tyy_up-1;
// 			}
// 		}
// 	Tyy_up=Tyy_up+2;
// 
//     //Hlong Txx, Tyy, TR;
// 	Txx=(Txx_left+Txx_right)/2;
// 	Tyy=(Tyy_up+Tyy_down+1)/2;


/////////////////////////////////////////////////////////////////////
	//////////////////////////////////圆心 法二


// 
// 	count_seconds(&T1);
// 
// 	double BackGrayVal_right_up, BackGrayVal_left_down, BackGrayVal_left_up, BackGrayVal_right_down, tem1,tem2,tem3,tem4;
// 
// 	Thred_center2=70;
// 	Hlong Cxx=Width/2;
// 	Hlong Cyy=Height/2;
//     get_grayval (image, 3, Cxx-Cyy+3, &tem1);
// 	get_grayval (image, 3, Cxx+Cyy-3, &tem2);
// 	get_grayval (image, 2*Cyy-3, Cxx+Cyy-3, &tem3);
// 	get_grayval (image, 2*Cyy-3, Cxx-Cyy+3, &tem4);
// 	BackGrayVal_left_up=tem1;
// 	BackGrayVal_right_up=tem2;
// 	BackGrayVal_right_down=tem3;
// 	BackGrayVal_left_down=tem4;
// 	get_grayval (image, 6, Cxx-Cyy+6, &tem1);
// 	get_grayval (image, 6, Cxx+Cyy-6, &tem2);
// 	get_grayval (image, 2*Cyy-6, Cxx+Cyy-6, &tem3);
// 	get_grayval (image, 2*Cyy-6, Cxx-Cyy+6, &tem4);
// 	BackGrayVal_left_up=BackGrayVal_left_up+tem1;
// 	BackGrayVal_right_up=BackGrayVal_right_up+tem2;
// 	BackGrayVal_right_down=BackGrayVal_right_down+tem3;
// 	BackGrayVal_left_down=BackGrayVal_left_down+tem4;
// 	get_grayval (image, 9, Cxx-Cyy+9, &tem1);
// 	get_grayval (image, 9, Cxx+Cyy-9, &tem2);
// 	get_grayval (image, 2*Cyy-9, Cxx+Cyy-9, &tem3);
// 	get_grayval (image, 2*Cyy-9, Cxx-Cyy+9, &tem4);
// 	BackGrayVal_left_up=BackGrayVal_left_up+tem1;
// 	BackGrayVal_right_up=BackGrayVal_right_up+tem2;
// 	BackGrayVal_right_down=BackGrayVal_right_down+tem3;
// 	BackGrayVal_left_down=BackGrayVal_left_down+tem4;
// 	BackGrayVal_left_up=BackGrayVal_left_up/3;
// 	BackGrayVal_right_up=BackGrayVal_right_up/3;
// 	BackGrayVal_right_down=BackGrayVal_right_down/3;
// 	BackGrayVal_left_down=BackGrayVal_left_down/3;
// 	
// 
// 	Hlong TemX=Cxx-Cyy+3, TemY=3;
//     get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_left_up<Thred && TemX<Cxx-60 && TemY<Cyy-60)
// 	{
// 		TemX=TemX+3;
// 		TemY=TemY+3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY-1, TemX-1, &tem1);
// 	if (tem1-BackGrayVal_left_up>=Thred)
// 	{
// 		TemY=TemY-1;
// 		TemX=TemX-1;
// 		get_grayval (image, TemY-1, TemX-1, &tem1);
//     	if (tem1-BackGrayVal_left_up>=Thred)
// 		{
// 			TemY=TemY-1;
// 			TemX=TemX-1;
// 			}
// 		}
// 	Hlong Xlu=TemX+1, Ylu=TemY+1;
// 
// 
// 	TemX=Cxx+Cyy-3, TemY=3;
//     get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_right_up<Thred && TemX>Cxx+60 && TemY<Cyy-60)
// 	{
// 		TemX=TemX-3;
// 		TemY=TemY+3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY-1, TemX+1, &tem1);
// 	if (tem1-BackGrayVal_right_up>=Thred)
// 	{
// 		TemY=TemY-1;
// 		TemX=TemX+1;
// 		get_grayval (image, TemY-1, TemX+1, &tem1);
// 		if (tem1-BackGrayVal_right_up>=Thred)
// 		{
// 			TemY=TemY-1;
// 			TemX=TemX+1;
// 		}
// 	}
// 	Hlong Xru=TemX, Yru=TemY;
// 
// 
// 
// 	TemX=Cxx+Cyy-3, TemY=2*Cyy-3;	 
//     get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_right_down<Thred && TemX>Cxx+60 && TemY>Cyy+60)
// 	{
// 		TemX=TemX-3;
// 		TemY=TemY-3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY+1, TemX+1, &tem1);
// 	if (tem1-BackGrayVal_right_down>=Thred)
// 	{
// 		TemY=TemY+1;
// 		TemX=TemX+1;
// 		get_grayval (image, TemY+1, TemX+1, &tem1);
// 		if (tem1-BackGrayVal_right_down>=Thred)
// 		{
// 			TemY=TemY+1;
// 			TemX=TemX+1;
// 		}
// 	}
// 	Hlong Xrd=TemX+2, Yrd=TemY+2;
// 
// 
// 
// 	TemX=Cxx-Cyy+3, TemY=2*Cyy-3;	 
//     get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_left_down<Thred && TemX<Cxx-60 && TemY>Cyy+60)
// 	{
// 		TemX=TemX+3;
// 		TemY=TemY-3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY+1, TemX-1, &tem1);
// 	if (tem1-BackGrayVal_left_down>=Thred)
// 	{
// 		TemY=TemY+1;
// 		TemX=TemX-1;
// 		get_grayval (image, TemY+1, TemX-1, &tem1);
// 		if (tem1-BackGrayVal_left_down>=Thred)
// 		{
// 			TemY=TemY+1;
// 			TemX=TemX-1;
// 		}
// 	}
// 	Hlong Xld=TemX, Yld=TemY;
// 
//  
//  	Txx=(Xlu+Xru+Xrd+Xld+Ylu-Yru+Yrd-Yld)/4;
//  	Tyy=(Xlu-Xru+Xrd-Xld+Yld+Ylu+Yrd+Yru)/4;
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// //////////////////////////////////////////////////////////////
// 	
// //计时
// 
// 	count_seconds(&T2);
// 
// 	HTuple DT = 1000000*(T2[0].D() - T1[0].D());
// 
// 	CString tmp;
// 	tmp.Format("%4.1f",DT[0].D());
// 	m_NeedTime.SetWindowText(tmp + "us");
// 
// //////////////////////////////////////////////////////////////////
// //*************************************************************//
// //显示
// 
// 	Hobject CircleLeft;
// 	gen_circle(&CircleLeft, Ylu, Xlu, 1);
// 	disp_obj(CircleLeft, FGHandle);
// 
// 	Hobject CircleRight;
// 	gen_circle(&CircleRight, Yru, Xru, 1);
// 	disp_obj(CircleRight, FGHandle);
// 
// 	Hobject CircleDown;
// 	gen_circle(&CircleDown, Yrd, Xrd, 1);
// 	disp_obj(CircleDown, FGHandle);
// 
// 	Hobject CircleUp;
// 	gen_circle(&CircleUp, Yld, Xld, 1);
// 	disp_obj(CircleUp, FGHandle);
// 
// 	Hobject CircleCenter;
// 	gen_circle(&CircleCenter, Tyy, Txx, 2);
// 	disp_obj(CircleCenter, FGHandle);
// 
// 	TR=sqrt((Txx-Xlu)*(Txx-Xlu)+(Tyy-Ylu)*(Tyy-Ylu));
// 
// 	Hobject CircleReal;
// 	gen_circle(&CircleReal, Tyy, Txx, TR);
// 	disp_obj(CircleReal, FGHandle);
// 
// 	Hobject CircleRange2;
// 	gen_circle(&CircleRange2, Tyy, Txx, TR+50);
// 	disp_obj(CircleRange2, FGHandle);



////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////圆心 法三 （综合）

// 	count_seconds(&T1);
// 
// 	double BackGrayVal_up, BackGrayVal_down, BackGrayVal_left, BackGrayVal_right, tem1,tem2,tem3,tem4;
// 
// 	Thred_center1=35;
// 	Hlong Cxx=Width/2;
// 	Hlong Cyy=Height/2;
//     get_grayval (image, Cyy, Cxx-Cyy, &tem1);
// 	get_grayval (image, Cyy, Cxx+Cyy, &tem2);
// 	get_grayval (image, 3, Cxx, &tem3);
// 	get_grayval (image, 2*Cyy-3, Cxx, &tem4);
// 	BackGrayVal_left=tem1;
// 	BackGrayVal_right=tem2;
// 	BackGrayVal_up=tem3;
// 	BackGrayVal_down=tem4;
//     get_grayval (image, Cyy, Cxx-Cyy+3,  &tem1);
// 	get_grayval (image, Cyy, Cxx+Cyy-3,  &tem2);
// 	get_grayval (image, 6, Cxx,  &tem3);
// 	get_grayval (image, 2*Cyy-6, Cxx, &tem4);
// 	BackGrayVal_left=BackGrayVal_left+tem1;
// 	BackGrayVal_right=BackGrayVal_right+tem2;
// 	BackGrayVal_up=BackGrayVal_up+tem3;
// 	BackGrayVal_down=BackGrayVal_down+tem4;
// 	get_grayval (image, Cyy, Cxx-Cyy+6,  &tem1);
// 	get_grayval (image, Cyy, Cxx+Cyy-6,  &tem2);
// 	get_grayval (image, 9, Cxx,  &tem3);
// 	get_grayval (image, 2*Cyy-9, Cxx, &tem4);
// 	BackGrayVal_left=BackGrayVal_left+tem1;
// 	BackGrayVal_right=BackGrayVal_right+tem2;
// 	BackGrayVal_up=BackGrayVal_up+tem3;
// 	BackGrayVal_down=BackGrayVal_down+tem4;
// 	BackGrayVal_left=BackGrayVal_left/3;
// 	BackGrayVal_right=BackGrayVal_right/3;
// 	BackGrayVal_up=BackGrayVal_up/3;
// 	BackGrayVal_down=BackGrayVal_down/3;
// 	
// 
// 	Hlong Txx_left=Cxx-Cyy+3;
//     get_grayval (image, Cyy, Txx_left, &tem1);
// 	while (tem1-BackGrayVal_left<Thred_center1 && Txx_left<Cxx)
// 	{
// 		Txx_left=Txx_left+3;
// 		get_grayval (image, Cyy, Txx_left, &tem1);
// 	}
// 	get_grayval (image, Cyy, Txx_left-1, &tem1);
// 	if (tem1-BackGrayVal_left>=Thred_center1)
// 		{Txx_left=Txx_left-1;
// 		get_grayval (image, Cyy, Txx_left-1, &tem1);
//     	if (tem1-BackGrayVal_left>=Thred_center1)
// 			{Txx_left=Txx_left-1;
// 			}
// 		}
// 	Txx_left=Txx_left+1;
// 
// 	Hlong Txx_right=Cxx+Cyy-3;
// 	get_grayval (image, Cyy, Txx_right, &tem2);
// 	while (tem2-BackGrayVal_right<Thred_center1 && Txx_right>Cxx)
// 	{
// 		Txx_right=Txx_right-3;
// 		get_grayval (image, Cyy, Txx_right, &tem2);
// 	}
// 	get_grayval (image, Cyy, Txx_right+1, &tem2);
// 	if (tem2-BackGrayVal_right>=Thred_center1)
// 		{Txx_right=Txx_right+1;	
// 		get_grayval (image, Cyy, Txx_right+1, &tem2);
// 		if (tem2-BackGrayVal_right>=Thred_center1)
// 			{Txx_right=Txx_right+1;
// 			}
// 		}
// 	Txx_right=Txx_right+2;
// 
// 	Hlong Tyy_down=2*Cyy-3;
//     get_grayval (image, Tyy_down, Cxx, &tem3);
// 	while (tem3-BackGrayVal_down<Thred_center1 && Tyy_down>Cyy)
// 	{
// 		Tyy_down=Tyy_down-3;
// 		get_grayval (image, Tyy_down, Cxx, &tem3);
// 	}
// 	get_grayval (image, Tyy_down+1, Cxx, &tem3);
// 	if (tem3-BackGrayVal_down>=Thred_center1)
// 		{Tyy_down=Tyy_down+1;
// 		get_grayval (image, Tyy_down+1, Cxx, &tem3);
// 		if (tem3-BackGrayVal_down>=Thred_center1)
// 			{Tyy_down=Tyy_down+1;
// 			}
// 		}
// 	Tyy_down=Tyy_down+2;
// 
// 	Hlong Tyy_up=3;
//     get_grayval (image, Tyy_up, Cxx, &tem4);
// 	while (tem4-BackGrayVal_up<Thred_center1 && Tyy_up<Cyy)
// 	{
// 		Tyy_up=Tyy_up+3;
// 		get_grayval (image, Tyy_up, Cxx, &tem4);
// 	}
// 	get_grayval (image, Tyy_up, Cxx-1, &tem4);
// 	if (tem4-BackGrayVal_up>=Thred_center1)
// 		{Tyy_up=Tyy_up-1;
// 		get_grayval (image, Tyy_up, Cxx-1, &tem4);
// 		if (tem4-BackGrayVal_up>=Thred_center1)
// 			{Tyy_up=Tyy_up-1;
// 			}
// 		}
// 	Tyy_up=Tyy_up+1;
// 
//     
// 	Txx=(Txx_left+Txx_right)/2;
// 	Tyy=(Tyy_up+Tyy_down+1)/2;
// 
// 
// 	count_seconds(&T2);
// 
// 
// 
// /////////////////////////////////////////////////////////////////
// 
// 	//////////////////////////////////////////////////////////////////
// 
// 	TR=sqrt((double)((Txx-Txx_left)*(Txx-Txx_left)+(Tyy-Cyy)*(Tyy-Cyy)));
// 	Hlong TR_test=sqrt((double)((Txx-Cxx)*(Txx-Cxx)+(Tyy-Tyy_up)*(Tyy-Tyy_up)));
// 
// 
// 	if (abs(TR-TR_test)<3)
// 	{
// 		
// 		//////////////////////////////////////////////////////////////
// 		
// 		//计时
// 		
// 
// 		
// 		HTuple DT = 1000000*(T2[0].D() - T1[0].D());
// 		
// 		CString tmp;
// 		tmp.Format("%4.1f",DT[0].D());
// 		m_NeedTime.SetWindowText(tmp + "us");
// 
// 
// 		//*************************************************************//
// 		//显示
// 		
// 		Hobject CircleLeft;
// 		gen_circle(&CircleLeft, Cyy, Txx_left, 1);
// 		disp_obj(CircleLeft, FGHandle);
// 		
// 		Hobject CircleRight;
// 		gen_circle(&CircleRight, Cyy, Txx_right, 1);
// 		disp_obj(CircleRight, FGHandle);
// 		
// 		Hobject CircleDown;
// 		gen_circle(&CircleDown, Tyy_down, Cxx, 1);
// 		disp_obj(CircleDown, FGHandle);
// 		
// 		Hobject CircleUp;
// 		gen_circle(&CircleUp, Tyy_up, Cxx, 1);
// 		disp_obj(CircleUp, FGHandle);
// 		
// 		Hobject CircleCenter;
// 		gen_circle(&CircleCenter, Tyy, Txx, 2);
// 		disp_obj(CircleCenter, FGHandle);
// 
// 		Hobject CircleReal;
// 		gen_circle(&CircleReal, Tyy, Txx, TR);
// 		disp_obj(CircleReal, FGHandle);
// 		
// 		Hobject CircleRange2;
// 		gen_circle(&CircleRange2, Tyy, Txx, TR+50);
// 		disp_obj(CircleRange2, FGHandle);
// 
// 		return;
// 	}
// 
// 	
// 	
// 	double BackGrayVal_right_up, BackGrayVal_left_down, BackGrayVal_left_up, BackGrayVal_right_down;
// 
// 	Thred_center2=50;
//     get_grayval (image, 3, Cxx-Cyy+3, &tem1);
// 	get_grayval (image, 3, Cxx+Cyy-3, &tem2);
// 	get_grayval (image, 2*Cyy-3, Cxx+Cyy-3, &tem3);
// 	get_grayval (image, 2*Cyy-3, Cxx-Cyy+3, &tem4);
// 	BackGrayVal_left_up=tem1;
// 	BackGrayVal_right_up=tem2;
// 	BackGrayVal_right_down=tem3;
// 	BackGrayVal_left_down=tem4;
// 	get_grayval (image, 6, Cxx-Cyy+6, &tem1);
// 	get_grayval (image, 6, Cxx+Cyy-6, &tem2);
// 	get_grayval (image, 2*Cyy-6, Cxx+Cyy-6, &tem3);
// 	get_grayval (image, 2*Cyy-6, Cxx-Cyy+6, &tem4);
// 	BackGrayVal_left_up=BackGrayVal_left_up+tem1;
// 	BackGrayVal_right_up=BackGrayVal_right_up+tem2;
// 	BackGrayVal_right_down=BackGrayVal_right_down+tem3;
// 	BackGrayVal_left_down=BackGrayVal_left_down+tem4;
// 	get_grayval (image, 9, Cxx-Cyy+9, &tem1);
// 	get_grayval (image, 9, Cxx+Cyy-9, &tem2);
// 	get_grayval (image, 2*Cyy-9, Cxx+Cyy-9, &tem3);
// 	get_grayval (image, 2*Cyy-9, Cxx-Cyy+9, &tem4);
// 	BackGrayVal_left_up=BackGrayVal_left_up+tem1;
// 	BackGrayVal_right_up=BackGrayVal_right_up+tem2;
// 	BackGrayVal_right_down=BackGrayVal_right_down+tem3;
// 	BackGrayVal_left_down=BackGrayVal_left_down+tem4;
// 	BackGrayVal_left_up=BackGrayVal_left_up/3;
// 	BackGrayVal_right_up=BackGrayVal_right_up/3;
// 	BackGrayVal_right_down=BackGrayVal_right_down/3;
// 	BackGrayVal_left_down=BackGrayVal_left_down/3;
// 	
// 
// 	Hlong TemX=Cxx-Cyy+3, TemY=3;
//     get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_left_up<Thred_center2 && TemX<Cxx-60 && TemY<Cyy-60)
// 	{
// 		TemX=TemX+3;
// 		TemY=TemY+3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY-1, TemX-1, &tem1);
// 	if (tem1-BackGrayVal_left_up>=Thred_center2)
// 	{
// 		TemY=TemY-1;
// 		TemX=TemX-1;
// 		get_grayval (image, TemY-1, TemX-1, &tem1);
//     	if (tem1-BackGrayVal_left_up>=Thred_center2)
// 		{
// 			TemY=TemY-1;
// 			TemX=TemX-1;
// 			}
// 		}
// 	Hlong Xlu=TemX+1, Ylu=TemY+1;
// 
// 
// 	TemX=Cxx+Cyy-3, TemY=3;
//     get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_right_up<Thred_center2 && TemX>Cxx+60 && TemY<Cyy-60)
// 	{
// 		TemX=TemX-3;
// 		TemY=TemY+3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY-1, TemX+1, &tem1);
// 	if (tem1-BackGrayVal_right_up>=Thred_center2)
// 	{
// 		TemY=TemY-1;
// 		TemX=TemX+1;
// 		get_grayval (image, TemY-1, TemX+1, &tem1);
// 		if (tem1-BackGrayVal_right_up>=Thred_center2)
// 		{
// 			TemY=TemY-1;
// 			TemX=TemX+1;
// 		}
// 	}
// 	Hlong Xru=TemX, Yru=TemY;
// 
// 
// 
// 	TemX=Cxx+Cyy-3, TemY=2*Cyy-3;	 
//     get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_right_down<Thred_center2 && TemX>Cxx+60 && TemY>Cyy+60)
// 	{
// 		TemX=TemX-3;
// 		TemY=TemY-3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY+1, TemX+1, &tem1);
// 	if (tem1-BackGrayVal_right_down>=Thred_center2)
// 	{
// 		TemY=TemY+1;
// 		TemX=TemX+1;
// 		get_grayval (image, TemY+1, TemX+1, &tem1);
// 		if (tem1-BackGrayVal_right_down>=Thred_center2)
// 		{
// 			TemY=TemY+1;
// 			TemX=TemX+1;
// 		}
// 	}
// 	Hlong Xrd=TemX+2, Yrd=TemY+2;
// 
// 
// 
// 	TemX=Cxx-Cyy+3, TemY=2*Cyy-3;	 
//     get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_left_down<Thred_center2 && TemX<Cxx-60 && TemY>Cyy+60)
// 	{
// 		TemX=TemX+3;
// 		TemY=TemY-3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY+1, TemX-1, &tem1);
// 	if (tem1-BackGrayVal_left_down>=Thred_center2)
// 	{
// 		TemY=TemY+1;
// 		TemX=TemX-1;
// 		get_grayval (image, TemY+1, TemX-1, &tem1);
// 		if (tem1-BackGrayVal_left_down>=Thred_center2)
// 		{
// 			TemY=TemY+1;
// 			TemX=TemX-1;
// 		}
// 	}
// 	Hlong Xld=TemX, Yld=TemY;
// 
//  
//  	Txx=(Xlu+Xru+Xrd+Xld+Ylu-Yru+Yrd-Yld)/4;
//  	Tyy=(Xlu-Xru+Xrd-Xld+Yld+Ylu+Yrd+Yru)/4;
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// 
// //////////////////////////////////////////////////////////////
// 	
// //计时
// 
// 	count_seconds(&T2);
// 
// 	HTuple DT = 1000000*(T2[0].D() - T1[0].D());
// 
// 	CString tmp;
// 	tmp.Format("%4.1f",DT[0].D());
// 	m_NeedTime.SetWindowText(tmp + "us");
// 
// //////////////////////////////////////////////////////////////////
// //*************************************************************//
// //显示
// 
// 
// 	Hobject CircleLeft;
// 	gen_circle(&CircleLeft, Ylu, Xlu, 1);
// 	disp_obj(CircleLeft, FGHandle);
// 
// 
// 	Hobject CircleRight;
// 	gen_circle(&CircleRight, Yru, Xru, 1);
// 	disp_obj(CircleRight, FGHandle);
// 
// 
// 	Hobject CircleDown;
// 	gen_circle(&CircleDown, Yrd, Xrd, 1);
// 	disp_obj(CircleDown, FGHandle);
// 
// 
// 	Hobject CircleUp;
// 	gen_circle(&CircleUp, Yld, Xld, 1);
// 	disp_obj(CircleUp, FGHandle);
// 
// 
// 	Hobject CircleCenter;
// 	gen_circle(&CircleCenter, Tyy, Txx, 2);
// 	disp_obj(CircleCenter, FGHandle);
// 
// 	TR=sqrt((double)((Txx-Xlu)*(Txx-Xlu)+(Tyy-Ylu)*(Tyy-Ylu)));
// 
// 	Hobject CircleReal;
// 	gen_circle(&CircleReal, Tyy, Txx, TR);
// 	disp_obj(CircleReal, FGHandle);
// 
// 	Hobject CircleRange2;
// 	gen_circle(&CircleRange2, Tyy, Txx, TR+50);
// 	disp_obj(CircleRange2, FGHandle);
	

	
////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////法四////////////统计///////////

// 
// 	count_seconds(&T1);
// 
// 	double BackGrayVal_up, BackGrayVal_down, BackGrayVal_left, BackGrayVal_right, tem1,tem2,tem3,tem4;
// 
// 	Thred_center1=15;
// 	Hlong Cxx=Width/2;
// 	Hlong Cyy=Height/2;
// 	int i, j;
// 
// 
// 	BackGrayVal_left=0;
// 	BackGrayVal_right=0;
// 	BackGrayVal_up=0;
// 	BackGrayVal_down=0;
// 
// 	for (int i=0; i<5; i++)
// 	{
// 		get_grayval (image, Cyy+5*i-10, Cxx-Cyy, &tem1);
// 		get_grayval (image, Cyy+5*i-10, Cxx+Cyy, &tem2);
// 		get_grayval (image, 3, Cxx+5*i-10, &tem3);
// 		get_grayval (image, 2*Cyy-3, Cxx+5*i-10, &tem4);
// 		BackGrayVal_left=BackGrayVal_left+tem1;
// 		BackGrayVal_right=BackGrayVal_right+tem2;
// 		BackGrayVal_up=BackGrayVal_up+tem3;
// 		BackGrayVal_down=BackGrayVal_down+tem4;
// 		get_grayval (image, Cyy+5*i-10, Cxx-Cyy+3,  &tem1);
// 		get_grayval (image, Cyy+5*i-10, Cxx+Cyy-3,  &tem2);
// 		get_grayval (image, 6, Cxx+5*i-10,  &tem3);
// 		get_grayval (image, 2*Cyy-6, Cxx+5*i-10, &tem4);
// 		BackGrayVal_left=BackGrayVal_left+tem1;
// 		BackGrayVal_right=BackGrayVal_right+tem2;
// 		BackGrayVal_up=BackGrayVal_up+tem3;
// 		BackGrayVal_down=BackGrayVal_down+tem4;
// 		get_grayval (image, Cyy+5*i-10, Cxx-Cyy+6,  &tem1);
// 		get_grayval (image, Cyy+5*i-10, Cxx+Cyy-6,  &tem2);
// 		get_grayval (image, 9, Cxx+5*i-10,  &tem3);
// 		get_grayval (image, 2*Cyy-9, Cxx+5*i-10, &tem4);
// 		BackGrayVal_left=BackGrayVal_left+tem1;
// 		BackGrayVal_right=BackGrayVal_right+tem2;
// 		BackGrayVal_up=BackGrayVal_up+tem3;
// 		BackGrayVal_down=BackGrayVal_down+tem4;
// 	}
// 		
// 	BackGrayVal_left=BackGrayVal_left/15;
// 	BackGrayVal_right=BackGrayVal_right/15;
// 	BackGrayVal_up=BackGrayVal_up/15;
// 	BackGrayVal_down=BackGrayVal_down/15;
// 
// 
// 
// 	Hlong Txx_left[5], Txx_right[5], Tyy_down[5], Tyy_up[5];
// 	Hlong Txxz[5], Tyyz[5];
// 
// 
// 
// 	for (i=0; i<5; i++)
// 	{
// 		Txx_left[i]=Cxx-Cyy+3;
// 		Txx_right[i]=Cxx+Cyy-3;
// 		Tyy_down[i]=2*Cyy-3;
// 		Tyy_up[i]=3;
// 
// 		get_grayval (image, Cyy-10+5*i, Txx_left[i], &tem1);
// 		while (tem1-BackGrayVal_left<Thred_center1 && Txx_left[i]<Cxx)
// 		{
// 			Txx_left[i]=Txx_left[i]+3;
// 			get_grayval (image, Cyy-10+5*i, Txx_left[i], &tem1);
// 		}
// 		get_grayval (image, Cyy-10+5*i, Txx_left[i]-1, &tem1);
// 		if (tem1-BackGrayVal_left>=Thred_center1)
// 		{Txx_left[i]=Txx_left[i]-1;
// 		get_grayval (image, Cyy-10+5*i, Txx_left[i]-1, &tem1);
// 		if (tem1-BackGrayVal_left>=Thred_center1)
// 		{Txx_left[i]=Txx_left[i]-1;
// 		}
// 		}
// 
// 		Txx_left[i]=Txx_left[i]+1;
// 
// 
// 		get_grayval (image, Cyy-10+5*i, Txx_right[i], &tem2);
// 		while (tem2-BackGrayVal_right<Thred_center1 && Txx_right[i]>Cxx)
// 		{
// 			Txx_right[i]=Txx_right[i]-3;
// 			get_grayval (image, Cyy-10+5*i, Txx_right[i], &tem2);
// 		}
// 		get_grayval (image, Cyy-10+5*i, Txx_right[i]+1, &tem2);
// 		if (tem2-BackGrayVal_right>=Thred_center1)
// 		{Txx_right[i]=Txx_right[i]+1;	
// 		get_grayval (image, Cyy-10+5*i, Txx_right[i]+1, &tem2);
// 		if (tem2-BackGrayVal_right>=Thred_center1)
// 		{Txx_right[i]=Txx_right[i]+1;
// 		}
// 		}
// 
// 		Txx_right[i]=Txx_right[i]+2;
// 
// 		get_grayval (image, Tyy_down[i], Cxx-10+5*i, &tem3);
// 		while (tem3-BackGrayVal_down<Thred_center1 && Tyy_down[i]>Cyy)
// 		{
// 			Tyy_down[i]=Tyy_down[i]-3;
// 			get_grayval (image, Tyy_down[i], Cxx-10+5*i, &tem3);
// 		}
// 		get_grayval (image, Tyy_down[i]+1, Cxx-10+5*i, &tem3);
// 		if (tem3-BackGrayVal_down>=Thred_center1)
// 		{Tyy_down[i]=Tyy_down[i]+1;
// 		get_grayval (image, Tyy_down[i]+1, Cxx-10+5*i, &tem3);
// 		if (tem3-BackGrayVal_down>=Thred_center1)
// 		{Tyy_down[i]=Tyy_down[i]+1;
// 		}
// 		}
// 
// 		Tyy_down[i]=Tyy_down[i]+2;
// 
// 
// 		get_grayval (image, Tyy_up[i], Cxx-10+5*i, &tem4);
// 		while (tem4-BackGrayVal_up<Thred_center1 && Tyy_up[i]<Cyy)
// 		{
// 			Tyy_up[i]=Tyy_up[i]+3;
// 			get_grayval (image, Tyy_up[i], Cxx-10+5*i, &tem4);
// 		}
// 		get_grayval (image, Tyy_up[i]-1, Cxx-10+5*i, &tem4);
// 		if (tem4-BackGrayVal_up>=Thred_center1)
// 		{Tyy_up[i]=Tyy_up[i]-1;
// 		get_grayval (image, Tyy_up[i]-1, Cxx-10+5*i, &tem4);
// 		if (tem4-BackGrayVal_up>=Thred_center1)
// 		{Tyy_up[i]=Tyy_up[i]-1;
// 		}
// 		}
// 
// 		Tyy_up[i]=Tyy_up[i]+1;
// 
// 
// 		Txxz[i]=(Txx_left[i]+Txx_right[i])/2;
// 		Tyyz[i]=(Tyy_up[i]+Tyy_down[i])/2;
// 		
// 
// 	}
// 
// 
// ////////////////////////////////////////////////////////////////////////////////////////
// 	/////////////////////////////////////////////////////计算//////////////////
// 
// 
// 	Txx=Txxz[3];
// 	Tyy=Tyyz[3];
// 	
// 	TR=sqrt((double)((Txx-Txx_left[3])*(Txx-Txx_left[3])+(Tyy-Cyy)*(Tyy-Cyy)));
// 	Hlong TR_test=sqrt((double)((Txx-Cxx)*(Txx-Cxx)+(Tyy-Tyy_up[3])*(Tyy-Tyy_up[3])));
// 	 
// 	 
// 	if (abs(TR-TR_test)<3)
// 	{
// 
// 		count_seconds(&T2);
// 
// 		HTuple DT = 1000000*(T2[0].D() - T1[0].D());
// 		CString tmp;
// 		tmp.Format("%4.1f",DT[0].D());
// 		m_NeedTime.SetWindowText(tmp + "us");
// 
// 		//////////////////////////////////////////////////////////////////////////////////////////
// 		// //显示
// 
// 
// 
// 		Hobject CircleLeft;
// 		gen_circle(&CircleLeft, Cyy, Txx_left[3], 1);
// 		disp_obj(CircleLeft, FGHandle);
// 
// 		Hobject CircleRight;
// 		gen_circle(&CircleRight, Cyy, Txx_right[3], 1);
// 		disp_obj(CircleRight, FGHandle);
// 
// 		Hobject CircleDown;
// 		gen_circle(&CircleDown, Tyy_down[3], Cxx, 1);
// 		disp_obj(CircleDown, FGHandle);
// 
// 		Hobject CircleUp;
// 		gen_circle(&CircleUp, Tyy_up[3], Cxx, 1);
// 		disp_obj(CircleUp, FGHandle);
// 
// 		Hobject CircleCenter;
// 		gen_circle(&CircleCenter, Tyy, Txx, 2);
// 		disp_obj(CircleCenter, FGHandle);
// 
// 		Hobject CircleReal;
// 		gen_circle(&CircleReal, Tyy, Txx, TR);
// 		disp_obj(CircleReal, FGHandle);
// 
// 		Hobject CircleRange2;
// 		gen_circle(&CircleRange2, Tyy, Txx, TR+50);
// 		disp_obj(CircleRange2, FGHandle);
// 
// 	
// 		return;
// 	}
// 
// 
// 
// 
// 
// 	double BackGrayVal_right_up, BackGrayVal_left_down, BackGrayVal_left_up, BackGrayVal_right_down;
// 
// 	Thred_center2=50;
// 	get_grayval (image, 3, Cxx-Cyy+3, &tem1);
// 	get_grayval (image, 3, Cxx+Cyy-3, &tem2);
// 	get_grayval (image, 2*Cyy-3, Cxx+Cyy-3, &tem3);
// 	get_grayval (image, 2*Cyy-3, Cxx-Cyy+3, &tem4);
// 	BackGrayVal_left_up=tem1;
// 	BackGrayVal_right_up=tem2;
// 	BackGrayVal_right_down=tem3;
// 	BackGrayVal_left_down=tem4;
// 	get_grayval (image, 6, Cxx-Cyy+6, &tem1);
// 	get_grayval (image, 6, Cxx+Cyy-6, &tem2);
// 	get_grayval (image, 2*Cyy-6, Cxx+Cyy-6, &tem3);
// 	get_grayval (image, 2*Cyy-6, Cxx-Cyy+6, &tem4);
// 	BackGrayVal_left_up=BackGrayVal_left_up+tem1;
// 	BackGrayVal_right_up=BackGrayVal_right_up+tem2;
// 	BackGrayVal_right_down=BackGrayVal_right_down+tem3;
// 	BackGrayVal_left_down=BackGrayVal_left_down+tem4;
// 	get_grayval (image, 9, Cxx-Cyy+9, &tem1);
// 	get_grayval (image, 9, Cxx+Cyy-9, &tem2);
// 	get_grayval (image, 2*Cyy-9, Cxx+Cyy-9, &tem3);
// 	get_grayval (image, 2*Cyy-9, Cxx-Cyy+9, &tem4);
// 	BackGrayVal_left_up=BackGrayVal_left_up+tem1;
// 	BackGrayVal_right_up=BackGrayVal_right_up+tem2;
// 	BackGrayVal_right_down=BackGrayVal_right_down+tem3;
// 	BackGrayVal_left_down=BackGrayVal_left_down+tem4;
// 	BackGrayVal_left_up=BackGrayVal_left_up/3;
// 	BackGrayVal_right_up=BackGrayVal_right_up/3;
// 	BackGrayVal_right_down=BackGrayVal_right_down/3;
// 	BackGrayVal_left_down=BackGrayVal_left_down/3;
// 
// 
// 	Hlong TemX=Cxx-Cyy+3, TemY=3;
// 	get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_left_up<Thred_center2 && TemX<Cxx-60 && TemY<Cyy-60)
// 	{
// 		TemX=TemX+3;
// 		TemY=TemY+3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY-1, TemX-1, &tem1);
// 	if (tem1-BackGrayVal_left_up>=Thred_center2)
// 	{
// 		TemY=TemY-1;
// 		TemX=TemX-1;
// 		get_grayval (image, TemY-1, TemX-1, &tem1);
// 		if (tem1-BackGrayVal_left_up>=Thred_center2)
// 		{
// 			TemY=TemY-1;
// 			TemX=TemX-1;
// 		}
// 	}
// 	Hlong Xlu=TemX+1, Ylu=TemY+1;
// 
// 
// 	TemX=Cxx+Cyy-3, TemY=3;
// 	get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_right_up<Thred_center2 && TemX>Cxx+60 && TemY<Cyy-60)
// 	{
// 		TemX=TemX-3;
// 		TemY=TemY+3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY-1, TemX+1, &tem1);
// 	if (tem1-BackGrayVal_right_up>=Thred_center2)
// 	{
// 		TemY=TemY-1;
// 		TemX=TemX+1;
// 		get_grayval (image, TemY-1, TemX+1, &tem1);
// 		if (tem1-BackGrayVal_right_up>=Thred_center2)
// 		{
// 			TemY=TemY-1;
// 			TemX=TemX+1;
// 		}
// 	}
// 	Hlong Xru=TemX, Yru=TemY;
// 
// 
// 
// 	TemX=Cxx+Cyy-3, TemY=2*Cyy-3;	 
// 	get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_right_down<Thred_center2 && TemX>Cxx+60 && TemY>Cyy+60)
// 	{
// 		TemX=TemX-3;
// 		TemY=TemY-3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY+1, TemX+1, &tem1);
// 	if (tem1-BackGrayVal_right_down>=Thred_center2)
// 	{
// 		TemY=TemY+1;
// 		TemX=TemX+1;
// 		get_grayval (image, TemY+1, TemX+1, &tem1);
// 		if (tem1-BackGrayVal_right_down>=Thred_center2)
// 		{
// 			TemY=TemY+1;
// 			TemX=TemX+1;
// 		}
// 	}
// 	Hlong Xrd=TemX+2, Yrd=TemY+2;
// 
// 
// 
// 	TemX=Cxx-Cyy+3, TemY=2*Cyy-3;	 
// 	get_grayval (image, TemY, TemX, &tem1);
// 	while (tem1-BackGrayVal_left_down<Thred_center2 && TemX<Cxx-60 && TemY>Cyy+60)
// 	{
// 		TemX=TemX+3;
// 		TemY=TemY-3;
// 		get_grayval (image, TemY, TemX, &tem1);
// 	}
// 	get_grayval (image, TemY+1, TemX-1, &tem1);
// 	if (tem1-BackGrayVal_left_down>=Thred_center2)
// 	{
// 		TemY=TemY+1;
// 		TemX=TemX-1;
// 		get_grayval (image, TemY+1, TemX-1, &tem1);
// 		if (tem1-BackGrayVal_left_down>=Thred_center2)
// 		{
// 			TemY=TemY+1;
// 			TemX=TemX-1;
// 		}
// 	}
// 	Hlong Xld=TemX, Yld=TemY;
// 
// 
// 	Txx=(Xlu+Xru+Xrd+Xld+Ylu-Yru+Yrd-Yld)/4;
// 	Tyy=(Xlu-Xru+Xrd-Xld+Yld+Ylu+Yrd+Yru)/4;












	//////////////////////////////////////////////////////////////

	//计时

	count_seconds(&T2);

	HTuple DT = 1000000*(T2[0].D() - T1[0].D());

	CString tmp;
	tmp.Format("%4.1f",DT[0].D());
	m_NeedTime.SetWindowText(tmp + "us");

	//////////////////////////////////////////////////////////////////
	//*************************************************************//
	//显示


// 	Hobject CircleLeft;
// 	gen_circle(&CircleLeft, Ylu, Xlu, 1);
// 	disp_obj(CircleLeft, FGHandle);
// 
// 
// 	Hobject CircleRight;
// 	gen_circle(&CircleRight, Yru, Xru, 1);
// 	disp_obj(CircleRight, FGHandle);
// 
// 
// 	Hobject CircleDown;
// 	gen_circle(&CircleDown, Yrd, Xrd, 1);
// 	disp_obj(CircleDown, FGHandle);
// 
// 
// 	Hobject CircleUp;
// 	gen_circle(&CircleUp, Yld, Xld, 1);
// 	disp_obj(CircleUp, FGHandle);
// 
// 
// 	Hobject CircleCenter;
// 	gen_circle(&CircleCenter, Tyy, Txx, 2);
// 	disp_obj(CircleCenter, FGHandle);
// 
// 	TR=sqrt((double)((Txx-Xlu)*(Txx-Xlu)+(Tyy-Ylu)*(Tyy-Ylu)));
// 
// 	Hobject CircleReal;
// 	gen_circle(&CircleReal, Tyy, Txx, TR);
// 	disp_obj(CircleReal, FGHandle);
// 
// 	Hobject CircleRange2;
// 	gen_circle(&CircleRange2, Tyy, Txx, TR+50);
// 	disp_obj(CircleRange2, FGHandle);

	
}






void CHalcon001Dlg::OnFileOpen()
{
		
	CFileDialog *lpszOpenFile;
		
	lpszOpenFile = new
			
	//CFileDialog(TRUE," "," ",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY,"文件类型(*.tiff)|*.tiff||");

	CFileDialog(TRUE," "," ",OFN_FILEMUSTEXIST |OFN_HIDEREADONLY,"文件类型(*.tiff)|*.tiff||");
	
	if(lpszOpenFile->DoModal()==IDOK)

	{
		
			
			szGetName = lpszOpenFile->GetPathName();
				
			SetWindowText(szGetName);
			
			}
		
		delete lpszOpenFile;
		

	





}

void CHalcon001Dlg::OnBnClose() 
{
	// TODO: Add your control notification handler code here

	close_window(FGHandle);


}

void CHalcon001Dlg::OnStaticFlag() 
{
	// TODO: Add your control notification handler code here
	
}

void CHalcon001Dlg::OnSTATICNeedTime() 
{
	// TODO: Add your control notification handler code here
	
}



void CHalcon001Dlg::On_Bn_Juanbian() 
{
	// TODO: Add your control notification handler code here
//均值差分法	



	Hobject Circle_juanyuan_inter;
	gen_circle(&Circle_juanyuan_inter, Tyy, Txx, TR-4);
	disp_obj(Circle_juanyuan_inter, FGHandle);

	Hobject CircleReal;
	gen_circle(&CircleReal, Tyy, Txx, TR);
	disp_obj(CircleReal, FGHandle);



	Hobject PolarTransImage_juan;

	HTuple T1, T2;


	count_seconds(&T1);

	polar_trans_image_ext (image, &PolarTransImage_juan, Tyy, Txx, 0, 7, TR-5, TR-1, 700, 5, "bilinear");

	Hobject CircleCurlError;
	int i, j, k;
	double tem1;
	int tem[70], ThredCurl, CurlPosition=100;

//////////////////////////////////////////////////////////////
	/////////////////////////法一


// 	ThredCurl=1000;
// 	tem[0]=0;
// 	for (j=0; j<10; j++)
// 	{
// 		for (k=0; k<5; k++)
// 		{
// 			get_grayval(PolarTransImage_juan, k, j, &tem1);
// 			tem[0]=tem[0]+tem1;
// 		}
// 	}
// 
// 
// 	tem[1]=0;
// 	for (j=10; j<20; j++)
// 	{
// 		for (k=0; k<5; k++)
// 		{
// 			get_grayval(PolarTransImage_juan, k, j, &tem1);
// 			tem[1]=tem[1]+tem1;
// 		}
// 	}
// 
// 
// 	for (i=2; i<60; i++)
// 	{
// 		tem[i]=0;
// 		for (j=i*10; j<10+i*10; j++)
// 		{
// 			for (k=0; k<5; k++)
// 			{
// 				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				tem[i]=tem[i]+tem1;
// 			}
// 		}
// 
// 		if (abs(tem[i-2]+tem[i]-2*tem[i-1])>ThredCurl)
// 		{
// 			//AfxMessageBox("Curl Bad");
// 
// 			ThredCurl=abs(tem[i-2]+tem[i]-2*tem[i-1]);
// 			CurlPosition=i-1;
// 			
// 		}
// 	
// 	}

// 	if (abs(tem[1]+tem[59]-2*tem[0])>ThredCurl)
// 	{
// 		//AfxMessageBox("Curl Bad");
// 		CurlPosition=0;
// 			
// 	}


// 	if (abs(tem[0]+tem[58]-2*tem[59])>ThredCurl)
// 	{
// 		//AfxMessageBox("Curl Bad");
// 		CurlPosition=59;
// 	}




//////////////////////////////////////////////////////////////////////////////

 ///////////////////////////////////法二 1-3 $


	
// 	ThredCurl=2200;
// 
// 
// 	for (i=0; i<4; i++)
// 	{
// 		tem[i]=0;
// 		for (j=i*10; j<10+i*10; j++)
// 		{
// 			for (k=0; k<4; k++)
// 			{
// 				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				tem[i]=tem[i]+tem1;
// 			}
// 		}
// 				
// 	}
// 	
// 	
// 	for (i=4; i<60; i++)
// 	{
// 		tem[i]=0;
// 		for (j=i*10; j<10+i*10; j++)
// 		{
// 			for (k=0; k<4; k++)
// 			{
// 				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				tem[i]=tem[i]+tem1;
// 			}
// 		}
// 		
// 		if (abs(tem[i-3]+tem[i-2]+tem[i-1]-3*tem[i])>ThredCurl)
// 		{
// 			//AfxMessageBox("Curl Bad");
// 			
// 			ThredCurl=abs(tem[i-3]+tem[i-2]+tem[i-1]-3*tem[i]);
// 			CurlPosition=i;
// 			
// 		}
// 		
// 	}
// 
// 	if (abs(tem[0]+tem[1]+tem[2]-3*tem[3])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[1]+tem[2]-3*tem[3]);
// 			CurlPosition=3;
// 	}
// 
// 	if (abs(tem[0]+tem[1]+tem[59]-3*tem[2])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[1]+tem[59]-3*tem[2]);
// 		CurlPosition=2;
// 	}
// 
// 	if (abs(tem[0]+tem[58]+tem[59]-3*tem[1])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[58]+tem[59]-3*tem[1]);
// 		CurlPosition=1;
// 	}
// 
// 	if (abs(tem[57]+tem[58]+tem[59]-3*tem[0])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[57]+tem[58]+tem[59]-3*tem[0]);
// 		CurlPosition=0;
// 	}

////////////////////////////////////////////////////////////////////
	///////////////////////////法三   2-4

// 
// 
// 	ThredCurl=1200;
// 
// 
// 	for (i=0; i<5; i++)
// 	{
// 		tem[i]=0;
// 		for (j=i*10; j<10+i*10; j++)
// 		{
// 			for (k=0; k<4; k++)
// 			{
// 				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				if (tem1>190)
// 				{
// 					tem1=190;
// 				}
// 				tem[i]=tem[i]+tem1;
// 			}
// 		}
// 				
// 	}
// 	
// 	
// 	for (i=5; i<60; i++)
// 	{
// 		tem[i]=0;
// 		for (j=i*10; j<10+i*10; j++)
// 		{
// 			for (k=0; k<4; k++)
// 			{
// 				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				if (tem1>190)
// 				{
// 					tem1=190;
// 				}
// 				tem[i]=tem[i]+tem1;
// 			}
// 		}
// 		
// 		if (abs(tem[i-5]+tem[i-4]+tem[i-3]+tem[i-2]-2*tem[i-1]-2*tem[i])>ThredCurl)
// 		{
// 			//AfxMessageBox("Curl Bad");
// 			
// 			ThredCurl=abs(tem[i-5]+tem[i-4]+tem[i-3]+tem[i-2]-2*tem[i-1]-2*tem[i]);
// 			CurlPosition=i;
// 			
// 		}
// 		
// 	}
// 
// 	if (abs(tem[0]+tem[1]+tem[2]+tem[59]-2*tem[3]-2*tem[4])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[1]+tem[2]+tem[59]-2*tem[3]-2*tem[4]);
// 			CurlPosition=4;
// 	}
// 
// 	if (abs(tem[0]+tem[1]+tem[58]+tem[59]-2*tem[3]-2*tem[2])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[1]+tem[58]+tem[59]-2*tem[3]-2*tem[2]);
// 		CurlPosition=3;
// 	}
// 
// 	if (abs(tem[0]+tem[57]+tem[58]+tem[59]-2*tem[1]-2*tem[2])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[57]+tem[58]+tem[59]-2*tem[1]-2*tem[2]);
// 		CurlPosition=2;
// 	}
// 
// 	if (abs(tem[56]+tem[57]+tem[58]+tem[59]-2*tem[1]-2*tem[0])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[56]+tem[57]+tem[58]+tem[59]-2*tem[1]-2*tem[0]);
// 		CurlPosition=1;
// 	}
// 
// 
// 	if (abs(tem[56]+tem[57]+tem[58]+tem[55]-2*tem[59]-2*tem[0])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[56]+tem[57]+tem[58]+tem[55]-2*tem[59]-2*tem[0]);
// 		CurlPosition=0;
// 	}
	
////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////法四 1-4 $$

// 	ThredCurl=1200;
// 	
// 	
// 	for (i=0; i<5; i++)
// 	{
// 		tem[i]=0;
// 		for (j=i*10; j<10+i*10; j++)
// 		{
// 			for (k=0; k<4; k++)
// 			{
// 				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				if (tem1>190)
// 				{
// 					tem1=190;
// 				}
// 				tem[i]=tem[i]+tem1;
// 			}
// 		}
// 		
// 	}
// 	
// 	
// 	for (i=5; i<60; i++)
// 	{
// 		tem[i]=0;
// 		for (j=i*10; j<10+i*10; j++)
// 		{
// 			for (k=0; k<4; k++)
// 			{
// 				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				if (tem1>190)
// 				{
// 					tem1=190;
// 				}
// 				tem[i]=tem[i]+tem1;
// 			}
// 		}
// 		
// 		if (abs(tem[i-5]+tem[i-4]+tem[i-3]+tem[i-2]-4*tem[i])>ThredCurl)
// 		{
// 			//AfxMessageBox("Curl Bad");
// 			
// 			ThredCurl=abs(tem[i-5]+tem[i-4]+tem[i-3]+tem[i-2]-4*tem[i]);
// 			CurlPosition=i;
// 			
// 		}
// 		
// 	}
// 	
// 	if (abs(tem[0]+tem[1]+tem[2]+tem[59]-4*tem[4])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[1]+tem[2]+tem[59]-4*tem[4]);
// 		CurlPosition=4;
// 	}
// 	
// 	if (abs(tem[0]+tem[1]+tem[58]+tem[59]-4*tem[2])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[1]+tem[58]+tem[59]-4*tem[2]);
// 		CurlPosition=3;
// 	}
// 	
// 	if (abs(tem[0]+tem[57]+tem[58]+tem[59]-4*tem[2])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[0]+tem[57]+tem[58]+tem[59]-4*tem[2]);
// 		CurlPosition=2;
// 	}
// 	
// 	if (abs(tem[56]+tem[57]+tem[58]+tem[59]-4*tem[0])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[56]+tem[57]+tem[58]+tem[59]-4*tem[0]);
// 		CurlPosition=1;
// 	}
// 	
// 	
// 	if (abs(tem[56]+tem[57]+tem[58]+tem[55]-4*tem[0])>ThredCurl)
// 	{
// 		ThredCurl=abs(tem[56]+tem[57]+tem[58]+tem[55]-4*tem[0]);
// 		CurlPosition=0;
// 	}



/////////////////////////////////////////////////////////////////
	/////////////////////////////法五 4-1-4////2011 11 14////


	ThredCurl=12900;
	
	
	for (i=0; i<10; i++)
	{
		tem[i]=0;
		for (j=i*10; j<10+i*10; j++)
		{
			for (k=0; k<5; k++)
			{
				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				if (tem1>190)
// 				{
// 					tem1=190;
// 				}
				tem[i]=tem[i]+tem1;
			}
		}
		
	}
	
	
	for (i=10; i<70; i++)
	{
		tem[i]=0;
		for (j=i*10; j<10+i*10; j++)
		{
			for (k=0; k<5; k++)
			{
				get_grayval(PolarTransImage_juan, k, j, &tem1);
// 				if (tem1>190)
// 				{
// 					tem1=190;
// 				}
				tem[i]=tem[i]+tem1;
			}
		}
		
		if (abs(tem[i-10]+tem[i-9]+tem[i-8]+tem[i-7]-8*tem[i-5]+tem[i-3]+tem[i-2]+tem[i-1]+tem[i])>ThredCurl)
		{
			//AfxMessageBox("Curl Bad");
			
			ThredCurl=abs(tem[i-10]+tem[i-9]+tem[i-8]+tem[i-7]-8*tem[i-5]+tem[i-3]+tem[i-2]+tem[i-1]+tem[i]);
			CurlPosition=i-5;
			
		}
		
	}
	
	
	if (abs(tem[58]+tem[57]+tem[0]+tem[59]-8*tem[2]+tem[6]+tem[7]+tem[4]+tem[5])>ThredCurl)
	{
		ThredCurl=abs(tem[58]+tem[57]+tem[0]+tem[59]-8*tem[2]+tem[6]+tem[7]+tem[4]+tem[5]);
		CurlPosition=2;
	}
	

	if (abs(tem[58]+tem[1]+tem[0]+tem[59]-8*tem[3]+tem[6]+tem[7]+tem[8]+tem[5])>ThredCurl)
	{
		ThredCurl=abs(tem[58]+tem[1]+tem[0]+tem[59]-8*tem[3]+tem[6]+tem[7]+tem[8]+tem[5]);
		CurlPosition=3;
	}

	if (abs(tem[2]+tem[1]+tem[0]+tem[59]-8*tem[4]+tem[6]+tem[7]+tem[8]+tem[9])>ThredCurl)
	{
		ThredCurl=abs(tem[2]+tem[1]+tem[0]+tem[59]-8*tem[4]+tem[6]+tem[7]+tem[8]+tem[9]);
		CurlPosition=4;
	}







////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
	count_seconds(&T2);

	HTuple DT = 1000000*(T2[0].D() - T1[0].D());
	
	CString tmp;
	tmp.Format("%4.1f",DT[0].D());
	m_NeedTime.SetWindowText(tmp + "us");

	if (CurlPosition>90)
	{
		AfxMessageBox("good juanbian");
		return;
	
	}


	set_color(FGHandle, "red");
	Hlong TxxError, TyyError;
	TxxError=Txx+TR*cos(6.28*CurlPosition/63);
	TyyError=Tyy-TR*sin(6.28*CurlPosition/63);
	gen_circle(&CircleCurlError, TyyError, TxxError, 10);
	disp_obj(CircleCurlError, FGHandle);


}

bool CHalcon001Dlg::Enable_Block(int block_x, int block_y)
{

	Hlong block_R=sqrt((double)((block_x-Txx)*(block_x-Txx)+(block_y-Tyy)*(block_y-Tyy)));
	if (block_R>TR-6&&block_R<TR)
	{
		return TRUE;
	} 
	else
	{
		return FALSE;
	}

}

void CHalcon001Dlg::On_Bn_jiao() 
{
	// TODO: Add your control notification handler code here
/////////////////////////////////////range TR-5~TR-24////////////////////////////
//////////////////////////////init////////////////////////2011 11 14///////////////

	Hobject Circle_jiao_inter;
	gen_circle(&Circle_jiao_inter, Tyy, Txx, TR-20);
	set_color(FGHandle, "blue");
	disp_obj(Circle_jiao_inter, FGHandle);


	Hobject Circle_jiao_outer;
	gen_circle(&Circle_jiao_outer, Tyy, Txx, TR-6);


	int Thred_error_jiao=0, Thred_jiao=350, Thred_jiao_inter=500, Thred_jiao_outer=800;

	Hobject Error_jiao;

///////////////////////////////////////////////////////////
///////////////////////////////run


	Hobject PolarTransImage_jiao, ImageEmphasize_jiao, ImageSub_jiao, ImageInvert_jiao;
	HTuple T1, T2;
	double tem_jiao, teml[160];
	int i, j, k;
	Hlong TxxError_jiao, TyyError_jiao;
	
	count_seconds(&T1);
	
	polar_trans_image_ext (image, &PolarTransImage_jiao, Tyy, Txx, 0, 6.74, TR-18, TR-7, 640, 12, "bilinear");

	emphasize(PolarTransImage_jiao, &ImageEmphasize_jiao, 5, 5, 3);

	invert_image(PolarTransImage_jiao, &ImageInvert_jiao);
	
	sub_image(ImageInvert_jiao, ImageEmphasize_jiao, &ImageSub_jiao, 1, 1);

	set_color(FGHandle, "red");

	for (i=0; i<3; i++)
	{
		teml[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=4; k<8; k++)
			{
				get_grayval(ImageSub_jiao, k, j, &tem_jiao);
				teml[i]=teml[i]+tem_jiao;	
			}
		}
	}

	for (i=3; i<155; i++)
	{
		teml[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=4; k<8; k++)
			{
				get_grayval(ImageSub_jiao, k, j, &tem_jiao);
				teml[i]=teml[i]+tem_jiao;	
			}	
		}
		if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_jiao)
		{
			Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
			TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
			TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
			gen_circle(&Error_jiao, TyyError_jiao, TxxError_jiao, 4);
			disp_obj(Error_jiao, FGHandle);
		}
	}






	if (Thred_error_jiao<=Thred_jiao)
	{
		for (i=0; i<3; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=8; k<12; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}
			}
		}
		
		for (i=3; i<155; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=8; k<12; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}	
			}
			if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_jiao_outer)
			{
				Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
				TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
				TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
				gen_circle(&Error_jiao, TyyError_jiao, TxxError_jiao, 4);
			disp_obj(Error_jiao, FGHandle);
			}
		}
	}


	
	if (Thred_error_jiao<=Thred_jiao_outer&&Thred_error_jiao<=Thred_jiao)
	{
		for (i=0; i<3; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<4; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}
			}
		}
		
		for (i=3; i<155; i++)
		{
			teml[i]=0;
			for (j=4*i; j<4*i+4; j++)
			{
				for (k=0; k<4; k++)
				{
					get_grayval(ImageSub_jiao, k, j, &tem_jiao);
					teml[i]=teml[i]+tem_jiao;	
				}	
			}
			if (abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i])>Thred_jiao_inter)
			{
				Thred_error_jiao=abs(teml[i-1]+teml[i-2]+teml[i-3]-3*teml[i]);
				TxxError_jiao=Txx+(TR-20+k)*cos(6.74*(j-2)/640);
				TyyError_jiao=Tyy-(TR-20+k)*sin(6.74*(j-2)/640);
				gen_circle(&Error_jiao, TyyError_jiao, TxxError_jiao, 4);
			disp_obj(Error_jiao, FGHandle);
			}
		}	
		
	}



///////////////////////////////////////////////////////////
///////////////////////////////run end


	count_seconds(&T2);
	
	HTuple DT = 1000000*(T2[0].D() - T1[0].D());
	
	CString tmp;
	tmp.Format("%4.1f",DT[0].D());
	m_NeedTime.SetWindowText(tmp + "us");


	if (Thred_error_jiao<=Thred_jiao_inter&&Thred_error_jiao<=Thred_jiao_outer&&Thred_error_jiao<=Thred_jiao)
	{
		AfxMessageBox("good jiao");
		}


	
}






void CHalcon001Dlg::On_Bn_qian() 
{
	// TODO: Add your control notification handler code here

///////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////init///////////////////////2011 11 14///////////////
	

	Hobject Circle_qian_mid;
	gen_circle(&Circle_qian_mid, Tyy, Txx, TR-26);
	set_color(FGHandle, "blue");
	disp_obj(Circle_qian_mid, FGHandle);
	
	
	Hobject Circle_qian_outer;
	gen_circle(&Circle_qian_outer, Tyy, Txx, TR-21);
	disp_obj(Circle_qian_outer, FGHandle);

	Hobject Circle_qian_inter;
	gen_circle(&Circle_qian_inter, Tyy, Txx, TR-31);
	disp_obj(Circle_qian_inter, FGHandle);
	

	int Thred_Error_qian=0, Thred_qian_a=1000, Thred_qian_b=2000;

///////////////////////////////////////////////////////////////////////
	///////////////////////////////////run////in a////out b////

	int i, j, k;
	
	Hobject PolarTransImage_qian_b, ImageEmphasize_qian_b;
	HTuple T1, T2;
	double tem_qian_b, tem_b[150];
	Hlong Txx_Error_qian_b, Tyy_Error_qian_b;
	Hobject Error_qian_b;

	count_seconds(&T1);
	
	polar_trans_image_ext (image, &PolarTransImage_qian_b, Tyy-1, Txx-1, 0, 6.667, TR-21, TR-25, 600, 5, "bilinear");
	
	emphasize(PolarTransImage_qian_b, &ImageEmphasize_qian_b, 5, 5, 3);

//	disp_obj(ImageEmphasize_qian_b, FGHandle);

	set_color(FGHandle, "red");

	for (i=0; i<3; i++)
	{
		tem_b[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<5; k++)
			{
				get_grayval(ImageEmphasize_qian_b, k, j, &tem_qian_b);
				tem_b[i]=tem_b[i]+tem_qian_b;	
			}
		}
	}

	for (i=3; i<145; i++)
	{
		tem_b[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<5; k++)
			{
				get_grayval(ImageEmphasize_qian_b, k, j, &tem_qian_b);
				tem_b[i]=tem_b[i]+tem_qian_b;	
			}	
		}
		if (abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i])>Thred_qian_b)
		{
			Thred_Error_qian=abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i]);
			Txx_Error_qian_b=Txx+(TR-22)*cos(6.667*(j-2)/600);
			Tyy_Error_qian_b=Tyy-(TR-22)*sin(6.667*(j-2)/600);
			gen_circle(&Error_qian_b, Tyy_Error_qian_b, Txx_Error_qian_b, 4);
			disp_obj(Error_qian_b, FGHandle);
		}
	}

	if (Thred_Error_qian>Thred_qian_b)
	{
		///////////////////////////////run end


		count_seconds(&T2);

		HTuple DT = 1000000*(T2[0].D() - T1[0].D());

		CString tmp;
		tmp.Format("%4.1f",DT[0].D());
		m_NeedTime.SetWindowText(tmp + "us_o");
		return;
	}
		
	////////////////////////////////////////////////////////////
	///////////////////////////a

	double tem_qian_a, tem_a[140];
	Hlong Txx_Error_qian_a, Tyy_Error_qian_a;
	Hobject Error_qian_a;

	Hobject PolarTransImage_qian_a, ImageEmphasize_qian_a;

	polar_trans_image_ext (image, &PolarTransImage_qian_a, Tyy-1, Txx-1, 0, 6.59, TR-31, TR-26, 560, 6, "bilinear");

	emphasize(PolarTransImage_qian_a, &ImageEmphasize_qian_a, 5, 5, 3);

//	disp_obj(ImageEmphasize_qian_a, FGHandle);

	set_color(FGHandle, "red");

	for (i=0; i<3; i++)
	{
		tem_a[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<6; k++)
			{
				get_grayval(ImageEmphasize_qian_a, k, j, &tem_qian_a);
				tem_a[i]=tem_a[i]+tem_qian_a;	
			}
		}
	}

	for (i=3; i<137; i++)
	{
		tem_a[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<6; k++)
			{
				get_grayval(ImageEmphasize_qian_a, k, j, &tem_qian_a);
				tem_a[i]=tem_a[i]+tem_qian_a;	
			}	
		}
		if (abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i])>Thred_qian_a)
		{
			Thred_Error_qian=abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i]);
			Txx_Error_qian_a=Txx+(TR-29)*cos(6.59*(j-2)/560);
			Tyy_Error_qian_a=Tyy-(TR-29)*sin(6.59*(j-2)/560);
			gen_circle(&Error_qian_a, Tyy_Error_qian_a, Txx_Error_qian_a, 4);
			disp_obj(Error_qian_a, FGHandle);
		}
	}



	if (Thred_Error_qian<=Thred_qian_a)
	{
		AfxMessageBox("good qian");
	}



	///////////////////////////////////////////////////////////
	///////////////////////////////run end
	
	
	count_seconds(&T2);
	
	HTuple DT = 1000000*(T2[0].D() - T1[0].D());
	
	CString tmp;
	tmp.Format("%4.1f",DT[0].D());
	m_NeedTime.SetWindowText(tmp + "us_i");
	
	

	
}

void CHalcon001Dlg::On_Bn_jin()
{
	// TODO: 在此添加控件通知处理程序代码



	Hobject Circle_jin_outer;
	gen_circle(&Circle_jin_outer, Tyy, Txx, TR-33);
	set_color(FGHandle, "blue");
	disp_obj(Circle_jin_outer, FGHandle);


	Hobject Circle_jin_a;
	gen_circle(&Circle_jin_a, Tyy, Txx, TR-42);
	disp_obj(Circle_jin_a, FGHandle);

	Hobject Circle_jin_b;
	gen_circle(&Circle_jin_b, Tyy, Txx, TR-52);
	disp_obj(Circle_jin_b, FGHandle);

	Hobject Circle_jin_c;
	gen_circle(&Circle_jin_c, Tyy, Txx, TR-58);
	disp_obj(Circle_jin_c, FGHandle);

	int Thred_Error_jin=0, Thred_jin_a=1700, Thred_jin_b=800, Thred_jin_c=800;

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////run////out a////mid b////in c////

	int i, j, k;

	Hobject PolarTransImage_jin_a, ImageEmphasize_jin_a;
	HTuple T1, T2;
	double tem_jin_a, tem_a[66];
	Hlong Txx_Error_jin_a, Tyy_Error_jin_a;
	Hobject Error_jin_a;

	count_seconds(&T1);

	polar_trans_image_ext (image, &PolarTransImage_jin_a, Tyy-1, Txx-1, 0, 6.6, TR-33, TR-41, 264, 9, "bilinear");

	emphasize(PolarTransImage_jin_a, &ImageEmphasize_jin_a, 5, 5, 3);

//	disp_obj(ImageEmphasize_jin_a, FGHandle);

	set_color(FGHandle, "red");

	for (i=0; i<3; i++)
	{
		tem_a[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<9; k++)
			{
				get_grayval(ImageEmphasize_jin_a, k, j, &tem_jin_a);
				tem_a[i]=tem_a[i]+tem_jin_a;	
			}
		}
	}

	for (i=3; i<66; i++)
	{
		tem_a[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<9; k++)
			{
				get_grayval(ImageEmphasize_jin_a, k, j, &tem_jin_a);
				tem_a[i]=tem_a[i]+tem_jin_a;	
			}	
		}
		if (abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i])>Thred_jin_a)
		{
			Thred_Error_jin=abs(tem_a[i-1]+tem_a[i-2]+tem_a[i-3]-3*tem_a[i]);
			Txx_Error_jin_a=Txx+(TR-37)*cos(6.6*(j-2)/264);
			Tyy_Error_jin_a=Tyy-(TR-37)*sin(6.6*(j-2)/264);
			gen_circle(&Error_jin_a, Tyy_Error_jin_a, Txx_Error_jin_a, 4);
			disp_obj(Error_jin_a, FGHandle);
		}
	}

	if (Thred_Error_jin>Thred_jin_a)
	{
		///////////////////////////////run end


		count_seconds(&T2);

		HTuple DT = 1000000*(T2[0].D() - T1[0].D());

		CString tmp;
		tmp.Format("%4.1f",DT[0].D());
		m_NeedTime.SetWindowText(tmp + "us_a");
		return;
	}

// 	////////////////////////////////////////////////////////////
// 	///////////////////////////b


	Hobject PolarTransImage_jin_b, ImageEmphasize_jin_b;
	double tem_jin_b, tem_b[62];
	Hlong Txx_Error_jin_b, Tyy_Error_jin_b;
	Hobject Error_jin_b;

	polar_trans_image_ext (image, &PolarTransImage_jin_b, Tyy-1, Txx-1, 0, 6.6, TR-42, TR-51, 248, 10, "bilinear");

	emphasize(PolarTransImage_jin_b, &ImageEmphasize_jin_b, 5, 5, 3);

//	disp_obj(ImageEmphasize_jin_b, FGHandle);

	set_color(FGHandle, "red");

	for (i=0; i<3; i++)
	{
		tem_b[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<10; k++)
			{
				get_grayval(ImageEmphasize_jin_b, k, j, &tem_jin_b);
				tem_b[i]=tem_b[i]+tem_jin_b;	
			}
		}
	}

	for (i=3; i<62; i++)
	{
		tem_b[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<10; k++)
			{
				get_grayval(ImageEmphasize_jin_b, k, j, &tem_jin_b);
				tem_b[i]=tem_b[i]+tem_jin_b;	
			}	
		}
		if (abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i])>Thred_jin_b)
		{
			Thred_Error_jin=abs(tem_b[i-1]+tem_b[i-2]+tem_b[i-3]-3*tem_b[i]);
			Txx_Error_jin_b=Txx+(TR-46)*cos(6.6*(j-2)/248);
			Tyy_Error_jin_b=Tyy-(TR-46)*sin(6.6*(j-2)/248);
			gen_circle(&Error_jin_b, Tyy_Error_jin_b, Txx_Error_jin_b, 4);
			disp_obj(Error_jin_b, FGHandle);
		}
	}

	if (Thred_Error_jin>Thred_jin_b)
	{
		///////////////////////////////run end


		count_seconds(&T2);

		HTuple DT = 1000000*(T2[0].D() - T1[0].D());

		CString tmp;
		tmp.Format("%4.1f",DT[0].D());
		m_NeedTime.SetWindowText(tmp + "us_b");
		return;
	}


	// 	////////////////////////////////////////////////////////////
	// 	///////////////////////////c


	Hobject PolarTransImage_jin_c, ImageEmphasize_jin_c;
	double tem_jin_c, tem_c[60];
	Hlong Txx_Error_jin_c, Tyy_Error_jin_c;
	Hobject Error_jin_c;

	polar_trans_image_ext (image, &PolarTransImage_jin_c, Tyy-1, Txx-1, 0, 6.7, TR-52, TR-58, 243, 7, "bilinear");

	emphasize(PolarTransImage_jin_c, &ImageEmphasize_jin_c, 5, 5, 3);

//	disp_obj(ImageEmphasize_jin_c, FGHandle);

	set_color(FGHandle, "red");

	for (i=0; i<3; i++)
	{
		tem_c[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<7; k++)
			{
				get_grayval(ImageEmphasize_jin_c, k, j, &tem_jin_c);
				tem_c[i]=tem_c[i]+tem_jin_c;	
			}
		}
	}

	for (i=3; i<60; i++)
	{
		tem_c[i]=0;
		for (j=4*i; j<4*i+4; j++)
		{
			for (k=0; k<7; k++)
			{
				get_grayval(ImageEmphasize_jin_c, k, j, &tem_jin_c);
				tem_c[i]=tem_c[i]+tem_jin_c;	
			}	
		}
		if (abs(tem_c[i-1]+tem_c[i-2]+tem_c[i-3]-3*tem_c[i])>Thred_jin_c)
		{
			Thred_Error_jin=abs(tem_c[i-1]+tem_c[i-2]+tem_c[i-3]-3*tem_c[i]);
			Txx_Error_jin_c=Txx+(TR-55)*cos(6.7*(j-2)/243);
			Tyy_Error_jin_c=Tyy-(TR-55)*sin(6.7*(j-2)/243);
			gen_circle(&Error_jin_c, Tyy_Error_jin_c, Txx_Error_jin_c, 4);
			disp_obj(Error_jin_c, FGHandle);
		}
	}


/////////////////////////////////////////////////////////////////////////////////
	// 	///////////////////////////////run end



	count_seconds(&T2);

	HTuple DT = 1000000*(T2[0].D() - T1[0].D());

	CString tmp;
	tmp.Format("%4.1f",DT[0].D());
	m_NeedTime.SetWindowText(tmp + "us_c");


	if (Thred_Error_jin<=Thred_jin_c)
	{
		AfxMessageBox("good jin");
	}



}











void CHalcon001Dlg::OnBnClickedBntai()
{
	// TODO: 在此添加控件通知处理程序代码


    Hlong error_number;

	///////////////////////////////////////////////////////////////////////
	///////////////////////////////////run////tai a////xin b////////

	HTuple T1, T2;


	count_seconds(&T1);




	Hobject tai, region_tai, mean_tai, white_tai, connect_tai, select_tai,em_tai, union_tai, dila_tai, ske_tai, error_tai, err;

	Hobject c1, c2, diff_taia, region_taia;



	
// 	// 	////////////////////////////////////////////////////////////
// 	// 	///////////////////////////b
// 

///////////////////////////////////////////////////////////////////////////////white
	gen_circle(&tai, Tyy, Txx, TR-90);
	change_domain (image, tai, &region_tai);
	mean_image (region_tai, &mean_tai, 2, 2);


	threshold (mean_tai, &white_tai, 189, 255);
	connection (white_tai, &connect_tai);
	select_shape (connect_tai, &select_tai, "area", "and", 10, 1000);
	union1 (select_tai, &union_tai);
	dilation_circle (union_tai, &dila_tai, 2);
	skeleton (dila_tai, &ske_tai);
	connection (ske_tai, &error_tai);
	select_shape (error_tai, &err, "outer_radius", "and", 10, 10000);
	disp_obj(err, FGHandle);


			count_obj(err, &error_number);

	if (error_number)
	{


		count_seconds(&T2);
		HTuple DT = 1000000*(T2[0].D() - T1[0].D());
		CString tmp;
		tmp.Format("%4.1f",DT[0].D());
		m_NeedTime.SetWindowText(tmp + "us_b");

		return;
	}


// //////////////////////////////////////////////////////////////////////////////black




		threshold (mean_tai, &white_tai, 0, 115);


		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &select_tai, "area", "and", 50, 1000);
		union1 (select_tai, &union_tai);
		dilation_circle (union_tai, &dila_tai, 1);
		skeleton (dila_tai, &ske_tai);
		connection (ske_tai, &error_tai);
		select_shape (error_tai, &err, "outer_radius", "and", 15, 10000);
		disp_obj(err, FGHandle);



				count_obj(err, &error_number);

				if (error_number)
				{


					count_seconds(&T2);
					HTuple DT = 1000000*(T2[0].D() - T1[0].D());
					CString tmp;
					tmp.Format("%4.1f",DT[0].D());
					m_NeedTime.SetWindowText(tmp + "us_b");

					return;
				}
/////////////////////////////////////////////////////////////////////////////////point


		threshold (mean_tai, &white_tai, 0, 80);


		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &err, "area", "and", 5, 1000);
		disp_obj(err, FGHandle);


				count_obj(err, &error_number);

				if (error_number)
				{


					count_seconds(&T2);
					HTuple DT = 1000000*(T2[0].D() - T1[0].D());
					CString tmp;
					tmp.Format("%4.1f",DT[0].D());
					m_NeedTime.SetWindowText(tmp + "us_b");

					return;
				}


////////////////////////////////////////////////////////////////////////////////press

		threshold (mean_tai, &white_tai, 140,255);


		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &err, "area", "and", 5, 1000);
		disp_obj(err, FGHandle);



				count_obj(err, &error_number);

				if (error_number)
				{



					count_seconds(&T2);
					HTuple DT = 1000000*(T2[0].D() - T1[0].D());
					CString tmp;
					tmp.Format("%4.1f",DT[0].D());
					m_NeedTime.SetWindowText(tmp + "us_b");

					return;
				}



/////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////a

		gen_circle(&c1, Tyy, Txx, TR-78);
		gen_circle(&c2, Tyy,Txx,TR-85);

		// 	set_color(FGHandle, "red");
		// 	disp_obj(c2, FGHandle);
		// 	disp_obj(c1, FGHandle);

		difference(c1, c2, &diff_taia);
		reduce_domain(image, diff_taia, &region_taia);
		mean_image (region_taia, &mean_tai, 2, 2);
		threshold(mean_tai, &white_tai, 90, 120);
		connection (white_tai, &connect_tai);
		select_shape (connect_tai, &select_tai, "area", "and", 10, 1000);
		union1 (select_tai, &union_tai);
		dilation_circle (union_tai, &dila_tai, 1.5);
		skeleton (dila_tai, &ske_tai);
		connection (ske_tai, &error_tai);
		select_shape (error_tai, &err, "area", "and", 5, 10000);

		count_obj(err, &error_number);

		count_seconds(&T2);
		HTuple DT = 1000000*(T2[0].D() - T1[0].D());
		CString tmp;
		tmp.Format("%4.1f",DT[0].D());
		m_NeedTime.SetWindowText(tmp + "us_b");

		if (!error_number)
		{
			AfxMessageBox("good tai");
		}


	









}
	
	












void CHalcon001Dlg::On_Bn_Test()
{
	// TODO: 在此添加控件通知处理程序代码




	HTuple T1, T2;

	count_seconds(&T1);

	
	Hobject tai, region_tai, mean_tai, white_tai, connect_tai, select_tai, union_tai, dila_tai, ske_tai, error_tai, err;
	Hlong t;
	double r, c;
	


	
	gen_circle(&tai, Tyy, Txx, TR-85);
	change_domain (image, tai, &region_tai);
	mean_image (region_tai, &mean_tai, 2, 2);
	threshold (mean_tai, &white_tai, 189, 255);
	connection (white_tai, &connect_tai);
	select_shape (connect_tai, &select_tai, "area", "and", 10, 1000);
	union1 (select_tai, &union_tai);
	dilation_circle (union_tai, &dila_tai, 3.5);
	skeleton (dila_tai, &ske_tai);
	connection (ske_tai, &error_tai);
	select_shape (error_tai, &err, "area", "and", 25, 10000);


	disp_obj(err, FGHandle);































	count_seconds(&T2);

	HTuple DT = 1000000*(T2[0].D() - T1[0].D());

	CString tmp;
	tmp.Format("%4.1f",DT[0].D());
	m_NeedTime.SetWindowText(tmp + "us_test");






}
