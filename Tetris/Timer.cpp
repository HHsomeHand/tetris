#include "Timer.h"

namespace corn {
#include "Timer.h"

	// 构造 / 析构
	Timer::Timer(
		HWND _hWnd,
		DWORD _nID,
		DWORD _nSpeed,
		DWORD _nMaxSpeed,
		DWORD _nStep
	)
		: m_hWnd(_hWnd),
		m_nID(_nID),
		m_nSpeed(_nSpeed),
		m_nMaxSpeed(_nMaxSpeed),
		m_nStep(_nStep),
		m_isStart(FALSE)
	{
	}

	Timer::Timer()
		: Timer(NULL, 0, 400, 100, 50)
	{
	}

	Timer::~Timer() {
		KillTimer();
	}

	// 移动构造
	Timer::Timer(Timer&& other) noexcept
		: m_hWnd(other.m_hWnd),
		m_nID(other.m_nID),
		m_nSpeed(other.m_nSpeed),
		m_nMaxSpeed(other.m_nMaxSpeed),
		m_nStep(other.m_nStep),
		m_isStart(other.m_isStart)
	{
		other.m_hWnd = NULL;
		other.m_nID = 0;
		other.m_isStart = FALSE;
	}

	// 移动赋值
	Timer& Timer::operator=(Timer&& other) noexcept {
		if (this != &other) {
			Stop();

			m_hWnd = other.m_hWnd;
			m_nID = other.m_nID;
			m_nSpeed = other.m_nSpeed;
			m_nMaxSpeed = other.m_nMaxSpeed;
			m_nStep = other.m_nStep;
			m_isStart = other.m_isStart;

			other.m_hWnd = NULL;
			other.m_nID = 0;
			other.m_isStart = FALSE;
		}
		return *this;
	}

	// Getter / Setter
	HWND Timer::GetHwnd() const {
		return m_hWnd;
	}

	void Timer::SetHwnd(HWND hWnd) {
		m_hWnd = hWnd;
	}

	DWORD Timer::GetID() const {
		return m_nID;
	}

	void Timer::SetID(DWORD id) {
		if (m_nID == id) return;

		BOOL wasStart = IsStart();
		Stop();

		m_nID = id;
		if (wasStart) {
			Start();
		}
	}

	DWORD Timer::GetSpeed() const {
		return m_nSpeed;
	}

	BOOL Timer::SetSpeed(DWORD speed) {
		if (speed < GetMaxSpeed()) {
			return FALSE;
		}

		m_nSpeed = speed;

		if (IsStart()) {
			Start();
		}
		return TRUE;
	}

	BOOL Timer::SpeedDown() {
		SetSpeed(GetSpeed() + GetStep());
		return TRUE;
	}

	BOOL Timer::SpeedUp() {
		int newSpeed = GetSpeed() - GetStep();
		if (newSpeed < (int)GetMaxSpeed()) {
			return FALSE;
		}
		SetSpeed(newSpeed);
		return TRUE;
	}

	DWORD Timer::GetMaxSpeed() const {
		return m_nMaxSpeed;
	}

	void Timer::SetMaxSpeed(DWORD max_speed) {
		m_nMaxSpeed = max_speed;
	}

	DWORD Timer::GetStep() const {
		return m_nStep;
	}

	void Timer::SetStep(DWORD nStep) {
		m_nStep = nStep;
	}

	// 控制
	void Timer::Start() {
		SetIsStart(TRUE);
		KillTimer();
		::SetTimer(GetHwnd(), GetID(), GetSpeed(), NULL);
	}

	void Timer::Stop() {
		SetIsStart(FALSE);
		KillTimer();
	}

	void Timer::SetIsStart(BOOL isStart) {
		m_isStart = isStart;
	}

	BOOL Timer::IsStart() const {
		return m_isStart;
	}

	void Timer::KillTimer() {
		if (GetHwnd() != NULL) {
			::KillTimer(GetHwnd(), GetID());
		}
	}

}