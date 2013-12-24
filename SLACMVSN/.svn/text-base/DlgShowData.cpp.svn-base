// DlgShowHistoryData.cpp : implementation file
//

#include "stdafx.h"
#include "SLACMVSN.h"
#include "DlgShowData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgShowHistoryData dialog

#define  itemCnt  4
CDlgShowHistoryData::CDlgShowHistoryData(CWnd* pParent /*=NULL*/)
: CDialog(CDlgShowHistoryData::IDD, pParent),m_bIsConnect(false)
{
	//{{AFX_DATA_INIT(CDlgShowHistoryData)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgShowHistoryData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgShowHistoryData)
	// NOTE: the ClassWizard will add DDX and DDV calls here

	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_LIST1, m_gridListVw);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dttmStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_dttmEnd);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_dttmTimeStart);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_dttmEndTime);
	DDX_Control(pDX, IDC_STATIC_ALL, m_lbTotalNum);
	DDX_Control(pDX, IDC_STATIC_FAIL, m_lbFautyNum);
	DDX_Control(pDX, IDC_STATIC_PERC, m_lbPercent);
}

int CDlgShowHistoryData::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	return CDialog::OnCreate(lpCreateStruct);
}
void CDlgShowHistoryData::SetDbName(char * pcdbname,int len)
{
	strcpy_s(m_dbname,len,pcdbname);
}
CDlgShowHistoryData::~CDlgShowHistoryData()
{
	if (m_bIsConnect)
	{
		m_db->Close();
		delete m_db;
	}
}
void CDlgShowHistoryData::InitConnect()
{
   if (!m_bIsConnect&&strlen(m_dbname)>0)
   {
	   m_db =  new CSqliteDB<CppSQLite3Query>;
	   m_db->SetDBName(m_dbname);
	   m_bIsConnect = m_db->Connect();
   }
}
BOOL CDlgShowHistoryData::OnInitDialog()
{
	BOOL   bResult = CDialog::OnInitDialog();
	UpdateData();
	m_gridListVw.SetExtendedStyle
		(m_gridListVw.GetExtendedStyle()|LVS_EX_BORDERSELECT|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	m_gridListVw.DeleteAllItems();
	m_gridListVw.PrepareControl(0);
	m_gridListVw.SetBkColor(RGB(253,248,187));
	m_gridListVw.SetTextBkColor(RGB(253,248,187));

	CImageList   m_l; 
	m_l.Create(1,24,TRUE|ILC_COLOR32,1,0); 
	m_gridListVw.SetImageList(&m_l,LVSIL_SMALL);

#ifdef _ENGLISH
	LPWSTR lptItemCol[itemCnt] = {TEXT("Test"),TEXT("SubTest"),TEXT("FailCount"),TEXT("FailRate")};
#else
	LPWSTR lptItemCol[itemCnt] = {TEXT("检测项目"),TEXT("检测内容"),TEXT("不良盖数"),TEXT("检测不良率")};
#endif
	LV_COLUMN lvcolumn;
	
	for (int i =0; i < itemCnt ; ++i )
	{
		lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_ORDER|LVS_EX_AUTOSIZECOLUMNS;
		lvcolumn.fmt  = LVCFMT_CENTER;
		lvcolumn.pszText = lptItemCol[i];
		lvcolumn.iSubItem = i;
		lvcolumn.iOrder   = i;
		lvcolumn.cxIdeal = 100;
		lvcolumn.cx = 100;
        m_gridListVw.InsertColumn(i,&lvcolumn);
	}
	CRect rc;
	m_dttmTimeStart.GetWindowRect(rc);
	long lStyle = ::GetWindowLong(m_dttmTimeStart.m_hWnd,GWL_STYLE);
	lStyle |= DTS_UPDOWN;
	m_dttmTimeStart.DestroyWindow();
	ScreenToClient(rc);
	m_dttmTimeStart.Create(lStyle,rc,this,IDC_DATETIMEPICKER3);
	CTime t = CTime::GetCurrentTime(); 
	t -= CTimeSpan(1, 0, 0, 0); // 1 day exactly
	m_dttmStart.SetTime(&t);
	m_dttmTimeStart.SetFormat(_T("HH:mm"));

	m_dttmEndTime.GetWindowRect(rc);
	lStyle = ::GetWindowLong(m_dttmEndTime.m_hWnd,GWL_STYLE);
	lStyle |= DTS_UPDOWN;
	m_dttmEndTime.DestroyWindow();
	ScreenToClient(rc);
	m_dttmEndTime.Create(lStyle,rc,this,IDC_DATETIMEPICKER4);
	m_dttmEndTime.SetFormat(_T("HH:mm"));

	m_lbTotalNum.SetColor(RGB(255,255,255),RGB(0,230,0));
	m_lbTotalNum.SetTxtFont(18,FW_MEDIUM);
	m_lbFautyNum.SetColor(RGB(255,255,255),RGB(220,0,0));
	m_lbFautyNum.SetTxtFont(18,FW_MEDIUM);
	m_lbPercent.SetColor(RGB(255,255,255),RGB(0,0,250));
	m_lbPercent.SetTxtFont(18,FW_MEDIUM);
	return bResult;
}
BEGIN_MESSAGE_MAP(CDlgShowHistoryData, CDialog)
	//{{AFX_MSG_MAP(CDlgShowHistoryData)
	// NOTE: the ClassWizard will add message map macros here
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_QUERY, &CDlgShowHistoryData::OnBnClickedBtnQuery)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgShowHistoryData message handlers

void CDlgShowHistoryData::OnBnClickedBtnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	char sqlbuf[1024];
	CTime timeTime;
	CString strStartTime;
	CString strEndTime;
	DWORD dwResult = m_dttmStart.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{
		// is it a time-only control, or a date-only control?
		if ((m_dttmStart.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
			strStartTime = timeTime.Format(_T("%X"));
		else
			strStartTime = timeTime.Format(_T("%Y-%m-%d"));
	}
	else
	{
		// the user unmarked the "none" box
		AfxMessageBox(_T("Time not set!"));
	}
    dwResult = m_dttmTimeStart.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{
		// is it a time-only control, or a date-only control?
		if ((m_dttmTimeStart.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
			strStartTime += timeTime.Format(_T(" %X"));
		else
			strStartTime += timeTime.Format(_T(" %x"));
	}
	else
	{
		// the user unmarked the "none" box
		AfxMessageBox(_T("Time not set!"));
	}
	dwResult = m_dttmEnd.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{

		// is it a time-only control, or a date-only control?
		if ((m_dttmEnd.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
			strEndTime = timeTime.Format(_T("%X"));
		else
			strEndTime = timeTime.Format(_T("%Y-%m-%d"));
	}
	else
	{
		// the user unmarked the "none" box
		AfxMessageBox(_T("Time not set!"));
	}
	dwResult = m_dttmEndTime.GetTime(timeTime);
	if (dwResult == GDT_VALID)
	{
		// is it a time-only control, or a date-only control?
		if ((m_dttmEndTime.GetStyle() & DTS_TIMEFORMAT) == DTS_TIMEFORMAT)
			strEndTime += timeTime.Format(_T(" %X"));
		else
			strEndTime += timeTime.Format(_T(" %x"));
	}
	else
	{
		// the user unmarked the "none" box
		AfxMessageBox(_T("Time not set!"));
	}
	wstring startdate(strStartTime.GetBuffer());
	wstring enddate(strEndTime.GetBuffer());
	sprintf_s(sqlbuf, "select sum(testcounts) as testcounts,sum(failcounts) as failcounts from events where events.event_start_time between '%s' and '%s'",ws2s(startdate).c_str(),ws2s(enddate).c_str());
	CppSQLite3Query rst = m_db->Query(sqlbuf);
	int totalTestCount = 1;
	int failCounts = 1;
	if (!rst.eof())
	{
		totalTestCount = rst.getIntField("testcounts");
		failCounts = rst.getIntField("failcounts");
	}
	float percent = 0.0;
	if(totalTestCount!=0)
		percent = ((float)failCounts / totalTestCount);
	CString str;
	str.Format(_T("%d"),totalTestCount);
	m_lbTotalNum.SetWindowText(str);
	str.Format(_T("%d"),failCounts);
	m_lbFautyNum.SetWindowText(str);
	str.Format(_T("%0.3f%%"),percent*100);
	m_lbPercent.SetWindowText(str);
	m_lbTotalNum.Invalidate();
	m_lbFautyNum.Invalidate();
	m_lbPercent.Invalidate();

	sprintf_s(sqlbuf, "select tests.testname name,tests.subtestname subname,sum(failcounts) sum from testevents,tests where tests.testid = testevents.testid and  testevents.eventid in (select eventid from events where events.event_start_time between '%s' and '%s') group by testevents.testid",ws2s(startdate).c_str(),ws2s(enddate).c_str());
	rst = m_db->Query(sqlbuf);

	CString strfield;
	m_gridListVw.DeleteAllItems();
	m_gridListVw.PrepareControl(0);
	while (!rst.eof())
	{

		string name = rst.getStringField("name");
		string subname = rst.getStringField("subname");
		int sum = rst.getIntField("sum");

		CString errRate;
		errRate.Format(_T("%0.3f%%"),((float)sum/failCounts*100));
		m_gridListVw.InsertItem(m_gridListVw.GetItemCount(),s2ws(name).c_str(),NULL);	
		m_gridListVw.SetItemText(m_gridListVw.GetItemCount()-1,1,s2ws(subname).c_str());
		CString CSsum;
		CSsum.Format(_T("%d"),sum);
		m_gridListVw.SetItemText(m_gridListVw.GetItemCount()-1,2,CSsum);
		m_gridListVw.SetItemText(m_gridListVw.GetItemCount()-1,3,errRate);
		

		rst.nextRow();

	}
	rst.finalize();
	m_gridListVw.Invalidate();
}
