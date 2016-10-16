#pragma once

/* Contine constante globale si structuri de date custom
*/
namespace global {
	const int SCREEN_WIDTH = 640;
	const int SCREEEN_HEIGHT = 480;

	const float SPRITE_RATIO = 2.0;
}

namespace sides {
	enum Side {
		TOP,
		BOTTOM,
		LEFT,
		RIGHT,
		NONE
	};

	inline Side getOppositeSide(Side side) {
		return 
			side == TOP ? BOTTOM:
			side == BOTTOM ? TOP:
			side == LEFT ? RIGHT:
			side == RIGHT ? LEFT:
			NONE;
	}
}

struct Vector2 {
	int x;
	int y;
	Vector2() : x(0), y(0) {};
	Vector2(int x, int y) : x(x), y(y) {};

	Vector2 zero() {
		return Vector2(0, 0);
	}
};

enum Direction {
	LEFT, RIGHT, UP, DOWN
};