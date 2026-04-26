#include "pentatope.h"
std::vector<Vertex> generatePentatope() {
    std::vector<Vertex> vertices(5);
    float phi = (1.0f + std::sqrt(5.0f)) / 2.0f; // 黄金比例
    vertices[0] = Vertex(glm::vec4(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    vertices[1] = Vertex(glm::vec4(-1.0f/phi, phi, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    vertices[2] = Vertex(glm::vec4(-1.0f/phi, -1.0f, std::sqrt(2.0f + 2.0f/phi), 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    vertices[3] = Vertex(glm::vec4(-1.0f/phi, -1.0f, -1.0f, std::sqrt(2.0f + 2.0f/phi) * 0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
    vertices[4] = Vertex(glm::vec4(-1.0f/phi, -1.0f, -1.0f, -std::sqrt(2.0f + 2.0f/phi) * 0.5f), glm::vec3(1.0f, 0.0f, 1.0f));
    return vertices;
}
std::vector<uint16_t>generatePentatopeIndices() {
    std::array indices = {
        0, 1, 2, 0, 2, 3, 0, 3, 1, 1, 2, 3,
        0, 1, 2, 0, 2, 4, 0, 4, 1, 1, 2, 4,
        0, 1, 3, 0, 3, 4, 0, 4, 1, 1, 3, 4,
        0, 2, 3, 0, 3, 4, 0, 4, 2, 2, 3, 4,
        1, 2, 3, 1, 3, 4, 1, 4, 2, 2, 3, 4
    };
    return std::vector<uint16_t>(indices.begin(), indices.end());
}

std::vector<uint16_t> generatePentatopeEdges() {
    std::array indices = {
        0, 1, 0, 2, 0, 3, 0, 4,
        1, 2, 1, 3, 1, 4,
        2, 3, 2, 4,
        3, 4
    };    
    return std::vector<uint16_t>(indices.begin(), indices.end());
}

// std::vector<glm::vec3> generatePentatopeNormals(const std::vector<Vertex>& vertices, 
//                                                 const std::vector<uint32_t>& indices) {
//     std::vector<glm::vec3> normals(vertices.size(), glm::vec3(0.0f));
    
//     // 计算每个面的法线并累加到顶点
//     for (size_t i = 0; i < indices.size(); i += 3) {
//         uint32_t i0 = indices[i];
//         uint32_t i1 = indices[i+1];
//         uint32_t i2 = indices[i+2];
        
//         // 从4D投影到3D（忽略w分量）
//         glm::vec3 v0 = glm::vec3(vertices[i0].pos);
//         glm::vec3 v1 = glm::vec3(vertices[i1].pos);
//         glm::vec3 v2 = glm::vec3(vertices[i2].pos);
        
//         glm::vec3 edge1 = v1 - v0;
//         glm::vec3 edge2 = v2 - v0;
//         glm::vec3 normal = glm::cross(edge1, edge2);
        
//         // 累加到顶点
//         normals[i0] += normal;
//         normals[i1] += normal;
//         normals[i2] += normal;
//     }
    
//     // 归一化
//     for (auto& n : normals) {
//         if (glm::length(n) > 0.0f) {
//             n = glm::normalize(n);
//         }
//     }
    
//     return normals;
// }
Pentatope::Pentatope(/* args */){
}

Pentatope::~Pentatope(){
}

void Pentatope::Cleanup(){
    mGeometry.Destroy(*gpu.device);
    mWireframe.Destroy(*gpu.device);
}

void Pentatope::Draw(vk::CommandBuffer command, vk::PipelineLayout layout){
    mGeometry.Bind(command);
    mGeometry.Draw(command);
}

void Pentatope::DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout){
    mWireframe.Bind(command);
    mWireframe.Draw(command);
}

void Pentatope::Update(){
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    vertices = generatePentatope();
    indices = generatePentatopeIndices();
    if(!mGeometry.IsVaildIndex() || !mGeometry.IsVaildVertex()){
        mGeometry.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mGeometry.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mGeometry.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mGeometry.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
    indices = generatePentatopeEdges();
    if(!mWireframe.IsVaildIndex() || !mWireframe.IsVaildVertex()){
        mWireframe.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mWireframe.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mWireframe.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mWireframe.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
}