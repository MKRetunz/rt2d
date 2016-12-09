#include "basicunit.h"

BasicUnit::BasicUnit() : Entity()
{
	this->addSprite("assets/grayscale.tga");
}


BasicUnit::~BasicUnit()
{

}

void BasicUnit::update(float deltaTime)
{

}

void BasicUnit::moveUnit(int input)
{
	if (input == 0) {
		this->position.y -= 64;
	}
	else if (input == 1) {
		this->position.x -= 64;
	}
	else if (input == 2) {
		this->position.y += 64;
	}
	else if (input == 3) {
		this->position.x += 64;
	}
}
