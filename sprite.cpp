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
}

Sprite::~Sprite() {}

void Sprite::draw(Graphics &graphics, int x, int y) {
	SDL_Rect destinationRectangle = { x, y, this->_sourceRect.w * global::SPRITE_RATIO, 
				this->_sourceRect.h * global::SPRITE_RATIO };
	graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destinationRectangle);
}

void Sprite::update() {
}