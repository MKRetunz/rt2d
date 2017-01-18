#ifndef UNITHANDLER_H
#define UNITHANDLER_H

#include "classstats.h"

class UnitHandler
{
public:
	UnitHandler();
	virtual ~UnitHandler();

	int AllocateStats(int stat);

private:

};

#endif /* UNITHANDLER_H */