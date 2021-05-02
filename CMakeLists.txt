cmake_minimum_required(VERSION 3.20)

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(ENGINE_NAME easy2d)
project(${ENGINE_NAME})
# temporarly disable JPG support
set(SUPPORT_JPG OFF CACHE BOOL "" FORCE)
set(PNG_TESTS OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(HAVE_LIBC ON CACHE BOOL "" FORCE)
option(ENGINE_RES_OUTPUT $<TARGET_FILE_DIR:${RUNTIME_OUTPUT_DIRECTORY}>)


set(DEPS_DIRNAME external)

add_library(${ENGINE_NAME} STATIC
    src/${ENGINE_NAME}/Core/Engine.cpp

    include/${ENGINE_NAME}/Core/Engine.hpp
)

target_include_directories(${ENGINE_NAME} PUBLIC include)
target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)

add_subdirectory(${DEPS_DIRNAME}/SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL2)
add_subdirectory(${DEPS_DIRNAME}/SDL_image ${CMAKE_CURRENT_BINARY_DIR}/SDL2_image)
target_link_libraries(${ENGINE_NAME} PRIVATE SDL2::SDL2-static SDL2::SDL2main SDL2_image)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(${DEPS_DIRNAME}/entt ${CMAKE_CURRENT_BINARY_DIR}/entt)
target_link_libraries(${ENGINE_NAME} PUBLIC EnTT)

add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_CURRENT_SOURCE_DIR}/easy2d ${ENGINE_RES_OUTPUT}/easy2d)