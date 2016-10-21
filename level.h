#pragma once

#include <string>
#include <vector>
#include "global.h"
#include "tile.h"
#include "rectangle.h"


struct SDL_Texture;
struct SDL_Rect;
struct Tileset;
class Graphics;

class Level {
public:
	Level();
	Level(std::string mapName, Vector2 spawnPoint, Graphics &graphics);
	~Level();

	void update(int elapsedTime);
	void draw(Graphics &graphics);

	std::vector<Rectangle> checkTileCollision(const Rectangle &other);

	const Vector2 getPlayerSpawnPoint() const;

private:
	std::string _mapName;
	Vector2 _spawnPoint;

	//contine inaltime si latime pt toata harta, in pixeli
	Vector2 _size;
	Vector2 _tileSize;

	SDL_Texture* _backgroundTexture;

	std::vector<Tile> _tileList;
	std::vector<Tileset> _tilesets;
	std::vector<Rectangle> _collisionRects;
	
	/*void loadMap
	incarca harta in memorie
	*/
	void loadMap(std::string mapName, Graphics &graphics);
};

struct Tileset {
	//toata imaginea tileset-ului
	SDL_Texture* Texture;
	//primul gid din tileset
	int firstGid;

	Tileset() {
		this->firstGid = -1;
	}

	Tileset(SDL_Texture* texture, int firstGid) {
		this->Texture = texture;
		this->firstGid = firstGid;
	}
};