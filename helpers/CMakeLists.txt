set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/Point.h")

add_executable(record record.cpp ${HEADER_LIST})

target_link_libraries(record PUBLIC communication)

target_include_directories(record PUBLIC ${assetto_autonomous_SOURCE_DIR}/include ../helpers)
