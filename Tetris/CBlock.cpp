#include "CBlock.h"

namespace corn {

	BOOL CBlock::IsExist() const
	{
		return m_bExist;
	}

	void CBlock::SetExist(BOOL _bExist)
	{
		m_bExist = _bExist;
	}

	HBRUSH CBlock::GetBrush() const
	{
		return m_hBrush;
	}

	void CBlock::SetBrush(HBRUSH hBrush)
	{
		m_hBrush = hBrush;
	}

}