#include "FlashTimer.h"

namespace corn {
#include "FlashTimer.h"

	FlashTimer::FlashTimer()
		: Timer()
	{
		SetID(TIMER_FLASH);
	}

	void FlashTimer::Start() {
		Timer::Start();
		SetDlgSpeedIndicator();
	}

	void FlashTimer::SetDlgSpeedIndicator() {
		/*
		SetDlgItemText(
			GetHwnd(),
			IDC_TEXT_SPEED,
			FormatStr(
				_T("当前速度: %d \n %s"),
				1000 - GetSpeed(),
				GetSpeed() == GetMaxSpeed() ? _T("最大速度") : _T("")
			).c_str()
		);
		*/
	}

	BOOL FlashTimer::SpeedDown() {
		Timer::SpeedDown();
		SetDlgSpeedIndicator();
		return TRUE;
	}

	BOOL FlashTimer::SpeedUp() {
		BOOL ret = Timer::SpeedUp();
		SetDlgSpeedIndicator();
		return ret;
	}

	BOOL FlashTimer::SetSpeed(DWORD speed)
	{
		BOOL ret = Timer::SetSpeed(speed);
		InvalidateRect(GetHwnd(), NULL, FALSE);
		return ret;
	}

}