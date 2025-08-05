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

	// 등장시켜야 할 노트가 있는지 확인합니다. 있을시 해당 데이터의 포인터, 없을경우 nullptr를 반환합니다.
	Arcaea::ArcaeaNoteData* PoolNextNote() {
		double now = AstrumChrono::GetRunningTime() - playedTime;
		if (nextNoteIndex < chart.Notes.size() && chart.Notes[nextNoteIndex].GetStartOffset() <= now) {
			return &chart.Notes[nextNoteIndex++];
		}
		return nullptr;
	}

	const Arcaea::ArcaeaChart& GetChart() {
		return chart;
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
		Position.SetY(360 + 25.f);
	}

	virtual void Update() override {
		Position.AddY(static_cast<float>(-ChartManager::Instance().GetNoteSpeed() * AstrumChrono::GetDeltaTime()));

		if (GetAbsolutePosition().Y < -360) {
			GetParent()->RemoveObject(shared_from_this());
		}

		AstrumRectangleObject::Update();
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
		Position.SetY(360 + height / 2.f);
	}

	virtual void Update() override {
		Position.AddY(static_cast<float>(-ChartManager::Instance().GetNoteSpeed() * AstrumChrono::GetDeltaTime()));

		if (GetAbsolutePosition().Y + height  < -720) {
			GetParent()->RemoveObject(shared_from_this());
		}

		AstrumRectangleObject::Update();
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

		Position.SetY(360 + height / 2.f);
	}

	virtual void Update() override {
		Position.AddY(static_cast<float>(-ChartManager::Instance().GetNoteSpeed() * AstrumChrono::GetDeltaTime()));

		if (GetAbsolutePosition().Y + height < -720) {
			GetParent()->RemoveObject(shared_from_this());
		}

		AstrumPolygonsObject::Update();
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

		Position.SetY(360 + height / 2.f);
	}

	virtual void Update() override {
		Position.AddY(static_cast<float>(-ChartManager::Instance().GetNoteSpeed() * AstrumChrono::GetDeltaTime()));

		if (GetAbsolutePosition().Y + height < -720) {
			GetParent()->RemoveObject(shared_from_this());
		}

		AstrumPolygonsObject::Update();
	}

private:
	float height = 0;
};

class NoteGroupObject : public AstrumGroupObject
{
public:
	NoteGroupObject() {
		ChartManager::Instance().Setup(L"./Assets/songs/bookmaker/2.aff");
	}

	virtual void Prepare() override {
		ChartManager::Instance().Play(L"./Assets/songs/bookmaker/base.ogg");

		AstrumGroupObject::Prepare();
	}

	virtual void Update() override {
		while (auto data = ChartManager::Instance().PoolNextNote()) {
			switch (data->NoteType) {
			case Arcaea::ArcaeaNoteType_Tap:
				AddObject(std::make_shared<NoteObject>(*data));
				break;
			case Arcaea::ArcaeaNoteType_Hold:
				AddObject(std::make_shared<HoldNoteObject>(*data));
				break;
			case Arcaea::ArcaeaNoteType_Arc:
				AddObject(std::make_shared<ArcObject>(*data));
				break;
			case Arcaea::ArcaeaNoteType_Trace:
				AddObject(std::make_shared<TraceObject>(*data));
				break;
			default:
				break;
			}
		}

		AstrumGroupObject::Update();
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
			default:
				break;
			}
			std::cout << "Data:";
			for (auto v : info.Data) {
				std::cout << ' ' << v;
			}
			std::cout << std::endl;
		}
#endif

		AstrumFramework::Run();
	}
};