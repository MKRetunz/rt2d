#include "UnitBase.h"


UnitBase::UnitBase()
{
	//Sprite
	this->addSprite("assets/soldierv1.tga");
}


UnitBase::~UnitBase()
{

}

void UnitBase::update(float deltaTime)
{
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

	//Move
	MsgCON = "Constitution: ";
	MsgCON.append(std::to_string(CON));

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

	//Dying
	if (this->HP <= 0) {
		this->position.x = 100000;
		removeChild(this);
	}
}

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

void UnitBase::refresh()
{
	this->MovOver = this->MOV;
	this->selected = false;
}

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
