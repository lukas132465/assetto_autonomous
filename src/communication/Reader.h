#ifndef _READER_HPP_
#define _READER_HPP_

#include <boost/json.hpp>

class Reader{
    public:
        int read();
        boost::json::object* get_info();
    private:
        boost::json::object info;
};

#endif // _READER_HPP_
