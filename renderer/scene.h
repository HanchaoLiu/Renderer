#ifndef scene_h
#define scene_h

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Vec.h"
#include "Triangle.h"
#include "Sphere.h"
#include "spatialIndex.h"
using namespace std;

class Scene
{
public:
	string filename;
	int iteration, w, h;
    Vec v1, v2, v3, v4;
    double angle;
	vector<Triangle>triList;
	vector<Sphere>sphList;
	//vector<Sphere>sphList;
	
	void read_file(string fname, int& iteration, int& w,
	int& h, Vec& v1, Vec& v2, Vec& v3, Vec& v4,
	double& angle, vector<Triangle>& buf);

	SpatialIndex* octree;

	Scene(string _filename)
	{
		filename= _filename;
		read_file(filename, iteration, w, h,
			v1, v2, v3, v4, angle, triList);
		octree = new SpatialIndex(v1, triList);

		 //manually add spheres
		sphList.push_back(Sphere(Vec(0.15,0.1,0.32),0.1,
			Vec(0.99,0.99,0.99),Vec(0,0,0),refl_t::REFR));
		sphList.push_back(Sphere(Vec(0.4,0.1,0.45),0.1,
			Vec(187.0/255,117.0/255,7.0/255),Vec(0,0,0),refl_t::DIFFS));

		//Sphere spheres[] = {//Scene: radius, position, emission, color, material
		//  Sphere(Vec( 1e5+1,40.8,81.6),1e5,  Vec(.75,.25,.25),Vec(),DIFF),//Left
		//  Sphere(Vec(-1e5+99,40.8,81.6),1e5, Vec(.25,.25,.75),Vec(),DIFF),//Rght
		//  Sphere( Vec(50,40.8, 1e5), 1e5,    Vec(.75,.75,.75),Vec(),DIFF),//Back
		//  Sphere( Vec(50,40.8,-1e5+170),1e5, Vec(),           Vec(),DIFF),//Frnt
		//  Sphere(Vec(50, 1e5, 81.6), 1e5,    Vec(.75,.75,.75),Vec(),DIFF),//Botm
		//  Sphere(Vec(50,-1e5+81.6,81.6),1e5, Vec(.75,.75,.75),Vec(),DIFF),//Top
  //
		//  Sphere(Vec(27,16.5,47), 16.5,      Vec(1,1,1)*0.4,  Vec(),DIFF),//Mirr
  //
  //
		//  Sphere(Vec(73,16.5,78), 16.5,      Vec(1,1,1)*0.4,  Vec(),DIFF),//Glas
		//  Sphere( Vec(50,681.6-.27,81.6),600, Vec(),Vec(12,12,12), DIFF) //Lite
		//};
		//for (int i= 0; i< 9; i++)
		//	sphList.push_back(spheres[i]);

	}
	Scene(){};

	bool intersect(const Ray& ray, Object* & id, double & tt);
};

#endif