cmake_minimum_required(VERSION 3.23.0...3.25.2)
project(assetto_autonomous VERSION 0.1 LANGUAGES CXX)

set(Boost_INCLUDE_DIR "C:/Program Files/vcpkg/vcpkg/installed/x86-windows/include")
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_LIBS OFF)
set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

add_definitions(-DPATH_TO_TXT=\"${CMAKE_SOURCE_DIR}/Records/monza_center.txt\")

include(CTest)

add_subdirectory(helpers)
#add_subdirectory(lib)
add_subdirectory(main)
add_subdirectory(src)
#add_subdirectory(tests)