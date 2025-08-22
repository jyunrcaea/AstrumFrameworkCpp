#pragma once
#include <vector>
#include <memory>
#include <functional>
#include "../Components/IAstrumComponent.hpp"

namespace Astrum {
	struct IComponent;
	// 여러 Component를 관리해줄 컬렉션의 기본 추상 인터페이스.
	struct IComponentList
	{
		virtual ~IComponentList() = default;

		// 컴포넌트 추가 (중복 또는 nullptr는 false 반환)
		virtual bool Add(const std::shared_ptr<IComponent>& component) = 0;
		// 컴포넌트 제거 (존재하지 않거나 nullptr는 false 반환)
		virtual bool Remove(const std::shared_ptr<IComponent>& component) = 0;
		// 모든 컴포넌트 제거
		virtual void Clear() = 0;

		virtual void Prepare() = 0;
		virtual void Update() = 0;
		virtual void Release() = 0;

		// 컬렉션 순회
		virtual void ForEach(const std::function<void(const std::shared_ptr<IComponent>&)>& func) = 0;
		// 복사본 생성
		virtual std::vector<std::shared_ptr<IComponent>> ToArray() const = 0;
	};
}