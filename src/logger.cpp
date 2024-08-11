#include "logger.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>

void blocklike::Logger::print(std::string message) {
	std::cout << message;
}

void blocklike::Logger::print(float message) {
	std::cout << message;
}

void blocklike::Logger::print(int message) {
	std::cout << message;
}