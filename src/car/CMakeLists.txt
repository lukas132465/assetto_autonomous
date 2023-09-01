set(HEADER_LIST "${CMAKE_SOURCE_DIR}/include/Point.h")

add_library(car STATIC Car.cpp Car.h ${HEADER_LIST})

target_include_directories(car PUBLIC ${CMAKE_SOURCE_DIR}/include ../car)

target_link_libraries(car PUBLIC control reader sender)
