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
				cell->CB = true;
			}

			//Bottom half
			if (y == 8 && x == 2 || y == 8 && x == 6 || y == 7 && x == 2 || y == 7 && x == 6 || y == 6 && x == 2 || y == 6 && x == 6 || y == 6 && x == 4 || y == 6 && x == 3) {
				cell->entity->sprite()->color = BLACK;
				cell->CB = true;
			}

			//Surrounding tiles
			if (y == 0 || y == 9 || x == 0 || x == 8) {
				cell->entity->sprite()->color = BLACK;
				cell->CB = true;
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
	//Move camera
	//moveCamera(deltaTime);

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
		unselection();
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
		unselection();
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

void MyScene::selection(UnitBase * unit)
{
	int s = cells.size();
	for (int i = 0; i < s; i++) {
		Cell* c = cells[i];
		//Point2 pos = c->entity->worldpos();

		float subX = (unit->position.x - c->position.x * c->position.x);
		float subY = (unit->position.y - c->position.y * c->position.y);

		float distance = sqrt((subX * subX) + (subY * subY));

		if (distance > 454 * unit->MovOver && c->CB == false) {
			c->entity->sprite()->color = BLUE;
		}
	}
}

void MyScene::unselection()
{
	int s = cells.size();
	for (int i = 0; i < s; i++) {
		Cell* c = cells[i];
		Point2 pos = c->entity->worldpos();
		if (c->CB == false) {
			c->entity->sprite()->color = GRAY;
		}
	}
}

/*void MyScene::moveCamera(float deltaTime)
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
}*/

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
