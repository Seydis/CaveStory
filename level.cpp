#include "stdafx.h"

#include <SDL.h>

#include "graphics.h"
#include "level.h"


Level::Level() {}

Level::Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics) :
	_mapName(mapName),
	_spawnPoint(spawnPoint),
	_size(Vector2(0, 0))
{
	this->loadMap(mapName, graphics);
}

Level::~Level(){}

void Level::loadMap(std::string mapName, Graphics &graphics) {
	//COD TEMPORAR
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
		graphics.loadImage("Content/Backgrounds/bkBlue.png"));
	this->_size = Vector2(1280, 960);
}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics) {
	SDL_Rect sourceRect = {0, 0, 64, 64};
	SDL_Rect destRect;

	// loop pt repetarea .png care constituie background
	for (int x = 0; x < this->_size.x / 64; x++) {
		for (int y = 0; y < this->_size.y / 64; y++) {
			destRect.x = x * 64 * global::SPRITE_RATIO;
			destRect.y = y * 64 * global::SPRITE_RATIO;
			destRect.w = 64 * global::SPRITE_RATIO;
			destRect.h = 64 * global::SPRITE_RATIO;
			graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
		}
			
	}
}