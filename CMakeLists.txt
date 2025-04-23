cmake_minimum_required(VERSION 3.10.0)
project(moonbit_cxx_ffi VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CXX_WARNING_AS_ERROR "-Werror=return-type")
set(CXX_SANITIZER_FLAG "-fsanitize=address -fsanitize=undefined")

set(CMAKE_CXX_FLAGS "${CXX_WARNING_AS_ERROR} ${CXX_SANITIZER_FLAG}")

file(TO_CMAKE_PATH $ENV{MOON_HOME} MOON_HOME)

add_executable(main ./stub/main.cxx)


add_library(stub ./stub/stub.cxx)

include_directories(${MOON_HOME}/include)
include_directories(.)