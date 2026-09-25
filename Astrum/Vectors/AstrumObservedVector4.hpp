#pragma once
#include "AstrumVector4.hpp"
#include <functional>

/// <summary>
/// 값 변경을 감지하는 4D 벡터입니다.
/// 벡터의 X, Y, Z, W 값이 변경될 때마다 콜백 함수를 호출합니다.
/// 주로 색상(RGBA), 사각형 영역, 또는 다른 4D 데이터 추적에 사용됩니다.
/// </summary>
class AstrumObservedVector4 {
public:
    /// <summary>
    /// 값 변경 시 호출될 콜백 함수 타입입니다.
    /// </summary>
    using Callback = std::function<void()>;

    /// <summary>
    /// 기본 생성자입니다. (0, 0, 0, 0)으로 초기화되고 콜백은 없습니다.
    /// </summary>
    AstrumObservedVector4();
    /// <summary>
    /// 콜백 함수를 지정하여 생성합니다.
    /// </summary>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다.</param>
    explicit AstrumObservedVector4(const Callback& onChange);
    /// <summary>
    /// X, Y, Z, W 값과 콜백 함수를 지정하여 생성합니다.
    /// </summary>
    /// <param name="x">X 값입니다.</param>
    /// <param name="y">Y 값입니다.</param>
    /// <param name="z">Z 값입니다.</param>
    /// <param name="w">W 값입니다.</param>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다. 기본값은 nullptr입니다.</param>
    AstrumObservedVector4(float x, float y, float z, float w, const Callback& onChange = {});
    /// <summary>
    /// 다른 벡터와 콜백 함수를 지정하여 생성합니다.
    /// </summary>
    /// <param name="v">초기 벡터 값입니다.</param>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다. 기본값은 nullptr입니다.</param>
    AstrumObservedVector4(const AstrumVector4& v, const Callback& onChange = {});

    /// <summary>
    /// AstrumVector4로 암시적 변환합니다.
    /// </summary>
    operator AstrumVector4() const;

    /// <summary>
    /// X 값을 반환합니다.
    /// </summary>
    /// <returns>X 값입니다.</returns>
    float GetX() const;
    /// <summary>
    /// Y 값을 반환합니다.
    /// </summary>
    /// <returns>Y 값입니다.</returns>
    float GetY() const;
    /// <summary>
    /// Z 값을 반환합니다.
    /// </summary>
    /// <returns>Z 값입니다.</returns>
    float GetZ() const;
    /// <summary>
    /// W 값을 반환합니다.
    /// </summary>
    /// <returns>W 값입니다.</returns>
    float GetW() const;

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
    /// Z 값을 설정합니다. 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    /// <param name="z">설정할 Z 값입니다.</param>
    void SetZ(float z);
    /// <summary>
    /// W 값을 설정합니다. 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    /// <param name="w">설정할 W 값입니다.</param>
    void SetW(float w);

    /// <summary>
    /// 벡터 값을 완전히 재설정합니다. 콜백을 호출합니다.
    /// </summary>
    /// <param name="v">설정할 벡터 값입니다.</param>
    void Reset(const AstrumVector4& v);
    /// <summary>
    /// 벡터 값을 X, Y, Z, W로 완전히 재설정합니다. 콜백을 호출합니다.
    /// </summary>
    /// <param name="x">설정할 X 값입니다.</param>
    /// <param name="y">설정할 Y 값입니다.</param>
    /// <param name="z">설정할 Z 값입니다.</param>
    /// <param name="w">설정할 W 값입니다.</param>
    void Reset(float x, float y, float z, float w);

    /// <summary>
    /// 두 개의 AstrumObservedVector4를 더합니다.
    /// </summary>
    AstrumVector4 operator+(const AstrumObservedVector4& o) const;
    /// <summary>
    /// AstrumObservedVector4에서 다른 AstrumObservedVector4를 뺍니다.
    /// </summary>
    AstrumVector4 operator-(const AstrumObservedVector4& o) const;
    /// <summary>
    /// AstrumObservedVector4에 스칼라값을 곱합니다.
    /// </summary>
    AstrumVector4 operator*(float scalar) const;
    /// <summary>
    /// AstrumObservedVector4를 스칼라값으로 나눕니다.
    /// </summary>
    AstrumVector4 operator/(float scalar) const;

    /// <summary>
    /// 다른 AstrumObservedVector4를 더합니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector4& operator+=(const AstrumObservedVector4& o);
    /// <summary>
    /// 다른 AstrumObservedVector4를 뺍니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector4& operator-=(const AstrumObservedVector4& o);
    /// <summary>
    /// 스칼라값을 곱합니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector4& operator*=(float scalar);
    /// <summary>
    /// 스칼라값으로 나눕니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector4& operator/=(float scalar);

    /// <summary>
    /// AstrumVector4를 더합니다.
    /// </summary>
    AstrumVector4 operator+(const AstrumVector4& v) const;
    /// <summary>
    /// AstrumVector4를 뺍니다.
    /// </summary>
    AstrumVector4 operator-(const AstrumVector4& v) const;

private:
    /// <summary>
    /// 현재 벡터 값입니다.
    /// </summary>
    AstrumVector4 value_{ 0.0f, 0.0f, 0.0f, 0.0f };
    /// <summary>
    /// 값 변경 시 호출될 콜백 함수입니다.
    /// </summary>
    Callback onChange_;

    /// <summary>
    /// 콜백 함수를 호출합니다. 값이 변경될 때 사용됩니다.
    /// </summary>
    void Notify();
};