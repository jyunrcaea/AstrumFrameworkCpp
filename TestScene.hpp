#include "AstrumChrono.hpp"
#include "AstrumDirectInput.hpp"
#include "AstrumGroupObject.hpp"
#include "AstrumMaterialObject.hpp"

class DotnetBot : public AstrumMaterialObject {
public:
	DotnetBot() : AstrumMaterialObject(AstrumTexture::MakeShared(L"./Resource/dotnetbot.png")) {

	}

	virtual void Update() override {
		const float delta = static_cast<float>(AstrumChrono::Instance().GetDeltaTime());
		
		AstrumVector3 movement{};
		if (AstrumDirectInput::Instance().IsKeyPressed(DIK_W)) movement.Y++;
		if (AstrumDirectInput::Instance().IsKeyPressed(DIK_S)) movement.Y--;
		if (AstrumDirectInput::Instance().IsKeyPressed(DIK_A)) movement.X--;
		if (AstrumDirectInput::Instance().IsKeyPressed(DIK_D)) movement.X++;
		if (movement.X > 0) GetMaterial()->SetFlip(AstrumMaterialFlipType_None);
		else if (movement.X < 0) GetMaterial()->SetFlip(AstrumMaterialFlipType_X);
		movement.Normalize();
		Position += movement * delta * 614.0f;


		if (AstrumDirectInput::Instance().IsKeyPressed(DIK_Q)) Rotation.AddZ(delta * 200.f);
		if (AstrumDirectInput::Instance().IsKeyPressed(DIK_E)) Rotation.AddZ(delta * -200.f);

		AstrumMaterialObject::Update();
	}
};

class TestScene : public AstrumGroupObject {
public:
	TestScene() {
		AddObject(std::make_shared<DotnetBot>());
	}
};