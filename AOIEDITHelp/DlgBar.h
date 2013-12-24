#pragma once

// CDlgBar
#include <string>
class CDlgBar : public CDialogBar
{
	DECLARE_DYNAMIC(CDlgBar)

public:
	CDlgBar();
	virtual ~CDlgBar();
	void SetBarTitle(std::wstring title);
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT CHGTitle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
    CStatic  m_staTextInfo;
};


