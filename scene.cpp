#include "scene.h"
#include "spatialIndex.h"

void Scene::read_file(string fname, int& iteration, int& w,
	int& h, Vec& v1, Vec& v2, Vec& v3, Vec& v4,
	double& angle, vector<Triangle>& buf)
{
	std::ifstream ifs (fname, std::ifstream::in);
	string head;
	ifs>>head;
	ifs>>iteration>>w>>h;
	cout<<iteration<<"---"<<endl;
	if (head!= "#MiniLight")
		return ;

	ifs>>v1>>v2;
	ifs>>angle;
	ifs>>v3>>v4;
	Vec v;
	string lines;
	Vec p1,p2,p3,e,c;
	
	while (ifs>>p1>>p2>>p3>>c>>e)
	{
		Triangle triInstance(p1,p2,p3,c,e,
			refl_t::DIFF);
		buf.push_back(triInstance);
	}
	ifs.close();
}

bool Scene::intersect(const Ray& ray, Object* & id, double & tt)
{
	Vec hit;
	const Triangle* ptr1= 0;
	Triangle* id_tri= 0;
	double tt_tri= INF;
	if ( triList.size() )
		octree->getIntersection(ray.o, ray.d, 0, ptr1, hit,tt_tri, id_tri, 0);
	bool isHit_tri= (tt_tri< INF);

	double tt_sph= INF;
	Sphere* id_sph= 0;
	double d;
	for (int idx= 0; idx< sphList.size(); idx++)
	{
		if ( ( d= sphList[idx].intersect(ray) )&&( d < tt_sph) )
		{
			tt_sph= d;
			id_sph= &sphList[idx];
		}
	}
	bool isHit_sph= (tt_sph < INF);
	if ( isHit_sph || isHit_tri )
	{
		if (tt_tri <= tt_sph )
		{
			id= id_tri;
			tt= tt_tri;
		}
		else
		{
			id= id_sph;
			tt= tt_sph;
		}
	}
	return (tt< INF);
}