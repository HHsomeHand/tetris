#include "corn_app_common.h"
#include "corn_debug.h"
#include <Windows.h>
#include <tchar.h>

namespace corn {
	DECLSPEC_NORETURN
	void ErrorReport() {
		FormatErrorAndMsgAndExit();

		::ExitProcess(0);
	}

	// [min, max)
	int GetRandom(int min, int max) {
		return min + rand() % (max - min);
	}
	tstring FormatStr(LPCTSTR fmt, ...)
	{
		TCHAR buffer[1024];

		va_list args;
		va_start(args, fmt);
		_vsntprintf_s(buffer, _countof(buffer), _TRUNCATE, fmt, args);
		va_end(args);

		return tstring(buffer);
	}
}