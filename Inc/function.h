#pragma once
#include <tchar.h>
#include <time.h>
#include <vector>

using namespace std;

#define MAXPATH	512

class CFUNC
{
public:
	//format current time to string(y-m-d h:M:S);
	//return TCHAR*;
	//should call CFUNC::FreeFromatStr(TCHAR* datatime) relase
	static std::vector<TCHAR> FormatCurTimeStr()
	{
		time_t curtime = time(NULL);
		return CFUNC::FormatTimeStr(curtime);
	}

	//format timer to string(y-m-d h:M:S);
	//return TCHAR*;
	//should call CFUNC::FreeFromatStr(TCHAR* datatime) relase
	static std::vector<TCHAR> FormatTimeStr(const time_t& timer)
	{
		short tlen = 20;
		time_t curtime = timer;
		struct tm stm;
		localtime_s(&stm, &curtime);
		std::vector<TCHAR> datetime(tlen, 0 );
		_tcsftime(&datetime[0], tlen, _T("%Y-%m-%d %H:%M:%S"), &stm);

		return datetime;
	}

	//format current time to string(y-m-d);
	//return TCHAR*;
	//should call CFUNC::FreeFromatStr(TCHAR* datatime) relase
	static std::vector<TCHAR> FormatCurDateStr()
	{
		time_t curtime = time(NULL);
		return FormatDateStr(curtime);
	}

	//format timer to string(y-m-d);
	//return TCHAR*;
	//should call CFUNC::FreeFromatStr(TCHAR* datatime) relase
	static std::vector<TCHAR> FormatDateStr(const time_t& timer)
	{
		short tlen = 20;
		time_t curtime = timer;
		struct tm stm;
		localtime_s(&stm, &curtime);
		std::vector<TCHAR> datetime(tlen, 0);
		_tcsftime(&datetime[0], tlen, _T("%Y-%m-%d"), &stm);

		return datetime;
	}

	/************************************************************************/
	// check this path is root path, eg:c:\abc and \\dev\c$\abc both root path
	/************************************************************************/
	static bool IsRootPath(const TCHAR* path)
	{
		if (_tcslen(path)<3)
		{
			return false;
		}
		if ((path[0] == _T('\\') && path[1] == _T('\\')) || (path[1] == _T(':') && path[2] == _T('\\')))
		{
			return true;
		}
		return false;
	}

	/************************************************************************/
	// return physical path								                    
	// if parameter is not physical path will create new memory then return
	// else return NULL
	//eg: \abc to c:\programname\abc
	/************************************************************************/
	static std::vector<TCHAR> TransForRootPath(const TCHAR* path)
	{
		std::vector<TCHAR> fullpath(MAXPATH, 0);
		if (CFUNC::IsRootPath(path))
		{
			return fullpath;
		}
		GetModuleFileName(NULL, &fullpath[0], MAXPATH);
		
		*(_tcsrchr(&fullpath[0], _T('\\'))+1) = 0;
		if (path[0] == _T('\\'))
		{
			path++;
		}

		_tcscat_s(&fullpath[0], MAXPATH, path);

		return fullpath;
	}

	/************************************************************************/
	// transfer Slash                                                               
	// eg: '\' to '/'
	/************************************************************************/
	static void SlashLtoR(TCHAR* path)
	{
		TCHAR* tmp = path;
		while (*tmp)
		{
			if (*tmp == _T('\\'))
			{
				*tmp = _T('/');
			}
			tmp++;
		}
	}

	/************************************************************************/
	// transfer Slash                                                               
	//eg: '/' to '\'
	/************************************************************************/
	static void SlashRtoL(TCHAR* path)
	{
		TCHAR* tmp = path;
		while (*tmp)
		{
			if (*tmp == _T('/'))
			{
				*tmp = _T('\\');
			}
			tmp++;
		}
	}
};
