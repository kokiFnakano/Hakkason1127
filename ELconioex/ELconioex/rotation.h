
#ifndef VEC4_H
#define VEC4_H
#include "vec4.h"
#endif
class Rotation
{
public:
	double z;//z
	double y;//y axis
	double x;//x

	Rotation();
	Rotation(double x,double y,double z);
	
	vec4 getright();
	vec4 getfoward();
	vec4 getup();
	
	void operator+=(const Rotation &r);
	
	static Rotation vtor(vec4 v);

	static vec4 rot3d(vec4 tgt, Rotation rot);
	static vec4 rotrev(vec4 tgt, Rotation rot);

};
