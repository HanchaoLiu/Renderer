#include "Vec.h"

ostream& operator<< (ostream& output , const Vec& v)
{
	output<<" ("<<v[0]<<" "<<v[1]<<" "<<v[2]<<") ";
	return output;
}

istream& operator>> (istream& str, Vec& p)
{
	char c1, c2;
    double a1, a2, a3;
    str>>c1>>a1>>a2>>a3>>c2;
    Vec res(a1, a2, a3);
    p= res;
    return str;
}