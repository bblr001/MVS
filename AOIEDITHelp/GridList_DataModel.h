#pragma once
#include <vector>
#include <algorithm>
using namespace std;
struct CListCtrl_DataRecord
{
	CListCtrl_DataRecord()
	{}

	CListCtrl_DataRecord(const CString& item, const CString& test, const CString& subtest\
		, const CString& log, const CString& appName
		, const CString& version)
		:m_Item(item),m_Test(test),m_Subtest(subtest),m_Log(log),
		m_ProName(appName),m_ProVersion(version)
	{}
	CString	m_Item;
	CString	m_Test;
	CString	m_Subtest;
	CString	m_Log;
	CString	m_ProName;
	CString	m_ProVersion;
	CString GetCellText(int col, bool title) const
	{
		switch(col)
		{
		case 0: { static const CString title0(_T("Item")); return title ? title0 : m_Item; }
		case 1: { static const CString title1(_T("Test")); return title ? title1 : m_Test; }
		case 2: { static const CString title2(_T("Subtest")); return title ? title2 : m_Subtest; }
		case 3: { static const CString title5(_T("Log")); return title ? title5 : m_Log; }
		case 4: { static const CString title6(_T("ProName")); return title ? title6 : m_ProName; }
		case 5: { static const CString title7(_T("ProVersion")); return title ? title7 : m_ProVersion; }
		default:{ static const CString emptyStr; return emptyStr; }
		}
	}
	int  GetColCount() const { return 6; }
};

class CListItem_DataModel
{
	vector<CListCtrl_DataRecord> m_Records;
	int m_RowMultiplier;

public:
	CListItem_DataModel()
		:m_RowMultiplier(0)
	{
		InitDataModel();
	}

	void InitDataModel()
	{
		if (m_RowMultiplier > 1)
		{
			vector<CListCtrl_DataRecord> rowset(m_Records);
			m_Records.reserve((m_RowMultiplier-1) * rowset.size());
			for(int i = 0 ; i < m_RowMultiplier ; ++i)
			{
				m_Records.insert(m_Records.end(), rowset.begin(), rowset.end());
			}
		}
	}

	CString GetCellText(size_t lookupId, int col) const
	{
		if (lookupId >= m_Records.size())
		{
			static CString oob(_T("Out of Bound"));
			return oob;
		}
		for(size_t rowId = 0; rowId < m_Records.size(); ++rowId)
		{
			if (rowId==lookupId)
				break;
		}
		return m_Records.at(lookupId).GetCellText(col, false);
	}

	vector<CString> GetCountries() const
	{
		vector<CString> countries;
		for(size_t rowId = 0 ; rowId < m_Records.size(); ++rowId)
			countries.push_back( m_Records[rowId].m_Item );
		sort(countries.begin(), countries.end());
		countries.erase(unique(countries.begin(), countries.end()), countries.end());
		return countries;
	}

	size_t GetRowIds() const { return m_Records.size(); }
	int GetColCount() const { return CListCtrl_DataRecord().GetColCount(); }
	CString GetColTitle(int col) const { return CListCtrl_DataRecord().GetCellText(col, true); }

	vector<CListCtrl_DataRecord>& GetRecords() { return m_Records; }
	void SetRowMultiplier(int multiply) { if (m_RowMultiplier != multiply ) { m_RowMultiplier = multiply; InitDataModel(); } }
};