#ifndef GAMMASETTING_H_
#define GAMMASETTING_H_
#include<Windows.h>

class gammasetting
{
public:
};


class CgammaSetting
{
protected:
	HMODULE hGDI32;
	HDC hScreenDC;
	typedef bool(WINAPI *Type_SetDeviceGammaRamp)(HDC hdc, LPVOID lpRamp);

	Type_SetDeviceGammaRamp pGetDeviceGammaRamp;
	Type_SetDeviceGammaRamp pSetDeviceGammaRamp;

public:
	CgammaSetting();
	~CgammaSetting();
	BOOL LoadLibraryTest();
	void FreeLibrary();
	BOOL LoadLibraryIfNeeded();
	BOOL SetDeviceGammaRamp(HDC hdc, LPVOID lpRamp);
	BOOL GetDeviceGammaRamp(HDC hdc, LPVOID lpRamp);
	BOOL SetBrightness(HDC hdc, WORD wBrightness);
};

#endif
