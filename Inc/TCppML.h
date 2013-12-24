#pragma once
#include <string>
#include <map>
#include <vector>
using namespace std;
/*
人机可读数据，用于程序内外通信
by lucky
例:
{$FTS_TESTDATA={$type=ALLTESTBEGIN;$data={$time=82382938;$clock=2493478375;};};};

{$FTS_TESTDATA=
	{
	$type=ALLTESTBEGIN;
	$data=
		{$time=82382938;
		$clock=2493478375;};
	};
};
*/
class TCppML
{
public:
	class TCppMLItem;
	typedef map<string,TCppMLItem*> CppMLMap;

	class TCppMLItem
	{
	public:
		TCppMLItem(LPCSTR szSML);
		TCppMLItem();
		~TCppMLItem();

		LPCSTR		GetString() const{return m_sSML.c_str();}
		long		GetLong() const{return atol(m_sSML.c_str());}
		const TCppMLItem*	GetChild(LPCSTR szChild) const;
		bool		HasChild() const{return m_mapItems.empty();}

		const TCppMLItem& operator [] (LPCSTR szChild) const
		{
			const TCppMLItem* pItem=GetChild(szChild);
			return pItem?*pItem:*this;
		}
		operator LPCSTR() const
		{
			return m_sSML.c_str();
		}
		operator long() const
		{
			return atol(m_sSML.c_str());
		}
		//循环遍历
		CppMLMap::const_iterator begin() const{return m_mapItems.begin();}
		CppMLMap::const_iterator end() const{return m_mapItems.end();} 


	protected:
		friend class TCppML;
		bool		Parse(LPCSTR szSML){return SML2Data(szSML);}

	protected:
		bool		SML2Data(LPCSTR szSML);//return the length
	private:
		bool	m_hasChild;
		string	m_sSML;	
		CppMLMap m_mapItems;
	private:
		TCppMLItem(const TCppMLItem&);
		TCppMLItem& operator= (const TCppMLItem&); 
	};
public:
	TCppML(void);
	TCppML(LPCSTR szSML);
	virtual ~TCppML(void);
	static bool	CheckSML(LPCSTR szSML);
	bool		Parse(LPCSTR szSML){return m_cmlItem.Parse(szSML);}
	const TCppMLItem*	GetRoot() const{return &m_cmlItem;}

	const TCppMLItem& operator [] (LPCSTR szChild) const
	{
		const TCppMLItem* pItem=m_cmlItem.GetChild(szChild);
		return pItem?*pItem:m_cmlItem;
	}
private:
	TCppMLItem m_cmlItem;
private:
	TCppML(const TCppML&);
	TCppML& operator= (const TCppML&); 
};

//CppML数组，用于分析多个并列SML字串
class TCppMLArray
{
public:
	TCppMLArray(){};
	~TCppMLArray();
	bool Parse(LPCSTR szSML);
	size_t  Count() const{return m_cmls.size();}
	const TCppML& GetCML(UINT i) const
	{
		if (i>=Count())
		{
			ASSERT(FALSE);
			return m_cmlNull;
		}
		const TCppML* pItem=m_cmls[i];
		return pItem?*pItem:m_cmlNull;
	}
const TCppML& operator [] (UINT i) const{ return GetCML(i);}
protected:
	void Clear();
private:
	int				m_nSMLCount;
	vector<TCppML*>	m_cmls;
	TCppML			m_cmlNull;
private:
	TCppMLArray(const TCppML&);
	TCppMLArray& operator= (const TCppML&); 
};