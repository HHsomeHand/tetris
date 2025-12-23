#define  _CRT_SECURE_NO_WARNINGS

#include "corn_debug.h"
#include <Windows.h>
#include <string>
#include <assert.h>
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <format>

namespace corn {

	// 格式化 GetLastError() 的错误信息
	// https://learn.microsoft.com/zh-tw/windows/win32/debug/retrieving-the-last-error-code
	_Success_(return != FALSE)
	BOOL FormatError(_Out_ tstring* _pStr, _Out_opt_ DWORD* _pDw)
	{
		assert(nullptr != _pStr && "CornFormatError: _pStr 传出参数不能为空");

		if (nullptr == _pStr) {
			::SetLastError(ERROR_INVALID_PARAMETER);

			return FALSE;
		}

		DWORD dwTmp = 0;
		if (nullptr == _pDw) {
			_pDw = &dwTmp;
		}

		LPTSTR lpMsgBuf;
		*_pDw = ::GetLastError();

		if (::FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			*_pDw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL) == 0) {

			return FALSE;
		}

		*_pStr += lpMsgBuf;

		::LocalFree(lpMsgBuf);

		return TRUE;
	}

	BOOL FormatErrorAndMsg(CFormatErrorAndMsgParam param) {
		_In_ HWND hwnd = param.hwnd;
		_Out_opt_ tstring* _pStr = param._pStr;
		_Out_opt_ DWORD* _pDw = param._pDw;

		tstring strTmp;

		if (nullptr == _pStr) {
			_pStr = &strTmp;
		}

		BOOL bRet = FormatError(_pStr, _pDw);

		::MessageBox(hwnd, _pStr->c_str(), _T("Error"), MB_OK);

		return bRet;
	}

	DECLSPEC_NORETURN 
	void FormatErrorAndMsgAndExit() {
		DWORD dwError = 0;

		FormatErrorAndMsg({
			._pDw = &dwError,
			});

		::ExitProcess(dwError);
	}

	void InitConsole()
	{
		// 1. 分配控制台
		AllocConsole();

		FILE* fp;

		// stdout
		if (freopen_s(&fp, "CONOUT$", "w", stdout) == 0)
			setvbuf(stdout, NULL, _IONBF, 0);

		// stderr
		if (freopen_s(&fp, "CONOUT$", "w", stderr) == 0)
			setvbuf(stderr, NULL, _IONBF, 0);

		// stdin
		if (freopen_s(&fp, "CONIN$", "r", stdin) == 0)
			setvbuf(stdin, NULL, _IONBF, 0);
	}

	void DebugPrintf(LPCTSTR fmt, ...)
	{
		TCHAR buffer[1024];

		va_list args;
		va_start(args, fmt);
		_vsntprintf_s(buffer, _countof(buffer), _TRUNCATE, fmt, args);
		va_end(args);

		OutputDebugString(buffer);
	}
}
