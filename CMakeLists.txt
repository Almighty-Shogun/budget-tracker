# Setting the minimum required CMake version for this project.
cmake_minimum_required(VERSION 3.31)

# Setting the project name.
project(BudgetTracker C)

# Set the C standard to C23 and make it required
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Automatically detect the VCPKG location if not already been defined.
if (NOT DEFINED VCPKG_ROOT)
    find_path(VCPKG_ROOT_DIR
            NAMES vcpkg.exe vcpkg
            PATHS
            ${CMAKE_PREFIX_PATH}
            $ENV{VCPKG_ROOT}
            $ENV{USERPROFILE}/.vcpkg-clion/vcpkg
            $ENV{USERPROFILE}/vcpkg
            $ENV{ProgramFiles}/vcpkg
            $ENV{ProgramFiles\(x86\)}/vcpkg
            $ENV{HOME}/.vcpkg-clion/vcpkg
            $ENV{HOME}/vcpkg
            /usr/local/vcpkg
            /opt/vcpkg
    )

    # If vcpkg was found, normalize path format and set VCPKG_ROOT
    if (VCPKG_ROOT_DIR)
        file(TO_CMAKE_PATH "${VCPKG_ROOT_DIR}" VCPKG_ROOT)
    endif ()
endif ()

# Setting defaults depending on the OS.
if (WIN32)
    set(DEFAULT_VCPKG_TRIPLET "x64-windows")
    set(VCPKG_TOOLCHAIN_SUBPATH "scripts\\buildsystems\\vcpkg.cmake")
else ()
    set(DEFAULT_VCPKG_TRIPLET "x64-linux")
    set(VCPKG_TOOLCHAIN_SUBPATH "scripts/buildsystems/vcpkg.cmake")
endif ()

# Throw error if VCPKG root is still not found.
if (NOT DEFINED VCPKG_ROOT)
    message(WARNING
            "VCPKG_ROOT is not set and automatic detection has failed. "
            "Please set it with:\n  cmake -DVCPKG_ROOT=path/to/vcpkg .."
    )
    message(FATAL_ERROR "VCPKG_ROOT is required to configure this project.")
endif ()

# Forces variables to be cached for configuration.
set(VCPKG_ROOT "${VCPKG_ROOT}" CACHE PATH "Path to VCPKG root directory" FORCE)
set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/${VCPKG_TOOLCHAIN_SUBPATH}" CACHE FILEPATH "VCPKG toolchain file" FORCE)

# Use the default triplet for the platform if VCPKG_TRIPLET is not found.
if (NOT DEFINED VCPKG_TRIPLET)
    set(VCPKG_TRIPLET "${DEFAULT_VCPKG_TRIPLET}" CACHE STRING "VCPKG target triplet" FORCE)
endif ()

# Try to find cJSON package via CMake's package config.
find_package(cjson CONFIG QUIET)

if (NOT cjson_FOUND)
    # If cJSON config package is not found, fall back to manual include/lib search.
    message(STATUS "cJSON package config not found, falling back to manual search.")

    # Search for cJSON include directory.
    find_path(CJSON_INCLUDE_DIR cjson/cJSON.h
            PATHS
            ${CMAKE_PREFIX_PATH}
            ${VCPKG_ROOT}/installed/*/include
            /usr/include
            /usr/local/include
    )

    # Search for cJSON library file.
    find_library(CJSON_LIBRARY NAMES cjson
            PATHS
            ${CMAKE_PREFIX_PATH}
            ${VCPKG_ROOT}/installed/*/lib
            /usr/lib
            /usr/local/lib
    )

    # If cJSON is still not found, abort with an error.
    if (NOT CJSON_INCLUDE_DIR OR NOT CJSON_LIBRARY)
        execute_process()
        message(FATAL_ERROR "Could not find cJSON. Please install it via vcpkg or your package manager.")
    endif ()
endif ()

# Get all source files from the src directory recursively.
file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

# Create the executable target.
add_executable(BudgetTracker ${SRC_FILES})

# Add the local src directory to include search path.
target_include_directories(BudgetTracker PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (cjson_FOUND)
    # If found via find_package, just link it directly.
    target_link_libraries(BudgetTracker PRIVATE cjson)
else ()
    # Link the manually found cJSON include directory and library to the target.
    target_include_directories(BudgetTracker PRIVATE ${CJSON_INCLUDE_DIR})
    target_link_libraries(BudgetTracker PRIVATE ${CJSON_LIBRARY})
endif ()