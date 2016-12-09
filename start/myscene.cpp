/**
 * This class describes MyScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

MyScene::MyScene() : Scene()
{
	gridMaker = new GridMaker();
	gridMaker->MakeGrid(5, 5, 64, 64);
	gridMaker->position = Point2(SWIDTH/2, SHEIGHT/2);

	this->addChild(gridMaker);

	basicunit = new BasicUnit();
	this->addChild(basicunit);
}

MyScene::~MyScene()
{
	this->removeChild(gridMaker);
	delete gridMaker;

	this->removeChild(basicunit);
	delete basicunit;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	if (input()->getKeyUp(GLFW_KEY_W)) {
		basicunit->moveUnit(0);
	}
	if (input()->getKeyUp(GLFW_KEY_A)) {
		basicunit->moveUnit(1);
	}
	if (input()->getKeyUp(GLFW_KEY_S)) {
		basicunit->moveUnit(2);
	}
	if (input()->getKeyUp(GLFW_KEY_D)) {
		basicunit->moveUnit(3);
	}
}
