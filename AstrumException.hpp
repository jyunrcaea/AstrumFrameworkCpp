#pragma once
#include <stdexcept>
#include <string>

class AstrumException : public std::runtime_error {
public:
    AstrumException() : std::runtime_error("Astrum Exception") {}
    AstrumException(const std::string& message) : std::runtime_error(message) {}
};