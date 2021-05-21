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

file(GLOB CORE_SRC
    src/${ENGINE_NAME}/Core/*.cpp
    include/${ENGINE_NAME}/Core/*.hpp
)

file(GLOB DEBUG_SRC
    src/${ENGINE_NAME}/Debug/*.cpp
    include/${ENGINE_NAME}/Debug/*.hpp
)

file(GLOB RENDERER_SRC
    src/${ENGINE_NAME}/Renderer/*.cpp
    include/${ENGINE_NAME}/Renderer/*.hpp
)

file(GLOB COMPONENTS_SRC
    src/${ENGINE_NAME}/Components/*.cpp
    include/${ENGINE_NAME}/Components/*.hpp
)

file(GLOB OWN_LIB_SRC
    src/${ENGINE_NAME}/lib/*.cpp
    include/${ENGINE_NAME}/lib/*.hpp
)

file(GLOB EXTERNALS_SRC
    ${DEPS_DIRNAME}/sole/sole.cpp
    ${DEPS_DIRNAME}/sole/sole.hpp
)

add_library(${ENGINE_NAME} STATIC
    ${EXTERNALS_SRC}
    ${COMPONENTS_SRC}
    ${CORE_SRC}
    ${RENDERER_SRC}
    ${DEBUG_SRC}
    ${OWN_LIB_SRC}
)

target_include_directories(${ENGINE_NAME} PUBLIC include)
target_include_directories(${ENGINE_NAME} PUBLIC ${DEPS_DIRNAME}/sole)

add_subdirectory(${DEPS_DIRNAME}/SDL ${CMAKE_CURRENT_BINARY_DIR}/SDL2)
add_subdirectory(${DEPS_DIRNAME}/SDL_image ${CMAKE_CURRENT_BINARY_DIR}/SDL2_image)
target_link_libraries(${ENGINE_NAME} PRIVATE SDL2::SDL2-static SDL2::SDL2main SDL2_image)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(${DEPS_DIRNAME}/entt ${CMAKE_CURRENT_BINARY_DIR}/entt)
target_link_libraries(${ENGINE_NAME} PUBLIC EnTT)

add_subdirectory(${DEPS_DIRNAME}/spdlog ${CMAKE_CURRENT_BINARY_DIR}/spdlog)
target_include_directories(${ENGINE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/${DEPS_DIRNAME}/spdlog/include)
target_link_libraries(${ENGINE_NAME} PRIVATE spdlog)

target_compile_features(${ENGINE_NAME} PUBLIC cxx_std_17)

add_custom_command(TARGET ${ENGINE_NAME} POST_BUILD
					COMMAND ${CMAKE_COMMAND} -E copy_directory
					${CMAKE_CURRENT_SOURCE_DIR}/easy2d ${ENGINE_RES_OUTPUT}/easy2d)