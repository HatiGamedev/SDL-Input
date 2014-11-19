PROJECT(sdlinputwrapper-tests)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
aux_source_directory(. SDLINPUTWRAPPER_TEST_SRC_LIST)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # enable C++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") # enable C++14


FIND_PACKAGE(GTest REQUIRED)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(
    ${GTEST_INCLUDE_DIR}
    ${SDL2_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME} ${SDLINPUTWRAPPER_TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES}
    ${SDL2_LIBRARIES}
    sdlinputwrapper
)

