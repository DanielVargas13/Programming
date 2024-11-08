#include "raylib.h"

int main() 
{
    // Window
    const int width = 512;
    const int height = 380;
    InitWindow(width, height, "Dapper Dasher");

    const int gravity = 1;

    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyBox = {
        x: 0,
        y: 0,
        width: float(scarfy.width/6),
        height: float(scarfy.height),
    };
    Vector2 scarfyPos = {
        x: (width/2) - (scarfyBox.width/2),
        y: height - scarfyBox.height,
    };

    const int initialPosY = height - scarfyBox.height;
    int velocity = 0;
    int isInAir = false;
    const int jumpVel = -22;

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfyPos.y < initialPosY) {
            velocity += gravity;
            isInAir = true;
        } else {
            velocity = 0;
            isInAir = false;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVel;
        }

        scarfyPos.y += velocity;
        
        DrawTextureRec(scarfy, scarfyBox, scarfyPos, WHITE);    

        EndDrawing();
    }
    UnloadTexture(scarfy);
    CloseWindow();
}