#include "raylib.h"

int main() 
{
    int low_limit = 0;
    int death = false;

    // Window
    int width = 800;
    int height = 450;
    InitWindow(width, height, "Daniel's Window");

    // Game Over
    int gv_pos_x = 400;
    int gv_pos_y = 200;
    int font_size = 20;

    // Circle
    int circle_x = 200;
    int circle_y = 200;
    int speed_x = 10;
    int radius = 25;
    // Circle edges
    int l_circle_x = circle_x - radius;
    int r_circle_x = circle_x + radius;
    int u_circle_y = circle_y - radius;
    int b_circle_y = circle_y + radius;

    // Axe
    int axe_pos_x = 400;
    int axe_pos_y = 0;
    int axe_speed = 10;
    int lenght = 50;
    // Axe edges
    int l_axe_x = axe_pos_x;
    int r_axe_x = axe_pos_x + lenght;
    int u_axe_y = axe_pos_y;
    int b_axe_y = axe_pos_y + lenght;

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (death) 
        {
            DrawText("Game Over!", gv_pos_x, gv_pos_y, 
                font_size, RED);
        } 
        else 
        {
            // Update edges
            l_circle_x = circle_x - radius;
            r_circle_x = circle_x + radius;
            u_circle_y = circle_y - radius;
            b_circle_y = circle_y + radius;

            l_axe_x = axe_pos_x;
            r_axe_x = axe_pos_x + lenght;
            u_axe_y = axe_pos_y;
            b_axe_y = axe_pos_y + lenght;

            // You died?
            death = (b_axe_y >= u_circle_y && 
                u_axe_y <= b_circle_y && 
                l_axe_x <= r_circle_x && 
                r_axe_x >= l_circle_x);

            DrawCircle(circle_x, circle_y, radius, BLUE);
            DrawRectangle(axe_pos_x, axe_pos_y, lenght, 
                lenght, RED);

            // Move the axe
            axe_pos_y += axe_speed;
            if (axe_pos_y > height || axe_pos_y < low_limit) 
            {
                axe_speed = -axe_speed;
            }

            // Move the circle
            if (IsKeyDown(KEY_D) && circle_x < width) 
            {
                circle_x += speed_x;
            }
            if (IsKeyDown(KEY_A) && circle_x > low_limit) 
            {
                circle_x -= speed_x;
            }
        }

        EndDrawing();
    }
}