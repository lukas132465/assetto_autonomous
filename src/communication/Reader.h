#ifndef _READER_HPP_
#define _READER_HPP_

#include "SharedInformation.h"

#include <string>
#include <mutex>


class Reader
{
    public:
        Reader(int port=5005);
        void read();
        SharedInformation get_info();

    private:
        int port;
        SharedInformation info;
        std::mutex mutex;

        void _update(std::string data_string);
};

#endif // _READER_HPP_
