#pragma once
#include <iostream>
#include "AstrumObject.hpp"
#include "AstrumChrono.hpp"

class MyFrameCounter : public AstrumObject {
public:
    MyFrameCounter() {}

    virtual void Update() override {
        if ((time += static_cast<float>(AstrumChrono::Instance().GetDeltaTime())) >= 1) {
            if ((time -= 1) >= 1) time = 0;
            std::cout << "frame per second: " << count << '\n';
            count = 0;
        }
        count++;
        AstrumObject::Update();
    }

private:
    float time = 0;
    int count = 0;
};