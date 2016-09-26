#pragma once

#include <map>

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;
struct SDL_Texture;
// forward declaring, pt a nu include sdl in header

/*
Clasa Graphics
se ocupa cu tot ceea ce inseamna grafica in joc
*/
class Graphics {
public:
	Graphics();
	~Graphics();

	/* SDL_Surface* loadImage
	incarca o image in .spriteSheets map, daca nu exista deja,
	astfel incat fiecare imagine se incarca o singura data.
	Intoarce imaginea din map, indiferent daca a fost sau nu incarcata
	*/
	SDL_Surface* loadImage(const std::string &filePath);

	/*	void blitSurface
	deseneaza o textura intr-o anume parte a ferestrei jocului
	*/
	void blitSurface(SDL_Texture* source, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	/*
	void flip
	randeaza in fereastra
	*/
	void flip();

	/*
	void clear
	goleste fereastra
	*/
	void clear();

	/*
	SDL_Renderer* getRenderer
	returneaza renderer
	*/
	SDL_Renderer* getRenderer() const;
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	std::map<std::string, SDL_Surface*> _spriteSheets;
};
