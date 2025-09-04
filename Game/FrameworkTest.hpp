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

class Program
{
    friend int main();

private:
    static void Main() {
        AstrumFramework::Initialize();

        AstrumFontsCache::SetDefaultRelativeDirectory(L"Game/Assets/fonts");
        auto helloObject = AstrumTextObject::MakeShared(
            L"Hello Astrum!",
            AstrumFontsCache::Load(L"Outfit-Medium.ttf")->GetFont(L"Outfit", DWRITE_FONT_WEIGHT_NORMAL, 24.0f)
        );
        helloObject->SetAlignment(AstrumTextHorizontalAlignmentType_Center, AstrumTextVerticalAlignmentType_Center);
        //helloObject->SetAlignment(AstrumTextHorizontalAlignmentType_Leading, AstrumTextVerticalAlignmentType_Near);

        AstrumFramework::GetRootObject()->AddObjects({
            helloObject
        });
        AstrumFramework::Run();
    }
};
