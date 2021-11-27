#pragma once
#define CONIOEX
#include"conioex.h"



typedef struct Arrow
{
	//座標関連
	int originPosX,originPosY;		// 回転の原点

	//方向関連
	float startVecX, startVecY;		// 始点方向ベクトル
	float endVecX, endVecY;			// 終点方向ベクトル
	float vecX, vecY;				// 現在のベクトル

	//回転関連
	int rotateCount;				// 片道にかかるカウント
	int count;						// 現在のカウント
	bool isReverse = false;			// 復路かのフラグ

	//その他
	bool isUse = false;				// 使用中かのフラグ
};




void Init_Arrow(int id, int posX, int posY, float startX, float startY, float endX, float endY, int count);
void SetArrowUse(int id, bool use);
void Update_Arrow(int id);
void Draw_Arrow(int id, int pointNum);
void DrawArrow(int x, int y);
Arrow* Get_Arrow(int id);