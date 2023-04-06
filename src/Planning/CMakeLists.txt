set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/Point.h")

#find_package(Boost REQUIRED)

add_library(planning STATIC Planner.cpp Planner.h ${HEADER_LIST})

target_include_directories(planning PUBLIC ${assetto_autonomous_SOURCE_DIR}/include ../Planning)

#target_link_libraries(planning ${Boost_LIBRARIES})
