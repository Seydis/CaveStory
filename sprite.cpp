#include "stdafx.h"
#include "sprite.h"
#include "graphics.h"
#include "global.h"
#include <iostream>

Sprite::Sprite() {}

Sprite::Sprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY, int width, int height,
	float posX, float posY) :_x(posX), _y(posY) {

	this->_sourceRect.x = sourceX;
	this->_sourceRect.y = sourceY;
	this->_sourceRect.w = width;
	this->_sourceRect.h = height;

	this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filePath));

	if (this->_spriteSheet == NULL) {
		std::cout << "Eroare ! Nu am incarcat nicio imagine, eroare: " << IMG_GetError() << std::endl;
	}

	this->_boundingBox = Rectangle(this->_x, this->_y, width * global::SPRITE_RATIO, height * global::SPRITE_RATIO);
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
	SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w * global::SPRITE_RATIO, 
				this->_sourceRect.h * global::SPRITE_RATIO };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update() {
	this->_boundingBox = Rectangle(this->_x, this->_y, this->_sourceRect.w * global::SPRITE_RATIO, this->_sourceRect.h * global::SPRITE_RATIO);
}

const Rectangle Sprite::getBoundingBox() const {
	return this->_boundingBox;
}

//Side getCollisionSide
//Returneaza latura pe care s-a produs coliziunea
const sides::Side Sprite::getCollisionSide(Rectangle &other) const {
	//Verificam cum exact se suprapun dreptunghiurile
	int amRight, amLeft, amTop, amBottom;
	amRight = this->getBoundingBox().getRight() - other.getLeft();
	amLeft = other.getRight() - this->getBoundingBox().getLeft();
	amTop = other.getBottom() - this->getBoundingBox().getTop();
	amBottom = this->getBoundingBox().getBottom() - other.getTop();

	int vals[4] = { abs(amRight), abs(amLeft), abs(amTop), abs(amBottom) };
	int lowest = vals[0];

	for (int i = 0; i < 4; i++) {
		if (vals[i] < lowest)
			lowest = vals[i];
	}

	return
		lowest == abs(amRight) ? sides::RIGHT :
		lowest == abs(amLeft) ? sides::LEFT :
		lowest == abs(amTop) ? sides::TOP :
		lowest == abs(amBottom) ? sides::BOTTOM :
		sides::NONE;
}