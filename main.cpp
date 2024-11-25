#include "deps/include/raylib.h"

const int COLS = 30;
const int ROWS = 30;

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;

const int CELL_WIDTH = SCREEN_WIDTH / COLS;
const int CELL_HEIGHT = SCREEN_HEIGHT / ROWS;

enum GameState
{
    PLAYING,
    STOPPED
};

GameState gameState = STOPPED;

struct Cell
{
    int i;
    int j;
    bool status;
    int nearbyAliveCells;
};

Cell grid[COLS][ROWS];

void gridInit();
void CellDraw(Cell cell);
bool IndexIsValid(int, int);
void countNearbyAliveCells();
void gameCycle();

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game Of Life");
    SetTargetFPS(6);
    gridInit();

    while (!WindowShouldClose())
    {
        if (IsKeyReleased(KEY_SPACE))
        {
            gameState == STOPPED ? gameState = PLAYING : gameState = STOPPED;
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mPos = GetMousePosition();
            int indexI = mPos.x / CELL_WIDTH;
            int indexJ = mPos.y / CELL_HEIGHT;
            grid[indexI][indexJ].status = !grid[indexI][indexJ].status;
        }

        if (gameState == PLAYING)
        {
            countNearbyAliveCells();
            gameCycle();
        }

        BeginDrawing();
        {
            ClearBackground(BLACK);
            for (int i = 0; i < COLS; i++)
            {
                for (int j = 0; j < ROWS; j++)
                {
                    CellDraw(grid[i][j]);
                }
            }
        }
        EndDrawing();
    }

    return 0;
}

void gridInit()
{
    for (int i = 0; i < COLS; i++)
    {
        for (int j = 0; j < ROWS; j++)
        {
            grid[i][j] = (Cell){
                .i = i,
                .j = j,
                .status = false,
                .nearbyAliveCells = 0};
        }
    }
}

void countNearbyAliveCells()
{
    for (int curI = 0; curI < ROWS; curI++)
    {
        for (int curJ = 0; curJ < COLS; curJ++)
        {
            grid[curI][curJ].nearbyAliveCells = 0;

            for (int i = -1; i <= 1; i++)
            {
                for (int j = -1; j <= 1; j++)
                {
                    if (i == 0 && j == 0)
                    {
                        continue;
                    }

                    int neighborI = curI + i;
                    int neighborJ = curJ + j;
                    if (IndexIsValid(neighborI, neighborJ))
                    {
                        if (grid[neighborI][neighborJ].status)
                        {
                            grid[curI][curJ].nearbyAliveCells++;
                        }
                    }
                }
            }
        }
    }
}

void gameCycle()
{
    bool newStatus[ROWS][COLS];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (grid[i][j].status && grid[i][j].nearbyAliveCells < 2)
            {
                newStatus[i][j] = false;
            }
            else if (grid[i][j].status && grid[i][j].nearbyAliveCells > 3)
            {
                newStatus[i][j] = false;
            }
            else if (!grid[i][j].status && grid[i][j].nearbyAliveCells == 3)
            {
                newStatus[i][j] = true;
            }
            else
            {
                newStatus[i][j] = grid[i][j].status;
            }
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            grid[i][j].status = newStatus[i][j];
        }
    }
}

void CellDraw(Cell cell)
{
    if (cell.status)
    {
        DrawRectangle(cell.i * CELL_WIDTH, cell.j * CELL_HEIGHT, CELL_WIDTH - 1, CELL_HEIGHT - 1, GREEN);
    }
    else
    {
        DrawRectangle(cell.i * CELL_WIDTH, cell.j * CELL_HEIGHT, CELL_WIDTH - 1, CELL_HEIGHT - 1, DARKGRAY);
    }
}

bool IndexIsValid(int i, int j)
{
    return i >= 0 && i < COLS && j >= 0 && j < ROWS;
}