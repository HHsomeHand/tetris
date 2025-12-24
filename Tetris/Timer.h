#pragma once
#include <windows.h>

namespace corn {

	class Timer {
	public:
		// 构造 / 析构
		Timer(HWND _hWnd, DWORD _nID, DWORD _nSpeed, DWORD _nMaxSpeed, DWORD _nStep);
		Timer();
		virtual ~Timer();

		// 禁止拷贝
		Timer(const Timer&) = delete;
		Timer& operator=(const Timer&) = delete;

		// 允许移动
		Timer(Timer&& other) noexcept;
		Timer& operator=(Timer&& other) noexcept;

		// Getter / Setter
		HWND  GetHwnd() const;
		void  SetHwnd(HWND hWnd);

		DWORD GetID() const;
		void  SetID(DWORD id);

		DWORD GetSpeed() const;
		virtual BOOL  SetSpeed(DWORD speed);

		virtual BOOL SpeedDown();
		virtual BOOL SpeedUp();

		DWORD GetMaxSpeed() const;
		void  SetMaxSpeed(DWORD max_speed);

		DWORD GetStep() const;
		void  SetStep(DWORD nStep);

		virtual void Start();
		void Stop();

		BOOL IsStart() const;

	protected:
		void SetIsStart(BOOL isStart);

	private:
		void KillTimer();

	private:
		HWND  m_hWnd = NULL;
		DWORD m_nID = 0;
		DWORD m_nSpeed = 0;
		DWORD m_nMaxSpeed = 0;
		DWORD m_nStep = 0;
		BOOL  m_isStart = FALSE;
	};

}