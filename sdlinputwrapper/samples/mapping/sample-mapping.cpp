#include <iostream>
#include <SDL2/SDL.h>
#include <cassert>

#include <sdlinputwrapper/sdlinputwrapper.h>
#include <memory>

#include "device.h"
#include <sdlinputwrapper/callback.h>

enum SampleInputActions
{
    SampleDown,
    Shoot,
    CHANGE_CTX,

    GAME_QUIT
};

enum SampleAxes
{
    MoveHorizontal
};

enum SampleContext
{
    GameMod,
    Game,
    Menu,

    MAX_COUNT
};

int main(int argc, char** argv)
{
//    std::setbuf(stdout, NULL); // used to always flush std::cout

    auto sdl_init_status = SDL_Init(SDL_INIT_EVENTS
                                     | SDL_INIT_JOYSTICK
                                     | SDL_INIT_GAMECONTROLLER);
    assert(sdl_init_status==0);

    auto inputproc = std::unique_ptr<sdli::Processor>(new sdli::Processor(SampleContext::MAX_COUNT));

    auto& device = inputproc->getKeyboard();
    auto& pad = inputproc->getGamecontroller(0);

    /** BEG Mappings **/

    auto ctx1 = inputproc->createContext(SampleContext::GameMod);
    auto ctx2 = inputproc->createContext(SampleContext::Game);

    ctx1->mapAxis(SDL_SCANCODE_D, SDL_SCANCODE_A, SampleAxes::MoveHorizontal);

    return 0;
}
