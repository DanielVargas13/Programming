#include "raylib.h"

struct AnimData
{
    Rectangle box;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight) {
    return data.pos.y < windowHeight - data.box.height;
}

AnimData updateAnimation(AnimData data, float deltaTime, int animFrames) {
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime) {
        data.runningTime = 0.0;
        data.box.x = data.frame * data.box.width;
        data.frame++;

        if (data.frame > animFrames) {
            data.frame = 0;
        }
    }

    return data;
}

bool verifyEndGame(
    bool collision, 
    int pos[], 
    float finishLine, 
    float scarfyX
) {
    if (collision) {
        DrawText("Game Over!", pos[0]/4, pos[1]/2, 40, RED);
        return true;
     }
     else if (scarfyX >= (finishLine + 300))
     {
        DrawText("You Win!", pos[0]/4, pos[1]/2, 40, GREEN);
        return true;
     }
     return false;
}

int main() 
{
    const int gravity = 1000;

    // Window
    int windowDimensions[2]{512, 380};
    InitWindow(windowDimensions[0], windowDimensions[1], "Dapper Dasher");

    // Nebula
    int nebVel = -200;
    const int sizeOfNebulae = 6;
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData nebulae[sizeOfNebulae]{};

    for (int i = 0; i < sizeOfNebulae; i++) {
        nebulae[i].box = {
            x: 0,
            y: 0,
            width: float(nebula.width/8),
            height: float(nebula.height/8),
        };
        nebulae[i].pos = {
            y: float(windowDimensions[1] - nebula.height/8),
        };
        nebulae[i].pos.x = windowDimensions[0] + (i * 300);
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0;
        nebulae[i].updateTime = 1.0/12.0;
    };

    float finishLine = nebulae[sizeOfNebulae-1].pos.x;

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

    int velocity = 0;
    int isInAir = false;
    const int jumpVel = -600;

    Texture2D background = LoadTexture("textures/far-buildings.png");
    float bgX = 0.0;

    Texture2D midground = LoadTexture("textures/back-buildings.png");
    float mgX = 0.0;

    Texture2D foreground = LoadTexture("textures/foreground.png");
    float fgX = 0.0;

    bool collision = false;

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        const float dT = GetFrameTime();
        
        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20 * dT;
        if (bgX <= -(background.width * 2)) {
            bgX = 0.0;
        }

        mgX -= 40 * dT;
        if (mgX <= -(midground.width * 2)) {
            mgX = 0.0;
        }

        fgX -= 80 * dT;
        if (fgX <= -(foreground.width * 2)) {
            fgX = 0.0;
        }

        // Draw background
        Vector2 bg1Pos{bgX, 0.0};
        DrawTextureEx(background, bg1Pos, 0.0, 2.0, WHITE);

        Vector2 bg2Pos{bgX + (background.width * 2), 0.0};
        DrawTextureEx(background, bg2Pos, 0.0, 2.0, WHITE);

        // Draw midground
        Vector2 mg1Pos{mgX, 0.0};
        DrawTextureEx(midground, mg1Pos, 0.0, 2.0, WHITE);

        Vector2 mg2Pos{mgX + (midground.width * 2), 0.0};
        DrawTextureEx(midground, mg2Pos, 0.0, 2.0, WHITE);

        // Draw foreground
        Vector2 fg1Pos{fgX, 0.0};
        DrawTextureEx(foreground, fg1Pos, 0.0, 2.0, WHITE);

        Vector2 fg2Pos{fgX + (foreground.width * 2), 0.0};
        DrawTextureEx(foreground, fg2Pos, 0.0, 2.0, WHITE);

        if (isOnGround(scarfyData, windowDimensions[1])) {
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
            scarfyData = updateAnimation(scarfyData, dT, 5);
        }

        for (AnimData nebulaInst : nebulae) {
            float pad = 50;
            Rectangle nebRec{
                nebulaInst.pos.x + pad,
                nebulaInst.pos.y + pad,
                nebulaInst.box.width - (2 * pad),
                nebulaInst.box.height - (2 * pad),
            };
            Rectangle scarfyRec{
                scarfyData.pos.x,
                scarfyData.pos.y,
                scarfyData.box.width,
                scarfyData.box.height,
            };
            if (CheckCollisionRecs(nebRec, scarfyRec)) {
                collision = true;
            }
        };

        for (int i = 0; i < sizeOfNebulae; i++) {
            nebulae[i].pos.x += nebVel * dT;
            nebulae[i] = updateAnimation(nebulae[i], dT, 7);
            if (!verifyEndGame(collision, windowDimensions, finishLine, scarfyData.pos.x)) {
                DrawTextureRec(nebula, nebulae[i].box, nebulae[i].pos, WHITE);
            }
        };

        finishLine += nebVel * dT;
        
        // Draw scarfy
        if (!verifyEndGame(collision, windowDimensions, finishLine, scarfyData.pos.x)) {
            DrawTextureRec(scarfy, scarfyData.box, scarfyData.pos, WHITE);     
        }

        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    UnloadTexture(background);
    UnloadTexture(midground);
    UnloadTexture(foreground);
    CloseWindow();
}