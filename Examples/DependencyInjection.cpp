#include "../Astrum/Vectors/AstrumVector4.hpp"
#include "../Astrum/Units/AstrumColor.hpp"
#include "../Astrum/Singletons/AstrumFramework.hpp"
#include "../Astrum/Singletons/AstrumRawInput.hpp"
#include "../Astrum/Objects/AstrumRectangleObject.hpp"
#include "../Astrum/Components/AstrumStateComponent.hpp"
#include "../Astrum/Components/AstrumAnimatorComponent.hpp"
#include "../Astrum/Animations/AstrumMovementAnimator.hpp"
#include "../Astrum/Animations/AstrumAnimationFunctions.hpp"
#include "../Astrum/Singletons/AstrumKeyBinder.hpp"
#include "../Astrum/Objects/AstrumMaterialObject.hpp"
#include "../Astrum/Objects/AstrumTextObject.hpp"
#include "../Astrum/Resources/AstrumFonts.hpp"
#include "../Astrum/Singletons/AstrumFontsCache.hpp"
#include "../Astrum/DI/AstrumDependencyInjectionService.hpp"

namespace DependencyInjection {
    class ChildChildObject : public AstrumObject {
    public:
        std::string*& title = DI.Reserve<std::string>("title");

        virtual void Prepare() override {
            std::cout << std::format("[{}] Before dependency injection: {}\n", __FUNCTION__, title == nullptr ? "(nullptr)" : *title);

            AstrumObject::Prepare();

            std::cout << std::format("[{}] After dependency injection: {}\n", __FUNCTION__, title == nullptr ? "(nullptr)" : *title);
        }
    };

    class ChildObject : public AstrumGroupObject {
    public:
        std::string*& title = DI.Reserve<std::string>("title");

        virtual void Prepare() override {
            std::cout << std::format("[{}] Before dependency injection: {}\n", __FUNCTION__, title == nullptr ? "(nullptr)" : *title);

            AstrumGroupObject::Prepare();

            std::cout << std::format("[{}] After dependency injection: {}\n", __FUNCTION__, title == nullptr ? "(nullptr)" : *title);

            AddObject(std::make_shared<ChildChildObject>());
        }
    };

    class ParentObject : public AstrumGroupObject {
    public:
        std::string title = "Dependency Injection test";

        virtual void Prepare() override {
            AstrumGroupObject::Prepare();

            DI.Add("title", title);

            AddObject(std::make_shared<ChildObject>());
        }
    };

    class Program
    {
        friend int main();

    private:
        static int Main() {
            AstrumFramework::Initialize();
            AstrumFramework::GetRootObject()->AddObjects({
                std::make_shared<ParentObject>()
                });
            return AstrumFramework::Run();
        }
    };
}