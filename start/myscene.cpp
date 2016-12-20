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
	gridMaker->position = Point2(SWIDTH/4, SHEIGHT/8);
	this->addChild(gridMaker);

	basicunit = new BasicUnit();
	unitList.push_back(basicunit);
	basicunit->position = gridMaker->position;
	this->addChild(basicunit);
	//basicunit->selected = true;

	unitTesting = new BasicUnit();
	unitList.push_back(unitTesting);
	unitTesting->position = gridMaker->position + gridMaker->cellwidth;
	this->addChild(unitTesting);
	unitTesting->selected = true;
	unitTesting->addSprite("assets/mercenaryv2.tga");

	unitspriteR = 32;
	unitspriteL = 32;
	unitspriteD = 32;
	unitspriteT = 32;

	for (unsigned int i = 0; i < 16; i++) {
		Text* line = new Text();
		line->scale = Point2(0.5f, 0.5f);
		line->position.y = i * 25;
		line->position.x = 10;

		text.push_back(line);
		this->addChild(line);
	}

	text[1]->message("Placeholder:");
	text[2]->message("This will be the basic UI and needs to be changed when possible.");

}

MyScene::~MyScene()
{
	int ts = text.size();
	for (int i = 0; i < ts; i++) {
		this->removeChild(text[i]);
		delete text[i];
		text[i] = NULL;
	}
	text.clear();

	int us = unitList.size();
	for (int i = 0; i < us; i++) {
		this->removeChild(unitList[i]);
		delete unitList[i];
	}
	unitList.clear();

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

	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH / 2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT / 2;

	for (int ul = 0; ul < unitList.size(); ul++) {
		unitspriteR = unitList[ul]->position.x + gridMaker->cellwidth / 2;
		unitspriteL = unitList[ul]->position.x - gridMaker->cellwidth / 2;
		unitspriteD = unitList[ul]->position.y + gridMaker->cellwidth / 2;
		unitspriteT = unitList[ul]->position.y - gridMaker->cellwidth / 2;

		if (mousex < unitspriteR && mousex > unitspriteL && mousey > unitspriteT && mousey < unitspriteD) {
			if (input()->getMouseDown(0)) {
				unitList[ul]->selected = true;
				for (int ul2 = 0; ul2 < unitList.size(); ul2++) {
					if (ul2 != ul) {
						unitList[ul2]->selected = false;
					}
				}
			}
		}
	}

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

				for (int ul = 0; ul < unitList.size(); ul++) {
					if (unitList[ul]->selected == true) {
						unitspriteR = unitList[ul]->position.x + gridMaker->cellwidth / 2;
						unitspriteL = unitList[ul]->position.x - gridMaker->cellwidth / 2;
						unitspriteD = unitList[ul]->position.y + gridMaker->cellwidth / 2;
						unitspriteT = unitList[ul]->position.y - gridMaker->cellwidth / 2;

						std::cout << basicunit->position << mousex << " " << mousey << std::endl;

						if (input()->getMouseDown(0)) {
							if (!gridMaker->isHighlighting && mousex < unitspriteR && mousex > unitspriteL && mousey > unitspriteT && mousey < unitspriteD) {
								gridMaker->ResetGrid();
								gridMaker->HighlightGrid(6, counter);
							}
							else if (gridMaker->isHighlighting && gridMaker->spritebatch()[counter]->frame() == 1) {
								gridMaker->MoveUnit(unitList[ul], pos);
								gridMaker->ResetGrid();
							}
							else if (gridMaker->isHighlighting && gridMaker->spritebatch()[counter]->frame() == 0) {
								gridMaker->ResetGrid();
							}
						}
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
