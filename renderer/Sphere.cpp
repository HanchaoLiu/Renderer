#include "Sphere.h"


//return the distance t;
double Sphere::intersect(
	const Ray& r) const
{
	Vec op = center- r.o;
	double t;
	double eps= 1e-4;
	double b= op.dot(r.d);
	double det
		=b*b-op.dot(op)+rad*rad;
	if (det<0) 
		return 0;
	else 
		det= sqrt(det);

	return 
		(t=b-det)>eps ? t : 
		((t=b+det)>eps ? t : 0);

}

Vec Sphere::getNormal(Point p)
{
	return (p- center).norm();
}