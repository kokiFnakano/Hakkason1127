#include "Arrow.h"
#include <time.h>


static Arrow g_Arrow[4];
static float g_UsedTime[4];


// 矢印の回転開始～終了角度と往復にかかる時間をセット
void SetArrowAngle(int id, float start, float end, float time)
{
	g_Arrow[id].startAngle = start;
	g_Arrow[id].endAngle   = end;
	g_Arrow[id].rotateTime = time;
}


// 矢印の使用状態をセットする
void SetArrowUse(int id, bool use)
{ 
	g_Arrow[id].isUse; 
}




// 矢印の更新
void UpdateArrow(int id)
{
	if (g_Arrow[id].isUse)
	{

	}
}