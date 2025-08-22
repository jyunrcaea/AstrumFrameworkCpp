#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumPolygonsObject.hpp"

namespace InGame {
	class ArcObject : public Astrum::PolygonsObject
	{
	public:
		ArcObject(const Arcaea::NoteData& data) {
			using namespace Astrum;
			height = static_cast<float>(data.Data[1] - data.Data[0]);
			//const float startX = static_cast<float>(LeftX + (NoteWidth * 4.f) * data.Data[2]) * 0.8f;
			//const float endX = static_cast<float>(LeftX + (NoteWidth * 4.f) * data.Data[3]) * 0.8f;
			const float startX = static_cast<float>(LeftX + (NoteWidth * 1.5f) + (NoteWidth * 3.f) * data.Data[2]);
			const float endX = static_cast<float>(LeftX + (NoteWidth * 1.5f) + (NoteWidth * 3.f) * data.Data[3]);

			std::vector<VertexColor> vertices = {
				VertexColor({ startX - 15, height * 0.5f }, Color::MintGreen),
				VertexColor({ startX + 15, height * 0.5f }, Color::MintGreen),
				VertexColor({ endX - 15, height * -0.5f }, Color::MintGreen),
				VertexColor({ endX + 15, height * -0.5f }, Color::MintGreen),
			};
			SetPolygons(Polygons::MakeShared(
				vertices,
				{ 0, 1, 2, 1, 3, 2 }
			));

			Position.SetY(data.GetStartOffset() + height / 2.f);
		}

	private:
		float height = 0;
	};
}