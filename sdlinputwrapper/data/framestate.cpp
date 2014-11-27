#include "framestate.h"

namespace sdli {
namespace states {
enum ActionStates
{
    Up=1,
    Down=1<<1,
    Pressed=1<<2,
    Released=1<<3
};
} // data
} // sdli

namespace sdli {
namespace data {

void pushUp(ActionState& state) 
{
    state.state |= sdli::states::ActionStates::Up;
}

void pushDown(ActionState& state) 
{
    state.state |= sdli::states::ActionStates::Down;
}

void pushPressed(ActionState& state) 
{
    state.state |= sdli::states::ActionStates::Pressed;
}

void pushReleased(ActionState& state) 
{
    state.state |= sdli::states::ActionStates::Released;
}

bool isUp(const ActionState& state)
{
    return state.state & sdli::states::ActionStates::Up;
}

bool isDown(const ActionState& state)
{
    return state.state & sdli::states::ActionStates::Down;
}

bool isReleased(const ActionState& state)
{
    return state.state & sdli::states::ActionStates::Released;
}

bool isPressed(const ActionState& state)
{
    return state.state & sdli::states::ActionStates::Pressed;
}

} // data
} // sdli

