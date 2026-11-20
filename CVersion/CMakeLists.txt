cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(LIB_CVersion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB sourcesPath ${PROJECT_SOURCE_DIR}/../src/source/CVersion/*.cpp)
file(GLOB headersPath ${PROJECT_SOURCE_DIR}/../src/include/CVersion/*.h)

add_library(CVersion STATIC ${sourcesPath} ${headersPath})

target_include_directories(CVersion PUBLIC ${PROJECT_SOURCE_DIR}/../src/include/CVersion)

install(TARGETS CVersion DESTINATION lib)