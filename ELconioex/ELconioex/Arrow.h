#pragma once

typedef struct Arrow
{
	float startAngle, endAngle;
	float rotateTime;

	float angle;
	float vecX, vecY;
	bool isUse = false;
};

