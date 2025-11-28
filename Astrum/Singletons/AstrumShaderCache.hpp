#pragma once
#include <memory>
#include <filesystem>
#include <unordered_map>
#include "AstrumSingleton.hpp"
#include "../Shaders/AstrumShaderSetup.hpp"
#include "../Shaders/AstrumVertexShader.hpp"
#include "../Shaders/AstrumPixelShader.hpp"
#include "../Shaders/AstrumGeometryShader.hpp"
#include "../Shaders/AstrumDomainShader.hpp"
#include "../Shaders/AstrumHullShader.hpp"


class AstrumShaderCacheSingleton : public AstrumSingleton<AstrumShaderCacheSingleton>
{
	friend class AstrumSingleton<AstrumShaderCacheSingleton>;
	friend class AstrumShaderCache;

public:
	/// <summary>
	/// 주어진 경로에서 정점 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 정점 셰이더의 공유 포인터입니다.</returns>
	std::shared_ptr<AstrumVertexShader> LoadVertexShader(const std::filesystem::path& path, const std::string& entry);
	/// <summary>
	/// 주어진 경로에서 픽셀 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 픽셀 셰이더의 공유 포인터입니다.</returns>
	std::shared_ptr<AstrumPixelShader> LoadPixelShader(const std::filesystem::path& path, const std::string& entry);
	/// <summary>
	/// 주어진 경로에서 기하 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 기하 셰이더의 공유 포인터입니다.</returns>
	std::shared_ptr<AstrumGeometryShader> LoadGeometryShader(const std::filesystem::path& path, const std::string& entry);
	/// <summary>
	/// 주어진 경로에서 도메인 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 도메인 셰이더의 공유 포인터입니다.</returns>
	std::shared_ptr<AstrumDomainShader> LoadDomainShader(const std::filesystem::path& path, const std::string& entry);
	/// <summary>
	/// 주어진 경로에서 헐 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 헐 셰이더의 공유 포인터입니다.</returns>
	std::shared_ptr<AstrumHullShader> LoadHullShader(const std::filesystem::path& path, const std::string& entry);
	/// <summary>
	/// 만료된 셰이더 참조를 모두 캐시에서 정리합니다.
	/// </summary>
	void CleanUp();
	/// <summary>
	/// 셰이더가 상대 경로로 로드될 때 사용할 기본 상대 경로입니다. 기본값은 "./Game/Shaders/"입니다.
	/// </summary>
	std::filesystem::path DefaultRelativeDirectory = L"./Game/Shaders/";

private:
	std::unordered_map<std::filesystem::path, std::weak_ptr<AstrumVertexShader>> vertexShaderMap;
	std::unordered_map<std::filesystem::path, std::weak_ptr<AstrumPixelShader>> pixelShaderMap;
	std::unordered_map<std::filesystem::path, std::weak_ptr<AstrumGeometryShader>> geometryShaderMap;
	std::unordered_map<std::filesystem::path, std::weak_ptr<AstrumDomainShader>> domainShaderMap;
	std::unordered_map<std::filesystem::path, std::weak_ptr<AstrumHullShader>> hullShaderMap;
};

class AstrumShaderCache
{
	AstrumShaderCache() = delete;
public:
	/// <summary>
	/// 주어진 경로에서 정점 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 정점 셰이더의 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumVertexShader> LoadVertexShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadVertexShader(path, entry);
	}
	/// <summary>
	/// 주어진 경로에서 픽셀 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 픽셀 셰이더의 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumPixelShader> LoadPixelShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadPixelShader(path, entry);
	}
	/// <summary>
	/// 주어진 경로에서 기하 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 기하 셰이더의 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumGeometryShader> LoadGeometryShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadGeometryShader(path, entry);
	}
	/// <summary>
	/// 주어진 경로에서 도메인 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 도메인 셰더의 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumDomainShader> LoadDomainShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadDomainShader(path, entry);
	}
	/// <summary>
	/// 주어진 경로에서 헐 셰이더를 로드합니다. 캐시에 이미 로드된 셰이더가 있으면 재사용합니다.
	/// </summary>
	/// <param name="path">셰이더 파일의 경로입니다.</param>
	/// <param name="entry">셰이더의 진입점 함수 이름입니다.</param>
	/// <returns>로드된 헐 셰이더의 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumHullShader> LoadHullShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadHullShader(path, entry);
	}
	/// <summary>
	/// 만료된 셰이더 참조를 모두 캐시에서 정리합니다.
	/// </summary>
	static inline void CleanUp() { AstrumShaderCacheSingleton::Instance().CleanUp(); }
	/// <summary>
	/// 셰이더가 상대 경로로 로드될 때 사용할 기본 상대 경로를 반환합니다.
	/// </summary>
	/// <returns>기본 상대 경로입니다.</returns>
	static std::filesystem::path& GetDefaultRelativeDirectory() { return AstrumShaderCacheSingleton::Instance().DefaultRelativeDirectory; }
	/// <summary>
	/// 셰이더가 상대 경로로 로드될 때 사용할 기본 상대 경로를 설정합니다.
	/// </summary>
	/// <param name="path">설정할 기본 상대 경로입니다.</param>
	static void SetDefaultRelativeDirectory(const std::filesystem::path& path) { AstrumShaderCacheSingleton::Instance().DefaultRelativeDirectory = path; }
	/// <summary>
	/// 셰이더가 상대 경로로 로드될 때 사용할 기본 상대 경로를 설정합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="path">설정할 기본 상대 경로입니다.</param>
	static void SetDefaultRelativeDirectory(std::filesystem::path&& path) { AstrumShaderCacheSingleton::Instance().DefaultRelativeDirectory = std::move(path); }
};