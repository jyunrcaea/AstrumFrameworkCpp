#pragma once

template<typename T>
class singleton {
protected:
    singleton() = default;
    ~singleton() = default;
    singleton(const singleton&) = delete;
    singleton& operator=(const singleton&) = delete;

public:
    static T& Instance() {
        static T instance;
        return instance;
    }
};