#include "stdafx.h"
#include "DBSQLite.h"
#include "TypeCent.h"
#include "function.h"
CDbsource::CDbsource()
{
	m_db = new CSqliteDB<CppSQLite3Query>;
	TCHAR dbname[] = COMMONDBNAME;
	auto tmp = CFUNC::TransForRootPath(dbname);
	wstring wStr;
	wStr.assign(tmp.begin(), tmp.end());
	string tmps = ws2s(wStr);
	m_db->SetDBName(tmps.c_str());
	m_db->Connect();
}
CDbsource::~CDbsource()
{
	if(m_db != NULL)
	{
		m_db->Close();
		delete m_db;
		m_db = NULL;
	}
}
CDbsource& CDbsource::GetDB()
{
	static CDbsource _db;
	return _db;
}
bool CDbsource::Update(char strQry[])
{
	try
	{
		CppSQLite3Query rst = m_db->Query(strQry);
	}
	catch(...)
	{
		return false;
	}
	return true;
}
list<CString> CDbsource::GetResult(char strQry[],int colnum)
{

	CppSQLite3Query rst = m_db->Query(strQry);
	int i = 0;
	list<CString> lt_result;
	if(colnum > rst.numFields())
		return lt_result;
	while(!rst.eof())
	{
		for(i=0;i<colnum;i++)
		{
			CString _data(rst.getStringField(i));
			lt_result.push_back(_data);
		}
		rst.nextRow();
	}
	i++;
	rst.finalize();
	return lt_result;
}