cmake_minimum_required(VERSION 2.8.11)

project(platformer)

add_subdirectory(module/aether)
add_subdirectory(module/hadron)
add_subdirectory(module/secs)

include("module/aether/cmake/Build.cmake")

file(GLOB_RECURSE ECS "src/ecs/*.cpp" "src/ecs/*.h")
file(GLOB_RECURSE SCREEN "src/screens/*.cpp" "src/screens/*.h")
file(GLOB_RECURSE CORE "src/core/*.cpp" "src/core/*.h" "src/config.h")

function(platformer_target targetname gamesources)

    set(ALLSOURCES ${ECS} ${SCREEN} ${CORE} ${gamesources})
    ADD_AETHER_TARGET(${targetname} "${ALLSOURCES}")

    target_link_libraries(${targetname} hadron secs tmxparser)
    target_include_directories(${targetname} PRIVATE
        "src"
        "gamesrc"
        "module/aether/module/tmxparser/include"
        "module/secs/src/lib"
        "module/hadron/src/lib"
        )

    set_target_properties(${targetname} PROPERTIES LINK_SEARCH_START_STATIC 1)
    set_target_properties(${targetname} PROPERTIES LINK_SEARCH_END_STATIC 1)

endfunction(platformer_target)

file(GLOB_RECURSE CORTEX_SRC
    "gamesrc/cortex/*.cpp"
    "gamesrc/cortex/*.h")

file(GLOB_RECURSE JOJO_SRC
    "gamesrc/jojo/*.cpp"
    "gamesrc/jojo/*.h")

file(GLOB_RECURSE DEMUX_SRC
    "gamesrc/demux/*.cpp"
    "gamesrc/demux/*.h")

platformer_target(cortex "${CORTEX_SRC}")
platformer_target(jojo "${JOJO_SRC}")
#platformer_target(demux "${DEMUX_SRC}")

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
