#include "AstrumGroupObject.hpp"
#include "IAstrumObject.hpp"

AstrumGroupObject::AstrumGroupObject() : objects(std::make_unique<AstrumObjectList>(this)) {
}

//이거는 추가될때마다 Prepare이 호출되도록 해서, 주석처리가 되었고
void AstrumGroupObject::Prepare()
{
    AstrumObject::Prepare();
    //objects->ForEach([](std::shared_ptr<IAstrumObject> obj) {
    //    obj->Prepare();
    //});
}

//이렇게 자식까지 호출되도록 로직을 구성했어요.
void AstrumGroupObject::Update() {
    objects->ForEach([](shared_ptr<IAstrumObject> obj) {
        obj->Update();
    });
}

void AstrumGroupObject::Release() {
    objects->Clear();
}

void AstrumGroupObject::Draw() {
    if (visible) {
        objects->ForEach([](shared_ptr<IAstrumObject> obj) {
            obj->Draw();
        });
    }
}

AstrumObjectList* AstrumGroupObject::GetObjects() { return objects.get(); }

// 이게 AstrumGroupObject의 절대 위치를 업데이트하는 함수입니다.
void AstrumGroupObject::UpdateAbsolutePosition()
{
    AstrumObject::UpdateAbsolutePosition();
    //이건 자식도 같이 업데이트하도록 순회하는 코드
    objects->ForEach([](shared_ptr<IAstrumObject> obj) {
        obj->UpdateAbsolutePosition();
	});
}

void AstrumGroupObject::UpdateAbsoluteRotation()
{
    AstrumObject::UpdateAbsoluteRotation();
    objects->ForEach([](shared_ptr<IAstrumObject> obj) {
        obj->UpdateAbsoluteRotation();
        obj->UpdateAbsolutePosition();
    });
}

void AstrumGroupObject::UpdateAbsoluteScale()
{
    AstrumObject::UpdateAbsoluteScale();
    objects->ForEach([](shared_ptr<IAstrumObject> obj) {
        obj->UpdateAbsoluteScale();
        obj->UpdateAbsolutePosition();
    });
}
