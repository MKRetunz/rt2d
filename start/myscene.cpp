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
	for (unsigned int i = 0; i < 18; i++) {
		Text* line = new Text();
		line->scale = Point2(0.5f, 0.5f);

		text.push_back(line);
		layers[top_layer]->addChild(line);
	}

	// #############################################################
	// Unit creation
	// #############################################################

	//Blue unit creation
	soldier = new UnitBase();
	this->addChild(soldier);
	soldier->name = "Blue soldier";
	soldier->position.x = 410;
	soldier->position.y = 300;
	soldier->team = false;
	soldier->UnitClass = 1;

	mercenary = new UnitBase();
	this->addChild(mercenary);
	mercenary->name = "Blue mercenary";
	mercenary->position.x = 410;
	mercenary->position.y = 236;
	mercenary->team = false;
	mercenary->UnitClass = 2;

	fighter = new UnitBase();
	this->addChild(fighter);
	fighter->name = "Blue fighter";
	fighter->position.x = 410;
	fighter->position.y = 428;
	fighter->team = false;
	fighter->UnitClass = 3;

	//Red unit creation
	Rsoldier = new UnitBase();
	this->addChild(Rsoldier);
	Rsoldier->name = "Red soldier";
	Rsoldier->position.x = 794;
	Rsoldier->position.y = 364;
	Rsoldier->team = true;
	Rsoldier->UnitClass = 1;

	Rmercenary = new UnitBase();
	this->addChild(Rmercenary);
	Rmercenary->name = "Red mercenary";
	Rmercenary->position.x = 794;
	Rmercenary->position.y = 428;
	Rmercenary->team = true;
	Rmercenary->UnitClass = 2;

	Rfighter = new UnitBase();
	this->addChild(Rfighter);
	Rfighter->name = "Red fighter";
	Rfighter->position.x = 794;
	Rfighter->position.y = 236;
	Rfighter->team = true;
	Rfighter->UnitClass = 3;

	// #############################################################
	// Map creation
	// #############################################################

	//making a map
	gridwidth = 9;
	gridheight = 10;
	cellwidth = 64;
	cellheight = 64;
	border = 1;

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
	text[15]->message("Hit chance is Hit - enemy dodge.");
	text[16]->message("Final damage is Damage - enemy defense.");
	text[17]->message("If you have 5 speed more than the enemy attack twice.");

}


MyScene::~MyScene()
{
	// #############################################################
	// Cleaning up once scene is closed
	// #############################################################

	// deconstruct and delete the units

	//Blue team
	this->addChild(soldier);
	this->removeChild(soldier);

	this->addChild(mercenary);
	this->removeChild(mercenary);

	this->addChild(fighter);
	this->removeChild(fighter);

	//Red team
	this->addChild(Rsoldier);
	this->removeChild(Rsoldier);

	this->addChild(Rmercenary);
	this->removeChild(Rmercenary);

	this->addChild(Rfighter);
	this->removeChild(Rfighter);

	// delete objects
	delete soldier;
	delete mercenary;
	delete fighter;
	delete Rsoldier;
	delete Rmercenary;
	delete Rfighter;
}

void MyScene::update(float deltaTime)
{
	//Move camera
	moveCamera(deltaTime);

	// #############################################################
	// Selecting units
	// #############################################################

	selectUnit(soldier);
	selectUnit(Rsoldier);
	selectUnit(Rfighter);
	selectUnit(mercenary);
	selectUnit(Rmercenary);
	selectUnit(fighter);

	// #############################################################
	// Button presses
	// #############################################################

	//Movement
	if (input()->getKeyDown(GLFW_KEY_W)) {
		soldier->moveUp();
		Rsoldier->moveUp();
		mercenary->moveUp();
		Rmercenary->moveUp();
		fighter->moveUp();
		Rfighter->moveUp();
	}
	if (input()->getKeyDown(GLFW_KEY_A)) {
		soldier->moveLeft();
		Rsoldier->moveLeft();
		mercenary->moveLeft();
		Rmercenary->moveLeft();
		fighter->moveLeft();
		Rfighter->moveLeft();
	}
	if (input()->getKeyDown(GLFW_KEY_S)) {
		soldier->moveDown();
		Rsoldier->moveDown();
		mercenary->moveDown();
		Rmercenary->moveDown();
		fighter->moveDown();
		Rfighter->moveDown();
	}
	if (input()->getKeyDown(GLFW_KEY_D)) {
		soldier->moveRight();
		Rsoldier->moveRight();
		mercenary->moveRight();
		Rmercenary->moveRight();
		fighter->moveRight();
		Rfighter->moveRight();
	}

	//Unselect all units
	if (input()->getMouseDown( 1 )) {
		soldier->unSelect();
		Rsoldier->unSelect();
		mercenary->unSelect();
		Rmercenary->unSelect();
		fighter->unSelect();
		Rfighter->unSelect();
	}

	// #############################################################
	// Attacking
	// #############################################################

	//Attacking is called on every frame, but only activates if units colide
	if (turns == true) {
		//Simplify if possible
		soldier->collide(Rsoldier);
		soldier->collide(Rmercenary);
		soldier->collide(Rfighter);
		soldier->collide(mercenary);
		soldier->collide(fighter);
		mercenary->collide(Rsoldier);
		mercenary->collide(Rmercenary);
		mercenary->collide(Rfighter);
		mercenary->collide(soldier);
		mercenary->collide(fighter);
		fighter->collide(Rsoldier);
		fighter->collide(Rmercenary);
		fighter->collide(Rfighter);
		fighter->collide(soldier);
		fighter->collide(mercenary);
	}
	if (turns == false)
	{
		Rsoldier->collide(soldier);
		Rsoldier->collide(mercenary);
		Rsoldier->collide(fighter);
		Rsoldier->collide(Rmercenary);
		Rsoldier->collide(Rfighter);
		Rmercenary->collide(soldier);
		Rmercenary->collide(mercenary);
		Rmercenary->collide(fighter);
		Rmercenary->collide(Rsoldier);
		Rmercenary->collide(Rfighter);
		Rfighter->collide(soldier);
		Rfighter->collide(mercenary);
		Rfighter->collide(fighter);
		Rfighter->collide(Rsoldier);
		Rfighter->collide(Rmercenary);
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
		soldier->unSelect();
		Rsoldier->unSelect();
		mercenary->unSelect();
		Rmercenary->unSelect();
		fighter->unSelect();
		Rfighter->unSelect();
		if (turns == false && check == true) {
			turns = true;
			check = false;
			soldier->refresh();
			mercenary->refresh();
			fighter->refresh();
			text[0]->message("Blue turn.");
		}

		if (turns == true && check == true) {
			turns = false;
			check = false;
			Rsoldier->refresh();
			Rmercenary->refresh();
			Rfighter->refresh();
			text[0]->message("Red turn.");
		}
		//Empty text
		text[1]->clearMessage();
		text[2]->clearMessage();
		text[3]->clearMessage();
		text[4]->clearMessage();
		text[5]->clearMessage();
		text[6]->clearMessage();
		text[7]->clearMessage();
		text[8]->clearMessage();
		text[9]->clearMessage();
		text[10]->clearMessage();
		text[11]->clearMessage();
		text[12]->clearMessage();
		text[13]->clearMessage();
		text[14]->clearMessage();
	}
}

void MyScene::moveCamera(float deltaTime)
{
	// ###############################################################
	// Move Camera (Arrow up, down, left, right)
	// ###############################################################
	float speed = 600.0f; // 600 units / second

    // Right and Down vector
	Point2 right = Point2(1, 0);
	Point2 up = Point2(0, 1);
	// Direction
	Vector2 direction = Vector2(0, 0);

	if (input()->getKey(GLFW_KEY_UP)) {
		direction -= up;
	}
	if (input()->getKey(GLFW_KEY_DOWN)) {
		direction += up;
	}
	if (input()->getKey(GLFW_KEY_RIGHT)) {
		direction += right;
	}
	if (input()->getKey(GLFW_KEY_LEFT)) {
		direction -= right;
	}
	direction.normalize();
	direction *= deltaTime * speed;
	camera()->position += direction;
}

void MyScene::displayStats(UnitBase * unit)
{
	// #############################################################
	// Statistic display
	// #############################################################
	text[1]->message(unit->MsgName);
	text[2]->message(unit->MsgLVL);
	text[3]->message(unit->MsgHP);
	text[4]->message(unit->MsgSTR);
	text[5]->message(unit->MsgSKL);
	text[6]->message(unit->MsgSPD);
	text[7]->message(unit->MsgLCK);
	text[8]->message(unit->MsgDEF);
	text[9]->message(unit->MsgMOV);
	text[10]->message(unit->MsgCON);
	text[11]->message(unit->MsgHIT);
	text[12]->message(unit->MsgCRT);
	text[13]->message(unit->MsgDGD);
	text[14]->message(unit->MsgDMG);
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
