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

static car car_set(float x, float y, float dia)
{
	car ret;
	ret.position.x = x;
	ret.position.y = y;
	ret.dia = dia;
	return ret;
}
car car1, car2, car3;
void Car_Level_Init()
{
	CP_System_SetWindowSize(1000, 1000);

	car1 = car_set(300.f, 300.f, 60.f);
	car1.angle = 0.f;
	car1.speed = 0.f;
	car1.rspeed = 0.f;
	car2 = car_set(300.f, 600.f, 60.f);
	car2.angle = 0.f;
	car2.speed = 0.f;
	car2.rspeed = 0.f;
	car3 = car_set(600.f, 300.f, 60.f);
	car3.angle = 0.f;
	car3.speed = 0.f;
	car3.rspeed = 0.f;
}

void Car_Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	float mousex = CP_Input_GetMouseX();
	float mousey = CP_Input_GetMouseY();
	float deltatime = CP_System_GetDt();
	car1.rad = CP_Math_Radians(car1.angle);
	car1.direction = AngleToVector(car1.rad);
	car2.rad = CP_Math_Radians(car2.angle);
	car2.direction = AngleToVector(car2.rad);
	car3.rad = CP_Math_Radians(car3.angle);
	car3.direction = AngleToVector(car3.rad);

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

	if (CP_Input_KeyDown(KEY_E))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
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
	CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
	CP_Graphics_DrawCircle(car1.position.x, car1.position.y, car1.dia);
	
	//Car 2
	CP_Settings_Fill(CP_Color_Create(255, 0, 255, 255));
	CP_Graphics_DrawCircle(car2.position.x, car2.position.y, car2.dia);
	
	//Car 3
	CP_Settings_Fill(CP_Color_Create(0, 255, 255, 255));
	CP_Graphics_DrawCircle(car3.position.x, car3.position.y, car3.dia);

	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Graphics_DrawTriangleAdvanced(car1.position.x + 30.f, car1.position.y, car1.position.x - 15.f, car1.position.y - 25.f, car1.position.x - 15.f, car1.position.y + 25.f, car1.angle);
	CP_Graphics_DrawTriangleAdvanced(car2.position.x + 30.f, car2.position.y, car2.position.x - 15.f, car2.position.y - 25.f, car2.position.x - 15.f, car2.position.y + 25.f, car2.angle);
	CP_Graphics_DrawTriangleAdvanced(car3.position.x + 30.f, car3.position.y, car3.position.x - 15.f, car3.position.y - 25.f, car3.position.x - 15.f, car3.position.y + 25.f, car3.angle);

	// Mouse pos
	CP_Settings_TextSize(20.0f);
	char buffer1[50] = { 0 };
	sprintf_s(buffer1, _countof(buffer1), "Mouse x: %d", carselect);
	CP_Font_DrawText(buffer1, 100, 100);
	char buffer2[50] = { 0 };
	sprintf_s(buffer2, _countof(buffer2), "Mouse y: %.2f", car1.rspeed);
	CP_Font_DrawText(buffer2, 100, 120);

}

void Car_Level_Exit()
{

}