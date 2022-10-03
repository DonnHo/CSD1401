#pragma once
//---------------------------------------------------------
// file:	utils.h
// author:	Brandon Ho Jun Jie
// email:	brandonjunjie.ho@digipen.edu
//
// brief:	Contains function declarations for utils. Has function IsAreaclicked
//			and IsCircleClicked to check for mouse click in an area.
//			Function AngleToVector converts the angle of the car
//			relative to x-axis to a vector.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
union CP_Vector AngleToVector(float radian_angle);