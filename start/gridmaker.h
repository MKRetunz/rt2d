/**
 * Copyright 2015 Your Name <you@yourhost.com>
 *
 * @file GridMaker.h
 *
 * @brief description of GridMaker behavior.
 */

#ifndef GridMaker_H
#define GridMaker_H

#include <rt2d/entity.h>

/// @brief The GridMaker class is the Entity implementation
class GridMaker : public Entity
{
public:
	/// @brief Constructor
	GridMaker();
	/// @brief Destructor
	virtual ~GridMaker();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	virtual void update(float deltaTime);

	/// @brief makes a grid with the inserted specifications
	/// @param four ints for Grid width, height and Cell width and height respectively
	/// @return void
	void MakeGrid(int GW, int GH, int CW, int CH);

	/// @brief highlights tiles within the specified range
	/// @param range indicates the reach of the function while target is the base
	/// @return void
	void HighlightGrid(int range, int target, int color);

	/// @brief unhighlights all the tiles on the grid
	/// @return void
	void ResetGrid();

	/// @brief moves the target entity
	/// @param the entity to move and the point to move it to
	/// @return void
	void MoveUnit(Entity* e, Point2 p);

	/// @brief the width of the grid in cells
	int gridwidth;

	/// @brief the hieght of the grid in cells
	int gridheight;

	/// @brief the width of the cell in pixels
	int cellwidth;

	/// @brief the height of the cell in pixels
	int cellheight;

	int currentTile;

	/// @brief a bool to see if the grid is being highlighted or not
	bool isHighlighting;

private:

};

#endif /* GridMaker_H */
