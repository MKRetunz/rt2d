#include "UnitBase.h"


UnitBase::UnitBase()
{
	//Sprite
	this->addSprite("assets/soldierv1.tga");

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
}


UnitBase::~UnitBase()
{
}

void UnitBase::update(float deltaTime)
{

}

void UnitBase::mouseOver()
{
	this->position.x -= 64;
}
