#include "player.h"
#include "graphics.h"

namespace playerConstants {
	const float WALKSPEED = 0.2F;

	const float GRAVITY = 0.002F;
	const float GRAVITYCAP = 0.8F;
}

Player::Player () {}

Player::Player(Graphics &graphics, float x, float y) :
	AnimatedSprite(graphics, "content/sprites/MyChar.png", 0, 0, 16, 16, x, y, 100),
	_dx(0),
	_dy(0),
	_facing(RIGHT),
	_grounded(false)
{
	graphics.loadImage("Content/Sprites/MyChar.png");
	this->setupAnimations();
	this->playAnimation("RunRight");
}

void Player::setupAnimations() {
	this->addAnimation(1, 0, 0, "IdleLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(1, 0, 16, "IdleRight", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 0, "RunLeft", 16, 16, Vector2(0, 0));
	this->addAnimation(3, 0, 16, "RunRight", 16, 16, Vector2(0, 0));
	}

void Player::animationDone(std::string currentAnimation) {}

const float Player::getX() const {
	return this->_x;
}

const float Player::getY() const {
	return this->_y;
}

void Player::moveLeft() {
	this->_dx = -playerConstants::WALKSPEED;
	this->playAnimation("RunLeft");
	this->_facing = LEFT;
}

void Player::moveRight() {
	this->_dx = playerConstants::WALKSPEED;
	this->playAnimation("RunRight");
	this->_facing = RIGHT;
}

void Player::stopMoving() {
	this->_dx = 0;
	this->playAnimation(this->_facing == RIGHT ? "IdleRight" : "IdleLeft");
}
void Player::update(float elapsedTime) {
	//Gravitatie !

	if (this->_dy <= playerConstants::GRAVITYCAP) {
		this->_dy += playerConstants::GRAVITY * elapsedTime;
	}

	//Personajul se muta cu dx
	 this->_x += this->_dx * elapsedTime;

	 //Personajul se muta cu dy
	 this->_y += this->_dy * elapsedTime;

	AnimatedSprite::update(elapsedTime);
}

void Player::draw(Graphics &graphics) {
	AnimatedSprite::draw(graphics, this->_x, this->_y);
}