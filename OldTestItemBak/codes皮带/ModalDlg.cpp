// ModalDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "halcon001.h"
#include "ModalDlg.h"


// CModalDlg 对话框

IMPLEMENT_DYNAMIC(CModalDlg, CDialog)

CModalDlg::CModalDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModalDlg::IDD, pParent)
	, sel(0)
{

}

CModalDlg::~CModalDlg()
{
}

void CModalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModalDlg, CDialog)
	ON_BN_CLICKED(IDC_CenterHal, &CModalDlg::OnBnClickedCenterhal)
	ON_BN_CLICKED(IDC_CenterC, &CModalDlg::OnBnClickedCenterc)
END_MESSAGE_MAP()


// CModalDlg 消息处理程序

void CModalDlg::OnBnClickedCenterhal()
{
	// TODO: 在此添加控件通知处理程序代码

   *sel=1;
   CModalDlg::OnOK();
}

void CModalDlg::CenterSelectValue(int* CentSel)
{

  sel =CentSel;
    


}

void CModalDlg::OnBnClickedCenterc()
{
	// TODO: 在此添加控件通知处理程序代码

	 *sel=2;
	 CModalDlg::OnOK();
}
