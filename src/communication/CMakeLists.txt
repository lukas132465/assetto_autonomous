set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/Point.h" "${assetto_autonomous_SOURCE_DIR}/include/SharedMemory.h" "${Boost_INCLUDE_DIR}/boost/interprocess/windows_shared_memory.hpp")

find_package(Boost REQUIRED)

add_library(communication STATIC Communicator.cpp Communicator.h ${HEADER_LIST})

target_include_directories(communication PUBLIC ${assetto_autonomous_SOURCE_DIR}/include ${Boost_INCLUDE_DIRS} ../communication)

target_link_libraries(communication ${Boost_LIBRARIES})
