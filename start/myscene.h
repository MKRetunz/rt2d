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
#include "myentity.h"
#include "UnitBase.h"


struct Player
{
	int mouseclicks = 0;
};

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

	void addPlayer(Player* p) { player = p; };

protected:
	Player* player;
	std::vector<Text*> text;
	void moveCamera(float deltaTime);

private:
	/// @brief the rotating square in the middle of the screen
	MyEntity* myentity;
	/// @brief a Timer to rotate the color every n seconds
	Timer t;
};

#endif /* SCENE00_H */
