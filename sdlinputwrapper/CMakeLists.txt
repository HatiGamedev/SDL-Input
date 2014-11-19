project(sdlinputwrapper)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SDLINPUTWRAPPER_LIB_SRC_LIST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # enable C++11
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") # enable C++14

SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)

#add_subdirectory(util)
SET(SDLINPUTWRAPPER_LIB_SRC_LIST
    ${SDLINPUTWRAPPER_LIB_SRC_LIST}
    util/array.cpp
    util/linearallocator.cpp
)

OPTION(SDLI_Enable_Tests "Compiles sdli gtests" OFF)
OPTION(SDLI_Enable_Samples "Compiles the sdli samples" OFF)

IF(SDLI_Enable_Tests)
    add_subdirectory(sdlinputwrapper-tests)
ENDIF()

IF(SDLI_Enable_Samples)
    add_subdirectory(samples)
ENDIF()

#add_executable(${PROJECT_NAME} ${SDLINPUTWRAPPER_LIB_SRC_LIST})
add_library(${PROJECT_NAME} ${SDLINPUTWRAPPER_LIB_SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
)

