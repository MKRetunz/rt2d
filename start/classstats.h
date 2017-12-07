#ifndef CLASSSTATS_H
#define CLASSSTATS_H

#include "rt2d/entity.h"

class ClassStats
{
public:

	/// @brief Constructor
	ClassStats();

	/// @brief Destructor
	virtual ~ClassStats();

	/// @brief allocates stats to the caller
	/// @param the stat to give and which class it originates from.
	/// @return int
	int GetStat(int stat, int baseclass);

	/// @brief allocates a sprite to the caller
	/// @param the entity to give a sprite and a bool to determine which sprite
	/// @return void
	void GetSprite(int baseclass, Entity* e, bool team);

private:

	/// @brief the allocator for the HP
	int HPAllocater;

	/// @brief the allocator for the Damage
	int DamAllocater;

	/// @brief the allocator for the Hit
	int HitAllocater;

	/// @brief the allocator for the Avoid
	int AvoAllocater;

	/// @brief the allocator for the Defense
	int DefAllocater;

	/// @brief the allocator for the Movement
	int MovAllocater;
};

#endif /* CLASSSTATS_H */