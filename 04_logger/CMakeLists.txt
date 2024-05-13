cmake_minimum_required(VERSION 3.14)

project(LoggerProject)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER g++)

list(APPEND LIBS pthread)
add_executable(logger_example logger_example.cpp)
target_link_libraries(logger_example ${LIBS})