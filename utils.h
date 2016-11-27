#ifndef utils_h
#define utils_h

#include <stdlib.h>
#include <time.h>

class Random
{
public:
	Random()
	{
		//srand((unsigned int)time(0));
	}
	double random()
	{
		
		return (double)rand()/(double)RAND_MAX;
	}
};

double erand48( unsigned short xsubi[3]);

#endif