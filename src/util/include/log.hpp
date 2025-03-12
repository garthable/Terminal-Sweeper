#pragma once

#include <iostream>
#include <chrono>

namespace util
{

}

/**
 * @brief Prints out info
 * 
 * @param info
 * 
 */
#define LOG_INFO(info) do \
{ \
    std::cout << "[INFO] " << info << '\n'; \
} while(0) 

/**
 * @brief Prints out warning
 * 
 * @param warning
 * 
 */
#define LOG_WARNING(warning) do \
{ \
    std::cout << "[WARNING] " << warning << '\n'; \
} while(0) 

/**
 * @brief Prints out error
 * 
 * @param error
 * 
 */
#define LOG_ERROR(error) do \
{ \
    std::clog << "[ERROR] " << error << '\n'; \
} while(0) 
