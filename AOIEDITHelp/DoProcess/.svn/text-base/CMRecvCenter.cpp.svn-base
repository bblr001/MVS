#include "StdAfx.h"
#include "CMRecvCenter.h"
#include "CMCtrolCenter.h"
#include "CMCfgCenter.h"
void CMRecvCenter::RecvData(CMData* pData)
{
   return m_pCtrlCenter->FilterData(pData);
}
CMRecvCenter::CMRecvCenter():m_Recv(0)
{
   if(0==m_Recv)
	   m_Recv = new CMRecv;
   m_Recv->RegisterCenter(this);
}
CMRecvCenter::~CMRecvCenter()
{
	if(0!=m_Recv)
	   delete m_Recv;
	m_Recv =0;
}