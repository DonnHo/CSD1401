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
}

void game_update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(60, 60, 60, 255));
    
    // Grid window size x = 50 ~ 950, y = 50 - 950
    CP_Settings_Fill(CP_Color_Create(150, 150, 150, 255));
    CP_Settings_StrokeWeight(5.0f);
    CP_Graphics_DrawRect(grid_pos.x, grid_pos.y, gridsize, gridsize);

    // Drawing grid

    for (float yrow = grid_pos.y; yrow < gridsize + grid_pos.y; yrow += cellsize)
    {
        for (float xcol = grid_pos.x; xcol < gridsize + grid_pos.x; xcol += cellsize)
        {
            CP_Settings_StrokeWeight(1.0f);
            CP_Graphics_DrawRect(xcol, yrow, cellsize, cellsize);
        }
    }

    // 
    grid.x = (CP_Input_GetMouseX() - grid_pos.x) / cellsize;
    grid.y = (CP_Input_GetMouseY() - grid_pos.y) / cellsize;

    // Debug text (within X = 1000 ~ 1450, Y = 50 ~ 950)
    CP_Settings_Fill(CP_Color_Create(164, 219, 232, 255));
    CP_Settings_StrokeWeight(3.0f);
    CP_Graphics_DrawRect(1000, 50, 450, 900);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(25.0f);
    char buffer[50] = { 0 };
    sprintf_s(buffer, _countof(buffer), "Mouse X: %.2f Mouse Y: %.2f", CP_Input_GetMouseX(), CP_Input_GetMouseY());
    CP_Font_DrawText(buffer, 1025, 75);
    sprintf_s(buffer, _countof(buffer), "Grid X: %.2f Grid Y: %.2f", grid.x, grid.y);
    CP_Font_DrawText(buffer, 1025, 100);

}

void game_exit(void)
{

}
