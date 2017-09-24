cmake_minimum_required(VERSION 3.8)
project(Test)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES const_data.h main.cpp objects.cpp objects.h opengl_test.cpp opengl_test.h platform.cpp platform.hpp Program.cpp Program.h Shader.cpp Shader.h)

add_executable(Test ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(Test GL)
TARGET_LINK_LIBRARIES(Test glfw)
TARGET_LINK_LIBRARIES(Test GLEW)
