#pragma once

#include <string>
#include "animatedSprite.h"
#include "global.h"


class Graphics;

class Player : public AnimatedSprite {
public:
	Player();
	Player(Graphics &graphics, Vector2 spawnPoint);
	
	void update(float elapsedTime);
	void draw(Graphics &graphics);

	/*	void moveLeft
		void moveRight
		misca Player la stanga, respectiv la dreapta, cu _dx
	*/
	void moveLeft();
	void moveRight();

	/*	void stopMoving
		opreste miscarea lui Quote si apeleaza animatia de Idle
	*/
	void stopMoving();

	virtual void animationDone(std::string currentAnimation);
	virtual void setupAnimations();

	void handleTileCollisions(std::vector <Rectangle> &others);

	const float getX() const;
	const float getY() const;

private:
	float _dx, _dy;

	Direction _facing;

	bool _grounded;
};