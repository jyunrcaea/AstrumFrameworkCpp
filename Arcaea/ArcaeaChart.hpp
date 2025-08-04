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
		ArcaeaNoteType NoteType;
		std::vector<double> Data;
	};

	struct ArcaeaChart
	{
		int64 AudioOffset;
		std::vector<ArcaeaNoteData> Notes;
	};
}