#pragma once

#include "global.h"

class Rectangle {
public:
	Rectangle();

	Rectangle(int x, int y, int width, int height) :
		_x(x),
		_y(y),
		_width(width),
		_height(height)
	{}

	// Returneaza pozitia x-ului din centrul rectangle
	const int getCenterX() const { return this->_x + this->_width / 2; }
	// Returneaza pozitia y-ului din centrul rectangle
	const int getCenterY() const { return this->_y + this->_height / 2; }

	//Returneaza pozitia X din stanga sus
	const int getLeft() const { return this->_x; }
	//Returneaza pozitia X din dreapta sus
	const int getRight() const { return this->_x + this->_width; }
	//Returneaza pozitia Y din stanga sus
	const int getTop() const { return this->_y; }
	//Returneaza pozitia Y din stanga jos
	const int getBottom() const { return this->_y + this->_height; }

	const int getSide(const sides::Side side) const {
		return
			side == sides::LEFT ? this->getLeft() :
			side == sides::RIGHT ? this->getRight() :
			side == sides::TOP ? this->getTop() :
			side == sides::BOTTOM ? this->getBottom() :
			sides::NONE;
}

	//bool collidesWith
	//Primeste un alt Rectangle ca parametru si verifica daca Rectangle-ul al carui membru este
	// se ciocneste cu other
	const bool collidesWith(const Rectangle &other) const {
		//daca toate statementurile sunt adevarate, inseamna ca cele 2 Rectangle se suprapun, 
		//deci se returneaza true
		return
			this->getRight() >= other.getLeft() && this->getLeft() <= other.getRight() &&
			this->getTop() <= other.getBottom() && this->getBottom() >= other.getTop();

	}

	const bool isValidRectangle() const {
		return (this->_x >= 0 && this->_y >= 0 && this->_width >= 0 && this->_height >= 0);
	}

private:
	int _x, _y; 
	int _width, _height;
};