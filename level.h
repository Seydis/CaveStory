#pragma once

#include <string>
#include "global.h"

class Graphics;
struct SDL_Texture;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();

	void update(int elapsedTime);
	void draw(Graphics &graphics);

private:
	std::string _mapName;
	Vector2 _spawnPoint;

	//contine inaltime si latime pt toata harta, in pixeli
	Vector2 _size;

	SDL_Texture* _backgroundTexture;
	
	/*void loadMap
	incarca harta in memorie
	*/
	void loadMap(std::string mapName, Graphics &graphics);
};