#ifndef SDLI_DEFINITIONS_H
#define SDLI_DEFINITIONS_H

#include <vector>
#include <functional>

namespace sdli {
using InputAction = unsigned int;
using InputAxis = unsigned int;
using ContextId = unsigned int;

const InputAction INVALID_INPUT_ACTION = -1;
const InputAction INVALID_INPUT_AXIS = -1;

enum class CallType
{
    isDown,
    isUp,
    OnRelease,
    OnPress,
    Analog_GT,
    Analog_LT
};

struct LogicDigitalData
{
    bool currentStatus{false};
    bool previousStatus{false};
};

struct LogicAnalogData
{
    float currentStatus{0.0f};
};


enum class InputType
{
    Keyboard,
    Gamecontroller
};

// Forward declarations
class Processor;
class Context;
class Interface;
class Device;

using Callback = std::function<void()>;
using CallList = std::vector<Callback>;


namespace {
    const bool IS_DOWN_UNDEFINED = false;
    const bool IS_UP_UNDEFINED = true;
    const bool IS_RELEASED_UNDEFINED = false;
    const bool IS_PRESSED_UNDEFINED = false;
    const float RANGE_UNDEFINED = 0.0f;
}

} // sdli



#endif // SDLI_DEFINITIONS_H
