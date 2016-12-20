#ifndef BASICUNIT_H
#define BASICUNIT_H

#include "entity.h"
class BasicUnit :
	public Entity
{
public:
	/// @brief Constructor
	BasicUnit();

	/// @brief Deconstructor
	virtual ~BasicUnit();

	/// @brief update is automatically called every frame
	/// @param deltaTime the elapsed time in seconds
	/// @return void
	void update(float deltaTime);

	/// @brief a boolean to see if the unit is being selected or not
	bool selected;
};

#endif /* BASICUNIT_H */
