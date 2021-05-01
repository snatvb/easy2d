cmake_minimum_required(VERSION 3.16)

set(ENGINE_NAME easy2d)
set(DEPS_DIRNAME external)

add_library(${ENGINE_NAME} STATIC
    src/${ENGINE_NAME}/Core/Engine.cpp

    include/${ENGINE_NAME}/Core/Engine.hpp
)

target_include_directories(${ENGINE_NAME} PUBLIC include)
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)

add_subdirectory(${DEPS_DIRNAME}/SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL)
target_link_libraries(${ENGINE_NAME} PRIVATE SDL2main SDL2-static)

add_subdirectory(${DEPS_DIRNAME}/entt ${CMAKE_CURRENT_BINARY_DIR}/entt)
target_link_libraries(${ENGINE_NAME} PUBLIC EnTT)
