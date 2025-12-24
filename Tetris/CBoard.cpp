#include "CBoard.h"
#include "AutoHBrush.h"
#include "corn_debug.h"
namespace corn {
	CBoard::CBoard()
	{
		memset(m_blocks, 0, sizeof(m_blocks));

		for (int nHeight = 0; nHeight < BOARD_HEIGHT; nHeight++) {
			m_blocks[nHeight][0].SetExist(TRUE);
			m_blocks[nHeight][0].SetBrush(GetBrush());

			m_blocks[nHeight][BOARD_WIDTH - 1].SetExist(TRUE);
			m_blocks[nHeight][BOARD_WIDTH - 1].SetBrush(GetBrush());
		}

		for (int nWidth = 0; nWidth < BOARD_WIDTH; nWidth++) {
			m_blocks[BOARD_HEIGHT - 1][nWidth].SetExist(TRUE);
			m_blocks[BOARD_HEIGHT - 1][nWidth].SetBrush(GetBrush());
		}
	}
	BOOL CBoard::CanMove(const CShape& shape)
	{
		if (shape.GetX() >= GetWidth()) {
			return FALSE;
		}

		for (int nHeight = 0; nHeight < shape.GetHeight(); nHeight++) {
			for (int nWidth = 0; nWidth < shape.GetWidth(); nWidth++) {
				if (shape.IsBlockExist(nWidth, nHeight)) {
					int nX = (nWidth + shape.GetX());
					int nY = (nHeight + shape.GetY());

					if (GetBlock(nX, nY).IsExist()) {
						return FALSE;
					}
				}
			}
		}
		return TRUE;
	}
	void CBoard::FixShape(const CShape& shape)
	{
		for (int nHeight = 0; nHeight < shape.GetHeight(); nHeight++) {
			for (int nWidth = 0; nWidth < shape.GetWidth(); nWidth++) {
				if (shape.IsBlockExist(nWidth, nHeight)) {
					int nX = (nWidth + shape.GetX());
					int nY = (nHeight + shape.GetY());

					CBlock& block = GetBlock(nX, nY);
					block.SetExist(TRUE);
					block.SetBrush(shape.GetBrush());
				}
			}
		}

		ClearLine();
	}
	CBlock& CBoard::GetBlock(int nX, int nY)
	{
		return (CBlock&)(((const CBoard*)(this))->GetBlock(nX, nY));
	}

	const CBlock& CBoard::GetBlock(int nX, int nY) const
	{
		return m_blocks[nY][nX];
	}

	HBRUSH CBoard::GetBrush()
	{
		static AutoHBrush hBrush = CreateSolidBrush(RGB(180, 180, 180));

		return hBrush.Get();
	}
	void CBoard::ClearLine()
	{
		for (int nHeight = BOARD_HEIGHT - 2; nHeight >= 0; ) {

			BOOL isFull = TRUE;

			for (int nWidth = 1; nWidth < BOARD_WIDTH - 1; nWidth++) {
				if (!GetBlock(nWidth, nHeight).IsExist()) {
					isFull = FALSE;
					break;
				}
			}

			if (!isFull) {
				nHeight--;
			}
			else {
				for (int nMoveHeight = nHeight; nHeight > 0; nHeight--) {
					for (int nWidth = 1; nWidth < BOARD_WIDTH - 1; nWidth++) {
						GetBlock(nWidth, nHeight) = GetBlock(nWidth, nHeight - 1);
					}
				}
			}
		}
	}
}
