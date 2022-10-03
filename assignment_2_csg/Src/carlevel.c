//---------------------------------------------------------
// file:	carlevel.c
// author:	Brandon Ho Jun Jie
// email:	brandonjunjie.ho@digipen.edu
//
// brief:	Contains functions for car level. Loads 3 cars
//			that are selected by click on the car and moving
//			using WASD.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "mainmenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

int carselect = 0;

typedef struct
{
	CP_Vector position;
	CP_Vector direction;
	float angle;
	float dia;
	float rad;
	float speed;
	float rspeed;
	
}car;

static car car_set(float x, float y, float dia, float angle, float speed, float rspeed)
{
	car ret;
	ret.position.x = x;
	ret.position.y = y;
	ret.dia = dia;
	ret.angle = angle;
	ret.speed = speed;
	ret.rspeed = rspeed;
	return ret;
}
car car1, car2, car3;
void Car_Level_Init()
{
	CP_System_SetWindowSize(1000, 1000);

	car1 = car_set(300.f, 300.f, 60.f, 0.f ,0.f, 0.f);
	car2 = car_set(300.f, 600.f, 60.f, 0.f, 0.f, 0.f);
	car3 = car_set(600.f, 300.f, 60.f, 0.f, 0.f, 0.f);
}

void Car_Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	float mousex = CP_Input_GetMouseX();
	float mousey = CP_Input_GetMouseY();
	float deltatime = CP_System_GetDt();

	//converting car angle from x axis to vector of car
	car1.rad = CP_Math_Radians(car1.angle);
	car1.direction = AngleToVector(car1.rad);
	car2.rad = CP_Math_Radians(car2.angle);
	car2.direction = AngleToVector(car2.rad);
	car3.rad = CP_Math_Radians(car3.angle);
	car3.direction = AngleToVector(car3.rad);

	// collision box of car for selection
	if (CP_Input_MouseClicked() && IsCircleClicked(car1.position.x, car1.position.y, car1.dia, mousex, mousey))
	{
		carselect = 1;
	}
	if (CP_Input_MouseClicked() && IsCircleClicked(car2.position.x, car2.position.y, car2.dia, mousex, mousey))
	{
		carselect = 2;
	}
	if (CP_Input_MouseClicked() && IsCircleClicked(car3.position.x, car3.position.y, car3.dia, mousex, mousey))
	{
		carselect = 3;
	}

	// Return to main menu
	if (CP_Input_KeyDown(KEY_P))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	// Moving car forward
	if (CP_Input_KeyDown(KEY_W))
	{
		switch (carselect)
		{
		case 1:
			car1.speed += 3.f * deltatime;
			if (car1.speed >= 20.f)
			{
				car1.speed = 20.f;
			}
			break;
		case 2:
			car2.speed += 3.f * deltatime;
			if (car2.speed >= 20.f)
			{
				car2.speed = 20.f;
			}
			break;
		case 3:
			car3.speed += 3.f * deltatime;
			if (car3.speed >= 20.f)
			{
				car3.speed = 20.f;
			}
			break;
		default:
			break;
		}
	}
	
	// slowing car down after releasing key
	else
	{
		car1.speed -= 6.f * deltatime;
		if (car1.speed <= 0.f)
		{
			car1.speed = 0.f;
		}
		car2.speed -= 6.f * deltatime;
		if (car2.speed <= 0.f)
		{
			car2.speed = 0.f;
		}
		car3.speed -= 6.f * deltatime;
		if (car3.speed <= 0.f)
		{
			car3.speed = 0.f;
		}
	}

	// moving car backwards
	if (CP_Input_KeyDown(KEY_S))
	{
		switch (carselect)
		{
		case 1:
			car1.rspeed += 1.5f * deltatime;
			if (car1.rspeed >= 8.f)
			{
				car1.rspeed = 8.f;
			}
			break;
		case 2:
			car2.rspeed += 1.5f * deltatime;
			if (car2.rspeed >= 8.f)
			{
				car2.rspeed = 8.f;
			}
			break;
		case 3:
			car3.rspeed += 1.5f * deltatime;
			if (car3.rspeed >= 8.f)
			{
				car3.rspeed = 8.f;
			}
			break;
		default:
			break;
		}
	}

	// slowing down car after releasing key
	else
	{
		car1.rspeed -= 3.f * deltatime;
		if (car1.rspeed <= 0.f)
		{
			car1.rspeed = 0.f;
		}
		car2.rspeed -= 3.f * deltatime;
		if (car2.rspeed <= 0.f)
		{
			car2.rspeed = 0.f;
		}
		car3.rspeed -= 3.f * deltatime;
		if (car3.rspeed <= 0.f)
		{
			car3.rspeed = 0.f;
		}
	}

	// rotate car right
	if (CP_Input_KeyDown(KEY_D))
	{
		switch (carselect)
		{
		case 1:
			car1.angle += 5.f;
			break;
		case 2:
			car2.angle += 5.f;
			break;
		case 3:
			car3.angle += 5.f;
			break;
		}
	}

	// rotate car left
	if (CP_Input_KeyDown(KEY_A))
	{
		switch (carselect)
		{
		case 1:
			car1.angle -= 5.f;
			break;
		case 2:
			car2.angle -= 5.f;
			break;
		case 3:
			car3.angle -= 5.f;
			break;
		}
	}

	// moving position of car by multiplying its vector with speed
	car1.position.x += car1.direction.x * car1.speed;
	car1.position.y += car1.direction.y * car1.speed;
	car1.position.x -= car1.direction.x * car1.rspeed;
	car1.position.y -= car1.direction.y * car1.rspeed;
	car2.position.x += car2.direction.x * car2.speed;
	car2.position.y += car2.direction.y * car2.speed;
	car2.position.x -= car2.direction.x * car2.rspeed;
	car2.position.y -= car2.direction.y * car2.rspeed;
	car3.position.x += car3.direction.x * car3.speed;
	car3.position.y += car3.direction.y * car3.speed;
	car3.position.x -= car3.direction.x * car3.rspeed;
	car3.position.y -= car3.direction.y * car3.rspeed;

	// left edge window collision
	if (car1.position.x <= 30)
	{
		car1.position.x = 30;
	}
	if (car2.position.x <= 30)
	{
		car2.position.x = 30;
	}
	if (car3.position.x <= 30)
	{
		car3.position.x = 30;
	}

	// right edge window collision
	if (car1.position.x >= 970)
	{
		car1.position.x = 970;
	}
	if (car2.position.x >= 970)
	{
		car2.position.x = 970;
	}
	if (car3.position.x >= 970)
	{
		car3.position.x = 970;
	}

	// bottom edge window collision
	if (car1.position.y <= 30)
	{
		car1.position.y = 30;
	}
	if (car2.position.y <= 30)
	{
		car2.position.y = 30;
	}
	if (car3.position.y <= 30)
	{
		car3.position.y = 30;
	}

	// bottom edge window collision
	if (car1.position.y >= 970)
	{
		car1.position.y = 970;
	}
	if (car2.position.y >= 970)
	{
		car2.position.y = 970;
	}
	if (car3.position.y >= 970)
	{
		car3.position.y = 970;
	}
	//Car 1
	CP_Settings_Fill(CP_Color_Create(220, 220, 0, 255));
	CP_Graphics_DrawCircle(car1.position.x, car1.position.y, car1.dia);
	
	//Car 2
	CP_Settings_Fill(CP_Color_Create(220, 0, 220, 255));
	CP_Graphics_DrawCircle(car2.position.x, car2.position.y, car2.dia);
	
	//Car 3
	CP_Settings_Fill(CP_Color_Create(0, 220, 220, 255));
	CP_Graphics_DrawCircle(car3.position.x, car3.position.y, car3.dia);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawTriangleAdvanced(car1.position.x + 30.f, car1.position.y, car1.position.x - 15.f, car1.position.y - 25.f, car1.position.x - 15.f, car1.position.y + 25.f, car1.angle);
	CP_Graphics_DrawTriangleAdvanced(car2.position.x + 30.f, car2.position.y, car2.position.x - 15.f, car2.position.y - 25.f, car2.position.x - 15.f, car2.position.y + 25.f, car2.angle);
	CP_Graphics_DrawTriangleAdvanced(car3.position.x + 30.f, car3.position.y, car3.position.x - 15.f, car3.position.y - 25.f, car3.position.x - 15.f, car3.position.y + 25.f, car3.angle);
}

void Car_Level_Exit()
{

}