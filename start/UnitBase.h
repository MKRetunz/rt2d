#pragma once

#ifndef UNITBASE_H
#define UNITBASE_H

#include <rt2d/entity.h>
#include <iostream>
#include <string>
#include <sstream>
#include <rt2d/text.h>
#include "selector.h"


class UnitBase : public Entity
{
public:

	UnitBase();
	virtual ~UnitBase();

	virtual void update(float deltaTime);

	//Stats
	virtual void setStats(int Uclass);
	virtual void levelUp();

	//specifics
	int UnitClass; // 1 = soldier, 2 = mercenary, 3 = fighter

	//movement
	virtual void moveUp();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void moveDown();
	virtual void refresh();
	virtual void unSelect();
	virtual void collide(UnitBase* other);

	//combat
	virtual void attack(UnitBase* other);
	virtual void takeDamage(int amount);
	virtual void fight(UnitBase* other);
	virtual void animation();

	int lastposX;
	int lastposY;


	//Statistics
	std::string MsgName;
	std::string MsgLVL;
	std::string MsgEXP;
	std::string MsgHP;
	std::string MsgSTR;
	std::string MsgMAG;
	std::string MsgSKL;
	std::string MsgSPD;
	std::string MsgLCK;
	std::string MsgDEF;
	std::string MsgRES;
	std::string MsgMOV;
	std::string MsgCON;
	std::string MsgHIT;
	std::string MsgDGD;
	std::string MsgDMG;

	//Base stats
	int HP;
	int STR;
	int SKL;
	int SPD;
	int LCK;
	int DEF;
	int MOV = 6;
	int CON;

	//Weapon stats
	std::string wepName = "Placeholder";
	int uses;
	int wepMT;
	int wepHit;
	int wepWT;

	//Stat growths
	int HPGrow;
	int STRGrow;
	int SKLGrow;
	int SPDGrow;
	int LCKGrow;
	int DEFGrow;

	//Calculations
	int Hit = (SKL * 2) + (LCK / 2) + wepHit;
	int Dodge = (SPD * 2) + (LCK);
	int Damage = STR + wepMT;
	int EXP = 0;
	int Level = 1;

	//Name
	std::string name = "Placeholder";

	//Color
	bool team;

	bool statsSet = false;
	bool actionDone = false;
	bool selected = false;
	bool attacking = false;
	bool hitdetector = true;

	int MovOver = MOV;

	//Animation
	int frame = 0;
	float scounter = 0.0f;
	int fcounter = 0;

private:
	selector* selectorC;
	selector* selectorHit;

protected:
};

#endif /*UNITBASE_H*/

