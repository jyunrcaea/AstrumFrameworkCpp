#include <iostream>
#include "../Astrum/Singletons/AstrumChrono.hpp"
#include "../Astrum/Objects/AstrumObject.hpp"
#include "../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../Astrum/Objects/AstrumGroupObject.hpp"
#include "../Astrum/Singletons/AstrumFramework.hpp"
#include "../Astrum/Singletons/AstrumTextureCache.hpp"
#include "../Astrum/Singletons/AstrumSoundCache.hpp"
#include "../Astrum/Singletons/AstrumFontsCache.hpp"
#include "../Astrum/Resources/AstrumTexture.hpp"
#include "../Astrum/Resources/AstrumSound.hpp"
#include "../Astrum/Resources/AstrumFonts.hpp"


namespace LifeCycle {
	class TestObject1 : public AstrumObject
	{
	public:
		TestObject1() : AstrumObject() {
			std::cout << "Constructer" << std::endl;
		}
		virtual void Prepare() override {
			AstrumObject::Prepare();
			std::cout << "Prepared!" << std::endl;
		}
		virtual void Update() override {
			AstrumObject::Update();
			std::cout << "Updated! Delta time: " << AstrumChrono::GetDeltaTime() << std::endl;
		}
		virtual void Release() override {
			AstrumObject::Release();
			std::cout << "Released!" << std::endl;
		}
		virtual void Draw() override {
			AstrumObject::Draw();
			std::cout << "Drawn!" << std::endl;
		}

		void Test() {
			auto group = std::make_shared<AstrumGroupObject>();
			group->AddObjects({
				std::make_shared<AstrumObject>(),
				std::make_shared<AstrumGroupObject>()
			});
			AstrumFramework::SetRootObject(group);
		}
	};

	class TestObject2 : public AstrumMaterialObject {
	public:
		TestObject2() : AstrumMaterialObject() {
			auto texture = std::make_shared<AstrumTexture>("image.png");
			auto texture2 = AstrumTextureCache::Load("image.jpg");

			auto sound = std::make_shared<AstrumSound>("sound.wav");
			auto sound2 = AstrumSoundCache::Load("sound.mp3");

			auto fonts = std::make_shared<AstrumFonts>("fonts.ttf");
			auto fonts2 = AstrumFontsCache::Load("fonts2.otf");
		}
		virtual void Prepare() override {
			AstrumMaterialObject::Prepare();
			std::cout << "Prepared2!" << std::endl;
		}
		virtual void Update() override {
			AstrumMaterialObject::Update();
			std::cout << "Updated2! Delta time: " << AstrumChrono::GetDeltaTime() << std::endl;
		}
		virtual void Release() override {
			AstrumMaterialObject::Release();
			std::cout << "Released2!" << std::endl;
		}
		virtual void Draw() override {
			AstrumMaterialObject::Draw();
			std::cout << "Drawn2!" << std::endl;
		}
	};

	class Program
	{
		friend int main();

	private:
		static int Main() {
			AstrumFramework::Initialize();
			AstrumFramework::GetRootObject()->AddObjects({
				std::make_shared<TestObject1>(),
				std::make_shared<TestObject2>()
			});
			return AstrumFramework::Run();
		}
	};
}