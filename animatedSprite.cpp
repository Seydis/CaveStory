#include "animatedSprite.h"
#include "global.h"
#include "sprite.h"
#include "graphics.h"

/* AnimatedSprite class
   face ca sprite-urile sa se poata mmisca
*/

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, const std::string &filePath, int sourceX, int sourceY,
	int width, int height, float posX, float posY, float timeToUpdate) :
		Sprite(graphics, filePath, sourceX, sourceY, width, height, posX, posY),
		_frameIndex(0), _timeToUpdate(timeToUpdate), _visible(true), _currentAnimationOnce(false), _currentAnimation("")
{}

void AnimatedSprite::addAnimation(int frames, int x, int y, std::string name, int width, int height, Vector2 offset) {
	std::vector<SDL_Rect> rectangles;
	for (int i = 0; i < frames; i++) {
		SDL_Rect rect = { (i + x) * width, y, width, height };
		rectangles.push_back(rect);
	}

	this->_animations.insert(std::pair<std::string, std::vector<SDL_Rect> >(name, rectangles));
	this->_offsets.insert(std::pair<std::string, Vector2>(name, offset));
}

void AnimatedSprite::resetAnimations() {
	this->_animations.clear();
	this->_offsets.clear();
}

void AnimatedSprite::playAnimation(std::string animation, bool once) {
	this->_currentAnimationOnce = once;
	if (this->_currentAnimation != animation) {
		this->_currentAnimation = animation;
		this->_frameIndex = 0;
	}
}

