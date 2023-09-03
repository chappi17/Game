#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeigth)
{
    return data.pos.y >= windowHeigth - data.rec.height;
}

AnimData updateAnimData(AnimData data,float deltaTime, int maxFrame)
{
    // update runnuing time
    data.runningTime += deltaTime;
    if(data.runningTime >= data.updateTime)
    {
        data.runningTime = 0;
        // update animation frame

        data.rec.x = data.frame * data.rec.width;
        data.frame++;

        if(data.frame > maxFrame)
        {
            data.frame =0;
        }
    }

    return data;
}

bool collision = false;
int main()
{

    // window dimension
    int windwDimensions[2];
    windwDimensions[0] = 512;
    windwDimensions[1] = 380;

    // initialize the window
    InitWindow(windwDimensions[0],windwDimensions[1],"DapperDasher");
   
    int velocity = 0;

    // accelration due to gravity 
    const float gravity = 1000.0f;
    const int jumpvel = -600;

    //nebula varibles
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    const int sizeOfnebulae = 6;
     AnimData nebulae[sizeOfnebulae]{};

     for(int i=0; i < sizeOfnebulae; i++)
     {
        nebulae[i].rec.x = 0.0;
        nebulae[i].rec.y = 0.0;
        nebulae[i].rec.width = nebula.width/8;
        nebulae[i].rec.height = nebula.height/8;
        nebulae[i].pos.y = windwDimensions[1] - nebula.height/8;
        nebulae[i].frame = 0;
        nebulae[i].runningTime =0.0;
        nebulae[i].updateTime = 1.0f/16.0f;
         nebulae[i] .pos.x = windwDimensions[0] + i * 300;
     }

     float finishLine = nebulae[sizeOfnebulae-1].pos.x ;


    int nebulaVel= -200;


    //scarfy variables
    Texture2D scarfy =LoadTexture("textures/scarfy.png");
    AnimData scarftyData;
    scarftyData.rec.width = scarfy.width/6;
    scarftyData.rec.height = scarfy.height;
    scarftyData.rec.x = 0;
    scarftyData.rec.y =0;
    scarftyData.pos.x= windwDimensions[0]/2 - scarftyData.rec.width/2;
    scarftyData.pos.y = windwDimensions[1]- scarftyData.rec.height;
    scarftyData.frame =0;
    scarftyData.updateTime =1.0f/12.0f;
    scarftyData.runningTime = 0.0f;


    bool isInAir;

    Texture2D background = LoadTexture("textures/far-buildings.png");
    Texture2D midground = LoadTexture("textures/back-buildings.png");
    Texture2D foreground = LoadTexture("textures/foreground.png");
    float bgX= {};
    float mgX = {};
    float fgX = {};

    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        //Delta Time
        const float DT = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        bgX -= 20* DT;
        mgX -= 40 * DT;
        fgX -= 80 * DT;
        if(bgX <= -background.width*2)
        {
            bgX = 0.0;
        } 
        if(mgX <= -midground.width*2)
        {
            bgX = 0.0;
        }
        if(fgX <= -foreground.width*2)
        {
            fgX = 0.0;
        }

        // draw the background
        Vector2 bg1Pos= {bgX,0.0};
        DrawTextureEx(background,bg1Pos,0.0,2.0,WHITE);
        Vector2 bg2Pos= {bgX+background.width*2,0.0};
        DrawTextureEx(background,bg2Pos,0.0,2.0,WHITE);

        Vector2 mg1Pos = {mgX,0.0};
        DrawTextureEx(midground,mg1Pos,0.0,2.0,WHITE);
        Vector2 mg2Pos = {mgX + midground.width*2,0.0};
        DrawTextureEx(midground,mg2Pos,0.0,2.0,WHITE);

        Vector2 fg1Pos = {fgX,0.0};
        DrawTextureEx(foreground,fg1Pos,0.0,2.0,WHITE);
        Vector2 fg2Pos = {fgX+foreground.width*2,0.0};
        DrawTextureEx(foreground,fg2Pos,0.0,2.0,WHITE);


        // perform ground check
        if(isOnGround(scarftyData,windwDimensions[1]))
        {
            velocity = 0;
            isInAir =false;
        }
        else 
        {
            isInAir =true;
            // apply gravity
            velocity += gravity *DT;
        }

        //update scarfy's animation frams
        if (!isInAir)
        {
            scarftyData = updateAnimData(scarftyData,DT,5);
        }

        //update nubula animation frame    
        for(int i =0; i < sizeOfnebulae; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i],DT,7);
        }

        //jump Check
        if(IsKeyDown(KEY_SPACE) && !isInAir)
        {
            velocity += jumpvel;
        }


        for(int i=0; i< sizeOfnebulae;i++)
        {
            nebulae[i].pos.x += nebulaVel * DT;
        }
        //finish line
        finishLine += nebulaVel * DT;

        // update Position
        scarftyData.pos.y +=velocity *DT;

        
        
        for(AnimData nebula : nebulae)
        {
            float pad= {50};
            Rectangle nebRac
            { 
                nebula.pos.x+pad,
                nebula.pos.y+pad,
                nebula.rec.width-2*pad,
                nebula.rec.height-2*pad
            };Rectangle scarftRec
            {
                scarftyData.pos.x,
                scarftyData.pos.y,
                scarftyData.rec.width,
                scarftyData.rec.height
            };

            if (CheckCollisionRecs(nebRac,scarftRec))
            {
                collision = true;
            }
        }

        if (collision)
        {
            // lose the game
            DrawText("Game Over!",windwDimensions[0]/4,windwDimensions[1]/2,40,RED);
        }
        else if (scarftyData.pos.x >= finishLine)
        {
            //Win the game
            DrawText("You Win",windwDimensions[0]/4,windwDimensions[1]/2,40,RED);
        }
        else
        {
            //Draw nebula
            for(int i=0; i <sizeOfnebulae;i++)
            {
                DrawTextureRec(nebula,nebulae[i].rec,nebulae[i].pos,WHITE);
            }

            // Drwa Scarfy
            DrawTextureRec(scarfy,scarftyData.rec,scarftyData.pos,WHITE);
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