cmake_minimum_required(VERSION 3.12)

project(blind_test CXX)


# set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(SRC
  src/main.cc
  src/tools/Debug.cc
  src/tools/Random.cc
  src/tools/OptionsParser.cc
  src/GraphicsEngine.cc
  src/InputsManager.cc
)


set(COMPILE_SRC_FLAGS
  -Wall
  -Wextra
  -Wpedantic
  -Waggressive-loop-optimizations
  -Wformat=2
  -Wformat-contains-nul
  -Wformat-extra-args
  -Wformat-signedness
  -Wformat-zero-length
  -Warray-bounds=2
  -Wattributes
  -Wbool-compare
  -Wbuiltin-macro-redefined
  -Wcast-align
  -Wcast-qual
  -Wconditionally-supported
  -Wconversion
  -Wconversion-null
  -Wctor-dtor-privacy
  -Wdate-time
  -Wdelete-incomplete
  -Wdeprecated
  -Wdeprecated-declarations
  -Wdisabled-optimization
  -Wdiv-by-zero
  -Wdouble-promotion
  -Wendif-labels
  -Wfloat-equal
  -Wfree-nonheap-object
  -Winherited-variadic-ctor
  -Winit-self
  -Wint-to-pointer-cast
  -Winvalid-memory-model
  -Winvalid-offsetof
  -Winvalid-pch
  -Wlarger-than=4096
  -Wliteral-suffix
  -Wlogical-not-parentheses
  -Wlogical-op
  -Wlong-long
  -Wmemset-transposed-args
  -Wmissing-declarations
  -Wmissing-include-dirs
  -Wnoexcept
  -Wnon-template-friend
  -Wnon-virtual-dtor
  -Wnormalized
  -Wodr
  -Wold-style-cast
  -Woverflow
  -Woverloaded-virtual
  -Wpacked
  -Wpacked-bitfield-compat
  -Wpmf-conversions
  -Wpragmas
  -Wredundant-decls
  -Wreturn-local-addr
  -Wshadow
  -Wshift-count-negative
  -Wshift-count-overflow
  -Wsign-promo
  -Wsized-deallocation
  -Wsizeof-array-argument
  -Wsizeof-pointer-memaccess
  -Wstack-protector
  -Wstrict-null-sentinel
  -Wstrict-overflow=5
  -Wsuggest-attribute=const
  -Wsuggest-attribute=format
  -Wsuggest-attribute=noreturn
  -Wsuggest-attribute=pure
  -Wsuggest-final-methods
  -Wsuggest-final-types
  -Wsuggest-override
  -Wswitch-bool
  -Wswitch-default
  -Wsync-nand
  -Wtrampolines
  -Wunsafe-loop-optimizations
  -Wunused-macros
  -Wuseless-cast
  -Wvarargs
  -Wvector-operation-performance
  -Wvirtual-move-assign
  -Wwrite-strings
  -Wzero-as-null-pointer-constant
)



# Compile Dear ImGui as a static library
set(LIB_SRC
  lib/imgui/imgui.cpp
  lib/imgui/imgui_draw.cpp
  lib/imgui/imgui_widgets.cpp
  lib/imgui-sfml/imgui-SFML.cpp
  lib/imgui/imgui_demo.cpp
)
add_library(imgui STATIC ${LIB_SRC} ${LIB_HDR})
target_include_directories(imgui PRIVATE lib/ lib/imgui/ lib/imgui-sfml/)
target_compile_options(imgui PRIVATE "-Ofast")


# Specific flags for our own sources
foreach(f IN LISTS SRC)
  message(STATUS "test ${f} test")
  set_source_files_properties("${f}" PROPERTIES COMPILE_OPTIONS "${COMPILE_SRC_FLAGS}")
endforeach(f)


add_executable(${PROJECT_NAME} "${SRC}")

set(THREADS_PREFER_PTHREAD_FLAG ON) # TODO Cross-platform compatible?
find_package(Threads REQUIRED)

find_package(OpenGL REQUIRED)
find_package(SFML 2 REQUIRED graphics) # automatic link against 'window' and 'system'


target_include_directories(${PROJECT_NAME} PRIVATE src/ lib/imgui lib/imgui-sfml)
target_link_libraries(${PROJECT_NAME} Threads::Threads stdc++fs GL sfml-graphics imgui)
