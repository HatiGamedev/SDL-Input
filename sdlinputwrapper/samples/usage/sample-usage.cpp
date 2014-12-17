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
    auto& pad = inputproc->getGamecontroller(0);
//    auto& pad = inputproc->getGamecontroller(0);

    SDL_Window* w = SDL_CreateWindow("SampleWindow", 0, 0, 800, 600, SDL_WindowFlags::SDL_WINDOW_SHOWN|SDL_WindowFlags::SDL_WINDOW_OPENGL);

    auto sdl_glContext = SDL_GL_CreateContext(w);


    auto ctx = inputproc->createContext(SampleContext::Game);
    auto climb = inputproc->createContext(SampleContext::GameMod);
    /* [BEG] Bind Axes */
    ctx->mapAxis(SDL_SCANCODE_LEFT, SDL_SCANCODE_RIGHT, SampleInputAxis::Horizontal);
    ctx->mapAxis(SDL_SCANCODE_A, SDL_SCANCODE_D, SampleInputAxis::Horizontal);
    ctx->mapAxis(SDL_SCANCODE_W, SDL_SCANCODE_S, SampleInputAxis::Vertical);

    ctx->mapAxis(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT, SampleInputAxis::Horizontal);
    ctx->mapAxis(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP, SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN, SampleInputAxis::Vertical);
    ctx->mapAxis(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX, SampleInputAxis::Horizontal);
    ctx->mapAxis(SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY, SampleInputAxis::Vertical);
    /* [END] Bind Axes */


    /* [BEG] Bind Buttons */
    ctx->mapButton(SDL_SCANCODE_E, SampleInputActions::Shoot);
    ctx->mapButton(SDL_SCANCODE_F, SampleInputActions::CHANGE_CTX);

    ctx->mapButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_A, SampleInputActions::Shoot);
    ctx->mapButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B, SampleInputActions::CHANGE_CTX);

    /* [END] Bind Buttons */

    ctx->addCallback(sdli::CallType::OnPress, SampleInputActions::CHANGE_CTX, [=,&keyboard, &pad](){
        keyboard.pushContext(climb);
        pad.pushContext(climb);
    });


    climb->mapButton(SDL_SCANCODE_F, SampleInputActions::CHANGE_CTX);
    climb->mapButton(SDL_GameControllerButton::SDL_CONTROLLER_BUTTON_B, SampleInputActions::CHANGE_CTX);
    climb->addCallback(sdli::CallType::OnRelease, SampleInputActions::CHANGE_CTX, [=,&keyboard, &pad](){
        keyboard.popContext();
        pad.popContext();
    });


    keyboard.pushContext(ctx);
    pad.pushContext(ctx);

    /* Sample Data */
    const int trailCount = 100;
    float aspectRatio = 600.0f/800.0f;

    float dx = 0.025f * aspectRatio;
    float dy = 0.025f;
    float color[trailCount][4];
    color[0][0] = 1.0f; color[0][1] = 1.0f; color[0][2] = 1.0f; color[0][3] = 1.0f;

    for(int i=1;i<trailCount;++i)
    {
        color[i][0] = 0.5f + i*(0.5f/trailCount); color[i][1] = 1.0f; color[i][2] = 1.0f; color[i][3] = 1.0f - i*(1.0f/trailCount);
    }

    struct Test {
        float   x{0.0f},
                y{0.0f};
    } player[trailCount];
    float add = -0.01f;


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

        for(int i=trailCount-1;i>0;--i)
        {
            player[i].x = player[i-1].x; player[i].y = player[i-1].y;

        }



        float movDir[2];
        movDir[0] = pad.getAxis(SampleInputAxis::Horizontal) + keyboard.getAxis(SampleInputAxis::Horizontal);
        movDir[1] = pad.getAxis(SampleInputAxis::Vertical) + keyboard.getAxis(SampleInputAxis::Vertical);
        float len = sqrtf((movDir[0]*movDir[0])+(movDir[1]*movDir[1]));


        if(!isnanf(len) && len!=0.0f) // Character Control
        {
            player[0].x += (movDir[0] / len) * 0.001f * fabs(movDir[0]);
            player[0].y -= (movDir[1] / len) * 0.001f * fabs(movDir[1]);
        }

        if(pad.isPressed(SampleInputActions::Shoot) || keyboard.isPressed(SampleInputActions::Shoot))
        {
            printf("shoot\n");
            add = 0.001f;
        }
        if(pad.isReleased(SampleInputActions::Shoot) || keyboard.isReleased(SampleInputActions::Shoot))
        {
            printf("unshoot\n");
            add = -0.001f;
        }

        color[0][1] = sdli::clamp(color[0][1] + add, 0.5f, 1.0f);
        color[0][0] = keyboard.isDown(SampleInputActions::CHANGE_CTX)||pad.isDown(SampleInputActions::CHANGE_CTX)?1.0f:0.0f;

        glClearColor(0,0,0,1);
        glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);

        glEnable(GL_BLEND);
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//        int i = 0;
        for(int i=trailCount-1;i>=0;--i)
        {
            glColor4fv((const GLfloat*)color[0]);
            glBegin(GL_TRIANGLE_STRIP);
                glVertex2f(player[i].x - dx, player[i].y - dy);
                glVertex2f(player[i].x + dx, player[i].y - dy);
                glVertex2f(player[i].x - dx, player[i].y + dy);
                glVertex2f(player[i].x + dx, player[i].y + dy);
            glEnd();
        }
        glDisable(GL_BLEND);

        inputproc->swap();
        SDL_GL_SwapWindow(w);
    }

    SDL_GL_DeleteContext(sdl_glContext);
    SDL_DestroyWindow(w);

    return 0;
}
