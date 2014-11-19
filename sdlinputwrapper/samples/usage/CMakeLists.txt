PROJECT(sdlinputwrapper-sample-usage)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
aux_source_directory(. SDLINPUTWRAPPER_SAMPLES_SRC_LIST)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)

MESSAGE(${SDLIW_INCLUDES})

INCLUDE_DIRECTORIES(
    ${SDL2_INCLUDE_DIRS}
    ${SDLIW_INCLUDES}
)


add_executable(${PROJECT_NAME} ${SDLINPUTWRAPPER_SAMPLES_SRC_LIST})
target_link_libraries(${PROJECT_NAME}
    ${GTEST_LIBRARIES}
    ${SDL2_LIBRARIES}
    sdlinputwrapper
)

