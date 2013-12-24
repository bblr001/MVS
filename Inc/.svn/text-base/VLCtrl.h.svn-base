#pragma once
#include <stdio.h>
#include <string>

using namespace std;

typedef byte (__stdcall * LE_ComportConnect)(int& ComPort);
typedef byte (__stdcall * LE_ComportDisConnect)(byte ComPort);
typedef byte (__stdcall * LE_USBConnect)(char*& ProductName);
typedef byte (__stdcall * LE_USBDisconnect)();
typedef byte (__stdcall * LE_SetMultipier)(byte sMul);
typedef byte (__stdcall * LE_SetCHMode)(int sCH, int sMode);
typedef byte (__stdcall * LE_SetConstInt)(int sInt);
typedef byte (__stdcall * LE_SetCONSTOnOff)(byte sOn);
typedef byte (__stdcall * LE_SetStrobeWidth)(short sWidth);
typedef byte (__stdcall * LE_STROBE)(bool CH1, bool CH2, bool CH3, bool CH4);
typedef string (__stdcall * LE_GETErrMsg)(byte ErrCode);
typedef byte (__stdcall * LE_SetAutoStrobeUpTime)(short UpTime);
typedef byte (__stdcall * LE_SetAutoStrobeDnTime)(short DnTime);
typedef byte (__stdcall * LE_AUTOSTROBE)(bool CH1, bool CH2, bool CH3, bool CH4);
typedef byte (__stdcall * LE_EEPROM)();
typedef byte (__stdcall * LE_SelectAdd)(byte add);

class CVLCtrl
{
public:
	CVLCtrl();
	~CVLCtrl();

	LE_SetMultipier SetMultipier;
	LE_SetCHMode SetCHMode;
	LE_SetConstInt SetConstInt;
	LE_STROBE STROBE;
	LE_SetStrobeWidth SetStrobeWidth;
	LE_SetCONSTOnOff SetCONSTOnOff;
	LE_ComportConnect ComPortConnect;				
	LE_ComportDisConnect ComPortDisConnect;				
	LE_USBConnect USBConnect;				
	LE_USBDisconnect USBDisconnect;

	LE_SetAutoStrobeDnTime SetAutoStrobeDnTime;
	LE_AUTOSTROBE AUTOSTROBE;
	LE_EEPROM EEPROM;
	LE_GETErrMsg GETErrMsg;
	LE_SetAutoStrobeUpTime SetAutoStrobeUpTime;
	LE_SelectAdd SelectAdd;

	bool TryConnectToUSB(bool bDisplayMsg = true);
	void SetConnectedFlag(bool flag);
	bool GetConnectedFlag()
	{
		return m_bUsbConnected;
	}
	void WriteLightParam2Controller();
private:
	bool ConnectToUSB(bool bDisplayMsg = true);
	bool m_bUsbConnected;
	HMODULE m_hDriver;
};


