#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumPolygonsObject.hpp"

namespace InGame {
	class TraceObject : public AstrumPolygonsObject
	{
	public:
		TraceObject(const Arcaea::NoteData& data) {
			height = static_cast<float>(data.Data[1] - data.Data[0]);
			const float startX = static_cast<float>(LeftX + (NoteWidth * 1.5f) + (NoteWidth * 3.f) * data.Data[2]);
			const float endX = static_cast<float>(LeftX + (NoteWidth * 1.5f) + (NoteWidth * 3.f) * data.Data[3]);

			auto color = AstrumColor::Periwinkle;
			color.Alpha = 0.5f;
			std::vector<AstrumVertexColor> vertices = {
				AstrumVertexColor({ startX - 10, height * 0.5f }, color),
				AstrumVertexColor({ startX + 10, height * 0.5f }, color),
				AstrumVertexColor({ endX - 10, height * -0.5f }, color),
				AstrumVertexColor({ endX + 10, height * -0.5f }, color),
			};
			SetPolygons(AstrumPolygons::MakeShared(
				vertices,
				{ 0, 1, 2, 1, 3, 2 }
			));

			Position.SetY(data.GetStartOffset() + height / 2.f);
		}

	private:
		float height = 0;
	};
}