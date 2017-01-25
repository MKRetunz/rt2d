#include "basicunit.h"

BasicUnit::BasicUnit() : Entity()
{
	cs = new ClassStats();

	selected = false;

	unitTeam = false;

	attacking = false;

	scounter = 0.0f;

	frame = 0;

	fcounter = 0;

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
	if (this->attacking == true) {
		scounter += deltaTime;
		if (frame > 2) { frame = 0; }
		if (scounter > 1.0f && fcounter < 3) {
			frame++;
			scounter = 0.0f;
			fcounter++;
		}
		if (fcounter == 3) {
			this->attacking = false;
			frame = 0;
			fcounter = 0;
		}
	}

	this->sprite()->frame(frame);

	if (this->HitPoints <= 0) {
		this->position.x += 1000;
		parent()->removeChild(this);
	}
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

void BasicUnit::attack(BasicUnit * unit)
{
	int totalHit = this->Hit - unit->Avoid;
	int totalDamage = this->Damage - unit->Defense;

	if ((rand() % 100 + 1) <= totalHit) {
		unit->HitPoints -= totalDamage;
	}

	attacking = true;
}
