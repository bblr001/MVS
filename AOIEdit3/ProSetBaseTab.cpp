// ProSetBaseTab.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "ProSetBaseTab.h"
#include "ProgramSettingDlg.h"
#include "MConfigCenter.h"
#include "MCtrlCenter.h"

// CProSetBaseTab 对话框

IMPLEMENT_DYNAMIC(CProSetBaseTab, CPropertyPage)

CProSetBaseTab::CProSetBaseTab()
	:CPropertyPage(CProSetBaseTab::IDD),
	 m_pConfigCenter(CMConfigCenter::GetSingletonConfigCenter())
{

}

CProSetBaseTab::~CProSetBaseTab()
{
}

void CProSetBaseTab::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_SAVE_IMAGE, m_bSaveErrImag);
	DDX_Control(pDX, IDC_BUTTON_SOURCESEL, m_SettingPathButton);
	DDX_Control(pDX, IDC_STATIC_PATH, m_ShowSetting);
	DDX_Control(pDX, IDC_EDIT_TIMEI, m_TimeInterval);
	DDX_Control(pDX, IDC_EDIT_ERRORCOUNT, m_ErrorFileCount);
	DDX_Control(pDX, IDC_CHECK2, m_bSavePassImage);
}


BEGIN_MESSAGE_MAP(CProSetBaseTab, CPropertyPage)
		ON_BN_CLICKED(IDOK, &CProgramSettingDlg::OnBnClickedOk)
		ON_BN_CLICKED(IDC_RADIO_FILE, &CProSetBaseTab::OnBnClickedRadioFile)
		ON_BN_CLICKED(IDC_RADIO_FILES, &CProSetBaseTab::OnBnClickedRadioFiles)
		ON_BN_CLICKED(IDC_RADIO_CAMERA, &CProSetBaseTab::OnBnClickedRadioCamera)
		ON_BN_CLICKED(IDC_BUTTON_SOURCESEL, &CProSetBaseTab::OnBnClickedButtonSourcesel)
		ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CProSetBaseTab 消息处理程序
BOOL CProSetBaseTab::OnBnClickedOk()
{
	if(m_bSaveErrImag.GetCheck()   ==   BST_CHECKED) 
	{
		m_pConfigCenter->SetSaveFailImageStatus(true);
	}
	else
	{
		m_pConfigCenter->SetSaveFailImageStatus(false);
	}

	if(m_bSavePassImage.GetCheck()  ==  BST_CHECKED) 
	{
		m_pConfigCenter->SetSavePassImageStatus(true);
	}
	else
	{
		m_pConfigCenter->SetSavePassImageStatus(false);
	}

	if (m_pConfigCenter->GetImgSource() == SINGLE_IMG_FILE)
	{
		string fileName = m_pConfigCenter->GetRecvFileName();
		if (_access(fileName.c_str(),0))
		{
			CString msg;
			msg.Format(_T("Debug Error！ Can't read image file %s.Please check the setting file"),(s2ws(fileName)).c_str());
			AfxMessageBox(msg);
			return FALSE;
		}
	}
	m_pConfigCenter->SetReciveFilesTimeInterval(GetDlgItemInt(IDC_EDIT_TIMEI));

	OnOK();
	return TRUE;
}

BOOL CProSetBaseTab::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	if(m_pConfigCenter->GetSaveFailImageStatus())
	{
		m_bSaveErrImag.SetCheck(BST_CHECKED);
		m_ErrorFileCount.EnableWindow(TRUE);
	}
	else
	{
		m_bSaveErrImag.SetCheck(BST_UNCHECKED);
		m_ErrorFileCount.EnableWindow(FALSE);
	}

	((CButton *)GetDlgItem(IDC_RADIO_FILE))->SetCheck(FALSE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_FILES))->SetCheck(FALSE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_CAMERA))->SetCheck(FALSE);//选上

	CString name;
	switch(m_pConfigCenter->GetImgSource())
	{
	case IMG_FILES:
		name = (s2ws(m_pConfigCenter->GetRecvFilesPath())).c_str();
		m_ShowSetting.SetWindowText(name);
		((CButton *)GetDlgItem(IDC_RADIO_FILES))->SetCheck(TRUE);//选上
		m_SettingPathButton.EnableWindow(TRUE);
		m_ShowSetting.SetWindowText((s2ws(m_pConfigCenter->GetRecvFilesPath())).c_str());
		m_TimeInterval.EnableWindow(TRUE);
		SetDlgItemInt(IDC_EDIT_TIMEI,m_pConfigCenter->GetReciveFilesTimeInterval());
		break;

	case SINGLE_IMG_FILE:
		((CButton *)GetDlgItem(IDC_RADIO_FILE))->SetCheck(TRUE);//选上
#ifdef _ENGLISH
		m_ShowSetting.SetWindowText(_T("Please select the image file."));
#else
		m_ShowSetting.SetWindowText(_T("请选择图片文件路径."));
#endif
		m_SettingPathButton.EnableWindow(TRUE);
		break;

	case CAMERA_SOURCE:			
		name = (s2ws(m_pConfigCenter->GetCameraName())).c_str();
		m_SettingPathButton.EnableWindow(FALSE);
		m_ShowSetting.SetWindowText(name);
		((CButton *)GetDlgItem(IDC_RADIO_CAMERA))->SetCheck(TRUE);//选上
		break;
	default:
		break;
	}
	return TRUE;
}

void CProSetBaseTab::OnBnClickedRadioFile()
{

	((CButton *)GetDlgItem(IDC_RADIO_FILE))->SetCheck(TRUE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_FILES))->SetCheck(FALSE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_CAMERA))->SetCheck(FALSE);//选上

	m_SettingPathButton.EnableWindow(TRUE);
	m_TimeInterval.EnableWindow(FALSE);
#ifdef _ENGLISH
		m_ShowSetting.SetWindowText(_T("Please select the image file."));
#else
		m_ShowSetting.SetWindowText(_T("请选择图片文件路径."));
#endif

	m_pConfigCenter->SetImgSource(SINGLE_IMG_FILE);
	m_pConfigCenter->SetDebugModeFlag(true);
	return;
}

void CProSetBaseTab::OnBnClickedRadioFiles()
{
	((CButton *)GetDlgItem(IDC_RADIO_FILE))->SetCheck(FALSE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_FILES))->SetCheck(TRUE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_CAMERA))->SetCheck(FALSE);//选上
	m_SettingPathButton.EnableWindow(TRUE);
	m_TimeInterval.EnableWindow(TRUE);
	SetDlgItemInt(IDC_EDIT_TIMEI,500);
	m_ShowSetting.SetWindowText((s2ws(m_pConfigCenter->GetRecvFilesPath())).c_str());
	m_pConfigCenter->SetImgSource(IMG_FILES);
	return;
}

void CProSetBaseTab::OnBnClickedRadioCamera()
{
	((CButton *)GetDlgItem(IDC_RADIO_FILE))->SetCheck(FALSE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_FILES))->SetCheck(FALSE);//选上
	((CButton *)GetDlgItem(IDC_RADIO_CAMERA))->SetCheck(TRUE);//选上
	m_SettingPathButton.EnableWindow(FALSE);
	m_TimeInterval.EnableWindow(FALSE);
	m_ShowSetting.SetWindowText((s2ws(m_pConfigCenter->GetCameraName())).c_str());
	m_pConfigCenter->SetImgSource(CAMERA_SOURCE);

}


void CProSetBaseTab::OnBnClickedButtonSourcesel()
{
	if (m_pConfigCenter->GetImgSource() ==SINGLE_IMG_FILE)
	{
		//from 文件
		string fileName;
		CFileDialog   OpenImageDlg(TRUE,NULL, NULL,OFN_HIDEREADONLY, _T("Image File(*.tiff;*.png;*.bmp;*.jpg)|*.tiff;*.bmp;*.jpg;*.png"));//open   as 
		CString defPath;
		defPath.Format(_T("d:\\SLACTST\\%s\\"),(s2ws(m_pConfigCenter->GetProgramName())).c_str());
		OpenImageDlg.m_ofn.lpstrInitialDir=defPath;
		if(OpenImageDlg.DoModal()==IDOK) 
		{ 		
			wstring tmp(OpenImageDlg.GetPathName());
			fileName= ws2s(tmp);
			m_ShowSetting.SetWindowText(tmp.c_str());
		}
		m_pConfigCenter->SetRecvFileName(fileName);
		OpenImageDlg.DestroyWindow();

	}
	if (m_pConfigCenter->GetImgSource() ==IMG_FILES)
	{
		//from 文件夹
		TCHAR strDirName[MAX_PATH];
		BROWSEINFO bi;
		CString szString = TEXT("选择一个源文件子文件夹");
		bi.hwndOwner = ::GetFocus();
		bi.pidlRoot = NULL;
		bi.pszDisplayName = strDirName;
		bi.lpszTitle = szString;
		bi.ulFlags = BIF_BROWSEFORCOMPUTER | BIF_DONTGOBELOWDOMAIN | BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		bi.lParam = 0;
		bi.iImage = 0;
		LPITEMIDLIST pItemIDList = ::SHBrowseForFolder(&bi);
		if(pItemIDList == NULL)
		{
			return ;
		}
		::SHGetPathFromIDList(pItemIDList, strDirName);
		CString str = strDirName;
		if(str != "" && str.Right(1) != '\\')
			str += '\\';

		wstring strTmp =str.GetBuffer(0);
		string tmpa = ws2s(strTmp);
		
		m_pConfigCenter->SetRecvFilesPath(tmpa.c_str());
		m_ShowSetting.SetWindowText(strTmp.c_str());
	}
}

