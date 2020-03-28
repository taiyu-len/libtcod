cmake_minimum_required (VERSION 3.9)
project(libtcod C CXX)

add_library(tcod)
add_library(TCOD::TCOD ALIAS tcod)

# location of src relative to this file
set(TCOD_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../src)

file(GLOB_RECURSE TCOD_SOURCES
    ${TCOD_SOURCE_DIR}/libtcod/*.c
    ${TCOD_SOURCE_DIR}/libtcod/*.cpp
)

target_sources(tcod PRIVATE
    ${TCOD_SOURCES}
    # Vender Sources
    ${TCOD_SOURCE_DIR}/vendor/glad.c
    ${TCOD_SOURCE_DIR}/vendor/lodepng.c
    ${TCOD_SOURCE_DIR}/vendor/stb.c
    ${TCOD_SOURCE_DIR}/vendor/utf8proc/utf8proc.c
)

target_include_directories(tcod
    PUBLIC  ${TCOD_SOURCE_DIR}
    PRIVATE ${TCOD_SOURCE_DIR}/vendor
)

find_package(SDL2 REQUIRED)
find_package(ZLIB REQUIRED)

target_link_libraries(tcod
    PUBLIC  SDL2::SDL2
    PRIVATE ZLIB::ZLIB ${CMAKE_DL_LIBS}
)

target_compile_features(tcod PUBLIC cxx_std_14)

target_compile_options(tcod
    PRIVATE
    $<$<C_COMPILER_ID:GNU,AppleClang,Clang>:-Wall -Wextra>
    $<$<C_COMPILER_ID:MSVC>:/W4>
)

target_compile_definitions(tcod
    PRIVATE TCOD_IGNORE_DEPRECATED
    PRIVATE $<$<BOOL:${BUILD_SHARED_LIBS}>:LIBTCOD_EXPORTS>
    PUBLIC  $<$<NOT:$<BOOL:${BUILD_SHARED_LIBS}>>:LIBTCOD_STATIC>
    PRIVATE $<$<C_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
)

if(MSVC)
    set_target_properties(tcod PROPERTIES OUTPUT_NAME libtcod)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)
if(IPO_SUPPORTED)
    set_target_properties(tcod PROPERTIES
        INTERPROCEDURAL_OPTIMIZATION TRUE
        INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    )
endif()
