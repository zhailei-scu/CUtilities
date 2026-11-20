cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(CUtilities)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_COMPILER_LAUNCHER
    ${PROJECT_SOURCE_DIR}/Scripts/git-compiler.sh)

set(BASE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/BuildProducts")

foreach(_conftype ${CMAKE_CONFIGURATION_TYPES})
  string(TOUPPER ${_conftype} _conftype_uppercase)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_conftype_uppercase}
    "${BASE_OUTPUT_DIRECTORY}/${_conftype}/${CMAKE_INSTALL_BINDIR}"
    )
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${_conftype_uppercase}
    "${BASE_OUTPUT_DIRECTORY}/${_conftype}/${CMAKE_INSTALL_LIBDIR}"
    )
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${_conftype_uppercase}
    "${BASE_OUTPUT_DIRECTORY}/${_conftype}/${CMAKE_INSTALL_LIBDIR}"
    )
endforeach()

set(CUTILLIBS CVersion MiniUtilities JsonExt)

foreach(CUTILLIBNAME ${CUTILLIBS})
  add_subdirectory(${PROJECT_SOURCE_DIR}/${CUTILLIBNAME})
endforeach()

add_library(CUtilities INTERFACE)

foreach(CUTILLIBNAME ${CUTILLIBS})
  add_library(CUtilities::${CUTILLIBNAME} ALIAS ${CUTILLIBNAME})
endforeach()

add_library(CUtilities::CUtilities ALIAS CUtilities)

target_link_libraries(CUtilities INTERFACE ${CUTILLIBS})