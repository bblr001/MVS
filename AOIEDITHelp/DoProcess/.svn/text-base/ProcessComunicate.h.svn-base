#pragma once
#include "IMActiveObj.h"
#include "../../inc/ShareMem.h"
#include "..\..\inc\TCppML.h"
using namespace std;
class CMCmd: public IActiveObj 
{
public:
	 CMCmd();
	~CMCmd();	
	void Close();
protected:
	DWORD Main();
private:	
	IPC_CMD_BUS_DEPRECATED* m_pUiCmdProxy;	
	bool m_isExit;
};
