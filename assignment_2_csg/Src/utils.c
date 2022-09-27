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
	// TODO
	return 0;
}

CP_Vector AngleToVector(float radian_angle)
{
    // TODO 
   // CP_Vector ret;
    //return ret;
}