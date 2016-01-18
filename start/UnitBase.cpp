#include "UnitBase.h"


UnitBase::UnitBase()
{
	selectorC = new selector();
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

	if (this->UnitClass == 3) {
		if (this->team == true) {
			this->addSprite("assets/fighterv1.tga");
		}

		if (this->team == false) {
			this->addSprite("assets/fighterv2.tga");
		}
	}

	this->setStats(UnitClass);

	// #############################################################
	// Text display
	// #############################################################

	//name
	MsgName = "Name: ";
	MsgName.append(name);

	//Level
	MsgLVL = "Level: ";
	MsgLVL.append(std::to_string(Level));
	MsgLVL.append(", Experience: ");
	MsgLVL.append(std::to_string(EXP));
	MsgLVL.append("/50");

	//Hit Points
	MsgHP = "Hit points: ";
	MsgHP.append(std::to_string(HP));

	//Strength
	MsgSTR = "Strength: ";
	MsgSTR.append(std::to_string(STR));

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

	//Move
	MsgMOV = "Move: ";
	MsgMOV.append(std::to_string(MOV));

	//Con
	MsgCON = "Constitution: ";
	MsgCON.append(std::to_string(CON));

	//Hit
	MsgHIT = "Hit: ";
	MsgHIT.append(std::to_string(Hit));

	//Crit
	MsgCRT = "Crit: ";
	MsgCRT.append(std::to_string(Crit));

	//Dodge
	MsgDGD = "Dodge: ";
	MsgDGD.append(std::to_string(Dodge));

	MsgDMG = "Damage: ";
	MsgDMG.append(std::to_string(Damage));


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

	// ############################################################
	// Selector
	// ############################################################

	if (this->selected == true) {
		this->addChild(selectorC);
	}
	if (this->selected == false) {
		this->addChild(selectorC);
		this->removeChild(selectorC);
	}

	// ############################################################
	// Level up
	// ############################################################

	if (this->EXP >= 50) {
		this->EXP -= 50;
		this->levelUp();
	}
}

// ################################################################
// Class stats & level ups
// ################################################################

void UnitBase::setStats(int Uclass)
{
	if (statsSet == false) {
		if (Uclass == 1) {
			//Base stats
			this->HP = 28;
			this->STR = 15;
			this->SKL = 11;
			this->SPD = 11;
			this->LCK = 8;
			this->DEF = 13;
			this->CON = 11; //x2 = 22
			//this->MOV = 6; //x3 = 18
			//Total: 80

			//Weapon stats
			this->wepName = "Iron lance";
			this->uses = 45;
			this->wepMT = 7;
			this->wepHit = 80;
			this->wepCrit = 0;
			this->wepWT = 7;

			//Stat growths
			this->HPGrow = 70;
			this->STRGrow = 55;
			this->SKLGrow = 45;
			this->SPDGrow = 55;
			this->LCKGrow = 40;
			this->DEFGrow = 35;
			//Total: 300
		}

		if (Uclass == 2) {
			//Base stats
			this->HP = 31;
			this->STR = 13;
			this->SKL = 13;
			this->SPD = 14;
			this->LCK = 9;
			this->DEF = 11;
			this->CON = 10; //x2 = 20
			//this->MOV = 5; //x3 = 15
			//Total: 80

			//Weapon stats
			this->wepName = "Iron sword";
			this->uses = 46;
			this->wepMT = 5;
			this->wepHit = 90;
			this->wepCrit = 0;
			this->wepWT = 5;

			//Stat growths
			this->HPGrow = 65;
			this->STRGrow = 50;
			this->SKLGrow = 50;
			this->SPDGrow = 55;
			this->LCKGrow = 35;
			this->DEFGrow = 45;
			//Total: 300
		}

		if (Uclass == 3) {
			//Base stats
			this->HP = 34;
			this->STR = 17;
			this->SKL = 13;
			this->SPD = 8;
			this->LCK = 10;
			this->DEF = 11;
			this->CON = 14; //x2 = 28
			//this->MOV = 5; //x3 = 15
			//total: 80

			//Weapon stats
			this->wepName = "Iron axe";
			this->uses = 45;
			this->wepMT = 8;
			this->wepHit = 75;
			this->wepCrit = 0;
			this->wepWT = 10;

			//Stat growths
			this->HPGrow = 80;
			this->STRGrow = 70;
			this->SKLGrow = 50;
			this->SPDGrow = 20;
			this->LCKGrow = 25;
			this->DEFGrow = 55;
			//total 300
		}
		statsSet = true;
	}
}

void UnitBase::levelUp()
{
	if (rand() % 100 + 1 <= this->HPGrow) {
		this->HP += 1;
	}
	if (rand() % 100 + 1 <= this->STRGrow) {
		this->STR += 1;
	}
	if (rand() % 100 + 1 <= this->SKLGrow) {
		this->SKL += 1;
	}
	if (rand() % 100 + 1 <= this->SPDGrow) {
		this->SPD += 1;
	}
	if (rand() % 100 + 1 <= this->LCKGrow) {
		this->LCK += 1;
	}
	if (rand() % 100 + 1 <= this->DEFGrow) {
		this->DEF += 1;
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

void UnitBase::collide(UnitBase * other)
{
	if (this->position == other->position && this->selected == true) {
		if (this->team != other->team) {
			this->attack(other);
		}
		if (this->team == other->team) {
			this->position.x = this->lastposX;
			this->position.y = this->lastposY;
			this->MovOver++;
		}
	}
}

// #################################################################
// Combat functions
// #################################################################

void UnitBase::attack(UnitBase* other)
{
	this->MovOver++;

	this->fight(other);
	if (other->HP > 0) {
		other->fight(this);
		if (this->HP > 0) {
			if (this->SPD > other->SPD + 4) {
				this->fight(other);
			}
			if (other->SPD > this->SPD + 4) {
				other->fight(this);
			}
		}
	}
	
	this->position.x = this->lastposX;
	this->position.y = this->lastposY;
}

void UnitBase::takeDamage(int amount)
{
	amount -= this->DEF;
	if (amount <= 0) {
		amount = 0;
	}
	this->HP -= amount;
}

void UnitBase::fight(UnitBase * other)
{
	if (this->uses > 0) {
		if (rand() % 100 + 1 <= this->Hit - other->Dodge) {
			other->takeDamage(this->Damage);
			this->uses -= 1;
			this->EXP += 10;
			if (rand() % 100 + 1 <= this->Crit) {
				other->takeDamage(this->Damage);
			}
		}
		this->MovOver = 0;
	}
}
