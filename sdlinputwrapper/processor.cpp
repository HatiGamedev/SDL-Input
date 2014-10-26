#include "processor.h"
#include <assert.h>
#include "context.h"
#include "interface.h"
#include <iostream>


namespace sdli
{

void Processor::addController(Sint32 controllerId)
{
    auto controller = SDL_GameControllerOpen(controllerId);



    gamecontrollers.emplace(std::make_pair(controllerId, std::unique_ptr<sdli::Interface>(new sdli::Interface)));
}

Processor::Processor()
    : keyboard(new sdli::Interface),
      keyboardDevice(keyboard.get())
{
}


sdli::Context* Processor::createContext(const sdli::ContextId& contextId)
{
    /* Only one type of context allowed per processor */
    assert(contextMap.find(contextId) == contextMap.end());

    contextMap.emplace(std::make_pair(contextId, std::unique_ptr<sdli::Context>(new sdli::Context(contextId))));

    return contextMap[contextId].get();
}

sdli::Device& Processor::getDevice(InputType type)
{
    switch(type)
    {
    case sdli::InputType::Keyboard:
        return keyboardDevice;
        break;
    case sdli::InputType::Gamecontroller:
        assert(false);
        break;
    }
}

void Processor::handleSdlEvents(const SDL_Event& e)
{
    switch(e.type)
    {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        keyboard->push(InputType::Keyboard, e.key.keysym.scancode, e.key.state);
        break;
    case SDL_CONTROLLERDEVICEADDED:
        std::cout << "Controller added " << e.cdevice.type << ":" << e.cdevice.which << std::endl;
        break;
    case SDL_CONTROLLERDEVICEREMOVED:
        std::cout << "Controller removed " << e.cdevice.type << ":" << e.cdevice.which << std::endl;
        break;
    }
}

















} // sdli
