class CModelessSettingPropSheet;
class CSettingPropSheetFrame : public CMiniFrameWnd
{
// Constructor
public:
	CSettingPropSheetFrame();

// Attributes
	CModelessSettingPropSheet* m_pModelessSettingPropSheet;
public:
// Handlers
protected:
	//{{AFX_MSG(CShapePropSheetFrame)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};