#pragma once
#include "CBlock.h"
#include "CShape.h"


namespace corn {
	class CBoard
	{
	public:
		CBoard();
		static constexpr int BOARD_WIDTH = 12;
		static constexpr int BOARD_HEIGHT = 20;

		BOOL CanMove(const CShape& shape);

		void FixShape(const CShape& shape);

		CBlock& GetBlock(int nX, int nY);
		const CBlock& GetBlock(int nX, int nY) const;

		constexpr int GetWidth() const
		{
			return BOARD_WIDTH;
		}

		constexpr int GetHeight() const
		{
			return BOARD_HEIGHT;
		}

		static HBRUSH GetBrush();

		void ClearLine();
	private:
		CBlock m_blocks[BOARD_HEIGHT][BOARD_WIDTH]; // ¸ß 20, ¿í 10 µÄ±³¾°°å

	};
}

