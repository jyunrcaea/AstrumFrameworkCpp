#pragma once

namespace Arcaea {
	using int64 = long long int;

	enum class NoteType
	{
		Unknown,
		Tap,
		Arc,
		Hold,
		Trace,
		ArcTap,
	};

	struct NoteData
	{
		NoteType NoteType = NoteType::Unknown;
		std::vector<double> Data{};

		float GetStartOffset() const {
			return static_cast<float>(Data[0]);
		}
	};

	struct ChartData
	{
		int64 AudioOffset = 0;
		std::vector<NoteData> Notes{};
	};
}