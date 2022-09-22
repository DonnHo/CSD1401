#include "cprocessing.h"
#include "carlevel.h"
#include <stdio.h>
#include <stdlib.h>

void Main_Menu_Init()
{
	CP_System_SetWindowSize(1000, 1000);
}

void Main_Menu_Update()
{
	int buttonW = 200, buttonH = 100;
	int mousex = CP_Input_GetMouseX(), mousey = CP_Input_GetMouseY();

	double windowX = CP_System_GetWindowWidth() / 2;
	double windowY = CP_System_GetWindowHeight() / 2;

	typedef struct buttoncollision
	{
		int x1;
		int x2;
		int y1;
		int y2;
	}button;

	button startbutton, exitbutton;

	startbutton.x1 = windowX - buttonW/2;
	startbutton.y1 = windowY - 50;
	startbutton.x2 = windowX + buttonW/2;
	startbutton.y2 = windowY - 50 - buttonH;

	exitbutton.x1 = windowX - buttonW / 2;
	exitbutton.y1 = windowY + 50 + buttonH;
	exitbutton.x2 = windowX + buttonW / 2;
	exitbutton.y2 = windowY + 50;

	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	
	//color
	CP_Color black = CP_Color_Create(0,0,0,255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Color lblue = CP_Color_CreateHex(0x80dfff);
	CP_Color green = CP_Color_CreateHex(0x00F55D);
	CP_Color dred = CP_Color_Create(139, 0, 0, 255);
	CP_Color red = CP_Color_Create(200, 0 , 0, 255);

	//Text Alignment
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
	//Draw rectangle mode
	CP_Settings_RectMode(CP_POSITION_CENTER);

	//start button
	CP_Settings_Fill(lblue); 
	CP_Graphics_DrawRect(windowX, windowY - 100, buttonW, buttonH); 
	CP_Settings_Fill(black);
	CP_Settings_TextSize(70);
	CP_Font_DrawText("Start", windowX, windowY - 150);

	//button exit
	CP_Settings_Fill(red);
	CP_Graphics_DrawRect(windowX, windowY + 100, buttonW, buttonH);
	CP_Settings_Fill(black);
	CP_Font_DrawText("Exit", windowX , windowY + 50 );


	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
	
	//Start button collision
	if (mousex > startbutton.x1 && mousex < startbutton.x2)
	{
		if (mousey < startbutton.y1 && mousey > startbutton.y2)
		{
			CP_Settings_Fill(green);
			CP_Graphics_DrawRect(windowX, windowY - 100, buttonW, buttonH);
			if (CP_Input_MouseClicked())
			{

				CP_Engine_SetNextGameState(Car_Level_Init, Car_Level_Update, Car_Level_Exit);
			}
		}
	}

	//Exit button collision
	if (mousex > exitbutton.x1 && mousex < exitbutton.x2)
	{
		if (mousey < exitbutton.y1 && mousey > exitbutton.y2)
		{
			CP_Settings_Fill(dred);
			CP_Graphics_DrawRect(windowX, windowY + 100, buttonW, buttonH);
			if (CP_Input_MouseClicked())
			{

				CP_Engine_Terminate();
			}
		}
	}

	//Centre of window
	CP_Settings_Stroke(CP_Color_Create(70, 93, 130, 255));
	CP_Settings_StrokeWeight(1.0f);
	CP_Graphics_DrawLine(0, windowY, (float)CP_System_GetDisplayWidth(), windowY);
	CP_Graphics_DrawLine(windowX, 0, windowX, (float)CP_System_GetDisplayHeight());

	//mouse x,y
	CP_Settings_TextSize(20.0f);
	char buffer1[50] = { 0 };
	sprintf_s(buffer1, _countof(buffer1), "Mouse x: %i", mousex);
	CP_Font_DrawText(buffer1, 100, 100);
	char buffer2[50] = { 0 };
	sprintf_s(buffer2, _countof(buffer2), "Mouse y: %i", mousey);
	CP_Font_DrawText(buffer2, 100, 120);
}

void Main_Menu_Exit()
{

}