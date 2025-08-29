#pragma once
#include <stdexcept>
#include <string>

class AstrumException : public std::runtime_error {
public:
    AstrumException() : std::runtime_error("Astrum Exception") { }
    AstrumException(const std::string& message) : std::runtime_error(message) { }
    AstrumException(const std::wstring& message) : std::runtime_error(wstr2str(message)) { }
    AstrumException(const int line, const std::string& file, const std::string& message) : std::runtime_error(message +" (Line: " + std::to_string(line) + ", File: {" + file +"})") { }
    AstrumException(const int line, const std::string& file, const std::wstring& message) : std::runtime_error(wstr2str(message) +" (Line: " + std::to_string(line) + ", File: '" + file + "')") { }

private:
    std::string wstr2str(const std::wstring& wstr);
};