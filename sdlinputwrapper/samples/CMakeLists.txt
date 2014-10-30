PROJECT(sdlinputwrapper-samples)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
aux_source_directory(. SDLINPUTWRAPPER_SAMPLES_SRC_LIST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # enable C++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") # enable C++14

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

set(SDLI_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../..)

INCLUDE_DIRECTORIES(
    ${SDL2_INCLUDE_DIRS}
    ${SDLI_INCLUDE_DIR}
)


add_executable(${PROJECT_NAME} ${SDLINPUTWRAPPER_SAMPLES_SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES}
    ${SDL2_LIBRARIES}
    sdlinputwrapper
)

