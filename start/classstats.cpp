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
			HPAllocater = 24;
		}
		if (baseclass = 1) {
			HPAllocater = 19;
		}
		if (baseclass = 2) {
			HPAllocater = 30;
		}
		return HPAllocater;
	}
	else if (stat = 1) {
		if (baseclass = 0) {
			DamAllocater = 21;
		}
		if (baseclass = 1) {
			DamAllocater = 19;
		}
		if (baseclass = 2) {
			DamAllocater = 28;
		}
		return DamAllocater;
	}
	else if (stat = 2) {
		if (baseclass = 0) {
			HitAllocater = 140;
		}
		if (baseclass = 1) {
			HitAllocater = 125;
		}
		if (baseclass = 2) {
			HitAllocater = 105;
		}
		return HitAllocater;
	}
	else if (stat  = 3) {
		if (baseclass = 0) {
			AvoAllocater = 40;
		}
		if (baseclass = 1) {
			AvoAllocater = 30;
		}
		if (baseclass = 2) {
			AvoAllocater = 10;
		}
		return AvoAllocater;
	}
	else if (stat = 4) {
		if (baseclass = 0) {
			DefAllocater = 10;
		}
		if (baseclass = 1) {
			DefAllocater = 12;
		}
		if (baseclass = 2) {
			DefAllocater = 15;
		}
		return DefAllocater;
	}
	else if (stat = 5) {
		if (baseclass = 0) {
			MovAllocater = 6;
		}
		if (baseclass = 1) {
			MovAllocater = 5;
		}
		if (baseclass = 2) {
			MovAllocater = 5;
		}
		return MovAllocater;
	}
	else {
		return 0;
	}
}
