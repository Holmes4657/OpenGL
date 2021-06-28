cmake_minimum_required(VERSION 3.0.0)
project(openGLproject VERSION 0.1.0)

if (UNIX)
  find_package(OpenGL REQUIRED)
  find_package(PkgConfig REQUIRED)
  pkg_check_modules(EXTERNAL REQUIRED sdl2 glew)

  include_directories(${OpenGL_INCLUDE_DIRS})
endif (UNIX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-long-long -pedantic")

add_executable(${PROJECT_NAME} source/camera.c source/game.c source/input.c source/main.c source/shader.c source/texture.c source/model.c)

if (UNIX)
  target_link_libraries(${PROJECT_NAME} ${EXTERNAL_LIBRARIES} ${OPENGL_LIBRARIES} m)
  target_include_directories(${PROJECT_NAME} PUBLIC ${EXTERNAL_INCLUDE_DIRS})
  target_compile_options(${PROJECT_NAME} PUBLIC ${EXTERNAL_CFLAGS_OTHER})
endif (UNIX)
