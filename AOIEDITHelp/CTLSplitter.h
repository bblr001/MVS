class CExSplitWnd : public CSplitterWnd
{
	DECLARE_DYNAMIC(CExSplitWnd)

	// Implementation
public:
	 CExSplitWnd();
	~CExSplitWnd();
	CWnd* GetActivePane(int* pRow = NULL, int* pCol = NULL);
	// Generated message map functions
	//{{AFX_MSG(CExSplitWnd)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};