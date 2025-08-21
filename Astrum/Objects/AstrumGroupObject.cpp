#include "AstrumGroupObject.hpp"
#include "IAstrumObject.hpp"
#include "IAstrumGroupObject.hpp"

AstrumGroupObject::AstrumGroupObject() : objects(this) { }

//추가될때마다 Prepare이 호출되도록 해서, 주석처리
void AstrumGroupObject::Prepare()
{
    AstrumObject::Prepare();
    objects.ForEach([](const std::shared_ptr<IAstrumObject>& obj) {
        obj->Prepare();
    });
}

//이렇게 자식까지 호출되도록 로직을 구성했어요.
void AstrumGroupObject::Update() {
    AstrumObject::Update();
    objects.ForEach([](const std::shared_ptr<IAstrumObject>& obj) {
        obj->Update();
    });
}

void AstrumGroupObject::Release() { 
    AstrumObject::Release();
    objects.ForEach([](const std::shared_ptr<IAstrumObject>& obj) {
        obj->Release();
    });
}

void AstrumGroupObject::Draw() {
    if (false == IsVisible()) return;
    AstrumObject::Draw();
    objects.ForEach([](const std::shared_ptr<IAstrumObject>& obj) {
        obj->Draw();
    });
}

IAstrumObjectList& AstrumGroupObject::GetObjectList() { return objects; }

// 이게 AstrumGroupObject의 절대 위치를 업데이트하는 함수입니다.
void AstrumGroupObject::UpdateAbsolutePosition()
{
    AstrumObject::UpdateAbsolutePosition();
    //이건 자식도 같이 업데이트하도록 순회하는 코드
    objects.ForEach([](const std::shared_ptr<IAstrumObject>& obj) {
        obj->UpdateAbsolutePosition();
	});
}

void AstrumGroupObject::UpdateAbsoluteRotation()
{
    AstrumObject::UpdateAbsoluteRotation();
    objects.ForEach([](const std::shared_ptr<IAstrumObject>& obj) {
        obj->UpdateAbsoluteRotation();
        obj->UpdateAbsolutePosition();
    });
}

void AstrumGroupObject::UpdateAbsoluteScale()
{
    AstrumObject::UpdateAbsoluteScale();
    objects.ForEach([](const std::shared_ptr<IAstrumObject>& obj) {
        obj->UpdateAbsoluteScale();
        obj->UpdateAbsolutePosition();
    });
}
