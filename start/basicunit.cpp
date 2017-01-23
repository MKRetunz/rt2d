#include "basicunit.h"

BasicUnit::BasicUnit() : Entity()
{
	cs = new ClassStats();

	selected = false;

	unitTeam = false;

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

void BasicUnit::makeUnit()
{
	HitPoints = cs->GetStat(0, unitClass);
	Damage = cs->GetStat(1, unitClass);
	Hit = cs->GetStat(2, unitClass);
	Avoid = cs->GetStat(3, unitClass);
	Defense = cs->GetStat(4, unitClass);
	Move = cs->GetStat(5, unitClass);
	cs->GetSprite(unitClass, this, unitTeam);
}
