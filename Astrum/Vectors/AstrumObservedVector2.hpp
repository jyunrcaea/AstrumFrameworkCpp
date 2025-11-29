#pragma once
#include "AstrumVector2.hpp"
#include <functional>

/// <summary>
/// 값 변경을 감지하는 2D 벡터입니다.
/// 벡터의 X, Y 값이 변경될 때마다 콜백 함수를 호출합니다.
/// 게임 객체의 트리 구조에서 부모의 변경을 자식에게 전파할 때 유용합니다.
/// </summary>
class AstrumObservedVector2 {
public:
    /// <summary>
    /// 값 변경 시 호출될 콜백 함수 타입입니다.
    /// </summary>
    using Callback = std::function<void()>;

    /// <summary>
    /// 기본 생성자입니다. (0, 0)으로 초기화되고 콜백은 없습니다.
    /// </summary>
    constexpr AstrumObservedVector2();
    /// <summary>
    /// 콜백 함수를 지정하여 생성합니다.
    /// </summary>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다.</param>
    explicit AstrumObservedVector2(const Callback& onChange);
    /// <summary>
    /// X, Y 값과 콜백 함수를 지정하여 생성합니다.
    /// </summary>
    /// <param name="x">X 좌표입니다.</param>
    /// <param name="y">Y 좌표입니다.</param>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다. 기본값은 nullptr입니다.</param>
    AstrumObservedVector2(float x, float y, const Callback& onChange = {});
    /// <summary>
    /// 다른 벡터와 콜백 함수를 지정하여 생성합니다.
    /// </summary>
    /// <param name="v">초기 벡터 값입니다.</param>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다. 기본값은 nullptr입니다.</param>
    AstrumObservedVector2(const AstrumVector2& v, const Callback& onChange = {});

    /// <summary>
    /// AstrumVector2로 암시적 변환합니다.
    /// </summary>
    operator AstrumVector2() const;

    /// <summary>
    /// X 값을 반환합니다.
    /// </summary>
    /// <returns>X 좌표입니다.</returns>
    float GetX() const;
    /// <summary>
    /// Y 값을 반환합니다.
    /// </summary>
    /// <returns>Y 좌표입니다.</returns>
    float GetY() const;

    /// <summary>
    /// X 값을 설정합니다. 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    /// <param name="x">설정할 X 값입니다.</param>
    void SetX(float x);
    /// <summary>
    /// Y 값을 설정합니다. 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    /// <param name="y">설정할 Y 값입니다.</param>
    void SetY(float y);

    /// <summary>
    /// 벡터 값을 완전히 재설정합니다. 콜백을 호출합니다.
    /// </summary>
    /// <param name="v">설정할 벡터 값입니다.</param>
    void Reset(const AstrumVector2& v);
    /// <summary>
    /// 벡터 값을 X, Y로 완전히 재설정합니다. 콜백을 호출합니다.
    /// </summary>
    /// <param name="x">설정할 X 값입니다.</param>
    /// <param name="y">설정할 Y 값입니다.</param>
    void Reset(float x, float y);

    /// <summary>
    /// 두 개의 AstrumObservedVector2를 더합니다.
    /// </summary>
    AstrumVector2 operator+(const AstrumObservedVector2& o) const;
    /// <summary>
    /// AstrumObservedVector2에서 다른 AstrumObservedVector2를 뺍니다.
    /// </summary>
    AstrumVector2 operator-(const AstrumObservedVector2& o) const;
    /// <summary>
    /// AstrumObservedVector2에 스칼라값을 곱합니다.
    /// </summary>
    AstrumVector2 operator*(float scalar) const;
    /// <summary>
    /// AstrumObservedVector2를 스칼라값으로 나눕니다.
    /// </summary>
    AstrumVector2 operator/(float scalar) const;

    /// <summary>
    /// 다른 AstrumObservedVector2를 더합니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector2& operator+=(const AstrumObservedVector2& other);
    /// <summary>
    /// 다른 AstrumObservedVector2를 뺍니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector2& operator-=(const AstrumObservedVector2& other);
    /// <summary>
    /// 스칼라값을 곱합니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector2& operator*=(float scalar);
    /// <summary>
    /// 스칼라값으로 나눕니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector2& operator/=(float scalar);

    /// <summary>
    /// AstrumVector2를 더합니다.
    /// </summary>
    AstrumVector2 operator+(const AstrumVector2& v) const;
    /// <summary>
    /// AstrumVector2를 뺍니다.
    /// </summary>
    AstrumVector2 operator-(const AstrumVector2& v) const;

private:
    /// <summary>
    /// 현재 벡터 값입니다.
    /// </summary>
    AstrumVector2 value_{ 0.0f, 0.0f };
    /// <summary>
    /// 값 변경 시 호출될 콜백 함수입니다.
    /// </summary>
    Callback onChange_;

    /// <summary>
    /// 콜백 함수를 호출합니다. 값이 변경될 때 사용됩니다.
    /// </summary>
    void Notify();
};