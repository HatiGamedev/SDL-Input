#include "device.h"
#include "interface.h"
#include "context.h"
#include "keyboardinterface.h"
#include <iostream>

#define _DEVICE_GUARD_(x, defVal) if(!(x)) { return defVal;}

namespace sdli {


void Device::setInterface(Interface* interface)
{
    this->interface = interface;
}

void Device::setKeyboard(KeyboardInterface* keyboard)
{
    keyboardInterface = keyboard;
}

void Device::setMouseInterface(MouseInterface* mouse)
{
    mouseInterface = mouse;
}

Device::Device()
{
}

void Device::pushContext(Context* ctx)
{
    contextStack_.push(ctx);
}

Context* Device::currentContext()
{
    if(contextStack_.empty())
    {
        return nullptr;
    }

    return contextStack_.top();
}

Context* Device::popContext()
{
    if(contextStack_.empty())
    {
        return nullptr;
    }

    auto ctx = contextStack_.top();
    contextStack_.pop();
    return ctx;
}

void Device::poll()
{
    _DEVICE_GUARD_(!contextStack_.empty(), ;);
    if(keyboardInterface)
    {
        keyboardInterface->poll(*contextStack_.top());
    }
    _DEVICE_GUARD_(interface, ;);
    interface->poll(*contextStack_.top());
}

void Device::dispatch()
{
    _DEVICE_GUARD_(!contextStack_.empty(), ;);
    if(keyboardInterface)
    {
        keyboardInterface->dispatch(*contextStack_.top());
    }
    _DEVICE_GUARD_(interface, ;);
    interface->dispatch(*contextStack_.top());
}

float Device::getAxis(InputAxis axis)
{
    ///TODO: how to handle mouse and different normalized axes
    if(keyboardInterface)
    {
        return keyboardInterface->getRange(axis);
    }
    _DEVICE_GUARD_(interface, ::sdli::RANGE_UNDEFINED);
    return interface->getRange(axis);
}

bool Device::isPressed(InputAction action)
{
    return (keyboardInterface?keyboardInterface->isPressed(action): ::sdli::IS_PRESSED_UNDEFINED)
           || (interface ? interface->isPressed(action) : ::sdli::IS_PRESSED_UNDEFINED);
}

bool Device::isReleased(InputAction action)
{
    return (keyboardInterface?keyboardInterface->isReleased(action): ::sdli::IS_RELEASED_UNDEFINED)
           || (interface ? interface->isReleased(action) : ::sdli::IS_RELEASED_UNDEFINED);
}

bool Device::isDown(InputAction action)
{
    return (keyboardInterface?keyboardInterface->isDown(action): ::sdli::IS_DOWN_UNDEFINED)
           || (interface ? interface->isDown(action) : ::sdli::IS_DOWN_UNDEFINED);
}

bool Device::isUp(InputAction action)
{
    return (keyboardInterface?keyboardInterface->isUp(action): ::sdli::IS_UP_UNDEFINED)
           || (interface ? interface->isUp(action) : ::sdli::IS_UP_UNDEFINED);
}

void Device::swap()
{
    if(keyboardInterface)
    {
        keyboardInterface->swap();
    }
    _DEVICE_GUARD_(interface,;);
    interface->swap();
}

} // sdli
