#include "scene.h"
#include "Vec.h"
#include "spatialIndex.h"
#include "PathTracer.h"
#include "camera.h"
#include <stdio.h>

double clamp(double r)
{
	return r> 1? 1:( r<0? 0 : r );
}



int main(int argc, char* argv[])
{
	
	Scene scene(argv[1]);
	
	Vec cam_pos= scene.v1;
	Vec cam_dir= scene.v2;
	Vec lookUp(0,1,0);

	cout<<cam_pos<<endl;
	cout<<cam_dir<<endl;
	cout<<scene.angle<<endl;

	Camera cam(cam_pos, cam_dir, lookUp, 
		scene.w, scene.h, scene.angle);
	cam.loadScene(scene);

	cout<<cam.pTracer.scene.triList.size()<<endl;
	cout<<cam.pTracer.scene.sphList.size()<<endl;

	//cam.renderFrame(scene.iteration);
	cam.renderSmallPt(scene.iteration, "zsw.ppm");
	cout<<"iteration= "<<scene.iteration<<endl;

	return 0;


}


