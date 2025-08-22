#include "AstrumImage.hpp"

namespace Astrum
{
	Image::Image(const std::filesystem::path& path)
	{
		image = std::make_unique<DirectX::ScratchImage>();
		std::wstring ext = path.extension();
		std::ranges::transform(ext.begin(), ext.end(), ext.begin(), ::towlower);
		if (ext == L".dds") {
			if (FAILED(DirectX::LoadFromDDSFile(path.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, *image))) {
				throw Exception("Failed to load DDS image from file: " + path.string());
			}
		}
		else if (ext == L".tga") {
			if (FAILED(DirectX::LoadFromTGAFile(path.c_str(), nullptr, *image))) {
				throw Exception("Failed to load TGA image from file: " + path.string());
			}
		}
		else if (ext == L".png" || ext == L".jpg" || ext == L".jpeg") {
			if (FAILED(DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, *image))) {
				throw Exception("Failed to load WIC image from file: " + path.string());
			}
		}
		else throw Exception(L"Unsupported image format: " + ext);
	}

	Image::~Image() { /* ScratchImage is mannaged by unique_ptr. */ }

	size_t Image::GetWidth() const { return image->GetMetadata().width; }
	size_t Image::GetHeight() const { return image->GetMetadata().height; }

	const DirectX::Image* Image::GetImages() const { return image->GetImages(); }
	const size_t Image::GetImageCount() const { return image->GetImageCount(); }
	const DirectX::TexMetadata& Image::GetMetadata() const { return image->GetMetadata(); }
}