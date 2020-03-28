Cmake can be used to build libtcod as a submodule of another project

# Dependencies
This requires SDL2 and ZLIB to be installed locally, or where cmake can find it.

# using libTCOD as a Submodule in a CMake Project
Add libtcod as a subdirectory into your project; via git, or dowloading the
sources.
```sh
git submodule add https://github.com/libtcod/libtcod
```

Add libtcod directory within your CMakeLists.txt, which provides the TCOD::TCOD
target, which you can then link to your application.
```cmake
add_subdirectory(libtcod/buildsys/cmake)
target_link_libraries(my_app PRIVATE TCOD::TCOD)
```

# using libTCOD via cmake FetchContent module
```cmake
include(FetchContent)
FetchContent_Declare(
	libtcod
	GIT_REPOSITORY https://github.com/libtcod/libtcod.git
)
FetchContent_GetProperties(libtcod)
if (NOT libtcod_POPULATED)
	FetchContent_Populate(libtcod)
	add_subdirectory(${libtcod_SOURCE_DIR}/buildsys/cmake ${libtcod_BINARY_DIR})
endif()
target_link_libraries(my_app PRIVATE TCOD::TCOD)
```


