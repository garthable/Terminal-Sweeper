find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(ImGui STATIC
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui_demo.cpp

    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

target_include_directories(ImGui PUBLIC
    imgui
    imgui/backends
)

target_link_libraries(ImGui glfw OpenGL::GL)

add_library(StbImage INTERFACE
    stb_image/stb_image.h
)
target_compile_definitions(StbImage INTERFACE
    STB_IMAGE_IMPLEMENTATION
)