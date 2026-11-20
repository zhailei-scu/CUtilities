cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(CUtilities_JsonExt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/../src/include/CVersion)
include_directories(${PROJECT_SOURCE_DIR}/../src/include/MiniUtilities)
include_directories(${PROJECT_SOURCE_DIR}/../src/include/JsonExt)

file(GLOB sourcesPath ${PROJECT_SOURCE_DIR}/../src/source/JsonExt/*.cpp)
file(GLOB headersPath ${PROJECT_SOURCE_DIR}/../src/include/JsonExt/*.h)

add_library(JsonExt STATIC ${sourcesPath} ${headersPath})

install(TARGETS JsonExt DESTINATION lib)