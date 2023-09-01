#include "Reader.h"

#include <iostream>
#include <boost/asio.hpp>
#include <boost/json/src.hpp> // ToDo: Find out if this should be changed to boost/json.hpp


Reader::Reader(int port) : port{port} {};

void Reader::read()
{
    using boost::asio::ip::udp;

    const size_t buffer_size = 1024; // stores the input json string

    try
    {
        boost::asio::io_context io_context;
        udp::socket socket(io_context, udp::endpoint(udp::v4(), port));
        std::cout << "Server listening on port " << port << std::endl;

        while (true)
        {
            std::array<char, buffer_size> recv_buffer;
            udp::endpoint sender_endpoint;
            size_t length = socket.receive_from(boost::asio::buffer(recv_buffer), sender_endpoint);

            std::string received_message(recv_buffer.data(), length);
            _update(received_message);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

SharedInformation Reader::get_info()
{
    return info;
}

void Reader::_update(std::string data_string)
{
    std::lock_guard<std::mutex> lock(mutex);
    boost::json::object data = boost::json::parse(data_string).as_object();

    auto find_element = [data](std::string name)
    {
        boost::json::value value = data.find(name)->value();
        return value.is_double() ? static_cast<float>(value.as_double()) : static_cast<float>(value.as_int64());
    };

    // ToDo: add this to the SharedInformation.h include file - after figuring out linking...
    info.speedKmh = data.contains("speedKmh") ? find_element("speedKmh") : 0;
    info.heading = data.contains("heading") ? find_element("heading") : 0;
    info.steerAngle = data.contains("steerAngle") ? find_element("steerAngle") : 0;
    info.coordinate_x = data.contains("coordinate_x") ? find_element("coordinate_x") : 0;
    info.coordinate_y = data.contains("coordinate_y") ? find_element("coordinate_y") : 0;
}
