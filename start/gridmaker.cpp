/**
 * This class describes GridMaker behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "gridmaker.h"

GridMaker::GridMaker() : Entity()
{
	this->addSprite("assets/square.tga");
	this->sprite()->color = RED;
}

GridMaker::~GridMaker()
{

}

void GridMaker::update(float deltaTime)
{
	// ###############################################################
	// Rotate
	// ###############################################################
	this->rotation += HALF_PI * deltaTime; // 90 deg/sec
	if (this->rotation > TWO_PI) {
		this->rotation -= TWO_PI;
	}
}
