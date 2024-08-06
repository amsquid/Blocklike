#include "logger.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>

void blocklike::Logger::println(std::string message) {
    std::time_t time = std::time(0);
    
    std::cout << "[" << time << "] " << message << "\n";
}