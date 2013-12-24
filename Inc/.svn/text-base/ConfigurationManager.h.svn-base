#pragma once 

#include <stdlib.h>
#include <WinBase.h>
#include <Windows.h>
#include <WinNT.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <atlconv.h>
#include "../Inc/tinxml/tinyxml.h"
#include "../Inc/Tools.h"
#include "TypeCent.h"
//
using namespace std;

// Base class
class BaseConfigurationManager
{
public:
   BaseConfigurationManager(wstring configFilePath)
	   : m_configFilePath(configFilePath),
         m_bLoaded(false)
   {
   }
   virtual ~BaseConfigurationManager()
   {
   }
   virtual bool GetSettings() = 0;
   bool CheckFileExists(const wstring& path, bool bOutputMsg = true)
	{
		if(INVALID_FILE_ATTRIBUTES == (::GetFileAttributes(path.c_str())))
		{
			if(bOutputMsg == true)
			printf("File does not exists : %s\n", path.c_str());
			return false;
		}
		return true;
	}
   wstring Utf8ToUnicode(const char* str)
	{
		//UTF8 to Unicode
		//预转换，得到所需空间的大小
		int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, str, strlen(str), NULL, 0);
		wstring retStr(wcsLen, '\0');
		::MultiByteToWideChar(CP_UTF8, NULL, str, strlen(str), &retStr[0], wcsLen);

		return retStr;
	}
protected:
   wstring m_configFilePath;
   bool    m_bLoaded;
private:
	BaseConfigurationManager(const BaseConfigurationManager&);
	BaseConfigurationManager& operator=(const BaseConfigurationManager&);
};

class MvsConfigurationManager : public BaseConfigurationManager
{
public:
	MvsConfigurationManager()
		:BaseConfigurationManager(GetConfigFilePath())
	{
		m_basicSettings.clear();
		m_channelSettings.clear();
	}
	virtual ~MvsConfigurationManager()
	{
		std::for_each(m_channelSettings.begin(), m_channelSettings.end(),[](CHANNEL_SETTING& setting)
		{
			EnumThreadWindows(setting.m_pi.dwThreadId,EnumThreadWndProc,WM_MI_EXIT_MESSAGE);   		
 			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,setting.m_pi.dwProcessId);
 			if(hProcess != NULL)
 			{
 				TerminateProcess(hProcess,0);
 				CloseHandle(hProcess);
 			}
		});
	}
	virtual bool GetSettings()
	{
		if(m_bLoaded == true)
			return true;

		if(CheckFileExists(m_configFilePath))
		{
			USES_CONVERSION;
			string strConfigFilePath(T2CA(m_configFilePath.c_str()));
			TiXmlDocument config(strConfigFilePath);
			if(!config.LoadFile())
				return false;

			TiXmlNode* node = config.FirstChild("configuration");
			if(node == nullptr)
				return false;
			// basic setting
			TiXmlNode* basicNode = node->FirstChild("basicSetting");
			if(basicNode == nullptr)
				return false;

			string key;
			string strValue;
			TiXmlElement* pAppElement = basicNode->ToElement();
			if(pAppElement != nullptr)
			{
				for(TiXmlElement* pElement = pAppElement->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
				{
					pElement->QueryValueAttribute("key",&key);
					pElement->QueryValueAttribute("value",&strValue);
					if(!key.empty() && !strValue.empty())
					{
						wstring wsKey   = Utf8ToUnicode(key.c_str());
						wstring wsValue = Utf8ToUnicode(strValue.c_str());
						m_basicSettings[wsKey] = wsValue;
					}
				}
			}
			// panel settings
			TiXmlNode* pPanelNode = node->FirstChild("panelSetting");
			if(pPanelNode != nullptr)
			{
				TiXmlElement* pPanelSettingElement = pPanelNode->ToElement();
				if(pPanelSettingElement != nullptr)
				{
					size_t index = 0;
					for(auto pElement = pPanelSettingElement->FirstChildElement(); pElement; pElement = pElement->NextSiblingElement())
					{
						pElement->QueryValueAttribute("key",&key);
						pElement->QueryValueAttribute("value",&strValue);
						if(!key.empty() && !strValue.empty())
						{
							CHANNEL_SETTING setting;
							setting.szStationID    = Utf8ToUnicode(key.c_str());
							setting.szProgramName  = Utf8ToUnicode(strValue.c_str());
							setting.m_channelIndex = index++;
							m_channelSettings.push_back(setting);
						}
					}
				}
			}
		}

		m_bLoaded = true;
		return true;
	}
	std::vector<CHANNEL_SETTING>* GetChannelSettingPtr()
	{
		if(!m_bLoaded)
			GetSettings();
		return &m_channelSettings;
	}
	wstring GetBasicSetting(wstring key)
	{
		if(!m_bLoaded)
			GetSettings();

		wstring ret(L"");
		if(m_basicSettings.count(key) > 0)
	    {
		    ret = m_basicSettings[key];
	    }
	   return ret;
	}
	void SetProgram(wstring sStationID,wstring program)
	{
		//FILE *fp;
		//if(_wfopen_s(&fp,&m_sDataPath[0],_T("w+"))!=0)
		//{
		//	AfxMessageBox(_T("Error"));
		//	return;
		//}

		//fprintf(fp,"%s\r\n","[StationID]");
		//CHANNEL_SETTING* p=NULL;

		//CHANNEL_SETTING retVal;
		//std::for_each(m_vSettings.begin(), m_vSettings.end(),[&](CHANNEL_SETTING& data)
		//{
		//	if (!_wcsicmp(data.szStationID.c_str(),sStationID))
		//	{
		//		data.szProgramName = program;
		//	}
		//	fwprintf_s(fp,_T("Panel=%s-%s\n"),data.szStationID.c_str(),data.szProgramName.c_str());
		//});

		//fclose(fp);
	}
private:
	static std::wstring GetConfigFilePath()
	{
		TCHAR  moduleFileName[MAX_PATH];  
		::GetModuleFileName(NULL,moduleFileName, MAX_PATH);
		wstring filePath(moduleFileName);
		filePath.append(L".config");
		return filePath;
	}
private:
	std::map<wstring, wstring> m_basicSettings;
    std::vector<CHANNEL_SETTING> m_channelSettings;
private:
	MvsConfigurationManager(const MvsConfigurationManager&);
	MvsConfigurationManager& operator=(const MvsConfigurationManager&);
};
