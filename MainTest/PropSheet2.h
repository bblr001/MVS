#include "UserManagePage.h"
#include "UserAddIn.h"
#include "GroupAddIn.h"
class CModelessSettingPropSheet;
class CModelessSettingPropSheet : public CPropertySheet
{
public:
	DECLARE_DYNAMIC(CModelessSettingPropSheet)
	CModelessSettingPropSheet(CWnd* pWndParent);

// Attributes
	 CUserManagePage m_userManaPage;
	 CUserAddIn      m_userAddIn;
	 CGroupAddIn     m_groupAddIn;

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
