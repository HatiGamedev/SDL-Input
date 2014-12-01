#include <gtest/gtest.h>
#include "../sdlinputwrapper.h"
#include "inputaction.h"
#include "oracle_inputdevice.h"


enum EInputContext
{
    ModShiftContext
};

TEST(InputDevice, Defaults)
{
    sdli::Interface device;
    ASSERT_EQ(false, device.isPressed(EInputAction::Down));
    ASSERT_EQ(false, device.isDown(EInputAction::Down));
    ASSERT_EQ(false, device.isReleased(EInputAction::Down));
    ASSERT_EQ(true, device.isUp(EInputAction::Down));
}

enum EEventTestAxis
{
    MoveHorizontal
};

enum EEventTestButton
{
    Action_A,
    Action_B
};

TEST(InputDevice, EventTest)
{
    InputTestOracle testOracle;

    sdli::Processor processor{1};
    sdli::Context* ctx = processor.createContext(0);

    ctx->mapAxis(SDL_SCANCODE_A, SDL_SCANCODE_D, EEventTestAxis::MoveHorizontal);
    ctx->mapButton(SDL_SCANCODE_J, EEventTestButton::Action_A);
    ctx->mapButton(SDL_SCANCODE_K, EEventTestButton::Action_B);


    auto& device = processor.getKeyboard();
    device.pushContext(ctx);

    float range = device.getRange(EEventTestAxis::MoveHorizontal);


    ASSERT_EQ(0.0f, range);

    SDL_Event event;
//    testOracle.generateKeyboardEvent(&event);


    processor.handleSdlEvents(event);

    ASSERT_EQ(device.isDown(EEventTestButton::Action_A), false);

}
