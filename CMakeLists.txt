cmake_minimum_required(VERSION 3.14)

set(CPACK_PROJECT_NAME ray-tracer)
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(APP_TARGET ray-tracer)

project(${APP_TARGET} VERSION 0.0.1)

include(CPack)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# Fix linking on 10.14+. See https://stackoverflow.com/questions/54068035
LINK_DIRECTORIES(/usr/local/lib)

file(GLOB source_files
  "src/*.h"
  "src/*.cpp"
)

add_subdirectory(vendor)

add_executable(${APP_TARGET} src/main.cpp ${source_files})

set_target_properties (${APP_TARGET} PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED TRUE
)

