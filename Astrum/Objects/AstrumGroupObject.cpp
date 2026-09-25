#include "AstrumGroupObject.hpp"
#include "IAstrumObject.hpp"
#include "IAstrumGroupObject.hpp"

AstrumGroupObject::AstrumGroupObject() : objects(this) { }

//추가될때마다 Prepare이 호출되도록 해서, 주석처리
void AstrumGroupObject::Prepare()
{
    AstrumObject::Prepare();
    for (IAstrumObject* obj : objects.Iterate()) {
        obj->Prepare();
    }
}

//이렇게 자식까지 호출되도록 로직을 구성했어요.
void AstrumGroupObject::Update() {
    AstrumObject::Update();
    for (IAstrumObject* obj : objects.Iterate()) {
        obj->Update();
    }
}

void AstrumGroupObject::Release() { 
    AstrumObject::Release();
    for (IAstrumObject* obj : objects.Iterate()) {
        obj->Release();
    }
}

void AstrumGroupObject::Draw() {
    if (false == IsVisible()) return;
    AstrumObject::Draw();
    for (IAstrumObject* obj : objects.Iterate()) {
        obj->Draw();
    }
}

IAstrumObjectList& AstrumGroupObject::GetObjectList() { return objects; }

// 이게 AstrumGroupObject의 절대 위치를 업데이트하는 함수입니다.
void AstrumGroupObject::UpdateAbsolutePosition()
{
    AstrumObject::UpdateAbsolutePosition();
    //이건 자식도 같이 업데이트하도록 순회하는 코드
    for (IAstrumObject* obj : objects.Iterate()) {
        obj->UpdateAbsolutePosition();
    }
}

void AstrumGroupObject::UpdateAbsoluteRotation()
{
    AstrumObject::UpdateAbsoluteRotation();
    for (IAstrumObject* obj : objects.Iterate()) {
        obj->UpdateAbsoluteRotation();
        obj->UpdateAbsolutePosition();
    }
}

void AstrumGroupObject::UpdateAbsoluteScale()
{
    AstrumObject::UpdateAbsoluteScale();
    for (IAstrumObject* obj : objects.Iterate()) {
        obj->UpdateAbsoluteScale();
        obj->UpdateAbsolutePosition();
    }
}
