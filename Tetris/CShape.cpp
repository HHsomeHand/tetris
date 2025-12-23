#include "CShape.h"
#include "corn_debug.h"
#include "Vector2D.h"
#include <time.h>

namespace corn {

	CShape::CShape():
		m_x(0), m_y(0)
	{
		Init();
		
		m_nShapeType = rand() % TOTAL_SHAPES;
		m_dirRotate = (DIR)(rand() % DIR::DIR_COUNT);
	}

	CShape::CShape(int nShape, DIR dirRotate) :
		m_x(0), m_y(0)
	{
		m_nShapeType = nShape;
		m_dirRotate = dirRotate;
	}

	char CShape::GetPreSetChar(int nShape, int nVariant, int nX, int nY)
	{
		return acPreSet[
			nShape * SIZE_OF_PER_SHAPE +
			nVariant * SIZE_OF_PER_VARIANT +
			nY * VARIANT_WIDTH + 
			nX
		];
	}

	char CShape::GetCurrentChar(int nX, int nY) const
	{
		return GetPreSetChar(m_nShapeType, m_dirRotate, nX, nY);
	}

	void CShape::StaticRelease()
	{
		if (!isInit) {
			return;
		}

		for (int i = 0; i < TOTAL_SHAPES; i++) {
			::DeleteObject(aBrushPreSet[i]);
		}
	}

	BOOL CShape::IsBlockExist(int nX, int nY) const
	{
		return GetCurrentChar(nX, nY) == EXIST_FLAG;
	}

	void CShape::SetPos(int nX, int nY)
	{
		SetX(nX);
		SetY(nY);
	}

	void CShape::Init()
	{
		if (isInit) {
			return;
		};

		char acTmpPreSet[SIZE_OF_PRESET_TABLE];
		memcpy(acTmpPreSet, acPreSet, sizeof(acPreSet));

		char* pSource = acTmpPreSet;
		char* pDest = acPreSet;
		for (int nShape = 0; nShape < TOTAL_SHAPES; nShape++) {
			CreateVariant(pSource, pDest);

			pSource += SIZE_OF_PER_VARIANT;
			pDest += SIZE_OF_PER_SHAPE;
		}

		Print();

		for (int i = 0; i < TOTAL_SHAPES; i++) {
			aBrushPreSet[i] = CreateSolidBrush(aColorPreSet[i]);
		}

		isInit = true;
	}

	void CShape::Print()
	{
		for (int nShape = 0; nShape < TOTAL_SHAPES; nShape++) {
			for (int nVariant = 0; nVariant < NUMBER_OF_VARIANTS_SHAPE_CONTAIN; nVariant++) {
				for (int nHeight = 0; nHeight < VARIANT_HEIGHT; nHeight++) {
					for (int nWidth = 0; nWidth < VARIANT_WIDTH; nWidth++) {
						dbg_printf("%d ", GetPreSetChar(nShape, nVariant, nWidth, nHeight));
					}
					dbg_printf("\n");
				}
				dbg_printf("\n");
			}
			dbg_printf("\n");
			dbg_printf("\n");
		}
	}

	void CShape::CreateVariant(char* pSource, char* pDest)
	{
		memcpy(pDest, pSource, SIZE_OF_PER_VARIANT);

		pSource = pDest;

		pDest += SIZE_OF_PER_VARIANT;
		
		for (int nVariant = 1; nVariant < NUMBER_OF_VARIANTS_SHAPE_CONTAIN; nVariant++) {
			for (int nHeight = 0; nHeight < VARIANT_HEIGHT; nHeight++) {
				for (int nWidth = 0; nWidth < VARIANT_WIDTH; nWidth++) {
					pDest[nHeight * VARIANT_WIDTH + nWidth] = pSource[(VARIANT_WIDTH - 1 - nWidth) * VARIANT_HEIGHT + nHeight];
				}
			}
			pSource = pDest;

			pDest += SIZE_OF_PER_VARIANT;
		}
	}
	
	char CShape::acPreSet[SIZE_OF_PRESET_TABLE] = {
		0, 0, 1, 0,
		0, 1, 1, 1,
		0, 0, 0, 0,
		0, 0, 0, 0,
		
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,
		0, 1, 0, 0,

		0, 1, 1, 1,
		0, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,

		0, 0, 0, 0,
		0, 1, 1, 0,
		0, 1, 1, 0,
		0, 0, 0, 0
	};

	COLORREF CShape::aColorPreSet[TOTAL_SHAPES] = {
			RGB(102, 153, 204), // 柔和蓝色（I）
			RGB(102, 204, 204), // 柔和青色（O）
			RGB(153, 204, 102), // 柔和绿色（S）
			
			RGB(204, 204, 102), // 柔和黄色（Z）
			/*
			RGB(204, 153, 102), // 柔和橙色（L）
			RGB(204, 102, 102), // 柔和红色（J）
			RGB(153, 102, 204), // 柔和紫色（T）

			RGB(180, 180, 180)  // 柔和灰色（备用 / 特殊）
			*/

	};

	BOOL CShape::isInit = false;

	int CShape::GetX() const 
	{
		return m_x;
	}

	void CShape::SetX(int x)
	{
		m_x = x;
	}

	int CShape::GetY() const
	{
		return m_y;
	}

	void CShape::SetY(int y)
	{
		m_y = y;
	}
	void CShape::Move(Vector2D v)
	{
		SetX(GetX() + v.x);
		SetY(GetY() + v.y);
	}


	CShape::DIR CShape::RotateRight()
	{
		DIR targetDir = (CShape::DIR)((GetRotate() + 1) % DIR::DIR_COUNT);

		SetRotate(targetDir);

		return targetDir;
	}
	void CShape::SetRotate(DIR rotate)
	{
		m_dirRotate = rotate;
	}
	CShape::DIR CShape::GetRotate() const
	{
		return m_dirRotate;
	}

	COLORREF CShape::GetColor() const
	{
		return aColorPreSet[GetShapeType()];
	}

	int CShape::GetShapeType() const
	{
		return m_nShapeType;
	}

	HBRUSH CShape::GetBrush() const
	{
		return aBrushPreSet[GetShapeType()];
	}

	HBRUSH CShape::aBrushPreSet[TOTAL_SHAPES] = { 0 };

}