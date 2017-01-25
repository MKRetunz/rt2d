#ifndef BASICUNIT_H
#define BASICUNIT_H

#include "entity.h"
#include "classstats.h"

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

	bool unitTeam;

	int unitClass;

	int HitPoints;

	int Damage;

	int Hit;

	int Avoid;

	int Defense;

	int Move;

	ClassStats* cs;

	void makeUnit();

	void attack(BasicUnit* unit);
};

#endif /* BASICUNIT_H */
