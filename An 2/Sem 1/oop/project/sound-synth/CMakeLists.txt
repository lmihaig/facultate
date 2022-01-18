cmake_minimum_required(VERSION 3.15)
project(sound-synth VERSION 0.1.0)

if(MSVC)
else()
  if(WINDOWS)
    SET(CMAKE_COMPILER_IS_MINGW TRUE)
    SET(MINGW TRUE)
    SET(CMAKE_COMPILER_IS_GNUCC TRUE)
    SET(USE_GCC TRUE)
    SET(SDL_DIRECTX FALSE)
  endif()
endif()

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/artifacts)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/artifacts)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/artifacts)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/artifacts)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/artifacts)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/artifacts)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/artifacts)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/artifacts)

# Find and update submodules
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
                message(STATUS "Submodule update")
                execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                                RESULT_VARIABLE GIT_SUBMOD_RESULT)
                if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                        message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}")
                endif()
        endif()
endif()


# Add source files
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(${PROJECT_NAME} main.cpp ${SRC_FILES})

if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /permissive-)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -g)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        target_compile_options(${PROJECT_NAME} PRIVATE -stdlib=libstdc++)
    endif()
endif ()


# Add external libraries and header files
add_subdirectory(external/SDL2)
target_include_directories(${PROJECT_NAME}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include 
        PUBLIC external/SDL2/include
        )
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)