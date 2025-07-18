#pragma once
#include "IAstrumComponent.hpp"

class AstrumComponent : public IAstrumComponent, public std::enable_shared_from_this<AstrumComponent>
{
public:
	virtual ~AstrumComponent() = default;
	virtual void Prepare() override;
	virtual void Update() override;
	virtual void Release() override;

	virtual void SetOwner(IAstrumObject* owner);
	virtual IAstrumObject* GetOwner() const;

private:
	IAstrumObject* owner = nullptr;
};