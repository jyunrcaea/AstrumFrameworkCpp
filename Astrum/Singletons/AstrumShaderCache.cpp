#include "AstrumShaderCache.hpp"

namespace Astrum {
	std::shared_ptr<VertexShader> ShaderCacheSingleton::LoadVertexShader(const std::filesystem::path& path, const std::string& entry) {
		std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
		std::shared_ptr<VertexShader> shader;
		if (vertexShaderMap.contains(full) && (shader = vertexShaderMap[full].lock())) {
			return shader;
		}
		vertexShaderMap[full] = shader = VertexShader::MakeShared(full, entry);
		return shader;
	}

	std::shared_ptr<PixelShader> ShaderCacheSingleton::LoadPixelShader(const std::filesystem::path& path, const std::string& entry) {
		std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
		std::shared_ptr<PixelShader> shader;
		if (pixelShaderMap.contains(full) && (shader = pixelShaderMap[full].lock())) {
			return shader;
		}
		pixelShaderMap[full] = shader = PixelShader::MakeShared(full, entry);
		return shader;
	}

	std::shared_ptr<GeometryShader> ShaderCacheSingleton::LoadGeometryShader(const std::filesystem::path& path, const std::string& entry) {
		std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
		std::shared_ptr<GeometryShader> shader;
		if (geometryShaderMap.contains(full) && (shader = geometryShaderMap[full].lock())) {
			return shader;
		}
		geometryShaderMap[full] = shader = GeometryShader::MakeShared(full, entry);
		return shader;
	}

	std::shared_ptr<DomainShader> ShaderCacheSingleton::LoadDomainShader(const std::filesystem::path& path, const std::string& entry) {
		std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
		std::shared_ptr<DomainShader> shader;
		if (domainShaderMap.contains(full) && (shader = domainShaderMap[full].lock())) {
			return shader;
		}
		domainShaderMap[full] = shader = DomainShader::MakeShared(full, entry);
		return shader;
	}

	std::shared_ptr<HullShader> ShaderCacheSingleton::LoadHullShader(const std::filesystem::path& path, const std::string& entry) {
		std::wstring full = path.is_absolute() ? path : std::filesystem::absolute(DefaultRelativeDirectory / path);
		std::shared_ptr<HullShader> shader;
		if (hullShaderMap.contains(full) && (shader = hullShaderMap[full].lock())) {
			return shader;
		}
		hullShaderMap[full] = shader = HullShader::MakeShared(full, entry);
		return shader;
	}

	void ShaderCacheSingleton::CleanUp() {
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
}