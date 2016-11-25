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
	gridMaker->MakeGrid(5, 5, 16, 16);
	gridMaker->position = Point2(SWIDTH/2, SHEIGHT/2);

	this->addChild(gridMaker);
}

MyScene::~MyScene()
{
	this->removeChild(gridMaker);
	delete gridMaker;
}

void MyScene::update(float deltaTime)
{
	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}
}
