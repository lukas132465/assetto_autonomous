add_library(car)

target_sources(car
    PRIVATE
        Car.cpp
    PUBLIC
        Car.h)

target_include_directories(car PUBLIC ${CMAKE_CURRENT_LIST_DIR})