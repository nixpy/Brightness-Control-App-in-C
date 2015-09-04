#include "gammasetting.h"

CgammaSetting::CgammaSetting()
{
	hGDI32 = NULL;
	hScreenDC = NULL;
	pGetDeviceGammaRamp = NULL;
	pSetDeviceGammaRamp = NULL;
}

CgammaSetting::~CgammaSetting()
{
	FreeLibrary();
}

BOOL CgammaSetting::LoadLibraryTest()
{
	BOOL bResult = FALSE;
	FreeLibrary();


	LPCWSTR lpdll = (LPCWSTR)"gdi32.dll";

	hGDI32 = LoadLibraryA("gdi32.dll");

	if (hGDI32 != NULL)
	{
		//Get the addresses of GetDeviceGammaRamp and SetDeviceGammaRamp API functions.
		pGetDeviceGammaRamp =
			(Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "GetDeviceGammaRamp");

		pSetDeviceGammaRamp =
			(Type_SetDeviceGammaRamp)GetProcAddress(hGDI32, "SetDeviceGammaRamp");

		//Return TRUE only if these functions exist.
		if (pGetDeviceGammaRamp == NULL || pSetDeviceGammaRamp == NULL)
			FreeLibrary();
		else
			bResult = TRUE;
	}


	return bResult;
}

void CgammaSetting::FreeLibrary()
{
	//Free the GDI library.
	if (hGDI32 != NULL)
	{
		::FreeLibrary(hGDI32);
		hGDI32 = NULL;
	}
}

BOOL CgammaSetting::LoadLibraryIfNeeded()
{
	BOOL bReturn = FALSE;

	if (hGDI32 == NULL)
		LoadLibraryTest();

	if (pGetDeviceGammaRamp != NULL && pSetDeviceGammaRamp != NULL)
		bReturn = TRUE;

	return bReturn;
}

BOOL CgammaSetting::SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
	//Call to SetDeviceGammaRamp only if this function is successfully loaded.
	if (LoadLibraryIfNeeded())
	{
		return pSetDeviceGammaRamp(hDC, lpRamp);
	}
	else
		return FALSE;
}

BOOL CgammaSetting::GetDeviceGammaRamp(HDC hDC, LPVOID lpRamp)
{
	//Call to GetDeviceGammaRamp only if this function is successfully loaded.
	if (LoadLibraryIfNeeded())
	{
		return pGetDeviceGammaRamp(hDC, lpRamp);
	}
	else
		return FALSE;

}

BOOL CgammaSetting::SetBrightness(HDC hDC, WORD wBrightness)
{
	BOOL bReturn = FALSE;
	HDC hGammaDC = hDC;

	//Load the display device context of the entire screen if hDC is NULL.
	if (hDC == NULL)
		hGammaDC = GetDC(NULL);

	if (hGammaDC != NULL)
	{
		//Generate the 256-colors array for the specified wBrightness value.
		WORD GammaArray[3][256];

		for (int iIndex = 0; iIndex < 256; iIndex++)
		{
			int iArrayValue = iIndex * (wBrightness + 128);

			if (iArrayValue > 65535)
				iArrayValue = 65535;

			GammaArray[0][iIndex] =
				GammaArray[1][iIndex] =
				GammaArray[2][iIndex] = (WORD)iArrayValue;

		}

		//Set the GammaArray values into the display device context.
		bReturn = SetDeviceGammaRamp(hGammaDC, GammaArray);
	}

	if (hDC == NULL)
		ReleaseDC(NULL, hGammaDC);

	return bReturn;
}