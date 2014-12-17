project(sdlinputwrapper)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SDLINPUTWRAPPER_LIB_SRC_LIST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # enable C++11

SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
SET_PROPERTY(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${sdlinputwrapper_SOURCE_DIR}/cmake")
FIND_PACKAGE(SDL2 REQUIRED)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIR}
)

#add_subdirectory(util)
SET(SDLINPUTWRAPPER_LIB_SRC_LIST
    ${SDLINPUTWRAPPER_LIB_SRC_LIST}

    # util
    util/array.cpp
    util/indexmap.cpp
    util/linearallocator.cpp

    # data
    data/framestate.cpp
    data/sdli_axis.cpp
)

OPTION(SDLI_Enable_Tests "Compiles sdli gtests" OFF)
OPTION(SDLI_Enable_Samples "Compiles the sdli samples" OFF)

IF(SDLI_Enable_Tests)
    add_subdirectory(sdlinputwrapper-tests)
ENDIF()

IF(SDLI_Enable_Samples)
    add_subdirectory(samples)
ENDIF()

add_library(${PROJECT_NAME} ${SDLINPUTWRAPPER_LIB_SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARY}
)

