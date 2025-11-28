#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include "AstrumSingleton.hpp"

/// <summary>
/// 키 바인딩을 관리하는 싱글톤 클래스입니다.
/// 게임 액션 이름에 여러 키를 바인딩하고, 키 입력 상태를 추적합니다.
/// </summary>
class AstrumKeyBinderSingleton : public AstrumSingleton<AstrumKeyBinderSingleton>
{
	friend class AstrumSingleton<AstrumKeyBinderSingleton>;
	friend class AstrumKeyBinder;
	/// <summary>
	/// AstrumKeyBinderSingleton을 생성합니다.
	/// </summary>
	AstrumKeyBinderSingleton();

	/// <summary>
	/// 키 바인딩 정보를 저장하는 내부 구조체입니다.
	/// </summary>
	struct KeyBindTag
	{
		/// <summary>
		/// 바인딩된 가상 키 코드들입니다.
		/// </summary>
		std::vector<uint8_t> keys;
		/// <summary>
		/// 현재 누르고 있는 상태입니다.
		/// </summary>
		bool pressed = false;
	};

public:
	/// <summary>
	/// 게임 액션 이름에 키를 바인딩합니다.
	/// 같은 액션에 여러 키를 바인딩할 수 있습니다.
	/// </summary>
	/// <param name="name">게임 액션 이름입니다. (예: "Jump", "Attack")</param>
	/// <param name="key">바인딩할 가상 키 코드입니다.</param>
	/// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
	bool AddKeyBind(const std::string& name, uint8_t key);
	/// <summary>
	/// 게임 액션에서 키를 제거합니다.
	/// </summary>
	/// <param name="name">게임 액션 이름입니다.</param>
	/// <param name="key">제거할 가상 키 코드입니다.</param>
	/// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
	bool RemoveKeyBind(const std::string& name, uint8_t key);
	/// <summary>
	/// 게임 액션에 바인딩된 키 중 하나라도 누르고 있는지 확인합니다.
	/// </summary>
	/// <param name="name">게임 액션 이름입니다.</param>
	/// <returns>해당 액션의 키 중 하나라도 누르고 있으면 true, 아니면 false를 반환합니다.</returns>
	bool IsKeyPressed(const std::string& name);
	/// <summary>
	/// 모든 키 바인딩의 상태를 업데이트합니다.
	/// 매 프레임마다 호출되어야 합니다.
	/// </summary>
	void Update();

private:
	/// <summary>
	/// 게임 액션 이름을 키로 하는 바인딩 맵입니다.
	/// 각 액션은 여러 키를 가질 수 있습니다.
	/// </summary>
	std::unordered_map<std::string, KeyBindTag> name2key;
};

/// <summary>
/// 키 바인딩에 접근하기 위한 정적 인터페이스입니다.
/// AstrumKeyBinderSingleton의 싱글톤 인스턴스에 쉽게 접근할 수 있습니다.
/// </summary>
class AstrumKeyBinder
{
	/// <summary>
	/// 생성자를 삭제하여 인스턴스화를 방지합니다.
	/// </summary>
	AstrumKeyBinder() = delete;
public:
	/// <summary>
	/// 게임 액션 이름에 키를 바인딩합니다.
	/// </summary>
	/// <param name="name">게임 액션 이름입니다. (예: "Jump", "Attack")</param>
	/// <param name="key">바인딩할 가상 키 코드입니다.</param>
	/// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
	inline static bool AddKeyBind(const std::string& name, uint8_t key) { return AstrumKeyBinderSingleton::Instance().AddKeyBind(name, key); }
	/// <summary>
	/// 게임 액션에서 키를 제거합니다.
	/// </summary>
	/// <param name="name">게임 액션 이름입니다.</param>
	/// <param name="key">제거할 가상 키 코드입니다.</param>
	/// <returns>성공하면 true, 실패하면 false를 반환합니다.</returns>
	inline static bool RemoveKeyBind(const std::string& name, uint8_t key) { return AstrumKeyBinderSingleton::Instance().RemoveKeyBind(name, key); }
	/// <summary>
	/// 게임 액션에 바인딩된 키 중 하나라도 누르고 있는지 확인합니다.
	/// </summary>
	/// <param name="name">게임 액션 이름입니다.</param>
	/// <returns>해당 액션의 키 중 하나라도 누르고 있으면 true, 아니면 false를 반환합니다.</returns>
	inline static bool IsKeyPressed(const std::string& name) { return AstrumKeyBinderSingleton::Instance().IsKeyPressed(name); }
	/// <summary>
	/// 모든 키 바인딩의 상태를 업데이트합니다.
	/// 매 프레임마다 호출되어야 합니다.
	/// </summary>
	inline static void Update() { AstrumKeyBinderSingleton::Instance().Update(); }
};