#include "PathTracer.h"
#include "utils.h"

Vec pathTracer::radiance(const Ray& ray, int depth ,Random& random)
{
	Object* id= 0;
	double t= INF;
	if ( !scene.intersect(ray, id, t) )
		return Vec(0,0,0);
	Point p= ray.o+ ray.d*t;
	Vec n= id->getNormal(p);
	//cout<<"t= "<<t<<endl;
	//cout<<"n= "<<n<<endl;
	//try
	//{
	//	Triangle* idd= (Triangle*)id;
	//	cout<<idd->p1<<" "<<idd->p2<<" "<<idd->p3<<endl;
	//}
	//catch(...)
	//{
	//	cout<<"not a triangle"<<endl;
	//}

	bool isIn= ray.d.dot(n)<0? 0:1;
	Vec nl= (!isIn)? n: n*-1;
		Vec f = id->c;
	//cout<<"nl= "<<nl<<endl;

	double pp = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl
    if (++depth>5) 
		if (random.random() < pp) 
			f=f*(1/pp); 
	else 
		return id->e; //R.R.

	if (id->refl == DIFF)
	{                  // Ideal DIFFUSE reflection
		double r1= 2*M_PI*random.random();
		double r2 = random.random();

		double r2s = sqrt(r2);
		Vec w= nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
		Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
		Ray rr(p, d); 
		//cout<<"ray= "<<rr.o<<" "<<rr.d<<endl;
		return id->e + f.mult(radiance(rr,depth, random));
	}
	else if (id->refl == DIFFS)
	{                  // Ideal DIFFUSE reflection
		double r1= 2*M_PI*random.random();
		double r2 = random.random();
		double r2s = sqrt(r2);
		Vec w= nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
		Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
		Ray rr(p, ray.d-n*2*n.dot(ray.d)); 

		// should be in Object class
		Vec spec_coef = Vec(1,1,1); 
		double glossy= 1;

		Vec shading= spec_coef.mult(pow(d.dot( rr.d ), glossy))*(1/( rr.d.dot( nl )));
		Vec sp= f + shading ;
		return id->e + sp.mult(radiance(Ray(p,d),depth,random));
	}
	else if (id->refl == SPEC)            // Ideal SPECULAR reflection
		return id->e + f.mult(radiance(Ray(p,ray.d-n*2*n.dot(ray.d)),depth,random));

	else if (id->refl == REFR)
	{
		Ray reflRay(p, ray.d-n*2*n.dot(ray.d));     // Ideal dielectric REFRACTION
		bool into = n.dot(nl)>0;                // Ray from outside going in?
		double nc=1, nt=1.55, nnt=into?nc/nt:nt/nc, ddn=ray.d.dot(nl), cos2t;
		if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection
			return id->e + f.mult(radiance(reflRay,depth,random));

		Vec tdir = (ray.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
		double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));
		double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
		return id->e + f.mult(depth>2 ? (random.random()<P ?   // Russian roulette
			radiance(reflRay,depth,random)*RP:radiance(Ray(p,tdir),depth,random)*TP) :
		radiance(reflRay,depth,random)*Re+radiance(Ray(p,tdir),depth,random)*Tr);
	}

}

Vec pathTracer::radiance(const Ray& ray, int depth , unsigned short * Xi)
{
	Object* id= 0;
	double t= INF;
	if ( !scene.intersect(ray, id, t) )
		return Vec(0,0,0);
	Point p= ray.o+ ray.d*t;
	Vec n= id->getNormal(p);
	//cout<<"t= "<<t<<endl;
	//cout<<"n= "<<n<<endl;
	//try
	//{
	//	Triangle* idd= (Triangle*)id;
	//	cout<<idd->p1<<" "<<idd->p2<<" "<<idd->p3<<endl;
	//}
	//catch(...)
	//{
	//	cout<<"not a triangle"<<endl;
	//}

	bool isIn= ray.d.dot(n)<0? 0:1;
	Vec nl= (!isIn)? n: n*-1;
	Vec f = id->c;
	//cout<<"nl= "<<nl<<endl;

	double pp = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl
    if (++depth>5) 
		if (erand48(Xi) < pp) 
			f=f*(1/pp); 
	else 
		return id->e; //R.R.

	if (id->refl == DIFF)
	{                  // Ideal DIFFUSE reflection
		double r1= 2*M_PI*erand48(Xi);
		double r2 = erand48(Xi);

		double r2s = sqrt(r2);
		Vec w= nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
		Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
		Ray rr(p, d); 
		//cout<<"ray= "<<rr.o<<" "<<rr.d<<endl;
		return id->e + f.mult(radiance(rr,depth, Xi));
	}
	else if (id->refl == DIFFS)
	{                  // Ideal DIFFUSE reflection
		double r1= 2*M_PI*erand48(Xi);
		double r2 = erand48(Xi);
		double r2s = sqrt(r2);
		Vec w= nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
		Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
		Ray rr(p, ray.d-n*2*n.dot(ray.d)); 

		// should be in Object class
		double kk= 1;
		double glossy= 10;

		double shading= kk* pow(d.dot( rr.d ), glossy)/( rr.d.dot( nl ));
		double sp= 1+ shading;
		return id->e + (f*sp).mult(radiance(Ray(p,d),depth,Xi));
	}
	else if (id->refl == SPEC)            // Ideal SPECULAR reflection
		return id->e + f.mult(radiance(Ray(p,ray.d-n*2*n.dot(ray.d)),depth,Xi));

}