# external libraries
option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(external/glfw)

add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include/)

add_library(imgui external/imgui/backends/imgui_impl_glfw.cpp external/imgui/backends/imgui_impl_opengl3.cpp external/imgui/imgui.cpp external/imgui/imgui_demo.cpp external/imgui/imgui_draw.cpp external/imgui/imgui_tables.cpp external/imgui/imgui_widgets.cpp)
target_include_directories(imgui PUBLIC external/imgui/)

# crystal constructor libraries
add_subdirectory(crystal_model)
add_subdirectory(opengl_graphics)
add_subdirectory(utils)