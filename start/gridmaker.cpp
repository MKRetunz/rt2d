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
	//Set variables based on cell info
	gridwidth = GW;
	gridheight = GH;
	cellwidth = CW;
	cellheight = CH;

	// create grid depending on input
	addGrid("assets/default.tga", 8, 8, GW, GH, CW, CH);

	// fill Sprites with random numbers for now
	int counter = 0;
	for (int x = 0; x<GW; x++) {
		for (int y = 0; y<GH; y++) {
			spritebatch()[counter]->frame(0);
			counter++;
		}
	}

	HighlightGrid(3, 15);
}

void GridMaker::HighlightGrid(int range, int target)
{
	int posReach = target + range;
	int negReach = target - range;
	int targetRow = target / gridwidth;
	std::vector<Sprite*> spritebatch = this->spritebatch();
	int counter = 0;
	for (int x = 0; x < gridwidth; x++) {
		for (int y = 0; y < gridheight; y++) {

			if (counter >= negReach && counter <= posReach)
			{
				int counterRow = counter / gridwidth;
				if (counterRow != targetRow) {
					//Do nothing if the tile is in another row then the target.
				}
				else {
					spritebatch[counter]->frame(1);
				}
			}

			counter++;
		}
	}
	int newTarget = target - gridwidth;
	int newRange = range - 1;
	if (newRange > 0) {
		HighlightGrid(newRange, newTarget);
		newTarget = target + gridwidth;
		HighlightGrid(newRange, newTarget);
	}
}