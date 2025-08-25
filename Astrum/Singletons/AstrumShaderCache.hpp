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
	std::shared_ptr<AstrumVertexShader> LoadVertexShader(const std::filesystem::path& path, const std::string& entry);
	std::shared_ptr<AstrumPixelShader> LoadPixelShader(const std::filesystem::path& path, const std::string& entry);
	std::shared_ptr<AstrumGeometryShader> LoadGeometryShader(const std::filesystem::path& path, const std::string& entry);
	std::shared_ptr<AstrumDomainShader> LoadDomainShader(const std::filesystem::path& path, const std::string& entry);
	std::shared_ptr<AstrumHullShader> LoadHullShader(const std::filesystem::path& path, const std::string& entry);
	void CleanUp();
	// 기본적으로 상대 경로로 Game/Shaders 폴더를 사용합니다.
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
	// 주어진 경로의 정점 셰이더를 로드합니다.
	static std::shared_ptr<AstrumVertexShader> LoadVertexShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadVertexShader(path, entry);
	}
	// 주어진 경로의 픽셀 셰이더를 로드합니다.
	static std::shared_ptr<AstrumPixelShader> LoadPixelShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadPixelShader(path, entry);
	}
	// 주어진 경로의 기하 셰이더를 로드합니다.
	static std::shared_ptr<AstrumGeometryShader> LoadGeometryShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadGeometryShader(path, entry);
	}
	// 주어진 경로의 도메인 셰이더를 로드합니다.
	static std::shared_ptr<AstrumDomainShader> LoadDomainShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadDomainShader(path, entry);
	}
	// 주어진 경로의 헐 셰이더를 로드합니다.
	static std::shared_ptr<AstrumHullShader> LoadHullShader(const std::filesystem::path& path, const std::string& entry) {
		return AstrumShaderCacheSingleton::Instance().LoadHullShader(path, entry);
	}
	// 만료된 셰이더 참조를 모두 정리합니다.
	static inline void CleanUp() { AstrumShaderCacheSingleton::Instance().CleanUp(); }
	// 셰이더가 상대 경로로 로드될때 사용할 기준 상대경로를 반환합니다.
	static std::filesystem::path& GetDefaultRelativeDirectory() { return AstrumShaderCacheSingleton::Instance().DefaultRelativeDirectory; }
	// 셰이더가 상대 경로로 로드될때 사용할 기준 상대경로를 설정합니다.
	static void SetDefaultRelativeDirectory(const std::filesystem::path& path) { AstrumShaderCacheSingleton::Instance().DefaultRelativeDirectory = path; }
	static void SetDefaultRelativeDirectory(std::filesystem::path&& path) { AstrumShaderCacheSingleton::Instance().DefaultRelativeDirectory = std::move(path); }
};

