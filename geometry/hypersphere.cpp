#include "hypersphere.h"
Hypersphere::Hypersphere(/* args */){
}

Hypersphere::~Hypersphere(){
}

void Hypersphere::Cleanup(){
    mHypersphere.Destroy(*gpu.device);
}

void Hypersphere::Draw(vk::CommandBuffer command, vk::PipelineLayout layout){
    mHypersphere.Bind(command);
    mHypersphere.Draw(command);
}

void Hypersphere::DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout){
    mHypersphere.Bind(command);
    mHypersphere.Draw(command);
}

void Hypersphere::Update(){
    int stacks = 20;     // ψ方向分段数 (纬度)
    int sectors = 20;    // φ方向分段数 (纬度)
    int circles = 20;    // θ方向分段数 (经度)
    float radius = 1.0f;
    // x = r * sin(ψ) * sin(φ) * cos(θ)
    // y = r * sin(ψ) * sin(φ) * sin(θ)
    // z = r * sin(ψ) * cos(φ)
    // w = r * cos(ψ)
    // 其中：ψ∈[0,π], φ∈[0,π], θ∈[0,2π]
    Vertex v;
    std::vector<Vertex>vertices;
    std::vector<glm::vec3>color;
    std::vector<uint16_t> indices;
    for (int i = 0; i <= stacks; ++i) {
        float psi = M_PI * i / stacks;  // ψ ∈ [0, π]
        float sinPsi = sin(psi);
        float cosPsi = cos(psi);
        
        for (int j = 0; j <= sectors; ++j) {
            float phi = M_PI * j / sectors;  // φ ∈ [0, π]
            float sinPhi = sin(phi);
            float cosPhi = cos(phi);
            
            for (int k = 0; k <= circles; ++k) {
                float theta = 2.0f * M_PI * k / circles;  // θ ∈ [0, 2π]
                float sinTheta = sin(theta);
                float cosTheta = cos(theta);

                v.pos.x = radius * sinPsi * sinPhi * cosTheta;
                v.pos.y = radius * sinPsi * sinPhi * sinTheta;
                v.pos.z = radius * sinPsi * cosPhi;
                v.pos.w = radius * cosPsi;
                

                v.color = glm::vec3(0.5f + 0.5f * sinPsi, 0.5f + 0.5f * cosPhi, 0.5f + 0.5f * sinTheta);
                
                // vertex.normal = glm::normalize(glm::vec3(
                //     vertex.position.x,
                //     vertex.position.y,
                //     vertex.position.z
                // ));
                
                vertices.push_back(v);
            }
        }
    }
    int verticesPerPsi = (sectors + 1) * (circles + 1);
    
    for (int i = 0; i < stacks; ++i) {
        for (int j = 0; j < sectors; ++j) {
            for (int k = 0; k < circles; ++k) {
                int v0 = i * verticesPerPsi + j * (circles + 1) + k;
                int v1 = i * verticesPerPsi + j * (circles + 1) + (k + 1);
                int v2 = i * verticesPerPsi + (j + 1) * (circles + 1) + k;
                int v3 = i * verticesPerPsi + (j + 1) * (circles + 1) + (k + 1);
                
                int v4 = (i + 1) * verticesPerPsi + j * (circles + 1) + k;
                int v5 = (i + 1) * verticesPerPsi + j * (circles + 1) + (k + 1);
                int v6 = (i + 1) * verticesPerPsi + (j + 1) * (circles + 1) + k;
                int v7 = (i + 1) * verticesPerPsi + (j + 1) * (circles + 1) + (k + 1);
                
                // 在ψ-φ平面上的四边形（固定θ）
                indices.push_back(v0);
                indices.push_back(v2);
                indices.push_back(v6);
                
                indices.push_back(v0);
                indices.push_back(v6);
                indices.push_back(v4);
                
                // 在ψ-θ平面上的四边形（固定φ）
                indices.push_back(v0);
                indices.push_back(v4);
                indices.push_back(v5);
                
                indices.push_back(v0);
                indices.push_back(v5);
                indices.push_back(v1);
                
                // 在φ-θ平面上的四边形（固定ψ）
                indices.push_back(v0);
                indices.push_back(v1);
                indices.push_back(v3);
                
                indices.push_back(v0);
                indices.push_back(v3);
                indices.push_back(v2);
                
                // 对面的三角形
                indices.push_back(v7);
                indices.push_back(v3);
                indices.push_back(v1);
                
                indices.push_back(v7);
                indices.push_back(v1);
                indices.push_back(v5);
                
                indices.push_back(v7);
                indices.push_back(v5);
                indices.push_back(v4);
                
                indices.push_back(v7);
                indices.push_back(v4);
                indices.push_back(v6);
                
                indices.push_back(v7);
                indices.push_back(v6);
                indices.push_back(v2);
                
                indices.push_back(v7);
                indices.push_back(v2);
                indices.push_back(v3);
            }
        }
    }
    if(!mHypersphere.IsVaildIndex() || !mHypersphere.IsVaildVertex()){
        mHypersphere.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mHypersphere.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mHypersphere.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mHypersphere.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
}
