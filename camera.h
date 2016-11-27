#ifndef camera_h
#define camera_h


#include "Vec.h"
#include "PathTracer.h"

class Camera
{
public:
	Point view_pos;
	Vec view_dir;
	Vec lookUp;
	int w, h;
	double fov;
	Vec w_vec, h_vec;
	Scene sc;
	pathTracer pTracer;
	Random ra;
	double ratio;

	Camera(Point _view_pos, Vec _view_dir,
		Vec _lookUp, int _w, int _h, double _fov):
	view_pos(_view_pos),lookUp(_lookUp),
		w(_w),h(_h)
	{
		ratio = w*1.0/h;
		view_dir= _view_dir.norm();
		// normalized to : h -> [0, 1], w -> [0, w/h]
		w_vec = (view_dir % lookUp).norm()*ratio;
		h_vec =  ( view_dir % (w_vec*-1) ).norm();
		
		fov= _fov*M_PI/180;
		ra= Random();
	};

	void loadScene(Scene scene)
	{
		sc= Scene(scene);
		pTracer= pathTracer(sc);
	}

	Vec drawPixel(double x, double y);
	Vec drawSubPixel(int x, int y);
	void renderFrame(int samples);
	void clamp( Vec& pixel);
	double clamp( double x);
	void renderSmallPt(int samples, char* imgname);
	void renderCube(int samples);
};

int toInt(double val);
#endif