//#include "UserManagePage.h"
#include "UserManager.h"
class CModelessSettingPropSheet;
class CModelessSettingPropSheet : public CPropertySheet
{
public:
	DECLARE_DYNAMIC(CModelessSettingPropSheet)
	CModelessSettingPropSheet(CWnd* pWndParent);

	// Attributes
	//CUserManagePage m_userManaPage;
	CUserManager      m_userManager;
	// CGroupAddIn     m_groupAddIn;

	// Operations
	void SetSheetPropsFromShape(int* pShape);
	void SetShapePropsFromSheet(int* pShape);

	// Overrides
	virtual void PostNcDestroy();

	// Message Handlers
protected:
	//{{AFX_MSG(CModelessSettingPropSheet)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
