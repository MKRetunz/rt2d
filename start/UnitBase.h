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

	//movement
	virtual void moveUp();
	virtual void moveLeft();
	virtual void moveRight();
	virtual void moveDown();
	virtual void refresh();

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
	int STR = 15;
	int MAG = 4;
	int SKL = 12;
	int SPD = 12;
	int LCK = 12;
	int DEF = 10;
	int RES = 7;
	int MOV = 6;
	int CON = 11;

	//Weapon stats
	std::string wepName = "Iron lance";
	int uses = 45;
	int wepMT = 7;
	int wepHit = 80;
	int wepCrit = 0;
	int wepWT = 7;

	//Stat growths
	int HPGrow = 70;
	int STRGrow = 65;
	int MAGGrow = 5;
	int SKLGrow = 45;
	int SPDGrow = 60;
	int LCKGrow = 40;
	int DEFGrow = 35;
	int RESGrow = 25;

	//Calculations
	int Hit = (SKL * 2) + (LCK / 2) + wepHit;
	int Crit = (SKL / 2) + (LCK / 4) + wepCrit;
	int Dodge = (SPD * 2) + (LCK);
	int Damage = STR + wepMT;
	int gridrange = MOV * 64;

	//Name
	std::string name = "Paladius";

	bool actionDone = false;
	bool selected = false;

	int MovOver = MOV;

private:

protected:
};

#endif /*UNITBASE_H*/

