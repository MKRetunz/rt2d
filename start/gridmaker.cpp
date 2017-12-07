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
	currentTile = 0;
	sourceTile = 0;

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
}

void GridMaker::HighlightGrid(int range, int target, int color)
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
						if (this->spritebatch()[counter]->frame() != 2) {
							this->spritebatch()[counter]->frame(color);
						}
						else if (target >= counter) {
							//lower the range
						}
						else if (target < counter) {
							//Lower the range
						}
					}
				}
				counter++;
			}
		}
		//After finishing one row move on to the next and check if there are any tiles that need to be drawn.
		int newTarget = target - gridwidth;
		int newRange = range - 1;
		if (newRange >= 0) {
			HighlightGrid(newRange, newTarget, color);
			newTarget = target + gridwidth;
			HighlightGrid(newRange, newTarget, color);
		}
	}
	isHighlighting = true;
}

void GridMaker::ResetGrid()
{
	int counter = 0;
	for (int x = 0; x < gridwidth; x++) {
		for (int y = 0; y < gridheight; y++) {
			if (this->spritebatch()[counter]->frame() != 2) {
				this->spritebatch()[counter]->frame(0);
			}
			counter++;
		}
	}
	isHighlighting = false;
	//gridObstacle();
}

void GridMaker::MoveUnit(Entity * e, Point2 p)
{
	e->position = p;
}

void GridMaker::gridObstacle()
{
	int counter = 0;
	int checker = 0;
	for (int x = 0; x < gridwidth; x++) {
		for (int y = 0; y < gridheight; y++) {
			if (this->spritebatch()[counter]->frame() == 0) {
				
			}
			else {
				checker = counter++;
				if (this->spritebatch()[checker]->frame() == 0) {

				}
			}
			counter++;
		}
	}
}

