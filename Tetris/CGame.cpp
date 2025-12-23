#include "CGame.h"
#include <time.h>
#include <stdlib.h>
#include <tchar.h>
#include "corn_debug.h"
#include "main.h"

namespace corn {
	CGame::CGame()
	{
		Init();
	}

	CGame& CGame::GetInstance() {
		static CGame instance;
		return instance;
	}

	void CGame::OnTimer(HWND hwnd)
	{
		DownShape(hwnd);
	}

	void CGame::DownShape(HWND hwnd)
	{
		if (!Move(VECTOR2D_DOWN)) {
			if (IsNewShape()) {
				SendMessage(hwnd, WM_GAME_OVER, 0, 0);
				
				MessageBox(NULL, _T("游戏结束"), _T("俄罗斯方块"), MB_OK);
			}
			GetBoard().FixShape(GetCurrShape());

			SwitchCurrShape();
		}
		else {
			SetIsNewShape(FALSE);
		}
	}

	void CGame::SwitchCurrShape()
	{
		SetCurrShape(CShape());

		GetCurrShape().SetX(2); // TODO: Delete This

		SetIsNewShape(TRUE);
	}

	void CGame::Init()
	{
		GetCurrShape().SetX(2); // TODO: Delete This
	}

	void CGame::ReInit()
	{
		SetBoard(CBoard());

		SwitchCurrShape();
	}

	const CShape& CGame::GetCurrShape() const
	{
		return m_currShape;
	}

	CShape& CGame::GetCurrShape() {
		return (CShape&)(((const CGame*)(this))->GetCurrShape());
	}

	void CGame::SetCurrShape(const CShape& shape)
	{
		m_currShape = shape;
	}

	const CBoard& CGame::GetBoard() const 
	{
		return m_board;
	}

	CBoard& CGame::GetBoard() {
		return (CBoard&)(((const CGame*)(this))->GetBoard());
	}

	void CGame::SetBoard(const CBoard& board)
	{
		m_board = board;
	}

	void CGame::RotateCurrShape()
	{
		GetCurrShape().RotateRight();


		for (int x_off = 0; x_off < 5; x_off++) {
			for (int y_off = 0; y_off < 5; y_off++) {
				for (int x_sign : {1, -1}) {
					for (int y_sign : {1, -1}) {
						if (Move({
								.x = x_off * x_sign,
								.y = y_off,
							})) {
							return;
						}
					}
				}
			}
		}
	}
	void CGame::Paint(HDC hdc) const
	{
		const CBoard& board = GetBoard();

		for (int nY = 0; nY < board.GetHeight(); nY++) {
			for (int nX = 0; nX < board.GetWidth(); nX++) {
				const CBlock& block = board.GetBlock(nX, nY);
				if (block.IsExist()) {
					PaintBlock(hdc, nX, nY, block.GetBrush());
				}
			}
		}
		const CShape& shape = GetCurrShape();

		HBRUSH hShapeBrush = shape.GetBrush();

		for (int nHeight = 0; nHeight < shape.GetHeight(); nHeight++) {
			for (int nWidth = 0; nWidth < shape.GetWidth(); nWidth++) {
				if (shape.IsBlockExist(nWidth, nHeight)) {
					int nX = (nWidth + shape.GetX());
					int nY = (nHeight + shape.GetY());

					PaintBlock(hdc, nX, nY, hShapeBrush);
				}
			}
		}
	}
	void CGame::PaintBlock(HDC hdc, int x, int y, HBRUSH hBrush) const
	{
		constexpr int BLOCK_SIZE = 24;

		RECT rect = { 0 };
		rect.left = x * BLOCK_SIZE;
		rect.top = y * BLOCK_SIZE;
		rect.right = (x + 1) * BLOCK_SIZE;
		rect.bottom = (y + 1) * BLOCK_SIZE;

		FillRect(hdc, &rect, hBrush);
	}

	BOOL CGame::Move(Vector2D v) {

		CShape& shape = GetCurrShape();

		int nOldX = shape.GetX();
		int nOldY = shape.GetY();

		shape.Move(v);
		if (!GetBoard().CanMove(shape)) {
			shape.SetPos(nOldX, nOldY);
			return FALSE;
		}

		SetIsNewShape(FALSE);
		return TRUE;
	}
	BOOL CGame::IsNewShape() const
	{
		return m_isNewShape;
	}
	void CGame::SetIsNewShape(BOOL isNew)
	{
		m_isNewShape = isNew;
	}
}