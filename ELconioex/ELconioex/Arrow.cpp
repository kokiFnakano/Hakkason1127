#include "Arrow.h"
#include <time.h>
#include "conioex.h"


static Arrow g_Arrow[4];





// ���̉�]�J�n�`�I���p�x�Ɖ����ɂ����鎞�Ԃ��Z�b�g
void Init_Arrow(int id, int posX, int posY, float startX, float startY, float endX, float endY, int count)
{
	//���S���W�̃Z�b�g
	g_Arrow[id].originPosX = posX;
	g_Arrow[id].originPosX = posY;

	// ��]�ϐ��̏�����
	g_Arrow[id].startVecX = startX;
	g_Arrow[id].startVecY = startY;
	g_Arrow[id].endVecX = endX;
	g_Arrow[id].endVecY = endY;


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
		g_Arrow[id].count = (g_Arrow[id].count + 1) % g_Arrow[id].count;

		// �J�E���g0�Ŕ��]
		if (g_Arrow[id].count)
			g_Arrow[id].isReverse = !g_Arrow[id].isReverse;

		int rev = g_Arrow[id].isReverse ? -1 : 1;

		// �p�x���v�Z
		g_Arrow[id].vecX = g_Arrow[id].startVecX
			+ ((g_Arrow[id].endVecX - g_Arrow[id].startVecX) * (g_Arrow[id].count / g_Arrow[id].rotateCount * rev));
		g_Arrow[id].vecY = g_Arrow[id].startVecY
			+ ((g_Arrow[id].endVecY - g_Arrow[id].startVecY) * (g_Arrow[id].count / g_Arrow[id].rotateCount * rev));
	}
}




//���̕`��
void Draw_Arrow(int id, int pointNum)
{
	if (g_Arrow[id].isUse)
	{
		int x = g_Arrow[id].originPosX;
		int y = g_Arrow[id].originPosY;
		
		float dist = 3.0f;

		//����`�悵�Ă���
		for (int i = 0; i < pointNum; i++)
		{
			//�_�̕`��


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