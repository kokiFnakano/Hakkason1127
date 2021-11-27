#include "Arrow.h"
#include <time.h>
#include "conioex.h"


static Arrow g_Arrow[4];





// 矢印の回転開始～終了角度と往復にかかる時間をセット
void Init_Arrow(int id, int posX, int posY, float startX, float startY, float endX, float endY, int count)
{
	//中心座標のセット
	g_Arrow[id].originPosX = posX;
	g_Arrow[id].originPosX = posY;

	// 回転変数の初期化
	g_Arrow[id].startVecX = startX;
	g_Arrow[id].startVecY = startY;
	g_Arrow[id].endVecX = endX;
	g_Arrow[id].endVecY = endY;


	g_Arrow[id].rotateCount = count;
}




// 矢印の使用状態をセットする
void SetArrowUse(int id, bool use)
{ 
	g_Arrow[id].isUse; 

	//回転情報を初期化
	if (!g_Arrow[id].isUse)
	{
		g_Arrow[id].count = 0;
		g_Arrow[id].isReverse = false;
	}
		
}




// 矢印の更新
void Update_Arrow(int id)
{
	if (g_Arrow[id].isUse)
	{
		g_Arrow[id].count = (g_Arrow[id].count + 1) % g_Arrow[id].count;

		// カウント0で反転
		if (g_Arrow[id].count)
			g_Arrow[id].isReverse = !g_Arrow[id].isReverse;

		int rev = g_Arrow[id].isReverse ? -1 : 1;

		// 角度を計算
		g_Arrow[id].vecX = g_Arrow[id].startVecX
			+ ((g_Arrow[id].endVecX - g_Arrow[id].startVecX) * (g_Arrow[id].count / g_Arrow[id].rotateCount * rev));
		g_Arrow[id].vecY = g_Arrow[id].startVecY
			+ ((g_Arrow[id].endVecY - g_Arrow[id].startVecY) * (g_Arrow[id].count / g_Arrow[id].rotateCount * rev));
	}
}




//線の描画
void Draw_Arrow(int id, int pointNum)
{
	if (g_Arrow[id].isUse)
	{
		int x = g_Arrow[id].originPosX;
		int y = g_Arrow[id].originPosY;
		
		float dist = 3.0f;

		//線を描画していく
		for (int i = 0; i < pointNum; i++)
		{
			//点の描画


			//次の点へ座標を伸ばす
			x += g_Arrow[id].vecX * dist;
			y += g_Arrow[id].vecY * dist;
		}
	}
}



void DrawArrow(int x, int y)
{
	gotoxy(x, y);
	textcolor(BLACK);
	printf("**********");
}


Arrow* Get_Arrow(int id)
{
	return &g_Arrow[id];
}