#pragma once
#include <stdexcept>
#include <string>

namespace Astrum {
	namespace {
		std::string wstr2str(const std::wstring& message) {
			std::string result;
			result.reserve(message.size());
			for (auto c : message) result.push_back(static_cast<char>(c));
			return result;
		}
		std::wstring str2wstr(const std::string& message) {
			return std::wstring(message.begin(), message.end());
		}
	}

	class Exception : public std::runtime_error {
	public:
		Exception() : std::runtime_error("Astrum Exception") { }
		Exception(const std::string& message) : std::runtime_error(message) { }
		Exception(const std::wstring& message) : std::runtime_error(wstr2str(message)) { }
		Exception(const int line, const std::string& file, const std::string& message) : std::runtime_error(message +" (Line: " + std::to_string(line) + ", File: {" + file +"})") { }
		Exception(const int line, const std::string& file, const std::wstring& message) : Exception(message +L" (Line: " + std::to_wstring(line) + L", File: '" + str2wstr(file) +L"')") { }
	};
}