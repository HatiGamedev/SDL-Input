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
    sdli::Interface device;
    std::unique_ptr<sdli::Context> ctx(new sdli::Context(EInputContext::isPressedContext));

}

TEST(InputDevice, UnmappedDefaults)
{
    sdli::Interface device;
    ASSERT_EQ(false, device.isPressed(EInputAction::Down));
    ASSERT_EQ(false, device.isDown(EInputAction::Down));
    ASSERT_EQ(false, device.isReleased(EInputAction::Down));
    ASSERT_EQ(true, device.isUp(EInputAction::Down));
}

#include "../array.h"
TEST(SDLIBaseArray, Util)
{
    auto array = sdli::util::BaseArray(100);
    array[0] = 1;
    ASSERT_EQ(1, array[0]);
    ASSERT_EQ(1, *array.begin());
}
struct DataType
{
    int idx;
    float value;
    bool flag;
};

TEST(SDLIArray, Util)
{
    unsigned int size = 300000;
    auto array = sdli::util::Array<DataType>(size);
//    ASSERT_EQ(size, array.size());
    array[0].idx = 0;
    array[1].value = 1.0f;
    array[2].flag = false;

    ASSERT_EQ(0, array[0].idx);
    ASSERT_EQ(1.0f, array[1].value);
    ASSERT_EQ(false, array[2].flag);

    for(auto it = array.begin(); it!=array.end(); ++it)
    {
        it->idx = 0;
        it->value = 10.0f;
        it->flag = true;
    }

    for(auto it = array.begin(); it!=array.end(); ++it)
    {
        ASSERT_EQ(0, it->idx);
        ASSERT_EQ(10.0f, it->value);
        ASSERT_EQ(true, it->flag);
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new SDL_TestEnviroment);




    return RUN_ALL_TESTS();
}
