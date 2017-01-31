/**
 * This class describes GameScene behavior.
 *
 * Copyright 2015 Your Name <you@yourhost.com>
 */

#include <fstream>
#include <sstream>

#include "myscene.h"

GameScene::GameScene() : Scene()
{
	for (unsigned int i = 0; i < 16; i++) {
		Text* line = new Text();
		line->scale = Point2(0.5f, 0.5f);
		line->position.y = i * 25;
		line->position.x = 10;

		text.push_back(line);
		this->addChild(line);
	}

	gridMaker = new GridMaker();
	gridMaker->MakeGrid(10, 10, 64, 64);
	gridMaker->position = Point2(SWIDTH/4, SHEIGHT/8);
	this->addChild(gridMaker);

	mercR = new BasicUnit();
	unitList.push_back(mercR);
	mercR->position = gridMaker->position;
	this->addChild(mercR);
	mercR->unitClass = 0;
	mercR->makeUnit();

	soldierR = new BasicUnit();
	unitList.push_back(soldierR);
	soldierR->position = gridMaker->position;
	soldierR->position.y += 64;
	this->addChild(soldierR);
	soldierR->unitClass = 1;
	soldierR->makeUnit();

	fighterR = new BasicUnit();
	unitList.push_back(fighterR);
	fighterR->position = gridMaker->position;
	fighterR->position.y += 124;
	this->addChild(fighterR);
	fighterR->unitClass = 2;
	fighterR->makeUnit();

	mercB = new BasicUnit();
	unitList.push_back(mercB);
	mercB->position = gridMaker->position;
	mercB->position.x += 124;
	this->addChild(mercB);
	mercB->unitClass = 0;
	mercB->unitTeam = true;
	mercB->makeUnit();

	soldierB = new BasicUnit();
	unitList.push_back(soldierB);
	soldierB->position = gridMaker->position;
	soldierB->position.x += 128;
	soldierB->position.y += 64;
	this->addChild(soldierB);
	soldierB->unitClass = 1;
	soldierB->unitTeam = true;
	soldierB->makeUnit();

	fighterB = new BasicUnit();
	unitList.push_back(fighterB);
	fighterB->position = gridMaker->position;
	fighterB->position.x += 128;
	fighterB->position.y += 128;
	this->addChild(fighterB);
	fighterB->unitClass = 2;
	fighterB->unitTeam = true;
	fighterB->makeUnit();

	unitspriteR = 32;
	unitspriteL = 32;
	unitspriteD = 32;
	unitspriteT = 32;

	menuOn = false;

	currentTurn = false;

	text[1]->message("Turn: Red");
	text[2]->message("Press A to switch turns.");

}

GameScene::~GameScene()
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

void GameScene::update(float deltaTime)
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
			unitMenu(unitList[ul]);
			if (input()->getMouseDown(0) && unitList[ul]->unitTeam == currentTurn) {
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
					unitspriteR = unitList[ul]->position.x + gridMaker->cellwidth / 2;
					unitspriteL = unitList[ul]->position.x - gridMaker->cellwidth / 2;
					unitspriteD = unitList[ul]->position.y + gridMaker->cellwidth / 2;
					unitspriteT = unitList[ul]->position.y - gridMaker->cellwidth / 2;

					if (input()->getMouseDown(0)) {	
						if (!gridMaker->isHighlighting && mousex < unitspriteR && mousex > unitspriteL && mousey > unitspriteT && mousey < unitspriteD && unitList[ul]->unitTeam == currentTurn && unitList[ul]->selected) {
							gridMaker->ResetGrid();
							gridMaker->sourceTile = counter;
							gridMaker->HighlightGrid(unitList[ul]->Move, counter, 1);
							actionMenu();
						}
						else if (gridMaker->isHighlighting && gridMaker->spritebatch()[counter]->frame() == 1 && unitList[ul]->unitTeam == currentTurn && unitList[ul]->selected) {
							gridMaker->ResetGrid();
							gridMaker->HighlightGrid(unitList[ul]->Move, gridMaker->sourceTile, 1);
							gridMaker->MoveUnit(unitList[ul], pos);
							gridMaker->currentTile = counter;
							menuOn = false;
							actionMenu();
						}
						else if (gridMaker->isHighlighting && gridMaker->spritebatch()[counter]->frame() == 0) {
							gridMaker->ResetGrid();
							actionMenu();
						}
						else if (gridMaker->isHighlighting && gridMaker->spritebatch()[counter]->frame() == 3 && unitList[ul]->position == pos && unitList[ul]->unitTeam != currentTurn) {
							for (int ul2 = 0; ul2 < unitList.size(); ul2++) { 
								if (unitList[ul2]->selected) {
									unitList[ul2]->attack(unitList[ul]);
								}
							}
							gridMaker->ResetGrid();
							actionMenu();
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

	if (menuOn && input()->getKeyDown(GLFW_KEY_X)) {
		gridMaker->ResetGrid();
		actionMenu();
	}
	if (menuOn && input()->getKeyDown(GLFW_KEY_Z)) {
		gridMaker->HighlightGrid(1, gridMaker->currentTile, 3);
	}
	if (input()->getKeyDown(GLFW_KEY_A)) {
		if (currentTurn) {
			currentTurn = false;
			text[1]->message("Turn: Red");
		}
		else
		{
			currentTurn = true;
			text[1]->message("Turn: Blue");
		}
		gridMaker->ResetGrid();
	}
}

void GameScene::actionMenu()
{
	if (!menuOn) {
		text[10]->message("Press Z to attack");
		text[11]->message("Press X to wait");

		menuOn = true;
	}
	else {
		text[10]->message("");
		text[11]->message("");
		menuOn = false;
	}
}

void GameScene::unitMenu(BasicUnit * b)
{
	std::string Message;

	Message = "Hit points: ";
	Message.append(std::to_string(b->HitPoints));

	text[3]->message(Message);

	Message = "Damage: ";
	Message.append(std::to_string(b->Damage));

	text[4]->message(Message);

	Message = "Hit: ";
	Message.append(std::to_string(b->Hit));

	text[5]->message(Message);

	Message = "Avoid: ";
	Message.append(std::to_string(b->Avoid));

	text[6]->message(Message);

	Message = "Defense: ";
	Message.append(std::to_string(b->Defense));

	text[7]->message(Message);

	Message = "Movement: ";
	Message.append(std::to_string(b->Move));

	text[8]->message(Message);

	Message.clear();
}
