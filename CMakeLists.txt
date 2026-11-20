cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(CUtilities
        VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_COMPILER_LAUNCHER
    ${PROJECT_SOURCE_DIR}/Scripts/git-compiler.sh)

set(BASE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/BuildProducts")

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

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

install(TARGETS CUtilities
        EXPORT CUtilitiesTargets)

install(EXPORT CUtilitiesTargets
        FILE CUtilitiesTargets.cmake
        NAMESPACE CUtilities::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CUtilities)

configure_package_config_file(
  cmake/CUtilitiesConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/CUtilitiesTargets.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CUtilities
)

write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/CUtilitiesConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
)

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/CUtilitiesTargets.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/CUtilitiesConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CUtilities
)