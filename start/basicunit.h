#ifndef BASICUNIT_H
#define BASICUNIT_H

#include "entity.h"
class BasicUnit :
	public Entity
{
public:
	BasicUnit();
	virtual ~BasicUnit();

	void update(float deltaTime);
};

#endif /* BASICUNIT_H */
