#include "AstrumShaderCache.hpp"

std::shared_ptr<AstrumVertexShader> AstrumShaderCacheSingleton::LoadVertexShader(const std::filesystem::path& path, const std::string& entry) {
	std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
	std::shared_ptr<AstrumVertexShader> shader;
	if (vertexShaderMap.contains(full) && (shader = vertexShaderMap[full].lock())) {
		return shader;
	}
	vertexShaderMap[full] = shader = AstrumVertexShader::MakeShared(full, entry);
	return shader;
}

std::shared_ptr<AstrumPixelShader> AstrumShaderCacheSingleton::LoadPixelShader(const std::filesystem::path& path, const std::string& entry) {
	std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
	std::shared_ptr<AstrumPixelShader> shader;
	if (pixelShaderMap.contains(full) && (shader = pixelShaderMap[full].lock())) {
		return shader;
	}
	pixelShaderMap[full] = shader = AstrumPixelShader::MakeShared(full, entry);
	return shader;
}

std::shared_ptr<AstrumGeometryShader> AstrumShaderCacheSingleton::LoadGeometryShader(const std::filesystem::path& path, const std::string& entry) {
	std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
	std::shared_ptr<AstrumGeometryShader> shader;
	if (geometryShaderMap.contains(full) && (shader = geometryShaderMap[full].lock())) {
		return shader;
	}
	geometryShaderMap[full] = shader = AstrumGeometryShader::MakeShared(full, entry);
	return shader;
}

std::shared_ptr<AstrumDomainShader> AstrumShaderCacheSingleton::LoadDomainShader(const std::filesystem::path& path, const std::string& entry) {
	std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
	std::shared_ptr<AstrumDomainShader> shader;
	if (domainShaderMap.contains(full) && (shader = domainShaderMap[full].lock())) {
		return shader;
	}
	domainShaderMap[full] = shader = AstrumDomainShader::MakeShared(full, entry);
	return shader;
}

std::shared_ptr<AstrumHullShader> AstrumShaderCacheSingleton::LoadHullShader(const std::filesystem::path& path, const std::string& entry) {
	std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
	std::shared_ptr<AstrumHullShader> shader;
	if (hullShaderMap.contains(full) && (shader = hullShaderMap[full].lock())) {
		return shader;
	}
	hullShaderMap[full] = shader = AstrumHullShader::MakeShared(full, entry);
	return shader;
}

void AstrumShaderCacheSingleton::CleanUp() {
	for (auto it = vertexShaderMap.begin(); it != vertexShaderMap.end();) {
		if (it->second.expired()) it = vertexShaderMap.erase(it);
		else ++it;
	}
	for (auto it = pixelShaderMap.begin(); it != pixelShaderMap.end();) {
		if (it->second.expired()) it = pixelShaderMap.erase(it);
		else ++it;
	}
	for (auto it = geometryShaderMap.begin(); it != geometryShaderMap.end();) {
		if (it->second.expired()) it = geometryShaderMap.erase(it);
		else ++it;
	}
	for (auto it = domainShaderMap.begin(); it != domainShaderMap.end();) {
		if (it->second.expired()) it = domainShaderMap.erase(it);
		else ++it;
	}
	for (auto it = hullShaderMap.begin(); it != hullShaderMap.end();) {
		if (it->second.expired()) it = hullShaderMap.erase(it);
		else ++it;
	}
}