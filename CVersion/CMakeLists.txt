cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(CUtilities_CVersion)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB sourcesPath ${PROJECT_SOURCE_DIR}/../src/source/CVersion/*.cpp)
file(GLOB headersPath ${PROJECT_SOURCE_DIR}/../src/include/CVersion/*.h)

add_library(CVersion STATIC ${sourcesPath} ${headersPath})

target_include_directories(CVersion PUBLIC 
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src/include/CVersion>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

install(TARGETS CVersion
        EXPORT CUtilitiesTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/../src/include/CVersion/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)