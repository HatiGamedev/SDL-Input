#include <SDL2/SDL.h>
#include <gtest/gtest.h>

#include "../sdlinputwrapper.h"
#include "sdl_testenviroment.h"
#include "inputaction.h"

//GTEST_ASSERT_EQ(false, device.isPressed(InputAction::Up));


TEST(InputDevice, isPressed)
{
    sdli::InputDevice device;
    device.map(SDL_SCANCODE_W, InputAction::Up);
    ASSERT_EQ(false, device.isPressed(InputAction::Up));

    device.push(sdli::InputType::Keyboard, SDL_SCANCODE_W, 1);
    device.dispatch();
    ASSERT_EQ(true, device.isPressed(InputAction::Up));
}

TEST(InputDevice, Unmapped)
{
    sdli::InputDevice device;
    ASSERT_EQ(false, device.isPressed(InputAction::Down));
    ASSERT_EQ(false, device.isDown(InputAction::Down));

    ASSERT_EQ(true, device.isReleased(InputAction::Down));
    ASSERT_EQ(true, device.isReleased(InputAction::Down));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new SDL_TestEnviroment);



    return RUN_ALL_TESTS();
}



