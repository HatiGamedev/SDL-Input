#include <iostream>
#include <SDL2/SDL.h>
#include <cassert>

#include <sdlinputwrapper/sdlinputwrapper.h>
#include <memory>

#include "device.h"
#include <sdlinputwrapper/callback.h>

#include <GL/gl.h>

enum SampleInputActions
{
    Shoot,
    CHANGE_CTX,

    GAME_QUIT
};

enum SampleInputAxis
{
    Vertical,
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

struct Sprite
{
};

#include "stub.h"

int main(int argc, char** argv)
{
    std::setbuf(stdout, NULL); // used to always flush std::cout

    auto sdl_init_status = SDL_Init(SDL_INIT_EVENTS
                                     | SDL_INIT_JOYSTICK
                                     | SDL_INIT_GAMECONTROLLER);
    assert(sdl_init_status==0);

    bool sampleQuit = false;

    auto inputproc = std::unique_ptr<sdli::Processor>(new sdli::Processor(SampleContext::MAX_COUNT));

    auto& keyboard = inputproc->getKeyboard();
//    auto& pad = inputproc->getGamecontroller(0);

    SDL_Window* w = SDL_CreateWindow("SampleWindow", 0, 0, 800, 600, SDL_WindowFlags::SDL_WINDOW_SHOWN|SDL_WindowFlags::SDL_WINDOW_OPENGL);

    auto sdl_glContext = SDL_GL_CreateContext(w);

    float aspectRatio = 600.0f/800.0f;

    float dx = 0.025f * aspectRatio;
    float dy = 0.025f;
    float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};

    auto ctx = inputproc->createContext(SampleContext::Game);
    auto climb = inputproc->createContext(SampleContext::GameMod);

    ctx->mapAxis(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SampleInputAxis::Horizontal);
    ctx->mapAxis(SDL_SCANCODE_A, SDL_SCANCODE_D, SampleInputAxis::Horizontal);
    ctx->mapAxis(SDL_SCANCODE_S, SDL_SCANCODE_W, SampleInputAxis::Vertical);

    ctx->mapButton(SDL_SCANCODE_E, SampleInputActions::Shoot);
    ctx->mapButton(SDL_SCANCODE_F1, SampleInputActions::CHANGE_CTX);

    ctx->addCallback(sdli::CallType::OnPress, SampleInputActions::CHANGE_CTX, [=,&keyboard](){
        keyboard.pushContext(climb);
    });


    climb->mapButton(SDL_SCANCODE_F1, SampleInputActions::CHANGE_CTX);
    climb->addCallback(sdli::CallType::OnRelease, SampleInputActions::CHANGE_CTX, [=,&keyboard](){
        keyboard.popContext();
    });


    keyboard.pushContext(ctx);
    struct Test {
        float   x{0.0f},
                y{0.0f};
    } player;


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

        inputproc->poll();
        inputproc->dispatch();

        player.x += keyboard.getAxis(SampleInputAxis::Horizontal) * 0.001f;
        player.y += keyboard.getAxis(SampleInputAxis::Vertical) * 0.001f;

        if(keyboard.isPressed(SampleInputActions::Shoot))
        {
            color[1] = 0.5f;
        }
        if(keyboard.isReleased(SampleInputActions::Shoot))
        {
            color[1] = 1.0f;
        }

        color[0] = keyboard.isDown(SampleInputActions::CHANGE_CTX)?1.0f:0.0f;

        glClearColor(0,0,0,1);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);


        glColor4fv((const GLfloat*)color);
        glBegin(GL_TRIANGLE_STRIP);
            glVertex2f(player.x - dx, player.y - dy);
            glVertex2f(player.x + dx, player.y - dy);
            glVertex2f(player.x - dx, player.y + dy);
            glVertex2f(player.x + dx, player.y + dy);
        glEnd();

        inputproc->swap();
        SDL_GL_SwapWindow(w);
    }

    SDL_GL_DeleteContext(sdl_glContext);
    SDL_DestroyWindow(w);

    return 0;
}
