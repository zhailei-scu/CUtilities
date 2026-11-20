cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(LIB_MiniUtilities)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/../src/include/MiniUtilities)


file(GLOB sourcesPath ${PROJECT_SOURCE_DIR}/../src/source/MiniUtilities/*.cpp)
file(GLOB headersPath ${PROJECT_SOURCE_DIR}/../src/include/MiniUtilities/*.h)

add_library(MiniUtilities STATIC ${sourcesPath} ${headersPath})

install(TARGETS MiniUtilities DESTINATION lib)