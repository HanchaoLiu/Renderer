#ifndef Triangle_h
#define Triangle_h

#include "Vec.h"
#include "object.h"

class Triangle : public Object
{
public:
    Point p1, p2, p3;
    Vec normal;
	Point vertex_m[3];
    
    Triangle(Point _p1, Point _p2, Point _p3,
		Vec c_, Vec e_, refl_t refl_
		)
    {
        p1= _p1;
        p2= _p2;
        p3= _p3;
        normal= (p2- p1)%(p3- p2);
        normal.norm();
		e= e_;
		c= c_;
		refl= refl_;

		vertex_m[0]= p1;
		vertex_m[1]= p2;
		vertex_m[2]= p3;

    }

	void getBound(double bound[]) const;

	bool getIntersection
	(
	   const Vec& rayOrigin,
	   const Vec& rayDirection,
	   double&         hitDistance_o
	) const;

	void geo()
	{
		cout<<"Triangle"<<endl;
	}

	Vec getNormal( Point p);
};

inline double max3(double x, double y, double z);
inline double min3(double x, double y, double z);
#endif