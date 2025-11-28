#pragma once
#include <span>
#include "AstrumConstantBuffer.hpp"
#include "../Data/AstrumMaterialData.hpp"
#include "../Vectors/AstrumVector2.hpp"
#include "../Graphics/AstrumTextureSampler.hpp"

/// <summary>
/// 재질(머터리얼) 정보를 관리하는 상수 버퍼입니다.
/// </summary>
class AstrumMaterialConstantBuffer : public AstrumConstantBuffer
{
protected:
	/// <summary>
	/// 재질 데이터입니다.
	/// </summary>
	AstrumMaterialData data;
	/// <summary>
	/// 텍스처 샘플링 방식입니다. 기본값은 Linear입니다.
	/// </summary>
	AstrumTextureSampleType sampleType = AstrumTextureSampleType::AstrumTextureSampleType_Linear;
public:
	/// <summary>
	/// 재질 상수 버퍼를 생성합니다.
	/// </summary>
	AstrumMaterialConstantBuffer() : AstrumConstantBuffer(sizeof(AstrumMaterialData)) {}

	/// <summary>
	/// 재질의 색상을 설정합니다.
	/// </summary>
	/// <param name="color">설정할 색상입니다.</param>
	void SetColor(const AstrumVector4& color) { data.BaseColor = color; }
	/// <summary>
	/// 재질의 불투명도를 설정합니다.
	/// </summary>
	/// <param name="opacity">설정할 불투명도(0~1)입니다.</param>
	void SetOpacity(float opacity) { data.Opacity = opacity; }
	/// <summary>
	/// 재질의 크기를 설정합니다.
	/// </summary>
	/// <param name="width">텍스처의 너비입니다.</param>
	/// <param name="height">텍스처의 높이입니다.</param>
	void SetSize(unsigned short width, unsigned short height) { data.Width = width; data.Height = height; }
	/// <summary>
	/// 텍스처 샘플링 방식을 설정합니다.
	/// </summary>
	/// <param name="type">설정할 샘플링 방식입니다.</param>
	void SetSampleType(AstrumTextureSampleType type) { this->sampleType = type; }
	/// <summary>
	/// 텍스처 뒤집기 옵션을 설정합니다.
	/// </summary>
	/// <param name="flip">설정할 뒤집기 방식입니다.</param>
	void SetFlip(AstrumMaterialFlipType flip) { data.Flip = flip; }

	/// <summary>
	/// 재질의 색상을 반환합니다.
	/// </summary>
	/// <returns>재질의 색상 참조입니다.</returns>
	AstrumVector4& GetColor() { return data.BaseColor; }
	/// <summary>
	/// 재질의 불투명도를 반환합니다.
	/// </summary>
	/// <returns>재질의 불투명도 참조입니다.</returns>
	float& GetOpacity() { return data.Opacity; }
	/// <summary>
	/// 텍스처의 크기를 반환합니다.
	/// </summary>
	/// <returns>텍스처의 (너비, 높이) 쌍입니다.</returns>
	std::pair<unsigned short, unsigned short> GetSize() const { return { static_cast<unsigned short>(data.Width), static_cast<unsigned short>(data.Height) }; }
	/// <summary>
	/// 텍스처 샘플링 방식을 반환합니다.
	/// </summary>
	/// <returns>현재 설정된 샘플링 방식입니다.</returns>
	AstrumTextureSampleType GetSampleType() const { return sampleType; }
	/// <summary>
	/// 텍스처 뒤집기 옵션을 반환합니다.
	/// </summary>
	/// <returns>현재 설정된 뒤집기 방식입니다.</returns>
	AstrumMaterialFlipType GetFlip() const { return data.Flip; }

	/// <summary>
	/// 상수 버퍼를 업데이트합니다.
	/// </summary>
	virtual void UpdateBuffer() override;
};

