cmake_minimum_required(VERSION 3.9)
project(Project2)

set(CMAKE_CXX_STANDARD 98)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(Project2 Buffers.h Buffers.cpp Camera.h Camera.cpp Canvas.h Canvas.cpp finalMain.cpp Lighting.h Lighting.cpp Material.h Object.h Object.cpp ShaderSetup.h ShaderSetup.cpp Shapes.h Shapes.cpp Textures.h Textures.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)

find_package(OpenGL REQUIRED)
target_include_directories(Project2 PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(Project2 ${PROJECT_SOURCE_DIR}/lib/libSOIL.a)
target_link_libraries(Project2 ${OPENGL_gl_LIBRARY})

target_link_libraries(Project2 ${PROJECT_SOURCE_DIR}/lib/libglew32.a)
target_link_libraries(Project2 ${PROJECT_SOURCE_DIR}/lib/libglew32.dll.a)
target_link_libraries(Project2 ${PROJECT_SOURCE_DIR}/lib/libglfw3.a)
target_link_libraries(Project2 ${PROJECT_SOURCE_DIR}/lib/libglfw3dll.a)
