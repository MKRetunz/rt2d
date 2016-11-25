/**
 * This class describes GridMaker behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "gridmaker.h"

GridMaker::GridMaker() : Entity()
{

}

GridMaker::~GridMaker()
{

}

void GridMaker::update(float deltaTime)
{

}

void GridMaker::MakeGrid(int GW, int GH, int CW, int CH) 
{
	gridwidth = GW;
	gridheight = GH;
	cellwidth = CW;
	cellheight = CH;

	// create grid depending on input
	addGrid("assets/default.tga", 8, 8, gridwidth, gridheight, cellwidth, cellheight);

	// fill Sprites with random numbers for now
	int counter = 0;
	for (int x = 0; x<gridwidth; x++) {
		for (int y = 0; y<gridheight; y++) {
			spritebatch()[counter]->frame(rand() % 16);
			counter++;
		}
	}
}