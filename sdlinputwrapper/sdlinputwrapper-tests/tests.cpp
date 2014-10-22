#include <SDL2/SDL.h>
#include <gtest/gtest.h>

#include "../sdlinputwrapper.h"
#include "sdl_testenviroment.h"
#include "inputaction.h"
#include <memory>
//GTEST_ASSERT_EQ(false, device.isPressed(InputAction::Up));

enum EInputContext
{
    isPressedContext
};

TEST(InputDevice, defaults)
{
    sdli::InputDevice device;
    std::unique_ptr<sdli::InputContext> ctx(new sdli::InputContext(EInputContext::isPressedContext));

}

TEST(InputDevice, UnmappedDefaults)
{
    sdli::InputDevice device;
    ASSERT_EQ(false, device.isPressed(EInputAction::Down));
    ASSERT_EQ(false, device.isDown(EInputAction::Down));
    ASSERT_EQ(false, device.isReleased(EInputAction::Down));
    ASSERT_EQ(true, device.isUp(EInputAction::Down));
}



int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new SDL_TestEnviroment);




    return RUN_ALL_TESTS();
}



