#include <d3d11_1.h>
#include <string>

// Forward declaration for Direct3D device
struct ID3D11Device;
struct ID3D11DeviceContext;

class AstrumTexture
{
public:
    // Constructor: Loads the image file from the given path and creates a DX11 texture.
    AstrumTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, const std::string& filePath);

    // Destructor: Releases the DX11 texture resources.
    ~AstrumTexture();

    // Get the shader resource view for the texture.
    ID3D11ShaderResourceView* GetShaderResourceView() const { return m_shaderResourceView; }

private:
    // Disable copy and assignment
    AstrumTexture(const AstrumTexture&) = delete;
    AstrumTexture& operator=(const AstrumTexture&) = delete;

    ID3D11ShaderResourceView* m_shaderResourceView = nullptr;
    // Depending on the image loading method, you might also need to store the texture resource itself
    // ID3D11Resource* m_textureResource = nullptr;

    // TODO: Implement the image loading logic in the .cpp file.
    // This will likely involve using a library like DirectXTex or Windows Imaging Component (WIC)
    // to load the image data and create the ID3D11Texture2D and ID3D11ShaderResourceView.
};