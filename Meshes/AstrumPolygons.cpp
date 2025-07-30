//#include "AstrumPolygons.hpp"
//
//AstrumPolygons::AstrumPolygons(const std::vector<AstrumVertexColor>& vertices,
//    const std::vector<uint16_t>& indices,
//    D3D11_PRIMITIVE_TOPOLOGY primitive,
//    DXGI_FORMAT format,
//    D3D11_USAGE vertexUsage,
//    D3D11_USAGE indexUsage)
//    : primitive(primitive)
//    , bufferFormat(format)
//    , indexCount(static_cast<unsigned int>(indices.size()))
//{
//    // 정점 버퍼
//    if (!AstrumRenderer::Instance().CreateBuffer(
//        vertices, vertexBuffer, D3D11_BIND_VERTEX_BUFFER, vertexUsage))
//    {
//        throw AstrumException("Create vertex buffer failed.");
//    }
//
//	// 인덱스 버퍼
//    if (!AstrumRenderer::Instance().CreateBuffer(
//        indices, indexBuffer, D3D11_BIND_INDEX_BUFFER, indexUsage))
//    {
//        throw AstrumException("Create index buffer failed.");
//    }
//}
//
//AstrumPolygons::~AstrumPolygons() {
//    Dispose();
//}
//
//// 렌더링을 하는 함수, 업데이트가 끝나고 프레임워크가 매번 호출해줘요.
//void AstrumPolygons::Render() {
//    UINT stride = sizeof(AstrumVertexColor);
//    UINT offset = 0;
//    auto* ctx = AstrumRenderer::Instance().GetContext();
//
//    ctx->IASetPrimitiveTopology(primitive);
//    ctx->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
//    ctx->IASetIndexBuffer(indexBuffer.Get(), bufferFormat, 0);
//    ctx->DrawIndexed(indexCount, 0, 0);
//}
//
//void AstrumPolygons::Dispose() {
//    if (vertexBuffer != nullptr) vertexBuffer.Reset();
//    if (indexBuffer != nullptr) indexBuffer.Reset();
//}