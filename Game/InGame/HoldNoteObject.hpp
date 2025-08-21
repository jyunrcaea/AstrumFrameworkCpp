#pragma once
#include "DataManager.hpp"
#include "../Arcaea/ArcaeaChartManager.hpp"
#include "../../Astrum/Objects/AstrumRectangleObject.hpp"

namespace InGame {
	class HoldNoteObject : public AstrumRectangleObject
	{
	public:
		HoldNoteObject(const Arcaea::NoteData& data) {
			height = static_cast<float>(data.Data[1] - data.Data[0]);

			SetRectanglePolygons(AstrumRectanglePolygons::MakeShared(
				200,
				height,
				AstrumColor::LightSeaGreen
			));

			Position.SetX(static_cast<float>(LeftX + (NoteWidth / 2.f) + data.Data[2] * NoteWidth));
			Position.SetY(data.GetStartOffset() + height / 2.f);

			//GetRenderPolygonsComponent().CustomShaderPipeline = DataManager::Instance().GetIllusionShader();
			GetRenderPolygonsComponent().SetCustomShaderPipeline(DataManager::Instance().GetIllusionShader());
			AddComponent(DataManager::Instance().GetIllusionConstantBufferComponent(this));
		}

	private:
		float height = 0;
	};
}