cmake_minimum_required(VERSION 3.16)
project(g_caster)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/modules)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
  message(
    FATAL_ERROR
      "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
  )
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_DEBUG_POSTFIX "d")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ROOT_SRC_DIR ${ROOT_DIR}/src)
set(ROOT_TESTS_DIR ${ROOT_DIR}/tests)

set(SHARED_INCLUDES
    ${ROOT_SRC_DIR}
    ${ROOT_TESTS_DIR}
    lib
    include
)

include_directories(${SHARED_INCLUDES})

add_subdirectory(src)

# enable_testing()
# add_subdirectory(tests)
