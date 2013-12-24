#include "stdafx.h"
#include "DBSQLite.h"
#include "TypeCent.h"
#include "function.h"
CDbsource::CDbsource()
{
    m_db = new CSqliteDB<CppSQLite3Query>;
	TCHAR dbname[] = COMMONDBNAME;
	wstring tmp = CFUNC::TransForRootPath(dbname);
	string tmps=ws2s(tmp);
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
list<CString>* CDbsource::GerResult(char strQry[],int colnum)
{
   CppSQLite3Query rst = m_db->Query(strQry);
   int i = 0;
   list<CString>* lt_result = new list<CString>();
   if(colnum > rst.numFields())return NULL;
   while(!rst.eof())
   {
	   for(i=0;i<colnum;i++)
	   {
		   CString _data(rst.getStringField(i));
		   lt_result->push_back(_data);
	   }
	   rst.nextRow();
   }
   i++;
   rst.finalize();
   return lt_result;
}