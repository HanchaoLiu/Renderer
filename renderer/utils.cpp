#include "utils.h"

double erand48( unsigned short xsubi[3])
{
	return (double)rand()/(double)RAND_MAX;
}