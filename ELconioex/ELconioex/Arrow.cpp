#include "Arrow.h"
#include <time.h>


static Arrow g_Arrow[4];
static float g_UsedTime[4];


// ���̉�]�J�n�`�I���p�x�Ɖ����ɂ����鎞�Ԃ��Z�b�g
void SetArrowAngle(int id, float start, float end, float time)
{
	g_Arrow[id].startAngle = start;
	g_Arrow[id].endAngle   = end;
	g_Arrow[id].rotateTime = time;
}


// ���̎g�p��Ԃ��Z�b�g����
void SetArrowUse(int id, bool use)
{ 
	g_Arrow[id].isUse; 
}




// ���̍X�V
void UpdateArrow(int id)
{
	if (g_Arrow[id].isUse)
	{

	}
}