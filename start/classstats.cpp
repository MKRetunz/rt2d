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
		return HPAllocater;
	}
	else if (stat = 1) {
		return DamAllocater;
	}
	else if (stat = 2) {
		return HitAllocater;
	}
	else if (stat  = 3) {
		return AvoAllocater;
	}
	else if (stat = 4) {
		return DefAllocater;
	}
	else if (stat = 5) {
		return MovAllocater;
	}
	else {
		return 0;
	}
}
