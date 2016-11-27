#ifndef object_h
#define object_h

#include "Vec.h"

class Object
{

public:
	Vec c, e;
	refl_t refl;
	//virtual Vec getNormal();
	virtual void geo()
	{
		cout<<"object"<<endl;
	}
	virtual Vec getNormal( Point p )=0;
};

#endif