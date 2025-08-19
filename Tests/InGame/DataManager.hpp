#pragma once
#include "../Arcaea/ArcaeaChartManager.hpp"
#include "../../Shaders/AstrumVertexShader.hpp"
#include "../../Shaders/AstrumShaderSetup.hpp"
#include "../../Singletons/AstrumSingleton.hpp"
#include "../../Objects/AstrumGroupObject.hpp"
#include "../../Objects/AstrumPolygonsObject.hpp"
#include "../../Objects/AstrumRectangleObject.hpp"

namespace InGame {
	constexpr float LeftX = -400.f;
	constexpr float NoteWidth = 200.f;

	class DataManager : public AstrumSingleton<DataManager>
	{
		friend class AstrumSingleton<DataManager>;
	public:
		

	};
}