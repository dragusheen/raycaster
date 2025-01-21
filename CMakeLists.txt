#  ---- SETUP ---- #
cmake_minimum_required(VERSION 3.16)
project(Raycaster VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#  ---- FIND PACKAGES ---- #
find_package(SFML 2.6.1 REQUIRED COMPONENTS graphics window system audio network)

#  ---- SOURCES ---- #
file(GLOB_RECURSE SOURCES
    "src/main.cpp"
)

#  ---- EXECUTABLE ---- #
add_executable(raycaster ${SOURCES})

#  ---- INCLUDES ---- #
target_include_directories(raycaster PRIVATE
    "src/"
)

#  ---- LINK LIBRARIES ---- #
target_link_libraries(raycaster PRIVATE
    sfml-graphics sfml-window sfml-system sfml-audio sfml-network
)

#  ---- POST BUILD ---- #
add_custom_command(TARGET raycaster POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:raycaster> ${CMAKE_SOURCE_DIR}
)
