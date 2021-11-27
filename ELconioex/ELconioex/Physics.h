
#include <vector>

#ifndef VEC4_H
#define VEC4_H
#include "vec4.h"
#endif
#ifndef ROTATION_H
#define ROTATION_H
#include "rotation.h"
#endif


class PhysicsMaterial
{
    //Butsuri Keisan You

public:
    float Force;
    float Weight;
    PhysicsMaterial(float force, float weight)
    {
        Force = force;
        Weight = weight;
    }
    PhysicsMaterial()
    {
        Force = 0;
        Weight = 0;
    }
};

class Transform
{
    //////////////
    //PURPOSE
    //BASIC TRANSFORM DATA
public:
    Transform();

    vec4 Pos;
    float Size;
    float Rot;

    PhysicsMaterial Phys;
    vec4 GetFoward();
    void AddForce(float x,float y,float Force);
    void AddForce(float Degree,float Force);
    static vec4 rotate(vec4 pos,float rot);
};
class Collision
{
public:
    int P1;
    int P2;
    Collision()
    {
        this->P1 = -1;
        this->P2 = -1;
    }

    Collision(int a, int b)
    {
        this->P1 = a;
        this->P2 = b;
    }

    bool operator==(const Collision v)
    {
        return (
            (this->P1 == v.P1 && this->P2 == v.P2) ||
            (this->P1 == v.P2 && this->P2 == v.P1));
    }
};

class PhysicsManager
{
public:
    std::vector<Transform *> ObjectList;
    std::vector<Collision> CollisionList;
    PhysicsManager(){};
    void ApplyForce();
    void FindCollision();
    void ResolveCollision();
};
