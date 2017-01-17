#ifndef CLASSSTATS_H
#define CLASSSTATS_H

class ClassStats
{
public:
	ClassStats();
	virtual ~ClassStats();

private:

	int HPAllocater;
	int DamAllocater;
	int HitAllocater;
	int AvoAllocater;
	int DefAllocater;
	int MovAllocater;
};

#endif /* CLASSSTATS_H */