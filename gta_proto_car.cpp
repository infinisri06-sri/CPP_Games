#include "raylib.h"
#include <cmath>

const int TILE_SIZE = 64;
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

enum TileType { GRASS, ROAD, BUILDING };

int map[MAP_HEIGHT][MAP_WIDTH] = {
    {1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,2,2,0,0,2,2,0,1},
    {1,0,2,2,0,0,2,2,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,0,2,2,0,0,2,2,0,1},
    {1,0,2,2,0,0,2,2,0,1},
    {1,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1}
};

Vector2 playerPos = { 1 * TILE_SIZE + TILE_SIZE / 2.0f, 1 * TILE_SIZE + TILE_SIZE / 2.0f };
Vector2 carPos = { 4 * TILE_SIZE + TILE_SIZE / 2.0f, 4 * TILE_SIZE + TILE_SIZE / 2.0f };
float playerSpeed = 2.5f;
float carSpeed = 3.5f;
bool inCar = false;

bool IsWalkable(int x, int y) {
    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) return false;
    return map[y][x] != BUILDING;
}

float Distance(Vector2 a, Vector2 b) {
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int main() {
    InitWindow(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "GTA Prototype - Phase 2");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Movement
        Vector2* controlled = inCar ? &carPos : &playerPos;
        Vector2 nextPos = *controlled;

        if (IsKeyDown(KEY_D)) nextPos.x += inCar ? carSpeed : playerSpeed;
        if (IsKeyDown(KEY_A)) nextPos.x -= inCar ? carSpeed : playerSpeed;
        if (IsKeyDown(KEY_S)) nextPos.y += inCar ? carSpeed : playerSpeed;
        if (IsKeyDown(KEY_W)) nextPos.y -= inCar ? carSpeed : playerSpeed;

        int tileX = (int)(nextPos.x / TILE_SIZE);
        int tileY = (int)(nextPos.y / TILE_SIZE);

        if (IsWalkable(tileX, tileY)) {
            *controlled = nextPos;
        }

        // Enter/Exit car
        if (IsKeyPressed(KEY_E)) {
            if (!inCar && Distance(playerPos, carPos) < 30) {
                inCar = true;
            } else if (inCar) {
                playerPos = carPos;
                inCar = false;
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw map
        for (int y = 0; y < MAP_HEIGHT; y++) {
            for (int x = 0; x < MAP_WIDTH; x++) {
                Color color;
                switch (map[y][x]) {
                    case GRASS: color = DARKGREEN; break;
                    case ROAD: color = GRAY; break;
                    case BUILDING: color = BROWN; break;
                }
                DrawRectangle(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, color);
                DrawRectangleLines(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE, BLACK);
            }
        }

        // Draw car
        DrawRectangleV(Vector2{carPos.x - 20, carPos.y - 10}, Vector2{40, 20}, RED);

        // Draw player (only if not in car)
        if (!inCar) {
            DrawCircleV(playerPos, 12, SKYBLUE);
        }

        // UI
        DrawText("WASD to move", 10, 10, 20, WHITE);
        DrawText("E to enter/exit car", 10, 35, 20, WHITE);
        if (inCar) DrawText("Driving...", 10, 60, 20, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}