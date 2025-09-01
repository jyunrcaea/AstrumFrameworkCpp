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

class Program
{
    friend int main();

private:
    static void Main() {
        AstrumFramework::Initialize();

        AstrumFonts fonts(L"Game/Assets/fonts/Outfit-Medium.ttf");
        auto font = fonts.GetFont(L"Outfit Medium", DWRITE_FONT_WEIGHT_NORMAL, 36.0f);

        auto hello = std::make_shared<AstrumTextObject>(L"Hello Astrum!", font);
        hello->SetColor(AstrumColor{ 1.0f, 0.92f, 0.2f, 1.0f }); // yellow
        hello->SetPivot(0.5f, 0.5f); // center pivot
        hello->SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER, DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        hello->SetPosition( 0, 0, 0 );

        AstrumFramework::GetRootObject()->AddObjects({
            hello
        });
        AstrumFramework::Run();
    }
};
