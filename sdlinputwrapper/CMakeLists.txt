project(sdlinputwrapper)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SDLINPUTWRAPPER_LIB_SRC_LIST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # enable C++11


include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)


add_subdirectory(sdlinputwrapper-tests)


#add_executable(${PROJECT_NAME} ${SDLINPUTWRAPPER_LIB_SRC_LIST})
add_library(${PROJECT_NAME} ${SDLINPUTWRAPPER_LIB_SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    ${SDL2_LIBRARIES}
)

