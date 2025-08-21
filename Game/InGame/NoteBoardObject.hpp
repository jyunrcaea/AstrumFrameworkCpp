#pragma once
#include "DataManager.hpp"
#include "../../Astrum/Objects/AstrumRectangleObject.hpp"

namespace InGame
{
	class NoteBoardObject : public AstrumRectangleObject
	{
	public:
		NoteBoardObject() : AstrumRectangleObject(NoteWidth * 4.f, static_cast<float>(AstrumWindow::GetHeight()), AstrumColor::LightGray) {
			//GetRenderPolygonsComponent().CustomShaderPipeline = DataManager::Instance().GetIllusionShader();
			GetRenderPolygonsComponent().SetCustomShaderPipeline(DataManager::Instance().GetIllusionShader());
			AddComponent(DataManager::Instance().GetIllusionConstantBufferComponent(this));
		}
	};
}