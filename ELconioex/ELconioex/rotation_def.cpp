
#ifndef ROTATION_H
#define ROTATION_H
#include "rotation.h"
#endif
#include<math.h>

vec4 Rotation::getright()
{
	vec4 buf;
	buf.x = 1;
	return buf = Rotation::rot3d(buf,*this);
}

vec4 Rotation::getfoward()
{
	vec4 buf;
	buf.z = 1;
	return buf = Rotation::rot3d(buf, *this);
}

vec4 Rotation::getup()
{
	vec4 buf;
	buf.y = 1;
	return buf = Rotation::rot3d(buf, *this);
}

vec4 Rotation::rot3d(vec4 tgt, Rotation rot)
{

	vec4 buf;
	vec4 res;
	Rotation rotbuf;

	//y
	//c -s 0 x
	//s c 0 y 
	//0 0 1 z



	rotbuf.z = rot.z / (180.00 / 3.1415926f);

	buf.x = (tgt.x * cos(rotbuf.z)) + (tgt.y * -sin(rotbuf.z));
	buf.y = (tgt.x * sin(rotbuf.z)) + (tgt.y * cos(rotbuf.z));
	buf.z = tgt.z;

	res = buf;

	//p
		// c 0 s
		//0 1 0
		//-s 0 c

	

	//r
	//1 0 0
//	0 c -s
	//0 s c

	rotbuf.x = rot.x / (180.00 / 3.1415926);

	buf.x = res.x;
	buf.y = (res.y * cos(rotbuf.x)) + (res.z * -sin(rotbuf.x));
	buf.z = (res.y * sin(rotbuf.x)) + (res.z * cos(rotbuf.x));

res=buf;

rotbuf.y = rot.y / (180.00 / 3.1415926f);

	buf.x = (res.x * cos(rotbuf.y)) + (res.z * sin(rotbuf.y));
	buf.y = res.y;
	buf.z = (res.x * -sin(rotbuf.y)) + (res.z * cos(rotbuf.y));

	res = buf;

	return buf;
}

vec4 Rotation::rotrev(vec4 tgt, Rotation rot)
{
	vec4 buf;
	vec4 res;
	Rotation rotbuf;

		rot.x *= -1;	
		rot.y *= -1;
		rot.z *= -1;

		//y
//c -s 0 x
//s c 0 y 
//0 0 1 z


	buf = tgt;


	res = buf;
	rotbuf.y = rot.y / (180.00 / 3.1415926f);

	buf.x = (res.x * cos(rotbuf.y)) + (res.z * sin(rotbuf.y));
	buf.y = res.y;
	buf.z = (res.x * -sin(rotbuf.y)) + (res.z * cos(rotbuf.y));
	

	res = buf;

	rotbuf.x = rot.x / (180.00 / 3.1415926f);

	buf.x = res.x;
	buf.y = (res.y * cos(rotbuf.x)) + (res.z * -sin(rotbuf.x));
	buf.z = (res.y * sin(rotbuf.x)) + (res.z * cos(rotbuf.x));



	res = buf;
	rotbuf.z = rot.z / (180.00 / 3.1415926f);

	buf.x = (res.x * cos(rotbuf.z)) + (res.y * -sin(rotbuf.z));
	buf.y = (res.x * sin(rotbuf.z)) + (res.y * cos(rotbuf.z));
	buf.z = res.z;

	return buf;
}


Rotation Rotation::vtor(vec4 tgt)
{
vec4 buf=tgt;
Rotation rb;

buf=vec4::normalize(buf);

rb.x=asin(-buf.y)*(180/3.1415926f);
rb.y=atan2(buf.x,buf.z)*(180/3.1415926f);

rb.z=0;

return rb;
}
Rotation::Rotation(double x,double y,double z)
{
	this->x=x;
	this->y=y;
	this->z=z;

}

void Rotation::operator+=(const Rotation &r)
{
	this->x+=r.x;
	this->y+=r.y;
	this->z+=r.z;
}