#include "cprocessing.h"
#include <stdio.h>
#include <stdlib.h>
CP_Image logo;
int alphav = 0;
int increase = 1;

void splash_screen_init(void)
{
	logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
	
	CP_System_SetWindowSize(CP_Image_GetWidth(logo), CP_Image_GetHeight(logo));
}

void splash_screen_update(void)
{
	float elapsedtime = CP_System_GetDt();

	if (increase == 1)
	{
		alphav += 255 * elapsedtime/4;
	}
	if (increase == 0)
	{
		alphav -= 255 * elapsedtime/4;
	}
	//alphav = alphav % 256; not necessary if doing fade out, causes alpha value to jump to 0 sometimes
	if (alphav >= 255)
	{
		increase = 0;
	}
	if (alphav <= 0)
	{
		increase = 1;
	}

	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	CP_Image_Draw(logo, 0.f, 0.f, CP_Image_GetWidth(logo), CP_Image_GetHeight(logo), alphav);
	CP_Graphics_DrawCircle(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 20.0f);

	CP_Settings_Fill(CP_Color_Create(0, 200, 200, 255));

	if (CP_Input_KeyDown(KEY_Q))
	{
		CP_Engine_Terminate();
	}
}

void splash_screen_exit(void)
{
	CP_Image_Free(&logo);
}
