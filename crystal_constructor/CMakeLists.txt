# external libraries
add_subdirectory(external/glfw)
add_library(glad external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include/)

# crystal constructor libraries
add_subdirectory(crystal_model)
add_subdirectory(utils)