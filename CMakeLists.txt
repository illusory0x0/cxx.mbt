cmake_minimum_required(VERSION 3.10.0)
project(moonbit_cxx_ffi VERSION 0.1.0 LANGUAGES C CXX)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "-fsanitize=address -fsanitize=undefined")
file(TO_CMAKE_PATH $ENV{MOON_HOME} MOON_HOME)

add_executable(main ./stub/main.cxx)


add_library(stub ./stub/stub.cxx)

include_directories(${MOON_HOME}/include)
include_directories(.)