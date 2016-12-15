/**
 * This class describes GridMaker behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include "gridmaker.h"

GridMaker::GridMaker() : Entity()
{
	gridwidth = 0;
	gridheight = 0;
	cellwidth = 0;
	cellheight = 0;

	isHighlighting = false;
}

GridMaker::~GridMaker()
{

}

void GridMaker::update(float deltaTime)
{
	
}

void GridMaker::MakeGrid(int GW, int GH, int CW, int CH) 
{
	//Set variables based on cell info
	gridwidth = GW;
	gridheight = GH;
	cellwidth = CW;
	cellheight = CH;

	// create grid depending on input
	addGrid("assets/mapcolors.tga", 2, 2, GW, GH, CW, CH);

	// fill Sprites with random numbers for now
	int counter = 0;
	for (int x = 0; x<GW; x++) {
		for (int y = 0; y<GH; y++) {
			spritebatch()[counter]->frame(0);
			counter++;
		}
	}

	//HighlightGrid(3, 15);
}

void GridMaker::HighlightGrid(int range, int target)
{
	if (target >= 0) {
		int posReach = target + range;	
		int negReach = target - range;
		int targetRow = target / gridwidth;
		int counter = 0;
		for (int x = 0; x < gridwidth; x++) {
			for (int y = 0; y < gridheight; y++) {
				if (counter >= negReach && counter <= posReach)
				{
					int counterRow = counter / gridwidth;
					if (counterRow == targetRow) {
						this->spritebatch()[counter]->frame(1);
					}
				}
				counter++;
			}
		}
		//After finishing one row move on to the next and check if there are any tiles that need to be drawn.
		int newTarget = target - gridwidth;
		int newRange = range - 1;
		if (newRange >= 0) {
			HighlightGrid(newRange, newTarget);
			newTarget = target + gridwidth;
			HighlightGrid(newRange, newTarget);
		}
	}
}

void GridMaker::ResetGrid()
{
	int counter = 0;
	for (int x = 0; x < gridwidth; x++) {
		for (int y = 0; y < gridheight; y++) {
			this->spritebatch()[counter]->frame(0);
			counter++;
		}
	}
}

void GridMaker::MoveUnit(Entity * e, Point2 p)
{
}



