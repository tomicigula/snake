cmake_minimum_required(VERSION 3.21)
project(snake LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(snake src/main.cpp src/Engine.cpp headers/Engine.h src/draw.cpp src/input.cpp src/Snake.cpp headers/Snake.h src/update.cpp src/apple.cpp headers/apple.h src/wall.cpp headers/wall.h)
target_link_libraries(snake PRIVATE sfml-graphics)
target_compile_features(snake PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET snake POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:snake> $<TARGET_FILE_DIR:snake> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS snake)
