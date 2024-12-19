add_library(opengl_graphics vbo.cpp ebo.cpp vao.cpp shader.cpp camera.cpp mesh.cpp)
target_link_libraries(opengl_graphics PUBLIC glad utils cxx_setup)