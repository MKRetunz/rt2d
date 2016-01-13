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
#include "UnitBase.h"
#include "basicentity.h"

struct Cell
{
	BasicEntity* entity; // visual representation
	Point_t<int> position; // x/y in grid
};


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
	unsigned int top_layer;
	Player* player;
	std::vector<Text*> text;

	std::vector<BasicEntity*> layers;
	void moveCamera(float deltaTime);
	void displayStats(UnitBase* unit);
	void selectUnit(UnitBase* unit);

private:
	BasicEntity* grid;
	std::vector<Cell*> cells;

	int border;

	// Making units
	UnitBase* soldier;
	UnitBase* mercenary;
	UnitBase* fighter;
	UnitBase* Rsoldier;
	UnitBase* Rmercenary;
	UnitBase* Rfighter;

	int gridwidth;
	int gridheight;
	int cellwidth;
	int cellheight;

	bool turns = true;
	bool check = false;
};

#endif /* SCENE00_H */
