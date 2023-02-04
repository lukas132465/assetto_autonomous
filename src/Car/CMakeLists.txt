set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/Point.h")

add_library(car STATIC Car.cpp Car.h ${HEADER_LIST})

target_include_directories(car PUBLIC ${assetto_autonomous_SOURCE_DIR}/include ../Car)

target_link_libraries(car control communication)