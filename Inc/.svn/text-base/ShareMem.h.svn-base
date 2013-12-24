#pragma once

#include <string>
#include "TLog.h"
#include "TypeCent.h"
#include "cpp/HalconCpp.h"

using namespace std;
using namespace Halcon;

const size_t CMDDATASIZE = 128;
const size_t ZOOM_IMAGE_W = 234;
const size_t ZOOM_IMAGE_H = 174;

// Internal Process Communication Code
// Notice : DO NOT change these IPC code! You can add some new ones.
const int RUNNING			= 1;
const int PAUSED			= 2;
const int STOPPED			= 3;
const int DISMISS_WARNING	= 4;
const int USER_OPERATOR		= 5;
const int USER_ENGINEER		= 6;
const int USER_ADMIN		= 7;
const int USER_SLAC_ADMIN	= 8;
const int IDLE				= 9;
const int INIT              = 10;
const int TURN_ON_RED_LIGHT = 11;
const int UPDATE_SETTINGS   = 12;
const int UPDATE_TLS_FILE   = 13;

template<class T = char,unsigned int SIZE = 128>
class CBaseShareMem
{
public:
	CBaseShareMem()
	{
	}
	CBaseShareMem(LPCWSTR szName)
	{
		m_strName = szName;
		m_hMem = ::CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(T)* SIZE,szName);
		if (GetLastError() == ERROR_ALREADY_EXISTS) 
		{
			m_hMem = ::OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,szName);
		} 
		if (m_hMem == NULL)
		{
			TLOG_ERROR(_T("CreateFileMapping Failed!"));
		}
		m_pBuff = (T*)::MapViewOfFile(m_hMem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(T) * SIZE);
		//事件与互斥对象
		wstring tmpStr = szName;

		m_hMutex=::CreateMutex(NULL,FALSE,(tmpStr + _T("-Mutex")).c_str());
		if (m_hMutex == NULL)
		{
			TLOG_ERROR(_T("CreateMutex %s Failed"),szName);
		}
		m_hReadEvent=::CreateEvent(NULL,TRUE,FALSE,(tmpStr + _T("-ReadEvent")).c_str());
		if (m_hReadEvent == NULL)
		{
			TLOG_ERROR(_T("Create Read Event %s Failed"),szName);
		}
		m_hWriteEvent = ::CreateEvent(NULL,TRUE, TRUE, (tmpStr + _T("-WriteEvent")).c_str()); 
		if(m_hWriteEvent == NULL)
		{
			TLOG_ERROR(_T("Create Write Event %s Failed"),szName);
		}
	}
	virtual ~CBaseShareMem()
	{
		ResetShareMemory();
	}
	void Init(LPCWSTR szName)
	{
		m_strName = szName;
		m_hMem = ::CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,sizeof(T)* SIZE,szName);
		if (GetLastError() == ERROR_ALREADY_EXISTS) 
		{
			m_hMem = ::OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,szName);
		} 
		if (m_hMem == NULL)
		{
			TLOG_ERROR(_T("CreateFileMapping Failed!"));
		}
		m_pBuff = (T*)::MapViewOfFile(m_hMem, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(T) * SIZE);
		//事件与互斥对象
		wstring tmpStr = szName;

		m_hMutex=::CreateMutex(NULL,FALSE,(tmpStr + _T("-Mutex")).c_str());
		if (m_hMutex == NULL)
		{
			TLOG_ERROR(_T("CreateMutex %s Failed"),szName);
		}
		m_hReadEvent=::CreateEvent(NULL,TRUE,FALSE,(tmpStr + _T("-ReadEvent")).c_str());
		if (m_hReadEvent == NULL)
		{
			TLOG_ERROR(_T("Create Read Event %s Failed"),szName);
		}
		m_hWriteEvent = ::CreateEvent(NULL,TRUE, TRUE, (tmpStr + _T("-WriteEvent")).c_str()); 
		if(m_hWriteEvent == NULL)
		{
			TLOG_ERROR(_T("Create Write Event %s Failed"),szName);
		}
	}
	void ResetShareMemory()
	{
		SetEvent(m_hWriteEvent);
		ResetEvent(m_hReadEvent);

		if(m_hMem != NULL)
		{
			::CloseHandle(m_hMem);
			m_hMem = NULL;
		}
		if(m_pBuff != NULL)
		{
			::UnmapViewOfFile(m_pBuff);
			m_pBuff = NULL;
		}
		if(m_hMutex != NULL)
		{
			::CloseHandle(m_hMutex);
			m_hMutex = NULL;
		}

		if(m_hReadEvent != NULL)
		{
			::CloseHandle(m_hReadEvent);	
			m_hReadEvent = NULL;
		}
		if(m_hWriteEvent != NULL)
		{
			::CloseHandle(m_hWriteEvent);
			m_hWriteEvent = NULL;
		}
	}
	void Lock()
	{
		::WaitForSingleObject(m_hMutex, INFINITE);
	}
	void Unlock()
	{
		::ReleaseMutex(m_hMutex);
	}
protected:
	T*      m_pBuff;
	HANDLE	m_hMem;
	HANDLE	m_hMutex;
	HANDLE	m_hReadEvent;
	HANDLE  m_hWriteEvent;

	wstring m_strName;
};

template<class T = char, unsigned int SIZE = 128>
class IPC_CmdBus : public CBaseShareMem<T,SIZE>
{
public:
	IPC_CmdBus()
	{
	}
	IPC_CmdBus(LPCWSTR szName):CBaseShareMem<T,SIZE>(szName)
	{
		::memset((void*)m_chCmd, 0x00, sizeof(T) * SIZE);
	}
	~IPC_CmdBus(void)
	{
	}

	bool Read(T* pDstCmdStr,  size_t sz)
	{
		if (m_pBuff == nullptr || pDstCmdStr == nullptr)
			return false;
		if(sz <= 0)
			return false;
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hReadEvent, 2))
			return false;

		Lock();
		memcpy_s((void*)pDstCmdStr, sz, m_pBuff, SIZE);
		pDstCmdStr[sz-1] = 0;
		ResetEvent(m_hReadEvent);
		SetEvent(m_hWriteEvent); // enable writing 
		Unlock();

		return true;
	}
	bool Write(T* pSrcCmdStr, size_t sz)
	{
		if (m_pBuff == nullptr || pSrcCmdStr == nullptr)
			return false;
		if(sz <= 0)
			return false;
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hWriteEvent, 2))
			return false;

		Lock();
		memcpy_s((void*)m_pBuff, SIZE, pSrcCmdStr, sz);
		m_pBuff[SIZE-1] = 0;
		ResetEvent(m_hWriteEvent); // disable writing
		SetEvent(m_hReadEvent);    // enable reading
		Unlock();
		return true;
	}
private:
	T     m_chCmd[SIZE];
};

template<class T = char, unsigned int SIZE = 40716>
class IPC_ImageBus : public CBaseShareMem<T,SIZE>
{
public:
	IPC_ImageBus()
	{
	}
	IPC_ImageBus(LPCWSTR szName):CBaseShareMem<T,SIZE>(szName)
	{
		::memset((void*)m_chImage, 0x00, sizeof(T) * SIZE);
	}
	~IPC_ImageBus(void)
	{
	}

	bool Read(Hobject* pDstImg)
	{
		if (m_pBuff == nullptr || pDstImg == nullptr)
			return false;

		if (WAIT_TIMEOUT == WaitForSingleObject(m_hReadEvent, 10))
			return false;

		Lock();
		gen_image1(pDstImg,"byte", ZOOM_IMAGE_W, ZOOM_IMAGE_H, (long)m_pBuff);
		ResetEvent(m_hReadEvent); // Disable reading image now
		SetEvent(m_hWriteEvent); //  Enable writing image
		Unlock();

		return true;
	}
	bool Write(Hobject* pSrcImg)
	{
		if (m_pBuff == nullptr || pSrcImg == nullptr)
			return false;

		if (WAIT_TIMEOUT == WaitForSingleObject(m_hWriteEvent, 10))
			return false;

		Lock();
		Hlong    width ;       // Width of the image
		Hlong    height;      // Height of the image
		char  chType[128];
		unsigned char  *ptr;
		Hobject zoomImg;
		zoom_image_size(*pSrcImg, &zoomImg, ZOOM_IMAGE_W, ZOOM_IMAGE_H, "nearest_neighbor");	
		get_image_pointer1(zoomImg, (long*)&ptr, chType, &width, &height);
		image_to_channels(zoomImg, &zoomImg);

		size_t imgeSize = width * height;
		::memset((void*)m_pBuff, 0x00, sizeof(T) * SIZE);
		memcpy_s((void*)m_pBuff, SIZE, (void*)ptr, imgeSize); 
		m_pBuff[imgeSize] = 0;
		ResetEvent(m_hWriteEvent); // Disable writing image
		SetEvent(m_hReadEvent);   // Enable reading
		Unlock();

		return true;
	}

private:
	T    m_chImage[SIZE];
};

const wstring RSLT_FLAG_BUFFER_NAME = L"RSLT_FLAG_BUFFER_NAME";
const wstring SEND_IMG_CMD_BUFFER_NAME = L"SEND_IMG_CMD_BUFFER_NAME"; 

template<class T = char, unsigned int SIZE = 256> // 
class CInfoTransfer : public CBaseShareMem<T,SIZE>
{
public:
	CInfoTransfer()
	{
	}
	CInfoTransfer(LPCWSTR szName):CBaseShareMem<T,SIZE>(szName)
	{
		::memset((void*)m_infoBuffer, 0x00, sizeof(T) * SIZE);
	}
	~CInfoTransfer()
	{
	}
	void EnableWriteBuff()
	{
		Lock();
		::memset((void*)m_pBuff, 0x00, SIZE);
		SetEvent(m_hWriteEvent); // Enable writing
		ResetEvent(m_hReadEvent); // Disable reading
		Unlock();
	}
	void DisableWriteBuff()
	{
		Lock();
		::memset((void*)m_pBuff, 0x00, SIZE);
		SetEvent(m_hReadEvent); // Enable writing
		ResetEvent(m_hWriteEvent); // Disable reading
		Unlock();
	}
	bool Read(size_t typeSz, T* pDst, size_t szDst)
	{
		if (m_pBuff == nullptr || pDst == nullptr)
			return false;
		if(szDst <= 0)
			return false;
		// wait for read permission
		if (WAIT_TIMEOUT == ::WaitForSingleObject(m_hReadEvent, 5))
		{
			return false;
		}
		Lock();
		::memcpy_s((void*)pDst, typeSz*szDst, (void*)m_pBuff, SIZE*typeSz);
		ResetEvent(m_hReadEvent); // Disable reading
		SetEvent(m_hWriteEvent); // Enable writing
		Unlock();
		return true;
	}
	bool Write(size_t typeSz,const T* pSrc, size_t sz)
	{
		if (m_pBuff == nullptr /*|| pSrc == nullptr*/)
			return false;
		if(sz <= 0) 
			return false;
		if(sz > SIZE)
			sz = SIZE;
		// poll writing permission 
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hWriteEvent, 5))
			return false;

		Lock();
		::memset((void*)m_pBuff, 0x00, typeSz*sz);
		::memcpy_s((void*)m_pBuff, sz*typeSz, (void*)pSrc, sz*sizeof(T));
		m_pBuff[sz] = T(0);
		ResetEvent(m_hWriteEvent); // disable writing now
		SetEvent(m_hReadEvent);    // enable reading now
		Unlock();

		return true;
	}

	// Use this method to transfer image and its width and height information
	bool Write(const T* pSrc, size_t width, size_t height)
	{
		if (m_pBuff == nullptr || pSrc == nullptr)
			return false;
		size_t sz = width * height;
		if(sz <= 0) 
			return false;
		// poll writing permission 
		if (WAIT_TIMEOUT == WaitForSingleObject(m_hWriteEvent, 10))
			return false;

		Lock();
		::memset((void*)m_pBuff, 0x00, sizeof(T)*9);
		// package the size  information of the image
		size_t index = 0;
		while(width != 0)
		{
			m_pBuff[index++] = (T) (width%10);
			width /= 10;
		}
		m_pBuff[index++] = (T)'x';

		while(height != 0)
		{
			m_pBuff[index++] = (T)(height%10);
			height /= 10;
		}
		size_t totalSize = sz + index;
		T* pImgBgn = m_pBuff + index;
		::memset((void*)pImgBgn, 0x00, sizeof(T)*(SIZE - index));
		::memcpy_s((void*)pImgBgn, sizeof(T)*sz, (void*)pSrc, sizeof(T)*sz);
		if(m_pBuff == nullptr)
		{
			TLOG_ERROR(_T("m_pBuff is nullptr !Failed"));
		}
		m_pBuff[totalSize] = 0;

		ResetEvent(m_hWriteEvent); // disable writing now
		SetEvent(m_hReadEvent);    // enable reading now
		Unlock();

		return true;
	}
private:
	T  m_infoBuffer[SIZE];
};


//typedef IPC_CmdBus<char, CMDDATASIZE> IPC_REPORT_BUS;
// Report format: 
// char report[4];
//      report[0]  -- channel status;
//      report[1]  -- red light port number
//      report[2]  -- green light port number
//      report[3]  -- 0
typedef CInfoTransfer<char, 32> IPC_REPORT_BUS;
typedef CInfoTransfer<char, 2> IPC_CMD_BUS;
typedef IPC_CmdBus<char, CMDDATASIZE> IPC_CMD_BUS_DEPRECATED;
typedef IPC_ImageBus<unsigned char, 40716> IPC_IMAGE_BUS;

const long DEFAULT_SIZE = 115216;
typedef CInfoTransfer<unsigned char, DEFAULT_SIZE> CHANNEL_RESULT_BUFFER;

const int DEFAULT_ERROR_RGN_COUNTER = 64;
typedef CInfoTransfer<ERROR_RGN_INFO, DEFAULT_ERROR_RGN_COUNTER> ERROR_RGN_INFO_BUFFER;

typedef CInfoTransfer<char, 2> FLAG_BUFFER;
typedef CInfoTransfer<char, 6> PORT_NUM_BUFFER;
