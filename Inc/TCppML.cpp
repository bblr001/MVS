#include "StdAfx.h"
#include "TCppML.h"
#include "TLog.h"
#include <set>
#include <memory>

#ifdef _DEBUG
   #ifndef DBG_NEW
      #define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
      #define new DBG_NEW
   #endif
#endif  // _DEBUG

using namespace std;

TCppML::TCppML(void)
{
}

TCppML::TCppML( LPCSTR szSML )
{
	m_cmlItem.Parse(szSML);
}
TCppML::~TCppML(void)
{
}

bool TCppML::CheckSML( LPCSTR szSML )
{
	int nCount=0;
	while (*szSML)
	{
		if (*szSML=='{')
		{
			nCount++;
		}
		else if (*szSML=='}')
		{
			nCount--;
		}
		szSML++;
	}
	return nCount==0;
}
//////////////////////////////////////////////////////////////////////////
///Item
//////////////////////////////////////////////////////////////////////////
TCppML::TCppMLItem::TCppMLItem( LPCSTR szSML )
{	
	SML2Data(szSML);
}

TCppML::TCppMLItem::TCppMLItem()
{	
}
TCppML::TCppMLItem::~TCppMLItem()
{
	CppMLMap::const_iterator map_it=m_mapItems.begin();
	while (map_it!=m_mapItems.end())
	{
        //TLOG_DEBUG(_T("delete map_it->second %s"),map_it->second->GetString());  
        delete map_it->second;
		++map_it;
	}
	m_mapItems.clear();
}
bool TCppML::TCppMLItem::SML2Data( LPCSTR szSML )
{
	LPCSTR szPos=szSML;
	LPCSTR szKey=NULL,szValue=NULL;

	m_sSML=szSML;

	TCppMLItem* pItem=NULL;
	int nCountA=0;

	char cLast=0;//上一个关键字
	char cLastNc=0;//上一个非空字符

	while (*szPos)
	{
		switch(*szPos)
		{
		case '{':
			if (cLast==0 || cLastNc=='=')
			{
				cLast='{';
				nCountA++;
			}
			break;
		case '}':
			if (cLastNc==';')
			{
				cLast='}';

				nCountA--;
				if (nCountA==0)
					goto SMLEND;
			}
			break;
		case '$':				
			if (nCountA==1 && (cLastNc=='{' || cLastNc==';'))
			{
				cLast='$';
				szKey=szPos+1;
			}			
			break;
		case '=':
			if (nCountA==1 && cLast=='$')
			{	
				cLast='=';
				ASSERT(szKey);
				pItem = new TCppMLItem();
				string sKey(szKey,szPos-szKey);
				/*由於使用map，沒有重複鍵，所以當多次new對象時，在析構中有內存洩漏*/
				m_mapItems.insert(make_pair(sKey,pItem));
				szKey=NULL;

				szValue=szPos+1;
			}			
			break;
		case ';':
			if (nCountA==1 && (cLast=='=' || cLastNc=='}'))
			{
				cLast=';';
				ASSERT(szValue);
				ASSERT(pItem);
				string sValue(szValue,szPos-szValue);
				pItem->Parse(sValue.c_str());

				pItem=NULL;
				szValue=NULL;
			}
			break;
		default:
			
			break;
		}
		if (isgraph((unsigned char)(*szPos)))
		{
			cLastNc=*szPos;
		}

		szPos++;
	}
SMLEND:
	if (nCountA!=0 || szKey!=NULL || szValue!=NULL || pItem!=NULL)
	{
		return false;
	}
	return true;
}

const TCppML::TCppMLItem* TCppML::TCppMLItem::GetChild( LPCSTR szChild ) const
{
	TCppMLItem* pCMLItem=NULL;
	CppMLMap::const_iterator it=m_mapItems.find(szChild);
	if (it!=m_mapItems.end())
	{
		pCMLItem=it->second;
	}
//	ASSERT(pCMLItem);
	return pCMLItem;	
}

///////////////////////////////////////
//////////////////////////////////////////

bool TCppMLArray::Parse( LPCSTR szSML )
{		
	Clear();
	int nCount=0;
	while (*szSML)
	{
		if (*szSML=='{')
		{
			if (nCount==0)
			{
				std::shared_ptr<TCppML> pcml(new TCppML());
				if(pcml->Parse(szSML))
				{
					m_cmls.push_back(pcml.get());
				}
				else
				{
                    TLOG_DEBUG(_T("delete pcml;"));
					return false;
				}
				
			}
			nCount++;
		}
		else if (*szSML=='}')
		{
			nCount--;		
		}
		szSML++;
	}
	return nCount==0;
}
void TCppMLArray::Clear()
{
	m_cmls.clear();
}
TCppMLArray::~TCppMLArray()
{
	Clear();
}