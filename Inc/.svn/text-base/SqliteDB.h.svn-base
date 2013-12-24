#pragma once
#include "dbcontrol.h"
#include "CppSQLite3.h"
#include <exception>
#include "Tools.h"
//#include "ErrorProcess.h"
#include <windows.h>
#include <stdio.h>
#include "TypeCent.h"

#define SQL_LEN 1024

using namespace std;
enum ShareMode{
						SHARE_NO,			//don't share
						SHARE_READ,		//read share
						SHARE_WRITE		//write share
						};

template <typename _QueryType>
class CSqliteDB :
	public CDBControl<_QueryType>
{
public:
	CSqliteDB(ShareMode mode = SHARE_READ);
	virtual ~CSqliteDB(void);

	bool Connect(void);
	bool Connect(char* dbName);
	bool Connect(char* dbConnectString, DATABASETYPE dbType);
	bool Connect(DATABASETYPE dbType, char* serverName, char* dbName, char* userName, char* pwd, bool isSecure);
	bool CreateTable(const char* tbname, const char* fieldstr);
	bool CreateTable(const char* sqlstr);
	int Excute(const char* sqlstr);
	_QueryType Query(const char* sqlstr);
	bool Close(void);
	__int64 GetLastRowID();
	bool TableExists(const char* tbname){return m_db.tableExists(tbname);};


protected:
	bool Open(void);
	bool Open(char* dbname);

	//lock share file
	bool Lock();
	void Unlock();

private:
	CppSQLite3DB m_db;
	ShareMode		m_share;
	HANDLE m_hfile;
};

template <typename _QueryType>
CSqliteDB<_QueryType>::CSqliteDB(ShareMode mode)
{
	m_dbType = SQLITE;
	m_hfile = NULL;
	m_share = mode;
}

template <typename _QueryType>
CSqliteDB<_QueryType>::~CSqliteDB(void)
{
	m_db.close();
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::Open(void)
{
	//lock share file
// 	if (m_hfile != NULL && INVALID_HANDLE_VALUE != m_hfile)
// 	{
// 		CloseHandle(m_hfile);
// 		m_hfile = NULL;
// 	}
// 
// 	string tmpfile = m_dbName;
// 	tmpfile += ".share";
// 	wstring tmpfile_w=s2ws(tmpfile);
// 	while(NULL == m_hfile || INVALID_HANDLE_VALUE == m_hfile)
// 	{
// 		m_hfile = CreateFile(tmpfile_w.c_str(), 
// 										GENERIC_READ|GENERIC_WRITE, 
// 										m_share, 
// 										NULL, 
// 										OPEN_ALWAYS,
// 										FILE_ATTRIBUTE_NORMAL,
// 										NULL);
// 		DWORD errCode = GetLastError();
// 		switch(errCode)
// 		{
// 		case ERROR_ALREADY_EXISTS:
// 			break;
// 		case ERROR_ACCESS_DENIED:
// 			break;
// 		// The process cannot access the file because it is being used by another process.
// 		case ERROR_SHARING_VIOLATION:
// 			break;
// 		// The process cannot access the file because another process has locked a portion of the file.
// 		case ERROR_LOCK_VIOLATION:
// 			break;
// 		// The network path was not found.
// 		case ERROR_BAD_NETPATH:
// 			return false;
// 			break;
// 		default:
// 			break;
// 		}
// 		//sleep one second then retry
// 		Sleep(100);
// 	}

	//open database
	try
	{
		m_db.open(m_strDbName.c_str());
	}
	catch (std::exception* e)
	{
		TCHAR msg[MSG_LEN], file[FILE_LEN], func[FUNC_LEN] ;
		_stprintf_s(msg, MSG_LEN, _T("%s"), e->what());
		_stprintf_s(file, FILE_LEN, _T("%s"), __FILE__);
		_stprintf_s(func, FUNC_LEN, _T("%s"), __FUNCTION__);

		//CErrorProcess::GetInstance().WriteLogMsg(msg, file, func, __LINE__);		
		return false;
	}
	return true;
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::Open(char* dbname)
{              
	SetDBName(dbname);
	return Open();
}

template <typename _QueryType>
__int64 CSqliteDB<_QueryType>::GetLastRowID()
{
	return m_db.lastRowId();
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::Connect(void)
{
	return Open();
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::Connect(char* dbName)
{
	return Open(dbName);
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::Connect(char* dbConnectString, DATABASETYPE dbType)
{
	m_dbType = dbType;
	return Open();
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::Connect(DATABASETYPE dbType, char* serverName, char* dbName, char* userName, char* pwd, bool isSecure)
{
	m_dbType = dbType;
	return Open(dbName);
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::CreateTable(const char *tbname, const char *fieldstr)
{
	bool exists = m_db.tableExists(tbname);
	if (!exists)
	{
		char sqlstr[SQL_LEN];
		sprintf_s(sqlstr, SQL_LEN, "Create Table %s(%s);", tbname, fieldstr);
		try
		{
			m_db.execDML(sqlstr);
		}
		catch (CppSQLite3Exception* e)
		{
			TCHAR msg[MSG_LEN], file[FILE_LEN], func[FUNC_LEN] ;
			_stprintf_s(msg, MSG_LEN, _T("%s"), e->errorMessage());
			_stprintf_s(file, FILE_LEN, _T("%s"), __FILE__);
			_stprintf_s(func, FUNC_LEN, _T("%s"), __FUNCTION__);
			//CErrorProcess::GetInstance().WriteLogMsg(msg, file, func, __LINE__);		
		}
	}

	return true;
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::CreateTable(const char *sqlstr)
{
	//execDML return affect numbers
	try
	{
		m_db.execDML(sqlstr);
	}
	catch (CppSQLite3Exception* e)
	{
		TCHAR msg[MSG_LEN], file[FILE_LEN], func[FUNC_LEN] ;
		_stprintf_s(msg, MSG_LEN, _T("%s"), e->errorMessage());
		_stprintf_s(file, FILE_LEN, _T("%s"), __FILE__);
		_stprintf_s(func, FUNC_LEN, _T("%s"), __FUNCTION__);
		//CErrorProcess::GetInstance().WriteLogMsg(msg, file, func, __LINE__);		
	}
	return true;
}

template <typename _QueryType>
int CSqliteDB<_QueryType>::Excute(const char* sqlstr)
{
	int ret = 0;
	try
	{
		ret = m_db.execDML(sqlstr);
	}
	catch (CppSQLite3Exception* e)
	{
		TCHAR msg[MSG_LEN], file[FILE_LEN], func[FUNC_LEN] ;
		_stprintf_s(msg, MSG_LEN, _T("%s"), e->errorMessage());
		_stprintf_s(file, FILE_LEN, _T("%s"), __FILE__);
		_stprintf_s(func, FUNC_LEN, _T("%s"), __FUNCTION__);
		//CErrorProcess::GetInstance().WriteLogMsg(msg, file, func, __LINE__);		
	}
	return ret;
}

template <typename _QueryType>
_QueryType CSqliteDB<_QueryType>::Query(const char* sqlstr)
{
	_QueryType result;

	try
	{
		result = m_db.execQuery(sqlstr);
	}
	catch (CppSQLite3Exception* e)
	{
		TCHAR msg[MSG_LEN], file[FILE_LEN], func[FUNC_LEN] ;
		_stprintf_s(msg, MSG_LEN, _T("%s"), e->errorMessage());
		_stprintf_s(file, FILE_LEN, _T("%s"), __FILE__);
		_stprintf_s(func, FUNC_LEN, _T("%s"), __FUNCTION__);
		//CErrorProcess::GetInstance().WriteLogMsg(msg, file, func, __LINE__);		
	}

	return result;
}

template <typename _QueryType>
bool CSqliteDB<_QueryType>::Close(void)
{
	if (m_hfile != NULL && INVALID_HANDLE_VALUE != m_hfile)
	{
		CloseHandle(m_hfile);
		m_hfile = NULL;
	}

	m_db.close();
	return true;
}