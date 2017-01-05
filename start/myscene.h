/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file myscene.h
 *
 * @brief description of MyScene behavior.
 */

#ifndef MYSCENE_H
#define MYSCENE_H

#include <vector>
#include <rt2d/scene.h>
#include <rt2d/text.h>

#include "gridmaker.h"
#include "basicunit.h"

/// @brief The MyScene class is the Scene implementation
class MyScene : public Scene
{
public:
	/// @brief Constructor
	MyScene();
	/// @brief Destructor
	virtual ~MyScene();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

private:

	void actionMenu();

	/// @brief the grid which makes the level
	GridMaker* gridMaker;

	/// @brief a example unit to be replaced by the final version later
	BasicUnit* basicunit;

	/// @brief another example unit to be replaced later
	BasicUnit* unitTesting;

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

	bool menuOn;

protected:
	/// @brief a list of texts for the UI
	std::vector<Text*> text;
};

#endif /* SCENE00_H */
