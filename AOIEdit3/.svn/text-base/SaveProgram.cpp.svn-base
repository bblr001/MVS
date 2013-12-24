// SaveProgram.cpp : 实现文件
//

#include "stdafx.h"
#include "AOIEditVer3.h"
#include "SaveProgram.h"

#include "MConfigCenter.h"


// SaveProgram 对话框

IMPLEMENT_DYNAMIC(SaveProgram, CDialog)

SaveProgram::SaveProgram(CWnd* pParent /*=NULL*/)
	: CDialog(SaveProgram::IDD, pParent),
	  m_pConfigCenter(CMConfigCenter::GetSingletonConfigCenter())
{

}

SaveProgram::~SaveProgram()
{
}

void SaveProgram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SAVEDLG_LOGO, m_Static_SaveDLG_ProLogo);
}


BEGIN_MESSAGE_MAP(SaveProgram, CDialog)
	ON_WM_CREATE()
	ON_WM_SIZE()

	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
	ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED, OnPropertyChanged)
	
	ON_BN_CLICKED(IDOK, &SaveProgram::OnBnClickedOk)
END_MESSAGE_MAP()


// SaveProgram 消息处理程序

void SaveProgram::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}
	CRect rectClient;
	GetClientRect(rectClient);
	m_ProgramList.SetWindowPos(NULL, rectClient.left+1, rectClient.top+1, (int)(rectClient.Width()/2.5), (int)(rectClient.Height()/1.2), SWP_NOACTIVATE | SWP_NOZORDER);
}


void SaveProgram::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	CRect rectProp;
	m_ProgramList.GetWindowRect(rectProp);
	ScreenToClient(rectProp);
	rectProp.InflateRect(1, 1);
	dc.Draw3dRect(rectProp, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}


int SaveProgram::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// 	// 创建组合:
	//const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
	if (!m_ProgramList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}
	AdjustLayout();
	return 0;
}

void SaveProgram::OnSize(UINT nType, int cx, int cy)
{
	AdjustLayout();
}

void SaveProgram::SetPropertyList()
{
	SetPropListFont();
	m_ProgramList.RemoveAll();

	m_ProgramList.EnableHeaderCtrl(FALSE);
	m_ProgramList.EnableDescriptionArea();
	m_ProgramList.SetVSDotNetLook();
	m_ProgramList.MarkModifiedProperties();

	
	CMFCPropertyGridProperty* pBaseInfo = new CMFCPropertyGridProperty(_T("BaseInfo"));
		
	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("programname"),s2ws(m_pConfigCenter->GetProgramName()).c_str(), _T("Program Name"));
	pProp->Enable(FALSE);
	pBaseInfo->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("tlsfilename"), (s2ws(m_pConfigCenter->GetTLSFileName())).c_str(), _T("TLS File Name"));
	pProp->Enable(FALSE);
	pBaseInfo->AddSubItem(pProp);
	
	EMDATA_SOURCE source = m_pConfigCenter->GetImgSource();
	wstring str_source;
	str_source = _T("NONE");
	switch(source)
	{
	case  IMG_FILES:
		{
			str_source=_T("IMG_FILES");
			break;
		}
	case  SINGLE_IMG_FILE:
		{
			str_source=_T("SINGLE_IMG_FILE");
			break;
		}
	case CAMERA_SOURCE:
		{
			str_source=_T("CAMERA_SOURCE");
			break;
		}
	default:
		break;
	}
	pProp = new CMFCPropertyGridProperty( _T("source"), str_source.c_str(), _T("Source"));
	pProp->Enable(FALSE);
	pBaseInfo->AddSubItem(pProp);

	bool m_bStatus = m_pConfigCenter->GetSaveFailImageStatus();
	wstring str_SaveErrImageStatus;
	if(m_bStatus)
	{
		str_SaveErrImageStatus=_T("YES");
	}
	else
	{
		str_SaveErrImageStatus=_T("NO");
	}

	pProp = new CMFCPropertyGridProperty( _T("SaveErrImage"), str_SaveErrImageStatus.c_str(), _T("SaveErrImage"));
	pProp->Enable(FALSE);
	pBaseInfo->AddSubItem(pProp);

	m_ProgramList.AddProperty(pBaseInfo);

	CMFCPropertyGridProperty* pCameraInfo = new CMFCPropertyGridProperty(_T("CameraInfo"));

	pProp = new CMFCPropertyGridProperty(_T("CameraName"),s2ws(m_pConfigCenter->GetCameraName()).c_str(), _T("Camera Name"));
	pProp->Enable(FALSE);
	pCameraInfo->AddSubItem(pProp);

	m_ProgramList.AddProperty(pCameraInfo);

	CMFCPropertyGridProperty* pRejectInfo = new CMFCPropertyGridProperty(_T("RejectInfo"));

	CString msg;
	msg.Format(_T("%d"),m_pConfigCenter->GetRejectPort());
	pProp = new CMFCPropertyGridProperty(_T("RejectPort"),msg, _T("Reject Port"));
	pProp->Enable(FALSE);
	pRejectInfo->AddSubItem(pProp);

	m_ProgramList.AddProperty(pRejectInfo);
}

void SaveProgram::OnSetFocus(CWnd* pOldWnd)
{
	m_ProgramList.SetFocus();
}

void SaveProgram::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	//AfxMessageBox(_T("Setting change"));
	//CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void SaveProgram::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_ProgramList.SetFont(&m_fntPropList);
}

LRESULT SaveProgram::OnPropertyChanged( WPARAM,LPARAM lParam )
{
	CMFCPropertyGridProperty* pProp = (CMFCPropertyGridProperty*) lParam;
	return 0;
}

void SaveProgram::OnBnClickedOk()
{
	m_pConfigCenter->SaveProgramData();
	OnOK();
}

BOOL SaveProgram::OnInitDialog()
{
	CDialog::OnInitDialog();
	SetPropertyList();
	CRect m_Input_Log_Rect;
	m_Input_Log_Rect.SetRectEmpty();

	m_sProgramPath = m_pConfigCenter->GetTestProgramPath() + _T("\\");
	m_sProgramPath+= s2ws(m_pConfigCenter->GetProgramName());
	m_sProgramPath+=_T("\\");

	m_Static_SaveDLG_ProLogo.GetClientRect(&m_Input_Log_Rect);

	return TRUE;
}