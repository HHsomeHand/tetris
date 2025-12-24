#pragma once
#include "Timer.h"

namespace corn {

	class FlashTimer : public Timer {
	public:
		static constexpr int TIMER_FLASH = 1;

		FlashTimer();

		virtual void Start() override;

		virtual BOOL SpeedDown() override;
		virtual BOOL SpeedUp() override;

		virtual BOOL  SetSpeed(DWORD speed) override;

	private:
		void SetDlgSpeedIndicator();
	};

}