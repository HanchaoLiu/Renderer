#ifndef Vec_h
#define Vec_h

#define INF 1e20
#define M_PI 3.1415926

#include <iostream>
using namespace std;

class Vec 
 {
 public:
    
   double x, y, z;                  // position, also color (r,g,b)
   Vec(double x_=0, double y_=0, double z_=0){ x=x_; y=y_; z=z_; }
   Vec (const Vec& _v){ x= _v.x; y= _v.y; z= _v.z;}
   Vec operator+(const Vec &b) const { return Vec(x+b.x,y+b.y,z+b.z); }
   Vec operator-(const Vec &b) const { return Vec(x-b.x,y-b.y,z-b.z); }
   Vec operator*(double b) const { return Vec(x*b,y*b,z*b); }
   double operator[](int i) const 
   {
       if (i==0) return x;
       if (i==1) return y;
       if (i==2) return z;
   }
   Vec mult(const Vec &b) const { return Vec(x*b.x,y*b.y,z*b.z); }
   Vec& norm(){ return *this = *this * (1/sqrt(x*x+y*y+z*z)); }
   double dot(const Vec &b) const { return x*b.x+y*b.y+z*b.z; } // cross:
   Vec operator%(Vec&b){return Vec(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}
 };

ostream& operator<< (ostream& output , const Vec& v);

istream& operator>> (istream& str, Vec& p);

typedef Vec Point;

class Ray 
 {public:
      Vec o, d; 
	  Ray(Vec o_, Vec d_) : o(o_), d(d_.norm()) {};
};

enum refl_t{ DIFF, SPEC, REFR, DIFFS};

#endif