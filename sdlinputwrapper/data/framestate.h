#ifndef FRAMESTATE_H
#define FRAMESTATE_H

namespace sdli {
namespace data {

struct ActionState
{
    unsigned int state{0};
};

static void pushUp(ActionState& state);
static void pushDown(ActionState& state);
static void pushPressed(ActionState& state);
static void pushReleased(ActionState& state);

static bool isUp(const ActionState& state);
static bool isDown(const ActionState& state);
static bool isReleased(const ActionState& state);
static bool isPressed(const ActionState& state);


} // data
} // sdli


#endif // FRAMESTATE_H
