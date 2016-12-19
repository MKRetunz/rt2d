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

/// @brief The MyScene class is the Scene implementation.
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
	/// @brief the grid which makes the level.
	GridMaker* gridMaker;
	BasicUnit* basicunit;
	BasicUnit* unitTesting;
	std::vector<BasicUnit*> unitList;

protected:
	std::vector<Text*> text;
};

#endif /* SCENE00_H */
