#include "corn_app_common.h"
#include "corn_debug.h"

namespace corn {
	DECLSPEC_NORETURN
	void ErrorReport() {
		FormatErrorAndMsgAndExit();

		::ExitProcess(0);
	}
}