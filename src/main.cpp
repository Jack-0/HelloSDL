#include <iostream>
#include <SDL2/SDL.h>

#include "Game.h"
#include "entity/mob/Player.h"


SDL_Window* window = 0;
SDL_Renderer* renderer = 0;

Game* game = nullptr;


#define FRAME_VALUES 10 // The array will hold 10 frames (higher == more accuracy)
Uint32 frametimes[FRAME_VALUES]; // to store frames
Uint32 frametimelast; // last calculated SDL_GetTicks
Uint32 framecount; // total frames rendered
float framespersecond; // fps

void fpsinit()
{
    // Set all frame times to 0ms.
    memset(frametimes, 0, sizeof(frametimes));
    framecount = 0;
    framespersecond = 0;
    frametimelast = SDL_GetTicks();
}

void fpsCalc()
{
    Uint32 frametimesindex;
    Uint32 getticks;
    Uint32 count;
    Uint32 i;

    // frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
    // This value rotates back to 0 after it hits FRAME_VALUES.
    frametimesindex = framecount % FRAME_VALUES;

    getticks = SDL_GetTicks(); // store current time
    frametimes[frametimesindex] = getticks - frametimelast; //save the frame time value
    frametimelast = getticks; // save last frame time for next fpsCalc call
    framecount++;

    // Work out the current framerate

    // test to see if whole array ahs been written to
    if (framecount < FRAME_VALUES)
        count = framecount;
    else
        count = FRAME_VALUES;

    // add up all the values and divide to get the average frame time.
    framespersecond = 0;
    for (i = 0; i < count; i++)
        framespersecond += frametimes[i];

    framespersecond /= count;
    framespersecond = 1000.f / framespersecond; // convert to fps
}


const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

const int SCREEN_WIDTH = 1440 * 0.8;
const int SCREEN_HEIGHT = 900 * 0.8;

int main()
{
    Uint32 frame_start, frame_time;

    // initialise game and start game loop
    if(TheGame::Instance()->init("Hello SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0))
    {
        std::cout << "TheGame::Instance()->init = success" << std::endl;

        fpsinit();

        while(TheGame::Instance()->isRunning())
        {
            frame_start = SDL_GetTicks();

            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            frame_time = SDL_GetTicks() - frame_start;

            if(frame_time < DELAY_TIME)
                SDL_Delay((int)(DELAY_TIME - frame_time));

            //SDL_Delay(6);

            /// FPS
            //fpsCalc();
            //std::cout << "fps = " << framespersecond << std::endl;
        }
    }
    else
    {
        return -1;
    }

    TheGame::Instance()->clean();

    return 0;
}