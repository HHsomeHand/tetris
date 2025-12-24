#pragma once
#include "CBoard.h"
#include "CShape.h"
#include <Windows.h>

namespace corn {
	class CGame
	{ 
	public:


		void OnTimer(HWND hwnd);

		void DownShape(HWND hwnd);

		void SwitchCurrShape();

		void Init();

		void InitShape();

		void Restart();

		CShape& GetCurrShape();
		const CShape& GetCurrShape() const;
		void SetCurrShape(const CShape& shape);

		CBoard& GetBoard();
		const CBoard& GetBoard() const;
		void SetBoard(const CBoard& board);

		void RotateCurrShape();

		void Paint(HDC hdc) const ;

		void PaintBlock(HDC hdc, int x, int y, HBRUSH hBrush) const;
		static CGame& GetInstance();

		BOOL Move(Vector2D v);

		void MakeShapeInBoard();

		void SetIsGameOver(BOOL isGameOver);
		BOOL GetIsGameOver();
	private:
		BOOL IsNewShape() const;
		void SetIsNewShape(BOOL isNew);


		CGame();
		CBoard m_board;
		CShape m_currShape;
		BOOL m_isNewShape;
		BOOL m_isGameOver;
	};
}
