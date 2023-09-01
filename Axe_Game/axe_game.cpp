#include "raylib.h"
#include <string>

using namespace std;

// 충돌 체크 함수
bool CheckCollision(int circle_x, int circle_y, int radius, int axe_x, int axe_y, int axe_length) {
    int l_circle_x = circle_x - radius;
    int r_circle_x = circle_x + radius;
    int u_circle_y = circle_y - radius;
    int d_circle_y = circle_y + radius;
    
    int l_axe_x = axe_x;
    int r_axe_x = axe_x + axe_length;
    int u_axe_y = axe_y;
    int d_axe_y = axe_y + axe_length;
    
    return (d_axe_y >= u_circle_y) &&
           (u_axe_y <= d_circle_y) &&
           (r_axe_x >= l_circle_x) &&
           (l_axe_x <= r_circle_x);
}

int main() {
    const int WIDTH = 800;
    const int HEIGHT = 450;
    const int FPS = 60;
    const int AXE_BOUNDARY = HEIGHT - 50;

    int score =0;
    
    InitWindow(WIDTH, HEIGHT, "Hello");
    SetTargetFPS(FPS);
    
    int circle_x = 200;
    int circle_y = 200;
    int radius = 25;
    
    int axe_x = 400;
    int axe_y = 0;
    int axe_length = 50;
    int direction = 10;
    
    bool collision_with_axe = false;
    
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        
        collision_with_axe = CheckCollision(circle_x, circle_y, radius, axe_x, axe_y, axe_length);
        
        if (collision_with_axe) 
        {
            DrawText("Game Over!", 350, 200, 20, RED);
        }
        
        else
        {
            score++;
            string scores =to_string(score);
            DrawText(scores.c_str(),700,20,20,BLACK);
            // Game Logic Begins
            DrawCircle(circle_x, circle_y, radius, BLUE);
            DrawRectangle(axe_x, axe_y, axe_length, axe_length, RED);
            
            // Drop the axe
            axe_y += direction;
            
            if (axe_y > AXE_BOUNDARY || axe_y < 0) {
                direction = -direction;
            }
            
            // Move the circle
            if (IsKeyDown(KEY_D) && circle_x < WIDTH - radius) 
            {
                circle_x += 10;
            }
            if (IsKeyDown(KEY_A) && circle_x - radius > 0) 
            {
                circle_x -= 10;
            }
            if(IsKeyDown(KEY_S) && circle_y <HEIGHT-radius)
            {
                circle_y += 10;
            }
            if(IsKeyDown(KEY_W) && circle_y-radius >0)
            {
                circle_y -=10;
            }

            // Game Logic Ends
        }
        
        EndDrawing();
    }
    
    return 0;
}