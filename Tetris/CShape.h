#pragma once
#include <Windows.h>
#include "Vector2D.h"

namespace corn {
	class CShape
	{
	public:
		CShape();

		enum DIR {
			UP = 0,
			RIGHT = 1,
			DOWN = 2,
			LEFT = 3,
			DIR_COUNT
		};

		CShape(int nShape, DIR dirRotate);

		static constexpr int VARIANT_WIDTH = 4;
		static constexpr int VARIANT_HEIGHT = 4;

		static constexpr int SIZE_OF_PER_VARIANT = VARIANT_WIDTH * VARIANT_HEIGHT;
		static constexpr int NUMBER_OF_VARIANTS_SHAPE_CONTAIN = 4;
		static constexpr int TOTAL_SHAPES = 4;
		static constexpr int SIZE_OF_PER_SHAPE = SIZE_OF_PER_VARIANT * NUMBER_OF_VARIANTS_SHAPE_CONTAIN;

		static constexpr int SIZE_OF_PRESET_TABLE = SIZE_OF_PER_VARIANT * NUMBER_OF_VARIANTS_SHAPE_CONTAIN * TOTAL_SHAPES;

		static char GetPreSetChar(int nShape, int nVariant, int nX, int nY);

		char GetCurrentChar(int nX, int nY) const;

		int GetX() const; 
		void SetX(int x);

		int GetY() const;
		void SetY(int y);

		void Move(Vector2D v);
		DIR RotateRight();

		void SetRotate(DIR rotate);
		DIR GetRotate() const;

		COLORREF GetColor() const;

		int GetShapeType() const;

		HBRUSH GetBrush() const;

		constexpr int GetWidth() const
		{
			return VARIANT_WIDTH;
		}

		constexpr int GetHeight() const
		{
			return VARIANT_HEIGHT;
		}

		static void StaticRelease();

		static constexpr int EXIST_FLAG = 1;

		BOOL IsBlockExist(int nX, int nY) const;

		void SetPos(int nX, int nY);
	private:
		void Init();
		void Print();
		void CreateVariant(char* pSource, char* pDest);
		static char acPreSet[SIZE_OF_PRESET_TABLE];
		static COLORREF aColorPreSet[TOTAL_SHAPES];
		static HBRUSH aBrushPreSet[TOTAL_SHAPES];

		static BOOL isInit;

		int m_nShapeType;

		DIR m_dirRotate;

		int m_x;

		int m_y;
	};
}

