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

target_include_directories(JsonExt PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src/include/JsonExt>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(JsonExt PRIVATE CVersion MiniUtilities)

install(TARGETS JsonExt
        EXPORT CUtilitiesTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/../src/include/JsonExt/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)