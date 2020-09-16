cmake_minimum_required(VERSION 3.0.0)
project(OpenGL1 VERSION 0.1.0)

if (UNIX)
  find_package(OpenGL REQUIRED)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(OPENGL_LIBS REQUIRED sdl2 glew)

  include_directories(${OpenGL_INCLUDE_DIRS})
endif (UNIX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")

add_executable(OpenGL1 Project1/camera.c Project1/game.c Project1/input.c Project1/main.c Project1/shader.c Project1/texture.c Project1/model.c)

if (UNIX)
  target_link_libraries(OpenGL1 ${OPENGL_LIBS_LIBRARIES})
  target_link_libraries(OpenGL1 m)
  target_link_libraries (OpenGL1 ${OPENGL_LIBRARIES})
  target_include_directories(OpenGL1 PUBLIC ${OPENGL_LIBS_INCLUDE_DIRS})
  target_compile_options(OpenGL1 PUBLIC ${OPENGL_LIBS_CFLAGS_OTHER})
endif (UNIX)
