#include "processor.h"
#include <assert.h>
#include "inputcontext.h"
#include "inputdevice.h"

namespace sdli
{

Processor::Processor()
    : keyboard(new sdli::InputDevice)
{
}


sdli::InputContext* Processor::createContext(const sdli::ContextId& contextId)
{
    /* Only one type of context allowed per processor */
    assert(contextMap.find(contextId) == contextMap.end());

    contextMap.emplace(std::make_pair(contextId, std::unique_ptr<sdli::InputContext>(new sdli::InputContext(contextId))));

    return contextMap[contextId].get();
}

InputDevice* Processor::getDevice(InputType type)
{
    switch(type)
    {
    case sdli::InputType::Keyboard:
        return this->keyboard.get();
        break;
    case sdli::InputType::Gamecontroller:
        assert(false);
        return nullptr;
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

        break;
    case SDL_CONTROLLERDEVICEREMOVED:

        break;
    }
}

















} // sdli
