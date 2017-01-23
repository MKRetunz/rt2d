#ifndef CLASSSTATS_H
#define CLASSSTATS_H

#include "rt2d/entity.h"

class ClassStats
{
public:
	ClassStats();
	virtual ~ClassStats();

	int GetStat(int stat, int baseclass);

	void GetSprite(int baseclass, Entity* e);

private:

	int HPAllocater;
	int DamAllocater;
	int HitAllocater;
	int AvoAllocater;
	int DefAllocater;
	int MovAllocater;
};

#endif /* CLASSSTATS_H */