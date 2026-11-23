cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(CUtilities_MiniUtilities)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/../src/include/CVersion)
include_directories(${PROJECT_SOURCE_DIR}/../src/include/MiniUtilities)


file(GLOB sourcesPath ${PROJECT_SOURCE_DIR}/../src/source/MiniUtilities/*.cpp)
file(GLOB headersPath ${PROJECT_SOURCE_DIR}/../src/include/MiniUtilities/*.h)

add_library(MiniUtilities STATIC ${sourcesPath} ${headersPath})

target_include_directories(MiniUtilities PUBLIC
                           $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/../src/include/MiniUtilities>
                           $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_link_libraries(MiniUtilities PRIVATE CVersion)

install(TARGETS MiniUtilities
        EXPORT CUtilitiesTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(
    DIRECTORY ${PROJECT_SOURCE_DIR}/../src/include/MiniUtilities/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)