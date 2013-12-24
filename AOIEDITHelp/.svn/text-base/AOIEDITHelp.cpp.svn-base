
// AOIEDITHelp.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "AOIEDITHelp.h"
#include "MainFrm.h"
#include "DoProcess/CMCfgCenter.h"
#include "AOIEDITHelpDoc.h"
#include "AOIEDITHelpView.h"
#include <atlconv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma data_seg("Shared")
volatile LONG g_lIsOpenCfg = 0;
#pragma data_seg()
#pragma  comment(linker,"/Section:Shared,RWS")

BEGIN_MESSAGE_MAP(CAOIEDITHelpApp, CWinApp)
END_MESSAGE_MAP()

void CAOIEDITHelpApp::OnMyFileOpen()
{
	if (!CWinApp::DoPromptFileName(m_file_path,
		AFX_IDS_OPENFILE,
		OFN_HIDEREADONLY|OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST,
		TRUE, NULL))
	{
		return;
	}
    m_pFrmWnd->ReStart();
    return;
};
CAOIEDITHelpApp::CAOIEDITHelpApp():m_currentDocument(0)
{
	EnableHtmlHelp();
	m_TLSFileName = L"";
	m_ImageFileName=L"D:\\SLACTST\\MaLai_CPG_EN\\sample.tiff";
}

CAOIEDITHelpApp theApp;

void CAOIEDITHelpApp::LoadBitmaps(BOOL fFree)
{
   if (fFree)
   {
	   m_images.DeleteImageList();
   }
   if (0==m_images.Create(IDB_IMAGELIST,16,100,RGB(0,255,0)))
   {
	   AfxMessageBox(_T("Cannot load bitmaps"));
   }
}

void CAOIEDITHelpApp::FreeBitmaps()
{
   m_images.DeleteImageList();
}

int CAOIEDITHelpApp::ExitInstance()
{
	InterlockedExchangeAdd(&g_lIsOpenCfg,-1);
	return CWinApp::ExitInstance() ;
}

BOOL CAOIEDITHelpApp::InitInstance()
{
	CWinApp::InitInstance();
    
	if (1<=g_lIsOpenCfg)
	{
		//return FALSE;
	}
	InterlockedExchangeAdd(&g_lIsOpenCfg,1);
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(4);  
    LoadBitmaps( FALSE ) ;

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CAOIEDITHelpDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CAOIEDITHelpView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	CString cmd1 = GetCommandLine();
	std::wstring szCmd(cmd1.GetBuffer());
	wchar_t exeName[MAX_PATH]=L"";
	wchar_t ImageFileBuFF[MAX_PATH]=L"";
	wchar_t TLSFileBuFF[MAX_PATH]=L"";
	wchar_t ProcessBuFF[MAX_PATH]=L"";
	wchar_t UserBuFF[MAX_PATH]=L"";
	_stscanf(szCmd.c_str(),_T("%s %s %s %s %s"),exeName,ImageFileBuFF,TLSFileBuFF,ProcessBuFF,UserBuFF);
	int process_id = _ttoi(ProcessBuFF);

	CMCfgCenter::GetCfgCenter().SetImageSize(600, 600);

	USES_CONVERSION;
	if (0 != process_id)
	{
		m_ImageFileName = ImageFileBuFF;
		wstring name = m_ImageFileName;

		Hobject image;
		read_image(&image,W2A(name.c_str()));
		Hlong  lWidth,  lHeight;
		get_image_size(image, &lWidth, &lHeight);

		CMCfgCenter::GetCfgCenter().SetImageSize(lWidth, lHeight);

		m_TLSFileName = TLSFileBuFF;
		m_processID = ProcessBuFF;
		m_user = UserBuFF;
		
		(_tcsrchr(ImageFileBuFF, _T('\\')))[1] = 0; //删除文件名，只获得路径
		m_ProgramName = ImageFileBuFF;
	}
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	cmdInfo.m_nShellCommand = cmdInfo.FileNew;

	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	m_pMainWnd->ShowWindow(SW_MAXIMIZE);

	m_pMainWnd->UpdateWindow();
	m_pMainWnd->SetMenu(NULL);
	m_pMainWnd->DragAcceptFiles();
	m_pFrmWnd= (CMainFrame*)m_pMainWnd;
	m_file_path = _T("sample.tiff");
	m_pFrmWnd->SysInit();
	return TRUE;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

void CAOIEDITHelpApp::OnAppAbout()
{
	if (m_pFrmWnd->m_bSysRun)return;
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}



