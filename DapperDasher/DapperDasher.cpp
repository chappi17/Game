#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};



int main()
{
    // window dimension
    const int WIdTH = 512;
    const int Height =380;

    // initialize the window
    InitWindow(WIdTH,Height,"DapperDasher");
   
    int velocity = 0;

    // accelration due to gravity 
    const float gravity = 1000.0f;
    const int jumpvel = -600;

    //nebula varibles
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");

    AnimData nebulaData = 
    {
    {0.0,0.0,nebula.width/8, nebula.height/8},
     {WIdTH,Height-nebula.height/8},
     0,
     1.0f/12.0f,
     0
     };

     AnimData nebula2Data =
     {
        {0.0,0.0,nebula.width/8,nebula.height/8},
        {WIdTH +300, Height - nebula.height/8},
        0,
        1.0f/16.0f,
        0
     };




    int nebulaVel= -200;


    //scarfy variables
    Texture2D scarfy =LoadTexture("textures/scarfy.png");
    AnimData scarftyData;
    scarftyData.rec.width = scarfy.width/6;
    scarftyData.rec.height = scarfy.height;
    scarftyData.rec.x = 0;
    scarftyData.rec.y =0;
    scarftyData.pos.x= WIdTH/2 - scarftyData.rec.width/2;
    scarftyData.pos.y = Height- scarftyData.rec.height;
    scarftyData.frame =0;
    scarftyData.updateTime =1.0f/12.0f;
    scarftyData.runningTime = 0.0f;




    int frame =0;
    int nebulaframe =0;

    float updateTime= 1.0f/12.0f;
    float nebulaupdateTime = 1.0f/12.0f;

    float nebulaRunningTime;
    float runningTime;


    int nebula2frame=0;
    const float nebula2updateTime={1.0f/16.0f};
    float nebula2RunningTime;

    bool isInAir;
    SetTargetFPS(60);
    while (!WindowShouldClose()) 
    {
        //Delta Time
        const float DT = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        // perform ground check
        if(scarfyPos.y >= Height-scarfyRec.height)
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
            // update runningTime
            runningTime += DT;
            if (runningTime >= updateTime)
            {
                runningTime = 0;
                
                // update animation frame
                scarfyRec.x = frame * scarfyRec.width;
                frame++;

                if ( frame > 5)
                {
                    frame =0;
                }
            }
        }

        //update nubula animation frame
        nebulaRunningTime += DT;
        if (nebulaRunningTime >= nebulaupdateTime)
        {
            nebulaRunningTime = 0;
            nebulaRec.x = nebula2frame * nebulaRec.width;
            nebula2frame++;

            if (nebulaframe > 7)
            {
                nebulaframe = 0;
            }
        }

        nebula2RunningTime += DT;
        if (nebula2RunningTime >= nebula2updateTime)
        {
            nebula2RunningTime = 0;
            nebula2Rec.x = nebula2frame * nebula2Rec.width;
            nebula2frame++;

            if (nebula2frame > 7)
            {
                nebula2frame = 0;
            }
        }

        //jump Check
        if(IsKeyDown(KEY_SPACE) && !isInAir)
        {
            velocity += jumpvel;
        }

        //update nebula Postion
        nebulaPos.x +=nebulaVel * DT;

        //update 2nebula Position

        nebula2Pos.x += nebulaVel * DT;

        // update Position
        scarfyPos.y +=velocity *DT;

        

        //Draw nebula
        DrawTextureRec(nebula,nebulaRec,nebulaPos,WHITE);

        DrawTextureRec(nebula,nebula2Rec,nebula2Pos,WHITE);

        // Drwa Scarfy
        DrawTextureRec(scarfy,scarfyRec,scarfyPos,WHITE);
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);
    CloseWindow();
    

}