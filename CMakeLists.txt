cmake_minimum_required(VERSION 3.14)
project(BetterIntegralConstant VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set default build type if not specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)

    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
endif()

# === Options ===
option(BIC_BUILD_DEMO "Build demo executable" OFF)
option(BIC_BUILD_DOC  "Build Doxygen documentation" OFF)

# === Dependencies ===
find_package(fmt REQUIRED)

# === Doxygen ===
if(BIC_BUILD_DOC)
    find_package(Doxygen REQUIRED dot)

    # Set default values for Doxyfile
    set(DOXYGEN_PROJECT_NAME "Lightweight Numerical Optimization Tools (BIC)")
    set(DOXYGEN_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
    set(DOXYGEN_OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/doc")

    set(DOXYGEN_FILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in ${DOXYGEN_FILE} @ONLY)

    add_custom_target(doc
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()

# === Demo subdir ===
if(BIC_BUILD_DEMO)
    add_subdirectory(demo)
endif()

# === Library Target ===

add_library(BIC INTERFACE)

target_include_directories(BIC
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(BIC INTERFACE fmt::fmt)

target_compile_options(BIC INTERFACE
    $<$<COMPILE_LANGUAGE:CXX>:${BIC_COMPILE_WARNINGS}>
)

if(BIC_NATIVE_OPT)
    message(STATUS "Enabling native CPU optimizations (-march=native -mtune=native)")
    target_compile_options(BIC INTERFACE -march=native -mtune=native)
endif()

# === Installation ===
include(GNUInstallDirs)

install(DIRECTORY include/BIC DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS BIC
    EXPORT BICTargets
)

install(EXPORT BICTargets
    FILE BICTargets.cmake
    NAMESPACE BIC::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BIC
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/BICConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/BICConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/BICConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BIC
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/BICConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/BICConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/BIC
)

# === pkg-config ===
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/bic.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/bic.pc
    @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/bic.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
