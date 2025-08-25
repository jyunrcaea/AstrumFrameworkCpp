#include "AstrumImage.hpp"

AstrumImage::AstrumImage(const std::filesystem::path& path)
{
	image = std::make_unique<DirectX::ScratchImage>();
	std::wstring ext = path.extension();
	std::ranges::transform(ext.begin(), ext.end(), ext.begin(), ::towlower);
	if (ext == L".dds") {
		if (FAILED(DirectX::LoadFromDDSFile(path.c_str(), DirectX::DDS_FLAGS_NONE, nullptr, *image ))) {
			throw AstrumException("Failed to load DDS image from file: " + path.string());
		}
	}
	else if (ext == L".tga") {
		if (FAILED(DirectX::LoadFromTGAFile(path.c_str(), nullptr, *image ))) {
			throw AstrumException("Failed to load TGA image from file: " + path.string());
		}
	}
	else if (ext == L".png" || ext == L".jpg" || ext == L".jpeg") {
		if (FAILED(DirectX::LoadFromWICFile(path.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, *image))) {
			throw AstrumException("Failed to load WIC image from file: " + path.string());
		}
	}
	else throw AstrumException(L"Unsupported image format: " + ext);
}

AstrumImage::~AstrumImage() { /* ScratchImage is mannaged by unique_ptr. */ }

size_t AstrumImage::GetWidth() const { return image->GetMetadata().width; }
size_t AstrumImage::GetHeight() const { return image->GetMetadata().height; }

const DirectX::Image* AstrumImage::GetImages() const { return image->GetImages(); }
const size_t AstrumImage::GetImageCount() const { return image->GetImageCount(); }
const DirectX::TexMetadata& AstrumImage::GetMetadata() const { return image->GetMetadata(); }