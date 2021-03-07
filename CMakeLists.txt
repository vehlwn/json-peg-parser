cmake_minimum_required(VERSION 3.10)

project(json-peg-parser)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

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
conan_cmake_run(REQUIRES cpp-peglib/1.3.3 BASIC_SETUP)

add_executable(
  ${PROJECT_NAME}
  main.cpp
  AstBuilder.h
  AstBuilder.cpp
)
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
