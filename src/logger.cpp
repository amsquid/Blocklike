#include "logger.hpp"

#include <cstdlib>
#include <iostream>
#include <ctime>

bool shouldAddPrefix = true;

void prefix() {
	std::time_t time = std::time(0);

	std::cout << "[" << time << "] ";
}

void blocklike::Logger::print(std::string message) {
	if(shouldAddPrefix) prefix();

	shouldAddPrefix = message.find("\n") != std::string::npos;

	std::cout << message;
}

void blocklike::Logger::print(float message) {
	std::time_t time = std::time(0);
	
	std::cout << message;
}

void blocklike::Logger::print(int message) {
	std::time_t time = std::time(0);
	
	std::cout << message;
}