set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/Point.h")

find_package(Boost REQUIRED)

add_library(control STATIC PurePursuit.cpp PurePursuit.h Controller.h ${HEADER_LIST})

target_include_directories(control PUBLIC ${assetto_autonomous_SOURCE_DIR}/include ../Control)

target_link_libraries(control ${Boost_LIBRARIES})
