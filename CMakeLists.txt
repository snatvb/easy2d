cmake_minimum_required(VERSION 3.16)

set(ENGINE_NAME easy2d)

add_library(${ENGINE_NAME} STATIC
    src/${ENGINE_NAME}/Core/Engine.cpp

    includes/${ENGINE_NAME}/Core/Engine.hpp
)

target_include_directories(${ENGINE_NAME} PUBLIC includes)
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)
