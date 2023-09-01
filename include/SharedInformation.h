#include <sstream>


struct SharedInformation
{
    float speedKmh = 0;
    float heading = 0;
    float steerAngle = 0;
    float coordinate_x = 0;
    float coordinate_y = 1; 

    std::string to_string();
};

std::string SharedInformation::to_string()
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
