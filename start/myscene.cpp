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
	//##############################################################
	//Camera
	//##############################################################

	camera()->position.x -= 100;

	// #############################################################
	// Setting up for text and map creation
	// #############################################################

	top_layer = 7; // 8 layers (0-7)

	//add layers
	for (unsigned int i = 0; i <= top_layer; i++) {
		BasicEntity* layer = new BasicEntity();
		layers.push_back(layer);
		this->addChild(layer);
	}

	//add text
	for (unsigned int i = 0; i < 26; i++) {
		Text* line = new Text();
		line->scale = Point2(0.5f, 0.5f);

		text.push_back(line);
		layers[top_layer]->addChild(line);
	}

	// #############################################################
	// Unit creation
	// #############################################################

	//Blue unit creation
	//Add list of UnitBases
	soldier = new UnitBase();
	soldier->name = "Blue soldier";
	soldier->position.x = 416;
	soldier->position.y = 296;
	soldier->team = false;
	soldier->UnitClass = 1;
	units.push_back(soldier);
	this->addChild(soldier);

	mercenary = new UnitBase();
	mercenary->name = "Blue mercenary";
	mercenary->position.x = 416;
	mercenary->position.y = 232;
	mercenary->team = false;
	mercenary->UnitClass = 2;
	units.push_back(mercenary);
	this->addChild(mercenary);

	fighter = new UnitBase();
	this->addChild(fighter);
	fighter->name = "Blue fighter";
	fighter->position.x = 416;
	fighter->position.y = 424;
	fighter->team = false;
	fighter->UnitClass = 3;
	units.push_back(fighter);
	this->addChild(fighter);

	//Red unit creation
	Rsoldier = new UnitBase();
	Rsoldier->name = "Red soldier";
	Rsoldier->position.x = 800;
	Rsoldier->position.y = 360;
	Rsoldier->team = true;
	Rsoldier->UnitClass = 1;
	units.push_back(Rsoldier);
	this->addChild(Rsoldier);

	Rmercenary = new UnitBase();
	Rmercenary->name = "Red mercenary";
	Rmercenary->position.x = 800;
	Rmercenary->position.y = 424;
	Rmercenary->team = true;
	Rmercenary->UnitClass = 2;
	units.push_back(Rmercenary);
	this->addChild(Rmercenary);

	Rfighter = new UnitBase();
	Rfighter->name = "Red fighter";
	Rfighter->position.x = 800;
	Rfighter->position.y = 232;
	Rfighter->team = true;
	Rfighter->UnitClass = 3;
	units.push_back(Rfighter);
	this->addChild(Rfighter);

	// #############################################################
	// Map creation
	// #############################################################

	//making a map
	gridwidth = 9;
	gridheight = 10;
	cellwidth = 62;
	cellheight = 62;
	border = 2;

	grid = new BasicEntity();
	int xgridpos = (SWIDTH / 2) - (gridwidth*(cellwidth + border) / 2);
	int ygridpos = (SHEIGHT / 2) - (gridheight*(cellheight + border) / 2);
	grid->position = Point2(xgridpos, ygridpos);

	// create cells
	for (int x = 0; x<gridwidth; x++) {
		for (int y = 0; y<gridheight; y++) {
			Cell* cell = new Cell();
			cell->position.x = x;
			cell->position.y = y;

			cell->entity = new BasicEntity();
			cell->entity->addSprite(AUTOGENWHITE);
			cell->entity->sprite()->size.x = cellwidth;
			cell->entity->sprite()->size.y = cellheight;
			cell->entity->sprite()->color = GRAY;

			//Top half of black tiles
			if (y == 1 && x == 2 || y == 1 && x == 6 || y == 2 && x == 2 || y == 2 && x == 6 || y == 3 && x == 2 || y == 3 && x == 6 || y == 3 && x == 4 || y == 3 && x == 5) {
				cell->entity->sprite()->color = BLACK;
			}

			//Bottom half
			if (y == 8 && x == 2 || y == 8 && x == 6 || y == 7 && x == 2 || y == 7 && x == 6 || y == 6 && x == 2 || y == 6 && x == 6 || y == 6 && x == 4 || y == 6 && x == 3) {
				cell->entity->sprite()->color = BLACK;
			}

			//Surrounding tiles
			if (y == 0 || y == 9 || x == 0 || x == 8) {
				cell->entity->sprite()->color = BLACK;
			}

			// initial position
			cell->entity->position.x = x*(cellwidth + border);
			cell->entity->position.y = y*(cellheight + border);

			cells.push_back(cell);
			grid->addChild(cell->entity);
			layers[0]->addChild(grid);
		}
	}

	text[0]->message("Blue turn.");
	text[16]->message("Press M to switch turns.");
	text[17]->message("Use the mouse to select.");
	text[18]->message("Use WASD to move units.");
	text[19]->message("Hit chance is Hit - enemy Dodge.");
	text[20]->message("Final damage is Damage - enemy Defense.");
	text[21]->message("If you have 5 speed more than the enemy attack twice.");
}


MyScene::~MyScene()
{
	// #############################################################
	// Cleaning up once scene is closed
	// #############################################################

	// Remove Grid
	int s = cells.size();
	for (int i = 0; i<s; i++) {
		layers[0]->removeChild(cells[i]->entity);
		delete cells[i]->entity;
		delete cells[i];
		cells[i] = NULL;
	}
	cells.clear();

	delete grid;

	// deconstruct and delete the units
	int us = units.size();
	for (int u = 0; u < us; u++) {
		this->removeChild(units[u]);
		delete units[u];
		units[u] = NULL;
	}
	units.clear();
	
	//Text and layers

	int ls = layers.size();
	for (int i = 0; i<ls; i++) {
		this->removeChild(layers[i]);
		delete layers[i];
		layers[i] = NULL;
	}
	layers.clear();

	int ts = text.size();
	for (int i = 0; i<ts; i++) {
		this->removeChild(text[i]);
		delete text[i];
		text[i] = NULL;
	}
	text.clear();
}

void MyScene::update(float deltaTime)
{
	// #############################################################
	// Selecting units
	// #############################################################

	int us = units.size();
	for (int u = 0; u<us ; u++) {
		selectUnit(units[u]);
	}

	// #############################################################
	// Button presses
	// #############################################################

	//Movement
	if (input()->getKeyDown(GLFW_KEY_W)) {
		for (int u = 0; u<us; u++) {
			units[u]->moveUp();
		}
	}
	if (input()->getKeyDown(GLFW_KEY_A)) {
		for (int u = 0; u<us; u++) {
			units[u]->moveLeft();
		}
	}
	if (input()->getKeyDown(GLFW_KEY_S)) {
		for (int u = 0; u<us; u++) {
			units[u]->moveDown();
		}
	}
	if (input()->getKeyDown(GLFW_KEY_D)) {
		for (int u = 0; u<us; u++) {
			units[u]->moveRight();
		}
	}

	//Unselect all units
	if (input()->getMouseDown( 1 )) {
		for (int u = 0; u<us; u++) {
			units[u]->unSelect();
		}
	}

	// #############################################################
	// Attacking
	// #############################################################

	//Attacking is called on every frame, but only activates if units colide
	for (int u = 0; u<us; u++) {
		for (int o = 0; o<us; o++) {
			if (u == o) {
				//Left blank to do nothing.
			}
			else {
				units[u]->collide(units[o]);
			}
		}
	}


	// #############################################################
	// Text follows camera
	// #############################################################

	unsigned int s = text.size();
	for (unsigned int i = 0; i < s; i++) {
		text[i]->position = Point2(camera()->position.x + 50 - SWIDTH / 2, camera()->position.y + 50 + (30 * i) - SHEIGHT / 2);
	}

	// ###############################################################
	// Escape key stops the Scene
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_ESCAPE )) {
		this->stop();
	}

	// ###############################################################
	// Pressing the Right mouse button switches player turns
	// ###############################################################
	if (input()->getKeyUp( GLFW_KEY_M )) {
		check = true;
		for (int u = 0; u<us; u++) {
			units[u]->unSelect();
		}

		if (turns == false && check == true) {
			turns = true;
			check = false;
			text[0]->message("Blue turn.");
		}

		if (turns == true && check == true) {
			turns = false;
			check = false;
			text[0]->message("Red turn.");
		}

		for (int u = 0; u<us; u++) {
			units[u]->refresh();
		}

		//Empty text
		for (int i = 1; i < 15; i++) {
			text[i]->clearMessage();
		}
	}
}

void MyScene::displayStats(UnitBase * unit)
{
	// #############################################################
	// Statistic display
	// #############################################################
	text[1]->message(unit->MsgName);
	text[2]->message(unit->MsgLVL);
	text[3]->message(unit->MsgEXP);
	text[4]->message(unit->MsgHP);
	text[5]->message(unit->MsgDMG);
	text[6]->message(unit->MsgSPD);
	text[7]->message(unit->MsgDEF);
	text[8]->message(unit->MsgMOV);
	text[9]->message(unit->MsgHIT);
	text[10]->message(unit->MsgDGD);
}

void MyScene::selectUnit(UnitBase* unit)
{
	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH / 2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT / 2;

	if (mousey >= unit->position.y + -32 && mousey <= unit->position.y + 32 && mousex >= unit->position.x + -32 && mousex <= unit->position.x + 32) {
		displayStats(unit);
		if (turns == false && unit->team == true && input()->getMouseDown( 0 )) {
			unit->selected = true;
		}
		if (turns == true && unit->team == false && input()->getMouseDown( 0 )) {
			unit->selected = true;
		}
	}
}
