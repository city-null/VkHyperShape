#include "twentyFourCell.h"
std::vector<Vertex> generateTwentyFourCell(){
    const std::vector<Vertex> vertices = {
        // XY 平面组 (z=0, w=0)
        Vertex(glm::vec4(1.0f,  1.0f,  0.0f,  0.0f), glm::vec3(1, 0, 0)), // 0
        Vertex(glm::vec4(1.0f, -1.0f,  0.0f,  0.0f), glm::vec3(.5, 0, 0)), // 1
        Vertex(glm::vec4(-1.0f,  1.0f,  0.0f,  0.0f), glm::vec3(.25, 0, 0)), // 2
        Vertex(glm::vec4(-1.0f, -1.0f,  0.0f,  0.0f), glm::vec3(.15, 0, 0)), // 3
        
        // XZ 平面组 (y=0, w=0)
        Vertex(glm::vec4(1.0f,  0.0f,  1.0f,  0.0f), glm::vec3(0, 1, 0)), // 4
        Vertex(glm::vec4(1.0f,  0.0f, -1.0f,  0.0f), glm::vec3(0, .5, 0)), // 5
        Vertex(glm::vec4(-1.0f,  0.0f,  1.0f,  0.0f), glm::vec3(0, .25, 0)), // 6
        Vertex(glm::vec4(-1.0f,  0.0f, -1.0f,  0.0f), glm::vec3(0, .15, 0)), // 7
        
        // XW 平面组 (y=0, z=0)
        Vertex(glm::vec4(1.0f,  0.0f,  0.0f,  1.0f), glm::vec3(0, 0, 1)), // 8
        Vertex(glm::vec4(1.0f,  0.0f,  0.0f, -1.0f), glm::vec3(0, 0, .5)), // 9
        Vertex(glm::vec4(-1.0f,  0.0f,  0.0f,  1.0f), glm::vec3(0, 0, .25)), // 10
        Vertex(glm::vec4(-1.0f,  0.0f,  0.0f, -1.0f), glm::vec3(0, 0, .15)), // 11
        
        // YZ 平面组 (x=0, w=0)
        Vertex(glm::vec4(0.0f,  1.0f,  1.0f,  0.0f), glm::vec3(1, .5, 0)), // 12
        Vertex(glm::vec4(0.0f,  1.0f, -1.0f,  0.0f), glm::vec3(.5, .5, 0)), // 13
        Vertex(glm::vec4(0.0f, -1.0f,  1.0f,  0.0f), glm::vec3(.25, .5, 0)), // 14
        Vertex(glm::vec4(0.0f, -1.0f, -1.0f,  0.0f), glm::vec3(.15, .5, 0)), // 15
        
        // YW 平面组 (x=0, z=0)
        Vertex(glm::vec4(0.0f,  1.0f,  0.0f,  1.0f), glm::vec3(1, 0, .5)), // 16
        Vertex(glm::vec4(0.0f,  1.0f,  0.0f, -1.0f), glm::vec3(.5, 0, .5)), // 17
        Vertex(glm::vec4(0.0f, -1.0f,  0.0f,  1.0f), glm::vec3(.25, 0, .5)), // 18
        Vertex(glm::vec4(0.0f, -1.0f,  0.0f, -1.0f), glm::vec3(.15, 0, .5)), // 19
        
        // ZW 平面组 (x=0, y=0)
        Vertex(glm::vec4(0.0f,  0.0f,  1.0f,  1.0f), glm::vec3(1, .5, .5)), // 20
        Vertex(glm::vec4(0.0f,  0.0f,  1.0f, -1.0f), glm::vec3(.5, .5, .5)), // 21
        Vertex(glm::vec4(0.0f,  0.0f, -1.0f,  1.0f), glm::vec3(.25, .5, .5)), // 22
        Vertex(glm::vec4(0.0f,  0.0f, -1.0f, -1.0f), glm::vec3(.15, .5, .5))  // 23
    };
    return vertices;
}
std::vector<uint16_t>generateTwentyFourCellIndices(bool line){
    const std::vector<uint16_t>line_indices = {
        // XY 组连接到其他组
        0, 4,   0, 5,   1, 4,   1, 5,   2, 6,   2, 7,   3, 6,   3, 7, // XY - XZ
        0, 8,   0, 9,   1, 8,   1, 9,   2,10,   2,11,   3,10,   3,11, // XY - XW
        0,12,   0,13,   1,14,   1,15,   2,12,   2,13,   3,14,   3,15, // XY - YZ
        0,16,   0,17,   1,18,   1,19,   2,16,   2,17,   3,18,   3,19, // XY - YW

        // XZ 组连接到剩余组
        4, 8,   4, 9,   5, 8,   5, 9,   6,10,   6,11,   7,10,   7,11, // XZ - XW
        4,12,   4,14,   5,13,   5,15,   6,12,   6,14,   7,13,   7,15, // XZ - YZ
        4,20,   4,21,   5,22,   5,23,   6,20,   6,21,   7,22,   7,23, // XZ - ZW

        // XW 组连接到剩余组
        8,16,   8,18,   9,17,   9,19,  10,16,  10,18,  11,17,  11,19, // XW - YW
        8,20,   8,22,   9,21,   9,23,  10,20,  10,22,  11,21,  11,23, // XW - ZW

        // YZ 组连接到剩余组
        12,16,  12,17,  13,16,  13,17,  14,18,  14,19,  15,18,  15,19, // YZ - YW
        12,20,  12,21,  13,22,  13,23,  14,20,  14,21,  15,22,  15,23, // YZ - ZW

        // YW 组连接到 ZW 组
        16,20,  16,22,  17,21,  17,23,  18,20,  18,22,  19,21,  19,23  // YW - ZW
    };
    const std::vector<uint16_t>indices_triangles = {
        // --- 类别 1：三个顶点涉及 3 个维度，无共享非零轴 (32个面) ---
        // (X,Y,Z) 组合
        0,  4, 12,   0,  5, 13,   1,  4, 14,   1,  5, 15,
        2,  6, 12,   2,  7, 13,   3,  6, 14,   3,  7, 15,
        // (X,Y,W) 组合
        0,  8, 16,   0,  9, 17,   1,  8, 18,   1,  9, 19,
        2, 10, 16,   2, 11, 17,   3, 10, 18,   3, 11, 19,
        // (X,Z,W) 组合
        4,  8, 20,   4,  9, 21,   5,  8, 22,   5,  9, 23,
        6, 10, 20,   6, 11, 21,   7, 10, 22,   7, 11, 23,
        // (Y,Z,W) 组合
        12, 16, 20,  12, 17, 21,  13, 16, 22,  13, 17, 23,
        14, 18, 20,  14, 19, 21,  15, 18, 22,  15, 19, 23,

        // --- 类别 2：三个顶点共享一个非零坐标轴，涉及 4 个维度 (64个面) ---
        // 共享 X 轴 (XY, XZ, XW 组合)
        0,  4,  8,   0,  4,  9,   0,  5,  8,   0,  5,  9,
        1,  4,  8,   1,  4,  9,   1,  5,  8,   1,  5,  9,
        2,  6, 10,   2,  6, 11,   2,  7, 10,   2,  7, 11,
        3,  6, 10,   3,  6, 11,   3,  7, 10,   3,  7, 11,
        // 共享 Y 轴 (XY, YZ, YW 组合)
        0, 12, 16,   0, 12, 17,   0, 13, 16,   0, 13, 17,
        2, 12, 16,   2, 12, 17,   2, 13, 16,   2, 13, 17,
        1, 14, 18,   1, 14, 19,   1, 15, 18,   1, 15, 19,
        3, 14, 18,   3, 14, 19,   3, 15, 18,   3, 15, 19,
        // 共享 Z 轴 (XZ, YZ, ZW 组合)
        4, 12, 20,   4, 12, 21,   4, 14, 20,   4, 14, 21,
        6, 12, 20,   6, 12, 21,   6, 14, 20,   6, 14, 21,
        5, 13, 22,   5, 13, 23,   5, 15, 22,   5, 15, 23,
        7, 13, 22,   7, 13, 23,   7, 15, 22,   7, 15, 23,
        // 共享 W 轴 (XW, YW, ZW 组合)
        8, 16, 20,   8, 16, 22,   8, 18, 20,   8, 18, 22,
        10, 16, 20,  10, 16, 22,  10, 18, 20,  10, 18, 22,
        9, 17, 21,   9, 17, 23,   9, 19, 21,   9, 19, 23,
        11, 17, 21,  11, 17, 23,  11, 19, 21,  11, 19, 23
    };
    if(line){
        return line_indices;
    }
    return  indices_triangles;
}
TwentyFourCell::TwentyFourCell(/* args */){
}

TwentyFourCell::~TwentyFourCell(){
}
void TwentyFourCell::Cleanup(){
    mGeometry.Destroy(*gpu.device);
    mWireframe.Destroy(*gpu.device);
}

void TwentyFourCell::Draw(vk::CommandBuffer command, vk::PipelineLayout layout){
    mGeometry.Bind(command);
    mGeometry.Draw(command);
}

void TwentyFourCell::DrawWireframe(vk::CommandBuffer command, vk::PipelineLayout layout){
    mWireframe.Bind(command);
    mWireframe.Draw(command);
}

void TwentyFourCell::Update(const void *useData){
    std::vector<Vertex> vertices;
    std::vector<uint16_t> indices;
    vertices = generateTwentyFourCell();
    indices = generateTwentyFourCellIndices(false);
    if(!mGeometry.IsVaildIndex() || !mGeometry.IsVaildVertex()){
        mGeometry.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mGeometry.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mGeometry.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mGeometry.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
    indices = generateTwentyFourCellIndices(true);
    if(!mWireframe.IsVaildIndex() || !mWireframe.IsVaildVertex()){
        mWireframe.CreateIndexBuffer(*gpu.device, indices.data(), sizeof(uint16_t) * indices.size(), gpu.graphics, *gpu.pool);
        mWireframe.CreateVertexBuffer(*gpu.device, vertices.data(), sizeof(Vertex) * vertices.size(), vertices.size(), gpu.graphics, *gpu.pool);
    }
    else{
        mWireframe.UpdateIndexData(*gpu.device, indices.data(), gpu.graphics, *gpu.pool);
        mWireframe.UpdateVertexData(*gpu.device, vertices.data(), gpu.graphics, *gpu.pool);
    }
}