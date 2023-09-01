#ifndef _READER_HPP_
#define _READER_HPP_

#include "SharedInformation.h"
#include <string>


class Reader
{
    public:
        Reader(int port=5005);
        void read();
        SharedInformation* get_info();
        void update(std::string data_string);
    
    private:
        int port;
        SharedInformation info;
};

#endif // _READER_HPP_
