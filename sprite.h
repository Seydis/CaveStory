#pragma once

#include <SDL_image.h>

#include <string>

#include "rectangle.h"
#include "global.h"

class Graphics;

/* Sprite class
Contine informatii despre fiecare sprite folosit
*/

class Sprite {
public:
	Sprite();
	Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
		float posX, float posY);
	virtual ~Sprite();
	virtual void update();

	void draw(Graphics &graphics, int x, int y);

	const Rectangle getBoundingBox() const;
	const sides::Side getCollisionSide(Rectangle &other) const;

protected:
	SDL_Rect _sourceRect;
	SDL_Texture* _spriteSheet;
	float _x, _y;

	Rectangle _boundingBox;

private:
	
};