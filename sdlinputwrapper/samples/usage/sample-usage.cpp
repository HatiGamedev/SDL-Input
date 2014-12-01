#include <iostream>
#include <SDL2/SDL.h>
#include <cassert>

#include <sdlinputwrapper/sdlinputwrapper.h>
#include <memory>

#include "device.h"
#include <sdlinputwrapper/callback.h>

enum SampleInputActions
{
    Shoot,
    CHANGE_CTX,

    GAME_QUIT
};

enum SampleInputAxis
{
    Horizontal
};

enum SampleContext
{
    GameMod,
    Game,
    Menu,

    MAX_COUNT
};

void func()
{
    std::cout << "raw c function" << std::endl;
}

void sdlKeyEvent(const SDL_Event& e, sdli::Interface& device)
{
    device.push(sdli::InputType::Keyboard, e.key.keysym.scancode, e.key.state);
}

#include "stub.h"

int main(int argc, char** argv)
{
//    std::setbuf(stdout, NULL); // used to always flush std::cout

    auto sdl_init_status = SDL_Init(SDL_INIT_EVENTS
                                     | SDL_INIT_JOYSTICK
                                     | SDL_INIT_GAMECONTROLLER);
    assert(sdl_init_status==0);

    bool sampleQuit = false;

    auto inputproc = std::unique_ptr<sdli::Processor>(new sdli::Processor(SampleContext::MAX_COUNT));

    auto& keyboard = inputproc->getKeyboard();
    auto& pad = inputproc->getGamecontroller(0);

    SDL_Window* w = SDL_CreateWindow("SampleWindow", 0, 0, 800, 600, SDL_WindowFlags::SDL_WINDOW_SHOWN|SDL_WindowFlags::SDL_WINDOW_OPENGL);

    auto sdl_glContext = SDL_GL_CreateContext(w);




    SDL_Event event;
    while(!sampleQuit)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                sampleQuit = true;
                break;
            }
            inputproc->handleSdlEvents(event);
        }

        SDL_GL_SwapWindow(w);
    }

    SDL_GL_DeleteContext(sdl_glContext);
    SDL_DestroyWindow(w);

    return 0;
}
