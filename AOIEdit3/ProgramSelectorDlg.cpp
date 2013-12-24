// OpenProgram.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "ProgramSelectorDlg.h"
#include "MConfigCenter.h"
#include <io.h>


// CProgramSelectorDlg 对话框

IMPLEMENT_DYNAMIC(CProgramSelectorDlg, CDialog)

CProgramSelectorDlg::CProgramSelectorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgramSelectorDlg::IDD, pParent)
{
}

CProgramSelectorDlg::~CProgramSelectorDlg()
{
	close_window(m_HWindowID);
}

void CProgramSelectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROGRAM, m_ProgramList);
	DDX_Control(pDX, IDC_STATIC_OPENDLG_LOGO, m_PicLog);
	DDX_Control(pDX, IDOK, m_bOK);
}


BEGIN_MESSAGE_MAP(CProgramSelectorDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROGRAM, &CProgramSelectorDlg::OnNMClickListProgram)
	ON_BN_CLICKED(IDOK, &CProgramSelectorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CProgramSelectorDlg 消息处理程序

BOOL CProgramSelectorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitProgramList();
	CRect logoRect;
	logoRect.SetRectEmpty();
	m_PicLog.GetClientRect(&logoRect);
	using namespace Halcon;
	set_window_attr("border_width",0);
	set_check("~father");
	open_window(logoRect.top, logoRect.left, logoRect.Width(), logoRect.Height(), (Hlong)m_PicLog.m_hWnd,"visible","",&m_HWindowID);
	set_check("father");

	return TRUE;

}

void CProgramSelectorDlg::InitProgramList()
{
	DWORD dwStyle2 = m_ProgramList.GetExtendedStyle();
	dwStyle2 |= LVS_EX_FULLROWSELECT;//选中某行使整行高亮（只适用与report风格的listctrl）
	dwStyle2 |= LVS_EX_GRIDLINES;//网格线（只适用与report风格的listctrl）
	dwStyle2 |= LVS_EX_CHECKBOXES;//item前生成checkbox控件
	m_ProgramList.SetExtendedStyle(dwStyle2); //设置扩展风格

	m_ProgramList.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
#ifdef _ENGLISH
	m_ProgramList.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 60);
	m_ProgramList.InsertColumn(1, _T("Program Name"), LVCFMT_LEFT, 150);
#else
	m_ProgramList.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 60);
	m_ProgramList.InsertColumn(1, _T("程式名"), LVCFMT_LEFT, 150);
#endif

	CFileFind ff;
	wstring serachPath = CMConfigCenter::GetSingletonConfigCenter()->GetTestProgramPath();
	serachPath += _T("\\*.*");
	BOOL bRet = FALSE;
	if (ff.FindFile(serachPath.c_str()))
	{
		int itemCount = 0;
		CString item;		
		do
		{
			bRet = ff.FindNextFile();
			if(ff.IsDirectory() && !ff.IsDots())//目录是文件夹
			{
				item.Format(_T("%d"),itemCount);
				m_ProgramList.InsertItem(itemCount, item);
				m_ProgramList.SetItemText(itemCount,1,ff.GetFileName());
				itemCount++;
			}
		}while (bRet);		
	} 
	m_bOK.EnableWindow(TRUE);
}

void CProgramSelectorDlg::OnNMClickListProgram(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int iItem = pNMItemActivate->iItem;
	if(-1 != iItem)
	{
		int iSubItem = 1;

		TCHAR szBuf[1024];
		LVITEM lvi;
		lvi.iItem = iItem;
		lvi.iSubItem = 1;
		lvi.mask = LVIF_TEXT;
		lvi.pszText = szBuf;
		lvi.cchTextMax = 1024;
		m_ProgramList.GetItem(&lvi);
		wstring program(szBuf);
		m_programName = program;
		wstring programPath = CMConfigCenter::GetSingletonConfigCenter()->GetTestProgramPath();
		wstring strSampleImage = programPath + m_programName + L"\\sample.tiff";
		
		if (0 == _waccess(strSampleImage.c_str(),0))
		{
			Hobject image;
			read_image(&image,(ws2s(strSampleImage)).c_str());
			Hlong  lWidth,  lHeight;
			get_image_size(image, &lWidth, &lHeight);
			auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
			pConfigCenter->SetDemoImgSize(lWidth, lHeight);
			set_part(m_HWindowID, 0, 0, lHeight-1, lWidth-1);
			disp_obj(image,m_HWindowID);
		}
		else
		{
			MessageBox(_T("Sample Image does not exist!"),MB_OK);
		}
	}
	*pResult = 0;
}

void CProgramSelectorDlg::OnBnClickedOk()
{
	auto pConfigCenter = CMConfigCenter::GetSingletonConfigCenter();
	if(!pConfigCenter->LoadProgramConfig(m_programName))
	{
		AfxMessageBox(_T("Loading process.cfg failed !"));
		return;
	}
	wstring programPath = pConfigCenter->GetTestProgramPath();//ws2s();
	programPath += m_programName;
	programPath += L"\\";

	string tmpPath = ws2s(programPath);
	string filename = tmpPath +  pConfigCenter->GetTLSFileName();
	CString msg;
	if (0 != _access(filename.c_str(),0))
	{
		msg.Format(_T("Cannot find TLS File %s."),s2ws(filename).c_str());
		MessageBox(msg,theApp.m_strStaionID,MB_OK);
		return;
	}
	pConfigCenter->SetRejectPort(pConfigCenter->GetRejectPort());

	OnOK();
}
