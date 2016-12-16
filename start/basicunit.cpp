#include "basicunit.h"

BasicUnit::BasicUnit() : Entity()
{
	this->addSprite("assets/mercenaryv1.tga");

	selected = false;
}


BasicUnit::~BasicUnit()
{

}

void BasicUnit::update(float deltaTime)
{

}
