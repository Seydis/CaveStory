#include "stdafx.h"

#include <SDL.h>

#include "tinyxml2.h"

#include "graphics.h"
#include "level.h"

#include <algorithm>
#include <sstream>
#include <cmath>

using namespace tinyxml2;

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
	/*COD TEMPORAR
	this->_backgroundTexture = SDL_CreateTextureFromSurface(graphics.getRenderer(),
	graphics.loadImage("Content/Backgrounds/bkBlue.png"));
	this->_size = Vector2(1280, 960);
	*/

	
	//Parsam .tmx
	XMLDocument doc;
	std::stringstream ss;
	ss << "Content/Maps/" << mapName << ".tmx";
	//tinyxml2 e scrisa in c => functiile primesc ca argument un c string
	doc.LoadFile(ss.str().c_str());

	XMLElement* mapNode = doc.FirstChildElement("map");

	// Parsam width si height pt harta, pe care le stocam in _size
	int width, height;
	mapNode->QueryIntAttribute("width", &width);
	mapNode->QueryIntAttribute("height", &height);
	this->_size = Vector2(width, height); 

	// Parsam width si height pt fiecare tile, pe care le stocam in _tilesize
	int tilewidth, tileheight;
	mapNode->QueryIntAttribute("tilewidth", &tilewidth);
	mapNode->QueryIntAttribute("tileheight", &tileheight);
	this->_tileSize = Vector2(tilewidth, tileheight);

	// Parsam tilesets
	XMLElement* pTileset = mapNode->FirstChildElement("tileset");
	if (pTileset != NULL) {
		while (pTileset) {
			int firstgid;
			const char* source = pTileset->FirstChildElement("image")->Attribute("source");

			char* path;
			std::stringstream ss;
			ss << source; 

			pTileset->QueryIntAttribute("firstgid", &firstgid);
			SDL_Texture* texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(ss.str()));
			this->_tilesets.push_back(Tileset(texture, firstgid));
			
			pTileset = pTileset->NextSiblingElement("tileset");
		}
	}

	// Parsam layerele din .tmx, conform cu ce am facut in Tiles
	XMLElement* pLayer = mapNode->FirstChildElement("layer");
	if (pLayer != NULL) {
		while (pLayer) {
			//Parsam data
			XMLElement* pData = pLayer->FirstChildElement("data");
			if (pData != NULL) {
				while (pData) {
					// Parsam tile
					XMLElement* pTile = pData->FirstChildElement("tile");
					if (pTile != NULL) {
						int tileCounter = 0;
						while (pTile) {
							// Parsam fiecare tile, pe rand
							// Daca gid = 0 -> nu a fost desenat nimic pe Layerul respectiv in dreptul acelui tile

							if (pTile->IntAttribute("gid") == 0) {
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
									break;
							}

							// Parsam tilesetul din care a fost luat acel gid
							int gid = pTile->IntAttribute("gid");
							Tileset tls;
							for (int i = 0; i < this->_tilesets.size(); i++) {
								if (this->_tilesets.at(i).firstGid <= gid) {
									// gid-ul se afla in acest tileset
									tls = this->_tilesets.at(i);
									break;
								}
							}

							if (tls.firstGid == -1) {
								//Nu am gasit niciun tileset pt gid-ul respectiv;
								tileCounter++;
								if (pTile->NextSiblingElement("tile")) {
									pTile = pTile->NextSiblingElement("tile");
									continue;
								}
								else
									break;

							}

							//Aflam pozitia tile-ului in cadrul Level
							int xx = 0, yy = 0;
							xx = tileCounter % width;
							xx *= tilewidth;
							yy += tileheight * (tileCounter / width);

							Vector2 finalTilePosition = Vector2(xx, yy);

							//Calcul pozitia tile-ului in tileset
							int tilesetWidth, tilesetHeight;
							SDL_QueryTexture(tls.Texture, NULL, NULL, &tilesetWidth, &tilesetHeight);
							int tilesetxx = gid % (tilesetWidth / tilewidth) - 1;
							tilesetxx *= tilewidth;
							int tilesetyy = 0;
							int amount = (gid / (tilesetWidth / tilewidth));
							tilesetyy = tileheight * amount;
							Vector2 finalTilesetPosition = Vector2(tilesetxx, tilesetyy);

							//Construim tileul si il adaugam in vectorul de tile-uri al levelului
							Tile tile(tls.Texture, Vector2(tilewidth, tileheight), finalTilesetPosition, finalTilePosition);
							this->_tileList.push_back(tile);
							tileCounter++;

							pTile = pTile->NextSiblingElement("tile");
						}
					}

					pData = pData->NextSiblingElement("data");
				}
			}

			pLayer = pLayer->NextSiblingElement("Layer");
		}
	}
}

void Level::update(int elapsedTime) {

}

void Level::draw(Graphics &graphics) {
	/*SDL_Rect sourceRect = {0, 0, 64, 64};
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
	*/

	for (int i = 0; i < this->_tileList.size(); i++)
		this->_tileList.at(i).draw(graphics);
}