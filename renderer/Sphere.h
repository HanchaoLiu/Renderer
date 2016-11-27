#ifndef sphere_h
#define sphere_h

#include "Vec.h"
#include "object.h"

class Sphere : public Object
{
public:
	double rad;
	Vec center;
	Sphere(Vec _center, double _rad,
		Vec _c, Vec _e, refl_t _refl
		):
	center(_center), rad(_rad)
	{
		e= _e;
		c= _c;
		refl= _refl;
		
		
	}
	double intersect(const Ray& )const;
	void geo(){
		cout<<"sphere"<<endl;
	}
	Vec getNormal( Point p);
};


#endif