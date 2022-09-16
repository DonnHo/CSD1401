#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
CP_Image logo;
int alpha = 0;
void splash_screen_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	
	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
}

void splash_screen_update(void)
{
	alpha += 3;
	alpha %= 256;
	//char buffer[50] = { 0 };
	//sprintf_s(buffer, _countof(buffer), "Alpha value: %i", alpha);
	//CP_Font_DrawText(buffer, 30, 30);

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), alpha);
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f);
	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
}

void splash_screen_exit(void)
{
	CP_Image_Free(&logo);
}
