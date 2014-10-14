#include "sdl_testenviroment.h"
#include <SDL2/SDL.h>

void SDL_TestEnviroment::SetUp()
{
    auto sdl_init_status = SDL_Init(SDL_INIT_EVENTS
                                    | SDL_INIT_JOYSTICK
                                    | SDL_INIT_GAMECONTROLLER);
    ASSERT_TRUE(sdl_init_status==0);
}

void SDL_TestEnviroment::TearDown()
{
    SDL_Quit();
}
