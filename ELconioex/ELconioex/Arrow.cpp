#include "Arrow.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "conioex.h"


static Arrow g_Arrow[4];





// ���̉�]�J�n�`�I���p�x�Ɖ����ɂ����鎞�Ԃ��Z�b�g
void Init_Arrow(int id, int posX, int posY, int startAngle, int endAngle, int count)
{
	//���S���W�̃Z�b�g
	g_Arrow[id].originPosX = posX;
	g_Arrow[id].originPosY = posY;

	// ��]�ϐ��̏�����
	g_Arrow[id].startAngle = startAngle;
	g_Arrow[id].endAngle = endAngle;


	g_Arrow[id].rotateCount = count;
}




// ���̎g�p��Ԃ��Z�b�g����
void SetArrowUse(int id, bool use)
{ 
	g_Arrow[id].isUse; 

	//��]����������
	if (!g_Arrow[id].isUse)
	{
		g_Arrow[id].count = 0;
		g_Arrow[id].isReverse = false;
	}
		
}




// ���̍X�V
void Update_Arrow(int id)
{
	if (g_Arrow[id].isUse)
	{
		


		g_Arrow[id].count = (g_Arrow[id].count + 1) % g_Arrow[id].rotateCount;

		// �J�E���g0�Ŕ��]
		if (!g_Arrow[id].count)
			g_Arrow[id].isReverse = !g_Arrow[id].isReverse;

		int rev = g_Arrow[id].isReverse ? -1 : 1;

		// �p�x���v�Z
		float threshold = (float)g_Arrow[id].count / g_Arrow[id].rotateCount;
		float angle = g_Arrow[id].startAngle - (g_Arrow[id].endAngle - g_Arrow[id].startAngle) * threshold;
		float deg = angle/ 180 *  M_PI;
		g_Arrow[id].vecX = cosf(deg);
		g_Arrow[id].vecY = sinf(deg);
		int i = 0;
	}
}




//���̕`��
void Draw_Arrow(int id, int pointNum)
{
	if (g_Arrow[id].isUse)
	{
		int x = g_Arrow[id].originPosX;
		int y = g_Arrow[id].originPosY;
		
		float dist = 5.0f;


		x += g_Arrow[id].vecX * dist;
		y += g_Arrow[id].vecY * dist;


		//����`�悵�Ă���
		for (int i = 0; i < pointNum; i++)
		{
			//�_�̕`��
			gotoxy(x, y);
			printf("��");

			//���̓_�֍��W��L�΂�
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