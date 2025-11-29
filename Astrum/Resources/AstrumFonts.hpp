#pragma once
#include <d2d1.h>
#include <dwrite_3.h>
#include <wrl/client.h>
#include <string>
#include <filesystem>
#include <memory>

#pragma comment(lib, "DWrite.lib")
#pragma comment(lib, "D2d1.lib")

class AstrumTargetFont;

/// <summary>
/// 글꼴 파일에서 로드된 글꼴 컬렉션을 관리하는 클래스입니다.
/// DirectWrite를 사용하여 시스템 글꼴뿐 아니라 커스텀 글꼴도 로드할 수 있습니다.
/// 로드된 글꼴에서 특정 크기와 굵기의 폰트를 생성할 수 있습니다.
/// </summary>
class AstrumFonts
{
	friend class AstrumTargetFont;
public:
	/// <summary>
	/// 글꼴 파일을 로드하여 글꼴 컬렉션을 생성합니다.
	/// </summary>
	/// <param name="fontFilePath">로드할 글꼴 파일의 경로입니다. (.ttf, .otf 등)</param>
	AstrumFonts(const std::filesystem::path& fontFilePath) { Initialize(fontFilePath.c_str()); }
	/// <summary>
	/// 글꼴 파일을 로드하여 글꼴 컬렉션을 생성합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="fontFilePath">로드할 글꼴 파일의 경로입니다. (.ttf, .otf 등)</param>
	AstrumFonts(std::filesystem::path&& fontFilePath) { Initialize(fontFilePath.c_str()); }
	
	/// <summary>
	/// 이 글꼴 컬렉션에서 지정된 이름, 크기, 굵기의 폰트를 생성합니다.
	/// </summary>
	/// <param name="fontName">사용할 글꼴 이름입니다.</param>
	/// <param name="fontSize">글꼴 크기(포인트)입니다. 기본값은 24.0f입니다.</param>
	/// <param name="weight">글꼴 굵기입니다. DirectWrite 가중치 값입니다. 기본값은 DWRITE_FONT_WEIGHT_NORMAL입니다.</param>
	/// <returns>생성된 대상 폰트 공유 포인터입니다.</returns>
	std::shared_ptr<AstrumTargetFont> GetFont(const std::wstring& fontName, float fontSize = 24.0f, int weight = DWRITE_FONT_WEIGHT_NORMAL) const;

	/// <summary>
	/// 로드된 글꼴의 실제 면(Face) 이름을 반환합니다.
	/// </summary>
	/// <returns>글꼴의 면 이름입니다.</returns>
	const std::wstring& GetFaceName() const;
	/// <summary>
	/// 글꼴 컬렉션이 유효하게 로드되었는지 확인합니다.
	/// </summary>
	/// <returns>글꼴이 유효하면 true, 아니면 false를 반환합니다.</returns>
	bool IsValid() const noexcept { return fontCollection != nullptr; }
	/// <summary>
	/// 글꼴 컬렉션이 유효한지 bool로 변환합니다.
	/// IsValid()와 동일한 결과를 반환합니다.
	/// </summary>
	operator bool() const noexcept { return IsValid(); }
private:
	/// <summary>
	/// 로드된 글꼴의 실제 면(Face) 이름입니다.
	/// </summary>
	std::wstring faceName;
	/// <summary>
	/// DirectWrite 팩토리를 반환합니다.
	/// Direct2D와 DirectWrite 통합에 사용됩니다.
	/// </summary>
	/// <returns>IDWriteFactory5 COM 포인터입니다.</returns>
	Microsoft::WRL::ComPtr<IDWriteFactory5> GetWriteFactory() const;
	/// <summary>
	/// 로드된 글꼴 컬렉션입니다.
	/// DirectWrite의 글꼴 정보를 관리합니다.
	/// </summary>
	Microsoft::WRL::ComPtr<IDWriteFontCollection1> fontCollection;

	/// <summary>
	/// 주어진 경로에서 글꼴 파일을 로드하여 초기화합니다.
	/// </summary>
	/// <param name="pathstr">로드할 글꼴 파일의 경로입니다.</param>
	void Initialize(const std::filesystem::path::value_type* pathstr);

public:
	/// <summary>
	/// 글꼴 파일을 로드하여 AstrumFonts의 공유 포인터를 생성합니다.
	/// </summary>
	/// <param name="fontFilePath">로드할 글꼴 파일의 경로입니다.</param>
	/// <returns>새로 생성된 AstrumFonts 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumFonts> MakeShared(const std::filesystem::path& fontFilePath) { return std::make_shared<AstrumFonts>(fontFilePath); }
	/// <summary>
	/// 글꼴 파일을 로드하여 AstrumFonts의 공유 포인터를 생성합니다. (우측값 참조 버전)
	/// </summary>
	/// <param name="fontFilePath">로드할 글꼴 파일의 경로입니다.</param>
	/// <returns>새로 생성된 AstrumFonts 공유 포인터입니다.</returns>
	static std::shared_ptr<AstrumFonts> MakeShared(std::filesystem::path&& fontFilePath) { return std::make_shared<AstrumFonts>(std::move(fontFilePath)); }
};
