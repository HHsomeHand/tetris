#pragma once

namespace corn {
	struct Vector2D
	{
		int x;
		int y;
	};

	constexpr Vector2D VECTOR2D_UP = {
		.x = 0,
		.y = -1,
	};

	constexpr Vector2D VECTOR2D_DOWN = {
		.x = 0,
		.y = 1,
	};

	constexpr Vector2D VECTOR2D_LEFT = {
		.x = -1,
		.y = 0,
	};

	constexpr Vector2D VECTOR2D_RIGHT = {
		.x = 1,
		.y = 0,
	};
}
