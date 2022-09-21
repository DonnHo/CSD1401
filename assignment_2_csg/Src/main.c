//---------------------------------------------------------
// file:	main.c
// author:	Brandon Ho Jun Jie
// email:	brandonjunjie.ho@digipen.edu
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
//#include "splashscreen.h"
#include "mainmenu.h"

int main(void)
{
	//CP_Engine_SetNextGameState(splash_screen_init, splash_screen_update, splash_screen_exit);
	CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	CP_Engine_Run();
	return 0;
}
