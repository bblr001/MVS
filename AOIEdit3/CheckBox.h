#pragma once


// CCheckBox

class CCheckBox : public CButton
{
	DECLARE_DYNAMIC(CCheckBox)

public:
	CCheckBox();
	virtual ~CCheckBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnPaint();
};


