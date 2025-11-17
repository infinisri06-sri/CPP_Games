#include "raylib.h"

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

// Start player in a walkable tile (1,1)
Vector2 playerPos = { 1 * TILE_SIZE + TILE_SIZE / 2.0f, 1 * TILE_SIZE + TILE_SIZE / 2.0f };
float playerSpeed = 2.5f;

bool IsWalkable(int x, int y) {
    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) return false;
    return map[y][x] != BUILDING;
}

int main() {
    InitWindow(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "GTA Prototype - Phase 1");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Movement
        Vector2 nextPos = playerPos;

        if (IsKeyDown(KEY_D)) nextPos.x += playerSpeed;
        if (IsKeyDown(KEY_A)) nextPos.x -= playerSpeed;
        if (IsKeyDown(KEY_S)) nextPos.y += playerSpeed;
        if (IsKeyDown(KEY_W)) nextPos.y -= playerSpeed;

        int tileX = (int)(nextPos.x / TILE_SIZE);
        int tileY = (int)(nextPos.y / TILE_SIZE);

        if (IsWalkable(tileX, tileY)) {
            playerPos = nextPos;
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

        // Draw player
        DrawCircleV(playerPos, 12, SKYBLUE);

        DrawText("Use WASD to move", 10, 10, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}