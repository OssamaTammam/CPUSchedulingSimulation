cmake_minimum_required(VERSION 3.0.0)
project(CPU_SCHEDULING VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

file(GLOB SOURCES "./src/*.cpp" "./src/model/*.cpp")
file(GLOB HEADERS "./include/*.hpp" "./include/model/*.hpp")

add_executable(CPU_SCHEDULING ${SOURCES} ${HEADERS})

target_include_directories(CPU_SCHEDULING PUBLIC "./include" "./include/model")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
