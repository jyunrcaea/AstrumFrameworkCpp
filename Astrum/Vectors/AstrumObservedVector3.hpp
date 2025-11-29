#pragma once

#include "AstrumVector3.hpp"
#include <functional>

/// <summary>
/// 값 변경을 감지하는 3D 벡터입니다.
/// 벡터의 X, Y, Z 값이 변경될 때마다 콜백 함수를 호출합니다.
/// 게임 객체의 트리 구조에서 부모의 변경(크기, 회전, 좌표)을 자식에게 전파할 때 사용됩니다.
/// 예: 부모의 스케일을 2로 키우면 자식도 크기가 2배가 되고, 
///     부모가 X축을 1칸 이동하면 자식은 실제로 2칸을 이동합니다.
/// </summary>
class AstrumObservedVector3 {
public:
    /// <summary>
    /// 값 변경 시 호출될 콜백 함수 타입입니다.
    /// </summary>
    using Callback = std::function<void()>;

    /// <summary>
    /// 이동 생성자입니다.
    /// </summary>
    /// <param name="vec3">이동할 벡터입니다.</param>
    AstrumObservedVector3(AstrumObservedVector3&& vec3) noexcept;
    /// <summary>
    /// 콜백 함수를 지정하여 생성합니다.
    /// 벡터는 (0, 0, 0)으로 초기화됩니다.
    /// </summary>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다.</param>
    explicit AstrumObservedVector3(const Callback& onChange) noexcept;
    /// <summary>
    /// X, Y, Z 값과 콜백 함수를 지정하여 생성합니다.
    /// </summary>
    /// <param name="x">X 좌표입니다.</param>
    /// <param name="y">Y 좌표입니다.</param>
    /// <param name="z">Z 좌표입니다.</param>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다. 기본값은 nullptr입니다.</param>
    AstrumObservedVector3(float x, float y, float z, const Callback& onChange = {}) noexcept;
    /// <summary>
    /// 다른 벡터와 콜백 함수를 지정하여 생성합니다.
    /// 부모-자식 관계에서 자식의 위치/크기/회전을 추적할 때 유용합니다.
    /// </summary>
    /// <param name="v">초기 벡터 값입니다.</param>
    /// <param name="onChange">값이 변경될 때 호출될 콜백 함수입니다. 기본값은 nullptr입니다.</param>
    AstrumObservedVector3(const AstrumVector3& v, const Callback& onChange = {}) noexcept;

    /// <summary>
    /// AstrumVector3으로 암시적 변환합니다.
    /// </summary>
    operator AstrumVector3() const noexcept;

    /// <summary>
    /// X 값을 반환합니다.
    /// </summary>
    /// <returns>X 좌표입니다.</returns>
    float GetX() const noexcept;
    /// <summary>
    /// Y 값을 반환합니다.
    /// </summary>
    /// <returns>Y 좌표입니다.</returns>
    float GetY() const noexcept;
    /// <summary>
    /// Z 값을 반환합니다.
    /// </summary>
    /// <returns>Z 좌표입니다.</returns>
    float GetZ() const noexcept;

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
    /// X 값을 더합니다. 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    /// <param name="x">더할 X 값입니다.</param>
    void AddX(float x);
    /// <summary>
    /// Y 값을 더합니다. 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    /// <param name="y">더할 Y 값입니다.</param>
    void AddY(float y);
    /// <summary>
    /// Z 값을 더합니다. 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    /// <param name="z">더할 Z 값입니다.</param>
    void AddZ(float z);

    /// <summary>
    /// 벡터 값을 완전히 재설정합니다. 콜백을 호출합니다.
    /// </summary>
    /// <param name="v">설정할 벡터 값입니다.</param>
    void Reset(const AstrumVector3& v);
    /// <summary>
    /// 벡터 값을 이동으로 완전히 재설정합니다. 콜백을 호출합니다.
    /// </summary>
    /// <param name="v">설정할 벡터 값입니다.</param>
    void Reset(AstrumVector3&& v);
    /// <summary>
    /// 다른 AstrumObservedVector3의 값으로 재설정합니다. 콜백을 호출합니다.
    /// </summary>
    /// <param name="v">설정할 벡터 값입니다.</param>
    void Reset(const AstrumObservedVector3& v);
    /// <summary>
    /// 벡터 값을 X, Y, Z로 완전히 재설정합니다. 콜백을 호출합니다.
    /// NaN 값을 사용하여 특정 축만 선택적으로 설정할 수 있습니다.
    /// </summary>
    /// <param name="x">설정할 X 값입니다.</param>
    /// <param name="y">설정할 Y 값입니다.</param>
    /// <param name="z">설정할 Z 값입니다. NaN이면 기존 Z 값이 유지됩니다. 기본값은 NAN입니다.</param>
    void Reset(float x, float y, float z = NAN);

    /// <summary>
    /// 두 개의 AstrumObservedVector3을 더합니다.
    /// </summary>
    AstrumVector3 operator+(const AstrumObservedVector3& o) const noexcept;
    /// <summary>
    /// AstrumObservedVector3에서 다른 AstrumObservedVector3을 뺍니다.
    /// </summary>
    AstrumVector3 operator-(const AstrumObservedVector3& o) const noexcept;
    /// <summary>
    /// AstrumObservedVector3에 스칼라값을 곱합니다.
    /// </summary>
    AstrumVector3 operator*(float scalar) const noexcept;
    /// <summary>
    /// AstrumObservedVector3을 스칼라값으로 나눕니다.
    /// </summary>
    AstrumVector3 operator/(float scalar) const noexcept;

    /// <summary>
    /// 두 개의 AstrumObservedVector3의 성분별 곱셈을 합니다.
    /// </summary>
    AstrumVector3 operator*(const AstrumObservedVector3& o) const noexcept;
    /// <summary>
    /// AstrumObservedVector3의 성분별 나눗셈을 합니다.
    /// </summary>
    AstrumVector3 operator/(const AstrumObservedVector3& o) const noexcept;

    /// <summary>
    /// AstrumVector3을 더합니다.
    /// </summary>
    AstrumVector3 operator+(const AstrumVector3& v) const noexcept;
    /// <summary>
    /// AstrumVector3을 뺍니다.
    /// </summary>
    AstrumVector3 operator-(const AstrumVector3& v) const noexcept;
    /// <summary>
    /// AstrumVector3의 성분별 곱셈을 합니다.
    /// </summary>
    AstrumVector3 operator*(const AstrumVector3& v) const noexcept;
    /// <summary>
    /// AstrumVector3의 성분별 나눗셈을 합니다.
    /// </summary>
    AstrumVector3 operator/(const AstrumVector3& v) const noexcept;

    /// <summary>
    /// 다른 AstrumObservedVector3을 더합니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector3& operator+=(const AstrumObservedVector3& o);
    /// <summary>
    /// 다른 AstrumObservedVector3을 뺍니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector3& operator-=(const AstrumObservedVector3& o);
    /// <summary>
    /// 스칼라값을 곱합니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector3& operator*=(float scalar);
    /// <summary>
    /// 스칼라값으로 나눕니다. (복합 할당)
    /// 이 벡터의 값이 변경되면 콜백을 호출합니다.
    /// </summary>
    AstrumObservedVector3& operator/=(float scalar);

private:
    /// <summary>
    /// 현재 벡터 값입니다.
    /// </summary>
    AstrumVector3 value{ 0.0f, 0.0f, 0.0f };
    /// <summary>
    /// 값 변경 시 호출될 콜백 함수입니다.
    /// </summary>
    Callback onChange;

    /// <summary>
    /// 콜백 함수를 호출합니다. 값이 변경될 때 사용됩니다.
    /// </summary>
    void Notify();
};