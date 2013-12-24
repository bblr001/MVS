#ifndef _IACTIONOBJ_H__ 
#define _IACTIONOBJ_H__ 


#define   WIN32_LEAN_AND_MEAN  
 
typedef   unsigned   (WINAPI  *PBEGINTHREADEX_THREADFUNC)(  
        LPVOID   lpThreadParameter      );  
typedef   unsigned   *PBEGINTHREADEX_THREADID;  
 
 
class IActiveObj 
{ 
public: 
	IActiveObj(void); 
	virtual ~IActiveObj(void); 
	bool Run(); 
	virtual DWORD Main()=0; 
protected: 
	static   DWORD   WINAPI WorkThread(IActiveObj* lpthis); 
	
	DWORD m_ThreadID; 
	HANDLE m_Handle; 
}; 

#endif