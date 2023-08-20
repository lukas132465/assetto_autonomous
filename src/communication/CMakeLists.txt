find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/Point.h" "${assetto_autonomous_SOURCE_DIR}/include/SharedMemory.h")
add_library(ac_shared_memory STATIC ACSharedMemory.cpp ACSharedMemory.h ${HEADER_LIST})
target_include_directories(ac_shared_memory PUBLIC ${assetto_autonomous_SOURCE_DIR}/include ../communication)
# target_link_libraries(ac_shared_memory)

set(HEADER_LIST "${Boost_INCLUDE_DIR}/boost/asio.hpp")
add_library(sender STATIC Sender.cpp Sender.h ${HEADER_LIST})
target_include_directories(sender PUBLIC ../communication)
# target_link_libraries(sender)

# set(HEADER_LIST "${Boost_INCLUDE_DIR}/boost/asio.hpp" "${Boost_INCLUDE_DIR}/boost/json.hpp")
# add_library(reader STATIC Reader.cpp Reader.h ${HEADER_LIST})
# target_include_directories(reader PUBLIC ${Boost_INCLUDE_DIRS} ../communication)
# target_link_libraries(reader ${Boost_LIBRARIES})

set(HEADER_LIST "${assetto_autonomous_SOURCE_DIR}/include/SharedInformation.h")
add_executable(send_to_linux send_to_linux.cpp ${HEADER_LIST})
target_include_directories(send_to_linux PUBLIC ../communication)
target_link_libraries(send_to_linux PUBLIC sender ac_shared_memory)
