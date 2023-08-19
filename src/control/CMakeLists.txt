set(HEADER_LIST "${CMAKE_SOURCE_DIR}/include/Point.h")

find_package(Boost REQUIRED)

add_library(control STATIC PurePursuit.cpp PurePursuit.h Controller.cpp Controller.h ${HEADER_LIST})

target_include_directories(control PUBLIC ${CMAKE_SOURCE_DIR}/include ../control)

target_link_libraries(control ${Boost_LIBRARIES})
