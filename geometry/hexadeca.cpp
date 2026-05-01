#include "hexadeca.h"
std::vector<Vertex> generateHexadeca(){
    std::vector<Vertex> vertices = {
        // 四维坐标刚好在四个维度的正负半轴上，半径为 1.0
        Vertex(glm::vec4( 1.0f,  0.0f,  0.0f,  0.0f), glm::vec3(0.2f, 0.8f, 1.0f)), // 0 (+X)
        Vertex(glm::vec4(-1.0f,  0.0f,  0.0f,  0.0f), glm::vec3(0.1f, 0.6f, 0.9f)), // 1 (-X)
        Vertex(glm::vec4( 0.0f,  1.0f,  0.0f,  0.0f), glm::vec3(0.3f, 0.9f, 1.0f)), // 2 (+Y)
        Vertex(glm::vec4( 0.0f, -1.0f,  0.0f,  0.0f), glm::vec3(0.15f, 0.7f, 0.95f)),// 3 (-Y)
        Vertex(glm::vec4( 0.0f,  0.0f,  1.0f,  0.0f), glm::vec3(0.25f, 0.85f, 1.0f)),// 4 (+Z)
        Vertex(glm::vec4( 0.0f,  0.0f, -1.0f,  0.0f), glm::vec3(0.1f, 0.65f, 0.85f)),// 5 (-Z)
        Vertex(glm::vec4( 0.0f,  0.0f,  0.0f,  1.0f), glm::vec3(0.4f, 0.95f, 1.0f)), // 6 (+W)
        Vertex(glm::vec4( 0.0f,  0.0f,  0.0f, -1.0f), glm::vec3(0.05f, 0.5f, 0.8f))  // 7 (-W)
    };
    return vertices;
}
std::vector<uint16_t>generateHexadecaIndices(bool line){
    const std::vector<uint16_t>indices_lines = {
        // +X 连接除 -X 外的所有点
        0, 2,  0, 3,  0, 4,  0, 5,  0, 6,  0, 7,
        // -X 连接除 +X 外的所有点
        1, 2,  1, 3,  1, 4,  1, 5,  1, 6,  1, 7,
        // +Y 连接 Z, W 轴 (去掉已算的X)
        2, 4,  2, 5,  2, 6,  2, 7,
        // -Y 连接 Z, W 轴
        3, 4,  3, 5,  3, 6,  3, 7,
        // +Z 连接 W 轴
        4, 6,  4, 7,
        // -Z 连接 W 轴
        5, 6,  5, 7
    };
    const std::vector<uint16_t>indices_triangles = {
        // X-Y-Z 维度组合 (8个)
        0, 2, 4,  0, 2, 5,  0, 3, 4,  0, 3, 5,  1, 2, 4,  1, 2, 5,  1, 3, 4,  1, 3, 5,
        // X-Y-W 维度组合 (8个)
        0, 2, 6,  0, 2, 7,  0, 3, 6,  0, 3, 7,  1, 2, 6,  1, 2, 7,  1, 3, 6,  1, 3, 7,
        // X-Z-W 维度组合 (8个)
        0, 4, 6,  0, 4, 7,  0, 5, 6,  0, 5, 7,  1, 4, 6,  1, 4, 7,  1, 5, 6,  1, 5, 7,
        // Y-Z-W 维度组合 (8个)
        2, 4, 6,  2, 4, 7,  2, 5, 6,  2, 5, 7,  3, 4, 6,  3, 4, 7,  3, 5, 6,  3, 5, 7
    };
    if(line){
        return indices_lines;
    }
    return  indices_triangles;
}
Hexadeca::Hexadeca(/* args */){
}

Hexadeca::~Hexadeca(){
}

void Hexadeca::Cleanup(){
    mGeometry.Destroy(*gpu.device);
    mWireframe.Destroy(*gpu.device);
}

void Hexadeca::Draw(vk::CommandBuffer command, vk::PipelineLayout layout){
    mGeometry.Bind(command);
    mGeometry.Draw(command);
}

void Hexadeca::DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout){
    mWireframe.Bind(command);
    mWireframe.Draw(command);
}

void Hexadeca::Update(const void *useData){
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    vertices = generateHexadeca();
    indices = generateHexadecaIndices(false);
    if(!mGeometry.IsVaildIndex() || !mGeometry.IsVaildVertex()){
        mGeometry.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mGeometry.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mGeometry.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mGeometry.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
    indices = generateHexadecaIndices(true);
    if(!mWireframe.IsVaildIndex() || !mWireframe.IsVaildVertex()){
        mWireframe.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mWireframe.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mWireframe.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mWireframe.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
}