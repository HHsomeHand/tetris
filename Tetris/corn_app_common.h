#pragma once
#include <Windows.h>

namespace corn {
	// 通过 MessageBox 报告 GetLastError 的错误, 并退出
	DECLSPEC_NORETURN void ErrorReport();
}
