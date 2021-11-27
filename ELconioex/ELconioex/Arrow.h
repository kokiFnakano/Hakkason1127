#pragma once
#define CONIOEX
#include"conioex.h"



typedef struct Arrow
{
	//���W�֘A
	int originPosX,originPosY;		// ��]�̌��_

	//�����֘A
	float startVecX, startVecY;		// �n�_�����x�N�g��
	float endVecX, endVecY;			// �I�_�����x�N�g��
	float vecX, vecY;				// ���݂̃x�N�g��

	//��]�֘A
	int rotateCount;				// �Г��ɂ�����J�E���g
	int count;						// ���݂̃J�E���g
	bool isReverse = false;			// ���H���̃t���O

	//���̑�
	bool isUse = false;				// �g�p�����̃t���O
};




void Init_Arrow(int id, int posX, int posY, float startX, float startY, float endX, float endY, int count);
void SetArrowUse(int id, bool use);
void Update_Arrow(int id);
void Draw_Arrow(int id, int pointNum);
void DrawArrow(int x, int y);
Arrow* Get_Arrow(int id);