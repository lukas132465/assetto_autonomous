cmake_minimum_required(VERSION 3.23.0...3.25.2)
project(assetto_autonomous VERSION 0.1 LANGUAGES CXX)

set(Boost_INCLUDE_DIR "/usr/include/boost_1_82_0")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_LIBS OFF)
set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

include(CTest)

add_subdirectory(helpers)
add_subdirectory(main)
add_subdirectory(src)
