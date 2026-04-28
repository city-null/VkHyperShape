#include "cylindrical.h"
void generateHyperCylinder(std::vector<Vertex>& vertices,std::vector<uint16_t>& indices, float radius = 1.0f, float halfLength = 1.0f,  // w轴方向的半长
    int slices = 24,          // 球面经度细分
    int stacks = 12,          // 球面纬度细分
    int wSegments = 8         // w方向细分
) {
    vertices.clear();
    indices.clear();
    
    // 生成两个端盖（4D中的三维球面）
    // 1. 前端盖 (w = -halfLength)
    for (int stack = 0; stack <= stacks; ++stack) {
        float phi = M_PI * static_cast<float>(stack) / stacks;
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        
        for (int slice = 0; slice <= slices; ++slice) {
            float theta = 2.0f * M_PI * static_cast<float>(slice) / slices;
            float x = radius * sinPhi * cos(theta);
            float y = radius * sinPhi * sin(theta);
            float z = radius * cosPhi;
            float w = -halfLength;
            vertices.push_back(Vertex(glm::vec4(x, y, z, w), glm::vec3(w)));
        }
    }
    
    // 2. 后端盖 (w = halfLength)
    for (int stack = 0; stack <= stacks; ++stack) {
        float phi = M_PI * static_cast<float>(stack) / stacks;
        float sinPhi = sin(phi);
        float cosPhi = cos(phi);
        
        for (int slice = 0; slice <= slices; ++slice) {
            float theta = 2.0f * M_PI * static_cast<float>(slice) / slices;
            float x = radius * sinPhi * cos(theta);
            float y = radius * sinPhi * sin(theta);
            float z = radius * cosPhi;
            float w = halfLength;
            vertices.push_back(Vertex(glm::vec4(x, y, z, w), glm::vec3(w)));
        }
    }
    
    // 3. 侧面（连接两个端盖的三维流形）
    for (int wIdx = 0; wIdx <= wSegments; ++wIdx) {
        float w = -halfLength + 2.0f * halfLength * static_cast<float>(wIdx) / wSegments;
        
        for (int slice = 0; slice <= slices; ++slice) {
            float theta = 2.0f * M_PI * static_cast<float>(slice) / slices;
            float cosTheta = cos(theta);
            float sinTheta = sin(theta);
            
            for (int stack = 0; stack <= stacks; ++stack) {
                float phi = M_PI * static_cast<float>(stack) / stacks;
                float x = radius * sin(phi) * cosTheta;
                float y = radius * sin(phi) * sinTheta;
                float z = radius * cos(phi);
                vertices.push_back(Vertex(glm::vec4(x, y, z, w), glm::vec3(w)));
            }
        }
    }
    
    // 生成索引
    int capsVertices = (stacks + 1) * (slices + 1);
    
    // 前端盖索引
    for (int stack = 0; stack < stacks; ++stack) {
        for (int slice = 0; slice < slices; ++slice) {
            int first = stack * (slices + 1) + slice;
            int second = first + slices + 1;
            
            indices.push_back(first);
            indices.push_back(second);
            indices.push_back(first + 1);
            
            indices.push_back(second);
            indices.push_back(second + 1);
            indices.push_back(first + 1);
        }
    }
    
    // 后端盖索引
    int backCapOffset = capsVertices;
    for (int stack = 0; stack < stacks; ++stack) {
        for (int slice = 0; slice < slices; ++slice) {
            int first = backCapOffset + stack * (slices + 1) + slice;
            int second = first + slices + 1;
            
            indices.push_back(first);
            indices.push_back(first + 1);
            indices.push_back(second);
            
            indices.push_back(second);
            indices.push_back(first + 1);
            indices.push_back(second + 1);
        }
    }
    
    // 侧面索引
    int sideOffset = 2 * capsVertices;
    for (int wIdx = 0; wIdx < wSegments; ++wIdx) {
        for (int slice = 0; slice < slices; ++slice) {
            for (int stack = 0; stack < stacks; ++stack) {
                int currentLayer = wIdx * (stacks + 1) * (slices + 1);
                int nextLayer = (wIdx + 1) * (stacks + 1) * (slices + 1);
                
                int v0 = sideOffset + currentLayer + stack * (slices + 1) + slice;
                int v1 = v0 + 1;
                int v2 = sideOffset + currentLayer + (stack + 1) * (slices + 1) + slice;
                int v3 = v2 + 1;
                
                int v4 = sideOffset + nextLayer + stack * (slices + 1) + slice;
                int v5 = v4 + 1;
                int v6 = sideOffset + nextLayer + (stack + 1) * (slices + 1) + slice;
                int v7 = v6 + 1;
                
                // 每个小块分成两个三角形
                indices.push_back(v0);
                indices.push_back(v1);
                indices.push_back(v2);
                
                indices.push_back(v2);
                indices.push_back(v1);
                indices.push_back(v3);
                
                indices.push_back(v0);
                indices.push_back(v4);
                indices.push_back(v1);
                
                indices.push_back(v1);
                indices.push_back(v4);
                indices.push_back(v5);
                
                indices.push_back(v2);
                indices.push_back(v3);
                indices.push_back(v6);
                
                indices.push_back(v3);
                indices.push_back(v7);
                indices.push_back(v6);
            }
        }
    }
}
void generateHyperCylinderWireframe(std::vector<Vertex>&vertices, std::vector<uint16_t>&indices, float radius = 1.0f, float halfLength = 1.0f, int slices = 16, int stacks = 8, int wSegments = 4) {
    vertices.clear();
    indices.clear();
    
    std::vector<Vertex> frameVertices;
    
    // 端圆
    for (int i = 0; i <= slices; ++i) {
        float theta = 2.0f * M_PI * i / slices;
        
        // 前端圆 (w = -halfLength)
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        frameVertices.push_back(Vertex(glm::vec4(x, y, 0.0f, -halfLength), glm::vec3(x, y, halfLength)));
        
        // 后端圆 (w = halfLength)
        frameVertices.push_back(Vertex(glm::vec4(x, y, 0.0f, halfLength), glm::vec3(x, y, halfLength)));
    }
    
    // 生成一些球面上的点
    for (int wIdx = 0; wIdx <= wSegments; ++wIdx) {
        float w = -halfLength + 2.0f * halfLength * wIdx / wSegments;
        
        for (int slice = 0; slice < slices; ++slice) {
            float theta = 2.0f * M_PI * slice / slices;
            for (int stack = 0; stack <= stacks; ++stack) {
                float phi = M_PI * stack / stacks;
                
                float x = radius * sin(phi) * cos(theta);
                float y = radius * sin(phi) * sin(theta);
                float z = radius * cos(phi);
                
                frameVertices.push_back(Vertex(glm::vec4(x, y, z, w), glm::vec3(w)));
            }
        }
    }
    
    vertices = frameVertices;
    
    // 生成线框索引
    int frontCircleOffset = 0;
    int backCircleOffset = (slices + 1) * 2;  // 修正偏移
    
    // 连接端圆的线
    for (int i = 0; i <= slices; ++i) {
        indices.push_back(frontCircleOffset + 2 * i);
        indices.push_back(backCircleOffset + 2 * i);
    }
    
    // 端圆本身的线
    for (int i = 0; i < slices; ++i) {
        indices.push_back(frontCircleOffset + 2 * i);
        indices.push_back(frontCircleOffset + 2 * (i + 1));
        
        indices.push_back(backCircleOffset + 2 * i);
        indices.push_back(backCircleOffset + 2 * (i + 1));
    }
}
Cylindrical::Cylindrical(/* args */)
{
}

Cylindrical::~Cylindrical(){
}

void Cylindrical::Cleanup(){
    mGeometry.Destroy(*gpu.device);
    mWireframe.Destroy(*gpu.device);
}

void Cylindrical::Draw(vk::CommandBuffer command, vk::PipelineLayout layout){
    mGeometry.Bind(command);
    mGeometry.Draw(command);
}

void Cylindrical::DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout){
    mWireframe.Bind(command);
    mWireframe.Draw(command);
}

void Cylindrical::Update(const void *useData){
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    generateHyperCylinder(vertices, indices);
    if(!mGeometry.IsVaildIndex() || !mGeometry.IsVaildVertex()){
        mGeometry.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mGeometry.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mGeometry.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mGeometry.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
    generateHyperCylinderWireframe(vertices, indices);
    if(!mWireframe.IsVaildIndex() || !mWireframe.IsVaildVertex()){
        mWireframe.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mWireframe.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mWireframe.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mWireframe.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
}