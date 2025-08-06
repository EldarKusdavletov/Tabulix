cmake_minimum_required(VERSION 3.20)
project(tabulix VERSION 0.1.0 LANGUAGES CXX)

# Require C++26
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library option
option(TABULIX_BUILD_SHARED "Build tabulix as a shared library" ON)
option(TABULIX_BUILD_TESTS "Build tabulix tests" ON)
option(TABULIX_BUILD_EXAMPLES "Build tabulix examples" ON)

# Set default build type to Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
file(GLOB_RECURSE TABULIX_SOURCES "src/*.cpp")

# Create library
if(TABULIX_BUILD_SHARED)
    add_library(tabulix SHARED ${TABULIX_SOURCES})
    target_compile_definitions(tabulix PUBLIC TABULIX_SHARED)
    set_target_properties(tabulix PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR})
else()
    add_library(tabulix STATIC ${TABULIX_SOURCES})
endif()

# Installation
include(GNUInstallDirs)
install(TARGETS tabulix
    EXPORT tabulixTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export targets
install(EXPORT tabulixTargets
    FILE tabulixTargets.cmake
    NAMESPACE tabulix::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tabulix)

# Generate and install the package configuration file
include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/tabulixConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/tabulixConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tabulix)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/tabulixConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/tabulixConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/tabulixConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/tabulix)

# Add subdirectories
if(TABULIX_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(TABULIX_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
