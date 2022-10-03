//---------------------------------------------------------
// file:	utils.c
// author:	Brandon Ho Jun Jie
// email:	brandonjunjie.ho@digipen.edu
//
// brief:	Contains functions for utils. Has function IsAreaclicked
//			and IsCircleClicked to check for mouse click in an area.
//			Function AngleToVector converts the angle of the car
//			relative to x-axis to a vector.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include <math.h>

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	double x1 = area_center_x - area_width / 2, y1 = area_center_y + area_height / 2;
	double x2 = area_center_x + area_width / 2, y2 = area_center_y - area_height / 2;

	if (click_x > x1 && click_x < x2 && click_y < y1 && click_y > y2)
	{
		return 1;
	}
	else return 0;
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y)
{
	float distance = CP_Math_Distance(circle_center_x, circle_center_y, click_x, click_y);

	if (distance < diameter / 2)
	{
		return 1;
	}
	return 0;
}

CP_Vector AngleToVector(float radian_angle)
{
   CP_Vector vec1;
   vec1 = CP_Vector_Set(cos(radian_angle), sin(radian_angle));
   return vec1;
}