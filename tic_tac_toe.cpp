#include "raylib.h"

char board[9] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
char currentPlayer = 'X';
bool gameOver = false;
int winnerLine[3] = { -1, -1, -1 };

int CheckWinner() {
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // rows
        {0,3,6}, {1,4,7}, {2,5,8}, // cols
        {0,4,8}, {2,4,6}           // diagonals
    };

    for (int i = 0; i < 8; i++) {
        int a = wins[i][0], b = wins[i][1], c = wins[i][2];
        if (board[a] != ' ' && board[a] == board[b] && board[b] == board[c]) {
            winnerLine[0] = a;
            winnerLine[1] = b;
            winnerLine[2] = c;
            return board[a];
        }
    }

    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') return 0; // game not over
    }

    return 'D'; // draw
}

void ResetGame() {
    for (int i = 0; i < 9; i++) board[i] = ' ';
    currentPlayer = 'X';
    gameOver = false;
    winnerLine[0] = winnerLine[1] = winnerLine[2] = -1;
}

int main() {
    InitWindow(600, 600, "Tic-Tac-Toe");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (!gameOver && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse = GetMousePosition();
            int col = mouse.x / 200;
            int row = mouse.y / 200;
            int cell = row * 3 + col;

            if (cell >= 0 && cell < 9 && board[cell] == ' ') {
                board[cell] = currentPlayer;
                int result = CheckWinner();
                if (result == 'X' || result == 'O' || result == 'D') {
                    gameOver = true;
                } else {
                    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
                }
            }
        }

        if (gameOver && IsKeyPressed(KEY_R)) {
            ResetGame();
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw grid
        for (int i = 1; i < 3; i++) {
            DrawLine(i * 200, 0, i * 200, 600, BLACK); // vertical
            DrawLine(0, i * 200, 600, i * 200, BLACK); // horizontal
        }

        // Draw marks
        for (int i = 0; i < 9; i++) {
            int x = (i % 3) * 200 + 100;
            int y = (i / 3) * 200 + 100;

            if (board[i] == 'X') {
                DrawLine(x - 50, y - 50, x + 50, y + 50, RED);
                DrawLine(x + 50, y - 50, x - 50, y + 50, RED);
            } else if (board[i] == 'O') {
                DrawCircleLines(x, y, 50, BLUE);
            }
        }

        // Draw winning line
        if (gameOver && winnerLine[0] != -1) {
            int x1 = (winnerLine[0] % 3) * 200 + 100;
            int y1 = (winnerLine[0] / 3) * 200 + 100;
            int x2 = (winnerLine[2] % 3) * 200 + 100;
            int y2 = (winnerLine[2] / 3) * 200 + 100;
            DrawLine(x1, y1, x2, y2, GREEN);
        }

        // Show game over message
        if (gameOver) {
            const char* msg = (CheckWinner() == 'D') ? "Draw!" : (CheckWinner() == 'X' ? "X Wins!" : "O Wins!");
            DrawText(msg, 220, 270, 40, DARKGRAY);
            DrawText("Press R to restart", 180, 320, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}