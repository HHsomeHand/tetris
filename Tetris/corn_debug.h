#pragma once

#include <string>
#include <windows.h>

namespace corn {

#if defined(_UNICODE) || defined(UNICODE)
	using tstring = std::wstring;
#else
	using tstring = std::string;
#endif

	_Success_(return != FALSE)
	BOOL FormatError(_Out_ tstring* _pStr, _Out_opt_ DWORD* _pDw = nullptr);

	struct CFormatErrorAndMsgParam
	{
		_In_ HWND hwnd;
		_Out_opt_ tstring* _pStr;
		_Out_opt_ DWORD* _pDw;
	};

	BOOL FormatErrorAndMsg(CFormatErrorAndMsgParam param);

	DECLSPEC_NORETURN void FormatErrorAndMsgAndExit();

	// 使用了这个函数, 应用程序就可以正常 printf 了
	void InitConsole();

#if _DEBUG
	constexpr auto dbg_printf = printf;
#else
	constexpr auto dbg_printf = [](...) {};
#endif

	void DebugPrintf(LPCTSTR fmt, ...);
}