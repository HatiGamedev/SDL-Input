#include "processor.h"
#include <assert.h>
#include "inputcontext.h"

namespace sdli
{

Processor::Processor()
{
}


sdli::InputContext* Processor::createContext(const sdli::ContextId& contextId)
{
    /* Only one type of context allowed per processor */
    assert(contextMap.find(contextId) == contextMap.end());

    contextMap.emplace(std::make_pair(contextId, std::unique_ptr<sdli::InputContext>(new sdli::InputContext(contextId))));

    return contextMap[contextId].get();
}

void Processor::handleSdlEvents(const SDL_Event& e)
{
    switch(e.type)
    {
    case SDL_KEYDOWN:
    case SDL_KEYUP:

        break;
    case SDL_CONTROLLERDEVICEADDED:

        break;
    case SDL_CONTROLLERDEVICEREMOVED:

        break;
    }
}

















} // sdli
