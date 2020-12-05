cmake_minimum_required(VERSION 3.12)

project(blind_test CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(LIB_SRC
  lib/imgui/imgui.cpp
  lib/imgui/imgui_draw.cpp
  lib/imgui/imgui_widgets.cpp
  lib/imgui-sfml/imgui-SFML.cpp
  lib/imgui/imgui_demo.cpp
)

set(SRC
  src/main.cc
  src/tools/Debug.cc
  src/tools/Random.cc
  src/GraphicsEngine.cc
  src/InputsManager.cc
)


add_executable(${PROJECT_NAME} "${LIB_SRC}" "${SRC}")


set(THREADS_PREFER_PTHREAD_FLAG ON) # TODO Cross-platform compatible?
find_package(Threads REQUIRED)

find_package(OpenGL REQUIRED)
find_package(SFML 2 REQUIRED graphics) # automatic link against 'window' and 'system'

target_include_directories(${PROJECT_NAME} PUBLIC src/ lib/imgui lib/imgui-sfml ${SFML_DIR})

target_link_libraries(${PROJECT_NAME} Threads::Threads stdc++fs GL sfml-graphics)
