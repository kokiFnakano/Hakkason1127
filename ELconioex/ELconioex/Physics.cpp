#include "Physics.h"

#include<stdio.h>
#include <math.h>
vec4 Reflection(vec4 v1, vec4 sur);
vec4 Surface(vec4 val);

Transform::Transform()
{
    Pos = vec4(0, 0, 0, 0);
    //半径
    Size = 0;
    //Euler 360Degree
    Rot = 0;
    Phys=PhysicsMaterial(0,0);
}
  vec4 Transform::rotate(vec4 pos,float rot)
  {
      float val =rot / (180.00 / 3.1415926f);
    return vec4
    (
      cos(val)*pos.x-sin(val)*pos.y,
      sin(val)*pos.x+cos(val)*pos.y,
      0,0
    );
  }
vec4 Transform::GetFoward()
{
    return Transform::rotate(vec4(0,1,0,0),this->Rot);
}
void Transform::AddForce(float x,float y, float force)
{
  vec4 dir=vec4::normalize(vec4(x,y,0,0));    
  this->Phys.Force=force;
  this->Rot=Rotation::vtor(dir).z;
}
void Transform::AddForce(float degree, float force)
{
    this->Phys.Force=force;
  this->Rot=degree;
}


void PhysicsManager::ApplyForce()
{

    for (int i = 0; i < ObjectList.size(); i++)  
    {

        //APPLY ROTATION TO FOWARD VECTOR
        //方向ベクターを取得
        vec4 Dir = ObjectList[i]->GetFoward();
        //printf("DIR:X:%f,y:%f\n",Dir.x,Dir.y);
        //Ugokasu
        //方向に動かす
        //printf("POS:X:%f,y:%f\n",ObjectList[i]->Pos.x,ObjectList[i]->Pos.y);

        ObjectList[i]->Pos += Dir *ObjectList[i]->Phys.Force;
        //printf("FORCE:%f\n",ObjectList[i]->Phys.Force);
        //摩擦適用
        ObjectList[i]->Phys.Force *=0.98;// ObjectList[i]->Phys.Weight;
    }
}

void PhysicsManager::FindCollision()
{
    float size;
    Collision col;
    vec4 buf;

    float dist;
    //Find COLLIDER1
    //コライダー　ループ
    for (int i = 0; i < ObjectList.size() - 1; i++)
    {
        //Kyori
        //コライダー大きさ
        size = ObjectList[i]->Size;

        //SEARCH THRU ALL FURTHER OBJECTS
        //他コライダーと距離判定
        for (int a = i + 1; a < ObjectList.size(); a++)
        {
            //2Tsu no kyori wo dasu
            //距離取得
            dist = vec4::dist(ObjectList[i]->Pos , ObjectList[a]->Pos);
              //printf("%f\n",dist);
            //printf("\nDIST:%f\nSIZE:%f\n",dist,size);
            //IF COLLIDED
            //距離を比べる
            if (size > dist/2)
            {
              
//              printf("col");
                //ADD TO COLLISION LIST
                CollisionList.push_back(Collision(i, a));
                
            }
        }
    }
}

void PhysicsManager::ResolveCollision()
{
    vec4 sur;
    float power;

    Transform *t1, *t2;
    for (int i = 0; i < CollisionList.size(); i++)
    {
        t1 = ObjectList[CollisionList[i].P1];
        t2 = ObjectList[CollisionList[i].P2];

        //衝突表面
        sur = Surface(t2->Pos - t1->Pos);
        power = (t2->Phys.Force + t1->Phys.Force) / 2;

        //Get the Foward Vector
        //Reflect
        //Convert Back to Euler
        //正面ベクターを取得
        //衝突点を軸に反射したベクターを生成
        //オイラー回転に変換
        t1->Rot =
            Rotation::vtor(
                Reflection(t1->GetFoward(), sur))
                .y;
        t2->Rot =
            Rotation::vtor(
                Reflection(t2->GetFoward(), sur))
                .y;
        t1->Phys.Force = power;
        t2->Phys.Force = power;
    }
    CollisionList.clear();
}

vec4 Reflection(vec4 v1, vec4 sur)
{
  //Surを軸にV1ベクターを反射
    return v1 - (sur * (vec4::dot(v1, sur) * 2));
}

vec4 Surface(vec4 val)
{
  //ベクターの直角となるユニットベクター生成
    return vec4::normalize(vec4(-val.y, val.x, 0, 0));
}


   