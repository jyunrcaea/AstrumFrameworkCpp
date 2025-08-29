#pragma once
#include <stdexcept>
#include <string>

class AstrumException : public std::runtime_error {
public:
    AstrumException() : std::runtime_error("Astrum Exception") { print(); }
    AstrumException(const std::string& message) : std::runtime_error(message) { print(); }
    AstrumException(const std::wstring& message) : std::runtime_error(wstr2str(message)) { print(); }
    AstrumException(const int line, const std::string& file, const std::string& message) : std::runtime_error(message +" (Line: " + std::to_string(line) + ", File: {" + file +"})") { print(); }
    AstrumException(const int line, const std::string& file, const std::wstring& message) : std::runtime_error(wstr2str(message) +" (Line: " + std::to_string(line) + ", File: '" + file + "')") { print(); }

private:
    std::string wstr2str(const std::wstring& wstr);
    void print();
};