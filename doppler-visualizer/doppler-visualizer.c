#include <stdio.h>
#include <raylib.h>
#include <string.h>

#define WIDTH 900
#define HEIGHT 600
#define MAX_WAVES 50
#define WAVE_SPEED 100
#define CAR_SPEED 1.0f
#define WAVE_EMISSION_FREQUENCY 6 //Hertz

int current_waves = 0;

struct Car{
    float x,y;
};

struct SoundWave{
    float x,y,r;
};

struct Car car;

struct SoundWave waves[MAX_WAVES];

void draw_car()
{
    DrawCircle(car.x,car.y,20,WHITE);
}

void emit_new_wave()
{
    
     struct SoundWave copy[MAX_WAVES];
     memset(copy, 0, MAX_WAVES*sizeof(struct SoundWave));
     for(int i=0;i<MAX_WAVES;i++)
     {
        copy[i] = waves[i];
     }

    for(int i=0;i<MAX_WAVES;i++)
    {
        if(i< MAX_WAVES -1)
        {
             waves[i+1] = copy[i];
        }
    }
        
    waves[0] = (struct SoundWave){car.x, car.y, 0};

    if(current_waves < MAX_WAVES)
        current_waves++;
}

void draw_waves()
{
    for(int i=0;i<current_waves;i++)
    {
        DrawCircleLines(waves[i].x, waves[i].y, waves[i].r, WHITE);
    }
}

void propagate_waves(float dt)
{
    for(int i=0;i<current_waves;i++)
    {
        waves[i].r += WAVE_SPEED * dt;
    }
}

int main()
{
    InitWindow(WIDTH, HEIGHT, "Doppler Visualizer");

    car = (struct Car){WIDTH/2, HEIGHT/2};

    SetTargetFPS(60);
    float intervals = 0;
    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();
        
        intervals += dt;
        if(intervals > 1.0f / WAVE_EMISSION_FREQUENCY)
        {
            emit_new_wave();
            intervals = 0.0f;
        }
        propagate_waves(dt);

        if(IsKeyDown(KEY_RIGHT)) car.x += CAR_SPEED;
        if(IsKeyDown(KEY_LEFT)) car.x -= CAR_SPEED;
        if(IsKeyDown(KEY_UP)) car.y -= CAR_SPEED;
        if(IsKeyDown(KEY_DOWN)) car.y += CAR_SPEED;

        BeginDrawing();

        ClearBackground(BLACK);
        draw_car();
        draw_waves();

        EndDrawing();
    }
    return 0;
}