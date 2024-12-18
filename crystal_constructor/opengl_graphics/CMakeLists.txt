add_library(opengl_graphics vbo.cpp ebo.cpp)
target_link_libraries(opengl_graphics PUBLIC glad cxx_setup)