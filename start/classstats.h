#ifndef CLASSSTATS_H
#define CLASSSTATS_H

class ClassStats
{
public:
	ClassStats();
	virtual ~ClassStats();

	int GetStat(int stat, int baseclass);

private:

	int HPAllocater;
	int DamAllocater;
	int HitAllocater;
	int AvoAllocater;
	int DefAllocater;
	int MovAllocater;
};

#endif /* CLASSSTATS_H */