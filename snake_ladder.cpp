#include "raylib.h"
#include <cstdlib>
#include <ctime>

int playerPos[2] = { 0, 0 };
int currentPlayer = 0;
bool rolling = false;
int diceValue = 0;
float diceTimer = 0;
bool gameOver = false;

int snakes[100] = { 0 };
int ladders[100] = { 0 };

Vector2 GetCellPosition(int pos) {
    int row = pos / 10;
    int col = (row % 2 == 0) ? pos % 10 : 9 - (pos % 10);
    return Vector2{ (float)(col * 60 + 30), (float)(540 - row * 60 + 30) };
}

void InitBoard() {
    // Ladders
    ladders[3] = 22;
    ladders[5] = 8;
    ladders[11] = 26;
    ladders[20] = 29;
    ladders[27] = 56;
    ladders[36] = 44;
    ladders[51] = 67;
    ladders[71] = 92;

    // Snakes
    snakes[17] = 4;
    snakes[19] = 7;
    snakes[21] = 9;
    snakes[43] = 34;
    snakes[62] = 18;
    snakes[87] = 24;
    snakes[95] = 75;
    snakes[98] = 78;
}

int main() {
    InitWindow(600, 600, "Snake and Ladder");
    SetTargetFPS(60);
    srand(time(NULL));
    InitBoard();

    while (!WindowShouldClose()) {
        if (!gameOver && IsKeyPressed(KEY_SPACE) && !rolling) {
            rolling = true;
            diceTimer = 0;
        }

        if (rolling) {
            diceTimer += GetFrameTime();
            if (diceTimer >= 1.0f) {
                diceValue = rand() % 6 + 1;
                int newPos = playerPos[currentPlayer] + diceValue;
                if (newPos <= 99) playerPos[currentPlayer] = newPos;

                // Check for ladder
                if (ladders[playerPos[currentPlayer]] != 0)
                    playerPos[currentPlayer] = ladders[playerPos[currentPlayer]];

                // Check for snake
                if (snakes[playerPos[currentPlayer]] != 0)
                    playerPos[currentPlayer] = snakes[playerPos[currentPlayer]];

                if (playerPos[currentPlayer] == 99) {
                    gameOver = true;
                } else {
                    currentPlayer = 1 - currentPlayer;
                }

                rolling = false;
            }
        }

        if (gameOver && IsKeyPressed(KEY_R)) {
            playerPos[0] = playerPos[1] = 0;
            currentPlayer = 0;
            gameOver = false;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw board grid
        for (int i = 0; i < 100; i++) {
            Vector2 pos = GetCellPosition(i);
            DrawRectangleLines(pos.x - 30, pos.y - 30, 60, 60, LIGHTGRAY);
            DrawText(TextFormat("%d", i + 1), pos.x - 10, pos.y - 10, 10, DARKGRAY);
        }

        // Draw snakes and ladders
        for (int i = 0; i < 100; i++) {
            if (ladders[i] != 0) {
                Vector2 from = GetCellPosition(i);
                Vector2 to = GetCellPosition(ladders[i]);
                DrawLine(from.x, from.y, to.x, to.y, GREEN);
            }
            if (snakes[i] != 0) {
                Vector2 from = GetCellPosition(i);
                Vector2 to = GetCellPosition(snakes[i]);
                DrawLine(from.x, from.y, to.x, to.y, RED);
            }
        }

        // Draw players
        for (int i = 0; i < 2; i++) {
            Vector2 pos = GetCellPosition(playerPos[i]);
            DrawCircle(pos.x + (i == 0 ? -10 : 10), pos.y, 10, (i == 0 ? BLUE : ORANGE));
        }

        // Draw dice
        if (rolling) {
            DrawText("Rolling...", 250, 550, 20, DARKGRAY);
        } else {
            DrawText(TextFormat("Player %d's turn - Press SPACE", currentPlayer + 1), 180, 550, 20, DARKGRAY);
            if (diceValue > 0) {
                DrawText(TextFormat("Rolled: %d", diceValue), 250, 520, 20, DARKGRAY);
            }
        }

        if (gameOver) {
            DrawText(TextFormat("Player %d wins!", currentPlayer + 1), 220, 280, 30, MAROON);
            DrawText("Press R to restart", 220, 320, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}