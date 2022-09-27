#include "cprocessing.h"
#include "mainmenu.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utils.h"

typedef struct
{
	float posx;
	float posy;
	float dia;

}car;

static car car_set(float x, float y, float dia)
{
	car ret;
	ret.posx = x;
	ret.posy = y;
	ret.dia = dia;
	return ret;
}
void Car_Level_Init()
{
	CP_System_SetWindowSize(1000, 1000);
}

void Car_Level_Update()
{
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	float mousex = CP_Input_GetMouseX();
	float mousey = CP_Input_GetMouseY();
	
	// Mouse pos
	CP_Settings_TextSize(20.0f);
	char buffer1[50] = { 0 };
	sprintf_s(buffer1, _countof(buffer1), "Mouse x: %.2f", mousex);
	CP_Font_DrawText(buffer1,100, 100);
	char buffer2[50] = { 0 };
	sprintf_s(buffer2, _countof(buffer2), "Mouse y: %.2f", mousey);
	CP_Font_DrawText(buffer2, 100, 120);

	//Car 1
	car car1 = car_set(300.f, 300.f, 60.f);
	CP_Graphics_DrawCircle(car1.posx, car1.posy, car1.dia);
	
	//Car 2
	CP_Graphics_DrawTriangle(800, 300, 850, 300, 825, 350);

	//Car 3
	CP_Graphics_DrawTriangle(550, 300, 600, 300, 575, 350);

	if (CP_Input_MouseClicked() && IsCircleClicked(car1.posx, car1.posy, car1.dia, mousex, mousey))
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