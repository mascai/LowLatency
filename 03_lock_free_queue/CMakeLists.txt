cmake_minimum_required(VERSION 3.14)

project(LockFreeQueueProject)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)
set(CMAKE_VERBOSE_MAKEFILE ON)

add_executable(lock_free_queue_example lock_free_queue.cpp)
