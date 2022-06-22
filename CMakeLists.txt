cmake_minimum_required(VERSION 3.10)

project(json-peg-parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  # using Clang
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -stdlib=libc++ -lc++abi")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
endif()

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    STATUS
    "Downloading conan.cmake from https://github.com/conan-io/cmake-conan"
  )
  file(
    DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
  )
endif()
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_cmake_run(
  REQUIRES
  cpp-peglib/1.3.3
  icu/68.2
  BASIC_SETUP
)

add_executable(
  ${PROJECT_NAME}
  main.cpp
  AstBuilder.h
  AstBuilder.cpp
  JsonBuilder.h
  JsonBuilder.cpp
  Value.h
)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
