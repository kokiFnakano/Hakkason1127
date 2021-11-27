#pragma once
#define CONIOEX
#include"conioex.h"



typedef struct Arrow
{
	//���W�֘A
	int originPosX,originPosY;		// ��]�̌��_

	//�����֘A
	float startAngle;				// �n�_�����x�N�g��
	float endAngle;					// �I�_�����x�N�g��
	float vecX, vecY;				// ���݂̃x�N�g��

	//��]�֘A
	int rotateCount;				// �Г��ɂ�����J�E���g
	int count = 0;					// ���݂̃J�E���g
	bool isReverse = false;			// ���H���̃t���O

	//���̑�
	bool isUse = true;				// �g�p�����̃t���O
};




void Init_Arrow(int id, int posX, int posY, int startAngle, int endAngle, int count);
void SetArrowUse(int id, bool use);
void Update_Arrow(int id);
void Draw_Arrow(int id, int pointNum);
void DrawArrow(int x, int y);
Arrow* Get_Arrow(int id);