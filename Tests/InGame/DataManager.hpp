#pragma once
#include "../Arcaea/ArcaeaChartManager.hpp"
#include "../../Shaders/AstrumVertexShader.hpp"
#include "../../Shaders/AstrumShaderSetup.hpp"
#include "../../Singletons/AstrumSingleton.hpp"
#include "../../Objects/AstrumGroupObject.hpp"
#include "../../Objects/AstrumPolygonsObject.hpp"
#include "../../Objects/AstrumRectangleObject.hpp"

namespace InGame {
	constexpr float NoteWidth = 200.f;
	constexpr float LeftX = NoteWidth * -3.f;

	class DataManager : public AstrumSingleton<DataManager>
	{
		friend class AstrumSingleton<DataManager>;
	public:
		

	};
}