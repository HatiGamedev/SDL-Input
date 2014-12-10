PROJECT(sdlinputwrapper-sample-usage)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
aux_source_directory(. SDLINPUTWRAPPER_SAMPLES_SRC_LIST)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(
    ${SDL2_INCLUDE_DIRS}
    ${SDLIW_INCLUDES}
)


pkg_search_module(OpenGL REQUIRED gl)

add_executable(${PROJECT_NAME} ${SDLINPUTWRAPPER_SAMPLES_SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${OpenGL_LIBRARIES}
    sdlinputwrapper
)

