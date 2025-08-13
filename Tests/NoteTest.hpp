#pragma once
#include <iostream>
#include <format>
#include <string>
#include <vector>
#include "../Vectors/AstrumVector4.hpp"
#include "../Units/AstrumColor.hpp"
#include "../Singletons/AstrumFramework.hpp"
#include "../Singletons/AstrumDirectInput.hpp"
#include "../Objects/AstrumRectangleObject.hpp"
#include "../Objects/AstrumPolygonsObject.hpp"
#include "../Components/AstrumStateComponent.hpp"
#include "../Components/AstrumAnimatorComponent.hpp"
#include "../Animations/AstrumMovementAnimator.hpp"
#include "../Animations/AstrumAnimationFunctions.hpp"
#include "../Singletons/AstrumKeyBinder.hpp"
#include "../Resources/AstrumSound.hpp"
#include "../Arcaea/ArcaeaChartParser.hpp"

class ChartManager : public AstrumSingleton<ChartManager>
{
	friend class AstrumSingleton<ChartManager>;

public:
	void Setup(const std::filesystem::path& filePath) {
		Arcaea::ArcaeaChartParser parser(filePath);
		chart = parser.ToParse();
		nextNoteIndex = 0;
	}

	void Play(const std::filesystem::path& audioPath) {
		AstrumSound(audioPath).Play();
		playedTime = AstrumChrono::GetRunningTime() - (chart.AudioOffset * 0.001);
	}

	const Arcaea::ArcaeaChart& GetChart() {
		return chart;
	}

	const std::vector<Arcaea::ArcaeaNoteData>& GetNoteData() const {
		return chart.Notes;
	}

	float GetCurrentOffset() const {
		return static_cast<float>(AstrumChrono::GetRunningTime() - playedTime) * 1000.f;
	}

	float GetNoteSpeed() const {
		return noteSpeed;
	}

private:
	Arcaea::ArcaeaChart chart;
	int nextNoteIndex = 0;
	double playedTime = -1.f;
	float noteSpeed = 1000;
};

class NoteObject : public AstrumRectangleObject
{
public:
	NoteObject(const Arcaea::ArcaeaNoteData& data) : AstrumRectangleObject(200, 40, AstrumColor::SkyBlue) {
		Position.SetX(static_cast<float>(-500 + data.Data[1] * 200));
		Position.SetY(data.GetStartOffset() + 20);
	}
};

class HoldNoteObject : public AstrumRectangleObject
{
public:
	HoldNoteObject(const Arcaea::ArcaeaNoteData& data) {
		height = static_cast<float>(data.Data[1] - data.Data[0]);

		SetRectanglePolygons(AstrumRectanglePolygons::MakeShared(
			200,
			height,
			AstrumColor::LightSeaGreen
		));

		Position.SetX(static_cast<float>(-500 + data.Data[2] * 200));
		Position.SetY(data.GetStartOffset() + height / 2.f);
	}

private:
	float height = 0;
};

class ArcObject : public AstrumPolygonsObject
{
public:
	ArcObject(const Arcaea::ArcaeaNoteData& data) {
		height = static_cast<float>(data.Data[1] - data.Data[0]);
		const float startX = static_cast<float>(-400 + 800 * data.Data[2]) * 0.8f;
		const float endX = static_cast<float>(-400 + 800 * data.Data[3]) * 0.8f;

		std::vector<AstrumVertexColor> vertices = {
			AstrumVertexColor({startX - 15, height * 0.5f }, AstrumColor::MintGreen),
			AstrumVertexColor({startX + 15, height * 0.5f }, AstrumColor::MintGreen),
			AstrumVertexColor({ endX - 15, height * -0.5f }, AstrumColor::MintGreen),
			AstrumVertexColor({ endX + 15, height * -0.5f }, AstrumColor::MintGreen),
		};
		SetPolygons(AstrumPolygons::MakeShared(
			vertices,
			{0,1,2,1,3,2}
		));

		Position.SetY(data.GetStartOffset() + height / 2.f);
	}

private:
	float height = 0;
};

class TraceObject : public AstrumPolygonsObject
{
public:
	TraceObject(const Arcaea::ArcaeaNoteData& data) {
		height = static_cast<float>(data.Data[1] - data.Data[0]);
		const float startX = static_cast<float>(-400 + 800 * data.Data[2]);
		const float endX = static_cast<float>(-400 + 800 * data.Data[3]);

		std::vector<AstrumVertexColor> vertices = {
			AstrumVertexColor({ startX - 10, height * 0.5f }, AstrumColor::Periwinkle),
			AstrumVertexColor({ startX + 10, height * 0.5f }, AstrumColor::Periwinkle),
			AstrumVertexColor({ endX - 10, height * -0.5f }, AstrumColor::Periwinkle),
			AstrumVertexColor({ endX + 10, height * -0.5f }, AstrumColor::Periwinkle),
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

class SkyNoteObject : public AstrumRectangleObject
{
public:
	SkyNoteObject(const Arcaea::ArcaeaNoteData& data) : AstrumRectangleObject(200, 30, AstrumColor::Aquamarine) {
		const float startX = static_cast<float>(-400 + 800 * data.Data[1]);
		Position.SetX(startX);

		Position.SetY(data.GetStartOffset() + 15);
	}

private:
	float height = 0;
};

class NoteGroupObject : public AstrumGroupObject
{
public:
	NoteGroupObject() {
		ChartManager::Instance().Setup(L"./Assets/songs/goodtek/2.aff");
		Position.SetY(2000.f);
	}

	virtual void Prepare() override {
		for (const auto& data : ChartManager::Instance().GetNoteData()) {
			GenerateNote(data);
		}
		//ChartManager::Instance().Play(L"./Assets/songs/goodtek/base.ogg");

		AstrumGroupObject::Prepare();
	}

	virtual void Update() override {
		//if (AstrumDirectInput::IsKeyPressed(DIK_W)) Position.AddY(-10000 * AstrumChrono::GetDeltaTime());
		//if (AstrumDirectInput::IsKeyPressed(DIK_S)) Position.AddY(10000 * AstrumChrono::GetDeltaTime());

		Position.AddY(static_cast<float>(AstrumChrono::GetDeltaTime() * -1000.0));

		AstrumGroupObject::Update();
	}

private:
	void GenerateNote(const Arcaea::ArcaeaNoteData& data) {
		switch (data.NoteType) {
		case Arcaea::ArcaeaNoteType_Tap:
			AddObject(std::make_shared<NoteObject>(data));
			break;
		case Arcaea::ArcaeaNoteType_Hold:
			AddObject(std::make_shared<HoldNoteObject>(data));
			break;
		case Arcaea::ArcaeaNoteType_Arc:
			AddObject(std::make_shared<ArcObject>(data));
			break;
		case Arcaea::ArcaeaNoteType_Trace:
			AddObject(std::make_shared<TraceObject>(data));
			break;
		case Arcaea::ArcaeaNoteType_ArcTap:
			AddObject(std::make_shared<SkyNoteObject>(data));
			break;
		}
	}
};

class Program
{
	friend int main();

private:
	void Main() {
		AstrumFramework::Initialize();
		auto noteGroup = std::make_shared<NoteGroupObject>();
		AstrumFramework::GetRootObject()->AddObject(noteGroup);
		
#if _DEBUG
		const auto& patterns = ChartManager::Instance().GetChart();
		std::cout << std::format("Audio Offset: {}\n", patterns.AudioOffset);
		for (auto& info : patterns.Notes) {
			std::cout << "Type: ";
			switch (info.NoteType) {
			case Arcaea::ArcaeaNoteType_Arc:
				std::cout << "Arc";
				break;
			case Arcaea::ArcaeaNoteType_Hold:
				std::cout << "Hold";
				break;
			case Arcaea::ArcaeaNoteType_Tap:
				std::cout << "Tap";
				break;
			case Arcaea::ArcaeaNoteType_Trace:
				std::cout << "Trace";
				break;
			case Arcaea::ArcaeaNoteType_ArcTap:
				std::cout << "ArcTap";
				break;
			default:
				break;
			}
			std::cout << ", Data:";
			for (auto v : info.Data) {
				std::cout << ' ' << v;
			}
			std::cout << std::endl;
		}
#endif

		AstrumFramework::Run();
	}
};