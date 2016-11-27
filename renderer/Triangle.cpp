#include "Triangle.h"

#define TOLERANCE 1.0/1024.0
#define EPSILON 1e-5

double max3(double x, double y, double z)
{
	double a1= x> y? x:y;
	double a2= a1>z? a1:z;
	return a2;
}

double min3(double x, double y, double z)
{
	double a1= x<y? x:y;
	double a2= z<a1? z: a1;
	return a2;
}

//void Triangle::getBound(double bound[])const
//{
//	bound[3]= max3(p1.x, p2.x, p3.x);
//	bound[4]= max3(p1.y, p2.y, p3.y);
//	bound[5]= max3(p1.z, p2.z, p3.z);
//
//	bound[0]= min3(p1.x, p2.x, p3.x);
//	bound[1]= min3(p1.y, p2.y, p3.y);
//	bound[2]= min3(p1.z, p2.z, p3.z);
//}

void Triangle::getBound
(
   double bound[6]
) const
{
   // initialize
   for( int i = 6;  i-- > 0;  bound[i] = vertex_m[2][i % 3] ) {}

   // expand
   for( int i = 0;  i < 3;  ++i )
   {
      for( int j = 0, d = 0, m = 0;  j < 6;  ++j, d = j / 3, m = j % 3 )
      {
         // include some tolerance

         const double v = vertex_m[i][m] + ((d ? 1.0 : -1.0) * TOLERANCE);
         bound[j] = (bound[j] > v) ^ d ? v : bound[j];
      }
   }
}

bool Triangle::getIntersection
(
   const Vec& rayOrigin,
   const Vec& rayDirection,
   double&         hitDistance_o
) const
{
   // find vectors for two edges sharing vert0
   Vec edge1( p2-p1 );
   Vec edge2( p3-p1 );

   // begin calculating determinant - also used to calculate U parameter
   Vec pvec( const_cast<Vec&>(rayDirection)%edge2 );

   // if determinant is near zero, ray lies in plane of triangle
   const double det = edge1.dot( pvec );

   bool isHit = false;
   if( (det <= -EPSILON) | (det >= EPSILON) )
   {
      const double inv_det = 1.0 / det;

      // calculate distance from vertex 0 to ray origin
      Vec tvec( rayOrigin - p1 );

      // calculate U parameter and test bounds
      const double u = tvec.dot( pvec ) * inv_det;
      if( (u >= 0.0) & (u <= 1.0) )
      {
         // prepare to test V parameter
         Vec qvec( tvec % edge1 );

         // calculate V parameter and test bounds
         const double v = rayDirection.dot( qvec ) * inv_det;
         if( (v >= 0.0) & (u + v <= 1.0) )
         {
            // calculate t, ray intersects triangle
            hitDistance_o = edge2.dot( qvec ) * inv_det;

            // only allow intersections in the forward ray direction
            isHit = (hitDistance_o >= EPSILON);
         }
      }
   }

   return isHit;
}

Vec Triangle::getNormal(Point p)
{
	return normal;
}