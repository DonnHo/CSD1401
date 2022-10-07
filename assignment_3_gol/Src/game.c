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

float cellsize;
float gridsize;
CP_Vector grid_pos;
CP_Vector grid;
int nbalive;
int ref_grid;
int display_grid;

int nbref, nbdisplay;
int test;

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
    cellsize = 30.f;
    gridsize = 900.f;
    grid_pos.x = 50.f;
    grid_pos.y = 50.f;
    nbalive = 0;
    ref_grid = 0;
    display_grid = 1;

    test = 0;
}

void game_update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
    
    //gIsPaused = TRUE;
    if (CP_Input_KeyTriggered(KEY_ANY)) {
        gIsPaused = !gIsPaused;
    }
    if (gIsPaused == 1);
    else
    {
        // checking reference grid status
        for (int yrow = 0; yrow < GOL_GRID_ROWS; ++yrow) // loop through grid y
        {
            for (int xcol = 0; xcol < GOL_GRID_COLS; ++xcol) // loop through grid x
            {
                nbalive = 0;
                // checking current grid neighbour status
                for (int ycheck = yrow , i = 0; i < 3; ++ycheck, ++i) // loop through current grid neighbour y
                {
                    for (int xcheck = xcol , j = 0; j < 3; ++xcheck, ++j) // loop through current grid neighbour x
                    {
                        if (ycheck == yrow && xcheck == xcol); // check if current cell is itself
                                            
                        else if (gGrids[ref_grid][ycheck][xcheck] == GOL_ALIVE) // check if current cell is alive
                        {
                            ++nbalive;
                        }
                    }
                }

                // logic check
                if (gGrids[ref_grid][yrow][xcol] == GOL_ALIVE)
                {
                    if (nbalive < 2 || nbalive >  3)
                    {
                        gGrids[display_grid][yrow][xcol] = GOL_DEAD;
                    }
                    else
                    {
                        gGrids[display_grid][yrow][xcol] = GOL_ALIVE;
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
            if (gGrids[ref_grid][yrow][xcol] == GOL_ALIVE)
            {
                CP_Settings_StrokeWeight(1.0f);
                CP_Settings_Fill(CP_Color_Create(70, 150, 70, 255));
                CP_Graphics_DrawRect(grid_pos.x + cellsize * xcol, grid_pos.y + cellsize * yrow, cellsize, cellsize);
            }
            else
            {
                CP_Settings_StrokeWeight(1.0f);
                CP_Settings_Fill(CP_Color_Create(150, 150, 150, 255));
                CP_Graphics_DrawRect(grid_pos.x + cellsize * xcol, grid_pos.y + cellsize * yrow, cellsize, cellsize);
            }
        }
    }

    grid.x = (CP_Input_GetMouseX() - grid_pos.x) / cellsize;
    grid.y = (CP_Input_GetMouseY() - grid_pos.y) / cellsize; 
    
    nbref = 0;
    nbdisplay = 0;
    // debug logic check
    for (int ycheck = (int)grid.y - 1, i = 0; i < 3; ++ycheck, ++i) // loop through current grid neighbour y
    {
        for (int xcheck = (int)grid.x - 1, j = 0; j < 3; ++xcheck, ++j) // loop through current grid neighbour x
        {
            /*ycheck += ycheck < 0 ? 1 : 0;
            ycheck -= ycheck > 29 ? 1 : 0;
            xcheck += xcheck < 0 ? 1 : 0;
            xcheck -= xcheck > 29 ? 1 : 0;*/
            if (ycheck == (int)grid.y && xcheck == (int)grid.x) // check if current cell is itself
            {
                continue;
            }
            else if (gGrids[ref_grid][ycheck][xcheck] == GOL_ALIVE) // check if current cell is alive
            {
                ++nbref;
            }
            else if (gGrids[display_grid][ycheck][xcheck] == GOL_ALIVE) // check if current cell is alive
            {
                ++nbdisplay;
            }
            else
            {
                continue;
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

   
   
    if (gIsPaused);
    else
    {
        ref_grid = !ref_grid;
        display_grid = !display_grid;
    }
    /*if (CP_Input_KeyTriggered(KEY_ANY)) {
        gIsPaused = !gIsPaused;
    }*/
    
}

void game_exit(void)
{

}
