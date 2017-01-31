/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file gamescene.h
 *
 * @brief description of gamescene behavior.
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <vector>
#include <rt2d/scene.h>
#include <rt2d/text.h>

#include "gridmaker.h"
#include "basicunit.h"

/// @brief The gamescene class is the Scene implementation
class GameScene : public Scene
{
public:
	/// @brief Constructor
	GameScene();
	/// @brief Destructor
	virtual ~GameScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:

	/// @brief when called the menu gets turned on or off
	/// @return void
	void actionMenu();

	/// @brief adds a menu of the called unit, displaying its stats
	/// @param BasicUnit supplies the stats to be showcased
	/// @return void
	void unitMenu(BasicUnit* b);

	/// @brief the grid which makes the level
	GridMaker* gridMaker;

	/// @brief a red side unit of the mercenary class
	BasicUnit* mercR;

	/// @brief a red side unit of the soldier class
	BasicUnit* soldierR;

	/// @brief a red side unit of the fighter class
	BasicUnit* fighterR;

	/// @brief a blue side unit of the mercenary class
	BasicUnit* mercB;

	/// @brief a blue side unit of the soldier class
	BasicUnit* soldierB;
	
	/// @brief a blue side unit of the fighter class
	BasicUnit* fighterB;

	/// @brief the list of units
	std::vector<BasicUnit*> unitList;

	/// @brief the right side of a unit's sprite
	int unitspriteR;

	/// @brief the left side of a unit's sprite
	int unitspriteL;

	/// @brief the bottom side of a unit's sprite
	int unitspriteD;

	/// @brief the top side of a unit's sprite
	int unitspriteT;

	int unitTracker;

	/// @brief a bool to turn the menu on and off
	bool menuOn;

	/// @brief a bool to track which turn it is
	bool currentTurn;

protected:
	/// @brief a list of texts for the UI
	std::vector<Text*> text;
};

#endif /* GAMESCENE_H */
