//---------------------------------------------------------
// file:	game.c
// author:	Brandon Ho Jun Jie
// email:	brandonjunjie.ho@digipen.edu
//
// brief:	Contains functions for game of life. Simulates
// game of life automaton game. Press any key to pause
// and click any cell in pause state to change its state.
// Extra features include changing game speed to slow,
// normal and fast, and reset or clear grid buttons.
// Debugging and game values on the right side for user to
// view.
//
// documentation link:
// https://github.com/DigiPen-Faculty/CProcessing/wiki
//
// Copyright © 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"

#define GOL_GRID_COLS 30
#define GOL_GRID_ROWS 30
#define GOL_GRID_BUFFERS 2

#define GOL_ALIVE 1
#define GOL_DEAD 0

#define TRUE 1
#define FALSE 0

int gIsPaused;
int gGrids[GOL_GRID_BUFFERS][GOL_GRID_ROWS][GOL_GRID_COLS];

/* Feel free to declare your own variables here */

//Game variables
float cellsize;
float gridsize;
CP_Vector grid_pos;
CP_Vector grid;
int nbalive;
int ref_grid;
int display_grid;

//Debug variables
int nbref, nbdisplay;

void game_init(void)
{
    /* Set every grids' cells as 'dead' */
    for (int row = 0; row < GOL_GRID_ROWS; ++row) {
        for (int col = 0; col < GOL_GRID_COLS; ++col) {
            for (int i = 0; i < GOL_GRID_BUFFERS; ++i) {
                gGrids[i][row][col] = GOL_DEAD;
            }
        }
    }

    /*********************************************************
    *  Let's start with gGrids[0] as the 'reference grid'
    *  and gGrids[1] as the 'displaying grid'.
    *
    *  We initialize gGrids[0] with a simple 'glider'.
    *********************************************************/

    gGrids[0][1][2] = GOL_ALIVE;
    gGrids[0][2][3] = GOL_ALIVE;
    gGrids[0][3][1] = GOL_ALIVE;
    gGrids[0][3][2] = GOL_ALIVE;
    gGrids[0][3][3] = GOL_ALIVE;

    /* We start unpaused */
    gIsPaused = FALSE;

    /* Initialization of your other variables here */
    CP_System_SetWindowSize(1500, 1000);
    CP_System_SetFrameRate(30.0f);
    cellsize = 30.f;
    gridsize = 900.f;
    grid_pos.x = 50.f;
    grid_pos.y = 50.f;
    nbalive = 0;
    ref_grid = 0;
    display_grid = 1;
}

void game_update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
    
    if (gIsPaused == 1);
    else
    {
        // checking reference grid status and update display grid
        for (int yrow = 0; yrow < GOL_GRID_ROWS; ++yrow) // loop through grid y
        {
            for (int xcol = 0; xcol < GOL_GRID_COLS; ++xcol) // loop through grid x
            {
                nbalive = 0;
                // checking current grid neighbour status
                for (int ycheck = yrow - 1, i = 0; i < 3; ++ycheck, ++i) // loop through current grid neighbour y
                {
                    for (int xcheck = xcol - 1, j = 0; j < 3; ++xcheck, ++j) // loop through current grid neighbour x
                    {   
                        if (ycheck < 0 || ycheck >= GOL_GRID_ROWS || xcheck < 0 || xcheck >= GOL_GRID_COLS); // skip check if out of grid range
                        else
                        {
                            if (ycheck == yrow && xcheck == xcol); // check if current cell is itself
                            else if (gGrids[ref_grid][ycheck][xcheck] == GOL_ALIVE) // check if current cell is alive
                            {
                                ++nbalive;
                            }
                        }
                    }
                }

                // logic check
                if (gGrids[ref_grid][yrow][xcol] == GOL_ALIVE)
                {
                    if (nbalive == 2 || nbalive ==  3)
                    {
                        gGrids[display_grid][yrow][xcol] = GOL_ALIVE;
                    }
                    else
                    {
                        gGrids[display_grid][yrow][xcol] = GOL_DEAD;
                    }
                }
                else
                {
                    if (nbalive == 3)
                    {
                        gGrids[display_grid][yrow][xcol] = GOL_ALIVE;
                    }
                    else
                    {
                        gGrids[display_grid][yrow][xcol] = GOL_DEAD;
                    }
                }

            }
        }
    }
    // Grid window size x = 50 ~ 950, y = 50 - 950
    CP_Settings_Fill(CP_Color_Create(150, 150, 150, 255));
    CP_Settings_StrokeWeight(5.0f);
    CP_Graphics_DrawRect(grid_pos.x, grid_pos.y, gridsize, gridsize);

    // Drawing individual grid
    for (int yrow = 0; yrow < GOL_GRID_ROWS; ++yrow)
    {
        for (int xcol = 0; xcol < GOL_GRID_COLS; ++xcol)
        {
            if (gGrids[display_grid][yrow][xcol] == GOL_ALIVE)
            {                
                CP_Settings_Fill(CP_Color_Create(70, 150, 70, 255));
            }
            else
            {
                CP_Settings_StrokeWeight(1.0f);
                CP_Settings_Fill(CP_Color_Create(150, 150, 150, 255));
            }
            CP_Settings_StrokeWeight(1.0f);
            CP_Graphics_DrawRect(grid_pos.x + cellsize * xcol, grid_pos.y + cellsize * yrow, cellsize, cellsize);
        }
    }

    grid.x = (CP_Input_GetMouseX() - grid_pos.x) / cellsize; // mouse pos x in grid
    grid.y = (CP_Input_GetMouseY() - grid_pos.y) / cellsize; // mouse pos y in grid

    if (gIsPaused) 
    {
        if (CP_Input_MouseClicked()) // Click to change cell state
        {
            if (grid.x < GOL_GRID_COLS && grid.x >= 0 && grid.y < GOL_GRID_ROWS && grid.y >= 0)
            {
                gGrids[display_grid][(int)grid.y][(int)grid.x] = !gGrids[display_grid][(int)grid.y][(int)grid.x];
            }
        }
    }
         

    // Debug logic check
    nbref = 0;
    nbdisplay = 0;    
    for (int ycheck = (int)grid.y - 1, i = 0; i < 3; ++ycheck, ++i) // loop through current grid neighbour y
    {
        for (int xcheck = (int)grid.x - 1, j = 0; j < 3; ++xcheck, ++j) // loop through current grid neighbour x
        {
            if (ycheck == (int)grid.y && xcheck == (int)grid.x); // check if current cell is itself
            else if (gGrids[ref_grid][ycheck][xcheck] == GOL_ALIVE) // check if current cell is alive
            {
                ++nbref;
                
            }
            if (ycheck == (int)grid.y && xcheck == (int)grid.x);
            else if (gGrids[display_grid][ycheck][xcheck] == GOL_ALIVE) // check if current cell is alive
            {
                ++nbdisplay;
            }
        }
    }

    // Debug text (within X = 1000 ~ 1450, Y = 50 ~ 950)
    CP_Settings_Fill(CP_Color_Create(164, 219, 232, 255));
    CP_Settings_StrokeWeight(3.0f);
    CP_Graphics_DrawRect(1000, 50, 450, 900);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(25.0f);
    char buffer[50] = { 0 };
    sprintf_s(buffer, _countof(buffer), "Mouse X: %.2f Mouse Y: %.2f", CP_Input_GetMouseX(), CP_Input_GetMouseY());
    CP_Font_DrawText(buffer, 1025, 75);
    sprintf_s(buffer, _countof(buffer), "Grid X: %d Grid Y: %d", (int)grid.x, (int)grid.y);
    CP_Font_DrawText(buffer, 1025, 100);
    sprintf_s(buffer, _countof(buffer), "Alive display cell: %d Alive ref cell: %d", gGrids[display_grid][(int)grid.y][(int)grid.x], gGrids[ref_grid][(int)grid.y][(int)grid.x]);
    CP_Font_DrawText(buffer, 1025, 125);
    sprintf_s(buffer, _countof(buffer), "Display neighbours: %d Ref neighbours: %d", nbdisplay, nbref);
    CP_Font_DrawText(buffer, 1025, 150);
    sprintf_s(buffer, _countof(buffer), "Game paused : %d", gIsPaused);
    CP_Font_DrawText(buffer, 1025, 175);

    // Extra buttons feature
    CP_Settings_Fill(CP_Color_Create(200, 70, 220, 255));
    CP_Graphics_DrawRect(1050, 800, 100, 50); // Reset
    CP_Settings_Fill(CP_Color_Create(20, 220, 170, 255)); 
    CP_Graphics_DrawRect(1050, 875, 100, 50); // Clear
    CP_Settings_Fill(CP_Color_Create(100, 100, 220, 255));
    CP_Graphics_DrawRect(1050, 575, 100, 50); // Slow
    CP_Settings_Fill(CP_Color_Create(220, 100, 100, 255));
    CP_Graphics_DrawRect(1050, 650, 100, 50); // Normal
    CP_Settings_Fill(CP_Color_Create(100, 220, 100, 255));
    CP_Graphics_DrawRect(1050, 725, 100, 50); // Fast

    // Extra buttons text
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Reset", 1075, 825);
    CP_Font_DrawText("Clear", 1075, 900);
    CP_Font_DrawText("Slow", 1075, 600);
    CP_Font_DrawText("Normal", 1065, 675);
    CP_Font_DrawText("Fast", 1075, 750);

    //Extra buttons collision box
    if (CP_Input_MouseClicked())
    {
        if (CP_Input_GetMouseX() > 1050 && CP_Input_GetMouseX() < 1150 && CP_Input_GetMouseY() > 800 && CP_Input_GetMouseY() < 850)
        {
            for (int row = 0; row < GOL_GRID_ROWS; ++row) {
                for (int col = 0; col < GOL_GRID_COLS; ++col) {
                    for (int i = 0; i < GOL_GRID_BUFFERS; ++i) {
                        gGrids[i][row][col] = GOL_DEAD;
                    }
                }
            }
            gGrids[display_grid][1][2] = GOL_ALIVE;
            gGrids[display_grid][2][3] = GOL_ALIVE;
            gGrids[display_grid][3][1] = GOL_ALIVE;
            gGrids[display_grid][3][2] = GOL_ALIVE;
            gGrids[display_grid][3][3] = GOL_ALIVE;
        }
        else if (CP_Input_GetMouseX() > 1050 && CP_Input_GetMouseX() < 1150 && CP_Input_GetMouseY() > 875 && CP_Input_GetMouseY() < 925)
        {
            for (int row = 0; row < GOL_GRID_ROWS; ++row) {
                for (int col = 0; col < GOL_GRID_COLS; ++col) {
                    for (int i = 0; i < GOL_GRID_BUFFERS; ++i) {
                        gGrids[i][row][col] = GOL_DEAD;
                    }
                }
            }
        }
        else if (CP_Input_GetMouseX() > 1050 && CP_Input_GetMouseX() < 1150 && CP_Input_GetMouseY() > 575 && CP_Input_GetMouseY() < 625)
        {
            CP_System_SetFrameRate(15.0f);
        }
        else if (CP_Input_GetMouseX() > 1050 && CP_Input_GetMouseX() < 1150 && CP_Input_GetMouseY() > 650 && CP_Input_GetMouseY() < 700)
        {
            CP_System_SetFrameRate(30.0f);
        }
        else if (CP_Input_GetMouseX() > 1050 && CP_Input_GetMouseX() < 1150 && CP_Input_GetMouseY() > 725 && CP_Input_GetMouseY() < 775)
        {
            CP_System_SetFrameRate(45.0f);
        }
    }
    
    // pause game
    if (CP_Input_KeyTriggered(KEY_ANY))
    {
        gIsPaused = !gIsPaused;
    }   
    if (gIsPaused);
    else // swapping reference and display grid
    {
        ref_grid = !ref_grid;
        display_grid = !display_grid;
    }
    
}

void game_exit(void)
{

}
