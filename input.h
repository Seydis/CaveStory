#pragma once

#include <map>
#include <SDL.h>

/* Input class
contine starea in care se afla tastatura
*/
class Input {
public:
	//functie apelata la inceputul fiecarui frame
	//pt a reseta starea tastaturii
	void beginNewFrame();
	//functie care se apeleaza cand nu se mai apasa pe o tasta
	void keyUpEvent(const SDL_Event& event);
	//functie apelata atunci cand se apasa o tasta
	void keyDownEvent(const SDL_Event& event);


	//functii de verificare
	bool wasKeyPressed(SDL_Scancode key);
	bool wasKeyReleased(SDL_Scancode key);
	bool isKeyHeld(SDL_Scancode key);
private:
	std::map<SDL_Scancode, bool> _heldKeys;
	std::map<SDL_Scancode, bool> _pressedKeys;
	std::map<SDL_Scancode, bool> _releasedKeys;

};