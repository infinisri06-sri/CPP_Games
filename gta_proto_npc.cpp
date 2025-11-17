#include "raylib.h"
#include <cmath>
#include <vector>

const int TILE_SIZE = 64;
const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;
const int MAX_NPCS = 10;

enum TileType { GRASS, ROAD, BUILDING };
enum Direction { UP, DOWN, LEFT, RIGHT };

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

struct NPC {
    Vector2 pos;
    Direction dir;
    float speed;
    float timer;
};

struct Blood {
    Vector2 pos;
    float timer;
};

Vector2 playerPos = { 1 * TILE_SIZE + TILE_SIZE / 2.0f, 1 * TILE_SIZE + TILE_SIZE / 2.0f };
Vector2 carPos = { 4 * TILE_SIZE + TILE_SIZE / 2.0f, 4 * TILE_SIZE + TILE_SIZE / 2.0f };
float playerSpeed = 2.5f;
float carSpeed = 3.5f;
bool inCar = false;
float carRotation = 0.0f;

std::vector<NPC> npcs;
std::vector<Blood> bloods;
int killCount = 0;

bool IsWalkable(int x, int y) {
    if (x < 0 || y < 0 || x >= MAP_WIDTH || y >= MAP_HEIGHT) return false;
    return map[y][x] != BUILDING;
}

float Distance(Vector2 a, Vector2 b) {
    return sqrtf((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

NPC CreateNPC() {
    NPC npc;
    npc.pos = { (float)(GetRandomValue(1, 8)) * TILE_SIZE + TILE_SIZE / 2.0f,
                (float)(GetRandomValue(1, 8)) * TILE_SIZE + TILE_SIZE / 2.0f };
    npc.dir = (Direction)(GetRandomValue(0, 3));
    npc.speed = 1.0f;
    npc.timer = 0;
    return npc;
}

void SpawnNPCs(int count) {
    for (int i = 0; i < count; i++) {
        npcs.push_back(CreateNPC());
    }
}

void UpdateNPCs(float delta) {
    for (auto& npc : npcs) {
        npc.timer += delta;
        if (npc.timer > 2.0f) {
            npc.dir = (Direction)(GetRandomValue(0, 3));
            npc.timer = 0;
        }

        Vector2 next = npc.pos;
        switch (npc.dir) {
            case UP:    next.y -= npc.speed; break;
            case DOWN:  next.y += npc.speed; break;
            case LEFT:  next.x -= npc.speed; break;
            case RIGHT: next.x += npc.speed; break;
        }

        int tx = (int)(next.x / TILE_SIZE);
        int ty = (int)(next.y / TILE_SIZE);

        if (IsWalkable(tx, ty)) {
            npc.pos = next;
        } else {
            npc.dir = (Direction)(GetRandomValue(0, 3));
        }
    }
}

void UpdateBloods(float delta) {
    for (int i = 0; i < bloods.size(); ) {
        bloods[i].timer -= delta;
        if (bloods[i].timer <= 0) {
            bloods.erase(bloods.begin() + i);
        } else {
            i++;
        }
    }
}

int main() {
    InitWindow(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE, "GTA Prototype - Phase 6");
    SetTargetFPS(60);
    SpawnNPCs(MAX_NPCS);

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();

        // Movement
        Vector2* controlled = inCar ? &carPos : &playerPos;
        Vector2 nextPos = *controlled;

        if (IsKeyDown(KEY_D)) {
            nextPos.x += inCar ? carSpeed : playerSpeed;
            if (inCar) carRotation = 0.0f;
        }
        if (IsKeyDown(KEY_A)) {
            nextPos.x -= inCar ? carSpeed : playerSpeed;
            if (inCar) carRotation = 180.0f;
        }
        if (IsKeyDown(KEY_S)) {
            nextPos.y += inCar ? carSpeed : playerSpeed;
            if (inCar) carRotation = 90.0f;
        }
        if (IsKeyDown(KEY_W)) {
            nextPos.y -= inCar ? carSpeed : playerSpeed;
            if (inCar) carRotation = 270.0f;
        }

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

        UpdateNPCs(dt);
        UpdateBloods(dt);

        // Check car-NPC collision
        for (int i = 0; i < npcs.size(); ) {
            if (inCar && Distance(carPos, npcs[i].pos) < 20) {
                bloods.push_back({ npcs[i].pos, 1.0f });
                npcs.erase(npcs.begin() + i);
                killCount++;
            } else {
                i++;
            }
        }

        // Respawn NPCs to maintain count
        while (npcs.size() < MAX_NPCS) {
            npcs.push_back(CreateNPC());
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

        // Draw blood splatters
        for (auto& b : bloods) {
            DrawCircleV(b.pos, 15, RED);
        }

        // Draw car
        DrawRectanglePro((Rectangle){carPos.x - 20, carPos.y - 10, 40, 20}, (Vector2){20, 10}, carRotation, RED);

        // Draw player
        if (!inCar) {
            DrawCircleV(playerPos, 12, SKYBLUE);
        }

        // Draw NPCs
        for (auto& npc : npcs) {
            DrawCircleV(npc.pos, 10, ORANGE);
        }

        // UI
        DrawText("WASD to move", 10, 10, 20, WHITE);
        DrawText("E to enter/exit car", 10, 35, 20, WHITE);
        DrawText(TextFormat("Kills: %d", killCount), 10, 60, 20, RED);
        if (inCar) DrawText("Driving...", 10, 85, 20, YELLOW);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}