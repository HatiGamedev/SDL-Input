#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <map>
#include <memory>

#include <SDL2/SDL_events.h>

#include "sdli_definitions.h"
#include "device.h"

namespace sdli {

class Processor
{
    std::map<sdli::ContextId, std::unique_ptr<sdli::Context>> contextMap;

    std::unique_ptr<sdli::Interface> keyboard;
    std::map<Sint32, std::unique_ptr<sdli::Interface>> gamecontrollers;

    sdli::Device keyboardDevice;
    std::vector<sdli::Device> devices;

private:
    void addController(Sint32 controllerId);

public:
    Processor();

    sdli::Context* createContext(const sdli::ContextId& contextId);
    sdli::Device& getDevice(sdli::InputType type);





    void handleSdlEvents(const SDL_Event& e);



};

} // sdli

#endif // PROCESSOR_H
