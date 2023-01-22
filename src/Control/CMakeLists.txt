set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/Point.h")

add_library(control STATIC Controller.cpp Controller.h ${HEADER_LIST})

target_include_directories(control PUBLIC ${assetto_autonomous_SOURCE_DIR}/include ../control)
