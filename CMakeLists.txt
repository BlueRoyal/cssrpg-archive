cmake_minimum_required(VERSION 3.10)
project(cssrpg)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_WINDOWS "Build Windows plugin" OFF)
option(BUILD_LINUX "Build Linux plugin" ON)
set(HL2SDK_ROOT "hl2sdk/hl2sdk" CACHE PATH "Path to extracted HL2 SDK")

if(BUILD_WINDOWS AND BUILD_LINUX)
    message(FATAL_ERROR "Enable only one of BUILD_WINDOWS or BUILD_LINUX")
endif()

if(BUILD_WINDOWS)
    add_definitions(-DWIN32 -D_WINDOWS)
    set(SDK_LIB_DIR ${HL2SDK_ROOT}/lib/public)
    set(TIER0_LIB ${SDK_LIB_DIR}/tier0.lib)
    set(VSTDLIB_LIB ${SDK_LIB_DIR}/vstdlib.lib)
    set(SQLITE_LIB plugin_cssrpg/sqlite/sqlite3.lib)
elseif(BUILD_LINUX)
    add_definitions(-DLINUX)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set(SDK_LIB_DIR ${HL2SDK_ROOT}/srcds_l/bin)
    set(TIER0_LIB ${SDK_LIB_DIR}/tier0_i486.so)
    set(VSTDLIB_LIB ${SDK_LIB_DIR}/vstdlib_i486.so)
    set(SQLITE_LIB plugin_cssrpg/sqlite/sqlite3.a)
else()
    message(FATAL_ERROR "No build target selected")
endif()

include_directories(
    plugin_cssrpg
    plugin_cssrpg/sqlite
    ${HL2SDK_ROOT}/public
    ${HL2SDK_ROOT}/public/tier0
    ${HL2SDK_ROOT}/public/tier1
    ${HL2SDK_ROOT}/game_shared
    ${HL2SDK_ROOT}/dlls
)

file(GLOB PLUGIN_SOURCES
    plugin_cssrpg/*.cpp
    plugin_cssrpg/items/*.cpp
    plugin_cssrpg/rest/*.cpp
)

find_package(Threads REQUIRED)

add_library(cssrpg MODULE ${PLUGIN_SOURCES})

target_link_libraries(cssrpg ${TIER0_LIB} ${VSTDLIB_LIB} ${SQLITE_LIB} Threads::Threads)


