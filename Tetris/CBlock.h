#pragma once
#include <Windows.h>

namespace corn {
	class CBlock
	{
	public:
		BOOL IsExist() const;
		void SetExist(BOOL _bExist);

		HBRUSH GetBrush() const;
		void SetBrush(HBRUSH hBrush);

	private:
		BOOL m_bExist;
		HBRUSH m_hBrush; // use RGB init
	};
}

