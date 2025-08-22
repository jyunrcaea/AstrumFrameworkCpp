#include "AstrumGroupObject.hpp"
#include "IAstrumObject.hpp"
#include "IAstrumGroupObject.hpp"

namespace Astrum
{
	GroupObject::GroupObject() : objects(this) { }

	//추가될때마다 Prepare이 호출되도록 해서, 주석처리
	void GroupObject::Prepare()
	{
		Object::Prepare();
		objects.ForEach([](const std::shared_ptr<IObject>& obj) {
			obj->Prepare();
		});
	}

	//이렇게 자식까지 호출되도록 로직을 구성했어요.
	void GroupObject::Update() {
		Object::Update();
		objects.ForEach([](const std::shared_ptr<IObject>& obj) {
			obj->Update();
		});
	}

	void GroupObject::Release() {
		Object::Release();
		objects.ForEach([](const std::shared_ptr<IObject>& obj) {
			obj->Release();
		});
	}

	void GroupObject::Draw() {
		if (false == IsVisible()) return;
		Object::Draw();
		objects.ForEach([](const std::shared_ptr<IObject>& obj) {
			obj->Draw();
		});
	}

	IObjectList& GroupObject::GetObjectList() { return objects; }

	// 이게 GroupObject의 절대 위치를 업데이트하는 함수입니다.
	void GroupObject::UpdateAbsolutePosition()
	{
		Object::UpdateAbsolutePosition();
		//이건 자식도 같이 업데이트하도록 순회하는 코드
		objects.ForEach([](const std::shared_ptr<IObject>& obj) {
			obj->UpdateAbsolutePosition();
		});
	}

	void GroupObject::UpdateAbsoluteRotation()
	{
		Object::UpdateAbsoluteRotation();
		objects.ForEach([](const std::shared_ptr<IObject>& obj) {
			obj->UpdateAbsoluteRotation();
			obj->UpdateAbsolutePosition();
		});
	}

	void GroupObject::UpdateAbsoluteScale()
	{
		Object::UpdateAbsoluteScale();
		objects.ForEach([](const std::shared_ptr<IObject>& obj) {
			obj->UpdateAbsoluteScale();
			obj->UpdateAbsolutePosition();
		});
	}
}
