#include "cprocessing.h"
#include "mainmenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	int posx;
	int posy;
	int rad;

}car;

static car car_set(int x, int y, int rad)
{
	car ret;
	ret.posx = x;
	ret.posy = y;
	ret.rad = rad;
	return ret;
}
void Car_Level_Init()
{
	CP_System_SetWindowSize(1000, 1000);
}

void Car_Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	int mousex = CP_Input_GetMouseX();
	int mousey = CP_Input_GetMouseY();
	
	// Mouse pos
	CP_Settings_TextSize(20.0f);
	char buffer1[50] = { 0 };
	sprintf_s(buffer1, _countof(buffer1), "Mouse x: %i", mousex);
	CP_Font_DrawText(buffer1,100, 100);
	char buffer2[50] = { 0 };
	sprintf_s(buffer2, _countof(buffer2), "Mouse y: %i", mousey);
	CP_Font_DrawText(buffer2, 100, 120);

	//Car 1
	car car1 = car_set(300, 300, 30);
	CP_Graphics_DrawCircle(car1.posx, car1.posy, car1.rad*2);
	
	//Car 2
	CP_Graphics_DrawTriangle(800, 300, 850, 300, 825, 350);

	//Car 3
	CP_Graphics_DrawTriangle(550, 300, 600, 300, 575, 350);

	if (sqrt((car1.posx - mousex) * (car1.posx - mousex) + (car1.posy - mousey) * (car1.posy - mousey)) < car1.rad)
	{
		CP_Graphics_DrawTriangle(300, 300, 350, 300, 325, 350);
	}
	
	if (CP_Input_KeyDown(KEY_E))
	{
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Car_Level_Exit()
{

}