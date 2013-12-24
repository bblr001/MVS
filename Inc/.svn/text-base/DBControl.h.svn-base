#pragma once
#include <iostream>
#include <string>
#include "CppSQLite3.h"

using namespace std;

enum DATABASETYPE
{
	MSSQL = 1,
	SQLITE,
	MYSQL,
	SYSBASE,
	ORACLE
};

template <typename _QueryType>
class CDBControl
{
public:
	CDBControl(void);
	virtual ~CDBControl(void);
protected:
	std::string m_strDbName;
	std::string m_strSvrName;
	std::string m_strUserName;
	std::string m_strPwd;
	std::string m_strConnectString;
	//char*	m_dbName;		// database name with contain absolute path
	//char*	m_serverName;	//database server name;
	//char*	m_userName;		//username of the database server
	//char*	m_pwd;			//password of the username
	//char*	m_dbConnectString;
	bool	m_isSecureConnect;	//secure connect to this database system
	DATABASETYPE	m_dbType;		// database type, it's enumerable, eg:sqlite, mssql, oracle, sysbase..


public:
	virtual bool Connect(void) = 0;
	virtual bool Connect(char* dbName) = 0;
	virtual bool Connect(char* dbConnectString, DATABASETYPE dbType) = 0;
	virtual bool Connect(DATABASETYPE dbType, char* serverName, char* dbName, char* userName, char* pwd, bool isSecure) = 0;
	virtual bool CreateTable(const char* tbname, const char* fieldstr) = 0;
	virtual bool CreateTable(const char* sqlstr) = 0;
	virtual int Excute(const char* sqlstr) = 0;
	virtual _QueryType Query(const char* sqlstr) = 0;
	virtual __int64 GetLastRowID() = 0;
	virtual bool Close(void);

	void SetDBName(const char* dbName);
	void SetServerName(const char* serverName);
	void SetUserName(const char* userName);
	void SetPassword(const char* password);
	void SetSecureConnect(bool isSecure);
	void SetConnectString(const char* connectString);
	void SetType(DATABASETYPE type);

	bool IsSecureConnect(){return m_isSecureConnect;};
	virtual bool TableExists(const char* tbname){return true;};
	const char* GetDBName() const{return m_strDbName.c_str();};
	const char* GetServerName() const{return m_strSvrName.c_str();};
	const char* GetUserName() const{return m_strUserName.c_str();};
	const char* GetConnectString() const{return m_strConnectString.c_str();};
	DATABASETYPE GetType(){return m_dbType;};
protected:
	virtual bool Open(void) = 0;
	virtual bool Open(char* dbname) = 0;
};


template <typename _QueryType>
CDBControl<_QueryType>::CDBControl(void)
: m_dbType(SQLITE)
{
}

template <typename _QueryType>
CDBControl<_QueryType>::~CDBControl(void)
{
}

template <typename _QueryType>
void CDBControl<_QueryType>::SetDBName(const char* dbName)
{
	m_strDbName.clear();
	m_strDbName = dbName;
}

template <typename _QueryType>
void CDBControl<_QueryType>::SetServerName(const char* serverName)
{
	m_strSvrName.clear();
	m_strSvrName = serverName
}

template <typename _QueryType>
void CDBControl<_QueryType>::SetUserName(const char* userName)
{
	m_strUserName.clear();
	m_strUserName = userName;
}

template <typename _QueryType>
void CDBControl<_QueryType>::SetPassword(const char* password)
{
	m_strPwd.clear();
	m_strPwd = password;
}

template <typename _QueryType>
void CDBControl<_QueryType>::SetSecureConnect(bool isSecure)
{
	m_isSecureConnect = isSecure;
}

template <typename _QueryType>
void CDBControl<_QueryType>::SetConnectString(const char* connectString)
{
	m_strConnectString.clear();
	m_strConnectString = connecString;
}

template <typename _QueryType>
void CDBControl<_QueryType>::SetType(DATABASETYPE	type)
{
	m_dbType = type;
}

template <typename _QueryType>
bool CDBControl<_QueryType>::Close()
{
	return true;
}


