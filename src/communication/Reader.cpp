#include "Reader.h"

#include <iostream>
#include <string>
#include <boost/asio.hpp>


int Reader::read()
{
    using boost::asio::ip::udp;

    try {
        boost::asio::io_context io_context;

        udp::socket socket(io_context, udp::endpoint(udp::v4(), 5005));
        
        std::cout << "Server listening on port 5005..." << std::endl;

        while (true) {
            std::array<char, 1024> recv_buffer;
            udp::endpoint sender_endpoint;
            size_t length = socket.receive_from(boost::asio::buffer(recv_buffer), sender_endpoint);
            
            std::string received_message(recv_buffer.data(), length);
            boost::json::object parsed_data = boost::json::parse(received_message).as_object();
            info = parsed_data;
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

boost::json::object* Reader::get_info()
{
    return &info;
}
