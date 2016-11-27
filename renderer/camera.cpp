#include "camera.h"
#include <math.h>

Vec Camera::drawPixel(double x, double y)
{
	double focus = w*ratio/tan(fov/2)/2.0;
	double xx= (x- w/2.0)*ratio/focus;
	double yy= -(y- h/2.0)/focus;
	Vec dir= view_dir+ w_vec*xx+ h_vec*yy;
	dir.norm();
	/*cout<<w_vec<<" "<<h_vec<<endl;
	cout<<"dir = "<<dir<<endl;*/
	return pTracer.radiance(Ray(view_pos, dir),0, ra);
}

Vec Camera::drawSubPixel(int x, int y)
{
	Vec res(0,0,0);
	for (int sx= 0; sx<2 ;sx++)
	{
		for (int sy= 0; sy< 2; sy++)
		{
			
			double r1=2*ra.random(), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
			double r2=2*ra.random(), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);
			double jt_x= (sx+ 0.5 + dx)/2;
			double jt_y= (sy+ 0.5 + dy)/2;
			Vec pixel = drawPixel(x+ jt_x, y+jt_y);
			//clamp(pixel);
			res= res+ pixel*0.25;
			
		}
	}
	return res;
}

void Camera::clamp(Vec & re)
{
	re.x= re.x>1? 1: ( re.x< 0? 0: re.x );
	re.y= re.y>1? 1: ( re.y< 0? 0: re.y );
	re.z= re.z>1? 1: ( re.z< 0? 0: re.z );
	

}

double Camera::clamp( double x)
{
	return x>1? 1:x<0?0:x;
}

double clamp2( double x)
{
	return x> 1? 1: (x< 0 ? 0: x);
}


int toInt(double val)
	{
		return int(pow(clamp2(val),1/2.2)*255+.5);
	}

void Camera::renderFrame(int sample)
{	
	Vec* pic= new Vec[w*h];
	int cnt= 0;
	int samples= sample/4;
	for (int x= 0; x< w; x++)
	{
		fprintf(stderr, "\rRendering %.2f %%", x*100.0/h);
		for (int y= 0; y< h; y++)
		{
			Vec re(0,0,0);
			for (int s= 0; s< samples ;s++)
			{
				re = re+ drawSubPixel(x, y);
			}
			re= re*(1.0/samples);
			clamp(re);
			pic[cnt++]= re;
			//cout<<re<<endl;
		}
	}

	

	FILE *f = fopen("myTracer.ppm", "w");
	fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
	for (int i=0; i< w*h; i++)
		fprintf(f,"%d %d %d ", toInt(pic[i].x), 
						       toInt(pic[i].y),
						       toInt(pic[i].z) );
}

void Camera::renderSmallPt(int samples, char* imgname)
{
	int samps= samples/4; 
	Ray cam2(view_pos, view_dir.norm());
	double fov2= 2*tan(fov/2)/ratio;
	//fov2= 0.5135;


	Vec cx= Vec(w*fov2/h,0,0);
	Vec cy= Vec(cx%cam2.d).norm()*fov2;
	Vec r;
	Vec* c= new Vec[w*h];


	for (int y=0; y<h; y++)
	{                       // Loop over image rows
		fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
		for (unsigned short x=0; x<w; x++)   // Loop cols
		{
			unsigned short Xi[3]={0,0,y*y*y};
			int i= (h-y-1)*w+x;
			
			for (int sy= 0; sy<2; sy++)
				for (int sx= 0; sx<2; sx++)
				{
					r= Vec(0,0,0);
					for (int s= 0; s< samps; s++)
					{
						double r1= 2*erand48(Xi);
						double r2= 2*erand48(Xi);
						double dx= r1<1? sqrt(r1)-1:
							1-sqrt(2-r1);
						double dy= r2<1? sqrt(r2)-1:
							1-sqrt(2-r2);
						Vec d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) +
						cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + cam2.d;
						Ray sampleRay(cam2.o, d.norm());
						//r= r+ pTracer.radiance(sampleRay, 0, ra)
						//	*(1.0/samps);
						r= r+ pTracer.radiance(sampleRay, 0, ra)
							*(1.0/samps);

						
					}
					c[i] = c[i] + Vec(clamp(r.x),clamp(r.y),clamp(r.z))*.25;
				}

		}
	}
	
	FILE* f;
	f= fopen( imgname, "w");
	fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
	for (int i= 0; i< w*h; i++)
		fprintf(f, "%d %d %d ", toInt(c[i].x), toInt(c[i].y),
		toInt(c[i].z));
}

void Camera::renderCube(int samples)
{
	int samps= samples/4;
	Ray cam2(Vec(50,52,295.6), Vec(0,-0.042612,-1).norm()); // cam pos, dir
	Vec cx, cy;
	cx = Vec(w*.5135/h);
	cy=(cx%cam2.d).norm()*.5135;

	Vec r;
	Vec* c=new Vec[w*h];

	#pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP

	for (int y=0; y<h; y++)
	{                       // Loop over image rows
		fprintf(stderr,"\rRendering (%d spp) %5.2f%%",samps*4,100.*y/(h-1));
		for (unsigned short x=0; x<w; x++)   // Loop cols
		{
			unsigned short Xi[3]={0,0,y*y*y};
			for (int sy=0, i=(h-y-1)*w+x; sy<2; sy++)     // 2x2 subpixel rows
			for (int sx=0; sx<2; sx++, r=Vec())
			{        // 2x2 subpixel cols
				for (int s=0; s<samps; s++)
				{
					double r1=2*erand48(Xi), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
					double r2=2*erand48(Xi), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);

					Vec d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) +
                    cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + cam2.d;
					r = r + pTracer.radiance(Ray(cam2.o+d*140,d.norm()),0,Xi)*(1./samps);
				}
				c[i] = c[i] + Vec(clamp(r.x),clamp(r.y),clamp(r.z))*.25;
			}
		}
	}
	FILE *f = fopen("image_cube.ppm", "w");         // Write image to PPM file.
	fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
	for (int i=0; i<w*h; i++)
    fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z));
	//test_vec();
}
