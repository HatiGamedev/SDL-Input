#ifndef SDLI_DEFINITIONS_H
#define SDLI_DEFINITIONS_H

#include <vector>
#include "callback.h"
#include "stub.h"

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

/**
 * @brief Binary encoding of an interface
 */
enum class InputType
{
    Keyboard            = 1<<0,
    Gamecontroller      = 1<<1,
    Mouse               = 1<<2,

    Keyboard_AND_Mouse          = InputType::Keyboard | InputType::Mouse,
    Keyboard_AND_Gamecontroller = InputType::Keyboard | InputType::Gamecontroller,

    ALL                         = InputType::Gamecontroller | InputType::Keyboard | InputType::Mouse
};

// Forward declarations
class Processor;
class Context;
class Interface;
class KeyboardInterface;
class MouseInterface;
class Device;

using Callback = sdli::util::Lambda<void(void)>;
using CallList = std::vector<Callback>;


namespace {
    const bool IS_DOWN_UNDEFINED = false;
    const bool IS_UP_UNDEFINED = true;
    const bool IS_RELEASED_UNDEFINED = false;
    const bool IS_PRESSED_UNDEFINED = false;
    const float RANGE_UNDEFINED = 0.0f;
}

struct RawInputData
{
    unsigned int rawInput;
    int pollResult;
};

float clamp(float cur, float min, float max);

bool isPressed(const LogicDigitalData& d);
bool isReleased(const LogicDigitalData& d);
bool isDown(const LogicDigitalData& d);
bool isUp(const LogicDigitalData& d);


} // sdli



#endif // SDLI_DEFINITIONS_H
