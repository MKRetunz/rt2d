#pragma once

#ifndef UNITBASE_H
#define UNITBASE_H

#include <rt2d/entity.h>
#include <iostream>
#include <string>
#include <sstream>
#include <rt2d/text.h>


class UnitBase : public Entity
{
public:
	UnitBase();
	virtual ~UnitBase();

	virtual void update(float deltaTime);
	virtual void setStats(int Uclass);

	//specifics
	int UnitClass; // 1 = soldier, 2 = mercenary, 3 = fighter

	//movement
	virtual void moveUp();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void moveDown();
	virtual void refresh();
	virtual void unSelect();

	//combat
	virtual void attack(UnitBase* other);
	virtual void takeDamage(int amount);

	int lastposX;
	int lastposY;


	//Statistics
	std::string MsgName;
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

	//Base stats
	int HP = 28;
	int STR;
	int MAG;
	int SKL;
	int SPD;
	int LCK;
	int DEF;
	int RES;
	int MOV = 6;
	int CON;

	//Weapon stats
	std::string wepName = "Placeholder";
	int uses;
	int wepMT;
	int wepHit;
	int wepCrit;
	int wepWT;

	//Stat growths
	int HPGrow;
	int STRGrow;
	int MAGGrow;
	int SKLGrow;
	int SPDGrow;
	int LCKGrow;
	int DEFGrow;
	int RESGrow;

	//Calculations
	int Hit = (SKL * 2) + (LCK / 2) + wepHit;
	int Crit = (SKL / 2) + (LCK / 4) + wepCrit;
	int Dodge = (SPD * 2) + (LCK);
	int Damage = STR + wepMT;

	//Name
	std::string name = "Placeholder";

	//Color
	bool team;

	bool statsSet = false;
	bool actionDone = false;
	bool selected = false;

	int MovOver = MOV;

private:

protected:
};

#endif /*UNITBASE_H*/

