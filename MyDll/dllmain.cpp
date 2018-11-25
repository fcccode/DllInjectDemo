// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <IMM.H>
#include <immdev.h>
#include <tchar.h>

#define EXTERN_DLL_EXPORT extern "C" __declspec(dllexport)


EXTERN_DLL_EXPORT LRESULT  foo( _In_ int code, _In_ WPARAM wParam, _In_ LPARAM lParam );


LRESULT  foo( _In_ int code, _In_ WPARAM wParam, _In_ LPARAM lParam )
{
	return CallNextHookEx( NULL, code, wParam, lParam );
}



BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	/* Open file*/
	switch ( ul_reason_for_call )
	{
		case DLL_PROCESS_ATTACH:
			MessageBox( NULL, L"Dll injected.", L"", 0 );
			break;
		case DLL_THREAD_ATTACH:
			break;
		case DLL_THREAD_DETACH:
			break;
		case DLL_PROCESS_DETACH:
			break;

	}


	return TRUE;
}

// The IME window doesn't need to do anything.
LRESULT WINAPI UIWndProc(HWND hUIWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	return 0;
}
LRESULT WINAPI StatusWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return 0; }
LRESULT WINAPI CompWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return 0; }
LRESULT WINAPI CandWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) { return 0; }

// Necessary IME exports
UINT WINAPI ImeEnumRegisterWord(REGISTERWORDENUMPROC lpfnRegisterWordEnumProc, LPCTSTR lpszReading, DWORD dwStyle, LPCTSTR lpszString, LPVOID lpData) { return (FALSE); }
UINT WINAPI ImeGetRegisterWordStyle(UINT nItem, LPSTYLEBUF lpStyleBuf) { return (FALSE); }
BOOL WINAPI ImeRegisterWord(LPCTSTR lpszReading, DWORD dwStyle, LPCTSTR lpszString) { return (FALSE); }
BOOL WINAPI ImeUnregisterWord(LPCTSTR lpszReading, DWORD dwStyle, LPCTSTR lpszString) { return (FALSE); }
BOOL WINAPI NotifyIME(HIMC hIMC, DWORD dwAction, DWORD dwIndex, DWORD dwValue) { return (FALSE); }
UINT WINAPI ImeToAsciiEx(UINT uVKey, UINT uScanCode, CONST LPBYTE lpbKeyState, LPDWORD lpdwTransKey, UINT fuState, HIMC hIMC) { return 0; }
BOOL WINAPI ImeSetCompositionString(HIMC hIMC, DWORD dwIndex, LPCVOID lpComp, DWORD dwComp, LPCVOID lpRead, DWORD dwRead) { return (FALSE); }
BOOL WINAPI ImeProcessKey(HIMC hIMC, UINT uKey, LPARAM lKeyData, CONST LPBYTE lpbKeyState) { return (FALSE); }
LRESULT WINAPI ImeEscape(HIMC hIMC, UINT uSubFunc, LPVOID lpData) { return (FALSE); }
DWORD WINAPI ImeConversionList(HIMC hIMC, LPCTSTR lpSource, LPCANDIDATELIST lpCandList, DWORD dwBufLen, UINT uFlag) { return (FALSE); }
BOOL WINAPI ImeDestroy(UINT uForce) { return (uForce ? TRUE : (FALSE)); }
BOOL WINAPI ImeSetActiveContext(HIMC hIMC, BOOL fFlag) { return TRUE; }

BOOL WINAPI ImeSelect(HIMC hIMC, BOOL fSelect)
{
	return TRUE;
}

BOOL WINAPI ImeConfigure(HKL hKL, HWND hWnd, DWORD dwMode, LPVOID lpData)
{
	switch (dwMode) {
	case IME_CONFIG_GENERAL:
		break;
	default:
		return (FALSE);
		break;
	}
	return (TRUE);
}

// Note -- only ImeInquire is ever being run for some
BOOL WINAPI ImeInquire(LPIMEINFO lpIMEInfo, LPTSTR lpszUIClass, LPCTSTR lpszOption)
{
	lpIMEInfo->dwPrivateDataSize = 0;

	lpIMEInfo->fdwProperty = IME_PROP_KBD_CHAR_FIRST |
		IME_PROP_IGNORE_UPKEYS |
		IME_PROP_END_UNLOAD;

	lpIMEInfo->fdwConversionCaps = IME_CMODE_FULLSHAPE |
		IME_CMODE_NATIVE;

	lpIMEInfo->fdwSentenceCaps = IME_SMODE_NONE;
	lpIMEInfo->fdwUICaps = UI_CAP_2700;

	lpIMEInfo->fdwSCSCaps = 0;

	lpIMEInfo->fdwSelectCaps = SELECT_CAP_CONVERSION;


	return TRUE;
}

int WINAPI IMEClearPubString()
{
	return TRUE;
}

int WINAPI IMESetPubString(LPCTSTR tmpStr, DWORD UnloadDLL, DWORD loadNextIme, DWORD DllData1, DWORD DllData2, DWORD DllData3)
{
	return TRUE;
}