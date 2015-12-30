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
		selected = false;
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
}