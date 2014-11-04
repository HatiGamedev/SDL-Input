#include <SDL2/SDL.h>
#include <gtest/gtest.h>
#include "sdl_testenviroment.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new SDL_TestEnviroment);




    return RUN_ALL_TESTS();
}
