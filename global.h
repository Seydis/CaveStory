#pragma once

namespace global {
	const int SCREEN_WIDTH = 640;
	const int SCREEEN_HEIGHT = 480;

	const float SPRITE_RATIO = 2.0;
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