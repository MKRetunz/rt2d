#ifndef BASICUNIT_H
#define BASICUNIT_H

#include "entity.h"
class basicunit :
	public Entity
{
public:
	basicunit();
	virtual ~basicunit();

	void update(float deltaTime);
};

#endif /* BASICUNIT_H */
