#ifndef _SENDER_HPP_
#define _SENDER_HPP_

#include <boost/asio.hpp>
#include <iostream>

class Sender{
    public:
        Sender(std::string ip, std::string port);

        // ToDO: move to .cpp file - figure out linking
        template <typename T>
        void send(const T& message)
        {
                    using boost::asio::ip::udp;

            try
            {
                boost::asio::io_context io_context;
                udp::socket socket(io_context, udp::v4());

                udp::resolver resolver(io_context);
                udp::resolver::results_type endpoints = resolver.resolve(udp::v4(), ip, port);

                socket.send_to(boost::asio::buffer(message), *endpoints.begin());
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }

    private:
        std::string ip;
        std::string port;
};

#endif // _SENDER_HPP_
