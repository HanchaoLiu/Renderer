#ifndef pathTracer_h
#define pathTracer_h

#include "scene.h"
#include "utils.h"

class pathTracer
{
public:
	Scene scene;
	pathTracer(string filename)
		:scene(filename){};
	pathTracer(){};
	pathTracer(const Scene& _scene):scene(_scene){};
	Vec radiance(const Ray& ray, int depth ,Random& random);
	Vec radiance(const Ray& ray, int depth , unsigned short * Xi);
};


#endif