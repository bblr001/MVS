//DBSQLite.h
#include "SqliteDB.h"
#include "DBControl.h"
#include "CppSQLite3.h"
#include "string"
class CDbsource
{
public:
	CDbsource();
	~CDbsource();
protected:
	CDBControl<CppSQLite3Query>* m_db;
public:
	static CDbsource& GetDB();
	list<CString> GetResult(char[],int);
	bool Update(char[]);
private:
	CppSQLite3Query rst;
};