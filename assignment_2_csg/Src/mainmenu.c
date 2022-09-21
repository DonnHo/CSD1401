#include "cprocessing.h"


void Main_Menu_Init()
{
	CP_System_SetWindowSize(1200, 900);
}

void Main_Menu_Update()
{
	int buttonW = 200, buttonH = 100;
	double windowX = CP_System_GetWindowWidth() / 2;
	double windowY = CP_System_GetWindowHeight() / 2;

	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	
	CP_Color black = CP_Color_Create(0,0,0,255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Color lblue = CP_Color_CreateHex(0x80dfff);
	CP_Color green = CP_Color_CreateHex(0x00F55D);
	CP_Color yellow = CP_Color_CreateHex(0x80a0ff);
	CP_Color red = CP_Color_Create(200, 0 , 0, 255);

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);

	//Centre of window
	CP_Settings_Stroke(CP_Color_Create(70, 93, 130, 255)); 
	CP_Settings_StrokeWeight(1.0f);
	CP_Graphics_DrawLine(0, windowY, (float)CP_System_GetDisplayWidth(), windowY);
	CP_Graphics_DrawLine(windowX, 0, windowX, (float)CP_System_GetDisplayHeight()); 
	//Centre of window

	CP_Settings_Fill(lblue); 
	CP_Graphics_DrawRect(windowX - 100, windowY - 150, buttonW, buttonH); //button start
	CP_Settings_Fill(black); 
	CP_Settings_TextSize(70); //text size
	CP_Font_DrawText("Start", windowX, windowY - 150); //button start text
	CP_Settings_Fill(red);
	CP_Graphics_DrawRect(windowX - 100, windowY + 50, buttonW, buttonH); //button exit
	CP_Settings_Fill(black);
	CP_Font_DrawText("Exit", windowX , windowY + 50 ); //button exit text


	

}

void Main_Menu_Exit()
{

}