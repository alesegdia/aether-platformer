cmake_minimum_required(VERSION 2.8.11)

project(platformerjam)

add_subdirectory(module/aether)
add_subdirectory(module/hadron)

include("module/aether/cmake/Build.cmake")

file(GLOB_RECURSE GAMESOURCES "src/*.cpp" "src/*.h")
ADD_AETHER_TARGET(platformerjam "${GAMESOURCES}")

target_link_libraries(platformerjam hadron)
target_include_directories(platformerjam PUBLIC "module/hadron/src/lib")


