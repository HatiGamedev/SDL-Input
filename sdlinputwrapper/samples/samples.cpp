#include <iostream>
#include <SDL2/SDL.h>
#include <cassert>

#include <sdlinputwrapper/sdlinputwrapper.h>
#include <memory>

enum SampleInputActions
{
    SampleDown,
    Shoot
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

    auto ctx1 = std::unique_ptr<sdli::InputContext>(new sdli::InputContext(SampleContext::Menu));
    auto ctx2 = std::unique_ptr<sdli::InputContext>(new sdli::InputContext(SampleContext::Game));

    ctx1->mapDigital(SDL_SCANCODE_S, SampleInputActions::SampleDown);
    ctx2->mapDigital(SDL_SCANCODE_S, SampleInputActions::Shoot);

    ctx1->addCallback(SampleInputActions::SampleDown, sdli::CallType::OnPress, [=]()
    {
        std::cout << "Hello world" << std::endl;
    });

    SDL_Window* w = SDL_CreateWindow("SampleWindow", 0, 0, 256, 256, SDL_WindowFlags::SDL_WINDOW_SHOWN|SDL_WindowFlags::SDL_WINDOW_OPENGL);

    auto sdl_glContext = SDL_GL_CreateContext(w);

    device.pushContext(ctx1.get());

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

        device.dispatch();
        if(device.isPressed(SampleInputActions::SampleDown))
        {
            std::cout << "SampleInputActions::SampleDown " << "pressed" << std::endl;
        }

        SDL_GL_SwapWindow(w);
    }

    SDL_GL_DeleteContext(sdl_glContext);
    SDL_DestroyWindow(w);
    return 0;
}
