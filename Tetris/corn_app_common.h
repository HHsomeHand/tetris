#pragma once
#include <Windows.h>
#include "corn_debug.h"

namespace corn {
	// 通过 MessageBox 报告 GetLastError 的错误, 并退出
	DECLSPEC_NORETURN void ErrorReport();

	// [min, max)
	int GetRandom(int min, int max);

	tstring FormatStr(LPCTSTR fmt, ...);
}
