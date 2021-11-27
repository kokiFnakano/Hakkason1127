#pragma once
#define CONIOEX
#include"conioex.h"



typedef struct Arrow
{
	//座標関連
	int originPosX,originPosY;		// 回転の原点

	//方向関連
	float startAngle;				// 始点方向ベクトル
	float endAngle;					// 終点方向ベクトル
	float vecX, vecY;				// 現在のベクトル

	//回転関連
	int rotateCount;				// 片道にかかるカウント
	int count = 0;					// 現在のカウント
	bool isReverse = false;			// 復路かのフラグ

	//その他
	bool isUse = true;				// 使用中かのフラグ
};




void Init_Arrow(int id, int posX, int posY, int startAngle, int endAngle, int count);
void SetArrowUse(int id, bool use);
void Update_Arrow(int id);
void Draw_Arrow(int id, int pointNum);
void DrawArrow(int x, int y);
Arrow* Get_Arrow(int id);