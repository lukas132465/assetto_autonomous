#ifndef _SHARED_INFORMATION_HPP_
#define _SHARED_INFORMATION_HPP_

#include <sstream>


struct SharedInformation
{
    float speedKmh = 0;
    float heading = 0;
    float steerAngle = 0;
    float coordinate_x = 0;
    float coordinate_y = 0;

    inline std::string to_string();
};

inline std::string SharedInformation::to_string()
{
    std::stringstream builder;
    builder << "{"
            << "\"speedKmh\": " << speedKmh << ", "
            << "\"heading\": " << heading << ", "
            << "\"steerAngle\": " << steerAngle << ", "
            << "\"coordinate_x\": " << coordinate_x << ", "
            << "\"coordinate_y\": " << coordinate_y // << ", "
            << "}";

    return builder.str();
}

#endif // _SHARED_INFORMATION_HPP_
