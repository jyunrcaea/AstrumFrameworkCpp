#include "ArcaeaChartParser.hpp"

Arcaea::ArcaeaChartParser::ArcaeaChartParser(const std::filesystem::path& path)
	: fileStream(path) {
	
}

Arcaea::ArcaeaChart Arcaea::ArcaeaChartParser::ToParse() {
	ArcaeaChart ret{};
	
	for (std::string line; (line = ReadLine())[0] != '-';) {
		size_t cut = line.find(':');
		auto key = line.substr(0, cut);
		auto value = atoi(line.c_str() + cut + 1);	

		if (key == "AudioOffset") {
			ret.AudioOffset = value;
		}
	}

	for (std::string line; std::getline(fileStream, line);) {
		const size_t opening = line.find('(');
		const size_t ending = line.rfind(')');
		std::string noteType = line.substr(0, opening);

		char* const text = (line.data() + opening + 1);
		for (int i = 0; text[i] != '\0'; i++) {
			if (text[i] == ',') text[i] = ' ';
		}
		text[ending - opening - 1] = ' ';
		std::istringstream iss(text);

		if (noteType == "") {
			std::vector<double> vec(2);
			for (auto& v : vec) iss >> v;
			ret.Notes.emplace_back(ArcaeaNoteType::ArcaeaNoteType_Tap, std::move(vec));
			continue;
		}
		
		if (noteType == "hold") {
			std::vector<double> vec(3);
			for (auto& v : vec) iss >> v;
			ret.Notes.emplace_back(ArcaeaNoteType::ArcaeaNoteType_Hold, std::move(vec));
			continue;
		}

		if (noteType == "arc") {
			std::vector<double> vec(7);
			std::string str;

			for (int i = 0; i < 4; i++) iss >> vec[i];
			iss >> str;
			for (int i = 4; i < 6; i++) iss >> vec[i];
			iss >> vec[6];
			iss >> str;

			ArcaeaNoteType noteType;
			if (iss >> str; str == "true") noteType = ArcaeaNoteType::ArcaeaNoteType_Trace;
			else noteType = ArcaeaNoteType::ArcaeaNoteType_Arc;

			ret.Notes.emplace_back(noteType, std::move(vec));
		}
	}

	return ret;
}

std::string Arcaea::ArcaeaChartParser::ReadLine() {
	std::string line;
	std::getline(fileStream, line);
	return line;
}
