#pragma once

namespace Arcaea {
	using int64 = long long int;

	enum ArcaeaNoteType
	{
		ArcaeaNoteType_Unknown,
		ArcaeaNoteType_Tap,
		ArcaeaNoteType_Arc,
		ArcaeaNoteType_Hold,
		ArcaeaNoteType_Trace
	};

	struct ArcaeaNoteData
	{
		ArcaeaNoteType NoteType = ArcaeaNoteType::ArcaeaNoteType_Unknown;
		std::vector<double> Data{};

		double GetStartOffset() const {
			return static_cast<double>(Data[0]) * 0.001;
		}
	};

	struct ArcaeaChart
	{
		int64 AudioOffset = 0;
		std::vector<ArcaeaNoteData> Notes{};
	};
}