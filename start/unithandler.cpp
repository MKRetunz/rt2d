#include "unithandler.h"

UnitHandler::UnitHandler()
{
	statSource = new ClassStats();
}


UnitHandler::~UnitHandler()
{

}

int UnitHandler::AllocateStats(int stat, int baseclass) {
	int statAllocater = 0;

	if (stat = 0) {
		statAllocater = statSource->GetStat(stat);
	}

	return statAllocater;
}