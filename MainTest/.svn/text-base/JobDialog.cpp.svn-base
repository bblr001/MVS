// JobDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "MainTest.h"
#include "JobDialog.h"
#include "JobMainView.h"
#include "JobTestListView.h"

// CJobDialog 对话框

IMPLEMENT_DYNAMIC(CJobDialog, CDialog)

CJobDialog::CJobDialog(MI_SETTING*  wPanel)
	: CDialog(CJobDialog::IDD)
{
	m_pCurrentPanel = wPanel;

}

CJobDialog::~CJobDialog()
{
}

void CJobDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}



int CJobDialog::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	// Because the CFRameWnd needs a window class, we will create a new one. I just copied the sample from MSDN Help.
	// When using it in your project, you may keep CS_VREDRAW and CS_HREDRAW and then throw the other three parameters.
	//需要注册窗口类
	CString strMyClass = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW,  
		::LoadCursor(NULL, IDC_ARROW),    (HBRUSH) ::GetStockObject(WHITE_BRUSH),   
		::LoadIcon(NULL, IDI_APPLICATION));

	// Create the frame window with "this" as the parent
	m_pJobFrameWnd = new CFrameWnd;
	m_pJobFrameWnd->Create(strMyClass,_T(""), WS_CHILD,   CRect(0,0,500,500), this);
	m_pJobFrameWnd->ShowWindow(SW_SHOW);

	// and finally, create the splitter with the frame as the parent
	m_cSplitter.CreateStatic(m_pJobFrameWnd,2, 1); //在Frame里切分视图窗口为1×2，就是一行两列

	
	m_cSplitter.CreateView(0,0,  RUNTIME_CLASS(CJobMainView),   CSize(300,300), NULL);//第一行一列
	m_cSplitter.CreateView(1,0, RUNTIME_CLASS(CJobTestListView), CSize(200,200), NULL);//第二行一列
	
	CJobMainView* pJobMainView=(CJobMainView*)m_cSplitter.GetPane(0,0); 
	pJobMainView->Init(m_pCurrentPanel);

	CJobTestListView* pJopTestListView=(CJobTestListView*)m_cSplitter.GetPane(1,0); 
	pJopTestListView->Init(m_pCurrentPanel);

	return 0;
}

BEGIN_MESSAGE_MAP(CJobDialog, CDialog)
		ON_WM_CREATE()
END_MESSAGE_MAP()


// CJobDialog 消息处理程序

int CJobDialog::OnInitDialog()
{
	CDialog::OnInitDialog();
	CRect cRect;

	GetWindowRect(&cRect);
	cRect.top+=25;
	

	ScreenToClient(&cRect);
	m_pJobFrameWnd->MoveWindow(&cRect);
	m_pJobFrameWnd->ShowWindow(SW_SHOW);


	return TRUE;
}




