#ifndef ROTATION_H
#define ROTATION_H
#include "rotation.h"
#endif

#ifndef VEC4_H
#define VEC4_H
#include "vec4.h"
#endif
#include <math.h>

/*
void vec4::printv(int x,int y,const char *st)
{
	int a,b;
	a=x;
	b=y;
	setc(a,b);
	printf("###############");
	
	
	b++;
	setc(a,b);
	printf("%s:",st);
	
		b++;
	setc(a,b);
	printf("X :%lf",this->x);
	
	
		b++;
	setc(a,b);
	printf("Y :%lf",this->y);
		b++;
		setc(a,b);
	printf("Z :%lf",this->z);
	
		b++;
		setc(a,b);
	printf("###############");
}
*/
vec4::vec4(float X, float Y, float Z, float A)
{
	this->x = X;
	this->y = Y;
	this->z = Z;
	this->a = A;
}

Rotation::Rotation()
{
	z = 0;
	y = 0;
	x = 0;
}

vec4 vec4::zero()
{
	return vec4(0, 0, 0, 0);
}

vec4 vec4::one()
{
	return vec4(1, 1, 1, 1);
}

double vec4::tri_size(vec4 t1, vec4 t2, vec4 t3)
{

	//return abs((t1.x * (t2.y - t3.y) + t2.x * (t3.y - t1.y) + t3.x * (t1.y - t2.y)) / 2);

	float buf = (t1.x * (t2.y - t3.y) + t2.x * (t3.y - t1.y) + t3.x * (t1.y - t2.y)) / 2;

	if (buf < 0)
		buf *= -1;

	return buf;
}

vec4 vec4::lookat(vec4 from, vec4 to)
{
	return vec4::normalize(vec4::sub(to, from));
}

vec4 vec4::normalize(vec4 tgt)
{
	tgt.mult_self(1 / tgt.mag());
	return tgt;
}

void vec4::mult_self(float v)
{
	this->x *= v;
	this->y *= v;
	this->z *= v;
	this->a *= v;
}

vec4 vec4::sub(vec4 v1, vec4 v2)
{
	return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.a - v2.a);
}

vec4 vec4::add(vec4 v1, vec4 v2)
{
	return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.a + v2.a);
	/*
	vec4 buf;

	buf.x = v1.x + v2.x;
	buf.y = v1.y + v2.y;
	buf.z = v1.z + v2.z;
	buf.a = v1.a + v2.a;

	return buf;
	*/
}

void vec4::add_self(vec4 v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->a += v.a;
}

vec4 vec4::mult(vec4 v1, vec4 v2)
{
	return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.a * v2.a);
}

vec4::vec4()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
	this->a = 0;
}

void vec4::set(float x, float y, float z, float a)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->a = a;
}

void vec4::set(vec4 v)
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->a = v.a;
}

double vec4::mag()
{
	return sqrt((((this->x) * (this->x)) + ((this->y) * (this->y)) + ((this->z) * (this->z))));
}

double vec4::dist(vec4 from, vec4 to)
{
	return vec4(from.x - to.x, from.y - to.y, from.z - to.z, 0).mag();
}

vec4 vec4::operator*(const vec4 &v)
{
	return vec4(this->x * v.x, this->y * v.y, this->z * v.z, this->a * v.a);
}

void vec4::operator*=(const vec4 &v)
{
	this->x *= v.x;
	this->y *= v.y;
	this->z *= v.z;
	this->a *= v.a;
}

void vec4::operator+=(const vec4 &v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
	this->a += v.a;
}

vec4 vec4::operator+(const vec4 &v)
{
	return vec4(this->x + v.x, this->y + v.y, this->z + v.z, this->a + v.a);
}
vec4 vec4::operator-(const vec4 &v)
{
	return vec4(this->x - v.x, this->y - v.y, this->z + v.z, this->a - v.a);
}
void vec4::operator*=(const double &v)
{
	this->x *= v;
	this->y *= v;
	this->z *= v;
	this->a *= v;
}
vec4 vec4::operator*(const double &v)
{
	vec4 buf;
	buf.x = this->x * v;
	buf.y = this->y * v;
	buf.z = this->z * v;

	return buf;
}

vec4 vec4::operator/(const float &v)
{

	return (*this) * (1.0f / v);
}

vec4 vec4::normal(vec4 v1, vec4 v2)
{

	vec4 norm;
	norm.x = (v1.y * v2.z) - (v1.z * v2.y);
	norm.y = (v1.z * v2.x) - (v1.x * v2.z);
	norm.z = (v1.x * v2.y) - (v1.y * v2.x);

	return vec4::normalize(norm);
}

double vec4::dot(vec4 v1, vec4 v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z)) * 180 / 3.1415926f;
}

bool vec4::operator==(const vec4 &v)
{
	return (this->x == v.x && this->y == v.y && this->z == v.z && this->a == v.a);
}
