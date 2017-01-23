#include "ClassStats.h"



ClassStats::ClassStats()
{
	HPAllocater = 0;
	DamAllocater = 0;
	HitAllocater = 0;
	AvoAllocater = 0;
	DefAllocater = 0;
	MovAllocater = 0;
}


ClassStats::~ClassStats()
{

}

int ClassStats::GetStat(int stat, int baseclass)
{
	if (stat = 0) {
		if (baseclass = 0) {
			HPAllocater = 25; //12.5
		}
		if (baseclass = 1) {
			HPAllocater = 19; //9.5
		}
		if (baseclass = 2) {
			HPAllocater = 28; //14
		}
		return HPAllocater;
	}
	else if (stat = 1) {
		if (baseclass = 0) {
			DamAllocater = 21; //21
		}
		if (baseclass = 1) {
			DamAllocater = 18; //18
		}
		if (baseclass = 2) {
			DamAllocater = 24; //24
		}
		return DamAllocater;
	}
	else if (stat = 2) {
		if (baseclass = 0) {
			HitAllocater = 140; //14
		}
		if (baseclass = 1) {
			HitAllocater = 145; //14.5
		}
		if (baseclass = 2) {
			HitAllocater = 105; //10.5
		}
		return HitAllocater;
	}
	else if (stat  = 3) {
		if (baseclass = 0) {
			AvoAllocater = 50; //25
		}
		if (baseclass = 1) {
			AvoAllocater = 30; //15
		}
		if (baseclass = 2) {
			AvoAllocater = 10; //5
		}
		return AvoAllocater;
	}
	else if (stat = 4) {
		if (baseclass = 0) {
			DefAllocater = 10; //12.5
		}
		if (baseclass = 1) {
			DefAllocater = 12; //15
		}
		if (baseclass = 2) {
			DefAllocater = 14; //17.5
		}
		return DefAllocater;
	}
	else if (stat = 5) {
		if (baseclass = 0) {
			MovAllocater = 7; //28
		}
		if (baseclass = 1) {
			MovAllocater = 5; //20
		}
		if (baseclass = 2) {
			MovAllocater = 5; //20
		}
		return MovAllocater;
	}

	/* Total: 0 = 91 1 = 91 2 = 91 */

	else {
		return 0;
	}
}

void ClassStats::GetSprite(int baseclass, Entity* e)
{
	if (baseclass == 0) {
		e->addSprite("assets/mercenaryv1.tga");
	}
	else if (baseclass == 1)
	{
		e->addSprite("assets/soldierv1.tga");
	}
	else if (baseclass == 2) {
		e->addSprite("assets/fighterv1.tga");
	}
}

