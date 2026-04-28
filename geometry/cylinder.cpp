#include "cylinder.h"
glm::vec4 bezier(const glm::vec4& p0, const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3, float t) {
    float u = 1.0f - t;
    return p0 * (u*u*u) + p1 * (3*u*u*t) + p2 * (3*u*t*t) + p3 * (t*t*t);
}
// 四维贝塞尔曲线求导（切线）
glm::vec4 bezierTangent(const glm::vec4& p0, const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3, float t) {
    float u = 1.0f - t;
    return (p1 - p0) * (3*u*u) + (p2 - p1) * (6*u*t) + (p3 - p2) * (3*t*t);
}
void generateCurvedCylinder(
    std::vector<Vertex>& outVertices,
    std::vector<uint16_t>& outIndices,
    const glm::vec4& p0, const glm::vec4& p1,
    const glm::vec4& p2, const glm::vec4& p3,
    float radius, int samples, int segments
) {
    uint16_t baseIndex = static_cast<uint16_t>(outVertices.size());
    
    // 存储四维中心点
    std::vector<glm::vec4> centers(samples + 1);
    std::vector<glm::vec3> tangents3D(samples + 1);
    
    // 1. 采样曲线
    for (int i = 0; i <= samples; ++i) {
        float t = static_cast<float>(i) / samples;
        centers[i] = bezier(p0, p1, p2, p3, t);
        
        // 获取四维切线并转换为三维
        glm::vec4 tangent4D = glm::normalize(bezierTangent(p0, p1, p2, p3, t));
        tangents3D[i] = glm::normalize(glm::vec3(tangent4D.x, tangent4D.y, tangent4D.z));
    }
    
    // 2. 为每个采样点生成横截面（在三维空间中）
    for (int i = 0; i <= samples; ++i) {
        const glm::vec4& center4D = centers[i];
        const glm::vec3& tangent3D = tangents3D[i];
        
        // 构建三维正交标架（使用熟悉的 glm 函数）
        glm::vec3 up(0, 1, 0);
        if (std::abs(glm::dot(tangent3D, up)) > 0.99f) {
            up = glm::vec3(1, 0, 0);
        }
        
        glm::vec3 right = glm::normalize(glm::cross(up, tangent3D));
        up = glm::normalize(glm::cross(tangent3D, right));
        
        // 生成圆上的顶点（在三维空间中）
        for (int j = 0; j < segments; ++j) {
            float angle = 2.0f * M_PI * static_cast<float>(j) / segments;
            
            // 在三维空间中构建圆
            glm::vec3 offset = right * std::cos(angle) * radius + up * std::sin(angle) * radius;
            
            // 将三维圆上的点转换回四维（保持 w 坐标）
            glm::vec4 vertexPos(
                center4D.x + offset.x,
                center4D.y + offset.y,
                center4D.z + offset.z,
                center4D.w  // 保持原始 w 坐标
            );
            
            outVertices.emplace_back(vertexPos, vertexPos);
        }
    }
    
    // 3. 生成索引
    for (int i = 0; i < samples; ++i) {
        int row0 = baseIndex + i * segments;
        int row1 = row0 + segments;
        
        for (int j = 0; j < segments; ++j) {
            int next_j = (j + 1) % segments;
            outIndices.push_back(row0 + j);
            outIndices.push_back(row1 + j);
            outIndices.push_back(row0 + next_j);
            outIndices.push_back(row0 + next_j);
            outIndices.push_back(row1 + j);
            outIndices.push_back(row1 + next_j);
        }
    }
}
Cylinder::Cylinder(/* args */){
}

Cylinder::~Cylinder(){
}
void Cylinder::Cleanup(){
    mGeometry.Destroy(*gpu.device);
    mWireframe.Destroy(*gpu.device);
}

void Cylinder::Draw(vk::CommandBuffer command, vk::PipelineLayout layout){
    mGeometry.Bind(command);
    mGeometry.Draw(command);
}

void Cylinder::DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout){
    mWireframe.Bind(command);
    mWireframe.Draw(command);
}

void Cylinder::Update(const void *useData){
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    CylinderParameter parameter = *(CylinderParameter *)useData;
    generateCurvedCylinder(vertices, indices,
        glm::vec4(parameter.point[0][0], parameter.point[0][1], parameter.point[0][2], parameter.point[0][3]),
        glm::vec4(parameter.point[1][0], parameter.point[1][1], parameter.point[1][2], parameter.point[1][3]),
        glm::vec4(parameter.point[2][0], parameter.point[2][1], parameter.point[2][2], parameter.point[2][3]),
        glm::vec4(parameter.point[3][0], parameter.point[3][1], parameter.point[3][2], parameter.point[3][3]), parameter.radius, parameter.samples, parameter.segments);
    if(!mGeometry.IsVaildIndex() || !mGeometry.IsVaildVertex()){
        mGeometry.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mGeometry.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mGeometry.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mGeometry.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
    if(!mWireframe.IsVaildIndex() || !mWireframe.IsVaildVertex()){
        mWireframe.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mWireframe.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mWireframe.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mWireframe.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
}