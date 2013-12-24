#pragma once
#include "dbcontrol.h"

template<typename _QueryType>
class CSqlDB :
	public CDBControl<_QueryType>
{
public:
	CSqlDB(void);
	~CSqlDB(void);
};
