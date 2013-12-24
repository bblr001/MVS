#pragma once

#include "MData.h"
class IMReport
{
public:
	IMReport(void);
	virtual ~IMReport(void);
protected:
	friend class CMReportCenter;

	virtual void DoReport()=0;
	virtual void ReceiveData(CMData& pData)=0;
};
