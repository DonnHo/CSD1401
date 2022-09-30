#include "cprocessing.h"
#include "carlevel.h"
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

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

	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	
	//color
	CP_Color black = CP_Color_Create(0,0,0,255);
	CP_Color lblue = CP_Color_CreateHex(0x80dfff);
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
	if (CP_Input_MouseClicked() && IsAreaClicked(windowX, windowY - 100, buttonW, buttonH, mousex, mousey))
	{
		CP_Engine_SetNextGameState(Car_Level_Init, Car_Level_Update, Car_Level_Exit);
	}

	//Exit button collision
	if (CP_Input_MouseClicked() && IsAreaClicked(windowX, windowY + 100, buttonW, buttonH, mousex, mousey))
	{
		CP_Engine_Terminate();
	}
}

void Main_Menu_Exit()
{

}