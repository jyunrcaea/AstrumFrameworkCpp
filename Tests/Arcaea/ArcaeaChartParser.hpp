#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <regex>
#include <ranges>
#include <filesystem>
#include <format>
#include "ArcaeaChart.hpp"

namespace Arcaea {
	class ChartParser
	{
	public:
		ChartParser(const std::filesystem::path& path);
		ChartData ToParse();

	private:
		std::fstream fileStream;

		std::string ReadLine();
	};
}