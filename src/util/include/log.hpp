#pragma once

#include <iostream>
#include <chrono>

namespace util
{

}

#define LOG_INFO(info) do \
{ \
    std::cout << "[INFO]" << info << '\n'; \
} while(0) 

#define LOG_WARNING(warning) do \
{ \
    std::cout << "[WARNING]" << info << '\n'; \
} while(0) 

#define LOG_ERROR(error) do \
{ \
    std::cout << "[ERROR]" << info << '\n'; \
} while(0) 
