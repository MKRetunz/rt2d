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

/// @brief The GridMaker class is the Entity implementation.
class GridMaker : public Entity
{
public:
	/// @brief Constructor
	GridMaker();
	/// @brief Destructor
	virtual ~GridMaker();

	/// @brief makes a grid with the inserted specifications
	/// @param four ints for Grid width, height and Cell width and height respectively
	void MakeGrid(int GW, int GH, int CW, int CH);

private:
};

#endif /* GridMaker_H */
