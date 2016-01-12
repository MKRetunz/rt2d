#include "UnitBase.h"


UnitBase::UnitBase()
{
	
}


UnitBase::~UnitBase()
{

}

void UnitBase::update(float deltaTime)
{
	// #############################################################
	// Sprites and classes
	// #############################################################

	//Soldier
	if (this->UnitClass == 1) {
		if (this->team == true) {
			this->addSprite("assets/soldierv1.tga");
		}

		if (this->team == false) {
			this->addSprite("assets/soldierv2.tga");
		}
	}

	if (this->UnitClass == 2) {
		if (this->team == true) {
			this->addSprite("assets/mercenaryv1.tga");
		}

		if (this->team == false) {
			this->addSprite("assets/mercenaryv2.tga");
		}
	}

	this->setStats(UnitClass);

	// #############################################################
	// Text display
	// #############################################################

	//name
	MsgName = "Name: ";
	MsgName.append(name);

	//Hit Points
	MsgHP = "Hit points: ";
	MsgHP.append(std::to_string(HP));

	//Strength
	MsgSTR = "Strength: ";
	MsgSTR.append(std::to_string(STR));

	//Magic
	MsgMAG = "Magic: ";
	MsgMAG.append(std::to_string(MAG));

	//Skill
	MsgSKL = "Skill: ";
	MsgSKL.append(std::to_string(SKL));

	//Speed
	MsgSPD = "Speed: ";
	MsgSPD.append(std::to_string(SPD));

	//Luck
	MsgLCK = "Luck: ";
	MsgLCK.append(std::to_string(LCK));

	//Defense
	MsgDEF = "Defense: ";
	MsgDEF.append(std::to_string(DEF));

	//Resistance
	MsgRES = "Resistance: ";
	MsgRES.append(std::to_string(RES));

	//Move
	MsgMOV = "Move: ";
	MsgMOV.append(std::to_string(MOV));

	//Con
	MsgCON = "Constitution: ";
	MsgCON.append(std::to_string(CON));

	// #############################################################
	// Calculations
	// #############################################################

	//Calculations
	this->Hit = (SKL * 2) + (LCK / 2) + wepHit;
	this->Crit = (SKL / 2) + (LCK / 4) + wepCrit;
	this->Dodge = (SPD * 2) + (LCK);
	this->Damage = STR + wepMT;

	// #############################################################
	// Preventing movement after movement has been depleted
	// #############################################################

	if (MovOver == 0) {
		this->selected = false;
	}
	
	//############################################
	//Positional Correction
	//############################################

	//Horizontal border walls
	if (this->position.x <= 384 || this->position.x >= 832) {
		this->position.x = this->lastposX;
	}

	//Vertical border walls
	if (this->position.y <= 44 || this->position.y >= 620) {
		this->position.y = this->lastposY;
	}

	//Walls in the stage
	//Top half of stage
	if (this->position.y >= 44 + -32 && this->position.y <= 236 + 32 && this->position.x >= 474 + -32 && this->position.x <= 474 + 32 || this->position.y >= 44 + -32 && this->position.y <= 236 + 32 && this->position.x >= 730 + -32 && this->position.x <= 730 + 32 || this->position.y >= 236 + -32 && this->position.y <= 236 + 32 && this->position.x >= 602 + -32 && this->position.x <= 730 + 32) {
		this->position.y = this->lastposY;
		this->position.x = this->lastposX;
		MovOver++;
	}

	//Bottom half of stage
	if (this->position.y >= 428 + -32 && this->position.y <= 620 + 32 && this->position.x >= 474 + -32 && this->position.x <= 474 + 32 || this->position.y >= 428 + -32 && this->position.y <= 620 + 32 && this->position.x >= 730 + -32 && this->position.x <= 730 + 32 || this->position.y >= 428 + -32 && this->position.y <= 428 + 32 && this->position.x >= 538 + -32 && this->position.x <= 602 + 32) {
		this->position.y = this->lastposY;
		this->position.x = this->lastposX;
		MovOver++;
	}

	// #############################################################
	// Dying
	// #############################################################

	if (this->HP <= 0) {
		this->position.x = 100000;
		removeChild(this);
	}
}

// ################################################################
// Change stats depending on class
// ################################################################

void UnitBase::setStats(int Uclass)
{
		if (Uclass == 1) {
			//Base stats
			this->STR = 15;
			this->MAG = 4;
			this->SKL = 12;
			this->SPD = 12;
			this->LCK = 12;
			this->DEF = 10;
			this->RES = 7;
			this->CON = 11;

			//Weapon stats
			this->wepName = "Iron lance";
			this->uses = 45;
			this->wepMT = 7;
			this->wepHit = 80;
			this->wepCrit = 0;
			this->wepWT = 7;

			//Stat growths
			this->HPGrow = 70;
			this->STRGrow = 65;
			this->MAGGrow = 5;
			this->SKLGrow = 45;
			this->SPDGrow = 60;
			this->LCKGrow = 40;
			this->DEFGrow = 35;
			this->RESGrow = 25;
		}

		if (Uclass == 2) {
			//Base stats
			this->STR = 16;
			this->MAG = 2;
			this->SKL = 12;
			this->SPD = 13;
			this->LCK = 8;
			this->DEF = 13;
			this->RES = 3;
			this->CON = 13;

			//Weapon stats
			this->wepName = "Iron sword";
			this->uses = 46;
			this->wepMT = 5;
			this->wepHit = 90;
			this->wepCrit = 0;
			this->wepWT = 5;

			//Stat growths
			this->HPGrow = 80;
			this->STRGrow = 60;
			this->MAGGrow = 10;
			this->SKLGrow = 50;
			this->SPDGrow = 55;
			this->LCKGrow = 35;
			this->DEFGrow = 45;
			this->RESGrow = 10;
		}
}

// ################################################################
// Movement functions
// ################################################################

void UnitBase::moveUp()
{
	if (this->selected == true && MovOver > 0) {
		this->lastposX = this->position.x;
		this->lastposY = this->position.y;
		this->position.y -= 64;
		this->MovOver--;
		
	}
}

void UnitBase::moveLeft()
{
	if (this->selected == true == true && MovOver > 0) {
		this->lastposX = this->position.x;
		this->lastposY = this->position.y;
		this->position.x -= 64;
		this->MovOver--;
	}
}

void UnitBase::moveRight()
{
	if (this->selected == true == true && MovOver > 0) {
		this->lastposX = this->position.x;
		this->lastposY = this->position.y;
		this->position.x += 64;
		this->MovOver--;
	}
}

void UnitBase::moveDown()
{
	if (this->selected == true == true && MovOver > 0) {
		this->lastposX = this->position.x;
		this->lastposY = this->position.y;
		this->position.y += 64;
		this->MovOver--;
	}
}

// #################################################################
// Refill movement and unselect
// #################################################################

void UnitBase::refresh()
{
	this->MovOver = this->MOV;
	this->selected = false;
}

void UnitBase::unSelect()
{
	this->selected = false;
}

// #################################################################
// Combat functions
// #################################################################

void UnitBase::attack(UnitBase* other)
{
	if (this->position == other->position) {
		if (rand() % 100 + 1 <= this->Hit - other->Dodge) {
			other->takeDamage(this->Damage);
		}
		if (other->HP >= 0) {
			if (rand() % 100 + 1 <= other->Hit - this->Dodge) {
				this->takeDamage(other->Damage);
			}
			if (this->HP >= 0) {
				if (this->SPD >= other->SPD + 4) {
					if (rand() % 100 + 1 <= this->Hit - other->Dodge) {
						other->takeDamage(this->Damage);
					}
				}	
				if (other->SPD >= this->SPD + 4) {
					if (rand() % 100 + 1 <= other->Hit - this->Dodge) {
						this->takeDamage(other->Damage);
					}
				}
			}
		}
		this->position.x = this->lastposX;
		this->position.y = this->lastposY;
		this->MovOver = 0;
	}
}

void UnitBase::takeDamage(int amount)
{
	amount -= this->DEF;
	if (amount <= 0) {
		amount = 0;
	}
	this->HP -= amount;
}
