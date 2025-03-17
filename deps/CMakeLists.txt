add_library(Clay INTERFACE)
target_include_directories(Clay INTERFACE clay)

add_library(RaylibRenderer INTERFACE)
target_include_directories(RaylibRenderer INTERFACE clay/renderers/raylib)