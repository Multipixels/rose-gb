set(SDL_STATIC ON CACHE BOOL "Build SDL3 as a static library" FORCE)
set(SDL_SHARED OFF CACHE BOOL "Disable SDL3 shared library" FORCE)
add_subdirectory(SDL EXCLUDE_FROM_ALL)

add_library(vendor INTERFACE EXCLUDE_FROM_ALL)
target_link_libraries(vendor INTERFACE SDL3::SDL3)

add_library(glad INTERFACE EXCLUDE_FROM_ALL glad/gl.c)
target_include_directories(glad INTERFACE glad)