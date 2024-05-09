cmake_minimum_required(VERSION 3.14)

project(LowLatencyProject)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND LIBS pthread)
add_executable(thread_affinity_example thread_affinity_example.cpp)
target_link_libraries(thread_affinity_example PUBLIC ${LIBS})