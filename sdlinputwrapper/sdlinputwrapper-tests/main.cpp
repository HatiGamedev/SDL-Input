#include <SDL2/SDL.h>
#include <gtest/gtest.h>

#include "../sdlinputwrapper.h"
#include "sdl_testenviroment.h"


//GTEST_ASSERT_EQ(false, device.isPressed(InputAction::Up));


TEST(InputDevice, isPressed)
{
    InputDevice device;
    device.map(SDL_SCANCODE_W, InputAction::Up);
    ASSERT_EQ(false, device.isPressed(InputAction::Up));

    device.push(InputType::Keyboard, SDL_SCANCODE_W, 1);
    device.dispatch();
    ASSERT_EQ(true, device.isPressed(InputAction::Up));
}

TEST(InputDevice, Unmapped)
{
    InputDevice device;
    ASSERT_EQ(false, device.isPressed(InputAction::Down));
}


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new SDL_TestEnviroment);

//    InputDevice device;
//    device.map(SDL_SCANCODE_W, InputAction::Up);

    return RUN_ALL_TESTS();
}



