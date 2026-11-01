cmake_minimum_required(VERSION 3.10)
project(cpp_player)

set(SFML_DIR "путь до SFMl")

find_package(SFML COMPONENTS Audio System REQUIRED)

add_executable(cpp_player main.cpp)
target_link_libraries(cpp_player SFML::Audio SFML::System)
# хз нафига вам этот плеер, но если захотите собрать это говно, то вот файл CMake
