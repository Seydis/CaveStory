#pragma once

#include <map>
#include <vector>
#include <string>

#include "sprite.h"
#include "global.h"

class Graphics;

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite();
	AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
		int width, int height, float posX, float posY, float timeToUpdate);
	
	/* void playAnimation
		executa animatia daca nu se executa deja
	*/
	void playAnimation(std::string animation, bool playonce = false);
	//bool once = false -> optional parameter, nu e obligatoriu de trecut ca parametru la apel, este considerat default false

	void update(int elapsedTime);

	/* void draw
		deseneaza sprite-ul pe ecran
	*/
	void draw(Graphics &graphics, int x, int y);

protected:
	double _timeToUpdate;
	bool _currentAnimationOnce;
	std::string _currentAnimation;

	/*
		void addAnimation
		adauga o animatie in map-ul de animatii al unui anume spirte
	*/
	void addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset);

	void resetAnimations();

	/* void stopAnimation
		opreste animatia curenta
	*/
	void stopAnimation();

	/* void setVisible
		schimba vizibilitatea spriteului animat
	*/
	void setVisible(bool visible);

	/* void animationDone
		contine ce se intampla la sfarsitul unei anume animatii
	*/
	virtual void animationDone(std::string currentAnimation) = 0;

	/* void setupAnimations
	functie necesara care seteaza animatiile dintr-un sprite
	*/
	virtual void setupAnimations() = 0;
private:
	//fiecare vector de SDL_Rect contine partea din sprite necesara pt animatia in cauza
	std::map<std::string, std::vector<SDL_Rect> > _animations;
	std::map<std::string, Vector2> _offsets;

	int _frameIndex;
	double _timeElapsed;
	bool _visible;
};