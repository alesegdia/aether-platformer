cmake_minimum_required(VERSION 2.8.11)

project(platformerjam)


add_subdirectory(module/aether)
add_subdirectory(module/hadron)
add_subdirectory(module/secs)

include("module/aether/cmake/Build.cmake")

file(GLOB_RECURSE GAMESOURCES "src/*.cpp" "src/*.h")
ADD_AETHER_TARGET(platformerjam "${GAMESOURCES}")

target_link_libraries(platformerjam hadron)
target_include_directories(platformerjam PUBLIC "module/hadron/src/lib")

target_link_libraries(platformerjam secs)
target_include_directories(platformerjam PUBLIC "module/secs/src/lib")


target_include_directories(platformerjam PUBLIC "module/aether/module/tmxparser/include")
set_target_properties(platformerjam PROPERTIES LINK_SEARCH_START_STATIC 1)
set_target_properties(platformerjam PROPERTIES LINK_SEARCH_END_STATIC 1)

set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
