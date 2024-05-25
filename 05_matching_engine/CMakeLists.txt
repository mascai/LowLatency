cmake_minimum_required(VERSION 3.14)

project(MathcingEngineProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(common)
add_subdirectory(exchange)

list(APPEND LIBS libcommon)
list(APPEND LIBS libexchange)
list(APPEND LIBS pthread)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/exchange)

add_executable(exchange_main exchange/exchange_main.cpp)
target_link_libraries(exchange_main ${LIBS})