#include "raylib.h"

struct AnimData
{
    Rectangle box;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

int main() 
{
    const int gravity = 1000;

    // Window
    int windowDimensions[2]{512, 380};
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // Nebula
    int nebVel = -200;
    Color nebColor[3]{ WHITE, RED, GREEN };
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData nebulae[3]{};

    for (int i = 0; i < 3; i++) {
        nebulae[i].box = {
            x: 0,
            y: 0,
            width: float(nebula.width/8),
            height: float(nebula.height/8),
        };
        nebulae[i].pos = {
            y: float(windowDimensions[1] - nebula.height/8),
        };
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0;
    };

    nebulae[0].pos.x = float(windowDimensions[0]);
    nebulae[0].updateTime = 1.0/12.0;

    nebulae[1].pos.x = float(windowDimensions[0] + 300);
    nebulae[1].updateTime = 1.0/16.0;

    nebulae[2].pos.x = float(windowDimensions[0] + 600);
    nebulae[2].updateTime = 1.0/14.0;

    // Scarfy
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData{
        box: {
            x: 0,
            y: 0,
            width: float(scarfy.width/6),
            height: float(scarfy.height),
        },
        pos: {
            x: float(windowDimensions[0]/2 - (scarfy.width/6)/2),
            y: float(windowDimensions[1] - scarfy.height),
        },
        frame: 0,
        updateTime: 1.0/12.0,
        runningTime: 0.0
    };

    const int initialPosY = windowDimensions[1] - scarfyData.box.height;
    int velocity = 0;
    int isInAir = false;
    const int jumpVel = -600;

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        const float dT = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(WHITE);

        if (scarfyData.pos.y < initialPosY) {
            velocity += gravity * dT;
            isInAir = true;
        } else {
            velocity = 0;
            isInAir = false;
        }

        if (IsKeyPressed(KEY_SPACE) && !isInAir) {
            velocity += jumpVel;
        }

        // Update scarfy position
        scarfyData.pos.y += velocity * dT;

        // Scarfy animation
        if (!isInAir) {
            scarfyData.runningTime += dT;
            if (scarfyData.runningTime >= scarfyData.updateTime) {
                scarfyData.runningTime = 0.0;
                scarfyData.box.x = scarfyData.frame * scarfyData.box.width;
                scarfyData.frame++;

                if (scarfyData.frame > 5) {
                    scarfyData.frame = 0;
                }
            }
        }

        for (int i = 0; i < 3; i++) {
            nebulae[i].pos.x += nebVel * dT;
            nebulae[i].runningTime += dT;
            if (nebulae[i].runningTime >= nebulae[i].updateTime) {
                nebulae[i].runningTime = 0.0;
                nebulae[i].box.x = nebulae[i].frame * nebulae[i].box.width;
                nebulae[i].frame++;

                if (nebulae[i].frame > 7) {
                    nebulae[i].frame = 0;
                }
            }
            DrawTextureRec(nebula, nebulae[i].box, nebulae[i].pos, nebColor[i]);
        };
        
        // Draw scarfy
        DrawTextureRec(scarfy, scarfyData.box, scarfyData.pos, WHITE);    

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
}