#include <iostream>
#include <SDL2/SDL.h>
#include <cassert>

#include <sdlinputwrapper/sdlinputwrapper.h>

enum SampleInputActions
{
    SampleDown
};

enum SampleContext
{
    Menu,
    Game
};

void sdlKeyEvent(const SDL_Event& e, sdli::InputDevice& device)
{
    device.push(sdli::InputType::Keyboard, e.key.keysym.scancode, e.key.state);
}

int main(int argc, char** argv)
{
    auto sdl_init_status = SDL_Init(SDL_INIT_EVENTS
                                     | SDL_INIT_JOYSTICK
                                     | SDL_INIT_GAMECONTROLLER);
    assert(sdl_init_status==0);

    sdli::InputDevice device;


    bool sampleQuit = false;
    bool onUpdate = false;

    auto ctx1 = new sdli::InputContext(SampleContext::Menu);

    device.mapDigital(SDL_SCANCODE_S, SampleInputActions::SampleDown);

    SDL_Window* w = SDL_CreateWindow("SampleWindow", 0, 0, 256, 256, SDL_WindowFlags::SDL_WINDOW_SHOWN|SDL_WindowFlags::SDL_WINDOW_OPENGL);


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
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                sdlKeyEvent(event, device);
                break;
            }

        }
        device.poll();

//        device.dispatch();
        if(device.isPressed(SampleInputActions::SampleDown))
        {
            std::cout << "SampleInputActions::SampleDown " << "pressed" << std::endl;
        }

        SDL_GL_SwapWindow(w);
    }


    return 0;
}
