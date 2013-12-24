#include "StdAfx.h"
#include "VLCtrl.h"
#include "MCtrlCenter.h"
#include "MConfigCenter.h"

#include <atlconv.h>

CVLCtrl::CVLCtrl():m_bUsbConnected(false),
	               m_hDriver(NULL)
{
	SetMultipier = NULL;
	SetCHMode = NULL;
	SetConstInt = NULL;
	STROBE = NULL;
	SetStrobeWidth = NULL;
	SetCONSTOnOff = NULL;
	ComPortConnect = NULL;				
	ComPortDisConnect = NULL;				
	USBConnect = NULL;				
	USBDisconnect = NULL;

	SetAutoStrobeDnTime = NULL;
	AUTOSTROBE = NULL;
	EEPROM = NULL;
	GETErrMsg = NULL;
	SetAutoStrobeUpTime = NULL;
	SelectAdd = NULL;


	TCHAR szFilePath[MAX_PATH + 1];
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; //删除文件名，只获得路径
	CString dllName;
	dllName.Format(_T("%sLEDStudio.dll"),szFilePath);

	m_hDriver = ::LoadLibrary(_T("C:\\LEDStudio\\LEDLib\\LEDStudio.dll"));
	if(m_hDriver != NULL)
	{
		ComPortConnect      = reinterpret_cast<LE_ComportConnect>(GetProcAddress(m_hDriver, "LE_ComportConnect"));				
		ComPortDisConnect   = reinterpret_cast<LE_ComportDisConnect>(GetProcAddress(m_hDriver, "LE_ComportDisConnect"));
		USBConnect          = reinterpret_cast<LE_USBConnect>(GetProcAddress(m_hDriver, "LE_USBConnect"));
		USBDisconnect       = reinterpret_cast<LE_USBDisconnect>(GetProcAddress(m_hDriver, "LE_USBDisconnect"));
		SetMultipier        = reinterpret_cast<LE_SetMultipier>(GetProcAddress(m_hDriver, "LE_SetMultipier"));
		SetCHMode           = reinterpret_cast<LE_SetCHMode>(GetProcAddress(m_hDriver, "LE_SetCHMode"));
		SetConstInt		    = reinterpret_cast<LE_SetConstInt>(GetProcAddress(m_hDriver, "LE_SetConstInt"));
		SetCONSTOnOff       = reinterpret_cast<LE_SetCONSTOnOff>(GetProcAddress(m_hDriver, "LE_SetCONSTOnOff"));
		SetStrobeWidth      = reinterpret_cast<LE_SetStrobeWidth>(GetProcAddress(m_hDriver, "LE_SetStrobeWidth"));
		STROBE              = reinterpret_cast<LE_STROBE>(GetProcAddress(m_hDriver, "LE_STROBE"));
		GETErrMsg           = reinterpret_cast<LE_GETErrMsg>(GetProcAddress(m_hDriver, "LE_GETErrMsg"));
		SetAutoStrobeUpTime = reinterpret_cast<LE_SetAutoStrobeUpTime>(GetProcAddress(m_hDriver, "LE_SetAutoStrobeUpTime"));
		SetAutoStrobeDnTime = reinterpret_cast<LE_SetAutoStrobeDnTime>(GetProcAddress(m_hDriver, "LE_SetAutoStrobeDnTime"));
		AUTOSTROBE          = reinterpret_cast<LE_AUTOSTROBE>(GetProcAddress(m_hDriver, "LE_AUTOSTROBE"));
		EEPROM              = reinterpret_cast<LE_EEPROM>(GetProcAddress(m_hDriver, "LE_EEPROM"));
		SelectAdd           = reinterpret_cast<LE_SelectAdd>(GetProcAddress(m_hDriver, "LE_SelectAdd"));
	}
	else
	{
		CString msg = _T("Error. Load Dll ") + dllName + _T("Error");
		AfxMessageBox(msg);
	}
}

CVLCtrl::~CVLCtrl()
{
	if(m_hDriver != NULL)
	{
		::FreeLibrary(m_hDriver);
	}
}

bool CVLCtrl::TryConnectToUSB(bool bDisplayMsg)
{
	if(m_bUsbConnected == false)
	{
		return ConnectToUSB(bDisplayMsg);
	}
	return true;
}

bool CVLCtrl::ConnectToUSB(bool bDisplayMsg)
{
	char* productName = "LC-11"; 
	byte err_code = USBConnect(productName);
	if(err_code == 0)
	{
		m_bUsbConnected = true;
	}
	else
	{
		if(bDisplayMsg)
		{
#ifdef _ENGLISH
			AfxMessageBox(_T("Cannot connect to Light Controller!"));
#else
			AfxMessageBox(_T("连接光源控制器失败！"));
#endif
		}
		m_bUsbConnected = false;
	}
	return m_bUsbConnected;
}

void CVLCtrl::SetConnectedFlag(bool flag)
{
	m_bUsbConnected = flag;
}

void CVLCtrl::WriteLightParam2Controller()
{
	// Write default values
	auto pCtrlCenter = CMCtrlCenter::GetSingletonCtrlCenter();


	auto pLightInfos =  CMConfigCenter::GetSingletonConfigCenter()->GetLightCtrlInfosPtr();
	if(pLightInfos != nullptr && pLightInfos->empty() == true) 
		return;

	std::for_each(pLightInfos->begin(), pLightInfos->end(),[&](LightCtrlInfo& info)
	{
		byte err_code = pCtrlCenter->m_VLproxy.SelectAdd((byte)info.m_iaddress); //
		auto channels = info.m_vParameters;
		try
		{
			std::for_each(channels.begin(), channels.end(), [&](CHANNEL_PARAMETER& param)
			{
				int channel = atoi(param.channelIndex.c_str());
				err_code = pCtrlCenter->m_VLproxy.SetCHMode(channel, 1); // select channel to be adjusted
				int intensityValue = atoi(param.settingValue.c_str());
				pCtrlCenter->m_VLproxy.SetConstInt(intensityValue); // set intensity of the selected channel

				byte multiplier = 10; // default value;
				pCtrlCenter->m_VLproxy.SetMultipier(multiplier);

				byte strobeWidth = 20; // default value;
				pCtrlCenter->m_VLproxy.SetStrobeWidth(strobeWidth);

				pCtrlCenter->m_VLproxy.SetCHMode(channel, 1); // select channel to be adjusted

			});
		}
		catch(...)
		{
			AfxMessageBox(_T("SetConnectedFlag is False"));
			pCtrlCenter->m_VLproxy.SetConnectedFlag(false);
		}
	});
}