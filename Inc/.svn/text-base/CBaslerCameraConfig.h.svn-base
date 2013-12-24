#if !defined(__BASLERCAMERAMODULE_H__)
#define __BASLERCAMERAMODULE_H__
// BaslerCameraModule.h
#pragma once
// std string and file manipulations
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;
// Class to hold configurations
class CBaslerCameraConfig
{
public:
	CBaslerCameraConfig();
	CBaslerCameraConfig(string fileName);
	~CBaslerCameraConfig();
	string	m_GetIP() {return m_ip;};
	string	m_GetPixelFormat(){return m_pixelFormat;};
	string	m_GetTriggerMode(){return m_triggerMode;};
	string	m_GetTriggerEdge(){return m_triggerEdge;};
	int     m_GetExposureTime(){return m_exposureTime;};
	int     m_GetDebouncerTime(){return m_debouncerTime;};
	int     m_GetIndex(){return m_index;};
	int	GetDebouncerTime(){return m_debouncerTime;};



	void	m_SetIP(string ip) { m_ip = ip;};
	void	m_SetPixelFormat(string pixelFormat){m_pixelFormat = pixelFormat;};
	void	m_SetTriggerMode(string triggerMode){m_triggerMode = triggerMode;};
	void	m_SetTriggerEdge(string triggerEdge){m_triggerEdge = triggerEdge;};;
	void    m_SetExposureTime(int exposureTime){m_exposureTime = exposureTime;};;
	void    m_SetDebouncerTime(int debouncerTime){m_debouncerTime =debouncerTime;};;
	void    m_SetIndex(int index){m_index = index;};
	void	m_SetColorMode(bool colorMode){m_ColorMode = colorMode;};


	void	m_LoadConfigFile(const char * fileName);
	bool	m_SaveConfigFile(const char * fileName);
	bool	IsAvailable(){return true;};

private:
	int         m_index;
	string		m_ip;
	string		m_pixelFormat;
	string		m_triggerMode;
	string		m_triggerEdge;
	int         m_exposureTime;
	int         m_debouncerTime;
	string		m_configFileName;
	bool		m_ColorMode;

};

#endif