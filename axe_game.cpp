#include "raylib.h"


int main()
{
    int width =800;
    int heigth = 450;

/*
    float root_beer =1.99f;
    double cheese_burger =5.99f;
    bool shouldHaveLunch =true;
*/
    
    InitWindow(width,heigth,"Hello");
 
    // circle
    int circle_x = 200;
    int circle_y = 200;
    int radius = 25;

    // circle edges
    int l_circle_x = circle_x -radius;
    int r_circle_x = circle_x +radius;
    int u_circle_y = circle_y -radius;
    int d_circle_y = circle_y + radius;
 
    // axe
    int axe_x = 400;
    int axe_y =0;
    int axe_length =50;
    int direction = 10;

    // axe edges
    int l_axe_x =axe_x;
    int r_axe_x = axe_x +axe_length;
    int u_axe_y = axe_y;
    int d_axe_y = axe_y + axe_length;

    bool collision_with_axe = (d_axe_y >= u_circle_y) &&
                            (u_axe_y <= d_circle_y) &&
                            (r_axe_x >= l_circle_x) &&
                            (l_axe_x <= r_circle_x);

    SetTargetFPS(60);
    while (WindowShouldClose() != true)
    {
        BeginDrawing();
        ClearBackground(WHITE);

        if (collision_with_axe)
        {
            DrawText("Game Over!",350,200,20,RED);
        }
        else
        {
            // Game Logic Begins

            // Update the edges
            l_circle_x = circle_x -radius;
            r_circle_x = circle_x +radius;
            u_circle_y = circle_y -radius;
            d_circle_y = circle_y + radius;

            l_axe_x =axe_x;
            r_axe_x = axe_x +axe_length;
            u_axe_y = axe_y;
            d_axe_y = axe_y + axe_length;

            // update collision with axe
            collision_with_axe =(d_axe_y >= u_circle_y) &&
                            (u_axe_y <= d_circle_y) &&
                            (r_axe_x >= l_circle_x) &&
                            (l_axe_x <= r_circle_x);

            DrawCircle(circle_x,circle_y,radius,BLUE);
            DrawRectangle(axe_x,axe_y,axe_length,axe_length,RED);

            // drop the axe
            axe_y += direction;

            if(axe_y > heigth- 50 || axe_y <0)
            {
                direction = -direction;
            }

            // move the circle
            if(IsKeyDown(KEY_D) && circle_x < width- radius)
            {
                circle_x +=10;
            }
            if(IsKeyDown(KEY_A) && circle_x-radius > 0)
            {
                circle_x -=10;
            }


        // Game Logic Ends
        }
        EndDrawing();
    }

}