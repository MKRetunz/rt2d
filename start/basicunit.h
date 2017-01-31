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

	/// @brief makeunit adds all the stats and calls the sprite allocator
	/// @return void
	void makeUnit();

	/// @brief attacking inflicts damage on the target
	/// @param BasicUnit is the target for this to attack
	/// @return void
	void attack(BasicUnit* unit);

	/// @brief the classstats, used to allocate the stats.
	ClassStats* cs;

	/// @brief a int that contains the units class
	int unitClass;

	/// @brief the total amount of hitpoints the unit has
	int HitPoints;

	/// @brief the damage a unit deals
	int Damage;

	/// @brief the base hit a unit has
	int Hit;

	/// @brief the avoid a unit has, lowering the attackers hit
	int Avoid;

	/// @brief the defense a unit has, lowering the attacker's damage
	int Defense;

	/// @brief the ammount of tiles a unit may move
	int Move;

	/// @brief a boolean to see if the unit is being selected or not
	bool selected;

	/// @brief a boolean to see which team the unit is on
	bool unitTeam;

	/// @brief a boolean to see if a unit has done their turn
	bool turnDone;

private:

	/// @brief a float to move the animation forward
	float scounter;

	/// @brief a int that moves the animation
	int frame;

	/// @brief a int that keeps track of the current frame of the animation
	int fcounter;

	/// @brief a boolean to control the attack animation
	bool attacking;
};

#endif /* BASICUNIT_H */
