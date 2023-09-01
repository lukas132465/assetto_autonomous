set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/Point.h")

add_executable(main main.cpp ${HEADER_LIST})

target_link_libraries(main PUBLIC car)

target_include_directories(main PUBLIC ${assetto_autonomous_SOURCE_DIR}/include ../main)
