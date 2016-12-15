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
	gridMaker->MakeGrid(10, 10, 64, 64);
	gridMaker->position = Point2(SWIDTH/4, SHEIGHT/4);

	this->addChild(gridMaker);

	basicunit = new BasicUnit();
	this->addChild(basicunit);

	basicunit->position = gridMaker->position;
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

	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH / 2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT / 2;

	std::cout << mousex << " " << mousey << std::endl;

	int counter = 0;
	for (int x = 0; x<gridMaker->gridwidth; x++) {
		for (int y = 0; y<gridMaker->gridheight; y++) {
			Point2 pos = gridMaker->spritebatch()[counter]->spriteposition;

			pos += gridMaker->position;

			int halfwidth = gridMaker->cellwidth / 2;
			int halfheight = gridMaker->cellheight / 2;
			int left = pos.x - halfwidth;
			int right = pos.x + halfwidth;
			int top = pos.y - halfheight;
			int bottom = pos.y + halfheight;

			if (mousex > left && mousex < right && mousey > top && mousey < bottom) {
				gridMaker->spritebatch()[counter]->color.a = 192;
				
				int unitspriteR = basicunit->position.x + 32;
				int unitspriteL = basicunit->position.x - 32;
				int unitspriteD = basicunit->position.y + 32;
				int unitspriteT = basicunit->position.y - 32;

				//gridMaker->HighlightGrid(6, counter);
				if (gridMaker->isHighlighting == false && mousex < unitspriteR && mousex > unitspriteL && mousey > unitspriteT && mousey < unitspriteD) {
					if (input()->getMouseDown(0)) {
						gridMaker->ResetGrid();
						gridMaker->HighlightGrid(6, counter);
						gridMaker->isHighlighting = true;
					}
				}
			}
			else {
				gridMaker->spritebatch()[counter]->color.a = 255;
			}
			counter++;
		}
	}
}
