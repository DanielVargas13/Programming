#include "raylib.h"

int main() 
{
    const int gravity = 1000;

    // Window
    const int width = 512;
    const int height = 380;
    InitWindow(width, height, "Dapper Dasher");

    // Nebula
    int nebVel = -200;
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    // Nebula 1
    Rectangle nebulaBox{
        x: 0,
        y: 0,
        width: float(nebula.width/8),
        height: float(nebula.height/8),
    };
    Vector2 nebulaPos{
        x: width,
        y: height - nebulaBox.height,
    };

    int nebFrame = 0;
    const float nebUpdateTime = 1.0/12.0;
    float nebRunningTime = 0.0;

    // Nebula 2
    Rectangle nebula2Box{
        x: 0,
        y: 0,
        width: float(nebula.width/8),
        height: float(nebula.height/8),
    };
    Vector2 nebula2Pos{
        x: width + 300,
        y: height - nebulaBox.height,
    };

    int neb2Frame = 0;
    const float neb2UpdateTime = 1.0/16.0;
    float neb2RunningTime = 0.0;

    // Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    Rectangle scarfyBox{
        x: 0,
        y: 0,
        width: float(scarfy.width/6),
        height: float(scarfy.height),
    };
    Vector2 scarfyPos{
        x: (width/2) - (scarfyBox.width/2),
        y: height - scarfyBox.height,
    };

    const int initialPosY = height - scarfyBox.height;
    int velocity = 0;
    int isInAir = false;
    const int jumpVel = -600;

    int frame = 0;
    const float updateTime = 1.0/12.0;
    float runningTime = 0.0;

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        const float dT = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfyPos.y < initialPosY) {
            velocity += gravity * dT;
            isInAir = true;
        } else {
            velocity = 0;
            isInAir = false;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVel;
        }

        // Update nebula 1 position
        nebulaPos.x += nebVel * dT;

        // Update nebula 2 position
        nebula2Pos.x += nebVel * dT;

        // Update scarfy position
        scarfyPos.y += velocity * dT;

        // Scarfy animation
        if (!isInAir) {
            runningTime += dT;
            if (runningTime >= updateTime) {
                runningTime = 0.0;
                scarfyBox.x = frame * scarfyBox.width;
                frame++;

                if (frame > 5) {
                    frame = 0;
                }
            }
        }

        // Nebula 1 animation
        nebRunningTime += dT;
        if (nebRunningTime >= nebUpdateTime) {
            nebRunningTime = 0.0;
            nebulaBox.x = nebFrame * nebulaBox.width;
            nebFrame++;

            if (nebFrame > 7) {
                nebFrame = 0;
            }
        }

        // Nebula 2 animation
        neb2RunningTime += dT;
        if (neb2RunningTime >= neb2UpdateTime) {
            neb2RunningTime = 0.0;
            nebula2Box.x = neb2Frame * nebula2Box.width;
            neb2Frame++;

            if (neb2Frame > 7) {
                neb2Frame = 0;
            }
        }
        
        // Draw nebula 1
        DrawTextureRec(nebula, nebulaBox, nebulaPos, WHITE);

        // Draw nebula 2
        DrawTextureRec(nebula, nebula2Box, nebula2Pos, RED); 
        
        // Draw scarfy
        DrawTextureRec(scarfy, scarfyBox, scarfyPos, WHITE);    

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}