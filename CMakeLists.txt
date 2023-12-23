cmake_minimum_required(VERSION 3.0.0)
project(CPU_SCHEDULING VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Collect all source files in the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/model/*.cpp")

# Collect all header files in the include directory
file(GLOB_RECURSE HEADERS "src/model/header/*.hpp")

add_executable(CPU_SCHEDULING ${SOURCES} ${HEADERS})

target_include_directories(CPU_SCHEDULING PRIVATE "src/model")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
