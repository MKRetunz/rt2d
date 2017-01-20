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

	//HP = 0, Dam = 1, Hit = 2, Avo = 3, Def = 4, Mov = 5
	statAllocater = statSource->GetStat(stat, baseclass);

	return statAllocater;
}