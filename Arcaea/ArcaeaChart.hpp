#pragma once

namespace Arcaea {
	using int64 = long long int;

	enum ArcaeaNoteType
	{
		ArcaeaNoteType_Unknown,
		ArcaeaNoteType_Tap,
		ArcaeaNoteType_Arc,
		ArcaeaNoteType_Hold,
		ArcaeaNoteType_Trace,
		ArcaeaNoteType_ArcTap,
	};

	struct ArcaeaNoteData
	{
		ArcaeaNoteType NoteType = ArcaeaNoteType::ArcaeaNoteType_Unknown;
		std::vector<double> Data{};

		float GetStartOffset() const {
			return static_cast<float>(Data[0]);
		}
	};

	struct ArcaeaChart
	{
		int64 AudioOffset = 0;
		std::vector<ArcaeaNoteData> Notes{};
	};
}