#pragma once

#ifndef SELECTOR_H
#define SELECTOR_H

#include <rt2d/entity.h>

class selector : public Entity
{
public:
	selector();
	~selector();
	virtual void update(float deltatime);
};

#endif /*SELECTOR_H*/