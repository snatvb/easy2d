#include <iostream>
#include <easy2d/Debug/Log.hpp>

namespace easy2d
{
    using string = std::string;

    void log(const char *msg)
    {
        std::cout << msg << std::endl;
    };

    void log(const string &msg)
    {
        std::cout << msg << std::endl;
    };
} // -- easy2d
