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

	//Stat: HP = 0, Dam = 1, Hit = 2, Avo = 3, Def = 4, Mov = 5
	//Baseclass: 0 = Swordsman, 1 = Lancer, 3 = Axefighter
	statAllocater = statSource->GetStat(stat, baseclass);

	return statAllocater;
}