#include "basicunit.h"

BasicUnit::BasicUnit() : Entity()
{
	cs = new ClassStats();

	selected = false;

	unitClass = 0;

	HitPoints = 10;

	Damage = 0;

	Hit = 0;

	Avoid = 0;

	Defense = 0;

	Move = 6;
}


BasicUnit::~BasicUnit()
{

}

void BasicUnit::update(float deltaTime)
{

}
