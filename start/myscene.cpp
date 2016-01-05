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
	for (unsigned int i = 0; i < 16; i++) {
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
	soldier->name = "Blue";
	soldier->position.x = 410;
	soldier->position.y = 300;
	soldier->team = false;

	//Red unit creation
	Rsoldier = new UnitBase();
	this->addChild(Rsoldier);
	Rsoldier->name = "Red";
	Rsoldier->position.x = 474;
	Rsoldier->position.y = 300;
	Rsoldier->team = true;

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

	text[1]->message("Blue turn.");
}


MyScene::~MyScene()
{
	// #############################################################
	// Cleaning up once scene is closed
	// #############################################################

	// deconstruct and delete the units
	this->addChild(soldier);
	this->removeChild(soldier);

	this->addChild(Rsoldier);
	this->removeChild(Rsoldier);

	// delete objects
	delete soldier;
	delete Rsoldier;
}

void MyScene::update(float deltaTime)
{
	//Move camera
	moveCamera(deltaTime);

	// #############################################################
	// Holding mouse over units
	// #############################################################

	int mousex = input()->getMouseX() + camera()->position.x - SWIDTH / 2;
	int mousey = input()->getMouseY() + camera()->position.y - SHEIGHT / 2;

	if (mousey >= Rsoldier->position.y + -32 && mousey <= Rsoldier->position.y + 32 && mousex >= Rsoldier->position.x + -32 && mousex <= Rsoldier->position.x + 32) {
		displayStats(Rsoldier);
		if (turns == false) {
			Rsoldier->selected = true;
		}
	}

	if (mousey >= soldier->position.y + -32 && mousey <= soldier->position.y + 32 && mousex >= soldier->position.x + -32 && mousex <= soldier->position.x + 32) {
		displayStats(soldier);
		if (turns == true) {
			soldier->selected = true;
		}
	}

	// #############################################################
	// Button presses
	// #############################################################

	//Movement
	if (input()->getKeyDown(GLFW_KEY_W)) {
		soldier->moveUp();
		Rsoldier->moveUp();
	}
	if (input()->getKeyDown(GLFW_KEY_A)) {
		soldier->moveLeft();
		Rsoldier->moveLeft();
	}
	if (input()->getKeyDown(GLFW_KEY_S)) {
		soldier->moveDown();
		Rsoldier->moveDown();
	}
	if (input()->getKeyDown(GLFW_KEY_D)) {
		soldier->moveRight();
		Rsoldier->moveRight();
	}

	// #############################################################
	// Attacking
	// #############################################################

	//Attacking is called on every frame, but only activates if units colide
	if (turns == true) {
		soldier->attack(Rsoldier);
	}
	if (turns == false)
	{
		Rsoldier->attack(soldier);
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
	if (input()->getMouseDown( 1 )) {
		check = true;
		if (turns == false && check == true) {
			turns = true;
			check = false;
			soldier->refresh();
			Rsoldier->refresh();
			text[1]->message("Blue turn.");
		}

		if (turns == true && check == true) {
			turns = false;
			check = false;
			soldier->refresh();
			Rsoldier->refresh();
			text[1]->message("Red turn.");
		}
		//Empty text
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
	text[2]->message(unit->MsgName);
	text[3]->message(unit->MsgHP);
	text[4]->message(unit->MsgSTR);
	text[5]->message(unit->MsgMAG);
	text[6]->message(unit->MsgSKL);
	text[7]->message(unit->MsgSPD);
	text[8]->message(unit->MsgLCK);
	text[9]->message(unit->MsgDEF);
	text[10]->message(unit->MsgRES);
	text[11]->message(unit->MsgMOV);
	text[12]->message(unit->MsgCON);
	text[13]->message(unit->MsgMOVO);
}
